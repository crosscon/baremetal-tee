/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */
#ifndef __PLATFORM_IRQS_H__
#define __PLATFORM_IRQS_H__

#define N_IRQS                  96

#ifndef __ASSEMBLER__

typedef enum irqs_list
{
    MachineSoftwareInterrupt    = 3,
    MachineTimerInterrupt       = 7,
    MachineExternalInterrupt    = 11
} irqs_list_t;

typedef enum ext_irqs_list
{
    UART0 = 3,
    UART1 = 4
} ext_irqs_list_t;

typedef enum ext_irqs_priority
{
    PRIORITY_0 = 0,
    PRIORITY_1,
    PRIORITY_2,
    PRIORITY_3,
    PRIORITY_4,
    PRIORITY_5,
    PRIORITY_6,
    PRIORITY_7,
    PRIORITY_8,
    PRIORITY_9,
    PRIORITY_10,
    PRIORITY_11,
    PRIORITY_12,
    PRIORITY_13,
    PRIORITY_14,
    PRIORITY_15
} ext_irqs_priority_t;


#endif  /* |__ASSEMBLER__ */
#endif /* __PLATFORM_IRQS_H__ */