/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */
#include <utango.h>
#include <sys_regs.h>
#include <cpu.h>
#include <sys_timer.h>
#include <platform_config.h>
#include <worlds.h>
#include <mem.h>
#include <dev.h>

/**
 * \brief
 * \param
 */
void init() 
{
    /* TODO: configuration of clock and power features */

    /* TODO: platform sanity */

    /** arch_cpu_init() 
     * \details 
     * Armv8m:
     * (1) Enable all fault handlers 
     * (2) Disable system reset from NS state
     * (3) Configure interrupts between states
     * (4) Configure power sleeps between states
     * RiscV:
     * (1) ...
     */
    arch_cpu_init();

    /** system_timer_init() 
     * \details 
     * (1) Call architectural system timer initialization routine
     */
    // system_timer_init();
    
    /* TODO: hw init (console, debug auth, etc) */
    //plat_init();

    /* Initialize worlds tcb's and perform some architectural initializations 
     * for first run of worlds
     */
    worlds_init();

    /** mem_unit_init()
     * \details 
     * Armv8m: configure memory space for the first world to run (SAU and 
     * platform-dependent off-chip memory bus filters)
     */
    memory_init();

    /** devices_init()
     * \details 
     * Armv8m: assign each worlds devices/peripherals to the NS side 
     * (platform-dependent off-chip peripherals bus filters)
     */
    //devices_init();

    /* Start utango */
    utango_start();

    /* Should never reach here */
    while(1);
}
