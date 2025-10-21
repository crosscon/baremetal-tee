#include "permanent_storage.h"
#include "error.h"
#include "memory_map.h"
#include "microvisor_config.h"

/**
 * \brief Erases all the content of the permanent storage (1 page only on the
 * flash memory)
 */
uint32_t perma_storage_wipe() {
  uint8_t unlocked_flash = 0;

  /* Check if flash is already unlocked, unlock if necessary */
  if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != 0U) {
    unlocked_flash = 1;
    if (HAL_FLASH_Unlock() != HAL_OK)
      return PERMA_STORAGE_FLASH_ERROR;
  }

  /* Erase permanent storage page */
  FLASH_EraseInitTypeDef erase_confige = {
      FLASH_TYPEERASE_PAGES, 1,
      (((uint32_t)&__perma_storage_start__) - (uint32_t)&__flash_boot_start__) /
          FLASH_PAGE_SIZE,
      1};
  uint32_t page_error;
  if (HAL_FLASHEx_Erase(&erase_confige, &page_error) != HAL_OK)
    return PERMA_STORAGE_FLASH_ERROR;
  if (page_error != 0xFFFFFFFF)
    return PERMA_STORAGE_FLASH_ERROR;

  /* Relock flash only if was locked at the beginning of function  */
  if (unlocked_flash) {
    if (HAL_FLASH_Lock() != HAL_OK)
      return PERMA_STORAGE_FLASH_ERROR;
  }

  return PERMA_STORAGE_OK;
}

/**
 * \brief Update data in firmware storage while preserving content previously
 * written that should not be modified
 *
 * \param data: data to be written
 * \param len: length of data
 * \param address: address in permanent storage where data will be written
 */
uint32_t perma_storage_update(uint8_t *data, uint8_t len, uint32_t address) {
  uint8_t unlocked_flash = 0;
  uint8_t buffer[FLASH_PAGE_SIZE];

  /* Check if flash is already unlocked, unlock if necessary */
  if (READ_BIT(FLASH->CR, FLASH_CR_LOCK) != 0U) {
    unlocked_flash = 1;
    if (HAL_FLASH_Unlock() != HAL_OK)
      return PERMA_STORAGE_FLASH_ERROR;
  }

  /* Clear flash PG flag if error occurred during programming */
  CLEAR_BIT(FLASH->CR, FLASH_CR_PG);

  /* Buffer permanent storage content */
  uint32_t *perma_ptr = (uint32_t *)&__perma_storage_start__;
  uint32_t *buffer_byte_ptr = (uint32_t *)buffer;

  for (uint32_t i = 0; i < FLASH_PAGE_SIZE; i += 4) {
    *buffer_byte_ptr = *perma_ptr; // word access to increase speed
    buffer_byte_ptr++;
    perma_ptr++;
  }

  /* Update buffered content */
  uint8_t perma_offset =
      (uint8_t)(address - (uint32_t)&__perma_storage_start__);
  uint8_t data_index = 0;
  while (data_index < len) {
    buffer[perma_offset + data_index] = data[data_index];
    data_index++;
  }

  /* Erase permanent storage page */
  FLASH_EraseInitTypeDef erase_confige = {
      FLASH_TYPEERASE_PAGES, 1,
      (((uint32_t)&__perma_storage_start__) - (uint32_t)&__flash_boot_start__) /
          FLASH_PAGE_SIZE,
      1};
  uint32_t page_error;
  if (HAL_FLASHEx_Erase(&erase_confige, &page_error) != HAL_OK)
    return PERMA_STORAGE_FLASH_ERROR;
  if (page_error != 0xFFFFFFFF)
    return PERMA_STORAGE_FLASH_ERROR;

  /* Write new content to permanent storage */
  uint64_t *buffer_ptr = (uint64_t *)buffer;
  for (uint32_t i = 0; i < FLASH_PAGE_SIZE; i += 8) {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,
                          ((uint32_t)&__perma_storage_start__ + i),
                          *buffer_ptr) != HAL_OK)
      return PERMA_STORAGE_FLASH_ERROR;
    buffer_ptr++;
  }

  /* Relock flash only if previously unlocked at the beginning of function  */
  if (unlocked_flash) {
    if (HAL_FLASH_Lock() != HAL_OK)
      return PERMA_STORAGE_FLASH_ERROR;
  }

  return PERMA_STORAGE_OK;
}

/**
 * \brief Store the current size of the firmware in permament storage
 *
 * \param new_size: updated size of firmware
 */
uint32_t perma_storage_set_firmware_size(uint32_t new_size) {
  return perma_storage_update((uint8_t *)&new_size, 4,
                              (uint32_t)&(PERMA_STORAGE->firmware_size));
}

/**
 * \brief Store an error and the related error data in permament storage
 *
 * \param error_id: id of error to store
 * \param error_data: pointer to error data buffer
 * \param error_data_len: length of error data
 */
uint32_t perma_storage_store_error(uint32_t error_id, uint32_t *error_data,
                                   uint32_t error_data_len) {
  uint32_t status;
  // Store error id
  status = perma_storage_update((uint8_t *)&error_id, 4,
                                (uint32_t)&(PERMA_STORAGE->error_id));
  if (status != 0)
    return status;
  // Store error data
  return perma_storage_update((uint8_t *)error_data,
                              (uint8_t)error_data_len << 2,
                              (uint32_t)&(PERMA_STORAGE->error_data));
}

/**
 * \brief Clear the current error stored in permament storage
 * 		  Called after the error has been uploaded to the server
 */
uint32_t perma_storage_clear_error() {
  uint32_t empty = ERROR_NONE;
  return perma_storage_update((uint8_t *)&empty, 4,
                              (uint32_t)&(PERMA_STORAGE->error_id));
}

/**
 * \brief Store the activation code in the permanent memory
 *
 * \param ac: new activation code to be stored
 */
uint32_t perma_storage_set_activation_code(uint8_t *ac) {
  return perma_storage_update(ac, PERMA_STORAGE_ACTIVATION_CODE_LEN,
                              (uint32_t)&(PERMA_STORAGE->activation_code));
}
