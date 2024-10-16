#ifndef __BIP32_H__
#define __BIP32_H__

//#include <tee_client_api.h>
//#include <tee_internal_api_extensions.h>
#include <ecdsa.h>
#include "tee_common.h"
#include "tee_core_api.h"

typedef struct {
	const char *bip32_name;    // string for generating BIP32 xprv from seed
	const ecdsa_curve *params; // ecdsa curve parameters, null for ed25519
} curve_info;

TEE_Result hdnode_from_seed(const uint8_t *seed, int seed_len, uint8_t* master_sk, uint8_t* master_chaincode);
TEE_Result hdnode_private_ckd(uint8_t* parent_sk, uint8_t* parent_chaincode, uint32_t i, uint8_t* child_sk, uint8_t* child_chaincode);
TEE_Result hdnode_public_ckd(uint8_t* parent_sk, uint8_t* parent_chaincode, uint32_t i, uint8_t* child_pk_x, uint8_t* child_pk_y);

#endif
