#ifndef __ACTIVATOR_H
#define __ACTIVATOR_H

#include "sec_comm.h"
#include "mbedtls/ssl.h"
#include "mbedtls/sha256.h"

extern uint8_t Activation_Server_IP[];	// activation server IP
extern uint16_t ACTIVATION_SERVER_PORT;	// activation server port

#define ACTIVATION_SERVER_PUBKEY_LEN 270	// activation server public key length
extern const uint8_t Activation_Server_PubKey[ACTIVATION_SERVER_PUBKEY_LEN];	// activation server public key

#define STM32L4XX_UID		0x1FFF7590	/* Base address for 96 bit UID */
#define STM32L4XX_UID_LEN	12			/* Length (in bytes) of UID */

/* Module return codes */
#define ACTIVATOR_OK	0
#define ACTIVATOR_ERROR	1
#define ACTIVATOR_COMMUNICATION_ERROR	2
#define ACTIVATOR_UNEXPECTED_REPLY	3

/* Messages IDs */
#define ACTIVATOR_ACTIVATION_REQUEST 0
#define ACTIVATOR_ACTIVATION_REPLY	1

/* Activation result code */
#define ACTIVATOR_ACTIVATION_OK 0
#define ACTIVATOR_INVALID_LICENSE 1
#define ACTIVATOR_LICENSE_LIMIT_EXCEEDED 2

/* Functions used to perform the activation of the board with MCU-Fortifier using the license */
uint32_t activator_is_board_activated();
uint32_t activator_activate_board(sec_comm_context* ssl);

#endif /* __ACTIVATOR_H */