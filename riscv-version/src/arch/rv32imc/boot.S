/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */

.section    .utango.stack, "a"
.align      4
.global     register_ctx
.type       register_ctx, %object
register_ctx:   
    .word 0,0,0,0,0
/*----------------------------------------------------------------------------*/ 
.section    .utango.boot, "ax"
.align      4
.global     reset_handler
.type       reset_handler, %function
/*----------------------------------------------------------------------------*/
reset_handler:

/* Boot Stage 2 --------------------------------------------------------------*/
_boot2_10:      /* Copy .data section to RAM */
    la      t0, __data_vma_start
    la      t1, __data_start
    la      t2, __data_end

    sub     t2, t2, t1

    beq     t1, t2, _boot2_20

_boot2_11:
    addi    t2, t2, -4
    add     t4, t2, t0 
    lw      t3, 0(t4)
    add     t4, t1, t2 
    sw      t3, 0(t4)

    bnez    t2, _boot2_11

_boot2_20:      /* Zeroize .bss section */
    la     t0, __bss_start__
    la     t1, __bss_end__

    sub t1, t1, t0

    beq     t0, t1, _boot3_10

_boot2_21:
    addi    t1, t1, -4
    add     t2, t1, t0 
    sw      x0, 0(t2)
    bnez    t1, _boot2_21

/* Boot Stage 3 --------------------------------------------------------------*/
_boot3_10:
    /* TODO: Disable interrupts? */

    /* Init sp */
    la     sp, __stack_top  #really needed??

    /* Jump to uTango init() */
    j init
    
    /* This point should never be reached */
    j       .
