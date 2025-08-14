/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */
#ifndef __PMP_H__
#define __PMP_H__

#include <sys_regs.h>
#include <platform_config.h>

#define SET_PMP_REGION(pmpaddr_reg, pmpcfg_reg, addr, cfg) \
    asm volatile ( \
        "csrw " #pmpaddr_reg ", %0\n\t" \
        "csrs " #pmpcfg_reg ", %1" \
        : \
        : "r"(addr), "r"(cfg) \
        : "t0" \
    );

#ifndef __ASSEMBLER__

typedef struct pmp_regions
{
    uint32_t pmp_cfg;
    uint32_t pmp_addr;
}mem_regions_t[PMP_REGIONS];

void arch_mem_unit_set(uint32_t world_id);
void arch_mem_unit_enable(void);
void arch_mem_unit_disable(void);
void arch_mem_unit_ctx_init(uint32_t world_id);
void arch_set_PMP_region(uint32_t region, uint32_t addr, uint32_t cfg);

#endif  /* |__ASSEMBLER__ */
#endif /* __SAU_H__ */