#include <bip32.h>
#include <string.h>
#include <stdbool.h>
//#include <tee_client_api.h>
//#include <tee_internal_api_extensions.h>
#include <inttypes.h>
#include <secp256k1.h>

static void print_uint8(uint8_t* array, uint32_t array_len){
	uint32_t i;
	for(i=0; i<array_len; i++){
		printf("%x", array[i]);
	}
	printf("\n");
}


TEE_Result hdnode_from_seed(const uint8_t *seed, int seed_len, uint8_t* master_sk, uint8_t* master_chaincode)
{
	TEE_OperationHandle op = (TEE_OperationHandle)NULL;
	TEE_ObjectHandle key = (TEE_ObjectHandle)NULL;
	TEE_Attribute attr;
	TEE_Result res;

	uint8_t mac[64];
	const char key_str[512/8] = "Bitcoin seed";
	uint32_t key_len = sizeof(key_str);
	size_t mac_len = 64;
	uint8_t il[32];
	uint8_t ir[32];
	
	// mac operation must be init before compute final, and the operator has to have a key
	res = TEE_AllocateOperation(&op, TEE_ALG_HMAC_SHA512, TEE_MODE_MAC, 512);
	if(res != TEE_SUCCESS) EMSG("Failed in allocating operation: 0x%x", res);

	res = TEE_AllocateTransientObject(TEE_TYPE_HMAC_SHA512, 512, &key);
	if(res != TEE_SUCCESS) EMSG("Failed in allocating transient objec: 0x%x", res);
	
	TEE_InitRefAttribute(&attr, TEE_ATTR_SECRET_VALUE, key_str, key_len);

	res = TEE_PopulateTransientObject(key, &attr, 1);
	if(res != TEE_SUCCESS) EMSG("Failed in populating transient object: 0x%x", res);
	
	res = TEE_SetOperationKey(op,key);
	if(res != TEE_SUCCESS) EMSG("Failed in seting operation key: 0x%x", res);

	TEE_MACInit(op, NULL, 0);
	TEE_MACUpdate(op, seed, seed_len);

	res = TEE_MACComputeFinal(op, NULL, 0, mac, &mac_len);
	if(res != TEE_SUCCESS) EMSG("Failed in computing final mac: 0x%x", res);

	TEE_MemMove(il, mac, 32);
	TEE_MemMove(ir, mac+32, 32);

	TEE_MemMove(master_sk, il, 32);
	TEE_MemMove(master_chaincode, ir, 32);

	TEE_CloseObject(key);
	TEE_FreeOperation(op);

	return TEE_SUCCESS;
}

/*
	Bitcoin ECDSA public keys represent a point on a particular Elliptic Curve (EC) defined in secp256k1.
	use hardened child key only, which only allows user to generate child key from parent private key
 */
TEE_Result hdnode_private_ckd(uint8_t* parent_sk, uint8_t* parent_chaincode, uint32_t i, uint8_t* child_sk, uint8_t* child_chaincode)
{
	TEE_Result res;
	TEE_Attribute attr;
	TEE_ObjectHandle key = (TEE_ObjectHandle)NULL;
	TEE_OperationHandle op = TEE_HANDLE_NULL;
	uint8_t mac[64];
	uint8_t entropy[37];
	size_t mac_len = 64;
	uint8_t il[32];
	uint8_t ir[32];
	bignum256 a;
	bignum256 b;

	const ecdsa_curve* curve = &secp256k1;

	if (i< (uint32_t)(1 << 31)){
		EMSG("Only support hardened keys");
		printf("%zu\n", i);
		return TEE_ERROR_BAD_PARAMETERS;
	}

	entropy[0] = 0;
	TEE_MemMove(entropy+1, parent_sk, 32);
	TEE_MemMove(entropy+33, &i, 4);	

	// HMAC-SHA512 (parent_chain, 0x00||parent_sk||i)
	res = TEE_AllocateOperation(&op, TEE_ALG_HMAC_SHA512, TEE_MODE_MAC, 512);
	if(res != TEE_SUCCESS) EMSG("Failed in allocating operation: 0x%x", res);
	res = TEE_AllocateTransientObject(TEE_TYPE_HMAC_SHA512, 512, &key);
	if(res != TEE_SUCCESS) EMSG("Failed in allocating transient objec: 0x%x", res);
	TEE_InitRefAttribute(&attr, TEE_ATTR_SECRET_VALUE, parent_chaincode, 32);
	res = TEE_PopulateTransientObject(key, &attr, 1);
	if(res != TEE_SUCCESS) EMSG("Failed in populating transient object: 0x%x", res);
	res = TEE_SetOperationKey(op,key);
	if(res != TEE_SUCCESS) EMSG("Failed in seting operation key: 0x%x", res);
	TEE_MACInit(op, NULL, 0);
	TEE_MACUpdate(op, entropy, 37);
	res = TEE_MACComputeFinal(op, NULL, 0, mac, &mac_len);
	if(res != TEE_SUCCESS) EMSG("Failed in computing final mac: 0x%x", res);

	TEE_MemMove(il, mac, 32);
	TEE_MemMove(ir, mac+32, 32);

	bn_read_be(parent_sk, &a);

	while(true){
		bool failed = false;
		bn_read_be(il, &b);
		if(!bn_is_less(&b, &curve->order)){// b >= order
			failed = true;
		}else{
			bn_add(&b, &a);
			bn_mod(&b, &curve->order);
			if(bn_is_zero(&b)){
				failed = true;
			}
		}
		if(!failed){
			bn_write_be(&b, child_sk);
			break;
		}
	}

	TEE_MemMove(child_chaincode, ir, 32);

	return TEE_SUCCESS;
}


TEE_Result hdnode_public_ckd(uint8_t* parent_sk, uint8_t* parent_chaincode, uint32_t i, uint8_t* child_pk_x, uint8_t* child_pk_y)
{
	uint8_t child_sk[32];
	uint8_t child_pk[65];
	uint8_t child_chaincode[32];
	const ecdsa_curve* curve = &secp256k1;

	hdnode_private_ckd(parent_sk, parent_chaincode, i, child_sk, child_chaincode);
	
	/*computes extended public key based on extended private key*/
	ecdsa_get_public_key65(curve, child_sk, child_pk);

	TEE_MemMove(child_pk_x, child_pk+1, 32);
	TEE_MemMove(child_pk_y, child_pk+33, 32);

	// printf("i: %u\n", i);

	printf("\nChild_sk:");
	print_uint8(child_sk, 32);
	printf("Child_cc:");
	print_uint8(child_chaincode, 32);

	printf("\nChild_pk_x:");
	print_uint8(child_pk_x, 32);
	printf("Child_pk_y:");
	print_uint8(child_pk_y, 32);
	printf("\n");

	return TEE_SUCCESS;
}
