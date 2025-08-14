/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */
#include <worlds.h>

/**
 * \brief 
 */
void worlds_init(void)
{
    worlds_tcbs_init();

    worlds_arch_init();

    /* Initialize rworld_ctx_ptr to world 1 ctx */
    rworld_ctx_ptr = &WCB[0];
}

/**
 * \brief
 * \param
 */
void worlds_tcbs_init(void)
{
    for(int i = 0; i < UTANGO_WORLDS; i++)
    {
        WCB[i].world_id = worlds_cfg[i].id;
        WCB[i].entry_point = worlds_cfg[i].entry_point;
        WCB[i].ctx.irqs_tcb.n_irqs = worlds_cfg[i].n_irqs;
        WCB[i].ctx.irqs_tcb.n_ext_irqs = worlds_cfg[i].n_ext_irqs;

        WCB[i].ctx.virtual_mstatus = 0x1800;

        arch_cpu_ctx_init(i);
        arch_mem_unit_ctx_init(i);
        arch_irqs_ctx_init(i);
    }
}

/**
 * \brief 
 * \param
 * TODO: solve this name spell and move to arch
 */
void worlds_arch_init(void)
{    

}
