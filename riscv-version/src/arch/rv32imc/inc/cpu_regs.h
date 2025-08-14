/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */

#ifndef __CPU_REGS_H__
#define __CPU_REGS_H__

#include <utango.h>

#define EXEC_RETURN_INIT_VAL    0xFFFFFFB9

typedef struct cpu_regs
{
    uint32_t x1;
    uint32_t x2;
    uint32_t x3;
    uint32_t x4;
    uint32_t x5;
    uint32_t x6;
    uint32_t x7;
    uint32_t x8;
    uint32_t x9;
    uint32_t x10;
    uint32_t x11;
    uint32_t x12;
    uint32_t x13;
    uint32_t x14;
    uint32_t x15;
    uint32_t x16;
    uint32_t x17;
    uint32_t x18;
    uint32_t x19;
    uint32_t x20;
    uint32_t x21;
    uint32_t x22;
    uint32_t x23;
    uint32_t x24;
    uint32_t x25;
    uint32_t x26;
    uint32_t x27;
    uint32_t x28;
    uint32_t x29;
    uint32_t x30;
    uint32_t x31;
} cpu_regs_t;

typedef struct cpu_special_regs
{
    uint32_t mstatus;
    uint32_t mepc;
    uint32_t mcause;
    uint32_t mtval;
    uint32_t mie;
}cpu_special_regs_t;

void cpu_ctx_init(uint32_t world_id);

#endif /* __CPU_REGS_H__ */