/* Standard Libs */
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define AES_KEY_SIZE 32 // AES-256
#define AES_BLOCK_SIZE 16

// Include the TEE API header files
#include "tee_client_api.h"
#include "tee_core_api.h"

#define INVOKE_SVC(svc_num)    __asm volatile ("svc %0" : : "I" (svc_num))

TEE_Result  TA_CreateEntryPoint(void)
{   
	DMSG("has been called");
    return TEE_SUCCESS;
}

void TA_DestroyEntryPoint(void)
{
	DMSG("has been called");
	return;
}


TEE_Result TA_OpenSessionEntryPoint(uint32_t param_types, 
									TEE_Param params[4], 
									void **sessionContext)
{
	DMSG("has been called");
    return TEE_SUCCESS;
}


void TA_CloseSessionEntryPoint(void* sessionContext)
{
	DMSG("has been called");
	return; 
}


TEE_Result TA_InvokeCommandEntryPoint(void* sessionContext,
									uint32_t commandID,
									uint32_t paramTypes,
									TEE_Param params[4])
{

	DMSG("has been called");

	IMSG("Command ID: %d", commandID);

	//int res = TEE_SUCCESS;

	/*********************** TEST MEMORY FUNCTION ***************************** */
	/*char* test = TEE_Malloc(10, 0);
	char* test2 = TEE_Malloc(10, 0);

	// static array of 10 elements
	//int array[10];

	// Set values in the test buffer
	for (size_t i = 0; i < 10; i++)
	{
		test[i] = 'A' + i;
	}

	// Copy the test buffer to the test2 buffer
	TEE_MemMove(test2, test, 10);	

	TEE_Free(test);
	TEE_Free(test2); */

	/*********************** TEST OBJECTS FUNCTION ***************************** */

	/*TEE_ObjectHandle key = NULL;
	res = TEE_AllocateTransientObject(TEE_TYPE_ECDSA_KEYPAIR, 256, &key);

	if (res != TEE_SUCCESS){
		return res;
	}

	TEE_Attribute attr[4];

	uint8_t child_sk[32];
	uint8_t child_pk_x[32];
	uint8_t child_pk_y[32];
	uint8_t child_cc[32];

	// Initialize randomly child_sk, child_pk_x, child_pk_y, child_cc
	// For now, we just initialize them to i
	for (size_t i = 0; i < 32; i++)
	{
		child_sk[i] = i+3;
		child_pk_x[i] = i;
		child_pk_y[i] = i;
		child_cc[i] = i;
	}
	
	TEE_InitRefAttribute(attr, TEE_ATTR_ECC_PRIVATE_VALUE, child_sk, 32);
	TEE_InitRefAttribute(attr+1, TEE_ATTR_ECC_PUBLIC_VALUE_X, child_pk_x, 32);
	TEE_InitRefAttribute(attr+2, TEE_ATTR_ECC_PUBLIC_VALUE_Y, child_pk_y, 32);
	TEE_InitValueAttribute(attr+3, TEE_ATTR_ECC_CURVE, TEE_ECC_CURVE_NIST_P256, 4);


	// Test populate transient object
	res = TEE_PopulateTransientObject(key, attr, 4);

	if (res != TEE_SUCCESS){
		return res;
	} */


	/*uint8_t buffer[32];
	size_t size = 0;

	// Test get object buffer attribute
	res = TEE_GetObjectBufferAttribute(key, TEE_ATTR_ECC_PRIVATE_VALUE, buffer, &size);

	if (res != TEE_SUCCESS){
		return res;
	}

	// Test get object value attribute
	uint32_t a = 0, b = 0;
	res = TEE_GetObjectValueAttribute(key, TEE_ATTR_ECC_CURVE, &a, &b);

	if (res != TEE_SUCCESS){
		return res;
	}

	// Test write object data
	char* data = "Hello World 12345 9887 Bye!";
	res = TEE_WriteObjectData(key, data, strlen(data));

	if (res != TEE_SUCCESS){
		return res;
	}

	// Test read object data
	char read_data[100];
	size_t count = 0;
	res = TEE_ReadObjectData(key, read_data, 100, &count);

	if (res != TEE_SUCCESS){
		return res;
	} */

	//TEE_FreeTransientObject(key);
	//TEE_CloseObject(key);


	/*********************** TEST RANDOM and OPERATIONS FUNCTIONS ***************************** */
	//int randomBufferLen = 15;
	//uint32_t random_buffer[randomBufferLen];
	//TEE_GenerateRandom(random_buffer, randomBufferLen);

	// test key generation

	/*TEE_OperationHandle operation = NULL;

	res = TEE_AllocateOperation(&operation, TEE_ALG_ECDSA_P256, TEE_MODE_SIGN, 256);
	if(res != TEE_SUCCESS){
		return 0;
	}

	
	TEE_ObjectHandle object = NULL;
	res = TEE_AllocateTransientObject(TEE_TYPE_ECDSA_KEYPAIR, 256, &object);
	if(res != TEE_SUCCESS){
		return res;
	}

	res = TEE_GenerateKey(object, 256, NULL, 0);
	if(res != TEE_SUCCESS){
		return res;
	}


	// Set the key for the signing operation 
	res = TEE_SetOperationKey(operation, object);
	if(res != TEE_SUCCESS){
		//DMSG("Error setting the key 0x%x", res);
		return res;
	} */


	/*********************** TEST CIPHER FUNCTIONS ***************************** */


	/*TEE_Result res;

    TEE_OperationHandle op = NULL;
	TEE_ObjectHandle key_obj = NULL;
    uint8_t key[AES_KEY_SIZE];
    uint8_t iv[AES_BLOCK_SIZE];
    uint32_t key_size = AES_KEY_SIZE * 8; // Key size in bits
    size_t block_size = AES_BLOCK_SIZE;

    // Generate AES key
    TEE_GenerateRandom(key, AES_KEY_SIZE);

    // Generate IV
    TEE_GenerateRandom(iv, block_size);


	// ----------------- AES CTR encryption -----------------

    // Allocate the operation handle
    res = TEE_AllocateOperation(&op, TEE_ALG_AES_CTR, TEE_MODE_ENCRYPT, key_size);
    if (res != TEE_SUCCESS) {
        ERR_MSG("Failed to allocate operation handle: 0x%x", res);
        return res;
    }

    res = TEE_AllocateTransientObject(TEE_TYPE_AES, key_size, &key_obj);
    if (res != TEE_SUCCESS) {
        ERR_MSG("Failed to allocate transient object: 0x%x", res);
        TEE_FreeOperation(op);
        return res;
    }

	// Populate the key into the transient object
    TEE_Attribute attr;
    TEE_InitRefAttribute(&attr, TEE_ATTR_SECRET_VALUE, key, AES_KEY_SIZE);
    res = TEE_PopulateTransientObject(key_obj, &attr, 1);
    if (res != TEE_SUCCESS) {
        ERR_MSG("Failed to populate transient object: 0x%x", res);
        TEE_FreeTransientObject(key_obj);
        TEE_FreeOperation(op);
		
        return res;
    }


    // Set the key for the operation
    res = TEE_SetOperationKey(op, key_obj);
    if (res != TEE_SUCCESS) {
        ERR_MSG("Failed to set operation key: 0x%x", res);
        TEE_FreeOperation(op);
        return res;
    }

    // Initialize the cipher operation
    TEE_CipherInit(op, iv, block_size);

	const char *input = "Ciao mondo!123";
    size_t input_len = strlen(input);
    uint8_t output[128]; // Ensure the buffer is large enough
    size_t output_len = 0;
	size_t out_len = sizeof(output);

    // Update the cipher operation
    res = TEE_CipherUpdate(op, input, input_len, output, &out_len);
    if (res != TEE_SUCCESS) {
        ERR_MSG("Failed to update cipher: 0x%x", res);
        TEE_FreeOperation(op);
        return res;
    }

	output_len += out_len;
	out_len = sizeof(output) - output_len;

    // Finalize the cipher operation
    res = TEE_CipherDoFinal(op, NULL, 0, output + output_len, &out_len);
    if (res != TEE_SUCCESS) {
        ERR_MSG("Failed to finalize cipher: 0x%x", res);
        TEE_FreeOperation(op);
        return res;
    }			


	// Adjust the output length to include the length from CipherUpdate
    output_len += out_len;
    // Clean up
	TEE_FreeTransientObject(key_obj);
    TEE_FreeOperation(op);

	// ----------------- AES CTR decryption -----------------

	TEE_OperationHandle op2 = NULL;
	TEE_ObjectHandle key_obj2 = NULL;

	// Allocate the operation handle
    res = TEE_AllocateOperation(&op2, TEE_ALG_AES_CTR, TEE_MODE_DECRYPT, key_size);
    if (res != TEE_SUCCESS) {
        ERR_MSG("Failed to allocate operation handle: 0x%x", res);
        return res;
    }

    // Allocate the transient object
    res = TEE_AllocateTransientObject(TEE_TYPE_AES, key_size, &key_obj2);
    if (res != TEE_SUCCESS) {
        ERR_MSG("Failed to allocate transient object: 0x%x", res);
        TEE_FreeOperation(op2);
        return res;
    }


	// Initialize the key attribute
	TEE_Attribute attr2;
    TEE_InitRefAttribute(&attr2, TEE_ATTR_SECRET_VALUE, key, AES_KEY_SIZE);

    // Populate the key into the transient object
    res = TEE_PopulateTransientObject(key_obj2, &attr2, 1);
    if (res != TEE_SUCCESS) {
        ERR_MSG("Failed to populate transient object: 0x%x", res);
        TEE_FreeTransientObject(key_obj2);
        TEE_FreeOperation(op2);
        return res;
    }

	// Set the key for the operation
    res = TEE_SetOperationKey(op2, key_obj2);
    if (res != TEE_SUCCESS) {
        ERR_MSG("Failed to set operation key: 0x%x", res);
        TEE_FreeTransientObject(key_obj2);
        TEE_FreeOperation(op2);
        return res;
    }	


    uint8_t output_decryption[128]; // Ensure the buffer is large enough
    size_t output_decryption_len = 0;
	size_t out_decryption_len = sizeof(output_decryption);

	// Initialize the cipher operation
	TEE_CipherInit(op2, iv, block_size);

	// Update the cipher operation
	res = TEE_CipherUpdate(op2, output, output_len, output_decryption, &out_decryption_len);
    if (res != TEE_SUCCESS) {
        ERR_MSG("Failed to update cipher: 0x%x", res);
        TEE_FreeTransientObject(key_obj2);
        TEE_FreeOperation(op2);
        return res;
    }

	output_decryption_len += out_decryption_len;
	out_decryption_len = sizeof(output_decryption) - output_decryption_len;

	// Finalize the cipher operation
    res = TEE_CipherDoFinal(op2, NULL, 0, output_decryption + output_decryption_len, &out_decryption_len);
    if (res != TEE_SUCCESS) {
        ERR_MSG("Failed to finalize cipher: 0x%x", res);
        TEE_FreeTransientObject(key_obj2);
        TEE_FreeOperation(op2);
        return res;
    }

	output_decryption_len += out_decryption_len;	

	// Clean up
	TEE_FreeTransientObject(key_obj2);
	TEE_FreeOperation(op2);

	//printf("AES CTR encryption succeeded. Encrypted data:\n");
    //for (size_t i = 0; i < output_len; i++) {
    //    printf("%02x", output[i]);
    //}
    //printf("\n");

    return res; */


	/*********************** TEST MAC FUNCTIONS ***************************** */

	/*TEE_Result res;

	TEE_OperationHandle operation = NULL;
	TEE_ObjectHandle key_obj = NULL;
	int HMAC_KEY_SIZE = 32;
	uint32_t key_size = HMAC_KEY_SIZE * 8; // Key size in bits
	uint8_t key[HMAC_KEY_SIZE * 8];

	TEE_GenerateRandom(key, HMAC_KEY_SIZE);

	res = TEE_AllocateOperation(&operation, TEE_ALG_HMAC_SHA256, TEE_MODE_MAC, key_size);
	if(res != TEE_SUCCESS){
		return 0;
	}

	res = TEE_AllocateTransientObject(TEE_TYPE_HMAC_SHA256, key_size, &key_obj);
    if (res != TEE_SUCCESS) {
        ERR_MSG("Failed to allocate transient object: 0x%x", res);
        TEE_FreeOperation(operation);
        return res;
    }

	// Populate the key into the transient object
    TEE_Attribute attr;
    TEE_InitRefAttribute(&attr, TEE_ATTR_SECRET_VALUE, key, HMAC_KEY_SIZE);
    res = TEE_PopulateTransientObject(key_obj, &attr, 1);
    if (res != TEE_SUCCESS) {
        ERR_MSG("Failed to populate transient object: 0x%x", res);
        TEE_FreeTransientObject(key_obj);
        TEE_FreeOperation(operation);
		
        return res;
    }


    // Set the key for the operation
    res = TEE_SetOperationKey(operation, key_obj);
    if (res != TEE_SUCCESS) {
        ERR_MSG("Failed to set operation key: 0x%x", res);
        TEE_FreeOperation(operation);
        return res;
    }

	char *message = "Hello World from stm32!";
	char mac[32];
	size_t mac_len = 32;

	TEE_MACInit(operation, NULL, 0);

	TEE_MACUpdate(operation, message, strlen(message));

	res = TEE_MACComputeFinal(operation, NULL, 0, mac, &mac_len);
	if(res != TEE_SUCCESS){
		return res;
	}


	return res; */


	/*********************** TEST Digest FUNCTIONS ***************************** */

	/*char hash[32];
  	size_t hash_len = 0;

	char *message = "Hello World from stm32!";

	TEE_OperationHandle operation = NULL;
	TEE_Result res = TEE_SUCCESS;

	res = TEE_AllocateOperation(&operation, TEE_ALG_SHA256, TEE_MODE_DIGEST, 256);
  	if(res != TEE_SUCCESS){
    	return res;
  	}

	res = TEE_DigestDoFinal(operation, message, strlen(message), hash, &hash_len);
	if(res != TEE_SUCCESS){
		return res;
	}

	return res; */



	/*********************** TEST Asymmetric Sign Digest FUNCTIONS ***************************** */


	/* TEE_Result res;

	TEE_OperationHandle operation = NULL;
	TEE_OperationHandle operation2 = NULL;
	TEE_ObjectHandle key_obj = NULL;

	uint32_t key_size = 256; // Key size in bits


	res = TEE_AllocateOperation(&operation, TEE_ALG_ECDSA_SHA256, TEE_MODE_SIGN, key_size);
	if(res != TEE_SUCCESS){
		return 0;
	}

	res = TEE_AllocateTransientObject(TEE_TYPE_ECDSA_KEYPAIR, key_size, &key_obj);
    if (res != TEE_SUCCESS) {
        ERR_MSG("Failed to allocate transient object: 0x%x", res);
        TEE_FreeOperation(operation);
        return res;
    }

	res = TEE_GenerateKey(key_obj, 256, NULL, 0);
	if(res != TEE_SUCCESS){
		return 0;
	}

    // Set the key for the operation
    res = TEE_SetOperationKey(operation, key_obj);
    if (res != TEE_SUCCESS) {
        ERR_MSG("Failed to set operation key: 0x%x", res);
        TEE_FreeOperation(operation);
        return res;
    } 

	char hash[32];
  	size_t hash_len = 32;
	char sign[64];
  	size_t sign_len = 64;

	char *message = "Hello World from stm32!";

	res = TEE_AllocateOperation(&operation2, TEE_ALG_SHA256, TEE_MODE_DIGEST, 256);
	if(res != TEE_SUCCESS){
		return res;
	}

	res = TEE_DigestDoFinal(operation2, message, strlen(message), hash, &hash_len);
	if(res != TEE_SUCCESS){
		return res;
	}

	res = TEE_AsymmetricSignDigest(operation, NULL, 0, hash, hash_len, sign, &sign_len);
	if(res != TEE_SUCCESS){
		return res;
	}

	res = TEE_AsymmetricVerifyDigest(operation, NULL, 0, hash, hash_len, sign, sign_len);
	if(res != TEE_SUCCESS){
		return 0;
	}

	// Clean up
	TEE_FreeTransientObject(key_obj);
	TEE_FreeOperation(operation);
	TEE_FreeOperation(operation2);

	return res; */



	/*********************** TEST Persistent Object FUNCTIONS ***************************** */

	/* TEE_ObjectHandle object;
    TEE_Result res;

	uint32_t masterkey_id = 3;
	uint8_t  masterkey_ext[64];

	TEE_GenerateRandom(masterkey_ext, 64);

	res = TEE_CreatePersistentObject(TEE_STORAGE_PRIVATE, &masterkey_id, sizeof(uint32_t), 
										TEE_DATA_FLAG_ACCESS_WRITE, NULL, masterkey_ext, 64, &object);
	if(res != TEE_SUCCESS){
		return 0;
	}

	TEE_CloseObject(object);

	res = TEE_OpenPersistentObject(TEE_STORAGE_PRIVATE, &masterkey_id, sizeof(uint32_t), TEE_DATA_FLAG_ACCESS_READ, &object);
	if(res != TEE_SUCCESS){
		return 0;
	}

	uint8_t read_buff[64]; memset(read_buff, 0, sizeof(read_buff));
	size_t count = 0;
	res = TEE_ReadObjectData(object, read_buff, sizeof(read_buff), &count);
	if(res != TEE_SUCCESS){
		return 0;
	}

	res = TEE_CloseAndDeletePersistentObject1(object);
	if(res != TEE_SUCCESS){
		return 0;
	} 


	res = TEE_OpenPersistentObject(TEE_STORAGE_PRIVATE, &masterkey_id, sizeof(uint32_t), TEE_DATA_FLAG_ACCESS_READ, &object);
	if(res != TEE_SUCCESS){
		return 0;
	} */

	return TEE_SUCCESS;
}
