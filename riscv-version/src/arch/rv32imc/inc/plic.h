/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */

#ifndef __PLIC_H__
#define __PLIC_H__

#include <platform_irqs.h>
#include <sys_regs.h>


#ifndef __ASSEMBLER__
#include <utango.h>

#define PLIC_MAX_IRQS 64
#define PLIC_NUM_ENABLE_REGS PLIC_MAX_IRQS/32

typedef struct plic_irq_tcb
{
     uint32_t priority;
     uint32_t offset;
}plic_irq_tcb_t;

typedef struct irqs_tcb
{
     uint32_t n_irqs;
     uint32_t base_mie;
     uint32_t n_ext_irqs;
     uint32_t plic_enable[PLIC_NUM_ENABLE_REGS];
     uint32_t base_plic_enable[PLIC_NUM_ENABLE_REGS];
     plic_irq_tcb_t plic_priority[UTANGO_MAX_PLIC_IRQS];
     uint32_t claimed_plic_int;
     uint32_t previous_mepc;
     uint32_t previous_mtval;
     uint32_t previous_mie;
     uint32_t previous_mcause;
}irqs_tcb_t;

void arch_irqs_ctx_init(uint32_t world_id);

#endif  /* |__ASSEMBLER__ */
#endif /* __NVIC_H__ */