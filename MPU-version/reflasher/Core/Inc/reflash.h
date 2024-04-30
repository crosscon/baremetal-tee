#ifndef __REFLASH_H
#define __REFLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "stm32l4xx_hal.h"

void reflash(uint32_t* src, uint32_t* dst, uint32_t len);
void reset();

#ifdef __cplusplus
}
#endif

#endif /* __REFLASH_H */