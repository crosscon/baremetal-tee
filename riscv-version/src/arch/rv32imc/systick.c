/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */
#include <utango.h>
#include <systick.h>

uint64_t TimerIncrement = 0;

extern uint64_t timer_incr;
extern uint64_t next_mtime_cmp;

/**
 * \brief
 * \param
 */
void systick_init(void)
{
    /* Disable SysTick in MIE*/
    __disable_systick();

    /* Set reload value */
    TimerIncrement = DEFAULT_CLOCK*UTANGO_TICK - 1UL; //TODO: Make this a configurable value
    timer_incr = TimerIncrement;
}

/**
 * \brief
 * \param
 */
void systick_enable(void)
{
    /* Enable SysTick in MIE*/

    uint64_t NextTime;
    uint64_t* CurrentTimeCMP_ptr; 
    uint32_t CurrentTimeHigh, CurrentTimeLow;
    volatile uint32_t * const pulTimeHigh = ( uint32_t * ) ( MTIME_ADDR + 4UL ); /* 8-byte type so high 32-bit word is 4 bytes up. */
    volatile uint32_t * const pulTimeLow = ( uint32_t * ) ( MTIME_ADDR );

    CurrentTimeCMP_ptr = (uint64_t*)MTIMECMP_ADDR;

    CurrentTimeHigh = *pulTimeHigh;
    CurrentTimeLow = *pulTimeLow;

    NextTime = ( uint64_t ) CurrentTimeHigh;
    NextTime <<= 32ULL; /* High 4-byte word is 32-bits up. */
    NextTime |= ( uint64_t ) CurrentTimeLow;
    NextTime += ( uint64_t ) TimerIncrement;
    *CurrentTimeCMP_ptr = NextTime;

    /* Prepare the time to use after the next tick interrupt. */
    NextTime += ( uint64_t ) TimerIncrement;

    next_mtime_cmp = NextTime;

    __enable_systick();
}