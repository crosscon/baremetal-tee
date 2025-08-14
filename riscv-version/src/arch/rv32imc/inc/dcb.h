/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */
#ifndef __DCB_H__
#define __DCB_H__

#ifndef __ASSEMBLER__
#include <utango.h>

/* ==== Debug Control Block (DCB) ===================================== */
#define DCB_BASE                    (0xE000EDF0UL)
#define DCB                         ((DCB_type*)DCB_BASE)

#define DCB_DEMCR_TRCENA            (1 << 24)

/* struct type to access SAU */
typedef struct
{
    volatile uint32_t DHCSR;
    volatile uint32_t DCRSR;
    volatile uint32_t DCRDR;
    volatile uint32_t DEMCR;
    volatile uint32_t RESERVED0[1U];
    volatile uint32_t DAUTHCTRL;
    volatile uint32_t DSCSR;
} DCB_type;

#endif  /* |__ASSEMBLER__ */
#endif /* __DCB_H__ */