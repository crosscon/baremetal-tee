/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#define UTANGO_TICK         10 /*ms*/
#define UTANGO_WORLDS       2
#define UTANGO_MAX_IRQS     4   /* per world (to optimize size of irq TCB ) */
#define UTANGO_MAX_PLIC_IRQS     4   /* per world (to optimize size of irq TCB ) */

#ifndef __ASSEMBLER__
#include <utango.h>
#include <platform_irqs.h>

#define WORLD_IMAGE(world_name, image)                       \
    extern uint32_t _ ##world_name## _size;                  \
    extern uint32_t _ ##world_name## _start;                 \
    asm(                                                     \
        ".section ." #world_name ", \"ax\"              \n\t"\
        ".global _" #world_name "_start                 \n\t"\
        "_" #world_name "_start:                        \n\t"\
        ".incbin \"" #image "\"                         \n\t"\
        "_" #world_name "_end:                          \n\t"\
        ".global _" #world_name "_size                  \n\t"\
        ".set _" #world_name "_size, (                       \
        _" #world_name "_end - _" #world_name "_start) \n\t");

typedef struct world_regions
{
    uint32_t rgn_base_addr;
    uint32_t rgn_size;
} world_regions_t;

typedef struct world_cfg
{
    uint32_t id;
    uint32_t vect_base_addr;
    uint32_t entry_point;
    uint32_t n_regions;
    world_regions_t *w_regions;
    uint32_t n_irqs;
    irqs_list_t *enabled_irqs;
    uint32_t n_ext_irqs;
    ext_irqs_list_t *enabled_ext_irqs;
} world_cfg_t;

extern world_cfg_t worlds_cfg[];
#endif  /* |__ASSEMBLER__ */

#endif /* __CONFIG_H__ */
