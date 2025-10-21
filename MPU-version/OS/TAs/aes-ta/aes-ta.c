#include <string.h>
#include <stdlib.h>

// Include the TEE API header files
#include "tee_client_api.h"
#include "tee_core_api.h"

#include "include/aes-ta.h"

#define AES_BLOCK_SIZE	16

struct  
{
	uint32_t algo;			/* AES flavour */
	uint32_t mode;			/* Encode or decode */
	uint32_t key_size;		/* AES key size in byte */
	char     iv[AES_BLOCK_SIZE];
	TEE_OperationHandle op;	/* AES ciphering operation */
	TEE_ObjectHandle key;	/* transient object to load the key */
}aes;

int ta_test_generateKey(TEE_Param params[4])
{
    DMSG("Generate key for AES");
    int ret = -1;

    TEE_GenerateRandom(aes.iv, sizeof(aes.iv));
    
    aes.key_size = 256;

    ret = TEE_AllocateTransientObject(TEE_STORAGE_PRIVATE, aes.key_size, &aes.key);
    if(ret != TEE_SUCCESS){
        return -1;
    }

    ret = TEE_GenerateKey(aes.key, aes.key_size, NULL, 0);
    if(ret != TEE_SUCCESS){
        return -1;
    }

    return ret;
}


void ta_test_destroyKey(void)
{
    DMSG("Destroy key for AES");
    TEE_CloseObject(aes.key);
}

int ta_test_aesEncrypt(TEE_Param params[4])
{
    DMSG("AES encryption of the given buffer");
    int ret = -1;

    aes.key_size = 256;
    aes.algo = TEE_ALG_AES_CTR;
    aes.mode = TEE_MODE_ENCRYPT;

    ret = TEE_AllocateOperation(&aes.op, aes.algo, aes.mode, aes.key_size);
    if(ret != 0){
        return -1;
    }

    ret = TEE_SetOperationKey(aes.op, aes.key);
    if(ret != 0){
        return -1;
    }

    TEE_CipherInit(aes.op, aes.iv, sizeof(aes.iv));
    //TEE_CipherInit(aes.op, NULL, 0);

    if (AES_BLOCK_SIZE != params[0].memref.size && AES_BLOCK_SIZE != params[0].memref.size){
    	return -1;
    }

    uint8_t data[AES_BLOCK_SIZE];
    size_t size = params[1].memref.size;
    memcpy(data, params[0].memref.buffer, AES_BLOCK_SIZE);

    ret = TEE_CipherDoFinal(aes.op, data, params[0].memref.size, data, &size);
    params[1].memref.size = size;
    memcpy(params[1].memref.buffer, data, AES_BLOCK_SIZE);

    if(ret != 0){
        return -1;
    }

    TEE_FreeOperation(aes.op);

    return 0;
}

int ta_test_aesDecrypt(TEE_Param params[4])
{
    DMSG("AES decryption of the given buffer");
    int ret = -1;

    aes.key_size = 256;
    aes.algo = TEE_ALG_AES_CTR;
    aes.mode = TEE_MODE_DECRYPT;

    ret = TEE_AllocateOperation(&aes.op, aes.algo, aes.mode, aes.key_size);
    if(ret != 0){
        return -1;
    }

    ret = TEE_SetOperationKey(aes.op, aes.key);
    if(ret != 0){
        return -1;
    }

    TEE_CipherInit(aes.op, aes.iv, sizeof(aes.iv));
    //TEE_CipherInit(aes.op, NULL, 0);

    uint8_t data[AES_BLOCK_SIZE];
	size_t size = params[2].memref.size;
	memcpy(data, params[1].memref.buffer, AES_BLOCK_SIZE);

	ret = TEE_CipherDoFinal(aes.op, data, params[1].memref.size, data, &size);
	params[2].memref.size = size;
	memcpy(params[2].memref.buffer, data, AES_BLOCK_SIZE);

    if(ret != 0){
        return -1;
    }

    TEE_FreeOperation(aes.op);

    return 0;
}

int ta_test_digest(TEE_Param params[4]) {
    DMSG("Digest the given buffer");
    int ret = -1;

    TEE_OperationHandle digest_op;
    uint32_t algo = TEE_ALG_SHA256;

    ret = TEE_AllocateOperation(&digest_op, algo, TEE_MODE_DIGEST, 256);
    if(ret != 0){
        return -1;
    }

    TEE_DigestDoFinal(digest_op, params[0].memref.buffer, params[0].memref.size, params[3].memref.buffer, &params[3].memref.size);
    if(ret != 0) {
        return -1;
    }

    TEE_FreeOperation(digest_op);


    return 0;
}


TEE_Result  TA_CreateEntryPoint(void)
{
    DMSG("Entry point is created");
    
    return TEE_SUCCESS;
}


void TA_DestroyEntryPoint(void)
{
    DMSG("Entry point is destroyed");
}


TEE_Result TA_OpenSessionEntryPoint(uint32_t paramTypes,
									TEE_Param params[4],
									void** sessionContext)
{
    
    DMSG("Session is opened");
    return TEE_SUCCESS;
}


void  TA_CloseSessionEntryPoint(void* sessionContext)
{
    DMSG("Session is closed");    
} 


TEE_Result TA_InvokeCommandEntryPoint(void* sessionContext,
                                            uint32_t commandID,
                                            uint32_t paramTypes,
                                            TEE_Param params[4])
{
    int ret = TEE_SUCCESS;
     
    switch (commandID)
    {
        case TA_COMMAND_GENERATE_KEY: ret = ta_test_generateKey(params);      break;
        case TA_COMMAND_DESTROY_KEY:        ta_test_destroyKey();             break;
        case TA_COMMAND_ENCRYPT:      ret = ta_test_aesEncrypt(params);       break;
        case TA_COMMAND_DECRYPT:      ret = ta_test_aesDecrypt(params);       break;
        case TA_COMMAND_DIGEST:       ret = ta_test_digest(params);           break;
        default: ERR_MSG("Command id not recognized"); ret = TEE_FAILED;      break;
    }

	return ret;
}
