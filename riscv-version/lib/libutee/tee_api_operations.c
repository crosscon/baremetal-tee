// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (c) 2014, STMicroelectronics International N.V.
 * Copyright (c) 2021, SumUp Services GmbH
 */
#include <assert.h>
#include <config.h>
#include <stdlib.h>
#include <string.h>
#include <string_ext.h>
#include <tee_api.h>
#include <tee_api_defines_extensions.h>
#include <tee_internal_api_extensions.h>
#include <utee_syscalls.h>
#include <utee_defines.h>
#include <util.h>
#include "tee_api_private.h"

#include <rand.h>
// #include <bip39_tee.h>
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/entropy.h"


struct __TEE_OperationHandle {
	TEE_OperationInfo info;
	TEE_ObjectHandle key1;
	TEE_ObjectHandle key2;
	uint32_t operationState;/* Operation state : INITIAL or ACTIVE */

	/*
	 * buffer to collect complete blocks or to keep a complete digest
	 * for TEE_DigestExtract().
	 */
	uint8_t *buffer;
	bool buffer_two_blocks;	/* True if two blocks need to be buffered */
	size_t block_size;	/* Block size of cipher */
	size_t buffer_offs;	/* Offset in buffer */
	uint32_t state;		/* Handle to state in TEE Core */
};

/* Cryptographic Operations API - Generic Operation Functions */

int mbedtls_hardware_poll(void *data, unsigned char *output, size_t len, size_t *olen)
{
	TEE_GenerateRandom(output, len);
    *olen = len;
    return 0;
}

/**
 * @brief Converts Core API algorithm types to MBEDTLS PSA API algorithm types
 * 
 * @param type CORE API algorithm types
 * 
 * @return If it is success, returns MBEDTLS PSA API algorithm types else returns 0
*/
static uint32_t get_algorithmType(uint32_t type)
{    
    switch (type)
    {
        case TEE_ALG_AES_ECB_NOPAD:     return PSA_ALG_ECB_NO_PADDING;
        case TEE_ALG_AES_CBC_NOPAD:     return PSA_ALG_CBC_NO_PADDING;
        case TEE_ALG_AES_CTR:           return PSA_ALG_CTR;
        //case TEE_ALG_AES_CTS:           return 0;
        case TEE_ALG_AES_XTS:           return PSA_ALG_XTS;
        case TEE_ALG_AES_CBC_MAC_NOPAD: return PSA_ALG_CBC_MAC;
        //case TEE_ALG_AES_CBC_MAC_PKCS5: return 0;
        case TEE_ALG_AES_CMAC:          return PSA_ALG_CMAC;
        case TEE_ALG_AES_CCM:           return PSA_ALG_CCM;
        case TEE_ALG_AES_GCM:           return PSA_ALG_GCM;

        case TEE_ALG_SHA3_256:          return PSA_ALG_SHA3_256;
        case TEE_ALG_ECDSA_SHA3_256:    return PSA_ALG_ECDSA(MBEDTLS_MD_SHA3_256);

        case TEE_ALG_SHA256:            return PSA_ALG_SHA_256;
        case TEE_ALG_HMAC_SHA256:       return PSA_ALG_HMAC(PSA_ALG_SHA_256);
        case TEE_ALG_ECDSA_SHA256:      return PSA_ALG_ECDSA(PSA_ALG_SHA_256);

        case TEE_ALG_SHA3_384:          return PSA_ALG_SHA3_384;
        case TEE_ALG_ECDSA_SHA3_384:    return PSA_ALG_ECDSA(PSA_ALG_SHA3_384);

        case TEE_ALG_SHA384:            return PSA_ALG_SHA_384;
        case TEE_ALG_HMAC_SHA384:       return PSA_ALG_HMAC(PSA_ALG_SHA_384);
        case TEE_ALG_ECDSA_SHA384:      return PSA_ALG_ECDSA(PSA_ALG_SHA_384);

        case TEE_ALG_SHA3_512:          return PSA_ALG_SHA3_512;
        case TEE_ALG_ECDSA_SHA3_512:    return PSA_ALG_ECDSA(PSA_ALG_SHA3_512);

        case TEE_ALG_SHA512:            return PSA_ALG_SHA_512;
        case TEE_ALG_HMAC_SHA512:       return PSA_ALG_HMAC(PSA_ALG_SHA_512);
        case TEE_ALG_ECDSA_SHA512:      return PSA_ALG_ECDSA(PSA_ALG_SHA_512);

        default:                        return 0;
    }
}

/**
 * @brief Allocates the psa cipher operation struct (of MBEDTLS) and sets the default init settings
 * 
 * @return In case of success, it returns psa_cipher_operation_t struct else NULL
*/
static psa_cipher_operation_t* cipher_operationInit(void)
{
    psa_cipher_operation_t* cipher_op = (psa_cipher_operation_t*)calloc(1, sizeof(psa_cipher_operation_t));
    if(!cipher_op){
        return NULL;
    }

    cipher_op->private_default_iv_length = 0;
    cipher_op->private_id = 0;
    cipher_op->private_iv_required = 0;
    cipher_op->private_iv_set = 0;

    return cipher_op;
}

/**
 * @brief This function release the memory allocated by psa_cipher_operation_t struct
*/
static void cipher_operationDeinit(psa_cipher_operation_t* cipher_op)
{
    if(cipher_op)
        free(cipher_op);
}

/**
 * @brief Allocates the psa hash operation struct and sets the default init settings
 * 
 * @return If it's succes, it returns psa_hash_operation_t struct else NULL
*/
static psa_hash_operation_t* hash_operationInit(uint32_t alg)
{
    psa_hash_operation_t* hash_op = (psa_hash_operation_t*)calloc(1, sizeof(psa_hash_operation_t));
    if(!hash_op)
        return NULL;

    hash_op->private_id = 0;
    if(psa_hash_setup(hash_op, alg) != 0){
        free(hash_op);
        hash_op = NULL;
    }

    return hash_op;
}

/**
 * @brief This function release the memory allocated for the psa_hash_operation_t struct
*/
static void hash_operationDeInit(psa_hash_operation_t* hash_op)
{
    if(hash_op)
        free(hash_op);
}

/**
 * @brief Allocates the psa mac operation struct and sets the default init settings
 * 
 * @return If it's succes, it returns psa_mac_operation_t struct else NULL
*/
static psa_mac_operation_t* mac_operationInit(void)
{
    psa_mac_operation_t *mac_op = (psa_mac_operation_t*)calloc(1, sizeof(psa_mac_operation_t));
    if(!mac_op)
        return NULL;

    mac_op->private_id = 0;
    mac_op->private_is_sign = 0;
    mac_op->private_mac_size = 0;  

    return mac_op;
}

/**
 * @brief This function release the memory allocated for the psa_mac_operation_t struct
*/
static void mac_operationDeInit(psa_mac_operation_t* mac_op)
{
    if(mac_op)
        free(mac_op);
}

/**
 * @brief Initializes the correct PSA API CRYPTO structures based on the given mode and algorithm
 *
 * @param op    TEE operation Handle that holds the relevant parameter for crypto opeartions
 * @param mode  Crypto operations type (e.g., Encrpyt, Decrpyt, Sign, Verify etc.)
 * @param alg   Crypto operation algorithm
 *  
 * @return 0 if the operation is initialized successfully, -1 otherwise
*/
static int mbed_operationsInit(__TEE_OperationHandle *op, uint32_t mode, uint32_t alg)
{
    switch (mode)
    {
        // Symmetric Cipher Functions
        case TEE_MODE_ENCRYPT:  
        case TEE_MODE_DECRYPT:
            op->cipher_op = cipher_operationInit();
            if(!op->cipher_op)
                return -1;
            break;

        // Asymmetric Functios 
        case TEE_MODE_SIGN:    
        case TEE_MODE_VERIFY:  return 0;

        // MAC Functions   
        case TEE_MODE_MAC:
            op->mac_op = mac_operationInit();
            if(!op->mac_op)
                return -1;
            break;

        // Message Digest(HASH) Functions
        case TEE_MODE_DIGEST:
            // If there is no key set for signinf and verification of the proccess, we need to initalize PSA API
            if(psa_crypto_init() != 0)
                return -1;   
            op->hash_op = hash_operationInit(alg);
            if(!op->hash_op)
                return -1;
            break;

        default:
            EMSG("Invalid operation mod");
            return -1;    
    }

    return 0;
}

TEE_Result TEE_AllocateOperation(TEE_OperationHandle *operation,
				 uint32_t algorithm, uint32_t mode,
				 uint32_t maxKeySize)
{
	__TEE_OperationHandle *temp_op = (__TEE_OperationHandle*)malloc(sizeof(__TEE_OperationHandle));
    if(!temp_op){
        EMSG("Allocate operation failed");
        return TEE_ERROR_BAD_PARAMETERS;
    }

    // Intialize the PSA Crypto API
    if(psa_crypto_init() != PSA_SUCCESS){
        EMSG("PSA  cryto init failed");
        free(temp_op);
        return TEE_ERROR_BAD_PARAMETERS;
    }

    // Convert TEE crytpo algortihm to PSA API crypto algorithm
    uint32_t alg = get_algorithmType(algorithm);

    // Initialize relavent mode for psa crytpo api (like encryption, signature, mac etc.)
    if(mbed_operationsInit(temp_op, mode, alg) != 0)
    {
        EMSG("MOD initializing err");
        free(temp_op);
        return TEE_ERROR_BAD_STATE;
    }

    temp_op->info.algorithm = algorithm;
    temp_op->info.mode = mode;
    temp_op->info.keySize = maxKeySize;
    temp_op->key_id = 0;

    *operation = (void*)temp_op;

    return TEE_SUCCESS;
}

/**
 * @brief Deinitialize PSA API Crpyto operations based on the given mode and algorithm
 * 
 * @param op    TEE operation Handle that holds the relevant parameters for crypto opeartions
 * @param mode  Crypto operations type (e.g., Encrpyt, Decrpyt, Sign, Verify etc.)
 * 
*/
static void mbed_operationsDeInit(__TEE_OperationHandle *op, uint32_t mode)
{
    switch (mode)
    {
        //   Symmetric Cipher Functions
        case TEE_MODE_ENCRYPT:  
        case TEE_MODE_DECRYPT: cipher_operationDeinit(op->cipher_op); break;
        //   Asymmetric Functios 
        /*case TEE_MODE_SIGN:     
        case TEE_MODE_VERIFY:   return NULL;*/
        //   MAC Functions   
        case TEE_MODE_MAC:      mac_operationDeInit(op->mac_op);  break;
        //  Message Digest(HASH) Functions
        case TEE_MODE_DIGEST:   hash_operationDeInit(op->hash_op); break;
        default:
            EMSG("Invalid operation mod");
            return;    
    }
}

void TEE_FreeOperation(TEE_OperationHandle operation)
{
	if(operation)
    {
        __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;

        // Asymmetric signing and verification proccess might not use the PSA API,
        // if you want to set x and y values for eliptic curve for signature and verification. 
        // The if statement is used to check if the key_id is set or not, which allows us to understand
        // which PSA API was used for the operation and which elements should be freed.
        if((op->key_id != 0) || (op->info.mode == TEE_MODE_DIGEST))
        {
            mbed_operationsDeInit(op, op->info.mode);
            if(op->key_id != 0) 
                psa_destroy_key(op->key_id);
            
            mbedtls_psa_crypto_free();
        }else{
            mbedtls_ecdsa_free(&op->ctx_sign);
            mbedtls_ecdsa_free(&op->ctx_verify);
            mbedtls_ecp_point_free(&op->Q);
            mbedtls_ctr_drbg_free(&op->ctr_drbg);
            mbedtls_entropy_free(&op->entropy);
        }       

        // Free the operation handle
        free(op); 
    }        
}

void __GP11_TEE_FreeOperation(TEE_OperationHandle operation)
{
	if (operation == TEE_HANDLE_NULL)
		TEE_Panic(0);
	TEE_FreeOperation(operation);
}

void TEE_GetOperationInfo(TEE_OperationHandle operation,
			  TEE_OperationInfo *operationInfo)
{
	if (operation == TEE_HANDLE_NULL)
		TEE_Panic(0);

	__utee_check_out_annotation(operationInfo, sizeof(*operationInfo));

	*operationInfo = operation->info;
	if (operationInfo->handleState & TEE_HANDLE_FLAG_EXPECT_TWO_KEYS) {
		operationInfo->keySize = 0;
		operationInfo->requiredKeyUsage = 0;
	}
}

TEE_Result TEE_GetOperationInfoMultiple(TEE_OperationHandle op,
					TEE_OperationInfoMultiple *op_info,
					size_t *size)
{
	TEE_Result res = TEE_SUCCESS;
	TEE_ObjectInfo kinfo = { };
	size_t max_key_count = 0;
	bool two_keys = false;

	if (op == TEE_HANDLE_NULL) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	__utee_check_outbuf_annotation(op_info, size);

	if (*size < sizeof(*op_info)) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}
	max_key_count = (*size - sizeof(*op_info)) /
			sizeof(TEE_OperationInfoKey);

	TEE_MemFill(op_info, 0, *size);

	/* Two keys flag (TEE_ALG_AES_XTS only) */
	two_keys = op->info.handleState & TEE_HANDLE_FLAG_EXPECT_TWO_KEYS;

	if (op->info.mode == TEE_MODE_DIGEST) {
		op_info->numberOfKeys = 0;
	} else if (!two_keys) {
		if (max_key_count < 1) {
			res = TEE_ERROR_SHORT_BUFFER;
			goto out;
		}

		res = TEE_GetObjectInfo1(op->key1, &kinfo);
		/* Key1 is not a valid handle, "can't happen". */
		if (res)
			goto out;

		op_info->keyInformation[0].keySize = kinfo.objectSize;
		op_info->keyInformation[0].requiredKeyUsage =
			op->info.requiredKeyUsage;
		op_info->numberOfKeys = 1;
	} else {
		if (max_key_count < 2) {
			res = TEE_ERROR_SHORT_BUFFER;
			goto out;
		}

		res = TEE_GetObjectInfo1(op->key1, &kinfo);
		/* Key1 is not a valid handle, "can't happen". */
		if (res)
			goto out;

		op_info->keyInformation[0].keySize = kinfo.objectSize;
		op_info->keyInformation[0].requiredKeyUsage =
			op->info.requiredKeyUsage;

		res = TEE_GetObjectInfo1(op->key2, &kinfo);
		/* Key2 is not a valid handle, "can't happen". */
		if (res)
			goto out;

		op_info->keyInformation[1].keySize = kinfo.objectSize;
		op_info->keyInformation[1].requiredKeyUsage =
			op->info.requiredKeyUsage;

		op_info->numberOfKeys = 2;
	}

	op_info->algorithm = op->info.algorithm;
	op_info->operationClass = op->info.operationClass;
	op_info->mode = op->info.mode;
	op_info->digestLength = op->info.digestLength;
	op_info->maxKeySize = op->info.maxKeySize;
	op_info->handleState = op->info.handleState;
	op_info->operationState = op->operationState;

out:
	if (res != TEE_SUCCESS &&
	    res != TEE_ERROR_SHORT_BUFFER)
		TEE_Panic(res);

	return res;
}

TEE_Result
__GP11_TEE_GetOperationInfoMultiple(TEE_OperationHandle operation,
				    TEE_OperationInfoMultiple *info,
				    uint32_t *operationSize)
{
	TEE_Result res = TEE_SUCCESS;
	size_t s = 0;

	__utee_check_gp11_outbuf_annotation(info, operationSize);
	s = *operationSize;
	res = TEE_GetOperationInfoMultiple(operation, info, &s);
	*operationSize = s;
	return res;
}

static void reset_operation_state(TEE_OperationHandle op)
{
	op->operationState = TEE_OPERATION_STATE_INITIAL;

	if (op->info.operationClass == TEE_OPERATION_DIGEST) {
		TEE_Result res = _utee_hash_init(op->state, NULL, 0);

		if (res != TEE_SUCCESS)
			TEE_Panic(res);
		op->info.handleState |= TEE_HANDLE_FLAG_INITIALIZED;
	} else {
		op->info.handleState &= ~TEE_HANDLE_FLAG_INITIALIZED;
	}
}

void TEE_ResetOperation(TEE_OperationHandle operation)
{
	if (operation == TEE_HANDLE_NULL)
		TEE_Panic(0);

	if (!(operation->info.handleState & TEE_HANDLE_FLAG_KEY_SET))
		TEE_Panic(0);

	reset_operation_state(operation);
}

/**
 * @brief Converts TEE Core API ECC (Elliptic Curve Crypto) into to MBEDTLS ECC 
 * 
 * @param alg TEE Core API ECC type
 * 
 * @return If it is success, returns MBEDTLS ECC else returns 0
*/
static uint32_t get_eccAlgorithm(uint32_t alg)
{
    switch (alg)
    {
        case TEE_ECC_CURVE_NIST_P192:  return MBEDTLS_ECP_DP_SECP192R1;
        case TEE_ECC_CURVE_NIST_P224:  return MBEDTLS_ECP_DP_SECP224R1;
        case TEE_ECC_CURVE_NIST_P256:  return MBEDTLS_ECP_DP_SECP256R1;
        case TEE_ECC_CURVE_NIST_P384:  return MBEDTLS_ECP_DP_SECP384R1;
        case TEE_ECC_CURVE_NIST_P521:  return MBEDTLS_ECP_DP_SECP521R1;
        case TEE_ECC_CURVE_BSI_P256r1: return MBEDTLS_ECP_DP_BP256R1;
        case TEE_ECC_CURVE_BSI_P384r1: return MBEDTLS_ECP_DP_BP384R1;
        case TEE_ECC_CURVE_BSI_P512r1: return MBEDTLS_ECP_DP_BP512R1;
        default: return 0;
    }
}

/**
 * @brief Generate a key pair for the given ECC algorithm
 * 
 * @param op pointer to the operation handle, were the context is stored
 * @param key pointer to the object handle, were attributes are stored and were the key will be stored
 * 
 * @return TEE_SUCCESS if the key pair is generated successfully, TEE_FAILED otherwise
*/
static int generate_ecdsaKeyPair(__TEE_OperationHandle *op, __TEE_ObjectHandle *key)
{
    // Initialize neccessary things for set x and y coordinate and generate key pair for eliptic curve
    mbedtls_ecdsa_init(&op->ctx_sign);
    mbedtls_ecdsa_init(&op->ctx_verify);
    mbedtls_ecp_point_init(&op->Q);
    mbedtls_entropy_init(&op->entropy);
    mbedtls_ctr_drbg_init(&op->ctr_drbg);

    // Convert TEE algorithm type to MBED-TLS ECP algorithm type for eliptic curve
    uint32_t alg = get_eccAlgorithm(key->attrs[3].content.value.a);

    // The attributes contains the value of X and Y coordinates of the public key used for key generation of the private key
    int ret = mbedtls_ctr_drbg_seed(&op->ctr_drbg, mbedtls_entropy_func, &op->entropy, NULL, 0);
    if(ret != 0){
        EMSG("Failed mbedtls_ctr_drbg_seed: -0x%04x\n", -ret);
        goto end;
    }

    ret = mbedtls_ecp_group_load(&op->ctx_sign.private_grp, alg);
    if(ret != 0){
        EMSG("Failed mbedtls_ecp_group_load: -0x%04x\n", ret);
        goto end;
    }

    ret = mbedtls_mpi_read_binary(&op->ctx_sign.private_d, (const unsigned char*)key->attrs[0].content.ref.buffer, 
                                        key->attrs[0].content.ref.length); // 32 bytes for SECP256R1
    if(ret != 0){
        EMSG("mbedtls_mpi_read_binary failed for private key\n");
        goto end;
    }
    
    ret = mbedtls_mpi_read_binary(&op->ctx_sign.private_Q.private_X, (const unsigned char*)key->attrs[1].content.ref.buffer, 
                                    key->attrs[1].content.ref.length);
    if(ret != 0){
        EMSG("mbedtls_mpi_read_binary failed for private key\n");
        goto end;
    }

    ret = mbedtls_mpi_read_binary(&op->ctx_sign.private_Q.private_Y, (const unsigned char*)key->attrs[2].content.ref.buffer, 
                                    key->attrs[2].content.ref.length);
    if(ret != 0){
        EMSG("mbedtls_mpi_read_binary failed for private key\n");
        goto end;
    }
    ret = mbedtls_ecdsa_genkey(&op->ctx_sign, alg, mbedtls_ctr_drbg_random, &op->ctr_drbg);
    if(ret != 0){
        EMSG(" failed\n  ! mbedtls_ecdsa_genkey returned %d\n", ret);
        goto end;
    }

    mbedtls_ecp_group_id grp_id = mbedtls_ecp_keypair_get_group_id(&op->ctx_sign);

    ret = mbedtls_ecp_export(&op->ctx_sign, NULL, NULL, &op->Q);
    if(ret != 0){
        EMSG(" failed\n  ! mbedtls_ecp_export returned %d\n", ret);
        goto end;
    }

    ret = mbedtls_ecp_set_public_key(grp_id, &op->ctx_verify, &op->Q);
    if(ret != 0){
        EMSG(" failed\n  ! mbedtls_ecp_set_public_key returned %d\n", ret);
        goto end;
    }
    
    return TEE_SUCCESS;
end:
    mbedtls_ecdsa_free(&op->ctx_sign);
    mbedtls_ecdsa_free(&op->ctx_verify);
    mbedtls_ecp_point_free(&op->Q);
    mbedtls_ctr_drbg_free(&op->ctr_drbg);
    mbedtls_entropy_free(&op->entropy);

    return TEE_ERROR_GENERIC;
}

/**
 * @brief Returns key len in bytes according to the given TEE CORE API crpyto algorithm type
 * 
 * @param objectType TEE Core API crypto algorithm
 * 
 * @return if it's success, returns key len as a byte else 0
*/

static uint32_t get_keySize(uint32_t objectType)
{
    switch(objectType)
    {
        case TEE_ALG_AES_ECB_NOPAD:     
        case TEE_ALG_AES_CBC_NOPAD:     
        case TEE_ALG_AES_CTR:           
        //case TEE_ALG_AES_CTS:           
        case TEE_ALG_AES_XTS:           
        case TEE_ALG_AES_CBC_MAC_NOPAD: 
        //case TEE_ALG_AES_CBC_MAC_PKCS5: 
        case TEE_ALG_AES_CMAC:           
        case TEE_ALG_AES_CCM:           
        case TEE_ALG_AES_GCM:           return 32;

        case TEE_ALG_SHA3_256:          
        case TEE_ALG_ECDSA_SHA3_256:    
        case TEE_ALG_SHA256:
        case TEE_ALG_HMAC_SHA256:
        case TEE_ALG_ECDSA_SHA256:      return 32;

        case TEE_ALG_SHA3_384:       
        case TEE_ALG_ECDSA_SHA3_384:  
        case TEE_ALG_SHA384:
        case TEE_ALG_HMAC_SHA384:
        case TEE_ALG_ECDSA_SHA384:      return 48;

        case TEE_ALG_SHA3_512:          
        case TEE_ALG_ECDSA_SHA3_512:    
        case TEE_ALG_SHA512:
        case TEE_ALG_HMAC_SHA512:
        case TEE_ALG_ECDSA_SHA512:      return 64;
        
        default:
            return 0;
    }
}

/**
 * @brief Converts TEE Core API algorithm to MBEDTLS PSA API key type
 * 
 * @param alg TEE Core API crypto algorithm
 * 
 * @return If it is success, MBEDTLS PSA API key type else PSA_KEY_USAGE_VERIFY_MESSAGE
*/
static uint32_t convert_alg2KeyType(uint32_t alg)
{
    switch (alg)
    {   
        case TEE_ALG_ECDSA_SHA256:  
        case TEE_ALG_ECDSA_SHA384: 
        case TEE_ALG_ECDSA_SHA512:
        case TEE_ALG_ECDSA_SHA3_256:
        case TEE_ALG_ECDSA_SHA3_384:
        case TEE_ALG_ECDSA_SHA3_512:  return PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1);
        
        default: return PSA_KEY_USAGE_VERIFY_MESSAGE;
    }
}

/**
 * @brief Check if the expected key len in bytes, according to the given TEE CORE API crypto algorithm type,
 *  matches the given key len
 * 
 * @param alg TEE Core API crypto algorithm
 * @param key_len key length in bytes to check
 * 
 * @return if it's success, returns 0 else -1
*/
static int8_t check_keySize(uint32_t alg, uint32_t key_len)
{
    uint32_t len = 8 * get_keySize(alg);

    if(key_len != len){
        return -1;
    }

    return 0;
}

/**
 * @brief Converts TEE Core API mode to MBEDTLS PSA API key usage type
 * 
 * @param mode TEE Core API mode
 * 
 * @return If it is success, MBEDTLS PSA API key usage type else returns 0
*/
static uint32_t get_modeType(uint32_t mode)
{
    switch (mode)
    {
        case TEE_MODE_ENCRYPT:  return PSA_KEY_USAGE_ENCRYPT;
        case TEE_MODE_DECRYPT:  return PSA_KEY_USAGE_DECRYPT;
        case TEE_MODE_SIGN:     return PSA_KEY_USAGE_SIGN_HASH | PSA_KEY_USAGE_VERIFY_HASH;
        case TEE_MODE_VERIFY:   return PSA_KEY_USAGE_VERIFY_HASH | PSA_KEY_USAGE_SIGN_HASH;
        case TEE_MODE_MAC:      return PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_VERIFY_MESSAGE;
        case TEE_MODE_DIGEST:   return 0;
        default:                return 0;
    }
}

/**
 * @brief Converts TEE Core API mode to MBEDTLS PSA API key type
 * 
 * @param mode TEE Core API mode
 * @param alg TEE Core API crypto algorithm
 * 
 * 
 * @return If it is success, MBEDTLS PSA API key type else returns 0
*/
static uint32_t get_keyType(uint32_t mode, uint32_t alg)
{
    switch (mode)
    {
        case TEE_MODE_ENCRYPT:  
        case TEE_MODE_DECRYPT:  return PSA_KEY_TYPE_AES;
        case TEE_MODE_SIGN:     return convert_alg2KeyType(alg);
        case TEE_MODE_VERIFY:   return PSA_KEY_USAGE_VERIFY_MESSAGE;
        case TEE_MODE_MAC:      return PSA_KEY_TYPE_HMAC;
        case TEE_MODE_DIGEST:   return 0;
        default:                return 0; 
    }
}

TEE_Result TEE_SetOperationKey(TEE_OperationHandle operation,
			       TEE_ObjectHandle key)
{
	if(!operation){
        EMSG("Operation is null");
        return TEE_ERROR_BAD_PARAMETERS;
    }

    if(!key){
        EMSG("Key is null");
        return TEE_ERROR_BAD_PARAMETERS;
    }

    __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;  
    __TEE_ObjectHandle *obj = (__TEE_ObjectHandle*)key;

    if(!obj->buffer){
        EMSG("Key or content is null");
        return TEE_ERROR_BAD_PARAMETERS;
    }

    // Extract the attributes from the object to understand if the key should be generated or set
    int attr_flag = (obj->attrs[0].attributeID + obj->attrs[1].attributeID + 
                            obj->attrs[2].attributeID + obj->attrs[3].attributeID) > 0 ? 1 : 0;
    if((obj->obj_type == TEE_TYPE_ECDSA_KEYPAIR) && (attr_flag != 0))
    {
        // If the key is ECDSA key pair and the attributes are set, then the key should be generated
        // starting from the attributes that contain the x and y coordinates of the public key
        op->key_id = 0;
        return generate_ecdsaKeyPair(op, obj);
    }
    
    // Check if the key size (stored in the obj or generated before) is correct according to the algorithm
    if(check_keySize(op->info.algorithm, obj->key_len) != 0){
        EMSG("Key size error");
        return TEE_ERROR_GENERIC;
    }

    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;

    uint32_t key_alg = get_algorithmType(op->info.algorithm);
    uint32_t key_flag = get_modeType(op->info.mode);
    uint32_t key_type = get_keyType(op->info.mode, op->info.algorithm);
    
    psa_set_key_algorithm(&attributes, key_alg);
    psa_set_key_usage_flags(&attributes, key_flag);
    psa_set_key_type(&attributes, key_type);
    psa_set_key_bits(&attributes, obj->key_len);

    // Import the crypto key into the PSA API of MbedTLS
    int res = psa_import_key(&attributes, (const uint8_t*)obj->buffer, obj->key_len/8, &op->key_id);
    if(res != PSA_SUCCESS)
    {
        EMSG("Failed to set key:");
        return TEE_ERROR_GENERIC;
    }

    if(op->key_id != 0)
    {
        op->key1 = key;
    }

    return TEE_SUCCESS;
}

TEE_Result __GP11_TEE_SetOperationKey(TEE_OperationHandle operation,
				      TEE_ObjectHandle key)
{
	// if (operation == TEE_HANDLE_NULL ||
	//     operation->operationState != TEE_OPERATION_STATE_INITIAL)
	// 	TEE_Panic(0);

	return TEE_SetOperationKey(operation, key);
}

static TEE_Result set_operation_key2(TEE_OperationHandle operation,
				     TEE_ObjectHandle key1,
				     TEE_ObjectHandle key2)
{
	TEE_Result res;
	uint32_t key_size = 0;
	TEE_ObjectInfo key_info1;
	TEE_ObjectInfo key_info2;

	if (operation == TEE_HANDLE_NULL) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	/*
	 * Key1/Key2 and/or are not initialized and
	 * Either both keys are NULL or both are not NULL
	 */
	if (!key1 && !key2) {
		/* Clear the keys */
		TEE_ResetTransientObject(operation->key1);
		TEE_ResetTransientObject(operation->key2);
		operation->info.handleState &= ~TEE_HANDLE_FLAG_KEY_SET;
		if (operation->operationState != TEE_OPERATION_STATE_INITIAL)
			reset_operation_state(operation);
		return TEE_SUCCESS;
	} else if (!key1 || !key2) {
		/* Both keys are obviously not valid. */
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	/* No key for digest operation */
	if (operation->info.operationClass == TEE_OPERATION_DIGEST) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	/* Two keys flag expected (TEE_ALG_AES_XTS and TEE_ALG_SM2_KEP only) */
	if ((operation->info.handleState & TEE_HANDLE_FLAG_EXPECT_TWO_KEYS) ==
	    0) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	res = TEE_GetObjectInfo1(key1, &key_info1);
	/* Key1 is not a valid handle */
	if (res != TEE_SUCCESS)
		goto out;

	/* Supplied key has to meet required usage */
	if ((key_info1.objectUsage & operation->info.
	     requiredKeyUsage) != operation->info.requiredKeyUsage) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	res = TEE_GetObjectInfo1(key2, &key_info2);
	/* Key2 is not a valid handle */
	if (res != TEE_SUCCESS) {
		if (res == TEE_ERROR_CORRUPT_OBJECT)
			res = TEE_ERROR_CORRUPT_OBJECT_2;
		goto out;
	}

	/* Supplied key has to meet required usage */
	if ((key_info2.objectUsage & operation->info.
	     requiredKeyUsage) != operation->info.requiredKeyUsage) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	/*
	 * All the multi key algorithm currently supported requires the keys to
	 * be of equal size.
	 */
	if (key_info1.objectSize != key_info2.objectSize) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;

	}

	if (operation->info.maxKeySize < key_info1.objectSize) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	/*
	 * Odd that only the size of one key should be reported while
	 * size of two key are used when allocating the operation.
	 */
	key_size = key_info1.objectSize;

	TEE_ResetTransientObject(operation->key1);
	TEE_ResetTransientObject(operation->key2);
	operation->info.handleState &= ~TEE_HANDLE_FLAG_KEY_SET;

	res = TEE_CopyObjectAttributes1(operation->key1, key1);
	if (res != TEE_SUCCESS)
		goto out;
	res = TEE_CopyObjectAttributes1(operation->key2, key2);
	if (res != TEE_SUCCESS) {
		if (res == TEE_ERROR_CORRUPT_OBJECT)
			res = TEE_ERROR_CORRUPT_OBJECT_2;
		goto out;
	}

	operation->info.handleState |= TEE_HANDLE_FLAG_KEY_SET;

	operation->info.keySize = key_size;

	if (operation->operationState != TEE_OPERATION_STATE_INITIAL)
		reset_operation_state(operation);
out:
	if (res != TEE_SUCCESS  &&
	    res != TEE_ERROR_CORRUPT_OBJECT &&
	    res != TEE_ERROR_CORRUPT_OBJECT_2 &&
	    res != TEE_ERROR_STORAGE_NOT_AVAILABLE &&
	    res != TEE_ERROR_STORAGE_NOT_AVAILABLE_2)
		TEE_Panic(res);

	return res;
}

TEE_Result TEE_SetOperationKey2(TEE_OperationHandle operation,
				TEE_ObjectHandle key1, TEE_ObjectHandle key2)
{
	if (operation != TEE_HANDLE_NULL && key1 && key1 == key2)
		return TEE_ERROR_SECURITY;

	return set_operation_key2(operation, key1, key2);
}

TEE_Result __GP11_TEE_SetOperationKey2(TEE_OperationHandle operation,
				       TEE_ObjectHandle key1,
				       TEE_ObjectHandle key2)
{
	if (operation == TEE_HANDLE_NULL ||
	    operation->operationState != TEE_OPERATION_STATE_INITIAL)
		TEE_Panic(0);

	return set_operation_key2(operation, key1, key2);
}

void TEE_CopyOperation(TEE_OperationHandle dst_op, TEE_OperationHandle src_op)
{
	TEE_Result res;

	if (dst_op == TEE_HANDLE_NULL || src_op == TEE_HANDLE_NULL)
		TEE_Panic(0);
	if (dst_op->info.algorithm != src_op->info.algorithm)
		TEE_Panic(0);
	if (dst_op->info.mode != src_op->info.mode)
		TEE_Panic(0);
	if (src_op->info.operationClass != TEE_OPERATION_DIGEST) {
		TEE_ObjectHandle key1 = TEE_HANDLE_NULL;
		TEE_ObjectHandle key2 = TEE_HANDLE_NULL;

		if (src_op->info.handleState & TEE_HANDLE_FLAG_KEY_SET) {
			key1 = src_op->key1;
			key2 = src_op->key2;
		}

		if ((src_op->info.handleState &
		     TEE_HANDLE_FLAG_EXPECT_TWO_KEYS) == 0) {
			TEE_SetOperationKey(dst_op, key1);
		} else {
			TEE_SetOperationKey2(dst_op, key1, key2);
		}
	}
	dst_op->info.handleState = src_op->info.handleState;
	dst_op->info.keySize = src_op->info.keySize;
	dst_op->info.digestLength = src_op->info.digestLength;
	dst_op->operationState = src_op->operationState;

	if (dst_op->buffer_two_blocks != src_op->buffer_two_blocks ||
	    dst_op->block_size != src_op->block_size)
		TEE_Panic(0);

	if (dst_op->buffer != NULL) {
		size_t sz = src_op->block_size;

		if (src_op->buffer == NULL)
			TEE_Panic(0);

		if (src_op->buffer_two_blocks)
			sz *= 2;
		memcpy(dst_op->buffer, src_op->buffer, sz);
		dst_op->buffer_offs = src_op->buffer_offs;
	} else if (src_op->buffer != NULL) {
		TEE_Panic(0);
	}

	res = _utee_cryp_state_copy(dst_op->state, src_op->state);
	if (res != TEE_SUCCESS)
		TEE_Panic(res);
}

/* Cryptographic Operations API - Message Digest Functions */

static void init_hash_operation(TEE_OperationHandle operation, const void *IV,
				uint32_t IVLen)
{
	TEE_Result res;

	/*
	 * Note : IV and IVLen are never used in current implementation
	 * This is why coherent values of IV and IVLen are not checked
	 */
	res = _utee_hash_init(operation->state, IV, IVLen);
	if (res != TEE_SUCCESS)
		TEE_Panic(res);
	operation->buffer_offs = 0;
	operation->info.handleState |= TEE_HANDLE_FLAG_INITIALIZED;
}

void TEE_DigestUpdate(TEE_OperationHandle operation,
		      const void *chunk, size_t chunkSize)
{
	TEE_Result res = TEE_ERROR_GENERIC;

	if (operation == TEE_HANDLE_NULL ||
	    operation->info.operationClass != TEE_OPERATION_DIGEST)
		TEE_Panic(0);

	operation->operationState = TEE_OPERATION_STATE_ACTIVE;

	res = _utee_hash_update(operation->state, chunk, chunkSize);
	if (res != TEE_SUCCESS)
		TEE_Panic(res);
}

void __GP11_TEE_DigestUpdate(TEE_OperationHandle operation,
			     const void *chunk, uint32_t chunkSize)
{
	return TEE_DigestUpdate(operation, chunk, chunkSize);
}

TEE_Result TEE_DigestDoFinal(TEE_OperationHandle operation, const void *chunk,
			     size_t chunkLen, void *hash, size_t *hashLen)
{
	TEE_Result res = TEE_SUCCESS;

	digest_from_data(chunk, chunkLen, hash);

	return res;
}

TEE_Result __GP11_TEE_DigestDoFinal(TEE_OperationHandle operation,
				    const void *chunk, uint32_t chunkLen,
				    void *hash, uint32_t *hashLen)
{
	TEE_Result res = TEE_SUCCESS;
	//size_t l = 0;
//
	//__utee_check_inout_annotation(hashLen, sizeof(*hashLen));
	//l = *hashLen;
	res = TEE_DigestDoFinal(operation, chunk, chunkLen, hash, hashLen);
	//*hashLen = l;
	return res;
}

TEE_Result TEE_DigestExtract(TEE_OperationHandle operation, void *hash,
			     size_t *hashLen)
{
	TEE_Result res = TEE_SUCCESS;
	uint64_t hl = 0;
	size_t len = 0;

	if (operation == TEE_HANDLE_NULL ||
	    operation->info.operationClass != TEE_OPERATION_DIGEST)
		TEE_Panic(0);
	__utee_check_inout_annotation(hashLen, sizeof(*hashLen));

	if (!operation->buffer) {
		/* This is an Extendable-Output Function */
		operation->info.handleState |= TEE_HANDLE_FLAG_EXTRACTING;
		operation->operationState = TEE_OPERATION_STATE_EXTRACTING;
		hl = *hashLen;
		res = _utee_hash_final(operation->state, NULL, 0, hash, &hl);
		if (res)
			TEE_Panic(0);
		*hashLen = hl;

		return TEE_SUCCESS;
	}

	if (operation->operationState != TEE_OPERATION_STATE_EXTRACTING) {
		hl = operation->block_size;
		res = _utee_hash_final(operation->state, NULL, 0,
				       operation->buffer, &hl);
		if (res)
			TEE_Panic(0);
		if (hl != operation->block_size)
			TEE_Panic(0);
		assert(!operation->buffer_offs);
		operation->info.handleState |= TEE_HANDLE_FLAG_EXTRACTING;
		operation->operationState = TEE_OPERATION_STATE_EXTRACTING;
	}

	len = MIN(operation->block_size - operation->buffer_offs, *hashLen);
	memcpy(hash, operation->buffer + operation->buffer_offs, len);
	*hashLen = len;
	operation->buffer_offs += len;

	return TEE_SUCCESS;
}

/* Cryptographic Operations API - Symmetric Cipher Functions */

void TEE_CipherInit(TEE_OperationHandle operation, const void *IV,
		    size_t IVLen)
{
	TEE_Result res;

	if (operation == TEE_HANDLE_NULL)
		TEE_Panic(0);

	if (operation->info.operationClass != TEE_OPERATION_CIPHER)
		TEE_Panic(0);

	if (!(operation->info.handleState & TEE_HANDLE_FLAG_KEY_SET) ||
	    !(operation->key1))
		TEE_Panic(0);

	if (operation->operationState != TEE_OPERATION_STATE_INITIAL)
		TEE_ResetOperation(operation);

	if (IV && IVLen) {
		if (operation->info.algorithm == TEE_ALG_AES_ECB_NOPAD ||
		    operation->info.algorithm == TEE_ALG_DES_ECB_NOPAD ||
		    operation->info.algorithm == TEE_ALG_DES3_ECB_NOPAD ||
		    operation->info.algorithm == TEE_ALG_SM4_ECB_NOPAD)
			TEE_Panic(0);
	}

	operation->operationState = TEE_OPERATION_STATE_ACTIVE;

	res = _utee_cipher_init(operation->state, IV, IVLen);
	if (res != TEE_SUCCESS)
		TEE_Panic(res);

	operation->buffer_offs = 0;
	operation->info.handleState |= TEE_HANDLE_FLAG_INITIALIZED;
}

void __GP11_TEE_CipherInit(TEE_OperationHandle operation, const void *IV,
			   uint32_t IVLen)
{
	return TEE_CipherInit(operation, IV, IVLen);
}

static TEE_Result tee_buffer_update(
		TEE_OperationHandle op,
		TEE_Result(*update_func)(unsigned long state, const void *src,
				size_t slen, void *dst, uint64_t *dlen),
		const void *src_data, size_t src_len,
		void *dest_data, uint64_t *dest_len)
{
	TEE_Result res;
	const uint8_t *src = src_data;
	size_t slen = src_len;
	uint8_t *dst = dest_data;
	size_t dlen = *dest_len;
	size_t acc_dlen = 0;
	uint64_t tmp_dlen;
	size_t l;
	size_t buffer_size;
	size_t buffer_left;

	if (!src) {
		if (slen)
			TEE_Panic(0);
		goto out;
	}

	if (op->buffer_two_blocks) {
		buffer_size = op->block_size * 2;
		buffer_left = 1;
	} else {
		buffer_size = op->block_size;
		buffer_left = 0;
	}

	if (op->buffer_offs > 0) {
		/* Fill up complete block */
		if (op->buffer_offs < op->block_size)
			l = MIN(slen, op->block_size - op->buffer_offs);
		else
			l = MIN(slen, buffer_size - op->buffer_offs);
		memcpy(op->buffer + op->buffer_offs, src, l);
		op->buffer_offs += l;
		src += l;
		slen -= l;
		if ((op->buffer_offs % op->block_size) != 0)
			goto out;	/* Nothing left to do */
	}

	/* If we can feed from buffer */
	if ((op->buffer_offs > 0) &&
	    ((op->buffer_offs + slen) >= (buffer_size + buffer_left))) {
		l = ROUNDUP(op->buffer_offs + slen - buffer_size,
				op->block_size);
		l = MIN(op->buffer_offs, l);
		tmp_dlen = dlen;
		res = update_func(op->state, op->buffer, l, dst, &tmp_dlen);
		if (res != TEE_SUCCESS)
			TEE_Panic(res);
		dst += tmp_dlen;
		dlen -= tmp_dlen;
		acc_dlen += tmp_dlen;
		op->buffer_offs -= l;
		if (op->buffer_offs > 0) {
			/*
			 * Slen is small enough to be contained in rest buffer.
			 */
			memcpy(op->buffer, op->buffer + l, buffer_size - l);
			memcpy(op->buffer + op->buffer_offs, src, slen);
			op->buffer_offs += slen;
			goto out;	/* Nothing left to do */
		}
	}

	if (slen >= (buffer_size + buffer_left)) {
		/* Buffer is empty, feed as much as possible from src */
		if (op->info.algorithm == TEE_ALG_AES_CTS)
			l = ROUNDUP(slen - buffer_size, op->block_size);
		else
			l = ROUNDUP(slen - buffer_size + 1, op->block_size);

		tmp_dlen = dlen;
		res = update_func(op->state, src, l, dst, &tmp_dlen);
		if (res != TEE_SUCCESS)
			TEE_Panic(res);
		src += l;
		slen -= l;
		dst += tmp_dlen;
		dlen -= tmp_dlen;
		acc_dlen += tmp_dlen;
	}

	/* Slen is small enough to be contained in buffer. */
	memcpy(op->buffer + op->buffer_offs, src, slen);
	op->buffer_offs += slen;

out:
	*dest_len = acc_dlen;
	return TEE_SUCCESS;
}

TEE_Result TEE_CipherUpdate(TEE_OperationHandle operation, const void *srcData,
			    size_t srcLen, void *destData, size_t *destLen)
{
	TEE_Result res;
	size_t req_dlen;
	uint64_t dl;

	if (operation == TEE_HANDLE_NULL || (!srcData && srcLen)) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}
	__utee_check_inout_annotation(destLen, sizeof(*destLen));

	if (operation->info.operationClass != TEE_OPERATION_CIPHER) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	if ((operation->info.handleState & TEE_HANDLE_FLAG_INITIALIZED) == 0) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	if (operation->operationState != TEE_OPERATION_STATE_ACTIVE) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	if (!srcData && !srcLen) {
		*destLen = 0;
		res = TEE_SUCCESS;
		goto out;
	}

	/* Calculate required dlen */
	if (operation->block_size > 1) {
		req_dlen = ((operation->buffer_offs + srcLen) /
			    operation->block_size) * operation->block_size;
	} else {
		req_dlen = srcLen;
	}
	if (operation->buffer_two_blocks) {
		if (req_dlen > operation->block_size * 2)
			req_dlen -= operation->block_size * 2;
		else
			req_dlen = 0;
	}
	/*
	 * Check that required destLen is big enough before starting to feed
	 * data to the algorithm. Errors during feeding of data are fatal as we
	 * can't restore sync with this API.
	 */
	if (*destLen < req_dlen) {
		*destLen = req_dlen;
		res = TEE_ERROR_SHORT_BUFFER;
		goto out;
	}

	dl = *destLen;
	if (operation->block_size > 1) {
		res = tee_buffer_update(operation, _utee_cipher_update, srcData,
					srcLen, destData, &dl);
	} else {
		if (srcLen > 0) {
			res = _utee_cipher_update(operation->state, srcData,
						  srcLen, destData, &dl);
		} else {
			res = TEE_SUCCESS;
			dl = 0;
		}
	}
	*destLen = dl;

out:
	if (res != TEE_SUCCESS &&
	    res != TEE_ERROR_SHORT_BUFFER)
		TEE_Panic(res);

	return res;
}

TEE_Result __GP11_TEE_CipherUpdate(TEE_OperationHandle operation,
				   const void *srcData, uint32_t srcLen,
				   void *destData, uint32_t *destLen)
{
	TEE_Result res = TEE_SUCCESS;
	size_t dl = 0;

	__utee_check_inout_annotation(destLen, sizeof(*destLen));
	dl = *destLen;
	res = TEE_CipherUpdate(operation, srcData, srcLen, destData, &dl);
	*destLen = dl;
	return res;
}

TEE_Result TEE_CipherDoFinal(TEE_OperationHandle operation,
			     const void *srcData, size_t srcLen,
			     void *destData, size_t *destLen)
{
	TEE_Result res = TEE_SUCCESS;
	uint8_t *dst = destData;
	size_t acc_dlen = 0;
	uint64_t tmp_dlen = 0;
	size_t req_dlen = 0;

	if (operation == TEE_HANDLE_NULL || (!srcData && srcLen)) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}
	if (destLen)
		__utee_check_inout_annotation(destLen, sizeof(*destLen));

	if (operation->info.operationClass != TEE_OPERATION_CIPHER) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	if ((operation->info.handleState & TEE_HANDLE_FLAG_INITIALIZED) == 0) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	if (operation->operationState != TEE_OPERATION_STATE_ACTIVE) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	/*
	 * Check that the final block doesn't require padding for those
	 * algorithms that requires client to supply padding.
	 */
	if (operation->info.algorithm == TEE_ALG_AES_ECB_NOPAD ||
	    operation->info.algorithm == TEE_ALG_AES_CBC_NOPAD ||
	    operation->info.algorithm == TEE_ALG_DES_ECB_NOPAD ||
	    operation->info.algorithm == TEE_ALG_DES_CBC_NOPAD ||
	    operation->info.algorithm == TEE_ALG_DES3_ECB_NOPAD ||
	    operation->info.algorithm == TEE_ALG_DES3_CBC_NOPAD ||
	    operation->info.algorithm == TEE_ALG_SM4_ECB_NOPAD ||
	    operation->info.algorithm == TEE_ALG_SM4_CBC_NOPAD) {
		if (((operation->buffer_offs + srcLen) % operation->block_size)
		    != 0) {
			res = TEE_ERROR_BAD_PARAMETERS;
			goto out;
		}
	}

	/*
	 * Check that required destLen is big enough before starting to feed
	 * data to the algorithm. Errors during feeding of data are fatal as we
	 * can't restore sync with this API.
	 */
	if (operation->block_size > 1) {
		req_dlen = operation->buffer_offs + srcLen;
	} else {
		req_dlen = srcLen;
	}
	if (destLen)
		tmp_dlen = *destLen;
	if (tmp_dlen < req_dlen) {
		if (destLen)
			*destLen = req_dlen;
		res = TEE_ERROR_SHORT_BUFFER;
		goto out;
	}

	if (operation->block_size > 1) {
		if (srcLen) {
			res = tee_buffer_update(operation, _utee_cipher_update,
						srcData, srcLen, dst,
						&tmp_dlen);
			if (res != TEE_SUCCESS)
				goto out;

			dst += tmp_dlen;
			acc_dlen += tmp_dlen;

			tmp_dlen = *destLen - acc_dlen;
		}
		res = _utee_cipher_final(operation->state, operation->buffer,
					 operation->buffer_offs, dst,
					 &tmp_dlen);
	} else {
		res = _utee_cipher_final(operation->state, srcData, srcLen, dst,
					 &tmp_dlen);
	}
	if (res != TEE_SUCCESS)
		goto out;

	acc_dlen += tmp_dlen;
	if (destLen)
		*destLen = acc_dlen;

	operation->info.handleState &= ~TEE_HANDLE_FLAG_INITIALIZED;

	operation->operationState = TEE_OPERATION_STATE_INITIAL;

out:
	if (res != TEE_SUCCESS &&
	    res != TEE_ERROR_SHORT_BUFFER)
		TEE_Panic(res);

	return res;
}

TEE_Result __GP11_TEE_CipherDoFinal(TEE_OperationHandle operation,
				    const void *srcData, uint32_t srcLen,
				    void *destData, uint32_t *destLen)
{
	TEE_Result res = TEE_SUCCESS;
	size_t dl = 0;

	if (destLen) {
		__utee_check_inout_annotation(destLen, sizeof(*destLen));
		dl = *destLen;
	}
	res = TEE_CipherDoFinal(operation, srcData, srcLen, destData, &dl);
	if (destLen)
		*destLen = dl;
	return res;
}

/* Cryptographic Operations API - MAC Functions */

void TEE_MACInit(TEE_OperationHandle operation, const void *IV, size_t IVLen)
{
	if(!operation){
        EMSG("Operation is null");
        goto end;
    }

    __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;
    __TEE_ObjectHandle *key = (__TEE_ObjectHandle*)op->key1;
    
    if(check_keySize(op->info.algorithm, key->key_len) != 0){
        EMSG("The given key size is invalid");
        goto end;
    }

    uint32_t alg = get_algorithmType(op->info.algorithm);

    // Initialize the MAC operation of the PSA API 
    // For HMAC with SHA, the IV is not used
	psa_mac_sign_setup(op->mac_op, op->key_id, alg);
    // if(psa_mac_sign_setup(op->mac_op, op->key_id, alg) != 0){
    //     EMSG("MAC Init failed");
    //     psa_mac_abort(op->mac_op); 
    //     goto end;       
    // }

end:
    // Do nothing

}

void __GP11_TEE_MACInit(TEE_OperationHandle operation, const void *IV,
			uint32_t IVLen)
{
	return TEE_MACInit(operation, IV, IVLen);
}

void TEE_MACUpdate(TEE_OperationHandle operation, const void *chunk,
		   size_t chunkSize)
{
	if(!operation){
        EMSG("Error in MAC Update");
        goto end;
    }
    __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;
    
    // Update the MAC operation with the input data using the PSA API
    if(psa_mac_update(op->mac_op, (const uint8_t*)chunk, chunkSize) != 0){
        psa_mac_abort(op->mac_op);
        EMSG("Error in MAC Update");
        goto end;
    }

end:
    // Do nothing
}

void __GP11_TEE_MACUpdate(TEE_OperationHandle operation, const void *chunk,
			  uint32_t chunkSize)
{
	return TEE_MACUpdate(operation, chunk, chunkSize);
}

TEE_Result TEE_MACComputeFinal(TEE_OperationHandle operation,
			       const void *message, size_t messageLen,
			       void *mac, size_t *macLen)
{
	if(!operation){
        EMSG("Operation is null");
        return TEE_ERROR_BAD_PARAMETERS;
    }
    __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;

    // If the input data is not empty, update the MAC operation with the input data
    if(message && messageLen > 0) {
        if(psa_mac_update(op->mac_op, (const uint8_t*)message, messageLen) != 0){
            EMSG("MAC Update failed");
            psa_mac_abort(op->mac_op);
            return TEE_ERROR_MAC_INVALID;
        }
    }

    // Swap the physical size of the output buffer with the logical size of the output buffer
    size_t macSize = *macLen;
    *macLen = 0;

    // Finalize the MAC operation and store the final MAC in the output buffer using the PSA API
    if(psa_mac_sign_finish(op->mac_op,(uint8_t *)mac, macSize, macLen) != 0){
        psa_mac_abort(op->mac_op);
        return TEE_ERROR_MAC_INVALID;
    }

    return TEE_SUCCESS;
}

TEE_Result __GP11_TEE_MACComputeFinal(TEE_OperationHandle operation,
				      const void *message, uint32_t messageLen,
				      void *mac, uint32_t *macLen)
{
	TEE_Result res = TEE_SUCCESS;
	size_t ml = 0;

	__utee_check_inout_annotation(macLen, sizeof(*macLen));
	ml = *macLen;
	res = TEE_MACComputeFinal(operation, message, messageLen, mac, &ml);
	*macLen = ml;
	return res;
}

TEE_Result TEE_MACCompareFinal(TEE_OperationHandle operation,
			       const void *message, size_t messageLen,
			       const void *mac, size_t macLen)
{
	TEE_Result res;
	uint8_t computed_mac[TEE_MAX_HASH_SIZE] = { 0 };
	size_t computed_mac_size = TEE_MAX_HASH_SIZE;

	if (operation->info.operationClass != TEE_OPERATION_MAC) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	if ((operation->info.handleState & TEE_HANDLE_FLAG_INITIALIZED) == 0) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	if (operation->operationState != TEE_OPERATION_STATE_ACTIVE) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	res = TEE_MACComputeFinal(operation, message, messageLen, computed_mac,
				  &computed_mac_size);
	if (res != TEE_SUCCESS)
		goto out;

	if (computed_mac_size != macLen) {
		res = TEE_ERROR_MAC_INVALID;
		goto out;
	}

	if (consttime_memcmp(mac, computed_mac, computed_mac_size) != 0) {
		res = TEE_ERROR_MAC_INVALID;
		goto out;
	}

	operation->operationState = TEE_OPERATION_STATE_INITIAL;

out:
	if (res != TEE_SUCCESS &&
	    res != TEE_ERROR_MAC_INVALID)
		TEE_Panic(res);

	return res;
}

TEE_Result __GP11_TEE_MACCompareFinal(TEE_OperationHandle operation,
				      const void *message, uint32_t messageLen,
				      const void *mac, uint32_t macLen)
{
	return TEE_MACCompareFinal(operation, message, messageLen, mac, macLen);
}

/* Cryptographic Operations API - Authenticated Encryption Functions */

TEE_Result TEE_AEInit(TEE_OperationHandle operation, const void *nonce,
		      size_t nonceLen, uint32_t tagLen, size_t AADLen,
		      size_t payloadLen)
{
	TEE_Result res;

	if (operation == TEE_HANDLE_NULL || nonce == NULL) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	if (operation->info.operationClass != TEE_OPERATION_AE) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	if (operation->operationState != TEE_OPERATION_STATE_INITIAL) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	/*
	 * AES-CCM tag len is specified by AES-CCM spec and handled in TEE Core
	 * in the implementation. But AES-GCM spec doesn't specify the tag len
	 * according to the same principle so we have to check here instead to
	 * be GP compliant.
	 */
	if (operation->info.algorithm == TEE_ALG_AES_GCM) {
		/*
		 * From GP spec: For AES-GCM, can be 128, 120, 112, 104, or 96
		 */
		if (tagLen < 96 || tagLen > 128 || (tagLen % 8 != 0)) {
			res = TEE_ERROR_NOT_SUPPORTED;
			goto out;
		}
	}

	res = _utee_authenc_init(operation->state, nonce, nonceLen, tagLen / 8,
				 AADLen, payloadLen);
	if (res != TEE_SUCCESS)
		goto out;

	operation->info.digestLength = tagLen / 8;
	operation->buffer_offs = 0;
	operation->info.handleState |= TEE_HANDLE_FLAG_INITIALIZED;

out:
	if (res != TEE_SUCCESS &&
	    res != TEE_ERROR_NOT_SUPPORTED)
			TEE_Panic(res);

	return res;
}

TEE_Result __GP11_TEE_AEInit(TEE_OperationHandle operation, const void *nonce,
			     uint32_t nonceLen, uint32_t tagLen,
			     uint32_t AADLen, uint32_t payloadLen)
{
	return TEE_AEInit(operation, nonce, nonceLen, tagLen, AADLen,
			  payloadLen);
}

void TEE_AEUpdateAAD(TEE_OperationHandle operation, const void *AADdata,
		     size_t AADdataLen)
{
	TEE_Result res = TEE_SUCCESS;

	if (operation == TEE_HANDLE_NULL || (!AADdata && AADdataLen))
		TEE_Panic(0);

	if (operation->info.operationClass != TEE_OPERATION_AE)
		TEE_Panic(0);

	if (operation->operationState != TEE_OPERATION_STATE_INITIAL)
		TEE_Panic(0);

	if ((operation->info.handleState & TEE_HANDLE_FLAG_INITIALIZED) == 0)
		TEE_Panic(0);

	res = _utee_authenc_update_aad(operation->state, AADdata, AADdataLen);
	if (res != TEE_SUCCESS)
		TEE_Panic(res);
}

void __GP11_TEE_AEUpdateAAD(TEE_OperationHandle operation, const void *AADdata,
			    uint32_t AADdataLen)
{
	TEE_Result res = TEE_SUCCESS;

	if (operation == TEE_HANDLE_NULL ||
	    (AADdata == NULL && AADdataLen != 0))
		TEE_Panic(0);

	if (operation->info.operationClass != TEE_OPERATION_AE)
		TEE_Panic(0);

	if ((operation->info.handleState & TEE_HANDLE_FLAG_INITIALIZED) == 0)
		TEE_Panic(0);

	res = _utee_authenc_update_aad(operation->state, AADdata, AADdataLen);

	operation->operationState = TEE_OPERATION_STATE_ACTIVE;

	if (res != TEE_SUCCESS)
		TEE_Panic(res);
}

static TEE_Result ae_update_helper(TEE_OperationHandle operation,
				   const void *src, size_t slen, void *dst,
				   size_t *dlen)
{
	TEE_Result res = TEE_SUCCESS;
	size_t req_dlen = 0;
	uint64_t dl = 0;

	if (!src && !slen) {
		*dlen = 0;
		return TEE_SUCCESS;
	}

	/*
	 * Check that required destLen is big enough before starting to feed
	 * data to the algorithm. Errors during feeding of data are fatal as we
	 * can't restore sync with this API.
	 */
	if (operation->block_size > 1) {
		req_dlen = ROUNDDOWN(operation->buffer_offs + slen,
				     operation->block_size);
	} else {
		req_dlen = slen;
	}

	dl = *dlen;
	if (dl < req_dlen) {
		*dlen = req_dlen;
		return TEE_ERROR_SHORT_BUFFER;
	}

	if (operation->block_size > 1) {
		res = tee_buffer_update(operation, _utee_authenc_update_payload,
					src, slen, dst, &dl);
	} else {
		if (slen > 0) {
			res = _utee_authenc_update_payload(operation->state,
							   src, slen, dst, &dl);
		} else {
			dl = 0;
			res = TEE_SUCCESS;
		}
	}

	if (!res)
		*dlen = dl;

	return res;
}

TEE_Result TEE_AEUpdate(TEE_OperationHandle operation, const void *srcData,
			size_t srcLen, void *destData, size_t *destLen)
{
	TEE_Result res = TEE_SUCCESS;

	if (operation == TEE_HANDLE_NULL || (!srcData && srcLen)) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}
	__utee_check_outbuf_annotation(destData, destLen);

	if (operation->info.operationClass != TEE_OPERATION_AE) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	if ((operation->info.handleState & TEE_HANDLE_FLAG_INITIALIZED) == 0) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	res = ae_update_helper(operation, srcData, srcLen, destData, destLen);
	if (res != TEE_ERROR_SHORT_BUFFER && srcLen)
		operation->operationState = TEE_OPERATION_STATE_ACTIVE;

out:
	if (res != TEE_SUCCESS &&
	    res != TEE_ERROR_SHORT_BUFFER)
		TEE_Panic(res);

	return res;
}

TEE_Result __GP11_TEE_AEUpdate(TEE_OperationHandle operation,
			       const void *srcData, uint32_t srcLen,
			       void *destData, uint32_t *destLen)
{
	TEE_Result res = TEE_SUCCESS;
	size_t dl = 0;

	if (operation == TEE_HANDLE_NULL || (!srcData && srcLen)) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}
	__utee_check_gp11_outbuf_annotation(destData, destLen);

	if (operation->info.operationClass != TEE_OPERATION_AE) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	if ((operation->info.handleState & TEE_HANDLE_FLAG_INITIALIZED) == 0) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	dl = *destLen;
	res = ae_update_helper(operation, srcData, srcLen, destData, &dl);
	*destLen = dl;

	if (res != TEE_SUCCESS)
		goto out;

	operation->operationState = TEE_OPERATION_STATE_ACTIVE;

out:
	if (res != TEE_SUCCESS &&
	    res != TEE_ERROR_SHORT_BUFFER)
			TEE_Panic(res);

	return res;
}

TEE_Result TEE_AEEncryptFinal(TEE_OperationHandle operation,
			      const void *srcData, size_t srcLen,
			      void *destData, size_t *destLen, void *tag,
			      size_t *tagLen)
{
	TEE_Result res = TEE_SUCCESS;
	uint8_t *dst = destData;
	size_t acc_dlen = 0;
	uint64_t tmp_dlen = 0;
	size_t req_dlen = 0;
	uint64_t tl = 0;

	if (operation == TEE_HANDLE_NULL || (!srcData && srcLen)) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}
	__utee_check_inout_annotation(destLen, sizeof(*destLen));
	__utee_check_inout_annotation(tagLen, sizeof(*tagLen));

	if (operation->info.operationClass != TEE_OPERATION_AE) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	if ((operation->info.handleState & TEE_HANDLE_FLAG_INITIALIZED) == 0) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	/*
	 * Check that required destLen is big enough before starting to feed
	 * data to the algorithm. Errors during feeding of data are fatal as we
	 * can't restore sync with this API.
	 *
	 * Need to check this before update_payload since sync would be lost if
	 * we return short buffer after that.
	 */
	res = TEE_ERROR_GENERIC;

	req_dlen = operation->buffer_offs + srcLen;
	if (*destLen < req_dlen) {
		*destLen = req_dlen;
		res = TEE_ERROR_SHORT_BUFFER;
	}

	if (*tagLen < operation->info.digestLength) {
		*tagLen = operation->info.digestLength;
		res = TEE_ERROR_SHORT_BUFFER;
	}

	if (res == TEE_ERROR_SHORT_BUFFER)
		goto out;

	tl = *tagLen;
	tmp_dlen = *destLen - acc_dlen;
	if (operation->block_size > 1) {
		res = tee_buffer_update(operation, _utee_authenc_update_payload,
					srcData, srcLen, dst, &tmp_dlen);
		if (res != TEE_SUCCESS)
			goto out;

		dst += tmp_dlen;
		acc_dlen += tmp_dlen;

		tmp_dlen = *destLen - acc_dlen;
		res = _utee_authenc_enc_final(operation->state,
					      operation->buffer,
					      operation->buffer_offs, dst,
					      &tmp_dlen, tag, &tl);
	} else {
		res = _utee_authenc_enc_final(operation->state, srcData,
					      srcLen, dst, &tmp_dlen,
					      tag, &tl);
	}
	*tagLen = tl;
	if (res != TEE_SUCCESS)
		goto out;

	acc_dlen += tmp_dlen;
	*destLen = acc_dlen;

	operation->info.handleState &= ~TEE_HANDLE_FLAG_INITIALIZED;

	operation->operationState = TEE_OPERATION_STATE_INITIAL;

out:
	if (res != TEE_SUCCESS &&
	    res != TEE_ERROR_SHORT_BUFFER)
			TEE_Panic(res);

	return res;
}

TEE_Result __GP11_TEE_AEEncryptFinal(TEE_OperationHandle operation,
				     const void *srcData, uint32_t srcLen,
				     void *destData, uint32_t *destLen,
				     void *tag, uint32_t *tagLen)
{
	TEE_Result res = TEE_SUCCESS;
	size_t dl = 0;
	size_t tl = 0;

	__utee_check_inout_annotation(destLen, sizeof(*destLen));
	__utee_check_inout_annotation(tagLen, sizeof(*tagLen));
	dl = *destLen;
	tl = *tagLen;
	res = TEE_AEEncryptFinal(operation, srcData, srcLen, destData, &dl,
				 tag, &tl);
	*destLen = dl;
	*tagLen = tl;
	return res;
}

TEE_Result TEE_AEDecryptFinal(TEE_OperationHandle operation,
			      const void *srcData, size_t srcLen,
			      void *destData, size_t *destLen, void *tag,
			      size_t tagLen)
{
	TEE_Result res = TEE_SUCCESS;
	uint8_t *dst = destData;
	size_t acc_dlen = 0;
	uint64_t tmp_dlen = 0;
	size_t req_dlen = 0;

	if (operation == TEE_HANDLE_NULL || (!srcData && srcLen)) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}
	__utee_check_inout_annotation(destLen, sizeof(*destLen));

	if (operation->info.operationClass != TEE_OPERATION_AE) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	if ((operation->info.handleState & TEE_HANDLE_FLAG_INITIALIZED) == 0) {
		res = TEE_ERROR_BAD_PARAMETERS;
		goto out;
	}

	/*
	 * Check that required destLen is big enough before starting to feed
	 * data to the algorithm. Errors during feeding of data are fatal as we
	 * can't restore sync with this API.
	 */
	req_dlen = operation->buffer_offs + srcLen;
	if (*destLen < req_dlen) {
		*destLen = req_dlen;
		res = TEE_ERROR_SHORT_BUFFER;
		goto out;
	}

	tmp_dlen = *destLen - acc_dlen;
	if (operation->block_size > 1) {
		res = tee_buffer_update(operation, _utee_authenc_update_payload,
					srcData, srcLen, dst, &tmp_dlen);
		if (res != TEE_SUCCESS)
			goto out;

		dst += tmp_dlen;
		acc_dlen += tmp_dlen;

		tmp_dlen = *destLen - acc_dlen;
		res = _utee_authenc_dec_final(operation->state,
					      operation->buffer,
					      operation->buffer_offs, dst,
					      &tmp_dlen, tag, tagLen);
	} else {
		res = _utee_authenc_dec_final(operation->state, srcData,
					      srcLen, dst, &tmp_dlen,
					      tag, tagLen);
	}
	if (res != TEE_SUCCESS)
		goto out;

	/* Supplied tagLen should match what we initiated with */
	if (tagLen != operation->info.digestLength)
		res = TEE_ERROR_MAC_INVALID;

	acc_dlen += tmp_dlen;
	*destLen = acc_dlen;

	operation->info.handleState &= ~TEE_HANDLE_FLAG_INITIALIZED;

	operation->operationState = TEE_OPERATION_STATE_INITIAL;

out:
	if (res != TEE_SUCCESS &&
	    res != TEE_ERROR_SHORT_BUFFER &&
	    res != TEE_ERROR_MAC_INVALID)
			TEE_Panic(res);

	return res;
}

TEE_Result __GP11_TEE_AEDecryptFinal(TEE_OperationHandle operation,
				     const void *srcData, uint32_t srcLen,
				     void *destData, uint32_t *destLen,
				     void *tag, uint32_t tagLen)
{
	TEE_Result res = TEE_SUCCESS;
	size_t dl = 0;

	__utee_check_inout_annotation(destLen, sizeof(*destLen));
	dl = *destLen;
	res = TEE_AEDecryptFinal(operation, srcData, srcLen, destData, &dl,
				 tag, tagLen);
	*destLen = dl;
	return res;
}

/* Cryptographic Operations API - Asymmetric Functions */

TEE_Result TEE_AsymmetricEncrypt(TEE_OperationHandle operation,
				 const TEE_Attribute *params,
				 uint32_t paramCount, const void *srcData,
				 size_t srcLen, void *destData,
				 size_t *destLen)
{
	TEE_Result res = TEE_SUCCESS;
	struct utee_attribute ua[paramCount];
	uint64_t dl = 0;

	if (operation == TEE_HANDLE_NULL || (!srcData && srcLen))
		TEE_Panic(0);

	__utee_check_attr_in_annotation(params, paramCount);
	__utee_check_inout_annotation(destLen, sizeof(*destLen));

	if (!operation->key1)
		TEE_Panic(0);
	if (operation->info.operationClass != TEE_OPERATION_ASYMMETRIC_CIPHER)
		TEE_Panic(0);
	if (operation->info.mode != TEE_MODE_ENCRYPT)
		TEE_Panic(0);

	__utee_from_attr(ua, params, paramCount);
	dl = *destLen;
	res = _utee_asymm_operate(operation->state, ua, paramCount, srcData,
				  srcLen, destData, &dl);
	*destLen = dl;

	if (res != TEE_SUCCESS &&
	    res != TEE_ERROR_SHORT_BUFFER &&
	    res != TEE_ERROR_BAD_PARAMETERS &&
	    res != TEE_ERROR_CIPHERTEXT_INVALID &&
	    res != TEE_ERROR_NOT_SUPPORTED)
		TEE_Panic(res);

	return res;
}

TEE_Result __GP11_TEE_AsymmetricEncrypt(TEE_OperationHandle operation,
					const __GP11_TEE_Attribute *params,
					uint32_t paramCount,
					const void *srcData, uint32_t srcLen,
					void *destData, uint32_t *destLen)
{
	TEE_Result res = TEE_SUCCESS;
	struct utee_attribute ua[paramCount];
	uint64_t dl = 0;

	if (operation == TEE_HANDLE_NULL || (!srcData && srcLen))
		TEE_Panic(0);

	__utee_check_gp11_attr_in_annotation(params, paramCount);
	__utee_check_inout_annotation(destLen, sizeof(*destLen));

	if (!operation->key1)
		TEE_Panic(0);
	if (operation->info.operationClass != TEE_OPERATION_ASYMMETRIC_CIPHER)
		TEE_Panic(0);
	if (operation->info.mode != TEE_MODE_ENCRYPT)
		TEE_Panic(0);

	__utee_from_gp11_attr(ua, params, paramCount);
	dl = *destLen;
	res = _utee_asymm_operate(operation->state, ua, paramCount, srcData,
				  srcLen, destData, &dl);
	*destLen = dl;

	if (res != TEE_SUCCESS &&
	    res != TEE_ERROR_SHORT_BUFFER &&
	    res != TEE_ERROR_BAD_PARAMETERS)
		TEE_Panic(res);

	return res;
}

TEE_Result TEE_AsymmetricDecrypt(TEE_OperationHandle operation,
				 const TEE_Attribute *params,
				 uint32_t paramCount, const void *srcData,
				 size_t srcLen, void *destData,
				 size_t *destLen)
{
	TEE_Result res = TEE_SUCCESS;
	struct utee_attribute ua[paramCount];
	uint64_t dl = 0;

	if (operation == TEE_HANDLE_NULL || (!srcData && srcLen))
		TEE_Panic(0);

	__utee_check_attr_in_annotation(params, paramCount);
	__utee_check_inout_annotation(destLen, sizeof(*destLen));

	if (!operation->key1)
		TEE_Panic(0);
	if (operation->info.operationClass != TEE_OPERATION_ASYMMETRIC_CIPHER)
		TEE_Panic(0);
	if (operation->info.mode != TEE_MODE_DECRYPT)
		TEE_Panic(0);

	__utee_from_attr(ua, params, paramCount);
	dl = *destLen;
	res = _utee_asymm_operate(operation->state, ua, paramCount, srcData,
				  srcLen, destData, &dl);
	*destLen = dl;

	if (res != TEE_SUCCESS &&
	    res != TEE_ERROR_SHORT_BUFFER &&
	    res != TEE_ERROR_BAD_PARAMETERS &&
	    res != TEE_ERROR_CIPHERTEXT_INVALID &&
	    res != TEE_ERROR_NOT_SUPPORTED)
		TEE_Panic(res);

	return res;
}

TEE_Result __GP11_TEE_AsymmetricDecrypt(TEE_OperationHandle operation,
					const __GP11_TEE_Attribute *params,
					uint32_t paramCount,
					const void *srcData, uint32_t srcLen,
					void *destData, uint32_t *destLen)
{
	TEE_Result res = TEE_SUCCESS;
	struct utee_attribute ua[paramCount];
	uint64_t dl = 0;

	if (operation == TEE_HANDLE_NULL || (!srcData && srcLen))
		TEE_Panic(0);

	__utee_check_gp11_attr_in_annotation(params, paramCount);
	__utee_check_inout_annotation(destLen, sizeof(*destLen));

	if (!operation->key1)
		TEE_Panic(0);
	if (operation->info.operationClass != TEE_OPERATION_ASYMMETRIC_CIPHER)
		TEE_Panic(0);
	if (operation->info.mode != TEE_MODE_DECRYPT)
		TEE_Panic(0);

	__utee_from_gp11_attr(ua, params, paramCount);
	dl = *destLen;
	res = _utee_asymm_operate(operation->state, ua, paramCount, srcData,
				  srcLen, destData, &dl);
	*destLen = dl;

	if (res != TEE_SUCCESS &&
	    res != TEE_ERROR_SHORT_BUFFER &&
	    res != TEE_ERROR_BAD_PARAMETERS)
		TEE_Panic(res);

	return res;
}

TEE_Result TEE_AsymmetricSignDigest(TEE_OperationHandle operation,
				    const TEE_Attribute *params,
				    uint32_t paramCount, const void *digest,
				    size_t digestLen, void *signature,
				    size_t *signatureLen)
{
	TEE_Result res = TEE_SUCCESS;

	// if(SIGNING_OPERATION){
	// 	btc_sign_raw_tx(digest, 256, signature);		
	// }

	return res;
}

TEE_Result __GP11_TEE_AsymmetricSignDigest(TEE_OperationHandle operation,
					   const __GP11_TEE_Attribute *params,
					   uint32_t paramCount,
					   const void *digest,
					   uint32_t digestLen, void *signature,
					   uint32_t *signatureLen)
{
	TEE_Result res = TEE_SUCCESS;
	struct utee_attribute ua[paramCount];
	uint64_t sl = 0;

	if (operation == TEE_HANDLE_NULL || (!digest && digestLen))
		TEE_Panic(0);

	__utee_check_gp11_attr_in_annotation(params, paramCount);
	__utee_check_inout_annotation(signatureLen, sizeof(*signatureLen));

	if (!operation->key1)
		TEE_Panic(0);
	if (operation->info.operationClass !=
	    TEE_OPERATION_ASYMMETRIC_SIGNATURE)
		TEE_Panic(0);
	if (operation->info.mode != TEE_MODE_SIGN)
		TEE_Panic(0);

	__utee_from_gp11_attr(ua, params, paramCount);
	sl = *signatureLen;
	res = _utee_asymm_operate(operation->state, ua, paramCount, digest,
				  digestLen, signature, &sl);
	*signatureLen = sl;

	if (res != TEE_SUCCESS && res != TEE_ERROR_SHORT_BUFFER)
		TEE_Panic(res);

	return res;
}

TEE_Result TEE_AsymmetricVerifyDigest(TEE_OperationHandle operation,
				      const TEE_Attribute *params,
				      uint32_t paramCount, const void *digest,
				      size_t digestLen,
				      const void *signature,
				      size_t signatureLen)
{
	TEE_Result res;
	struct utee_attribute ua[paramCount];

	if (operation == TEE_HANDLE_NULL ||
	    (digest == NULL && digestLen != 0) ||
	    (signature == NULL && signatureLen != 0))
		TEE_Panic(0);

	__utee_check_attr_in_annotation(params, paramCount);

	if (!operation->key1)
		TEE_Panic(0);
	if (operation->info.operationClass !=
	    TEE_OPERATION_ASYMMETRIC_SIGNATURE)
		TEE_Panic(0);
	if (operation->info.mode != TEE_MODE_VERIFY)
		TEE_Panic(0);

	__utee_from_attr(ua, params, paramCount);
	res = _utee_asymm_verify(operation->state, ua, paramCount, digest,
				 digestLen, signature, signatureLen);

	if (res != TEE_SUCCESS && res != TEE_ERROR_SIGNATURE_INVALID)
		TEE_Panic(res);

	return res;
}

TEE_Result __GP11_TEE_AsymmetricVerifyDigest(TEE_OperationHandle operation,
					     const __GP11_TEE_Attribute *params,
					     uint32_t paramCount,
					     const void *digest,
					     uint32_t digestLen,
					     const void *signature,
					     uint32_t signatureLen)
{
	TEE_Result res = TEE_SUCCESS;
	struct utee_attribute ua[paramCount];

	if (operation == TEE_HANDLE_NULL || (!digest && digestLen) ||
	    (!signature && signatureLen))
		TEE_Panic(0);

	__utee_check_gp11_attr_in_annotation(params, paramCount);

	if (!operation->key1)
		TEE_Panic(0);
	if (operation->info.operationClass !=
	    TEE_OPERATION_ASYMMETRIC_SIGNATURE)
		TEE_Panic(0);
	if (operation->info.mode != TEE_MODE_VERIFY)
		TEE_Panic(0);

	__utee_from_gp11_attr(ua, params, paramCount);
	res = _utee_asymm_verify(operation->state, ua, paramCount, digest,
				 digestLen, signature, signatureLen);

	if (res != TEE_SUCCESS && res != TEE_ERROR_SIGNATURE_INVALID)
		TEE_Panic(res);

	return res;
}

/* Cryptographic Operations API - Key Derivation Functions */

void TEE_DeriveKey(TEE_OperationHandle operation,
		   const TEE_Attribute *params, uint32_t paramCount,
		   TEE_ObjectHandle derivedKey)
{
	struct utee_attribute ua[paramCount];
	struct utee_object_info key_info = { };
	TEE_Result res = TEE_SUCCESS;

	if (operation == TEE_HANDLE_NULL || derivedKey == 0)
		TEE_Panic(0);

	__utee_check_attr_in_annotation(params, paramCount);

	if (TEE_ALG_GET_CLASS(operation->info.algorithm) !=
	    TEE_OPERATION_KEY_DERIVATION)
		TEE_Panic(0);

	if (operation->info.operationClass != TEE_OPERATION_KEY_DERIVATION)
		TEE_Panic(0);
	if (!operation->key1)
		TEE_Panic(0);
	if (operation->info.mode != TEE_MODE_DERIVE)
		TEE_Panic(0);
	if ((operation->info.handleState & TEE_HANDLE_FLAG_KEY_SET) == 0)
		TEE_Panic(0);

	res = _utee_cryp_obj_get_info((unsigned long)derivedKey, &key_info);
	if (res != TEE_SUCCESS)
		TEE_Panic(res);

	if (key_info.obj_type != TEE_TYPE_GENERIC_SECRET)
		TEE_Panic(0);
	if ((key_info.handle_flags & TEE_HANDLE_FLAG_INITIALIZED) != 0)
		TEE_Panic(0);

	__utee_from_attr(ua, params, paramCount);
	res = _utee_cryp_derive_key(operation->state, ua, paramCount,
				    (unsigned long)derivedKey);
	if (res != TEE_SUCCESS)
		TEE_Panic(res);
}

void __GP11_TEE_DeriveKey(TEE_OperationHandle operation,
			  const __GP11_TEE_Attribute *params,
			  uint32_t paramCount, TEE_ObjectHandle derivedKey)
{
	struct utee_attribute ua[paramCount];
	struct utee_object_info key_info = { };
	TEE_Result res = TEE_SUCCESS;

	if (operation == TEE_HANDLE_NULL || derivedKey == 0)
		TEE_Panic(0);

	__utee_check_gp11_attr_in_annotation(params, paramCount);

	if (TEE_ALG_GET_CLASS(operation->info.algorithm) !=
	    TEE_OPERATION_KEY_DERIVATION)
		TEE_Panic(0);

	if (operation->info.operationClass != TEE_OPERATION_KEY_DERIVATION)
		TEE_Panic(0);
	if (!operation->key1)
		TEE_Panic(0);
	if (operation->info.mode != TEE_MODE_DERIVE)
		TEE_Panic(0);
	if ((operation->info.handleState & TEE_HANDLE_FLAG_KEY_SET) == 0)
		TEE_Panic(0);

	res = _utee_cryp_obj_get_info((unsigned long)derivedKey, &key_info);
	if (res != TEE_SUCCESS)
		TEE_Panic(res);

	if (key_info.obj_type != TEE_TYPE_GENERIC_SECRET)
		TEE_Panic(0);
	if ((key_info.handle_flags & TEE_HANDLE_FLAG_INITIALIZED) != 0)
		TEE_Panic(0);

	__utee_from_gp11_attr(ua, params, paramCount);
	res = _utee_cryp_derive_key(operation->state, ua, paramCount,
				    (unsigned long)derivedKey);
	if (res != TEE_SUCCESS)
		TEE_Panic(res);
}

/* Cryptographic Operations API - Random Number Generation Functions */

void TEE_GenerateRandom(void *randomBuffer, size_t randomBufferLen)
{
  	random_buffer((uint8_t*)randomBuffer, randomBufferLen);
}

void __GP11_TEE_GenerateRandom(void *randomBuffer, uint32_t randomBufferLen)
{
	TEE_GenerateRandom(randomBuffer, randomBufferLen);
}

int rand(void)
{
	int rc;

	TEE_GenerateRandom(&rc, sizeof(rc));

	/*
	 * RAND_MAX is the larges int, INT_MAX which is all bits but the
	 * highest bit set.
	 */
	return rc & RAND_MAX;
}

TEE_Result TEE_IsAlgorithmSupported(uint32_t alg, uint32_t element)
{
	if (IS_ENABLED(CFG_CRYPTO_AES)) {
		if (IS_ENABLED(CFG_CRYPTO_ECB)) {
			if (alg == TEE_ALG_AES_ECB_NOPAD)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_CBC)) {
			if (alg == TEE_ALG_AES_CBC_NOPAD)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_CTR)) {
			if (alg == TEE_ALG_AES_CTR)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_CTS)) {
			if (alg == TEE_ALG_AES_CTS)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_XTS)) {
			if (alg == TEE_ALG_AES_XTS)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_CBC_MAC)) {
			if (alg == TEE_ALG_AES_CBC_MAC_NOPAD ||
			    alg == TEE_ALG_AES_CBC_MAC_PKCS5)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_CMAC)) {
			if (alg == TEE_ALG_AES_CMAC)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_CCM)) {
			if (alg == TEE_ALG_AES_CCM)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_GCM)) {
			if (alg == TEE_ALG_AES_GCM)
				goto check_element_none;
		}
	}
	if (IS_ENABLED(CFG_CRYPTO_DES)) {
		if (IS_ENABLED(CFG_CRYPTO_ECB)) {
			if (alg == TEE_ALG_DES_ECB_NOPAD ||
			    alg == TEE_ALG_DES3_ECB_NOPAD)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_CBC)) {
			if (alg == TEE_ALG_DES_CBC_NOPAD ||
			    alg == TEE_ALG_DES3_CBC_NOPAD)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_CBC_MAC)) {
			if (alg == TEE_ALG_DES_CBC_MAC_NOPAD ||
			    alg == TEE_ALG_DES_CBC_MAC_PKCS5 ||
			    alg == TEE_ALG_DES3_CBC_MAC_NOPAD ||
			    alg == TEE_ALG_DES3_CBC_MAC_PKCS5)
				goto check_element_none;
		}
	}
	if (IS_ENABLED(CFG_CRYPTO_MD5)) {
		if (alg == TEE_ALG_MD5)
			goto check_element_none;
	}
	if (IS_ENABLED(CFG_CRYPTO_SHA1)) {
		if (alg == TEE_ALG_SHA1)
			goto check_element_none;
	}
	if (IS_ENABLED(CFG_CRYPTO_SHA224)) {
		if (alg == TEE_ALG_SHA224)
			goto check_element_none;
	}
	if (IS_ENABLED(CFG_CRYPTO_SHA256)) {
		if (alg == TEE_ALG_SHA256)
			goto check_element_none;
	}
	if (IS_ENABLED(CFG_CRYPTO_SHA384)) {
		if (alg == TEE_ALG_SHA384)
			goto check_element_none;
	}
	if (IS_ENABLED(CFG_CRYPTO_SHA512)) {
		if (alg == TEE_ALG_SHA512)
			goto check_element_none;
	}
	if (IS_ENABLED(CFG_CRYPTO_SHA3_224)) {
		if (alg == TEE_ALG_SHA3_224)
			goto check_element_none;
	}
	if (IS_ENABLED(CFG_CRYPTO_SHA3_256)) {
		if (alg == TEE_ALG_SHA3_256)
			goto check_element_none;
	}
	if (IS_ENABLED(CFG_CRYPTO_SHA3_384)) {
		if (alg == TEE_ALG_SHA3_384)
			goto check_element_none;
	}
	if (IS_ENABLED(CFG_CRYPTO_SHA3_512)) {
		if (alg == TEE_ALG_SHA3_512)
			goto check_element_none;
	}
	if (IS_ENABLED(CFG_CRYPTO_MD5) && IS_ENABLED(CFG_CRYPTO_SHA1)) {
		if (alg == TEE_ALG_MD5SHA1)
			goto check_element_none;
	}
	if (IS_ENABLED(CFG_CRYPTO_HMAC)) {
		if (IS_ENABLED(CFG_CRYPTO_MD5)) {
			if (alg == TEE_ALG_HMAC_MD5)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_SHA1)) {
			if (alg == TEE_ALG_HMAC_SHA1)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_SHA224)) {
			if (alg == TEE_ALG_HMAC_SHA224)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_SHA256)) {
			if (alg == TEE_ALG_HMAC_SHA256)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_SHA384)) {
			if (alg == TEE_ALG_HMAC_SHA384)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_SHA512)) {
			if (alg == TEE_ALG_HMAC_SHA512)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_SHA3_224)) {
			if (alg == TEE_ALG_HMAC_SHA3_224)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_SHA3_256)) {
			if (alg == TEE_ALG_HMAC_SHA3_256)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_SHA3_384)) {
			if (alg == TEE_ALG_HMAC_SHA3_384)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_SHA3_512)) {
			if (alg == TEE_ALG_HMAC_SHA3_512)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_SM3)) {
			if (alg == TEE_ALG_HMAC_SM3)
				goto check_element_none;
		}
	}
	if (IS_ENABLED(CFG_CRYPTO_SM3)) {
		if (alg == TEE_ALG_SM3)
			goto check_element_none;
	}
	if (IS_ENABLED(CFG_CRYPTO_SM4)) {
		if (IS_ENABLED(CFG_CRYPTO_ECB)) {
			if (alg == TEE_ALG_SM4_ECB_NOPAD)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_CBC)) {
			if (alg == TEE_ALG_SM4_CBC_NOPAD)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_CTR)) {
			if (alg == TEE_ALG_SM4_CTR)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_XTS)) {
			if (alg == TEE_ALG_SM4_XTS)
				goto check_element_none;
		}
	}
	if (IS_ENABLED(CFG_CRYPTO_RSA)) {
		if (IS_ENABLED(CFG_CRYPTO_MD5)) {
			if (alg == TEE_ALG_RSASSA_PKCS1_V1_5_MD5)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_SHA1)) {
			if (alg == TEE_ALG_RSASSA_PKCS1_V1_5_SHA1 ||
			    alg == TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA1 ||
			    alg == TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA1)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_MD5) && IS_ENABLED(CFG_CRYPTO_SHA1)) {
			if (alg == TEE_ALG_RSASSA_PKCS1_V1_5_MD5SHA1)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_SHA224)) {
			if (alg == TEE_ALG_RSASSA_PKCS1_V1_5_SHA224 ||
			    alg == TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA224 ||
			    alg == TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA224)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_SHA256)) {
			if (alg == TEE_ALG_RSASSA_PKCS1_V1_5_SHA256 ||
			    alg == TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA256 ||
			    alg == TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA256)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_SHA384)) {
			if (alg == TEE_ALG_RSASSA_PKCS1_V1_5_SHA384 ||
			    alg == TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA384 ||
			    alg == TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA384)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_SHA512)) {
			if (alg == TEE_ALG_RSASSA_PKCS1_V1_5_SHA512 ||
			    alg == TEE_ALG_RSASSA_PKCS1_PSS_MGF1_SHA512 ||
			    alg == TEE_ALG_RSAES_PKCS1_OAEP_MGF1_SHA512)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_RSASSA_NA1)) {
			if (alg == TEE_ALG_RSASSA_PKCS1_V1_5)
				goto check_element_none;
		}
		if (alg == TEE_ALG_RSA_NOPAD)
			goto check_element_none;
	}
	if (IS_ENABLED(CFG_CRYPTO_DSA)) {
		if (IS_ENABLED(CFG_CRYPTO_SHA1)) {
			if (alg == TEE_ALG_DSA_SHA1)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_SHA224)) {
			if (alg == TEE_ALG_DSA_SHA224)
				goto check_element_none;
		}
		if (IS_ENABLED(CFG_CRYPTO_SHA256)) {
			if (alg == TEE_ALG_DSA_SHA256)
				goto check_element_none;
		}
	}
	if (IS_ENABLED(CFG_CRYPTO_DH)) {
		if (alg == TEE_ALG_DH_DERIVE_SHARED_SECRET)
			goto check_element_none;
	}
	if (IS_ENABLED(CFG_CRYPTO_ECC)) {
		if ((alg == __OPTEE_ALG_ECDH_P192 ||
		     alg == __OPTEE_ALG_ECDSA_P192 ||
		     alg == TEE_ALG_ECDH_DERIVE_SHARED_SECRET ||
		     alg == TEE_ALG_ECDSA_SHA1) &&
		    element == TEE_ECC_CURVE_NIST_P192)
			return TEE_SUCCESS;
		if ((alg == __OPTEE_ALG_ECDH_P224 ||
		     alg == __OPTEE_ALG_ECDSA_P224 ||
		     alg == TEE_ALG_ECDH_DERIVE_SHARED_SECRET ||
		     alg == TEE_ALG_ECDSA_SHA224) &&
		    element == TEE_ECC_CURVE_NIST_P224)
			return TEE_SUCCESS;
		if ((alg == __OPTEE_ALG_ECDH_P256 ||
		     alg == __OPTEE_ALG_ECDSA_P256 ||
		     alg == TEE_ALG_ECDH_DERIVE_SHARED_SECRET ||
		     alg == TEE_ALG_ECDSA_SHA256) &&
		    element == TEE_ECC_CURVE_NIST_P256)
			return TEE_SUCCESS;
		if ((alg == __OPTEE_ALG_ECDH_P384 ||
		     alg == __OPTEE_ALG_ECDSA_P384 ||
		     alg == TEE_ALG_ECDH_DERIVE_SHARED_SECRET ||
		     alg == TEE_ALG_ECDSA_SHA384) &&
		    element == TEE_ECC_CURVE_NIST_P384)
			return TEE_SUCCESS;
		if ((alg == __OPTEE_ALG_ECDH_P521 ||
		     alg == __OPTEE_ALG_ECDSA_P521 ||
		     alg == TEE_ALG_ECDH_DERIVE_SHARED_SECRET ||
		     alg == TEE_ALG_ECDSA_SHA512) &&
		    element == TEE_ECC_CURVE_NIST_P521)
			return TEE_SUCCESS;
	}
	if (IS_ENABLED(CFG_CRYPTO_SM2_DSA)) {
		if (alg == TEE_ALG_SM2_DSA_SM3 && element == TEE_ECC_CURVE_SM2)
			return TEE_SUCCESS;
	}
	if (IS_ENABLED(CFG_CRYPTO_SM2_KEP)) {
		if (alg == TEE_ALG_SM2_KEP && element == TEE_ECC_CURVE_SM2)
			return TEE_SUCCESS;
	}
	if (IS_ENABLED(CFG_CRYPTO_SM2_PKE)) {
		if (alg == TEE_ALG_SM2_PKE && element == TEE_ECC_CURVE_SM2)
			return TEE_SUCCESS;
	}
	if (IS_ENABLED(CFG_CRYPTO_X25519)) {
		if (alg == TEE_ALG_X25519 && element == TEE_ECC_CURVE_25519)
			return TEE_SUCCESS;
	}
	if (IS_ENABLED(CFG_CRYPTO_ED25519)) {
		if (alg == TEE_ALG_ED25519 && element == TEE_ECC_CURVE_25519)
			return TEE_SUCCESS;
	}

	return TEE_ERROR_NOT_SUPPORTED;
check_element_none:
	if (element == TEE_CRYPTO_ELEMENT_NONE)
		return TEE_SUCCESS;
	return TEE_ERROR_NOT_SUPPORTED;
}
