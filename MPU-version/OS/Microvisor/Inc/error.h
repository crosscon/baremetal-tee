#ifndef __ERROR_H
#define __ERROR_H

#include <stdint.h>

/* Error IDs */
#define ERROR_NONE 0xffffffff // No error
#define ERROR_INIT 1          // Initialization error
#define ERROR_EXCEPTION_SIM_PRIO                                               \
  2 // Negative exception requsted during exception simulation
#define ERROR_PPB_ACCESS 3 // Error during PPB access recovery
#define ERROR_REGISTER_SIM                                                     \
  4 // Invalid register used during simulated instruction
#define ERROR_MPU_VIOLATION 5 // MPU violation error

/* Error associated data length (in words) */
#define ERROR_NONE_DATA_LEN 0
#define ERROR_INIT_DATA_LEN 0
#define ERROR_EXCEPTION_SIM_PRIO_DATA_LEN 0
#define ERROR_PPB_ACCESS_DATA_LEN 0
#define ERROR_REGISTER_SIM_DATA_LEN 0
#define ERROR_MPU_VIOLATION_DATA_LEN 6

/* Function to return the length of the error given its ID */
uint32_t error_data_len_from_id(uint32_t error_id);

#endif /* __ERROR_H */