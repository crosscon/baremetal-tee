#ifndef __BOOTLOADER_H
#define __BOOTLOADER_H

#include "stm32l4xx_hal.h"

/**
 * Defintion of custom functions to boot the system and to reset the system
 */
void boot(void);
void soft_reset(void);

#endif /* __BOOTLOADER_H */