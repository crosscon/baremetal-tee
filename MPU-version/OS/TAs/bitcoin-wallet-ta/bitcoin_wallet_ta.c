//#include <tee_client_api.h>
//#include <tee_internal_api_extensions.h>
#include <bitcoin_wallet_ta.h>
#include <string.h>
#include <bip39.h>
#include <bip32.h>
#include <inttypes.h>
#include <ta_ripemd160.h>

#include <stdio.h> 
#include <stdlib.h>
#include "tee_core_api.h"
#include "stm32l4xx_hal.h"

#define BIP39_PBKDF2_ROUNDS 2048

/*external functions*/
static TEE_Result check_masterkey(uint32_t param_types, TEE_Param params[4]);
static TEE_Result generate_new_masterkey(uint32_t param_types, TEE_Param params[4]);
static TEE_Result mnemonic_to_masterkey(uint32_t param_types, TEE_Param params[4]);
static TEE_Result erase_masterkey(uint32_t param_types, TEE_Param params[4]);
static TEE_Result sign_transaction(uint32_t param_types, TEE_Param params[4]);
static TEE_Result get_bitcoin_address (uint32_t param_types, TEE_Param params[4]);


/*internal functions*/
static void get_child_privatekey(uint32_t i, uint8_t* child_sk, uint8_t* child_chaincode);
static void get_child_publickey(uint32_t i, uint8_t* child_pk_x, uint8_t* child_pk_y);
static void print_uint8(uint8_t* array, uint32_t array_len);
static void from_mnemonic_to_masterkey (char* mnemonic);
static uint32_t sign_raw_tx(uint8_t *rawtx, size_t bytes, uint8_t *sig, uint32_t i);
static TEE_Result get_account_address(uint8_t *addr, uint32_t account_id);
static TEE_Result ecdsa_to_bitaddr(TEE_ObjectHandle obj, uint8_t *bcadd, uint8_t network);
static TEE_Result base58(uint8_t *instr, size_t size, uint8_t *outstr);
static void reverse_str(uint8_t *str, size_t len);


TEE_Result TA_CreateEntryPoint(void){
	//DMSG("has been called");
	return TEE_SUCCESS;
}

void TA_DestroyEntryPoint(void){
	//DMSG("has been called");
}

TEE_Result TA_OpenSessionEntryPoint(uint32_t param_types, TEE_Param /*__maybe_unused*/ params[4], void /*__maybe_unused*/ **sess_ctx){

	uint32_t exp_param_types = TEE_PARAM_TYPES(	TEE_PARAM_TYPE_NONE, 
												TEE_PARAM_TYPE_NONE, 
												TEE_PARAM_TYPE_NONE, 
												TEE_PARAM_TYPE_NONE);
	//DMSG("has been called");
	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;
	(void)&params;
	(void)&sess_ctx;
	//IMSG("Hello Bitcoin Wallet!\n");
	return TEE_SUCCESS;
}

void TA_CloseSessionEntryPoint(void /*__maybe_unused*/ *sess_ctx){
	(void)&sess_ctx;
	//IMSG("Goodbye!\n");
}

TEE_Result TA_InvokeCommandEntryPoint(void /*__maybe_unused*/ *sess_ctx, uint32_t cmd_id, uint32_t param_types, TEE_Param params[4]){

	(void)&sess_ctx;
	
	//IMSG("Choice from NW: %d\n",cmd_id);
	switch (cmd_id) {
		case TA_BITCOIN_WALLET_CMD_1:
			return check_masterkey(param_types, params);
		case TA_BITCOIN_WALLET_CMD_2:
			return generate_new_masterkey(param_types, params);
		case TA_BITCOIN_WALLET_CMD_3:
			return mnemonic_to_masterkey(param_types, params);
		case TA_BITCOIN_WALLET_CMD_4:
			return erase_masterkey(param_types, params);
		case TA_BITCOIN_WALLET_CMD_5:
			return sign_transaction(param_types, params);
		case TA_BITCOIN_WALLET_CMD_6:
			return get_bitcoin_address(param_types, params);
		default:
			return TEE_ERROR_BAD_PARAMETERS;
	}
}

static TEE_Result check_masterkey(uint32_t param_types, TEE_Param params[4]){
	uint32_t exp_param_types = TEE_PARAM_TYPES(	TEE_PARAM_TYPE_VALUE_INOUT, 
												TEE_PARAM_TYPE_VALUE_OUTPUT, 
												TEE_PARAM_TYPE_NONE, 
												TEE_PARAM_TYPE_NONE);
	
	TEE_Result res;
	TEE_ObjectHandle obj = TEE_HANDLE_NULL;
	uint32_t flags_read = TEE_DATA_FLAG_ACCESS_READ;

	uint32_t masterkey_ext_id = TA_OBJECT_MASTERKEY_EXT;

	//DMSG("has been called");

	// check parameter types
	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;
	// Check pin
	if(params[0].value.a!=1234){
		params[0].value.b = 2;
		return TEE_SUCCESS;
	}

	res = TEE_OpenPersistentObject(TEE_STORAGE_PRIVATE, &masterkey_ext_id, sizeof(masterkey_ext_id), flags_read, &obj);
	if(res == TEE_SUCCESS && obj!=TEE_HANDLE_NULL){
		params[1].value.a = 1;
		//DMSG("Master Key exists");
	}
	else if(obj == TEE_HANDLE_NULL){
		params[1].value.a = 0;
		//DMSG("Master Key does not exist");
	}
	TEE_CloseObject(obj);

	return TEE_SUCCESS;
}


static TEE_Result generate_new_masterkey(uint32_t param_types, TEE_Param params[4]){

	uint32_t exp_param_types = TEE_PARAM_TYPES(	TEE_PARAM_TYPE_VALUE_INOUT, 
												TEE_PARAM_TYPE_MEMREF_OUTPUT, 
												TEE_PARAM_TYPE_NONE, 
												TEE_PARAM_TYPE_NONE);
	
	TEE_Result res;
	TEE_ObjectHandle obj = TEE_HANDLE_NULL;
	
	uint32_t strength = 128;
	char* mnemonic = TEE_Malloc(MNEMONIC_LENGTH, TEE_MALLOC_FILL_ZERO);

	//DMSG("has been called");

	// check parameter types
	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;
	// Check pin
	if(params[0].value.a!=1234){
		params[0].value.b = 2;
		return TEE_SUCCESS;
	}
	
	// Generate a random mnemonic
	res = get_random_mnemonic(strength, mnemonic);
	if(res != TEE_SUCCESS) {
		EMSG("Failed to generate mnemonic: 0x%x", res);
	} //else {
		//DMSG("Mnemonic generated.");
	//}

	// Send the mnemonic to client
	TEE_MemMove(params[1].memref.buffer, mnemonic, MNEMONIC_LENGTH);

	TEE_CloseObject(obj);

	from_mnemonic_to_masterkey(mnemonic);

	return TEE_SUCCESS;
}

static TEE_Result mnemonic_to_masterkey(uint32_t param_types, TEE_Param params[4]){
	uint32_t exp_param_types = TEE_PARAM_TYPES(	TEE_PARAM_TYPE_VALUE_INOUT, 
												TEE_PARAM_TYPE_MEMREF_INPUT, 
												TEE_PARAM_TYPE_NONE, 
												TEE_PARAM_TYPE_NONE);
	
	char* mnemonic = TEE_Malloc(MNEMONIC_LENGTH, TEE_MALLOC_FILL_ZERO);

	//DMSG("has been called");

	// check parameter types
	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;
	// Check pin
	if(params[0].value.a!=1234){
		params[0].value.b = 2;
		return TEE_SUCCESS;
	}

	TEE_MemMove(mnemonic, params[1].memref.buffer, MNEMONIC_LENGTH);

	from_mnemonic_to_masterkey(mnemonic);

	return TEE_SUCCESS;
}

static TEE_Result erase_masterkey(uint32_t param_types, TEE_Param params[4]){
	uint32_t exp_param_types = TEE_PARAM_TYPES(	TEE_PARAM_TYPE_VALUE_INOUT, 
												TEE_PARAM_TYPE_VALUE_OUTPUT, 
												TEE_PARAM_TYPE_NONE, 
												TEE_PARAM_TYPE_NONE);
	
	TEE_Result res;
	TEE_ObjectHandle obj = TEE_HANDLE_NULL;
	uint32_t flags_read = TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE_META;
	uint32_t masterkey_ext_id = TA_OBJECT_MASTERKEY_EXT;

	//DMSG("has been called");

	// check parameter types
	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;
	// Check pin
	if(params[0].value.a!=1234){
		params[0].value.b = 2;
		return TEE_SUCCESS;
	}

	res = TEE_OpenPersistentObject(TEE_STORAGE_PRIVATE, &masterkey_ext_id, sizeof(masterkey_ext_id), flags_read, &obj);
	if(res == TEE_SUCCESS && obj!=TEE_HANDLE_NULL){
		params[1].value.a = 1;
		//DMSG("Master Key exists");
		res = TEE_CloseAndDeletePersistentObject1(obj);
		return res;
	}
	else if(obj == TEE_HANDLE_NULL){
		params[1].value.a = 0;
		//DMSG("Master Key does not exist");
	}

	return TEE_SUCCESS;
}

static TEE_Result get_bitcoin_address(uint32_t param_types, TEE_Param params[4]){
	uint32_t exp_param_types = TEE_PARAM_TYPES(	TEE_PARAM_TYPE_VALUE_INOUT, 
												TEE_PARAM_TYPE_VALUE_INPUT, 
												TEE_PARAM_TYPE_MEMREF_OUTPUT, 
												TEE_PARAM_TYPE_NONE);
	uint32_t account_id;
	uint8_t address[34];
	TEE_Result res;
	
	//DMSG("has been called");

	// check parameter types
	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;
	// Check pin
	if(params[0].value.a!=1234){
		params[0].value.b = 2;
		return TEE_SUCCESS;
	}

	account_id = params[1].value.a;

	//printf("%d\n",account_id);
	res = get_account_address(address, account_id);

	//printf("\nget_bitcoin_address\n");
	//print_uint8(address, 25);

	TEE_MemMove(params[2].memref.buffer, address, 25);
	//print_uint8(params[2].memref.buffer, 25);

	return res;
}


static TEE_Result sign_transaction(uint32_t param_types, TEE_Param params[4]){
	uint32_t exp_param_types = TEE_PARAM_TYPES(	TEE_PARAM_TYPE_VALUE_INOUT, 
												TEE_PARAM_TYPE_MEMREF_INPUT, 
												TEE_PARAM_TYPE_MEMREF_OUTPUT,
												TEE_PARAM_TYPE_VALUE_INPUT);
	uint32_t res;
	uint32_t account_id;

	//DMSG("has been called");

	// check parameter types
	if (param_types != exp_param_types)
		return TEE_ERROR_BAD_PARAMETERS;
	// Check pin
	if(params[0].value.a!=1234){
		params[0].value.b = 2;
		return TEE_SUCCESS;
	}

	account_id = params[3].value.a;

	//for (uint32_t i = 0; i < params[1].memref.size; i++){
		//DMSG("%x", ((uint8_t *)params[1].memref.buffer)[i]);
	//}
	//printf("\nbefore sign raw tx\n\n");
	res = sign_raw_tx((uint8_t *)params[1].memref.buffer, params[1].memref.size,
					  (uint8_t *)params[2].memref.buffer, account_id);
	//printf("\nafter sign raw tx\n\n");
	if (res == 1) {
		//DMSG("Transaction has been succefully signed.");
		params[0].value.a = 1;
	} else {
		//DMSG("Failed to sign address. Code 0x%x\n", res);
		params[0].value.b = 1;
	}

	return TEE_SUCCESS;
}


static void get_child_privatekey(uint32_t i, uint8_t* child_sk, uint8_t* child_chaincode){
	TEE_Result res;
	TEE_ObjectHandle obj = TEE_HANDLE_NULL;

	uint32_t flags_read = TEE_DATA_FLAG_ACCESS_READ;

	uint8_t masterkey_ext[64];
	uint8_t masterkey[32];
	uint8_t masterchain[32];
	uint32_t masterkey_ext_len;
	uint32_t masterkey_ext_id = TA_OBJECT_MASTERKEY_EXT;

	// change to hardened wallet
	// printf("\n%zu\n",i);
	i = i +(uint32_t)(1<<31);
	// printf("\ni: %zu\n",i);

	res = TEE_OpenPersistentObject(TEE_STORAGE_PRIVATE, &masterkey_ext_id, sizeof(masterkey_ext_id), flags_read, &obj);
	//if(res == TEE_SUCCESS) {
	//	//DMSG("Opening masterkey success");
	//} else {
	//	EMSG("Failed to open masterkey: 0x%x", res);
	//}

	// Read extended masterkey from object
	res = TEE_ReadObjectData(obj, masterkey_ext, 64, &masterkey_ext_len);
	//if(res == TEE_SUCCESS) {
	//	//DMSG("Reading masterkey success");
	//} else {
	//	EMSG("Failed to read masterkey: 0x%x", res);
	//}

	TEE_CloseObject(obj);

	TEE_MemMove(masterkey, masterkey_ext, 32);
	TEE_MemMove(masterchain, masterkey_ext+32, 32);
	
	res = hdnode_private_ckd(masterkey, masterchain, i, child_sk, child_chaincode);
	//if(res == TEE_SUCCESS) {
	//	//DMSG("success");
	//} else {
	//	EMSG("Failed: 0x%x", res);
	//}
}


static void get_child_publickey(uint32_t i, uint8_t* child_pk_x, uint8_t* child_pk_y){
	TEE_Result res;
	TEE_ObjectHandle obj = TEE_HANDLE_NULL;

	uint32_t flags_read = TEE_DATA_FLAG_ACCESS_READ;

	uint8_t masterkey_ext[64];
	uint8_t masterkey[32];
	uint8_t masterchain[32];
	uint32_t masterkey_ext_len;
	uint32_t masterkey_ext_id = TA_OBJECT_MASTERKEY_EXT;

	//printf("%d\n", i);

	i = i +(uint32_t)(1<<31);

	//printf("%u\n", i);

	res = TEE_OpenPersistentObject(TEE_STORAGE_PRIVATE, &masterkey_ext_id, sizeof(masterkey_ext_id), flags_read, &obj);
	//if(res == TEE_SUCCESS) {
	//	//DMSG("Opening masterkey success");
	//} else {
	//	EMSG("Failed to open masterkey: 0x%x", res);
	//}

	// Read extended masterkey from object
	res = TEE_ReadObjectData(obj, masterkey_ext, 64, &masterkey_ext_len);
	//if(res == TEE_SUCCESS) {
	//	//DMSG("Reading masterkey success");
	//} else {
	//	EMSG("Failed to read masterkey: 0x%x", res);
	//}

	TEE_CloseObject(obj);

	TEE_MemMove(masterkey, masterkey_ext, 32);
	TEE_MemMove(masterchain, masterkey_ext+32, 32);
	
	res = hdnode_public_ckd(masterkey, masterchain, i, child_pk_x, child_pk_y);
	//if(res == TEE_SUCCESS) {
	//	//DMSG("success");
	//} else {
	//	EMSG("Failed: 0x%x", res);
	//}
}

static void print_uint8(uint8_t* array, uint32_t array_len){
	uint32_t i;

	for(i=0; i<array_len; i++){
		printf("%x", array[i]);
	}
	printf("\n");
}

static void from_mnemonic_to_masterkey (char* mnemonic){

	uint32_t flags_write = TEE_DATA_FLAG_ACCESS_READ | 
						TEE_DATA_FLAG_ACCESS_WRITE | 
						TEE_DATA_FLAG_ACCESS_WRITE_META | 
						TEE_DATA_FLAG_SHARE_READ | 
						TEE_DATA_FLAG_SHARE_WRITE;

	TEE_Result res;
	TEE_ObjectHandle obj = TEE_HANDLE_NULL;

	uint8_t seed[512/8];
	uint8_t masterkey[32];
	uint8_t masterchain[32];
	uint8_t masterkey_ext[64];

	uint32_t masterkey_ext_id = TA_OBJECT_MASTERKEY_EXT;
	const char* passphrase = "mnemonic";

	// Generate seed, mnemonic --- password passphrase --- salt
	res = from_mnemonic_to_seed(mnemonic, passphrase, seed, 0);
	//if(res == TEE_SUCCESS) {
	//	//DMSG("Seed Generated");
	//} else {
	//	EMSG("Failed to generate seed: 0x%x", res);
	//}

	res = hdnode_from_seed(seed, sizeof(seed), masterkey, masterchain);
	//if(res == TEE_SUCCESS) {
	//	//DMSG("Generate master key success");
	//} else {
	//	EMSG("Failed to generate master key: 0x%x", res);
	//}

	TEE_MemMove(masterkey_ext, masterkey, 32);
	TEE_MemMove(masterkey_ext+32, masterchain, 32);

	obj = TEE_HANDLE_NULL;
	res = TEE_CreatePersistentObject(TEE_STORAGE_PRIVATE, &masterkey_ext_id, sizeof(masterkey_ext_id), flags_write, TEE_HANDLE_NULL, masterkey_ext, 64, &obj);
	//if(res == TEE_SUCCESS) {
	//	//DMSG("Store master key success");
	//} else {
	//	EMSG("Failed to store master key: 0x%x", res);
	//}

	TEE_CloseObject(obj);

	//printf("\n##########################\n");
	//printf("Mnemonic: %s\n", mnemonic);
	//printf("%d\n", strlen(mnemonic));
	//printf("Seed: ");
	//print_uint8(seed, 64);
	//printf("Master Key: ");
	//print_uint8(masterkey, 32);
	//printf("Master Chaincode: ");
	//print_uint8(masterchain, 32);
	//printf("##########################\n\n");
}


static uint32_t sign_raw_tx(uint8_t *rawtx, size_t bytes, uint8_t *sig, uint32_t account_id){
	TEE_Result res;
	TEE_ObjectHandle key = NULL;
	TEE_OperationHandle op = (TEE_OperationHandle)NULL;
	TEE_OperationHandle op2 = (TEE_OperationHandle)NULL;
	uint8_t child_sk[32];
	uint8_t child_pk_x[32];
	uint8_t child_pk_y[32];
	uint8_t child_cc[32];
	TEE_Attribute attr[4];

	size_t hlen = 32;
	size_t siglen = 72 * 8;
	uint8_t *hash = TEE_Malloc(hlen, TEE_MALLOC_FILL_ZERO);
	get_child_privatekey(account_id, child_sk, child_cc);
	get_child_publickey(account_id, child_pk_x, child_pk_y);
	TEE_AllocateTransientObject(TEE_TYPE_ECDSA_KEYPAIR, 256, &key);
	TEE_InitRefAttribute(attr, TEE_ATTR_ECC_PRIVATE_VALUE, child_sk, 32);
	TEE_InitRefAttribute(attr+1, TEE_ATTR_ECC_PUBLIC_VALUE_X, child_pk_x, 32);
	TEE_InitRefAttribute(attr+2, TEE_ATTR_ECC_PUBLIC_VALUE_Y, child_pk_y, 32);
	TEE_InitValueAttribute(attr+3, TEE_ATTR_ECC_CURVE, TEE_ECC_CURVE_NIST_P256, 4);
	TEE_PopulateTransientObject(key, attr, 4);

	res = TEE_AllocateOperation(&op, TEE_ALG_SHA256, TEE_MODE_DIGEST, 0);
	res = TEE_DigestDoFinal(op, rawtx, bytes, hash, &hlen);
	res = TEE_DigestDoFinal(op, hash, hlen, hash, &hlen);

	//DMSG("Key retrieved");
	res = TEE_AllocateOperation(&op2, TEE_ALG_ECDSA_P256, TEE_MODE_SIGN, 256);
	//if(res != TEE_SUCCESS){
	//	//DMSG("Error allocation sign op 0x%x", res);
	//} else {
	//	//DMSG("Allocation success");
	//}

	/* Set the key for the signing operation */
	res = TEE_SetOperationKey(op2, key);
	//if(res != TEE_SUCCESS){
	//	//DMSG("Error setting the key 0x%x", res);
	//} else {
	//	//DMSG("Key has been set!");
	//}

	/* Sign the hash of the raw transaction */
	res = TEE_AsymmetricSignDigest(op2, NULL, 0, hash, hlen, sig, &siglen);
	//if(res != TEE_SUCCESS){
	//	//DMSG("Error signing 0x%x", res);
	//} else {
	//	//DMSG("Sign complete!");
	//}

	//for(uint32_t i = 0; i < 72; i++){
	//	//DMSG("%x", sig[i]);
	//}
	if(res == TEE_SUCCESS)return 1;
	else return 0;
}

static TEE_Result get_account_address(uint8_t *addr, uint32_t account_id){
	TEE_Result res;
	TEE_ObjectHandle key = (TEE_ObjectHandle)NULL;
	uint8_t child_sk[32];
	uint8_t child_pk_x[32];
	uint8_t child_pk_y[32];
	// uint8_t child_chaincode[32]
	TEE_Attribute attr[4];

	get_child_publickey(account_id, child_pk_x, child_pk_y);

	TEE_AllocateTransientObject(TEE_TYPE_ECDSA_KEYPAIR, 256, &key);
	TEE_InitRefAttribute(attr, TEE_ATTR_ECC_PRIVATE_VALUE, child_sk, 32);
	TEE_InitRefAttribute(attr+1, TEE_ATTR_ECC_PUBLIC_VALUE_X, child_pk_x, 32);
	TEE_InitRefAttribute(attr+2, TEE_ATTR_ECC_PUBLIC_VALUE_Y, child_pk_y, 32);
	TEE_InitValueAttribute(attr+3, TEE_ATTR_ECC_CURVE, TEE_ECC_CURVE_NIST_P256, 4);
	TEE_PopulateTransientObject(key, attr, 4);
	res = ecdsa_to_bitaddr(key, addr, TESTNET_P2PKH_PREFIX);

	return res;
}

static TEE_Result ecdsa_to_bitaddr(TEE_ObjectHandle obj, uint8_t *bcadd, uint8_t network){
	TEE_Result res = TEE_SUCCESS;
	TEE_OperationHandle sha256_op = (TEE_OperationHandle)NULL;
	size_t shasize = 32;
	uint32_t keysize = 32;
	uint32_t j = 1;
	uint8_t net = network;

	uint32_t *pubX = TEE_Malloc(keysize, TEE_MALLOC_FILL_ZERO);
	uint32_t *pubY = TEE_Malloc(keysize, TEE_MALLOC_FILL_ZERO);
	uint32_t *pubkey = TEE_Malloc(2 * keysize, TEE_MALLOC_FILL_ZERO);
	uint8_t *extkey = TEE_Malloc(2 * keysize + 1, TEE_MALLOC_FILL_ZERO);
	uint8_t *shahash = TEE_Malloc(keysize, TEE_MALLOC_FILL_ZERO);
	uint8_t ripehash[20];
	uint8_t extripe[25];
	uint8_t *checksum = TEE_Malloc(4, TEE_MALLOC_FILL_ZERO);


	/* First stage: Retrieve the generated public X and Y values from the TEE */
	res = TEE_GetObjectBufferAttribute(obj, TEE_ATTR_ECC_PUBLIC_VALUE_X, pubX, &keysize);
	//if (res != TEE_SUCCESS) {
	//	//DMSG("Failed to retrieve ECDSA Public X. Error: 0x%x", res);
	//}
	res = TEE_GetObjectBufferAttribute(obj, TEE_ATTR_ECC_PUBLIC_VALUE_Y, pubY, &keysize);
	//if (res != TEE_SUCCESS) {
	//	//DMSG("Failed to retrieve ECDSA Public Y. Error: 0x%x", res);
	//}

	/* Second stage: Concatenate the two retrieved values into a single buffer */
	TEE_MemMove(pubkey, pubX, 32);
	TEE_MemMove(pubkey + 8, pubY, 32);
	TEE_Free(pubX);
	TEE_Free(pubY);
	pubX = NULL;
	pubY = NULL;

	/* Third stage: Preparation of the extended key, convert the key to octets. */
	for(uint32_t i = 0; i < 16; i++) {
		extkey[j] = (pubkey[i] >> 24) & 0xFF;
		j++;
		extkey[j] = (pubkey[i] >> 16) & 0xFF;
		j++;
		extkey[j] = (pubkey[i] >> 8) & 0xFF;
		j++;
		extkey[j] = pubkey[i] & 0xFF;
		j++;
	}

	/* The first byte is required to be 0x04 by the Bitcoin spec. */
	extkey[0] = BC_VERSION_BYTE;

	/* Fourth stage: Round 1 of SHA256 hashing. */
	res = TEE_AllocateOperation(&sha256_op, TEE_ALG_SHA256, TEE_MODE_DIGEST, 0);
	res = TEE_DigestDoFinal(sha256_op, extkey, 65, shahash, &shasize);


	/* Fifth stage: Round 1 of RIPEMD160 hashing */
	TEE_MemMove(ripehash, RMD((uint8_t*)shahash, 32), 20);
	//printf("%d\n", (int)ripehash);
	//print_uint8(ripehash, 32);
	extripe[0] = net;
	TEE_MemMove(extripe + 1, ripehash, 20);
	res = TEE_DigestDoFinal(sha256_op, extripe, 21, shahash, &shasize);
	res = TEE_DigestDoFinal(sha256_op, shahash, 32, shahash, &shasize);


	/* Sixth stage: Retrieve the checksum and append on the extended key. */
	for(uint32_t i = 0; i < 4; i++){
		checksum[i] = shahash[i];
	}

	TEE_MemMove(extripe + 21, checksum, 4);
	TEE_Free(shahash);
	// TEE_Free(ripehash);
	TEE_Free(checksum);
	TEE_Free(extkey);
	TEE_Free(pubkey);
	// TEE_MemMove(bcadd, extripe, 24);
	res = base58(extripe, 25, bcadd);

	return res;
}

static TEE_Result base58(uint8_t *instr, size_t size, uint8_t *outstr){

	uint32_t res = TEE_SUCCESS;
	int32_t b58ch = 0;
	uint8_t b58table[] = {'1','2','3','4','5','6','7','8','9','A','B','C','D','E',
						  'F','G','H','J','K','L','M','N','P','Q','R','S','T','U',
						  'V','W','X','Y','Z','a','b','c','d','e','f','g','h','i',
						  'j','k','m','n','o','p','q','r','s','t','u','v','w','x',
						  'y','z'};


	/* Variables for the TEE BigInteger operations. */
	TEE_BigInt *a;
	TEE_BigInt *b;
	TEE_BigInt *quotient;
	TEE_BigInt *reminder;
	size_t bintsiz;
	size_t b58len = 0; /* Keeps track of the base58 string length after each division */
	int32_t cont; /* Keeps track wheather or not we have more divisions left */
	uint8_t divisor = 58;
	uint32_t zcount = 0;
	uint8_t *b58str = TEE_Malloc(58 + 1, TEE_MALLOC_FILL_ZERO);
	/* Max length of a bitcoin address can be 34 bytes */
	uint8_t *final58 = TEE_Malloc(34 + 1, TEE_MALLOC_FILL_ZERO);


	// Allocation and initialization of the big integers
	bintsiz = (size_t) TEE_BigIntSizeInU32(296); // 37 bytes = 296 bits
	a = TEE_Malloc(bintsiz * sizeof(TEE_BigInt), TEE_MALLOC_FILL_ZERO);
	TEE_BigIntInit(a, bintsiz);

	bintsiz = (size_t) TEE_BigIntSizeInU32(8);
	b = TEE_Malloc(bintsiz * sizeof(TEE_BigInt), TEE_MALLOC_FILL_ZERO);
	TEE_BigIntInit(b, bintsiz);

	bintsiz = (size_t) TEE_BigIntSizeInU32(296);
	reminder = TEE_Malloc(bintsiz * sizeof(TEE_BigInt), TEE_MALLOC_FILL_ZERO);
	TEE_BigIntInit(reminder, bintsiz);

	bintsiz = (size_t) TEE_BigIntSizeInU32(296);
	quotient = TEE_Malloc(bintsiz * sizeof(TEE_BigInt), TEE_MALLOC_FILL_ZERO);
	TEE_BigIntInit(quotient, bintsiz);

	/* Convert the dividend (key) & divisor (58) from octets to BigIntegers */
	res = TEE_BigIntConvertFromOctetString(a, instr, size, 0);
	res = TEE_BigIntConvertFromOctetString(b, &divisor, 1, 0);

	/* Start dividing and adding the encoded characters in the output string */
	TEE_BigIntDiv(quotient, reminder, a, b);
	res = TEE_BigIntConvertToS32(&b58ch, reminder);
	b58str[b58len] = b58table[b58ch];
	cont = TEE_BigIntCmpS32(reminder, 0);
	b58len++;

	while (cont != 0) {
		TEE_BigIntDiv(quotient, reminder, quotient, b);
		res = TEE_BigIntConvertToS32(&b58ch, reminder);
		b58str[b58len] = b58table[b58ch];
		b58len++;
		cont = TEE_BigIntCmpS32(quotient, 0);
	}

	/* Count the leading zeroes of the input hashed string */
	while (instr[zcount] == 0x00){
		zcount++;
	}

	TEE_MemFill(final58, b58table[0], zcount);
	TEE_MemMove(final58 + zcount, b58str, b58len);
	final58[b58len] = '\0';

	//DMSG("%s", final58);
	reverse_str(final58, b58len);
	//DMSG("Bitcoin base58 format %s", final58);
	TEE_MemMove(outstr, final58, 38);

	// TEE_MemMove(outstr, b58str, 38);

	return res;
}

static void reverse_str(uint8_t *str, size_t len){
	uint8_t tmp;

	if (len <= 0) {
		return;
	}

	for (uint32_t i = 0; i < len / 2; i++) {
		tmp = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = tmp;
	}
}
