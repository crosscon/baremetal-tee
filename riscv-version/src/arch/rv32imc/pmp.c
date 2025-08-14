/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */
#include <utango.h>
#include <pmp.h>
#include <config.h>
#include <cpu.h>
#include <worlds.h>

/**
 * \brief
 * \param
 */
void arch_mem_unit_set(uint32_t world_id)
{    
    for(int i=0; i<worlds_cfg[world_id].n_regions; i++)
    {
        arch_set_PMP_region(i, WCB[world_id].ctx.w_mem_regions[i].pmp_addr, WCB[world_id].ctx.w_mem_regions[i].pmp_cfg);
    }
}

/**
 * \brief
 * \param
 */
void arch_mem_unit_ctx_init(uint32_t world_id)
{
    unsigned long size, addrmask, pmpaddr, addr;

    for(int i = 0; i < worlds_cfg[world_id].n_regions; i++)
    {
        addr = worlds_cfg[world_id].w_regions[i].rgn_base_addr;
        size = worlds_cfg[world_id].w_regions[i].rgn_size;

        /* encode PMP address */
        pmpaddr = (addr >> 2) + ((size >> 3) - 1);

        WCB[world_id].ctx.w_mem_regions[i].pmp_addr = pmpaddr;
        
        WCB[world_id].ctx.w_mem_regions[i].pmp_cfg = 0x01F << (0x8 * (i%4));
    }
}

void arch_set_PMP_region(uint32_t region, uint32_t addr, uint32_t cfg)
{
    switch (region)
    {
    case 0:
        SET_PMP_REGION(pmpaddr0, pmpcfg0, addr, cfg);
        break;
    case 1:
        SET_PMP_REGION(pmpaddr1, pmpcfg0, addr, cfg)
        break;
    case 2:
        SET_PMP_REGION(pmpaddr2, pmpcfg0, addr, cfg)
        break;
    case 3:
        SET_PMP_REGION(pmpaddr3, pmpcfg0, addr, cfg)
        break;
    case 4:
        SET_PMP_REGION(pmpaddr4, pmpcfg1, addr, cfg)
        break;
    case 5:
        SET_PMP_REGION(pmpaddr5, pmpcfg1, addr, cfg)
        break;
    case 6:
        SET_PMP_REGION(pmpaddr6, pmpcfg1, addr, cfg)
        break;
    case 7:
        SET_PMP_REGION(pmpaddr7, pmpcfg1, addr, cfg)
        break;
    case 8:
        SET_PMP_REGION(pmpaddr8, pmpcfg2, addr, cfg)
        break;
    case 9:
        SET_PMP_REGION(pmpaddr9, pmpcfg2, addr, cfg)
        break;
    case 10:
        SET_PMP_REGION(pmpaddr10, pmpcfg2, addr, cfg)
        break;
    case 11:
        SET_PMP_REGION(pmpaddr11, pmpcfg2, addr, cfg)
        break;
    case 12:
        SET_PMP_REGION(pmpaddr12, pmpcfg3, addr, cfg)
        break;
    case 13:
        SET_PMP_REGION(pmpaddr13, pmpcfg3, addr, cfg)
        break;
    case 14:
        SET_PMP_REGION(pmpaddr14, pmpcfg3, addr, cfg)
        break;
    case 15:
        SET_PMP_REGION(pmpaddr15, pmpcfg3, addr, cfg)
        break;
   
    default:
        break;
    }
}