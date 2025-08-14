/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */
#ifndef __PLATFORM_CONFIG_H__
#define __PLATFORM_CONFIG_H__

#define DEFAULT_CLOCK   16.25 //KHz
#define PMP_REGIONS     16

#ifndef __ASSEMBLER__
#include <utango.h>

void plat_sys_reset_config(void);
void plat_init(void);
void plat_mem_config(void);
void plat_dev_config(void);

#endif  /* |__ASSEMBLER__ */
#endif /* __PLATFORM_CONFIG_H__ */
