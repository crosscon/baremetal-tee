// if TA_BITCOIN_WALLET_H is not defined
#ifndef TA_BITCOIN_WALLET_H
#define TA_BITCOIN_WALLET_H

#include "tee_client_api.h"
#include "tee_core_api.h"

#define TA_BITCOIN_WALLET_UUID \
	{ 0x8aaaf200, 0x2450, 0x11e4, \
		{ 0xab, 0xe2, 0x00, 0x02, 0xa5, 0xd5, 0xc5, 0x1b} }

/**
 * Defintion of TA specific constants that identify the command to be executed
 */
#define TA_BITCOIN_WALLET_CMD_1		1
#define TA_BITCOIN_WALLET_CMD_2		2
#define TA_BITCOIN_WALLET_CMD_3		3
#define TA_BITCOIN_WALLET_CMD_4		4
#define TA_BITCOIN_WALLET_CMD_5		5
#define TA_BITCOIN_WALLET_CMD_6		6

#define MNEMONIC_LENGTH 240
#define TA_OBJECT_MASTERKEY_EXT 2

#define TESTNET_P2PKH_PREFIX 	0x6f
#define BC_VERSION_BYTE 0x04

#endif
