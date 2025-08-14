/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */
#ifndef __CPU_H__
#define __CPU_H__

/* ==== RISC-V Memory Map ================================================== */
#define MM_CODE_R_BASE      (0x00000000)
#define MM_CODE_R_TOP       (0x1FFFFFFF)

#define MM_SRAM_R_BASE      (0x20000000)
#define MM_SRAM_R_TOP       (0x3FFFFFFF)

#define MM_PER_R_BASE       (0x40000000)
#define MM_PER_R_TOP        (0x5FFFFFFF)

#define MM_RAM_R_BASE       (0x60000000)
#define MM_RAM_R_TOP        (0x9FFFFFFF)

#define MM_DEV_R_BASE       (0xA0000000)
#define MM_DEV_R_TOP        (0xDFFFFFFF)

#ifndef __ASSEMBLER__

#include <sys_regs.h>

extern void __vtb_start(void);

void arch_cpu_init(void);
void arch_cpu_ctx_init(uint32_t world_id);
void arch_cpu_kickoff(uint32_t w1_entry_point);


__attribute__((always_inline))
static inline void __set__user_entrypoint(uint32_t w1_entry_point)
{
      asm volatile ( \
        "csrw mepc, %0\n\t" \
        "li t0, 0x80 \n\t" \
        "csrw mstatus, t0 \n\t" \
        "mret" \
        : \
        : "r"(w1_entry_point) \
        : "t0" \
    );
}

__attribute__((always_inline))
static inline void __set__utango_vtb() {
    asm volatile (
        "la t0, _utango_vtb\n\t"
        "ori t0, t0, 0x1\n\t"
        "csrw mtvec, t0"
        :
        :
        : "t0"
    );
}


/**
  \brief
 */

#endif  /* |__ASSEMBLER__ */
#endif /* __CPU_H__ */
