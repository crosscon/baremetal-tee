//#include <tee_client_api.h>
//#include <tee_internal_api_extensions.h>
#include <bitcoin_wallet_ta.h>
#include <string.h>
#include <hmac.h>
#include <sha2.h>
#include <pbkdf2.h>
#include <bip39.h>
#include <bip39_english.h>
#include <options.h>

TEE_Result get_random_mnemonic(uint32_t strength, char* out){

	uint8_t entropy[33];
	uint8_t entropy_hash[32];
	size_t entropy_hash_len = 32;
	uint64_t mnemonic_num = strength / 8 * 3 / 4;
	uint64_t i, j, idx;
	char mnemonic[MNEMONIC_LENGTH];
	char *p = mnemonic;
	

	TEE_Result res;
	TEE_OperationHandle op = (TEE_OperationHandle)NULL;
	
	TEE_GenerateRandom(entropy, strength/8);

	res = TEE_AllocateOperation(&op, TEE_ALG_SHA256, TEE_MODE_DIGEST, 0);
	if(res != TEE_SUCCESS) EMSG("Failed to allocate operation: 0x%x", res);

	res = TEE_DigestDoFinal(op, entropy, strength/8, entropy_hash, &entropy_hash_len);
	if(res != TEE_SUCCESS) EMSG("Failed to DigestDoFinal: 0x%x", res);

	entropy[33] = entropy_hash[0];

	for (i = 0; i < mnemonic_num; i++) {
		idx = 0;
		for (j = 0; j < 11; j++) {
			idx <<= 1;
			idx += (entropy[(i * 11 + j) / 8] & (1 << (7 - ((i * 11 + j) % 8)))) > 0;
		}
		// copy the value from wordlist
		strcpy(p, wordlist[idx]);
		p += strlen(wordlist[idx]);
		*p = (i < mnemonic_num - 1) ? ' ' : 0;
		p++;
	}

	TEE_MemMove(out, mnemonic, MNEMONIC_LENGTH);
	TEE_FreeOperation(op);

	return TEE_SUCCESS;
}

TEE_Result from_mnemonic_to_seed(const char *mnemonic, const char *passphrase, uint8_t seed[512 / 8], void (*progress_callback)(uint32_t current, uint32_t total)){

	uint8_t salt[8 + 256];
	static PBKDF2_HMAC_SHA512_CTX pctx;
	int passphraselen = strlen(passphrase);

	memcpy(salt, "mnemonic", 8);
	memcpy(salt + 8, passphrase, passphraselen);

	pbkdf2_hmac_sha512_Init(&pctx, (const uint8_t *)mnemonic, strlen(mnemonic), salt, passphraselen + 8);

	if (progress_callback) {
		progress_callback(0, BIP39_PBKDF2_ROUNDS);
	}
	for (int i = 0; i < 16; i++) {
		pbkdf2_hmac_sha512_Update(&pctx, BIP39_PBKDF2_ROUNDS / 16);
		if (progress_callback) {
			progress_callback((i + 1) * BIP39_PBKDF2_ROUNDS / 16, BIP39_PBKDF2_ROUNDS);
		}
	}
	pbkdf2_hmac_sha512_Final(&pctx, seed);
	memset(salt, 0, sizeof(salt));

	return TEE_SUCCESS;
}

