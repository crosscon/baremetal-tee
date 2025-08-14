/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */

#include <utango.h>

//#define UTANGO_SIZE

#ifndef UTANGO_SIZE
/**
 * Declare WORLDS images using the WORLD_IMAGE macro, passing an identifier and 
 * the path for the image.
 */
WORLD_IMAGE(world1, ../../../worlds/world1/world1.bin);
WORLD_IMAGE(world2, ../../../worlds/world2/world2.bin);  
// WORLD_IMAGE(world3, ../../../worlds/world2/world2.bin);
//WORLD_IMAGE(world4, ../../../worlds/world2/world2.bin);
#endif

/**
 * Config each WORLD.
 */
 
world_cfg_t  worlds_cfg[UTANGO_WORLDS] =
{
    /* World 1 (Blinking Red LED) */
    {
        .id = 0,
        .vect_base_addr = 0x20410000,
        .entry_point = 0x20410042,
        .n_regions = 6,
        .w_regions = (world_regions_t[])
        {
            {   //FLASH
                .rgn_base_addr = 0x20410000,
                .rgn_size = 0x4000
            },
            {   //SRAM
                .rgn_base_addr = 0x80001000,
                .rgn_size = 0x1000
            },
            {   //SRAM
                .rgn_base_addr = 0x80003000,
                .rgn_size = 0x1000
            },
            {   //UART0
                .rgn_base_addr = 0x10013000,
                .rgn_size = 0x1000
            },
            {   //GPIO
                .rgn_base_addr = 0x10012000,
                .rgn_size = 0x1000
            },
            {   //ITIM
                .rgn_base_addr = 0x8000000,
                .rgn_size = 0x2000                
            }
        },
        .n_irqs = 2,
        .enabled_irqs = (irqs_list_t[])
        {
            MachineExternalInterrupt, 
            MachineTimerInterrupt
        },
        .n_ext_irqs = 1,
        .enabled_ext_irqs = (ext_irqs_list_t[])
        {UART0}
    },
    /* World 2 (Blinking Red LED)  */
    {
        .id = 1,
        .vect_base_addr = 0x20480000,
        .entry_point = 0x20480042,
        .n_regions = 5,
        .w_regions = (world_regions_t[])
        {
            {   //FLASH
                .rgn_base_addr = 0x20480000,
                .rgn_size = 0x40000
            },
            {   //SRAM
                .rgn_base_addr = 0x80002000,
                .rgn_size = 0x1000
            },
            {   //Shared Memory
                .rgn_base_addr = 0x80003000,
                .rgn_size = 0x1000
            },
            {   //UART1
                .rgn_base_addr = 0x10013000,
                .rgn_size = 0x1000
            },
            {   //GPIO
                .rgn_base_addr = 0x10012000,
                .rgn_size = 0x1000
            }
        },
        .n_irqs = 1,
        .enabled_irqs = (irqs_list_t[])
        {MachineExternalInterrupt},
        .n_ext_irqs = 1,
        .enabled_ext_irqs = (ext_irqs_list_t[])
        {UART0}
    },
    /* World 3 (Blinking Red LED) */
    {
        .id = 2,
        .vect_base_addr = 0x20480000,
        .entry_point = 0x20480042,
        .n_regions = 3,
        .w_regions = (world_regions_t[])
        {
            {   //FLASH
                .rgn_base_addr = 0x20480000,
                .rgn_size = 0x4000
            },
            {   //SRAM
                .rgn_base_addr = 0x80000A00,
                .rgn_size = 0x600
            },
            {   //UART1
                .rgn_base_addr = 0x10013000,
                .rgn_size = 0x1000
            }
        },
        .n_irqs = 1,
        .enabled_irqs = (irqs_list_t[])
        {MachineExternalInterrupt},
        .n_ext_irqs = 1,
        .enabled_ext_irqs = (ext_irqs_list_t[])
        {UART1} 
    },
    /* World 4 (Blinking Red LED) */
    {
        .id = 3,
        .vect_base_addr = 0x20430000,
        .entry_point = 0x20430042,
        .n_regions = 3,
        .w_regions = (world_regions_t[])
        {
            {   //FLASH
                .rgn_base_addr = 0x20430000,
                .rgn_size = 0x4000
            },
            {   //SRAM
                .rgn_base_addr = 0x80005000,
                .rgn_size = 0x1000
            },
            {   //UART1
                .rgn_base_addr = 0x10013000,
                .rgn_size = 0x1000
            }
        },
        .n_irqs = 1,
        .enabled_irqs = (irqs_list_t[])
        {MachineExternalInterrupt},
        .n_ext_irqs = 1,
        .enabled_ext_irqs = (ext_irqs_list_t[])
        {UART1}
    }
};
