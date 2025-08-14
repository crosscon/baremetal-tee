/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */
#ifndef __MEM_H__
#define __MEM_H__

#include <utango.h>
#include <pmp.h>
#include <platform_config.h>

#define MAX_REGIONS                         PMP_REGIONS*UTANGO_WORLDS

typedef struct memory_region
{
    uint32_t base_addr;
    uint32_t top_addr;
}memory_region_t;

memory_region_t memory_list[MAX_REGIONS];

void memory_init(void);
void memory_check_overlapps(void);
#endif /* __MEM_H__ */