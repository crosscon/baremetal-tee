/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */

/*----------------------------------------------------------------------------*/
.section .utango.vtb
.align   2
.global  _utango_vtb
/*----------------------------------------------------------------------------*/
_utango_vtb:
    j exception_handler   /*       Exception Handler                */
    .word 0                   /*       Reserved                         */
    .word 0                   /*       Reserved                         */
    j msi_handler         /*       Machine Software Interrupt       */
    .word 0                   /*       Reserved                         */
    .word 0                   /*       Reserved                         */
    .word 0                   /*       Reserved                         */
    j systick_handler     /*       Machine Timer Interrupt          */
    .word 0                   /*       Reserved                         */
    .word 0                   /*       Reserved                         */
    .word 0                   /*       Reserved                         */
    j mei_handler         /*       Machine External Interrupt       */
    .word 0                   /*       Reserved                         */
    .word 0                   /*       Reserved                         */
    .word 0                   /*       Reserved                         */
    .word 0                   /*       Reserved                         */
/* TODO: Check how to define interrupts */

.size _utango_vtb, . - _utango_vtb