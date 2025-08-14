/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */
#include <utango.h>

#include <systick.h>

/**
 * \brief
 * \param
 */
void system_timer_init(void) 
{
    systick_init();
}

/**
 * \brief
 * \param
 */
void system_timer_enable(void) 
{
    systick_enable();
}

/**
 * \brief
 * \param
 */
void system_timer_disable(void) 
{

}