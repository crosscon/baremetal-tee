#include "sec_comm.h"
#include "wifi_wrapper.h"

#define PACKET_LEN_BYTES 4	// bytes indicating packet size (4 = 32 bit unsigned integer)

RNG_HandleTypeDef sec_comm_hrng;

/**
  * @brief  Private function, decrypts new incoming packet and stores plaintext into context buffer
  * @param  ctx : sec_comm_context where the plaintext will be stored
  * @retval Operation status. Return SEC_COMM_OK when operations are performed successfully, SEC_COMM_ERROR otherwise
  */
int32_t sec_comm_refill_plaintext(sec_comm_context* ctx);

/**
  * @brief  Private function, generates random bytes of data
  * @param  ctx : sec_comm_context
  * @param  buff : buffer where generated data will be stored
  * @param  len : number of bytes to generate
  * @retval Operation status SEC_COMM_OK when operation performed successfully, SEC_COMM_ERROR otherwise
  */
int32_t sec_comm_rng_generate(sec_comm_context* ctx, uint8_t* buff, uint32_t len);


int32_t sec_comm_init(sec_comm_context* ctx, uint32_t socket) {
	sec_comm_hrng.Instance = RNG;
	if(HAL_OK != HAL_RNG_Init(&sec_comm_hrng))
		return SEC_COMM_ERROR;	// rng peripheral initialization error

	mbedtls_chachapoly_init(&(ctx->ccp_ctx));	// init encryption/decryption context

	ctx->socket = socket;	// set socket
	ctx->plaintext_len = 0;
	ctx-> plaintext_next = 0;
	
	return SEC_COMM_OK;
}

int32_t sec_comm_deinit(sec_comm_context* ctx) {
	mbedtls_chachapoly_free(&ctx->ccp_ctx);	// free chachapoly context
	sec_comm_hrng.Instance = RNG;
	if(HAL_OK != HAL_RNG_DeInit(&sec_comm_hrng))
		return SEC_COMM_ERROR;	// rng peripheral deinitialization error
	return SEC_COMM_OK;
}

int32_t sec_comm_set_key(sec_comm_context* ctx,  const uint8_t* key) {
	if(0 != mbedtls_chachapoly_setkey(&(ctx->ccp_ctx), key))	// set encryption/decryption key
		return SEC_COMM_ERROR;	// encryption/decryption context initialization failed
	return SEC_COMM_OK;
}

int32_t sec_comm_connect(sec_comm_context* ctx, uint8_t* ipaddr, uint16_t port, uint16_t local_port) {
	if(WIFI_STATUS_OK != wifi_wrapper_open_client_connection(ctx-> socket, ipaddr, port, local_port))
		return SEC_COMM_CONNECTION_ERROR;
	return SEC_COMM_OK;
}

int32_t sec_comm_disconnect(sec_comm_context* ctx) {
	if(WIFI_STATUS_OK == wifi_wrapper_close_client_connection(ctx-> socket))
		return SEC_COMM_OK;
	else
		return SEC_COMM_ERROR;
}

int32_t sec_comm_send(sec_comm_context* ctx, const uint8_t* buff, uint32_t len) {
	uint32_t remaining = len;
	uint8_t ciphertext_buff[BUFFER_SIZE];
	uint8_t auth_tag_buff[AUTH_TAG_LEN];
	uint8_t nonce_buff[NONCE_LEN];
	
	/* Divide data in chunks if necessary */
	while(remaining > 0) {
		uint32_t chunk_size = remaining < BUFFER_SIZE ? remaining : BUFFER_SIZE;	// plaintext processed in chunks of at most BUFFER_SIZE len

		/* Generate nonce */
		if(SEC_COMM_OK != sec_comm_rng_generate(ctx, nonce_buff, NONCE_LEN))
			return SEC_COMM_ERROR;	// failed to generate nonce

		/* Encrypt and authenticate data */

		if(0 != mbedtls_chachapoly_encrypt_and_tag(
			&ctx->ccp_ctx,
			chunk_size,
			nonce_buff,
			nonce_buff, NONCE_LEN,
			&buff[len - remaining],
			ciphertext_buff, auth_tag_buff
		))
			return SEC_COMM_ERROR;	// encryption failed		

		/* Send packet length on socket */
		if(WIFI_STATUS_OK != wifi_wrapper_send_data(ctx-> socket, (uint8_t *) &chunk_size, 4))
			return SEC_COMM_ERROR;	// data send failed
		
		/* Send ciphertext */
		if(WIFI_STATUS_OK != wifi_wrapper_send_data(ctx-> socket, ciphertext_buff, (uint16_t) chunk_size))
			return SEC_COMM_ERROR;	// data send failed

		/* Send auth tag */
		if(WIFI_STATUS_OK != wifi_wrapper_send_data(ctx-> socket, auth_tag_buff, AUTH_TAG_LEN))
			return SEC_COMM_ERROR;	// data send failed

		/* Send nonce */
		if(WIFI_STATUS_OK != wifi_wrapper_send_data(ctx-> socket, nonce_buff, NONCE_LEN))
			return SEC_COMM_ERROR;	// data send failed

		remaining -= chunk_size;
	}
	return len;
}

int32_t sec_comm_recv(sec_comm_context* ctx, uint8_t* buff, uint32_t len) {
	uint32_t remaining = len;
	uint32_t buff_index = 0;

	while(remaining > 0) {
		if(ctx->plaintext_next < ctx->plaintext_len) {	// data available from plaintext buffer
			buff[buff_index] = ctx->plaintext_buff[ctx->plaintext_next];
			ctx->plaintext_next++;
			buff_index++;
			remaining--;
		} else {	// plaintext buffer is empty, need to decrypt new packet
			if(SEC_COMM_OK != sec_comm_refill_plaintext(ctx))
				return SEC_COMM_ERROR;
		}
	}

	return len;
}

int32_t sec_comm_refill_plaintext(sec_comm_context* ctx) {
	uint32_t ciphertext_len;
	uint8_t ciphertext_buff[BUFFER_SIZE];
	uint8_t auth_tag_buff[AUTH_TAG_LEN];
	uint8_t nonce_buff[NONCE_LEN];
	if(ctx->plaintext_next < ctx->plaintext_len)
		return SEC_COMM_ERROR;	// plaintext buffer is not empty
	
	/* Reset context buffer variables */
	ctx->plaintext_len = 0;
	ctx->plaintext_next = 0;

	/* Read encrypted packet len */
	if(WIFI_STATUS_OK != wifi_wrapper_receive_data(ctx-> socket, (uint8_t *) &ciphertext_len, PACKET_LEN_BYTES)) {
		return SEC_COMM_ERROR;
	}

	if(ciphertext_len > BUFFER_SIZE)
		return SEC_COMM_ERROR;	// encrypted packet does not fit in buffer

	/* Read ciphertext */
	if(WIFI_STATUS_OK != wifi_wrapper_receive_data(ctx-> socket, ciphertext_buff, ciphertext_len)) {
		return SEC_COMM_ERROR;	// failed to read encrypted packet
	}

	/* Read auth tag */
	if(WIFI_STATUS_OK != wifi_wrapper_receive_data(ctx-> socket, auth_tag_buff, AUTH_TAG_LEN)) {
		return SEC_COMM_ERROR;	// failed to read auth tag
	}

	/* Read nonce */
	if(WIFI_STATUS_OK != wifi_wrapper_receive_data(ctx-> socket, nonce_buff, NONCE_LEN)) {
		return SEC_COMM_ERROR;	// failed to read nonce
	}

	/* Decrypt and store packet */
	if(0 != mbedtls_chachapoly_auth_decrypt(
		&ctx->ccp_ctx,
		ciphertext_len,
		nonce_buff,
		nonce_buff, NONCE_LEN,
		auth_tag_buff,
		ciphertext_buff,
		ctx->plaintext_buff
	))
		return SEC_COMM_ERROR;	// authenticated decryption error
	
	/* Update context buffer variables */
	ctx->plaintext_len = ciphertext_len;

	return SEC_COMM_OK;
}

int32_t sec_comm_rng_generate(sec_comm_context* ctx, uint8_t* buff, uint32_t len) {
	UNUSED(ctx);
	for(uint32_t i = 0; i < len; i++) {
		uint32_t int_out;
		if(HAL_RNG_GenerateRandomNumber(&sec_comm_hrng, &int_out) == HAL_OK) {
			for(uint32_t j = 0; j < 32; j+=8) {	// split int_out into 4 separate bytes
				if(i < len) {
					buff[i] = (uint8_t) (int_out >> j);
					i++;
				}
			}
		} else {
			return SEC_COMM_ERROR;	// random bytes generation failed
		}
	}
	return SEC_COMM_OK;
}