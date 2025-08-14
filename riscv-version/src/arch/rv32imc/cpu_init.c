/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */

#include <utango.h>
#include <sys_regs.h>
#include <cpu.h>
#include <platform_config.h>
#include <cpu_regs.h>
#include <worlds.h> 
#include <plic.h>

/**
 * \brief 
 */
void arch_cpu_ctx_init(uint32_t world_id)
{
    /* All registers already zeroized (.bss section) */

    WCB[world_id].ctx.vect_base_addr = worlds_cfg[world_id].vect_base_addr;
    WCB[world_id].ctx.s_regs.mepc = worlds_cfg[world_id].entry_point;

}

/**
 * \brief
 * \param
 */
void arch_cpu_init(void)
{
    __set__utango_vtb();
    asm ("csrs mcounteren, 7");
}

/**
 * \brief
 * \param
 */
void arch_cpu_kickoff(uint32_t w1_entry_point)
{
    __set__user_entrypoint(w1_entry_point);
}
