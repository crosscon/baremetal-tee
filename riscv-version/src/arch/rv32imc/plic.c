/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */

#include <utango.h>
#include <platform_irqs.h>
#include <worlds.h> 
#include <plic.h>

/**
 * \brief
 * \param
 */
void arch_irqs_ctx_init(uint32_t world_id)
{
    
    for(int i = 0; i < WCB[world_id].ctx.irqs_tcb.n_irqs; i++)
    {
        WCB[world_id].ctx.irqs_tcb.base_mie |= \
        1 << (worlds_cfg[world_id].enabled_irqs[i]);
    }

    /* Init Plic Interrupts*/

    for(int i = 0; i < WCB[world_id].ctx.irqs_tcb.n_ext_irqs; i++)
    {
        uint32_t world_ext_int_num =  worlds_cfg[world_id].enabled_ext_irqs[i];

        for(int j = 0; j < world_ext_int_num; j++)
            WCB[world_id].ctx.irqs_tcb.base_plic_enable[world_ext_int_num/32] |= \
                1 << (worlds_cfg[world_id].enabled_ext_irqs[i]);
    }
}
