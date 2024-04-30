#ifndef __PERMANENT_STORAGE_H
#define __PERMANENT_STORAGE_H

#include "stm32l4xx_hal.h"

extern unsigned int __perma_storage_start__;

#define PERMA_STORAGE_ACTIVATION_CODE_LEN 32

typedef struct {
	volatile uint8_t activation_code[PERMA_STORAGE_ACTIVATION_CODE_LEN];	/* Activation code downloaded from activation server on first boot */
	volatile uint32_t firmware_size;	/* Size of fortified application */
	volatile uint32_t error_id;			/* ID of occurred error (0xffffffff no error occurred) */
	volatile uint32_t error_data;		/* Error data if present */
} Perma_Storage_Type;

#define PERMA_STORAGE ((Perma_Storage_Type *) &__perma_storage_start__)

#define PERMA_STORAGE_OK 0
#define PERMA_STORAGE_ERROR 1
#define PERMA_STORAGE_FLASH_ERROR 2

/**
 * Wipes content from permanent storage.
 * Unlocks and re-locks flash when necessary,
 * flash is not re-locked if found already unlocked at function enter.
 */
uint32_t perma_storage_wipe();

/**
 * Update data in firmware storage.
 * Performs a read-modify-write operation on the permanent storage
 * preserving content previously written.
 * Unlocks and re-locks flash when necessary,
 * flash is not re-locked if found already unlocked at function enter.
 * 
 * data: data to be written
 * len: length of data in bytes
 * address: address in permanent storage where data will be written
 */
uint32_t perma_storage_update(uint8_t* data, uint8_t len, uint32_t address);

/**
 * Updates firmware length stored in permament storage.
 * 
 * new_size: updated size of firmware
 */
uint32_t perma_storage_set_firmware_size(uint32_t new_size);

/**
 * Updates error stored in permanent storage.
 * 
 * error_id: id of error to store
 * error_data: pointer to error data buffer
 * error_data_len: length of error data (in words)
 */
uint32_t perma_storage_store_error(uint32_t error_id, uint32_t* error_data, uint32_t error_data_len);

/**
 * Clears error stored in permanent storage.
 */
uint32_t perma_storage_clear_error();

/**
 * Updates activation_code stored in permanent storage.
 * 
 * ac: new activation code to be stored.
 */
uint32_t perma_storage_set_activation_code(uint8_t* ac);

#endif /* __PERMANENT_STORAGE_H */