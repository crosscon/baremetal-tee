/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */
#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include <sys_regs.h>
#include <platform_config.h>

/* ==== SysTick Timer (SYST_S) ======================================== */

#define MTIME                       ((uint32_t*)(CLINT_BASE+MTIME_OFF))
#define MTIMECMP                    ((uint32_t*)(CLINT_BASE+MTIMECMP_OFF))

#ifndef __ASSEMBLER__

/* struct type to access SCB */
typedef struct
{
    volatile uint32_t CSR;
    volatile uint32_t RVR;
    volatile uint32_t CVR;
    volatile uint32_t CALIB;
} SYST_type;

void systick_init(void);
void systick_enable(void);

__attribute__((always_inline))
static inline void __disable_systick(void) {
    asm volatile (
        "li t0, 0x80\n\t"
        "csrc mie, t0"
        :
        :
        : "t0"
    );
}

__attribute__((always_inline))
static inline void __enable_systick(void) {
    asm volatile (
        "li t0, 0x80\n\t"
        "csrs mie, t0"
        :
        :
        : "t0"
    );
}


#endif  /* |__ASSEMBLER__ */
#endif /* __SYSTICK_H__ */
