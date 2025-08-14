/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */

#include <worlds.h>
#include <systick.h>

#define DEFINE_OFFSET(SYMBOL, STRUCT, FIELD)  \
    asm volatile("\n-> " #SYMBOL " %0 \n" : : "i"(offsetof(STRUCT, FIELD)))

#define DEFINE_SIZE(SYMBOL, TYPE)  \
    asm volatile("\n-> " #SYMBOL " %0 \n" : : "i"(sizeof(TYPE)))

void world_defines() __attribute__((used));
void world_defines(){
    DEFINE_SIZE(WCB_SIZE, world_tcb_t);
    DEFINE_OFFSET(WCB_CTX_OFF, world_tcb_t, ctx);
    DEFINE_OFFSET(WCB_CTX_S_REGS_OFF, world_tcb_t, ctx.s_regs);
    DEFINE_OFFSET(WCB_CTX_CPU_REGS_OFF, world_tcb_t, ctx.regs);
    DEFINE_SIZE(CPU_REGS_SIZE, cpu_regs_t);
    DEFINE_SIZE(MEM_REGIONS_SIZE, mem_regions_t);
    DEFINE_OFFSET(WCB_ID, world_tcb_t, world_id);
    DEFINE_OFFSET(WCB_CTX_MEM_REG_OFF, world_tcb_t, ctx.w_mem_regions);
    DEFINE_OFFSET(WCB_CTX_VECT, world_tcb_t, ctx.vect_base_addr);
    DEFINE_OFFSET(WCB_CTX_N_IRQ_OFF, world_tcb_t, ctx.irqs_tcb.n_irqs);
    DEFINE_OFFSET(WCB_CTX_N_IRQ_OFF, world_tcb_t, ctx.irqs_tcb.n_irqs);
    DEFINE_OFFSET(WCB_CTX_N_EXT_IRQ_OFF, world_tcb_t, ctx.irqs_tcb.n_ext_irqs);
    DEFINE_OFFSET(WCB_CTX_IRQ_BASE_MIE_OFF, world_tcb_t, ctx.irqs_tcb.base_mie);
    DEFINE_OFFSET(WCB_CTX_CPU_REGS_MIE_OFF, world_tcb_t, ctx.s_regs.mie);
    DEFINE_OFFSET(WCB_CTX_IRQ_CLAIMED_PLIC_OFF, world_tcb_t, ctx.irqs_tcb.claimed_plic_int);
    DEFINE_OFFSET(WCB_CTX_IRQ_PREVIOUS_MEPC_OFF, world_tcb_t, ctx.irqs_tcb.previous_mepc);
    DEFINE_OFFSET(WCB_CTX_IRQ_PREVIOUS_MTVAL_OFF, world_tcb_t, ctx.irqs_tcb.previous_mtval);
    DEFINE_OFFSET(WCB_CTX_IRQ_PREVIOUS_MCAUSE_OFF, world_tcb_t, ctx.irqs_tcb.previous_mcause);
    DEFINE_OFFSET(WCB_CTX_IRQ_PREVIOUS_MIE_OFF, world_tcb_t, ctx.irqs_tcb.previous_mie);
    DEFINE_OFFSET(WCB_CTX_IRQ_PLIC_ENABLE, world_tcb_t, ctx.irqs_tcb.plic_enable);
    DEFINE_OFFSET(WCB_CTX_IRQ_BASE_PLIC_ENABLE, world_tcb_t, ctx.irqs_tcb.base_plic_enable);
    DEFINE_OFFSET(WCB_CTX_IRQ_PLIC_PRIORITY_OFF, world_tcb_t, ctx.irqs_tcb.plic_priority);
    DEFINE_SIZE(PLIC_IRQ_TCB_SIZE, plic_irq_tcb_t);
    DEFINE_OFFSET(WCB_CTX_VIRTUAL_MSTATUS, world_tcb_t, ctx.virtual_mstatus);
    DEFINE_OFFSET(WCB_CTX_VIRTUAL_MIE, world_tcb_t, ctx.virtual_mie);
    DEFINE_OFFSET(WCB_CTX_VIRTUAL_MTIME_CMP, world_tcb_t, ctx.virtual_mtime_cmp);
    DEFINE_OFFSET(WCB_CTX_IN_EXCEPTION, world_tcb_t, ctx.in_exception);
}

void list_defines() __attribute__((used));
void list_defines(){
    DEFINE_SIZE(TIMECMP_LIST_SIZE, world_mtimecmp_list_t);
    DEFINE_OFFSET(TIMECMP_LIST_ENABLE, world_mtimecmp_list_t, enable);
    DEFINE_OFFSET(TIMECMP_LIST_HIGH, world_mtimecmp_list_t, high);
    DEFINE_OFFSET(TIMECMP_LIST_LOW, world_mtimecmp_list_t, low);
}
