#ifndef __FLASH__
#define __FLASH__

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/*
 * Functions used to handle secure storage in FLASH memory for trusted
 * applications A specific memory areas are reserved for each TA using the
 * linker script file (e.g. FLASH_SECURE_TA1) Each TA has 16KB of reserved
 * memory area for secure storage
 *
 * The secure storage area does not include a real file system, but data are
 * organized using a JSON structure Each object has an ID, length, and data Yhe
 * data are stored in base64 encoded format to avoid character encoding issues
 */

void flash_internalRead(uint8_t *rx_buff, size_t len, int addr);

int flash_writeNewObject(const char *ctx, uint32_t len, int obj_id,
                         uint32_t ta_id);

size_t flash_objectSize(const char *ctx, uint32_t len, int obj_id);

int flash_readObject(const char *ctx, uint32_t len, int obj_id, char *out_buff,
                     size_t out_len);

uint32_t flash_getFreeSize(uint32_t ta_id);

int flash_deleteObject(uint32_t ta_id, int obj_id);

// Ersaing the flash area which is dedicated for the relevant TA passed as a
// parameter
int flash_erase(uint32_t ta_id);

// Get flash area starting address and total size using TA id
void flash_getConfig(uint32_t ta_id, uint32_t *start_addr,
                     uint32_t *total_size);

#endif
