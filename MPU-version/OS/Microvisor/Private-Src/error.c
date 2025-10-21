#include "error.h"

/**
 * Get the error size from the error id
 *
 * Parameters:
 * error_id: the error id
 *
 * Returns:
 * the size of the error data
 */
uint32_t error_data_len_from_id(uint32_t error_id) {
  switch (error_id) {
  case ERROR_INIT:
    return ERROR_INIT_DATA_LEN;
  case ERROR_EXCEPTION_SIM_PRIO:
    return ERROR_EXCEPTION_SIM_PRIO_DATA_LEN;
  case ERROR_PPB_ACCESS:
    return ERROR_PPB_ACCESS_DATA_LEN;
  case ERROR_REGISTER_SIM:
    return ERROR_REGISTER_SIM_DATA_LEN;
  case ERROR_MPU_VIOLATION:
    return ERROR_MPU_VIOLATION_DATA_LEN;
  case ERROR_NONE:
  default:
    return 0;
  }
}