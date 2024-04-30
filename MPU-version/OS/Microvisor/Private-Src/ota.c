#include "ota.h"
#include "mbedtls/sha256.h"
#include "stm32l4xx_hal.h"
#include "activator.h"
#include "permanent_storage.h"
#include "memory_map.h"
#include "microvisor_config.h"
#include "error.h"

/**
 * \brief	Boots Reflasher utility from RAM.
 */
__attribute__((naked)) void ota_boot_reflasher(uint32_t* src, uint32_t* dst, uint32_t len) {
	__asm__(
		/* The reflasher is stored in RAM sarting from the __ram_boot_start__ 
			location before calling the function  */
		"ldr r3, =__ram_boot_start__\n"
		"ldr r3, [r3, 4]\n"	// load ResetHandler address
		"bx r3\n"
	);
}

/**
 * \brief	Erases all flash memory reserved for fortified application.
 * 			Requires flash to be unlocked before calling.
 */
uint32_t ota_erase_flash() {
	/* STM32L475 device specific code */
	uint32_t base_page = (((uint32_t) &__flash_start__ - (uint32_t) &__flash_boot_start__) / FLASH_PAGE_SIZE);	// first page dedicated to user app
	uint32_t bank_1_available = (FLASH_BANK_SIZE / FLASH_PAGE_SIZE) - base_page;	// pages in bank 1 available for user app
	FLASH_EraseInitTypeDef erase_config_bank_1 = {
		FLASH_TYPEERASE_PAGES,	// erase pages
		1,	// erase from bank 1
		base_page,	// base page
		bank_1_available	// num pages
	};
	// Erase all the pages in the second bank
	FLASH_EraseInitTypeDef erase_config_bank_2 = {
		FLASH_TYPEERASE_PAGES,
		2,
		(FLASH_BANK_SIZE / FLASH_PAGE_SIZE),
		(FLASH_BANK_SIZE / FLASH_PAGE_SIZE)
	};
	uint32_t page_error;
	if(HAL_FLASHEx_Erase(&erase_config_bank_1, &page_error) != HAL_OK) {
		HAL_FLASH_Lock();
		return OTA_FLASH_ERASE_ERROR;
	}
	if(page_error != 0xFFFFFFFF) {
		HAL_FLASH_Lock();
		return OTA_FLASH_ERASE_ERROR;
	}
	if(HAL_FLASHEx_Erase(&erase_config_bank_2, &page_error) != HAL_OK) {
		HAL_FLASH_Lock();
		return OTA_FLASH_ERASE_ERROR;
	}
	if(page_error != 0xFFFFFFFF) {
		HAL_FLASH_Lock();
		return OTA_FLASH_ERASE_ERROR;
	}
	return OTA_OK;
}

/**
 * \brief	Computes size of firmware (fortified app) in flash
*/
uint32_t ota_compute_firmware_size() {
	uint32_t* last_word = (uint32_t*) ((uint32_t) &__flash_start__ + (uint32_t) &__flash_size__);
	last_word--;	// scroll to last address of flash
	while(last_word >= (uint32_t*) &__flash_start__) {
		if(*last_word == 0xffffffff){	// flash still empty, decrease pointer
			last_word--;
			continue;
		} else {
			break;	// found last word of firmware
		}
	}
	uint32_t size = (uint32_t) last_word - (uint32_t) &__flash_start__ + 4;	// + 4 to include the last word
	return size;
}

/**
 * \brief	Computes sha256 hash of firmware in flash
*/
int ota_compute_firmware_sha256(unsigned char* output) {
	// The firmware size is stored in the permanent storage (it is calculated during the boot)
	if(mbedtls_sha256((unsigned char*) &__flash_start__, (size_t) PERMA_STORAGE->firmware_size, output, 0) == 0) {
		return OTA_OK;
	} else {
		return OTA_ERROR;
	}
}

/**
 * \brief	Retrive the reflasher utility and updated version of the microvisor 
 * 			from the server, load the reflasher in memory and lauch it
*/
uint32_t ota_update_microvisor(sec_comm_context* ctx) {
	uint32_t msg_id = OTA_MICROVISOR_REQUEST;
	uint8_t buffer[UPDATE_BUFFER_SIZE];

	/* Check for Microvisor update */
	if(sec_comm_send(ctx, (unsigned char *) &msg_id, 4) != 4) {
		return OTA_COMMUNICATION_ERROR;
	}
	/* Read reply */
	if(sec_comm_recv(ctx, buffer, 4) != 4) {	// read 4 bytes message code
		return OTA_COMMUNICATION_ERROR;
	}
	if(*((uint32_t *) buffer) != OTA_MICROVISOR_REPLY) {
		return OTA_UNEXPECTED_REPLY;
	}
	if(sec_comm_recv(ctx, buffer, 4) != 4) { // read reply
		return OTA_COMMUNICATION_ERROR;
	}
	switch(*((uint32_t *) buffer)) {
		case 0:
			return OTA_OK;	// no microvisor update available
		case 1:
			break;	// microvisor update available, perform it
		default:
			return OTA_UNEXPECTED_REPLY;
	}

	/* Unlock flash */
	WRITE_REG(FLASH->SR, 0x8000);	// clear OPTVERR flag
	if(HAL_FLASH_Unlock() != HAL_OK) {
		return OTA_FLASH_LOCK_UNLOCK_ERROR;
	}

	/* Erase all user app flash */
	if(OTA_OK != ota_erase_flash())
		return OTA_FLASH_ERASE_ERROR;

	/* 
		NOTE: start downloading the reflasher utility from the update server
		The reflasher is not stored in the flash as it would consume precious storage space
	*/

	/* Retrieve reflasher utility size */
	uint32_t reflasher_size;
	msg_id = OTA_REFLASHER_SIZE_REQUEST;
	if(sec_comm_send(ctx, (uint8_t *) &msg_id, 4) != 4) {
		return OTA_COMMUNICATION_ERROR;
	}
	if(sec_comm_recv(ctx, buffer, 4) != 4) {	// read 4 bytes message code
		return OTA_COMMUNICATION_ERROR;
	}
	if(*((uint32_t *) buffer) != OTA_REFLASHER_SIZE_REPLY) {
		return OTA_UNEXPECTED_REPLY;
	}
	if(sec_comm_recv(ctx, (uint8_t *) &reflasher_size, 4) != 4) { // read reflasher utility size
		return OTA_COMMUNICATION_ERROR;
	}

	uint32_t remaining_size, current_address;
	current_address = (uint32_t) &__flash_start__;
	/* Start request-read-flash loop for the reflasher utility */
	remaining_size = reflasher_size;
	while(remaining_size > 0) {
		msg_id = OTA_UPDATE_NEXT;
		if(sec_comm_send(ctx, (uint8_t *) &msg_id, 4) != 4) {	// request packet
			HAL_FLASH_Lock();
			return OTA_COMMUNICATION_ERROR;
		}
		if(sec_comm_recv(ctx, buffer, 4) != 4) {	// read message id
			HAL_FLASH_Lock();
			return OTA_COMMUNICATION_ERROR;
		}
		if(*((uint32_t *) buffer) != OTA_UPDATE_PACKET) {	// check for update packet
			HAL_FLASH_Lock();
			return OTA_UNEXPECTED_REPLY;
		}
		uint32_t packet_size;
		if(sec_comm_recv(ctx, (uint8_t *) &packet_size, 4) != 4) { // read packet_size
			HAL_FLASH_Lock();
			return OTA_COMMUNICATION_ERROR;
		}
		if(packet_size > UPDATE_BUFFER_SIZE) {	// packet_size must be lower than buffer size
			HAL_FLASH_Lock();
			return OTA_PACKET_TOO_LARGE;
		}
		if(sec_comm_recv(ctx, buffer, packet_size) != packet_size) { // read whole packet
			HAL_FLASH_Lock();
			return OTA_COMMUNICATION_ERROR;
		}

		/* Reset unused buffer part (to prevent unwanted data writes in case of unaligned accesses) */
		for(uint32_t i = packet_size; i < UPDATE_BUFFER_SIZE; i++) {
			buffer[i] = 0xff; // Set to default empty flash value
		}

		/* Flash the packet one double word at the time */
		for(uint32_t packet_index = 0; packet_index < packet_size; packet_index += 8) {
			uint64_t d_word = *(uint64_t*) &buffer[packet_index]; //extract double word
			if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, current_address, d_word) != HAL_OK) {
				HAL_FLASH_Lock();
				return OTA_FLASH_PROGRAMMING_ERROR;
			} else {
				// double word (64 bit = 8 bytes) programmed succesfully
				current_address += 8;
			}
		}
		remaining_size -= packet_size;
	}

	current_address = (current_address & ~(0x7)) + 0x8;	// align current_address to next double word
	uint32_t microvisor_begin = current_address;

	/* Retrieve microvisor size */
	uint32_t microvisor_size;
	msg_id = OTA_MICROVISOR_SIZE_REQUEST;
	if(sec_comm_send(ctx, (uint8_t *) &msg_id, 4) != 4) {
		return OTA_COMMUNICATION_ERROR;
	}
	if(sec_comm_recv(ctx, buffer, 4) != 4) {	// read 4 bytes message code
		return OTA_COMMUNICATION_ERROR;
	}
	if(*((uint32_t *) buffer) != OTA_MICROVISOR_SIZE_REPLY) {
		return OTA_UNEXPECTED_REPLY;
	}
	if(sec_comm_recv(ctx, (uint8_t *) &microvisor_size, 4) != 4) { // read microvisor size
		return OTA_COMMUNICATION_ERROR;
	}

	/* Start request-read-flash loop for downloading the update */
	remaining_size = microvisor_size;
	while(remaining_size > 0) {
		msg_id = OTA_UPDATE_NEXT;
		if(sec_comm_send(ctx, (uint8_t *) &msg_id, 4) != 4) {	// request packet
			HAL_FLASH_Lock();
			return OTA_COMMUNICATION_ERROR;
		}
		if(sec_comm_recv(ctx, buffer, 4) != 4) {	// read message id
			HAL_FLASH_Lock();
			return OTA_COMMUNICATION_ERROR;
		}
		if(*((uint32_t *) buffer) != OTA_UPDATE_PACKET) {	// check for update packet
			HAL_FLASH_Lock();
			return OTA_UNEXPECTED_REPLY;
		}
		uint32_t packet_size;
		if(sec_comm_recv(ctx, (uint8_t *) &packet_size, 4) != 4) { // read packet_size
			HAL_FLASH_Lock();
			return OTA_COMMUNICATION_ERROR;
		}
		if(packet_size > UPDATE_BUFFER_SIZE) {	// packet_size must be lower than buffer size
			HAL_FLASH_Lock();
			return OTA_PACKET_TOO_LARGE;
		}
		if(sec_comm_recv(ctx, buffer, packet_size) != packet_size) { // read whole packet
			HAL_FLASH_Lock();
			return OTA_COMMUNICATION_ERROR;
		}

		/* Reset unused buffer part (to prevent unwanted data writes in case of unaligned accesses) */
		for(uint32_t i = packet_size; i < UPDATE_BUFFER_SIZE; i++) {
			buffer[i] = 0xff; // Set to default empty flash value
		}

		/* Flash the packet one double word at the time */
		for(uint32_t packet_index = 0; packet_index < packet_size; packet_index += 8) {
			uint64_t d_word = *(uint64_t*) &buffer[packet_index]; //extract double word
			if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, current_address, d_word) != HAL_OK) {
				HAL_FLASH_Lock();
				return OTA_FLASH_PROGRAMMING_ERROR;
			} else {
				// double word (64 bit = 8 bytes) programmed succesfully
				current_address += 8;
			}
		}
		remaining_size -= packet_size;
	}

	/* Transfer reflasher utility to RAM */
	uint8_t* ram_ptr = (uint8_t*) &__ram_boot_start__;
	uint8_t* reflasher_ptr = (uint8_t*) &__flash_start__;
	for(uint32_t i = 0; i < reflasher_size; i++) {
		*ram_ptr = *reflasher_ptr;
		ram_ptr++;
		reflasher_ptr++;
	}

	/* Launch reflasher */
	ota_boot_reflasher((uint32_t*) microvisor_begin, (uint32_t*) &__flash_boot_start__, microvisor_size);

	return OTA_OK;
}

/**
 * \brief	Report the error stored in the permanent memory to
 * 			the server and clear error storage
*/
int ota_report_error(sec_comm_context* ctx) {
	uint32_t msg_id = OTA_ERROR_REPORT;
	uint32_t error_id = PERMA_STORAGE->error_id;
	uint32_t error_data_len = error_data_len_from_id(error_id);

	if(error_id == ERROR_NONE)
		return OTA_OK;
	
	/* Compose and write error report */
	if(sec_comm_send(ctx, (unsigned char *) &msg_id, 4) != 4) {
		return OTA_COMMUNICATION_ERROR;
	}
	size_t total_data_len = 4 + (error_data_len * 4);	// error length (in bytes) of error id + error data
	if(sec_comm_send(ctx, (unsigned char *) &(PERMA_STORAGE->error_id), total_data_len) != total_data_len) {
		return OTA_COMMUNICATION_ERROR;
	}
	/* Read reply */
	int reply;
	if(sec_comm_recv(ctx, (unsigned char *) &reply, 4) != 4) {	// read 4 bytes message code
		return OTA_COMMUNICATION_ERROR;
	}
	if(reply != OTA_ERROR_REPLY) {
		return OTA_UNEXPECTED_REPLY;
	}

	/* Clear error storage */
	if(perma_storage_clear_error() != PERMA_STORAGE_OK)
		return OTA_FLASH_PROGRAMMING_ERROR;
	return OTA_OK;
}

/**
 * \brief	Check the availability of a new firmware, usng SHA, and perform the update when needed.
 * 			The new firmware is downloaded from the server
*/
int ota_update_firmware(sec_comm_context* ctx) {
	/* Allocate buffers and variables */
	uint32_t msg_id = OTA_FIRMWARE_REQUEST;
	uint8_t buffer[UPDATE_BUFFER_SIZE];

	/* Compute firmware sha256 (32 bytes) */
	if(ota_compute_firmware_sha256((uint8_t*) buffer) != 0) {
		return OTA_ERROR;
	}
	/* Check for firmware update availablility */
	if(sec_comm_send(ctx, (uint8_t*) &msg_id, 4) != 4) {
		return OTA_COMMUNICATION_ERROR;
	}
	if(sec_comm_send(ctx, buffer, 32) != 32) {
		return OTA_COMMUNICATION_ERROR;
	}
	/* Read reply */
	if(sec_comm_recv(ctx, buffer, 4) != 4) {	// read 4 bytes message code
		return OTA_COMMUNICATION_ERROR;
	}
	if(*((uint32_t *) buffer) != OTA_FIRMWARE_REPLY) {
		return OTA_UNEXPECTED_REPLY;
	}
	if(sec_comm_recv(ctx, buffer, 4) != 4) { // read reply
		return OTA_COMMUNICATION_ERROR;
	}
	switch(*((uint32_t *) buffer)) {
		case 0:
			return OTA_OK;	// no firmware update available
		case 1:
			break;	// firmware update available, perform it
		default:
			return OTA_UNEXPECTED_REPLY;
	}

	/* Unlock flash */
	WRITE_REG(FLASH->SR, 0x8000);	// clear OPTVERR flag
	if(HAL_FLASH_Unlock() != HAL_OK) {
		return OTA_FLASH_LOCK_UNLOCK_ERROR;
	}

	/* Erase all user app flash */
	if(OTA_OK != ota_erase_flash())
		return OTA_FLASH_ERASE_ERROR;

	/* Retrieve size of firmware update */
	uint32_t firmware_size;		// size of update in bytes
	msg_id = OTA_FIRMWARE_SIZE_REQUEST;
	if(sec_comm_send(ctx, (uint8_t *) &msg_id, 4) != 4) {
		return OTA_COMMUNICATION_ERROR;
	}
	if(sec_comm_recv(ctx, buffer, 4) != 4) {	// read 4 bytes message code
		return OTA_COMMUNICATION_ERROR;
	}
	if(*((uint32_t *) buffer) != OTA_FIRMWARE_SIZE_REPLY) {
		return OTA_UNEXPECTED_REPLY;
	}
	if(sec_comm_recv(ctx, (uint8_t *) &firmware_size, 4) != 4) { // read firmware size
		return OTA_COMMUNICATION_ERROR;
	}
	if(firmware_size > ((uint32_t) &__flash_size__)) {
		return OTA_UPDATE_TOO_LARGE;
	}

	/* Start request-read-flash loop */
	uint32_t remaining_size = firmware_size;
	uint32_t current_address = (uint32_t) &__flash_start__;
	while(remaining_size > 0) {
		msg_id = OTA_UPDATE_NEXT;
		if(sec_comm_send(ctx, (uint8_t *) &msg_id, 4) != 4) {	// request packet
			HAL_FLASH_Lock();
			return OTA_COMMUNICATION_ERROR;
		}
		if(sec_comm_recv(ctx, buffer, 4) != 4) {	// read message id
			HAL_FLASH_Lock();
			return OTA_COMMUNICATION_ERROR;
		}
		if(*((uint32_t *) buffer) != OTA_UPDATE_PACKET) {	// check for update packet
			HAL_FLASH_Lock();
			return OTA_UNEXPECTED_REPLY;
		}
		uint32_t packet_size;
		if(sec_comm_recv(ctx, (uint8_t *) &packet_size, 4) != 4) { // read packet_size
			HAL_FLASH_Lock();
			return OTA_COMMUNICATION_ERROR;
		}
		if(packet_size > UPDATE_BUFFER_SIZE) {	// packet_size must be lower than buffer size
			HAL_FLASH_Lock();
			return OTA_PACKET_TOO_LARGE;
		}
		if(sec_comm_recv(ctx, buffer, packet_size) != packet_size) { // read whole packet
			HAL_FLASH_Lock();
			return OTA_COMMUNICATION_ERROR;
		}

		/* Reset unused buffer part (to prevent unwanted data writes in case of unaligned accesses) */
		for(uint32_t i = packet_size; i < UPDATE_BUFFER_SIZE; i++) {
			buffer[i] = 0xff; // Set to default empty flash value
		}

		/* Flash the packet one double word at the time */
		for(uint32_t packet_index = 0; packet_index < packet_size; packet_index += 8) {
			uint64_t d_word = *(uint64_t*) &buffer[packet_index]; //extract double word
			if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, current_address, d_word) != HAL_OK) {
				HAL_FLASH_Lock();
				return OTA_FLASH_PROGRAMMING_ERROR;
			} else {
				// double word (64 bit = 8 bytes) programmed succesfully
				current_address += 8;
			}
		}
		remaining_size -= packet_size;
	}

	/* Update firmware_length (in FLASH) */
	if(perma_storage_set_firmware_size(firmware_size) != 0) {
		HAL_FLASH_Lock();
		return OTA_FLASH_PROGRAMMING_ERROR;
	}

	/* Compute new sha256 */
	if(ota_compute_firmware_sha256(buffer) != 0) {
		return OTA_ERROR;
	}

	/* Notify update over and send hash of new flash */
	msg_id = OTA_FIRMWARE_REQUEST;
	if(sec_comm_send(ctx, (uint8_t*) &msg_id, 4) != 4) {	// send message_id (4 bytes)
		HAL_FLASH_Lock();
		return OTA_COMMUNICATION_ERROR;
	}
	if(sec_comm_send(ctx, buffer, 32) != 32) {	// send sha256sum (32 bytes)
		HAL_FLASH_Lock();
		return OTA_COMMUNICATION_ERROR;
	}

	/* Read server reply  */
	if(sec_comm_recv(ctx, buffer, 4) != 4) {	// read 4 bytes message code
		HAL_FLASH_Lock();
		return OTA_COMMUNICATION_ERROR;
	}
	if(*((uint32_t *) buffer) != OTA_FIRMWARE_REPLY) {
		HAL_FLASH_Lock();
		return OTA_UNEXPECTED_REPLY;
	}
	if(sec_comm_recv(ctx, buffer, 4) != 4) {	// read reply
		HAL_FLASH_Lock();
		return OTA_COMMUNICATION_ERROR;
	}
	if(*((uint32_t *) buffer) != 0) {
		HAL_FLASH_Lock();
		return OTA_UPDATE_FAIL;
	}
	
	/* Lock flash */
	if(HAL_FLASH_Lock() != HAL_OK)
		return OTA_FLASH_LOCK_UNLOCK_ERROR;
	
	return OTA_OK;
}