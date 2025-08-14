#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "defines.h"
#include "../bsp/inc/sifive_plic.h"

void write_plic_priority(uint32_t int_num, uint32_t int_priority)
{
    uint32_t* priority_addr = (uint32_t*)PLIC_BASE;

    priority_addr += int_num;

    *priority_addr = int_priority;
}