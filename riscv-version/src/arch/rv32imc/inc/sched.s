/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */
#include <systick.h>
#include <sys_regs.h>
#include <asm_defs.h>
#include <config.h>
#include <pmp.h>
#include <plic.h>

.section    .utango.stack, "a"
.align      4
.global     next_mtimer_interrupt_is_world
.type       next_mtimer_interrupt_is_world, %object
next_mtimer_interrupt_is_world:   
    .word -1

.section    .utango.stack, "a"
.align      4
.global     secure_world_request
.type       secure_world_request, %object
secure_world_request:   
    .word -1

.section    .utango.stack, "a"
.align      4
.global     secure_call
.type       secure_call, %object
secure_call:   
    .word -1

.section    .utango.stack, "a"
.align      4
.global     secure_cmd
.type       secure_cmd, %object
secure_cmd:   
    .word -1

.section    .utango.stack, "a"
.align      4
.global     exit_secure_world_request
.type       exit_secure_world_request, %object
exit_secure_world_request:   
    .word -1

.section    .utango.stack, "a"
.align      4
.global     next_mtime_cmp
.type       next_mtime_cmp, %object
next_mtime_cmp:   
    .word 0,0

.section    .utango.stack, "a"
.align      4
.global     timer_incr
.type       timer_incr, %object
timer_incr:   
    .word 0,0

/**
 * \brief 
 */
.macro   STOP_SYSTICK
    /* Stop mtimer interrupt */
    csrci mie, 0x80
.endm

/**
 * \brief 
 */
.macro  SAVE_WORLD_CTX
    # saving t0 and t1, context
    csrw mscratch, t0
    la t0, register_ctx
    sw t1, 4(t0)
    csrr t1, mscratch
    sw t1, 0(t0)

    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    addi t0, t0, WCB_CTX_CPU_REGS_OFF

    /* Save context on WCB ctx.regs struct  (x1-31) */
    sw x1, 0(t0)
    sw x2, 4(t0)
    sw x3, 8(t0)
    sw x4, 12(t0)
    # t1 points to the saved registers
    la t1, register_ctx
    # reading t0 from saved context 
    lw t0, 0(t1)
    # t1 points to the struct
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    addi t1, t1, WCB_CTX_CPU_REGS_OFF
    # saving t0
    sw t0, 16(t1)
    # t0 points to the saved registers
    la t0, register_ctx
    # reading t1 from saved context 
    lw t1, 4(t0)
    # t1 points to the struct
    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    addi t0, t0, WCB_CTX_CPU_REGS_OFF
    # saving t1
    sw t1, 20(t0)
    sw x7, 24(t0)
    sw x8, 28(t0)
    sw x9, 32(t0)
    sw x10, 36(t0)
    sw x11, 40(t0)
    sw x12, 44(t0)
    sw x13, 48(t0)
    sw x14, 52(t0)
    sw x15, 56(t0)
    sw x16, 60(t0)
    sw x17, 64(t0)
    sw x18, 68(t0)
    sw x19, 72(t0)
    sw x20, 76(t0)
    sw x21, 80(t0)
    sw x22, 84(t0)
    sw x23, 88(t0)
    sw x24, 92(t0)
    sw x25, 96(t0)
    sw x26, 100(t0)
    sw x27, 104(t0)
    sw x28, 108(t0)
    sw x29, 112(t0)
    sw x30, 116(t0)
    sw x31, 120(t0)

    /* Save remaining context on WCB ctx.s_regs struct */
    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    addi t0, t0, WCB_CTX_S_REGS_OFF

    csrr t1, mstatus
    sw t1, (t0)
    csrr t1, mepc
    sw t1, 4(t0)
    csrr t1, mcause
    sw t1, 8(t0)
    csrr t1, mtval
    sw t1, 12(t0)
    csrr t1, mie
    sw t1, 16(t0)
.endm

/**
 * \brief 
 */
.macro   SAVE_PLIC
    # TODO make plic priorities modifiable aswell??

    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    addi t0, t0, WCB_CTX_IRQ_PLIC_ENABLE


    la t1, PLIC_ENABLE_ADDR     # get pointer to plic enables

    lw t2, 0(t1)        # read first word from plic enable
    sw t2, 0(t0)        # store the enable register in the context
    sw x0, 0(t1)

    lw t2, 4(t1)        # read second word from plic enable
    sw t2, 4(t0)        # store the enable register in the context
    sw x0, 0(t1)

    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    addi t0, t0, WCB_CTX_IRQ_PLIC_PRIORITY_OFF

    lw t1, 4(t0)    # offset
    slli t1, t1, 2 

    li t2, PLIC_BASE
    add t2, t2, t1      # get correct register

    lw t3, 0(t2)        # read priority
    sw t3, 0(t0)        # store priority

    addi t0, t0, PLIC_IRQ_TCB_SIZE      # piint to next interrupt

    lw t1, 4(t0)    # offset
    slli t1, t1, 2 

    li t2, PLIC_BASE
    add t2, t2, t1      # get correct register

    lw t3, 0(t2)        # read priority
    sw t3, 0(t0)        # store priority

    addi t0, t0, PLIC_IRQ_TCB_SIZE      # piint to next interrupt


    lw t1, 4(t0)    # offset
    slli t1, t1, 2 

    li t2, PLIC_BASE
    add t2, t2, t1      # get correct register

    lw t3, 0(t2)        # read priority
    sw t3, 0(t0)        # store priority

    addi t0, t0, PLIC_IRQ_TCB_SIZE      # point to next interrupt




    lw t1, 4(t0)    # offset
    slli t1, t1, 2 

    li t2, PLIC_BASE
    add t2, t2, t1      # get correct register

    lw t3, 0(t2)        # read priority
    sw t3, 0(t0)        # store priority

    # For different Implementations of the PLIC
    # lw t2, 8(t1)        # read third word from plic enable
    # sw t1, 8(t0)        # store the enable register in the context

    # lw t2, 12(t1)        # read forth word from plic enable
    # sw t1, 12(t0)        # store the enable register in the context
.endm

/**
 * \brief 
 */
.macro   SCHEDULE
    la t0, secure_world_request
    lw t0, 0(t0)
    li t1, UTANGO_WORLDS - 1
    beq t0, t1, switch_to_secure_world  # If no request, do normal scheduling

    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    lw t1, WCB_ID(t0)  # Get current world ID

    li  t3, UTANGO_WORLDS - 1 
    beq t1, t3, switch_from_secure_world   # Are we in the secure world?

normal_scheduling:
    li  t3, UTANGO_WORLDS - 2     # Last non-secure world
    beq t1, t3, reset_world_count # Last world in rotation
    li  t2, WCB_SIZE
    add t0, t0, t2              # t0 points to the next world
    la  t1, rworld_ctx_ptr
    sw  t0, 0(t1)
    j   exit_schedule

reset_world_count:
    la  t1, WCB  # Reset to first world
    la  t0, rworld_ctx_ptr
    sw  t1, 0(t0)
    j   exit_schedule  

switch_from_secure_world:
    la t4, exit_secure_world_request
    lw t4, 0(t4)
    li t5, 1
    beq t4, t5, normal_scheduling  # If exit request, do normal scheduling
    j   exit_schedule

switch_to_secure_world:

    # Switch to secure world
    la  t0, WCB
    li  t1, UTANGO_WORLDS - 1  # Secure world index
    li  t2, WCB_SIZE
    mul t1, t1, t2
    add t0, t0, t1  # t0 now points to secure world context
    la  t1, rworld_ctx_ptr
    sw  t0, 0(t1)

exit_schedule:
.endm

/**
 * \brief 
 */
.equ CSR_PMPCFG0,   0x3A0
.equ CSR_PMPADDR0,  0x3B0

.macro   PMP_SET
    /* Read SAU configuration from the world to resume TCB */
    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    addi t0, t0, WCB_CTX_MEM_REG_OFF
    
    /* Clear all regions config */
    csrw pmpcfg0, x0
    csrw pmpcfg1, x0
    csrw pmpcfg2, x0
    csrw pmpcfg3, x0

    .option push
    .option norvc
    .set _idx, 0
    .rept 16
        # Load and write pmpcfgX
        lw      t1, 0(t0)
        csrs    CSR_PMPCFG0 + ((_idx) / 4), t1

        # Load and write pmpaddrX
        lw      t1, 4(t0)
        csrw    CSR_PMPADDR0 + _idx, t1

        # Move to next region data
        addi    t0, t0, 8
        .set _idx, _idx + 1
    .endr
    .option pop

.endm

/**
 * \brief 
 */
.macro   RESTORE_PLIC

    #####################################################################
    #####################################################################
    #####################################################################

    # check if mstatus.mie is enabled for the world

    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    andi t1, t1, MSTATUS_MIE
    # skip writing plic enable registers if mstatus.mie is disabled
    bne t1, x0, 1f

    la t0, PLIC_ENABLE_ADDR
    sw x0, 0(t0)    # clearing PLIC enable register 0
    sw x0, 4(t0)    # clearing PLIC enable register 1
    j 2f

    1:
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    addi t1, t1, WCB_CTX_IRQ_PLIC_ENABLE      # get pointer to WCB

    la t0, PLIC_ENABLE_ADDR     # get pointer to PLIC ENABLE

    lw t2, 0(t1)        # read first word from the context
    sw t2, 0(t0)        # store the enable register in the plic

    lw t2, 4(t1)        # read second word from the context
    sw t2, 4(t0)        # store the enable register in the plic


    # Restore priority

    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    addi t0, t0, WCB_CTX_IRQ_PLIC_PRIORITY_OFF

    lw t1, 4(t0)    # offset
    slli t1, t1, 2 

    li t2, PLIC_BASE
    add t2, t2, t1      # get correct register

    lw t3, 0(t0)        # read priority
    sw t3, 0(t2)        # store priority

    addi t0, t0, PLIC_IRQ_TCB_SIZE      # piint to next interrupt


    lw t1, 4(t0)    # offset
    slli t1, t1, 2 

    li t2, PLIC_BASE
    add t2, t2, t1      # get correct register

    lw t3, 0(t0)        # read priority
    sw t3, 0(t2)        # store priority

    addi t0, t0, PLIC_IRQ_TCB_SIZE      # piint to next interrupt

    lw t1, 4(t0)    # offset
    slli t1, t1, 2 

    li t2, PLIC_BASE
    add t2, t2, t1      # get correct register

    lw t3, 0(t0)        # read priority
    sw t3, 0(t2)        # store priority

    addi t0, t0, PLIC_IRQ_TCB_SIZE      # piint to next interrupt

    lw t1, 4(t0)    # offset
    slli t1, t1, 2 

    li t2, PLIC_BASE
    add t2, t2, t1      # get correct register

    lw t3, 0(t0)        # read priority
    sw t3, 0(t2)        # store priority

    # For different Implementations of the PLIC
    # lw t2, 8(t1)        # read third word from the context
    # sw t1, 8(t0)        # store the enable register in the plic

    # lw t2, 12(t1)        # read forth word from the context
    # sw t1, 12(t0)        # store the enable register in the plic

    2:
   
.endm

/**
 * \brief
 */
.macro   RESTORE_WORLD_CTX
    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    addi t0, t0, WCB_CTX_CPU_REGS_OFF

    /* Restore context on WCB ctx.regs struct  (x1-31) */
    lw x1, 0(t0)
    lw x2, 4(t0)
    lw x3, 8(t0)
    lw x4, 12(t0)
    lw x5, 16(t0)       # t0
    # using t3 to point to the struct before reading t3
    la t3, rworld_ctx_ptr
    lw t3, 0(t3)
    addi t3, t3, WCB_CTX_CPU_REGS_OFF
    lw x6, 20(t3)       # t1       
    # save t0 and t1 to register context struct
    SAVE_TEMP
    # restoring t0 as the pointer to the struct
    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    addi t0, t0, WCB_CTX_CPU_REGS_OFF

    lw x7, 24(t0)       
    lw x8, 28(t0)
    lw x9, 32(t0)
    lw x10, 36(t0)
    lw x11, 40(t0)
    lw x12, 44(t0)
    lw x13, 48(t0)
    lw x14, 52(t0)
    lw x15, 56(t0)
    lw x16, 60(t0)
    lw x17, 64(t0)
    lw x18, 68(t0)
    lw x19, 72(t0)
    lw x20, 76(t0)
    lw x21, 80(t0)
    lw x22, 84(t0)
    lw x23, 88(t0)
    lw x24, 92(t0)
    lw x25, 96(t0)
    lw x26, 100(t0)
    lw x27, 104(t0)
    lw x28, 108(t0)
    lw x29, 112(t0)
    lw x30, 116(t0)
    lw x31, 120(t0)

    /* Restoring remaining context on WCB ctx.s_regs struct */
    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    addi t0, t0, WCB_CTX_S_REGS_OFF

    lw t1, (t0)
    /////// debug
    ori t1, t1, 0x80
    ///////
    csrw mstatus, t1
    lw t1, 4(t0)
    csrw mepc, t1
    lw t1, 8(t0)
    csrw mcause, t1
    lw t1, 12(t0)
    csrw mtval, t1

    ###############################################################

    # check if virtual mstatus.mie is enabled

    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # andi t1, t1, MSTATUS_MIE
    # # skip writing mie if mstatus.mie is disabled
    # beq t1, x0, 1f

    #lw t1, 16(t0)
    #ori t1, t1, 0x80
    #csrw mie, t1
    j 2f

    1:
    li t1, 0x80
    csrw mie, t1

    2:
    # restore t0 and t1
    # RESTORE_TEMP
.endm

/**
 * \brief 
 */
.macro SYSTICK_UPDATE_MTIMER_CMP

    # Update MTIMER_CMP
    la t0, MTIMECMP_ADDR
    # reading the mtime_cmp low regiter
    lw t1, 0(t0)

    # Reading the low timer_incr
    la t0, timer_incr
    lw t0, 0(t0)
    # adding the low next_timer_cmp with the low increment    
    add t0, t0, t1      
    # checking if the additon overflowed
    bltu t0, t1, 1f
    csrwi mscratch, 0
    j 2f
    # overflow
    1:
    csrwi mscratch, 1

    #overflow
    # store updated low next mtimer cmp 
    2:
    la t1, MTIMECMP_ADDR
    sw t0, 0(t1)
    la t1, next_mtime_cmp
    sw t0, 0(t1)

    ###################################################################
    ###################################################################

    # Reading the high next_mtime_cmp
    la t0, MTIMECMP_ADDR
    lw t1, 4(t0)

    # Reading the high timer_incr
    la t0, timer_incr
    lw t0, 4(t0)
    # adding the high next_timer_cmp with the high increment    
    add t0, t0, t1

    # adding carry
    csrr t1, mscratch
    add t1, t0, t1

    # updating the register with the next value
    li t0, MTIMECMP_ADDR
    sw t1, 4(t0)
    la t0, next_mtime_cmp
    sw t1, 4(t0)

.endm

.macro UPDATE_MTIMER_CMP_FROM_LIST      # mscratch must have world id
    #save mscratch 
    la t0, register_ctx
    csrr t1, mscratch
    sw t1, 16(t0)

    csrr t0, mscratch
    li t1, TIMECMP_LIST_SIZE
    mul t0, t1, t0
    la t1, mtimecmp_list
    add t0, t0, t1         # t0 now points to the currect struct
    csrw mscratch, t0

    # check if diferent from 0
    lw t1, TIMECMP_LIST_LOW(t0)
    lw t0, TIMECMP_LIST_HIGH(t0)
    add t0, t0, t1
    bnez t0,1000f  # write the values
    beqz t1, 2000f # skip writing the values

    1000:
    # writing the low reg
    csrr t0, mscratch
    lw t0, TIMECMP_LIST_LOW(t0)            # t0 has the low reg from the list
    li t1, MTIMECMP_ADDR
    sw t0, 0(t1)

    # writing the high reg
    csrr t0, mscratch
    lw t1, 4(t0)            # t0 has the high reg from the list
    li t0, MTIMECMP_ADDR
    sw t0, 4(t1)

    2000:
    # restore mscratch
    la t0, register_ctx
    lw t1, 16(t0)
    csrw mscratch, t1

.endm 

.macro PROCESS_NEXT_TIMER_INTERRUPT
    # Initialize loop counter t0 = 0    
    li t0, 0                  # Initialize loop counter t0 = 0
    li t1, UTANGO_WORLDS - 1  # Exclude the secure world from normal scheduling
    csrw mscratch, t0         # storing the index

    # main loop body
    1:
    csrr t0, mscratch         # reading the index
    li t1, UTANGO_WORLDS - 1  # Exclude the secure world
    bge t0, t1, 3f            # Exit loop if t0 >= UTANGO_WORLDS - 1

        # Save mscratch
        la t0, register_ctx
        csrr t1, mscratch
        sw t1, 12(t0)

        li t0, TIMECMP_LIST_SIZE
        mul t1, t1, t0
        la t0, mtimecmp_list
        add t0, t0, t1
        csrw mscratch, t0

        # Search the list for enabled timer interrupts
        CHECK_IF_NEW_MTIMECMP_HAPPENS_FIRST_FROM_LIST
        bnez t0, 2f 

        # Restore mscratch
        la t0, register_ctx
        lw t1, 12(t0)
        csrw mscratch, t1

        # Updating the next_interrupt identifier **(but not to secure world)**
        csrr t0, mscratch
        la t1, next_mtimer_interrupt_is_world
        sw t0, 0(t1)

        # gets here if systick happens_first and shouldnt update mtimer_cmp
        2:
        # Restore mscratch
        la t0, register_ctx
        lw t1, 12(t0)
        csrw mscratch, t1
        
        # Increment loop counter
        csrr t0, mscratch
        addi t0, t0, 1      # t0 = t0 + 1
        csrw mscratch, t0
        # Jump back to the start of the loop
        j 1b
    
    # Loop end
    3:
.endm

.macro CHECK_IF_NEW_MTIMECMP_HAPPENS_FIRST_FROM_LIST        # mscratch must point to a list_member
    # Check if the new mtimecmp will trigger before the systick
    # get the high cmp value for comparison
    csrr t1, mscratch
    li t0, 1    # default means it is not before the systick
    addi t1, t1, TIMECMP_LIST_ENABLE
    lw t1, 0(t1)
    beqz t1, 200f   # jump if not enabled

    ###################################################
    ############### get here if enabled ###############
    ###################################################
    # get the high value from the list
    csrr t1, mscratch
    addi t1, t1, TIMECMP_LIST_HIGH
    lw t1, 0(t1)
    # get the next_timecmp high value
    la t0, next_mtime_cmp
    lw t0, 4(t0)
    bgtu t1, t0, 100f  # jump if it is before systick

    # get the low cmp value for comparison
    csrr t1, mscratch
    addi t1, t1, TIMECMP_LIST_LOW
    lw t1, 0(t1)

    # get the next_timecmp low value
    la t0, next_mtime_cmp
    lw t0, 0(t0)

    bgtu t1, t0, 100f

    # execute this part if it should update mtimercmp
    li t0, 0
    j 200f

    100:
    # execute this part if it shouldt update mtimercmp
    li t0, 1

    200:
.endm