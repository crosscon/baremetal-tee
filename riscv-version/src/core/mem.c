/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */
#include <mem.h>
#include <worlds.h>

/**
 * \brief
 * \param
 */
void memory_list_init(void)
{
    uint32_t region_id = 0;
    uint32_t min_idx;

    if(!UTANGO_WORLDS)
        goto terminator;

    /* Fill up memory list with worlds memory regions */
    for(int i=0; i < UTANGO_WORLDS; i++)
    {
        for (int j = 0; j < worlds_cfg[i].n_regions; j++)
        {
            memory_list[region_id].base_addr = worlds_cfg[i].w_regions[j].rgn_base_addr;
            memory_list[region_id].top_addr = worlds_cfg[i].w_regions[j].rgn_base_addr + \
                worlds_cfg[i].w_regions[j].rgn_size;
            region_id++;
        }
    }

    /* (Selection) Sort memory list by ascending order  */
    for(int i = 0; i < region_id - 1; i++)
    {
        min_idx = i;
        for(int j = i+1; j < region_id; j++)
            if(memory_list[j].base_addr < memory_list[min_idx].base_addr)
                min_idx = j;

        memory_region_t temp;
        temp = memory_list[min_idx];

        memory_list[min_idx] = memory_list[i];
        memory_list[i] = temp;
    }

    terminator:

    /* Mark memory list with a terminator (maximum of memory space) */
    memory_list[region_id].base_addr = 0xFFFFFFFF;
    memory_list[region_id].top_addr = 0xFFFFFFFF;
}
/**
 * \brief
 * \param
 */
void memory_check_overlapps(void)
{
    /* Init memory list by ascending order */
    memory_list_init();
    
    for(int i = 1; i < MAX_REGIONS; i++)
    {
        if(memory_list[i].base_addr == 0xFFFFFFFF)
            break;

        if((memory_list[i-1].top_addr) > memory_list[i].base_addr)
            /* Memory region overlapped */
            /* TODO: return error id */
            return; 
    }

    /* If we reach here, then no overlap */
    /* TODO: return status id */
    return;
}

/**
 * \brief
 * \param
 */
void memory_init(void)
{
    memory_check_overlapps();

    arch_mem_unit_set(0);
}

