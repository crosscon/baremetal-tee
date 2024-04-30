/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OTA_H
#define __OTA_H

#include "sec_comm.h"

/* Configuration parameters */
#define UPDATE_BUFFER_SIZE 256

/* Return Codes */
#define OTA_OK 0
#define OTA_ERROR 1	// generic error
#define OTA_COMMUNICATION_ERROR 2	// generic communication error
#define OTA_UNEXPECTED_REPLY 3	// server answered with unexpected reply
#define OTA_UPDATE_TOO_LARGE 4	// new firmware does not fit in flash memory
#define OTA_FLASH_LOCK_UNLOCK_ERROR 5	// error while unlocking flash memory
#define OTA_FLASH_ERASE_ERROR 6		// error while eraseing flash memory
#define OTA_FLASH_PROGRAMMING_ERROR 7	// error while programming flash memory
#define OTA_PACKET_TOO_LARGE 8	// received packet surpasses size of buffer
#define OTA_UPDATE_FAIL	9	// hash don't match after update

/* Messages ID */
#define OTA_FIRMWARE_REQUEST 0
#define OTA_FIRMWARE_REPLY 1
#define OTA_FIRMWARE_SIZE_REQUEST 2
#define OTA_FIRMWARE_SIZE_REPLY 3
#define OTA_UPDATE_PACKET 4
#define OTA_UPDATE_NEXT 5
#define OTA_ERROR_REPORT 6
#define OTA_ERROR_REPLY 7
#define OTA_MICROVISOR_REQUEST 8
#define OTA_MICROVISOR_REPLY 9
#define OTA_MICROVISOR_SIZE_REQUEST 10
#define OTA_MICROVISOR_SIZE_REPLY 11
#define OTA_REFLASHER_SIZE_REQUEST 12
#define OTA_REFLASHER_SIZE_REPLY 13

/**
 * \brief			Computes size of fortified application by scrolling backwards
 * 					through flash memory until first non-empty (non 0xffffffff) word is found.
 * \return			Size of current fortified application in bytes (0 if not application is present).
 */
uint32_t ota_compute_firmware_size();

/**
 * \brief			Computes sha256 of flash memory assigned to user application.
 * \param output	Output buffer where sha256 is written,
 * 					must be at least 32 bytes long,
 * 					valid only when function returns 0.
 * \return			OTA_OK or some error.
 */
int ota_compute_firmware_sha256(unsigned char* output);

/**
 * \brief			Checks remote server for Microvisor update and performs it if available.
 * 					Attention, updating the microvisor will wipe the user application currently installed.
 * \param ctx		sec_comm context (must be already initialized)
 * \return			OTA_OK or some error.
 */
uint32_t ota_update_microvisor(sec_comm_context* ctx);

/**
 * \brief			Provides errors stored in permanent storage to remote server.
 * \param ctx		sec_comm context (must be already initialized)
 * \return			OTA_OK or some error.
 */
int ota_report_error(sec_comm_context* ctx);

/**
 * \brief			Checks update availablility and performs firmware update, writes new firmware
 * 					to flash memory, verifies correct update,
 * 					writes new firmware to flash.
 * \param ctx		sec_comm context (must be already initialized)
 * \return			OTA_OK or some error.
 */
int ota_update_firmware(sec_comm_context* ctx);

#endif /* __OTA_H */