#ifndef __SEC_COMM_H
#define __SEC_COMM_H

#include <stdint.h>
#include "mbedtls/chachapoly.h"

#define BUFFER_SIZE		256	// size of receive and send buffer in bytes (plaintext)

#define KEY_LEN			32
#define NONCE_LEN		12
#define AUTH_TAG_LEN	16

/* Return codes */
#define SEC_COMM_OK		-1
#define SEC_COMM_ERROR	-2
#define SEC_COMM_CONNECTION_ERROR -3
#define SEC_COMM_IDENTIFICATION_ERROR -4

/**
 * FORMAT OF SINGLE ENCRYPTED PACKET
 * ciphertext_len	(4 bytes)
 * ciphertext	(ciphertext_len bytes)
 * auth_tag (AUTH_TAG_LEN bytes)
 * nonce	(NONCE_LEN bytes)
*/


typedef struct {
	mbedtls_chachapoly_context ccp_ctx; // chachapoly context for encryption/decryption operations
	uint32_t socket;
	uint8_t plaintext_buff[BUFFER_SIZE];
	uint32_t plaintext_next;
	uint32_t plaintext_len;
} sec_comm_context;

/**
  * @brief Initialize data structures and RNG peripheral
  * @param ctx : sec_comm_context
  * @param socket : socket used for communication
  * @retval SEC_COMM_OK if succesfull connection, SEC_COMM_ERROR otherwise
  */
int32_t sec_comm_init(sec_comm_context* ctx, uint32_t socket);

/**
  * @brief Denitialize data structures and RNG peripheral
  * @param ctx : sec_comm_context
  * @retval SEC_COMM_OK if succesfull connection, SEC_COMM_ERROR otherwise
  */
int32_t sec_comm_deinit(sec_comm_context* ctx);

/**
  * @brief Set symmetric encryption key
  * @param ctx : sec_comm_context
  * @param key : 32 bytes symmetric encryption/decryption key used
  * @retval SEC_COMM_OK if succesfull connection, SEC_COMM_ERROR otherwise
  */
int32_t sec_comm_set_key(sec_comm_context* ctx, const uint8_t* key);

/**
  * @brief Attempts to open a TCP connection to a specified IP and port
  * @param ctx : sec_comm_context
  * @param ipaddr : IP of the target server
  * @param port : port of the target server
  * @param local_port : local port used for connection
  * @retval SEC_COMM_OK if succesfull connection, SEC_COMM_ERROR otherwise
  */
int32_t sec_comm_connect(sec_comm_context* ctx, uint8_t* ipaddr, uint16_t port, uint16_t local_port);

/**
  * @brief Attempts to close an open TCP connection
  * @param ctx : sec_comm_context
  * @retval SEC_COMM_OK if succesfull connection, SEC_COMM_ERROR otherwise
  */
int32_t sec_comm_disconnect(sec_comm_context* ctx);

/**
  * @brief Attempts to send specified amount of bytes encrypting and authenticating them
  * @param ctx : sec_comm_context
  * @param buff : buffer containing data to send
  * @param len	: amount of bytes to send
  * @retval Positive amounts of bytes actually sent or SEC_COMM_ERROR
  */
int32_t sec_comm_send(sec_comm_context* ctx, const uint8_t* buff, uint32_t len);

/**
  * @brief Attempts to retrieve specified amount of bytes of plaintext (decrypting new packets if necessary)
  * @param ctx : sec_comm_context
  * @param buff : buffer where received bytes will be stored
  * @param len	: amount of bytes to receive
  * @retval Positive amounts of bytes actually received or SEC_COMM_ERROR
  */
int32_t sec_comm_recv(sec_comm_context* ctx, uint8_t* buff, uint32_t len);

#endif /* __SEC_COMM_H */