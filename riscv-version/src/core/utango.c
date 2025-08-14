/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */

#include <utango.h>
#include <sys_regs.h>
#include <pmp.h>
#include <platform_regs.h>
#include <worlds.h>
#include <sys_timer.h>
#include <cpu.h>

/**
 * \brief 
 */
void utango_start(void)
{
    // system_timer_enable();

    arch_cpu_kickoff(worlds_cfg[0].entry_point);

    /* Should never reach here */
    while(1);
}
