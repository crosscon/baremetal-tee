/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */

#ifndef __WORLDS_H__
#define __WORLDS_H__

#include <utango.h>
#include <cpu_regs.h>
#include <sys_regs.h>
#include <pmp.h>
#include <config.h>
#include <plic.h>

typedef struct world_ctx
{
    cpu_regs_t regs;
    cpu_special_regs_t s_regs;
    mem_regions_t w_mem_regions;
    irqs_tcb_t irqs_tcb;
    uint32_t vect_base_addr;
    uint32_t virtual_mstatus;
    uint32_t virtual_mie;
    uint64_t virtual_mtime_cmp;
    uint32_t in_exception;
} world_ctx_t;

typedef struct vt_world
{
    uint32_t world_id;
    uint32_t entry_point;
    world_ctx_t ctx;
} world_tcb_t;

typedef struct world_mtimecmp_list
{
    uint32_t low;
    uint32_t high;
    uint32_t enable;
}world_mtimecmp_list_t;

world_tcb_t* rworld_ctx_ptr;
world_tcb_t  WCB[UTANGO_WORLDS];
world_mtimecmp_list_t mtimecmp_list[UTANGO_WORLDS];


void worlds_init(void);
void worlds_tcbs_init(void);
void worlds_arch_init(void);

#endif /* __WORLDS_H__ */