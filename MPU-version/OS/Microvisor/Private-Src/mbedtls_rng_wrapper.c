#include "mbedtls_rng_wrapper.h"
#include "mbedtls/entropy.h"


RNG_HandleTypeDef hrng;

/**
 * Initialize STM32 RNG peripheral
 */
HAL_StatusTypeDef mbedtls_rng_init() {
	hrng.Instance = RNG;
	return HAL_RNG_Init(&hrng);
}

/**
 * Deinitialize STM32 RNG peripheral
 */
HAL_StatusTypeDef mbedtls_rng_deinit() {
	hrng.Instance = RNG;
	return HAL_RNG_DeInit(&hrng);
}

/**
 * Entropy poll callback function
 */
int mbedtls_rng_f_source(void *data, unsigned char *output, size_t len, size_t *olen) {
	//UNUSED(data);
	uint32_t int_output;
	size_t i = 0;
	while(i < len) {
		if(HAL_RNG_GenerateRandomNumber(&hrng, &int_output) == HAL_OK) {
			for(int j = 0; j < 32; j+=8) {	// split int_output into 4 separate bytes
				if(i < len) {
					output[i] = (uint8_t) (int_output >> j);
					i++;
				}
			}
		} else {
			*olen = i;
			return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
		}
	}

	*olen = i;
	return 0;
}