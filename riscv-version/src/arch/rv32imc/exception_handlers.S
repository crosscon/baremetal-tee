/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */

#include <sched.s>

.macro SAVE_TEMP
    csrw mscratch, t0
    la t0, register_ctx
    sw t1, 4(t0)
    csrr t1, mscratch
    sw t1, 0(t0)
.endm

.macro RESTORE_TEMP
    la t0, register_ctx
    lw t1, 4(t0)   
    lw t0, 0(t0)
.endm

.macro CHECK_C_INST inst
    andi \inst, \inst, 0x3          #focus on the 2 LSb
    addi \inst, \inst, 0xFFFFFFFD   # \inst is 0 if regular, and !=0 if compressed
.endm

.macro MASK_INST_OP inst
    andi \inst, \inst, 0x7f
.endm

.macro MASK_SYSTEM_INST_FUNC inst
    srli \inst, \inst, 0xc
    andi \inst, \inst, 0x7
.endm

.macro MASK_CSR_REG inst
    srli \inst, \inst, 0x14
.endm

.macro MASK_CSR_DEST inst
    srli \inst, \inst, 0x7
    andi \inst, \inst, 0x1F
.endm

.macro MASK_C_LOAD_DEST inst
    srli \inst, \inst, 0x2
    andi \inst, \inst, 0x7
    addi \inst, \inst, 0x8
.endm

.macro MASK_I_LOAD_DEST inst
    srli \inst, \inst, 0x7
    andi \inst, \inst, 0x1F
.endm

.macro MASK_CSR_SOURCE inst
    srli \inst, \inst, 0xF
    andi \inst, \inst, 0x1F
.endm

.macro CS_TYPE_MASK_SOURCE inst
    srli \inst, \inst, 0x2
    andi \inst, \inst, 0x7
    addi \inst, \inst, 8
.endm

.macro CHECK_IF_NEW_MTIMECMP_HAPPENS_FIRST      # returns t0
    # Check if the new mtimecmp will trigger before the systick
    # get the high cmp value for comparison
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    addi t1, t1, WCB_CTX_VIRTUAL_MTIME_CMP + 4
    lw t1, 0(t1)

    # get the next_timecmp high value
    la t0, MTIMECMP_ADDR
    lw t0, 4(t0)

    bgt t1, t0, 100f

    # get the low cmp value for comparison
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    addi t1, t1, WCB_CTX_VIRTUAL_MTIME_CMP
    lw t1, 0(t1)

    # get the next_timecmp high value
    la t0, MTIMECMP_ADDR
    lw t0, 0(t0)

    bgtu t1, t0, 100f
    li t0, 0
    j 200f

    100:
    li t0, 1

    200:
.endm

.section    .text
/*----------------------------------------------------------------------------*/ 
.align      4
.global     exception_handler
.type       exception_handler, %function
/*----------------------------------------------------------------------------*/
exception_handler:
    SAVE_TEMP

    csrr t1, mcause
	li t0, 5
	beq t1, t0, load_fault_handler
	li t0, 7
	beq t1, t0, store_fault_handler 
	li t0, 8
	beq t1, t0, ecall_handler
	li t0, 2
	beq t1, t0, illegal_instruction_handler
	j world_exception_handler
    .size exception_handler, . - exception_handler

load_fault_handler:
	csrr t1, mtval
	li t0, PLIC_CLAIM_ADDR
	beq t0, t1, user_claim_plic
    li t0, PLIC_PENDING_ADDR
	beq t0, t1, user_pending_plic_load
    addi t0, t0, 4                          // to address both registers
	beq t0, t1, user_pending_plic_load
    li t0, MTIME_ADDR
	beq t0, t1, user_transparent_load
    addi t0, t0, 4                          // to address both registers
	beq t0, t1, user_transparent_load
    li t0, MTIMECMP_ADDR
	beq t0, t1, user_mtimecmp_load
    addi t0, t0, 4                          // to address both registers
	beq t0, t1, user_mtimecmp_load + 4
	j world_exception_handler
    .size load_fault_handler, . - load_fault_handler

user_mtimecmp_load:
    ###################################################################
    ###################################################################

    # is low register
    j 1f

    # is high register
    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    lw t0, WCB_CTX_VIRTUAL_MTIME_CMP(t0)
    j 2f    

    1:
    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    addi t0, t0, 4
    lw t0, WCB_CTX_VIRTUAL_MTIME_CMP(t0)

    ###################################################################
    ###################################################################

    # Check for misaligned addresses 
    2:
    csrr t1, mepc
    # check if misaligned
    andi t1, t1, 0x3
    beqz t1, 1f     # is aligned
    csrr t1, mepc
    andi t1, t1, 0xFFFFFFFC
    lw t0, 0(t1)        # get both instructions
    srli t0, t0, 0x10   # isolate the desired instruction
    j 2f

    ###################################################################
    ###################################################################

    # get the register to write to
    1:
    csrr t1, mepc
    lw t0, 0(t1)        # get the instruction to start decoding
    2:

    la t1, register_ctx
    sw t0, 12(t1)       # storing the instruction 

    CHECK_C_INST t0

    beqz t0, 1f     # is regular
    # is compressed
    la t1, register_ctx
    lw t0, 12(t1)       # reading the instruction 
    MASK_C_LOAD_DEST t0   # get the destination register
    j 2f


    1:
    la t1, register_ctx
    lw t0, 12(t1)       # reading the instruction 
    MASK_I_LOAD_DEST t0   # get the destination register

    2:
    slli t0, t0, 3      # multiplie the register by 8add
    la t1, mscratch_to_register_jump_table
    add t0, t1, t0
    la t1, return_from_trap_and_emul
    jalr x0, t0, 0

user_transparent_load:
    ###################################################################
    ###################################################################

    csrr t0, mtval
    lw t0, 0(t0)
    csrw mscratch, t0   # mscracth holds the value in the the mtime register

    ###################################################################
    ###################################################################

    # Check for misaligned addresses 

    csrr t1, mepc
    # check if misaligned
    andi t1, t1, 0x3
    beqz t1, 1f     # is aligned
    csrr t1, mepc
    andi t1, t1, 0xFFFFFFFC
    lw t0, 0(t1)        # get both instructions
    srli t0, t0, 0x10   # isolate the desired instruction
    j 2f

    ###################################################################
    ###################################################################

    # get the register to write to

    1:
    csrr t1, mepc
    lw t0, 0(t1)        # get the instruction to start decoding
    2:

    la t1, register_ctx
    sw t0, 12(t1)       # storing the instruction 

    CHECK_C_INST t0

    beqz t0, 1f     # is regular

    la t1, register_ctx
    lw t0, 12(t1)       # reading the instruction 
    MASK_C_LOAD_DEST t0   # get the destination register
    j 2f


    1:
    la t1, register_ctx
    lw t0, 12(t1)       # reading the instruction 
    MASK_I_LOAD_DEST t0   # get the destination register

    2:
    slli t0, t0, 3      # multiplie the register by 8add
    la t1, mscratch_to_register_jump_table
    add t0, t1, t0
    la t1, return_from_trap_and_emul
    jalr x0, t0, 0

user_pending_plic_load:
    ###################################################################
    ###################################################################

    csrr t0, mtval
    lw t0, 0(t0)
    csrw mscratch, t0   # mscracth holds the value in the the pending register

    ###################################################################
    ###################################################################

    # check which register the world is trying to read from 
    
    csrr t0, mtval
    la t1, PLIC_PENDING_ADDR
    sub t0, t0, t1      # t0 holds the register || 0 for register 0 or 4 for register 1

    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    // t1 points to the WCB
    addi t1, t1, WCB_CTX_IRQ_BASE_PLIC_ENABLE
    // t1 points to the first base plica enable
    add t1, t1, t0
    // t1 points to the correct base plic enable resgister
    lw t1, WCB_CTX_IRQ_BASE_PLIC_ENABLE(t1)

    // mask the interrupts pending
    csrr t0, mscratch
    and t0, t0, t1      # to only allow configured enables

    csrw mscratch, t0

    // mscratch holds the value to be writen to the dest register

    ###################################################################
    ###################################################################

    # Check for misaligned addresses 

    csrr t1, mepc
    # check if misaligned
    andi t1, t1, 0x3
    beqz t1, 1f     # is aligned
    csrr t1, mepc
    andi t1, t1, 0xFFFFFFFC
    lw t0, 0(t1)        # get both instructions
    srli t0, t0, 0x10   # isolate the desired instruction
    j 2f

    ###################################################################
    ###################################################################

    # get the register to write to

    1:
    csrr t1, mepc
    lw t0, 0(t1)        # get the instruction to start decoding
    2:

    la t1, register_ctx
    sw t0, 12(t1)       # storing the instruction

    CHECK_C_INST t0
    beqz t0, 1f     # is regular


    la t1, register_ctx
    sw t0, 12(t1)       # reading the instruction
    MASK_C_LOAD_DEST t0   # get the destination register
    j 2f

    1:
    la t1, register_ctx
    sw t0, 12(t1)       # reading the instruction
    MASK_I_LOAD_DEST t0   # get the destination register

    2:
    slli t0, t0, 3      # multiplie the register by 8add
    la t1, mscratch_to_register_jump_table
    add t0, t1, t0
    la t1, return_from_trap_and_emul
    jalr x0, t0, 0

user_claim_plic:
    ######################################################
    # Ge the instruction to start decoding
    csrr t0, mepc

    # check if misaligned
    andi t0, t0, 0x3
    beqz t0, 1f     # is aligned
    csrr t0, mepc
    andi t0, t0, 0xFFFFFFFC
    lw t0, 0(t0)        # get both instructions
    srli t0, t0, 0x10   # isolate the desired instruction
    j 2f

    1:
    csrr t1, mepc
    lw t0, 0(t1)        # get the instruction to start decoding
    2:

    csrw mscratch, t0

    CHECK_C_INST t0
    beqz t0, 1f     # is regular

    ######################################################
    # t0 holds the instruction, ready decode the 
    # destination register
    
    csrr t0, mscratch
    MASK_C_LOAD_DEST t0   # get the destination register
    j 2f

    1: 
    csrr t0, mscratch
    MASK_I_LOAD_DEST t0   # get the destination register

    2:
    slli t0, t0, 3                          # times 8 the register number 

    ######################################################
    # Get the value from the WCB and writes it to mscratch
	la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_IRQ_CLAIMED_PLIC_OFF(t1)
    csrw mscratch, t1

    la t1, mscratch_to_register_jump_table
    add t0, t0, t1 
    la t1, return_from_trap_and_emul
    jalr x0, t0, 0

store_fault_handler:
	csrr t1, mtval
	li t0, PLIC_CLAIM_ADDR
	beq t0, t1, user_complete_plic
	li t0, PLIC_ENABLE_ADDR
    beq t0, t1, user_write_plic_enable
    addi t0, t0, 4
    beq t0, t1, user_write_plic_enable
    li t0, MTIMECMP_ADDR
    beq t0, t1, user_write_mtimer_cmp
    addi t0, t0, 4
    beq t0, t1, user_write_mtimer_cmp
    li t0, PLIC_BASE
    blt t1, t0, 1f      
    li t0, PLIC_PRIORITY_LIMIT
    bgt t1, t0, 1f
    j user_write_plic_priority

    1:
    j world_exception_handler
    .size store_fault_handler, . - store_fault_handler

user_write_mtimer_cmp:
    ###################################################################
    ###################################################################

    # Check for misaligned addresses 

    csrr t1, mepc
    # check if misaligned
    andi t1, t1, 0x3
    beqz t1, 1f     # is aligned
    csrr t1, mepc
    andi t1, t1, 0xFFFFFFFC
    lw t0, 0(t1)        # get both instructions
    srli t0, t0, 0x10   # isolate the desired instruction
    j 2f

    ###################################################################
    ###################################################################

    # get the value to be written

    1:
    csrr t1, mepc
    lw t0, 0(t1)        # get the instruction to start decoding
    2:

    CS_TYPE_MASK_SOURCE t0   # get the source register

    slli t0, t0, 3      # multiplie the register by 8
    la t1, register_to_register_jump_table
    add t0, t1, t0
    la t1, 1f
    jalr x0, t0, 0
    # t0 now holds the value to write to the plic enable register

    1: 
    csrw mscratch, t0

    ###################################################################
    ###################################################################

    # check which register the world is trying to write to 
    
    csrr t0, mtval
    la t1, MTIMECMP_ADDR
    sub t0, t0, t1      # t0 holds the register || 0 for low register or 4 for high register
    
    ###################################################################
    ###################################################################
    
    # write to the WCB virtual mtime_cmp

    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    addi t1, t1, WCB_CTX_VIRTUAL_MTIME_CMP
    add t1, t1, t0      # now t1 point to the currect high or low register

    csrr t0, mscratch
    sw t0, 0(t1)        # storing the value in WCB

    ###################################################################
    # write the value to the mtimecmp_list
    ###################################################################
    # check which register the world is trying to write to 
    csrr t0, mtval
    la t1, MTIMECMP_ADDR
    sub t0, t0, t1      # t0 holds the register || 0 for low register or 4 for high register

    beqz t0, 1f         # jump if is low
    # is high
    # get world id to index the list
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)   
    lw t0, WCB_ID(t1)
    # get a pointer to the list
    li t1, TIMECMP_LIST_SIZE
    mul t0, t1, t0

    la t1, mtimecmp_list
    add t1, t1, t0          # t1 points to the correct struct in the list
    addi t1, t1, TIMECMP_LIST_HIGH

    csrr t0, mscratch
    sw t0, 0(t1)

    j 2f

    # is low
    1:
    # get world id to index the list
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)   
    lw t0, WCB_ID(t1)
    # get a pointer to the list
    li t1, TIMECMP_LIST_SIZE
    mul t0, t1, t0

    la t1, mtimecmp_list
    add t1, t1, t0          # t1 points to the correct struct in the list
    addi t1, t1, TIMECMP_LIST_LOW

    csrr t0, mscratch
    sw t0, 0(t1)

    2:
    ###################################################################
    ###################################################################
    ######### Do the right management of the systick variables ########
    ###################################################################
    ###################################################################
    
    # (WRONG) get here if the new value is less than the next_timecmp   
    # (WRONG) meaning that this interrupt occurs before the systick     
    # check if mstatus.mie is active
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    andi t1, t1, MSTATUS_MIE
    beqz t1, 3f     # jump if mie is not enabled

    #save mscratch 
    la t0, register_ctx
    csrr t1, mscratch
    sw t1, 12(t0)

    # check if mie.mtimer_interrupt is active
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MIE(t1)
    andi t1, t1, MIE_MTIMER_INTERRUPT
    beqz t1, 3f     # jump if mie is not enabled

    la t1, rworld_ctx_ptr
    lw t1, 0(t1)   
    lw t0, WCB_ID(t1)
    csrw mscratch, t0

    # updating the next_interrupt identyfier
    csrr t0, mscratch
    la t1, next_mtimer_interrupt_is_world
    sw t0, 0(t1)
    
    #update mtiemr_list_enable
    # get world id to index the list
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)   
    lw t0, WCB_ID(t1)
    # get a pointer to the list
    li t1, TIMECMP_LIST_SIZE
    mul t0, t1, t0
    
    la t1, mtimecmp_list
    add t1, t1, t0          # t1 points to the correct struct in the list
    li t0, 1
    sw t0, TIMECMP_LIST_ENABLE(t1)

    CHECK_IF_NEW_MTIMECMP_HAPPENS_FIRST
    bnez t0, 3f
    
    UPDATE_MTIMER_CMP_FROM_LIST

    # get here if the new value is greater than the next_timecmp
    # meaning that this interrupt occurs after the systick
    3:
    j return_from_trap_and_emul

user_write_plic_priority:
    csrr t1, mepc
    # check if misaligned
    andi t1, t1, 0x3
    beqz t1, 1f     # is aligned
    csrr t1, mepc
    andi t1, t1, 0xFFFFFFFC
    lw t0, 0(t1)        # get both instructions
    srli t0, t0, 0x10   # isolate the desired instruction
    j 2f

    1:
    csrr t1, mepc
    lw t0, 0(t1)        # get the instruction to start decoding
    2:

    CS_TYPE_MASK_SOURCE t0   # get the source register

    slli t0, t0, 3      # multiply the register by 8
    la t1, register_to_register_jump_table
    add t0, t1, t0
    la t1, 1f
    jalr x0, t0, 0
    # t0 now holds the value to write to the plic priority register

    1:
    csrr t1, mtval

    sw t0, 0(t1)

    j return_from_trap_and_emul

user_write_plic_enable:

    ###################################################################
    ###################################################################

    # Check for misaligned addresses 

    csrr t1, mepc
    # check if misaligned
    andi t1, t1, 0x3
    beqz t1, 1f     # is aligned
    csrr t1, mepc
    andi t1, t1, 0xFFFFFFFC
    lw t0, 0(t1)        # get both instructions
    srli t0, t0, 0x10   # isolate the desired instruction
    j 2f

    ###################################################################
    ###################################################################

    # get the value to be written

    1:
    csrr t1, mepc
    lw t0, 0(t1)        # get the instruction to start decoding
    2:

    CS_TYPE_MASK_SOURCE t0   # get the source register

    slli t0, t0, 3      # multiplie the register by 8
    la t1, register_to_register_jump_table
    add t0, t1, t0
    la t1, 1f
    jalr x0, t0, 0

    # t0 now holds the value to write to the plic enable register

    ###################################################################
    ###################################################################

    # mask the value to be written

    1: 
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_IRQ_BASE_PLIC_ENABLE(t1)

    and t0, t0, t1      # to only allow configured enables
    csrw mscratch, t0   # t0 holds the value to write to the register

    ###################################################################
    ###################################################################

    # check which register the world is trying to write to 
    
    csrr t0, mtval
    la t1, PLIC_ENABLE_ADDR
    sub t0, t0, t1      # t0 holds the register || 0 for register 0 or 4 for register 1
    
    ###################################################################
    ###################################################################
    
    # write to the WCB plic enable registers

    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    addi t1, t1, WCB_CTX_IRQ_PLIC_ENABLE
    add t1, t1, t0      # now t1 point to the currect "virtual plic" register

    csrr t0, mscratch
    sw t0, 0(t1)        # storing the value in WCB
    
    ###################################################################
    ###################################################################    

    # check if mstatus.mie is enabled, if so, write to plic enable register, else wcb registers are enough
    
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    andi t1, t1, MSTATUS_MIE
    # skip writing plic enable register if mstatus.mie is disabled
    beq t1, x0, 1f

    sw t0, 0(t1)    # write to the plic enable register
    1:
    j return_from_trap_and_emul

user_complete_plic:
	la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    lw t1, WCB_CTX_IRQ_CLAIMED_PLIC_OFF(t0)
    beqz t1, world_exception_handler    ### IF NO INTERRUPT WAS CLAIMED
    li t0, PLIC_CLAIM_ADDR
    sw t1, 0(t0)
    sw x0, WCB_CTX_IRQ_CLAIMED_PLIC_OFF(t0)
	j return_from_trap_and_emul

ecall_handler:
    mv t0, a7    # Read the ecall number
    li t1, 100
    bge  t0, t1, enter_secure_world
    li t1, 99
    beq t0, t1, exit_secure_world  # If special ecall, switch worlds

    # Normal ecall handling...
    j env_call_from_u_mode_handler

enter_secure_world:
    # Force the scheduler to pick the secure world
    li t0, UTANGO_WORLDS - 1
    la t1, secure_world_request
    sw t0, 0(t1)        # Update secure_world_request

    mv t0, a7           # Read the ecall number
    la t1, secure_call
    sw t0, 0(t1)        # Update secure_call

    mv t0, a6           # Read the cmd number
    la t1, secure_cmd
    sw t0, 0(t1)        # Update secure_cmd

    # Force the mepc of the current world forward
    csrr t1, mepc   # Get the current mepc (which holds the ecall address)
    addi t1, t1, 4  # Move to the next instruction
    csrw mepc, t1   # Update mepc

    # Make sure this is reset
    li t0, 0
    la t1, exit_secure_world_request
    sw t0, 0(t1)

    # Switch worlds using the regular context switch mechanism
    j context_switch

exit_secure_world:
    # Force the scheduler to get out of the secure world
    li t0, 1
    la t1, exit_secure_world_request
    sw t0, 0(t1)    # Update exit_secure_world_request

    # Force the mepc of the current world forward
    csrr t1, mepc   # Get the current mepc (which holds the ecall address)
    addi t1, t1, 4  # Move to the next instruction
    csrw mepc, t1   # Update mepc

    # Switch worlds using the regular context switch mechanism
    j context_switch


env_call_from_u_mode_handler:
    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    csrr t1, mepc
    sw t1, WCB_CTX_IRQ_PREVIOUS_MEPC_OFF(t0)
    csrr t1, mtval
    sw t1, WCB_CTX_IRQ_PREVIOUS_MTVAL_OFF(t0)
    csrr t1, mie
    sw t1, WCB_CTX_IRQ_PREVIOUS_MIE_OFF(t0)


    // checking the current virtual mstatus privelege to see 
    // if env call was from user or machine mode

    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t0)
    srli t1, t1, 8
    andi t1, t1, 0x18
    beqz t1, 1f
    li t1, 11   // is from machine mode
    sw t1, WCB_CTX_IRQ_PREVIOUS_MCAUSE_OFF(t0)
    j 2f

    1:  // is from user mode
    li t1, 8
    sw t1, WCB_CTX_IRQ_PREVIOUS_MCAUSE_OFF(t0)

    2:
    # jump to the correct world interrupt vector
    lw t0, WCB_CTX_VECT(t0)
    csrw mepc, t0

    RESTORE_TEMP
    mret

    .size env_call_from_u_mode_handler, . - env_call_from_u_mode_handler

illegal_instruction_handler:
	csrr t0, mtval
	li t1, MRET_OP 
	beq t0, t1, mret_from_user_mode
    MASK_INST_OP t0
    li t1, SYSTEM_OP
    beq t0, t1, system_instruction_handler

	j world_exception_handler
    .size illegal_instruction_handler, . - illegal_instruction_handler



system_instruction_handler:
	csrr t0, mtval
    MASK_SYSTEM_INST_FUNC t0
    li t1, CSRRW_FUNC
    beq t0, t1, illegal_csrop_handler
    li t1, CSRRS_FUNC
    beq t0, t1, illegal_csrop_handler
    li t1, CSRRC_FUNC
    beq t0, t1, illegal_csrop_handler
    li t1, CSRRWI_FUNC
    beq t0, t1, illegal_csrop_handler
    li t1, CSRRSI_FUNC
    beq t0, t1, illegal_csrop_handler
    li t1, CSRRCI_FUNC
    beq t0, t1, illegal_csrop_handler

    j world_exception_handler
    .size system_instruction_handler, . - system_instruction_handler

illegal_csrop_handler:
	csrr t0, mtval
    MASK_CSR_REG t0
    li t1, MIE_DEST
    beq t0, t1, rwcs_mie
    li t1, MTVEC_DEST
    beq t0, t1, rwcs_mtvec
    li t1, MEPC_DEST
    beq t0, t1, rwcs_mepc
    li t1, MCAUSE_DEST
    beq t0, t1, rwcs_mcause
    li t1, MTVAL_DEST
    beq t0, t1, rwcs_mtval
    li t1, MHARTID_DEST
    beq t0, t1, rwcs_mhartid
    li t1, MISA_DEST
    beq t0, t1, rwcs_misa
    li t1, MSTATUS_DEST
    beq t0, t1, rwcs_mstatus
    li t1, MIP_DEST
    beq t0, t1, rwcs_mip
    li t1, MCYCLE_DEST
    beq t0, t1, rwcs_mcycle
    li t1, MINSTRET_DEST
    beq t0, t1, rwcs_minstret

    j world_exception_handler

rwcs_mcycle:
    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the read part first

    # decoding the jump
	csrr t0, mtval                          # read the illegal instruction   
    MASK_CSR_DEST t0                        # t0 holds the register of destination
    slli t0, t0, 3                          # times 8 the register number 
    # writing mhartid to mscratch
    csrr t1, mcycle
    csrw mscratch, t1
    # writing the value that was on the csr to the dest register
    la t1, mscratch_to_register_jump_table
    add t0, t0, t1 
    la t1, 1f
    jalr x0, t0, 0


    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the write part (no writing allowed)
    1:
    # #  decoding the jump
	# csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # slli t0, t0, 3                          # multiplie the register by 8
    # # writing the value on the source register to t1
    # la t1, register_to_register_jump_table
    # add t0, t0, t1                          # t0 has the address of the correct jump
    # auipc t1, 0
    # addi t1, t1, 8
    # jalr x0, t0, 0
    # csrw mscratch, t0

    # ###########################################################
    # ###########################################################

    # # decoding the type of opperation (W, C, S, WI, CI, SI)
    # csrr t0, mtval
    # MASK_SYSTEM_INST_FUNC t0
    # li t1, CSRRW_FUNC
    # beq t0, t1, 1f
    # li t1, CSRRS_FUNC
    # beq t0, t1, 2f
    # li t1, CSRRC_FUNC
    # beq t0, t1, 3f
    # li t1, CSRRWI_FUNC
    # beq t0, t1, 4f
    # li t1, CSRRSI_FUNC
    # beq t0, t1, 5f
    # li t1, CSRRCI_FUNC
    # beq t0, t1, 6f

    # ###########################################################

    # # write operation
    # 1:
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # set operation
    # 2:
    # # reading the source value from mscratch
    # csrr t0, mscratch
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the set operation
    # or t0, t1, t0     # Set specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # clear operation
    # 3:
    # # reading the source value from mscratch
    # csrr t0, mscratch
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the clear operation
    # not t0, t0        # Invert mask to clear specific bit
    # and t0, t0, t1    # Clear specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # write immediate operation
    # 4:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # set immediate operation
    # 5:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the set operation
    # or t0, t1, t0     # Set specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # clear immediate operation
    # 6:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the clear operation
    # not t0, t0        # Invert mask to clear specific bit
    # and t0, t0, t1    # Clear specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # writing the value in t0 to virtual_mstatus
    # 7:
    # csrr t0, mscratch
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # sw t0, WCB_CTX_VIRTUAL_MSTATUS(t1)

    j return_from_trap_and_emul    

rwcs_minstret:
    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the read part first

    # decoding the jump
	csrr t0, mtval                          # read the illegal instruction   
    MASK_CSR_DEST t0                        # t0 holds the register of destination
    slli t0, t0, 3                          # times 8 the register number 
    # writing mhartid to mscratch
    csrr t1, minstret
    csrw mscratch, t1
    # writing the value that was on the csr to the dest register
    la t1, mscratch_to_register_jump_table
    add t0, t0, t1 
    la t1, 1f
    jalr x0, t0, 0


    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the write part (no writing allowed)
    1:
    # #  decoding the jump
	# csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # slli t0, t0, 3                          # multiplie the register by 8
    # # writing the value on the source register to t1
    # la t1, register_to_register_jump_table
    # add t0, t0, t1                          # t0 has the address of the correct jump
    # auipc t1, 0
    # addi t1, t1, 8
    # jalr x0, t0, 0
    # csrw mscratch, t0

    # ###########################################################
    # ###########################################################

    # # decoding the type of opperation (W, C, S, WI, CI, SI)
    # csrr t0, mtval
    # MASK_SYSTEM_INST_FUNC t0
    # li t1, CSRRW_FUNC
    # beq t0, t1, 1f
    # li t1, CSRRS_FUNC
    # beq t0, t1, 2f
    # li t1, CSRRC_FUNC
    # beq t0, t1, 3f
    # li t1, CSRRWI_FUNC
    # beq t0, t1, 4f
    # li t1, CSRRSI_FUNC
    # beq t0, t1, 5f
    # li t1, CSRRCI_FUNC
    # beq t0, t1, 6f

    # ###########################################################

    # # write operation
    # 1:
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # set operation
    # 2:
    # # reading the source value from mscratch
    # csrr t0, mscratch
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the set operation
    # or t0, t1, t0     # Set specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # clear operation
    # 3:
    # # reading the source value from mscratch
    # csrr t0, mscratch
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the clear operation
    # not t0, t0        # Invert mask to clear specific bit
    # and t0, t0, t1    # Clear specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # write immediate operation
    # 4:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # set immediate operation
    # 5:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the set operation
    # or t0, t1, t0     # Set specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # clear immediate operation
    # 6:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the clear operation
    # not t0, t0        # Invert mask to clear specific bit
    # and t0, t0, t1    # Clear specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # writing the value in t0 to virtual_mstatus
    # 7:
    # csrr t0, mscratch
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # sw t0, WCB_CTX_VIRTUAL_MSTATUS(t1)

    j return_from_trap_and_emul    


rwcs_mstatus:
    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the read part first

    # decoding the jump
	csrr t0, mtval                          # read the illegal instruction   
    MASK_CSR_DEST t0                        # t0 holds the register of destination
    slli t0, t0, 3                          # times 8 the register number 
    # writing virtual_mstatus to mscratch
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    csrw mscratch, t1
    # writing the value that was on the csr to the dest register
    la t1, mscratch_to_register_jump_table
    add t0, t0, t1 
    la t1, 1f
    jalr x0, t0, 0

    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the write part
    1:
    #  decoding the jump
	csrr t0, mtval
    MASK_CSR_SOURCE t0
    slli t0, t0, 3                          # multiplie the register by 8
    # writing the value on the source register to t1
    la t1, register_to_register_jump_table
    add t0, t0, t1                          # t0 has the address of the correct jump
    auipc t1, 0
    addi t1, t1, 8
    jalr x0, t0, 0
    csrw mscratch, t0

    ###########################################################
    ###########################################################

    # decoding the type of opperation (W, C, S, WI, CI, SI)
    csrr t0, mtval
    MASK_SYSTEM_INST_FUNC t0
    li t1, CSRRW_FUNC
    beq t0, t1, 1f
    li t1, CSRRS_FUNC
    beq t0, t1, 2f
    li t1, CSRRC_FUNC
    beq t0, t1, 3f
    li t1, CSRRWI_FUNC
    beq t0, t1, 4f
    li t1, CSRRSI_FUNC
    beq t0, t1, 5f
    li t1, CSRRCI_FUNC
    beq t0, t1, 6f

    ###########################################################

    # write operation
    1:
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # set operation
    2:
    # reading the source value from mscratch
    csrr t0, mscratch
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # performing the set operation
    or t0, t1, t0     # Set specific bit in x1
    la t1, 7f           # jumping to save the value back
    csrw mscratch, t0
    jalr x0, t1, 0

    ###########################################################

    # clear operation
    3:
    # reading the source value from mscratch
    csrr t0, mscratch
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # performing the clear operation
    not t0, t0        # Invert mask to clear specific bit
    and t0, t0, t1    # Clear specific bit in x1
    la t1, 7f           # jumping to save the value back
    csrw mscratch, t0
    jalr x0, t1, 0

    ###########################################################

    # write immediate operation
    4:
    # get immediate value to t0
    csrr t0, mtval
    MASK_CSR_SOURCE t0
    la t1, 7f           # jumping to save the value back
    csrw mscratch, t0
    jalr x0, t1, 0

    ###########################################################

    # set immediate operation
    5:
    # get immediate value to t0
    csrr t0, mtval
    MASK_CSR_SOURCE t0
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # performing the set operation
    or t0, t1, t0     # Set specific bit in x1
    la t1, 7f           # jumping to save the value back
    csrw mscratch, t0
    jalr x0, t1, 0

    ###########################################################

    # clear immediate operation
    6:
    # get immediate value to t0
    csrr t0, mtval
    MASK_CSR_SOURCE t0
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # performing the clear operation
    not t0, t0        # Invert mask to clear specific bit
    and t0, t0, t1    # Clear specific bit in x1
    la t1, 7f           # jumping to save the value back
    csrw mscratch, t0
    jalr x0, t1, 0

    ###########################################################

    # writing the value in t0 to virtual_mstatus
    7:
    csrr t0, mscratch
    # Check if mstatus.mie is enabled
    andi t0, t0, MSTATUS_MIE
    # jump to loading virtual mie and stored plic enable regsters if enabled
    bnez t0, 1f
    # set plic enable registers and mie to 0 if mstatus.mie is disabled
    li t0, 0x80
    csrw mie, t0    # leaving only timer interrupt active
    la t0, PLIC_ENABLE_ADDR
    sw x0, 0(t0)    # clearing PLIC enable register 0
    sw x0, 4(t0)    # clearing PLIC enable register 1
    # reseting th enable in the list struct
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t0, WCB_ID(t1)
    li t1, TIMECMP_LIST_SIZE
    mul t0, t0, t1
    la t1, mtimecmp_list
    add t0, t0, t1      # t0 now points to the correct struct

    # reset the enable variable in the struct
    li t1, 0
    sw t1, TIMECMP_LIST_ENABLE(t0)
    j end_emul

    # restore virtual mie and plic enable registers
    1:
    csrr t0, mscratch
    li t1, 0x21888
    and t0, t0, t1
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    sw t0, WCB_CTX_VIRTUAL_MSTATUS(t1)
    RESTORE_PLIC
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MIE(t1)
    ori t1, t1, 0x80
    csrw mie, t1
    # check if mtimecmp_interrupt is enabled
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t0, WCB_CTX_VIRTUAL_MIE(t1)
    andi t0, t0, MIE_MTIMER_INTERRUPT
    beqz t0, return_from_trap_and_emul     # jump if its not enabled
    # execute this code if timer_interrupt is enabled
    lw t0, WCB_ID(t1)
    li t1, TIMECMP_LIST_SIZE
    mul t0, t0, t1
    la t1, mtimecmp_list
    add t0, t0, t1      # t0 now points to the correct struct

    # set the enable variable in the struct
    li t1, 1
    sw t1, TIMECMP_LIST_ENABLE(t0)

    #save mscratch 
    la t0, register_ctx
    csrr t1, mscratch
    sw t1, 12(t0)

    CHECK_IF_NEW_MTIMECMP_HAPPENS_FIRST
    beqz t0, 1f
    j end_emul
    # execute if the next mtimercmp should be updated
    1:
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)   
    lw t0, WCB_ID(t1)
    csrw mscratch, t0
    UPDATE_MTIMER_CMP_FROM_LIST

    # updating the next_interrupt identyfier
    csrr t0, mscratch
    la t1, next_mtimer_interrupt_is_world
    sw t0, 0(t1)

    # restore mscratch
    la t0, register_ctx
    lw t1, 12(t0)
    csrw mscratch, t1

    end_emul:
    csrr t0, mscratch
    li t1, 0x21888      # maximum value in the mstatus reg
    and t0, t0, t1
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    sw t0, WCB_CTX_VIRTUAL_MSTATUS(t1)

    j return_from_trap_and_emul    

rwcs_mcause:
    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the read part first

    # decoding the jump
	csrr t0, mtval                          # read the illegal instruction   
    MASK_CSR_DEST t0                        # t0 holds the register of destination
    slli t0, t0, 3                          # times 8 the register number 
    # writing virtual_mstatus to mscratch
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_IRQ_PREVIOUS_MCAUSE_OFF(t1)
    csrw mscratch, t1
    # writing the value that was on the csr to the dest register
    la t1, mscratch_to_register_jump_table
    add t0, t0, t1 
    la t1, 1f
    jalr x0, t0, 0


    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the write part (no writing allowed)
    1:
    # #  decoding the jump
	# csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # slli t0, t0, 3                          # multiplie the register by 8
    # # writing the value on the source register to t1
    # la t1, register_to_register_jump_table
    # add t0, t0, t1                          # t0 has the address of the correct jump
    # auipc t1, 0
    # addi t1, t1, 8
    # jalr x0, t0, 0
    # csrw mscratch, t0

    # ###########################################################
    # ###########################################################

    # # decoding the type of opperation (W, C, S, WI, CI, SI)
    # csrr t0, mtval
    # MASK_SYSTEM_INST_FUNC t0
    # li t1, CSRRW_FUNC
    # beq t0, t1, 1f
    # li t1, CSRRS_FUNC
    # beq t0, t1, 2f
    # li t1, CSRRC_FUNC
    # beq t0, t1, 3f
    # li t1, CSRRWI_FUNC
    # beq t0, t1, 4f
    # li t1, CSRRSI_FUNC
    # beq t0, t1, 5f
    # li t1, CSRRCI_FUNC
    # beq t0, t1, 6f

    # ###########################################################

    # # write operation
    # 1:
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # set operation
    # 2:
    # # reading the source value from mscratch
    # csrr t0, mscratch
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the set operation
    # or t0, t1, t0     # Set specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # clear operation
    # 3:
    # # reading the source value from mscratch
    # csrr t0, mscratch
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the clear operation
    # not t0, t0        # Invert mask to clear specific bit
    # and t0, t0, t1    # Clear specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # write immediate operation
    # 4:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # set immediate operation
    # 5:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the set operation
    # or t0, t1, t0     # Set specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # clear immediate operation
    # 6:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the clear operation
    # not t0, t0        # Invert mask to clear specific bit
    # and t0, t0, t1    # Clear specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # writing the value in t0 to virtual_mstatus
    # 7:
    # csrr t0, mscratch
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # sw t0, WCB_CTX_VIRTUAL_MSTATUS(t1)

    j return_from_trap_and_emul    

rwcs_mtvec:
    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the read part first

    # decoding the jump
	csrr t0, mtval                          # read the illegal instruction   
    MASK_CSR_DEST t0                        # t0 holds the register of destination
    slli t0, t0, 3                          # times 8 the register number 
    # writing virtual_mstatus to mscratch
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VECT(t1)
    csrw mscratch, t1
    # writing the value that was on the csr to the dest register
    la t1, mscratch_to_register_jump_table
    add t0, t0, t1 
    la t1, 1f
    jalr x0, t0, 0


    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the write part
    1:
    #  decoding the jump
	csrr t0, mtval
    MASK_CSR_SOURCE t0
    slli t0, t0, 3                          # multiplie the register by 8
    # writing the value on the source register to t1
    la t1, register_to_register_jump_table
    add t0, t0, t1                          # t0 has the address of the correct jump
    auipc t1, 0
    addi t1, t1, 8
    jalr x0, t0, 0
    csrw mscratch, t0

    ###########################################################
    ###########################################################

    # decoding the type of opperation (W, C, S, WI, CI, SI)
    csrr t0, mtval
    MASK_SYSTEM_INST_FUNC t0
    li t1, CSRRW_FUNC
    beq t0, t1, 1f
    li t1, CSRRS_FUNC
    beq t0, t1, 2f
    li t1, CSRRC_FUNC
    beq t0, t1, 3f
    li t1, CSRRWI_FUNC
    beq t0, t1, 4f
    li t1, CSRRSI_FUNC
    beq t0, t1, 5f
    li t1, CSRRCI_FUNC
    beq t0, t1, 6f

    ###########################################################

    # write operation
    1:
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # set operation
    2:
    # reading the source value from mscratch
    csrr t0, mscratch
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VECT(t1)
    # performing the set operation
    or t0, t1, t0     # Set specific bit in x1
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # clear operation
    3:
    # reading the source value from mscratch
    csrr t0, mscratch
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VECT(t1)
    # performing the clear operation
    not t0, t0        # Invert mask to clear specific bit
    and t0, t0, t1    # Clear specific bit in x1
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # write immediate operation
    4:
    # get immediate value to t0
    csrr t0, mtval
    MASK_CSR_SOURCE t0
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # set immediate operation
    5:
    # get immediate value to t0
    csrr t0, mtval
    MASK_CSR_SOURCE t0
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VECT(t1)
    # performing the set operation
    or t0, t1, t0     # Set specific bit in x1
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # clear immediate operation
    6:
    # get immediate value to t0
    csrr t0, mtval
    MASK_CSR_SOURCE t0
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VECT(t1)
    # performing the clear operation
    not t0, t0        # Invert mask to clear specific bit
    and t0, t0, t1    # Clear specific bit in x1
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # writing the value in t0 to virtual_mstatus
    7:
    csrr t0, mscratch
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    sw t0, WCB_CTX_VECT(t1)
    j return_from_trap_and_emul    

rwcs_mtval:
    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the read part first

    # decoding the jump
	csrr t0, mtval                          # read the illegal instruction   
    MASK_CSR_DEST t0                        # t0 holds the register of destination
    slli t0, t0, 3                          # times 8 the register number 
    # writing virtual_mstatus to mscratch
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_IRQ_PREVIOUS_MTVAL_OFF(t1)
    csrw mscratch, t1
    # writing the value that was on the csr to the dest register
    la t1, mscratch_to_register_jump_table
    add t0, t0, t1 
    la t1, 1f
    jalr x0, t0, 0


    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the write part (no writing allowed)
    1:
    # #  decoding the jump
	# csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # slli t0, t0, 3                          # multiplie the register by 8
    # # writing the value on the source register to t1
    # la t1, register_to_register_jump_table
    # add t0, t0, t1                          # t0 has the address of the correct jump
    # auipc t1, 0
    # addi t1, t1, 8
    # jalr x0, t0, 0
    # csrw mscratch, t0

    # ###########################################################
    # ###########################################################

    # # decoding the type of opperation (W, C, S, WI, CI, SI)
    # csrr t0, mtval
    # MASK_SYSTEM_INST_FUNC t0
    # li t1, CSRRW_FUNC
    # beq t0, t1, 1f
    # li t1, CSRRS_FUNC
    # beq t0, t1, 2f
    # li t1, CSRRC_FUNC
    # beq t0, t1, 3f
    # li t1, CSRRWI_FUNC
    # beq t0, t1, 4f
    # li t1, CSRRSI_FUNC
    # beq t0, t1, 5f
    # li t1, CSRRCI_FUNC
    # beq t0, t1, 6f

    # ###########################################################

    # # write operation
    # 1:
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # set operation
    # 2:
    # # reading the source value from mscratch
    # csrr t0, mscratch
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the set operation
    # or t0, t1, t0     # Set specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # clear operation
    # 3:
    # # reading the source value from mscratch
    # csrr t0, mscratch
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the clear operation
    # not t0, t0        # Invert mask to clear specific bit
    # and t0, t0, t1    # Clear specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # write immediate operation
    # 4:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # set immediate operation
    # 5:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the set operation
    # or t0, t1, t0     # Set specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # clear immediate operation
    # 6:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the clear operation
    # not t0, t0        # Invert mask to clear specific bit
    # and t0, t0, t1    # Clear specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # writing the value in t0 to virtual_mstatus
    # 7:
    # csrr t0, mscratch
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # sw t0, WCB_CTX_VIRTUAL_MSTATUS(t1)

    j return_from_trap_and_emul    

rwcs_mepc:
    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the read part first

    # decoding the jump
	csrr t0, mtval                          # read the illegal instruction   
    MASK_CSR_DEST t0                        # t0 holds the register of destination
    slli t0, t0, 3                          # times 8 the register number 
    # writing virtual_mstatus to mscratch
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_IRQ_PREVIOUS_MEPC_OFF(t1)
    csrw mscratch, t1
    # writing the value that was on the csr to the dest register
    la t1, mscratch_to_register_jump_table
    add t0, t0, t1 
    la t1, 1f
    jalr x0, t0, 0


    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the write part
    1:
    #  decoding the jump
	csrr t0, mtval
    MASK_CSR_SOURCE t0
    slli t0, t0, 3                          # multiplie the register by 8
    # writing the value on the source register to t1
    la t1, register_to_register_jump_table
    add t0, t0, t1                          # t0 has the address of the correct jump
    auipc t1, 0
    addi t1, t1, 8
    jalr x0, t0, 0
    csrw mscratch, t0

    ###########################################################
    ###########################################################

    # decoding the type of opperation (W, C, S, WI, CI, SI)
    csrr t0, mtval
    MASK_SYSTEM_INST_FUNC t0
    li t1, CSRRW_FUNC
    beq t0, t1, 1f
    li t1, CSRRS_FUNC
    beq t0, t1, 2f
    li t1, CSRRC_FUNC
    beq t0, t1, 3f
    li t1, CSRRWI_FUNC
    beq t0, t1, 4f
    li t1, CSRRSI_FUNC
    beq t0, t1, 5f
    li t1, CSRRCI_FUNC
    beq t0, t1, 6f

    ###########################################################

    # write operation
    1:
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # set operation
    2:
    # reading the source value from mscratch
    csrr t0, mscratch
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_IRQ_PREVIOUS_MEPC_OFF(t1)
    # performing the set operation
    or t0, t1, t0     # Set specific bit in x1
    csrw mscratch, t0
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # clear operation
    3:
    # reading the source value from mscratch
    csrr t0, mscratch
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_IRQ_PREVIOUS_MEPC_OFF(t1)
    # performing the clear operation
    not t0, t0        # Invert mask to clear specific bit
    and t0, t0, t1    # Clear specific bit in x1
    csrw mscratch, t0
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # write immediate operation
    4:
    # get immediate value to t0
    csrr t0, mtval
    MASK_CSR_SOURCE t0
    la t1, 7f           # jumping to save the value back
    csrw mscratch, t0
    jalr x0, t1, 0

    ###########################################################

    # set immediate operation
    5:
    # get immediate value to t0
    csrr t0, mtval
    MASK_CSR_SOURCE t0
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_IRQ_PREVIOUS_MEPC_OFF(t1)
    # performing the set operation
    or t0, t1, t0     # Set specific bit in x1
    la t1, 7f           # jumping to save the value back
    csrw mscratch, t0
    jalr x0, t1, 0

    ###########################################################

    # clear immediate operation
    6:
    # get immediate value to t0
    csrr t0, mtval
    MASK_CSR_SOURCE t0
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_IRQ_PREVIOUS_MEPC_OFF(t1)
    # performing the clear operation
    not t0, t0        # Invert mask to clear specific bit
    and t0, t0, t1    # Clear specific bit in x1
    la t1, 7f           # jumping to save the value back
    csrw mscratch, t0
    jalr x0, t1, 0

    ###########################################################

    # writing the value in t0 to virtual_mstatus
    7:
    csrr t0, mscratch
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    sw t0, WCB_CTX_IRQ_PREVIOUS_MEPC_OFF(t1)

    j return_from_trap_and_emul    

rwcs_mhartid:
    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the read part first

    # decoding the jump
	csrr t0, mtval                          # read the illegal instruction   
    MASK_CSR_DEST t0                        # t0 holds the register of destination
    slli t0, t0, 3                          # times 8 the register number 
    # writing mhartid to mscratch
    csrr t1, mhartid
    csrw mscratch, t1
    # writing the value that was on the csr to the dest register
    la t1, mscratch_to_register_jump_table
    add t0, t0, t1 
    la t1, 1f
    jalr x0, t0, 0


    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the write part (no writing allowed)
    1:
    # #  decoding the jump
	# csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # slli t0, t0, 3                          # multiplie the register by 8
    # # writing the value on the source register to t1
    # la t1, register_to_register_jump_table
    # add t0, t0, t1                          # t0 has the address of the correct jump
    # auipc t1, 0
    # addi t1, t1, 8
    # jalr x0, t0, 0
    # csrw mscratch, t0

    # ###########################################################
    # ###########################################################

    # # decoding the type of opperation (W, C, S, WI, CI, SI)
    # csrr t0, mtval
    # MASK_SYSTEM_INST_FUNC t0
    # li t1, CSRRW_FUNC
    # beq t0, t1, 1f
    # li t1, CSRRS_FUNC
    # beq t0, t1, 2f
    # li t1, CSRRC_FUNC
    # beq t0, t1, 3f
    # li t1, CSRRWI_FUNC
    # beq t0, t1, 4f
    # li t1, CSRRSI_FUNC
    # beq t0, t1, 5f
    # li t1, CSRRCI_FUNC
    # beq t0, t1, 6f

    # ###########################################################

    # # write operation
    # 1:
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # set operation
    # 2:
    # # reading the source value from mscratch
    # csrr t0, mscratch
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the set operation
    # or t0, t1, t0     # Set specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # clear operation
    # 3:
    # # reading the source value from mscratch
    # csrr t0, mscratch
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the clear operation
    # not t0, t0        # Invert mask to clear specific bit
    # and t0, t0, t1    # Clear specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # write immediate operation
    # 4:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # set immediate operation
    # 5:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the set operation
    # or t0, t1, t0     # Set specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # clear immediate operation
    # 6:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the clear operation
    # not t0, t0        # Invert mask to clear specific bit
    # and t0, t0, t1    # Clear specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # writing the value in t0 to virtual_mstatus
    # 7:
    # csrr t0, mscratch
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # sw t0, WCB_CTX_VIRTUAL_MSTATUS(t1)

    j return_from_trap_and_emul    


rwcs_misa:
    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the read part first

    # decoding the jump
	csrr t0, mtval                          # read the illegal instruction   
    MASK_CSR_DEST t0                        # t0 holds the register of destination
    slli t0, t0, 3                          # times 8 the register number 
    # writing mhartid to mscratch
    csrr t1, misa
    csrw mscratch, t1
    # writing the value that was on the csr to the dest register
    la t1, mscratch_to_register_jump_table
    add t0, t0, t1 
    la t1, 1f
    jalr x0, t0, 0


    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the write part (no writing allowed)
    1:
    # #  decoding the jump
	# csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # slli t0, t0, 3                          # multiplie the register by 8
    # # writing the value on the source register to t1
    # la t1, register_to_register_jump_table
    # add t0, t0, t1                          # t0 has the address of the correct jump
    # auipc t1, 0
    # addi t1, t1, 8
    # jalr x0, t0, 0
    # csrw mscratch, t0

    # ###########################################################
    # ###########################################################

    # # decoding the type of opperation (W, C, S, WI, CI, SI)
    # csrr t0, mtval
    # MASK_SYSTEM_INST_FUNC t0
    # li t1, CSRRW_FUNC
    # beq t0, t1, 1f
    # li t1, CSRRS_FUNC
    # beq t0, t1, 2f
    # li t1, CSRRC_FUNC
    # beq t0, t1, 3f
    # li t1, CSRRWI_FUNC
    # beq t0, t1, 4f
    # li t1, CSRRSI_FUNC
    # beq t0, t1, 5f
    # li t1, CSRRCI_FUNC
    # beq t0, t1, 6f

    # ###########################################################

    # # write operation
    # 1:
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # set operation
    # 2:
    # # reading the source value from mscratch
    # csrr t0, mscratch
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the set operation
    # or t0, t1, t0     # Set specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # clear operation
    # 3:
    # # reading the source value from mscratch
    # csrr t0, mscratch
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the clear operation
    # not t0, t0        # Invert mask to clear specific bit
    # and t0, t0, t1    # Clear specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # write immediate operation
    # 4:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # set immediate operation
    # 5:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the set operation
    # or t0, t1, t0     # Set specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # clear immediate operation
    # 6:
    # # get immediate value to t0
    # csrr t0, mtval
    # MASK_CSR_SOURCE t0
    # # reading virtual mstatus
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # # performing the clear operation
    # not t0, t0        # Invert mask to clear specific bit
    # and t0, t0, t1    # Clear specific bit in x1
    # la t1, 7f           # jumping to save the value back
    # jalr x0, t1, 0

    # ###########################################################

    # # writing the value in t0 to virtual_mstatus
    # 7:
    # csrr t0, mscratch
    # la t1, rworld_ctx_ptr
    # lw t1, 0(t1)
    # sw t0, WCB_CTX_VIRTUAL_MSTATUS(t1)

    j return_from_trap_and_emul    



rwcs_mie:
    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the read part first

    # decoding the jump
	csrr t0, mtval                          # read the illegal instruction   
    MASK_CSR_DEST t0                        # t0 holds the register of destination
    slli t0, t0, 3                          # times 8 the register number 
    # writing virtual_mstatus to mscratch
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MIE(t1)
    csrw mscratch, t1
    # writing the value that was on the csr to the dest register
    la t1, mscratch_to_register_jump_table
    add t0, t0, t1 
    la t1, 1f
    jalr x0, t0, 0


    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the write part
    1:
    #  decoding the jump
	csrr t0, mtval
    MASK_CSR_SOURCE t0
    slli t0, t0, 3                          # multiplie the register by 8
    # writing the value on the source register to t1
    la t1, register_to_register_jump_table
    add t0, t0, t1                          # t0 has the address of the correct jump
    auipc t1, 0
    addi t1, t1, 8
    jalr x0, t0, 0
    csrw mscratch, t0

    ###########################################################
    ###########################################################

    # decoding the type of opperation (W, C, S, WI, CI, SI)
    csrr t0, mtval
    MASK_SYSTEM_INST_FUNC t0
    li t1, CSRRW_FUNC
    beq t0, t1, 1f
    li t1, CSRRS_FUNC
    beq t0, t1, 2f
    li t1, CSRRC_FUNC
    beq t0, t1, 3f
    li t1, CSRRWI_FUNC
    beq t0, t1, 4f
    li t1, CSRRSI_FUNC
    beq t0, t1, 5f
    li t1, CSRRCI_FUNC
    beq t0, t1, 6f

    ###########################################################

    # write operation
    1:
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # set operation
    2:
    # reading the source value from mscratch
    csrr t0, mscratch
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MIE(t1)
    # performing the set operation
    or t0, t1, t0     # Set specific bit in x1
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # clear operation
    3:
    # reading the source value from mscratch
    csrr t0, mscratch
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MIE(t1)
    # performing the clear operation
    not t0, t0        # Invert mask to clear specific bit
    and t0, t0, t1    # Clear specific bit in x1
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # write immediate operation
    4:
    # get immediate value to t0
    csrr t0, mtval
    MASK_CSR_SOURCE t0
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # set immediate operation
    5:
    # get immediate value to t0
    csrr t0, mtval
    MASK_CSR_SOURCE t0
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MIE(t1)
    # performing the set operation
    or t0, t1, t0     # Set specific bit in x1
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # clear immediate operation
    6:
    # get immediate value to t0
    csrr t0, mtval
    MASK_CSR_SOURCE t0
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MIE(t1)
    # performing the clear operation
    not t0, t0        # Invert mask to clear specific bit
    and t0, t0, t1    # Clear specific bit in x1
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # writing the value in mscratch to virtual_mie
    7:
    ##############################
    # masking the value with the base MIE
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_IRQ_BASE_MIE_OFF(t1)
    # storig the masked value in t0
    csrr t0, mscratch
    and t0, t1, t0
    ##############################
    # writing masked value to virtual mie
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    sw t0, WCB_CTX_VIRTUAL_MIE(t1)
    ##############################
    # check if mstatus.mie is enabled, if so, write to mie, else virtual mie is enough
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t1)
    andi t1, t1, MSTATUS_MIE
    # skip writing mie csr if mstatus.mie is disabled
    beq t1, x0, 8f

    # writing to mie and making sure timer interrupt is not disabled
    ori t0, t0, 0x80
    csrw mie, t0

    # check if mtimecmp_interrupt is enabled
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t0, WCB_CTX_VIRTUAL_MIE(t1)
    andi t0, t0, MIE_MTIMER_INTERRUPT
    beqz t0, return_from_trap_and_emul     # jump if its not enabled
    # execute this code if timer_interrupt is enabled
    lw t0, WCB_ID(t1)
    li t1, TIMECMP_LIST_SIZE
    mul t0, t0, t1
    la t1, mtimecmp_list
    add t0, t0, t1      # t0 now points to the correct struct


    # set the enable variable in the struct
    li t1, 1
    sw t1, TIMECMP_LIST_ENABLE(t0)

    #save mscratch 
    la t0, register_ctx
    csrr t1, mscratch
    sw t1, 12(t0)

    CHECK_IF_NEW_MTIMECMP_HAPPENS_FIRST
    bnez t0, 1f
    j 2f
    # execute if the next mtimercmp should be updated
    1:
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)   
    lw t0, WCB_ID(t1)
    csrw mscratch, t0
    UPDATE_MTIMER_CMP_FROM_LIST

    # updating the next_interrupt identyfier
    csrr t0, mscratch
    la t1, next_mtimer_interrupt_is_world
    sw t0, 0(t1)

    # restore mscratch
    la t0, register_ctx
    lw t1, 12(t0)
    csrw mscratch, t1

    j return_from_trap_and_emul

    8:
    # reseting th enable in the list struct
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t0, WCB_ID(t1)
    li t1, TIMECMP_LIST_SIZE
    mul t0, t0, t1
    la t1, mtimecmp_list
    add t0, t0, t1      # t0 now points to the correct struct

    # reset the enable variable in the struct
    li t1, 0
    sw t1, TIMECMP_LIST_ENABLE(t0)

    j return_from_trap_and_emul

rwcs_mip:
    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the read part first

    # getting the mie mask from wcb
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_IRQ_BASE_MIE_OFF(t1)
    # reading mie and masking it
    csrr t0, mip
    and t1, t1, t0

    csrw mscratch, t1

    # decoding the jump
	csrr t0, mtval                          # read the illegal instruction   
    MASK_CSR_DEST t0                        # t0 holds the register of destination
    slli t0, t0, 3                          # times 8 the register number 

    # writing the value that was on the csr to the dest register
    la t1, mscratch_to_register_jump_table
    add t0, t0, t1 
    la t1, 1f
    jalr x0, t0, 0


    ###########################################################
    ###########################################################
    ###########################################################

    # dealing with the write part
    1:
    # decoding the jump
	csrr t0, mtval
    MASK_CSR_SOURCE t0
    slli t0, t0, 3                          # multiply the register by 8
    # writing the value on the source register to t1
    la t1, register_to_register_jump_table
    add t0, t0, t1                          # t0 has the address of the correct jump
    auipc t1, 0
    addi t1, t1, 8
    jalr x0, t0, 0
    csrw mscratch, t0

    ###########################################################
    ###########################################################

    # decoding the type of opperation (W, C, S, WI, CI, SI)
    csrr t0, mtval
    MASK_SYSTEM_INST_FUNC t0
    li t1, CSRRW_FUNC
    beq t0, t1, 1f
    li t1, CSRRS_FUNC
    beq t0, t1, 2f
    li t1, CSRRC_FUNC
    beq t0, t1, 3f
    li t1, CSRRWI_FUNC
    beq t0, t1, 4f
    li t1, CSRRSI_FUNC
    beq t0, t1, 5f
    li t1, CSRRCI_FUNC
    beq t0, t1, 6f

    ###########################################################

    # write operation
    1:
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # set operation
    2:
    # reading the source value from mscratch
    csrr t0, mscratch
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MIE(t1)
    # performing the set operation
    or t0, t1, t0     # Set specific bit in x1
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # clear operation
    3:
    # reading the source value from mscratch
    csrr t0, mscratch
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MIE(t1)
    # performing the clear operation
    not t0, t0        # Invert mask to clear specific bit
    and t0, t0, t1    # Clear specific bit in x1
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # write immediate operation
    4:
    # get immediate value to t0
    csrr t0, mtval
    MASK_CSR_SOURCE t0
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # set immediate operation
    5:
    # get immediate value to t0
    csrr t0, mtval
    MASK_CSR_SOURCE t0
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MIE(t1)
    # performing the set operation
    or t0, t1, t0     # Set specific bit in x1
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # clear immediate operation
    6:
    # get immediate value to t0
    csrr t0, mtval
    MASK_CSR_SOURCE t0
    # reading virtual mstatus
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_VIRTUAL_MIE(t1)
    # performing the clear operation
    not t0, t0        # Invert mask to clear specific bit
    and t0, t0, t1    # Clear specific bit in x1
    la t1, 7f           # jumping to save the value back
    jalr x0, t1, 0

    ###########################################################

    # writing the value in mscratch to virtual_mie
    7:
    ##############################
    # masking the value with the base MIE
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_CTX_IRQ_BASE_MIE_OFF(t1)
    csrr t0, mscratch
    # storig the masked value in t0
    and t0, t1, t0
    ##############################
    # writing to mie
    csrw mip, t0

    j return_from_trap_and_emul

# puts the value from mscratch to the register specified in register t0 and returns to the address speciied in t1
mscratch_to_register_jump_table:
    csrr x0, mscratch                 //check this case
    jalr x0, t1, 0
    csrr x1, mscratch
    jalr x0, t1, 0
    csrr x2, mscratch
    jalr x0, t1, 0
    csrr x3, mscratch
    jalr x0, t1, 0
    csrr x4, mscratch
    jalr x0, t1, 0
    nop
    nop
    nop
    j mscratch_to_register_t0_temp      # t0
    nop
    nop
    nop
    j mscratch_to_register_t1_temp      # t1
    csrr x7, mscratch
    jalr x0, t1, 0
    csrr x8, mscratch
    jalr x0, t1, 0
    csrr x9, mscratch
    jalr x0, t1, 0
    csrr x10, mscratch
    jalr x0, t1, 0
    csrr x11, mscratch
    jalr x0, t1, 0
    csrr x12, mscratch
    jalr x0, t1, 0
    csrr x13, mscratch
    jalr x0, t1, 0
    csrr x14, mscratch
    jalr x0, t1, 0
    csrr x15, mscratch
    jalr x0, t1, 0
    csrr x16, mscratch
    jalr x0, t1, 0
    csrr x17, mscratch
    jalr x0, t1, 0
    csrr x18, mscratch
    jalr x0, t1, 0
    csrr x19, mscratch
    jalr x0, t1, 0
    csrr x20, mscratch
    jalr x0, t1, 0
    csrr x21, mscratch
    jalr x0, t1, 0
    csrr x22, mscratch
    jalr x0, t1, 0
    csrr x23, mscratch
    jalr x0, t1, 0
    csrr x24, mscratch
    jalr x0, t1, 0
    csrr x25, mscratch
    jalr x0, t1, 0
    csrr x26, mscratch
    jalr x0, t1, 0
    csrr x27, mscratch
    jalr x0, t1, 0
    csrr x28, mscratch
    jalr x0, t1, 0
    csrr x29, mscratch
    jalr x0, t1, 0
    csrr x30, mscratch
    jalr x0, t1, 0
    csrr x31, mscratch
    jalr x0, t1, 0

# puts the value from mscratch in the register t0
mscratch_to_register_t0_temp:
    csrr t1, mscratch
    csrw mscratch, t0
    la t0, register_ctx
    sw t1, 0(t0)
    j return_from_trap_and_emul

# puts the value from mscratch in the register t1
mscratch_to_register_t1_temp:
    csrr t1, mscratch
    csrw mscratch, t0
    la t0, register_ctx
    sw t1, 4(t0)
    j return_from_trap_and_emul

return_from_trap_and_emul:
    # Check for misaligned addresses 
    csrr t1, mepc
    # check if misaligned
    andi t1, t1, 0x3
    beqz t1, 1f     # is aligned
    csrr t1, mepc
    andi t1, t1, 0xFFFFFFFC
    lw t0, 0(t1)        # get both instructions
    srli t0, t0, 0x10   # isolate the desired instruction
    j 2f

    ###################################################################
    ###################################################################

    # get the register to write to

    1:
    csrr t1, mepc
    lw t0, 0(t1)        # get the instruction to start decoding
    2:

    CHECK_C_INST t0

    beqz t0, 3f     # is regular
    csrr t0, mepc
    addi t0, t0, 2
    csrw mepc, t0
    j 4f

    3:
	csrr t0, mepc
    addi t0, t0, 4
    csrw mepc, t0
    
    4:
    RESTORE_TEMP
	mret

# puts the value specified in register t0 in t0 and jumps back to the value in t1
register_to_register_jump_table:
    add t0, x0, x0
    jalr x0, t1, 0
    add t0, x1, x0
    jalr x0, t1, 0
    add t0, x2, x0
    jalr x0, t1, 0
    add t0, x3, x0
    jalr x0, t1, 0
    add t0, x4, x0
    jalr x0, t1, 0
    j value_t0_temp_to_t0       # t0
    nop
    jalr x0, t1, 0
    nop
    j value_t1_temp_to_t0       # t0
    jalr x0, t1, 0
    add t0, x7, x0
    jalr x0, t1, 0
    add t0, x8, x0
    jalr x0, t1, 0
    add t0, x9, x0
    jalr x0, t1, 0
    add t0, x10, x0
    jalr x0, t1, 0
    add t0, x11, x0
    jalr x0, t1, 0
    add t0, x12, x0
    jalr x0, t1, 0
    add t0, x13, x0
    jalr x0, t1, 0
    add t0, x14, x0
    jalr x0, t1, 0
    add t0, x15, x0
    jalr x0, t1, 0
    add t0, x16, x0
    jalr x0, t1, 0
    add t0, x17, x0
    jalr x0, t1, 0
    add t0, x18, x0
    jalr x0, t1, 0
    add t0, x19, x0
    jalr x0, t1, 0
    add t0, x20, x0
    jalr x0, t1, 0
    add t0, x21, x0
    jalr x0, t1, 0
    add t0, x22, x0
    jalr x0, t1, 0
    add t0, x23, x0
    jalr x0, t1, 0
    add t0, x24, x0
    jalr x0, t1, 0
    add t0, x25, x0
    jalr x0, t1, 0
    add t0, x26, x0
    jalr x0, t1, 0
    add t0, x27, x0
    jalr x0, t1, 0
    add t0, x28, x0
    jalr x0, t1, 0
    add t0, x29, x0
    jalr x0, t1, 0
    add t0, x30, x0
    jalr x0, t1, 0
    add t0, x31, x0
    jalr x0, t1, 0

value_t0_temp_to_t0:
    la t0, register_ctx
    lw t0, 0(t0)
    jalr x0, t1, 0

value_t1_temp_to_t0:
    la t0, register_ctx
    lw t0, 4(t0)
    jalr x0, t1, 0


mret_from_user_mode:
	la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    lw t1, WCB_CTX_IRQ_PREVIOUS_MEPC_OFF(t0)

    csrw mepc, t1

    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t0)
    andi t1, t1, 0x80   # MSTATUS.MPIE
    srli t1, t1, 4
    lw t0, WCB_CTX_VIRTUAL_MSTATUS(t0)
    or t0, t0, t1
    andi t1, t0, 0xFFFFFF7F
	la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    1:
    sw t1, WCB_CTX_VIRTUAL_MSTATUS(t0)

    lw t1, WCB_CTX_IRQ_PREVIOUS_MIE_OFF(t0)
    ori t1, t1, 0x80
    csrw mie, t1

    # to check if it is needed to enable world timer interrupt

    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t0)
    andi t1, t1, 0x8
    beqz t1, mret_interrupts_disabled      # jump if interrupt is not enabled

    lw t1, WCB_CTX_VIRTUAL_MIE(t0)
    andi t1, t1, MIE_MTIMER_INTERRUPT
    beqz t1, mret_interrupts_disabled      # jump if interrupt is not enabled

    #################################################
    # execute this code if timer_interrupt is enabled
    #################################################
    lw t0, WCB_ID(t0)
    li t1, TIMECMP_LIST_SIZE
    mul t0, t0, t1
    la t1, mtimecmp_list
    add t0, t0, t1      # t0 now points to the correct struct

    # set the enable variable in the struct
    li t1, 1
    sw t1, TIMECMP_LIST_ENABLE(t0)

    PROCESS_NEXT_TIMER_INTERRUPT

    la t0, next_mtimer_interrupt_is_world
    lw t0, 0(t0)
    li t1, -1
    beq t0, t1, exit_ctx_switch

    csrw mscratch, t0
    UPDATE_MTIMER_CMP_FROM_LIST

mret_interrupts_disabled:
    RESTORE_TEMP
	mret

 
world_exception_handler:
	la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    csrr t1, mepc
    sw t1, WCB_CTX_IRQ_PREVIOUS_MEPC_OFF(t0)
    csrr t1, mtval
    sw t1, WCB_CTX_IRQ_PREVIOUS_MTVAL_OFF(t0)
    csrr t1, mcause
    sw t1, WCB_CTX_IRQ_PREVIOUS_MCAUSE_OFF(t0)
    csrr t1, mie
    sw t1, WCB_CTX_IRQ_PREVIOUS_MIE_OFF(t0)

    # getting MSTATUS.MIE
    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t0)
    andi t1, t1, 0x8
    slli t1, t1, 4
    # puting mie in mpie
    lw t0, WCB_CTX_VIRTUAL_MSTATUS(t0)
    or t1, t1, t0     #MSTATUS.MPIE
    # clearing MSTATUS.MIE
    andi t1, t1, 0xFFFFFFF7
	la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    sw t1, WCB_CTX_VIRTUAL_MSTATUS(t0)

    lw t1, WCB_CTX_VECT(t0)
    csrw mepc, t1

    li t0, 0x80 # only timer interruot enabled
    csrw mie, t0

    1:
    RESTORE_TEMP
	mret


/*----------------------------------------------------------------------------*/ 
.align      4
.global     msi_handler
.type       msi_handler, %function
/*----------------------------------------------------------------------------*/
msi_handler:
    j   .
    .size msi_handler, . - msi_handler

/*----------------------------------------------------------------------------*/ 
.align      4
.global     mei_handler
.type       mei_handler, %function
/*----------------------------------------------------------------------------*/
mei_handler:
    SAVE_TEMP
    
    # store the current mepc to know where to return after servicing the interrupt
    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    csrr t1, mepc
    sw t1, WCB_CTX_IRQ_PREVIOUS_MEPC_OFF(t0)

    # read PLIC Claim register
    la t0, PLIC_CLAIM_ADDR
    lw t0, 0(t0)

    # store the interrupt claimed in the WCB
    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    sw t1, WCB_CTX_IRQ_CLAIMED_PLIC_OFF(t0)

    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t0)
    andi t1, t1, 0xFFFFFFF7
    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t0)

    # jump to the correct world interrupt vector
    lw t0, WCB_CTX_VECT(t0)
    add t0, t0, 0x2c        # world mie offset
    csrw mepc, t0

    RESTORE_TEMP
    mret

    .size mei_handler, . - mei_handler

/*----------------------------------------------------------------------------*/
.align      4
.global     systick_handler
.type       systick_handler, %function
/*----------------------------------------------------------------------------*/
systick_handler:
    SAVE_TEMP

    csrr t0, mie        # Read current MIE register
    li t1, ~(1 << 7)    # Create a mask to clear bit 7 (MTIE)
    and t0, t0, t1      # Apply the mask (clear MTIE)
    csrw mie, t0        # Write back to MIE register

    j context_switch

    la t0, next_mtimer_interrupt_is_world
    lw t0, 0(t0)
    li t1, -1
    beq t0, t1, context_switch

    # saving the world interrupt
    la t1, register_ctx
    sw t0, 16(t1)

    #### reach here if its interrupt for a world

    # checking if the interrupt is for the current world
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t1, WCB_ID(t1)
    beq t0, t1, timer_interrupt_for_current_world  #branch if is the same as the world

    # checking if the interrupt is enabled for the world
    # loading the world id
    la t1, register_ctx
    lw t0, 16(t1)

    li t1, WCB_SIZE
    mul t0, t1, t0  # t0 holds the correct WCB offset

    la t1, WCB
    add t1, t1, t0  # t1 holds the right WCB pointer

    # check if enabled
    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t0)
    andi t1, t1, 0x8
    bnez t1, timer_interrupt_for_other_world      # jump if interrupt is not enabled
    # check if enabled 
    lw t1, WCB_CTX_VIRTUAL_MIE(t0)
    andi t1, t1, MIE_MTIMER_INTERRUPT
    bnez t1, timer_interrupt_for_other_world      # jump if interrupt is not enabled
    j timer_interrupt_for_disabled_interrupt_other_world

timer_interrupt_for_other_world:
    RESTORE_TEMP

    /* Save context of the world being suspended */
    SAVE_WORLD_CTX

    /* Schedule new world to be resumed */
    la t1, register_ctx
    lw t0, 16(t1)

    li t2, WCB_SIZE
    mul t0, t2, t0  # t0 holds the correct WCB offset

    la t1, WCB
    add t1, t1, t0
    la t0, rworld_ctx_ptr
    sw t1, 0(t0)

    /* Set SAU configuration for the World resumed */
    PMP_SET

    /* Restore context of the NVIC on the world being resumed */
    RESTORE_PLIC

    /* Restore context of the world being resumed */

    RESTORE_WORLD_CTX

    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    csrr t1, mcause
    sw t1, WCB_CTX_IRQ_PREVIOUS_MCAUSE_OFF(t0)
    csrr t1, mtval
    sw t1, WCB_CTX_IRQ_PREVIOUS_MTVAL_OFF(t0)    

    addi t0, t0, WCB_CTX_S_REGS_OFF
    lw t1, 4(t0)
    addi t0, t0, -WCB_CTX_S_REGS_OFF
    sw t1, WCB_CTX_IRQ_PREVIOUS_MEPC_OFF(t0) 

    j update_timer_management

    ######################################################
    # execute this part if it is a timer interrupt for the current world
    # updating interrupt handling virtual registers
timer_interrupt_for_current_world:
    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t0)
    andi t1, t1, 0x8
    beqz t1, timer_interrupt_for_disabled_interrupt_current_world      # jump if interrupt is not enabled

    csrr t1, mepc
    sw t1, WCB_CTX_IRQ_PREVIOUS_MEPC_OFF(t0)
    csrr t1, mcause
    sw t1, WCB_CTX_IRQ_PREVIOUS_MCAUSE_OFF(t0)
    csrr t1, mtval
    sw t1, WCB_CTX_IRQ_PREVIOUS_MTVAL_OFF(t0)    

update_timer_management:

    SYSTICK_UPDATE_MTIMER_CMP

    # clear enable variable in mtimer list for this world
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    lw t0, WCB_ID(t1)
    li t1, TIMECMP_LIST_SIZE
    mul t0, t0, t1
    la t1, mtimecmp_list
    add t0, t0, t1      # t0 now points to the correct struct

    sw x0, TIMECMP_LIST_ENABLE(t0)

    # set the next_mtimer_interrupt_is_world to default -1
    li t1, -1
    la t0, next_mtimer_interrupt_is_world
    sw t1, 0(t0)

    # update mtimer for systick
    la t0, next_mtime_cmp
    lw t1, 4(t0)
    # store next high register in mscratch
    csrw mscratch, t1

    # reading the next low regiter
    lw t1, 0(t0)

    # updating the register with the next values
    li t0, MTIMECMP_ADDR
    sw t1, 0(t0)
    csrr t1, mscratch
    sw t1, 4(t0)

    # restoring the world interrupt enable
    la t1, register_ctx
    lw t1, 16(t1)
    li t0, TIMECMP_LIST_SIZE
    mul t0, t0, t1
    la t1, mtimecmp_list
    add t0, t1, t0 
    li t1, 0
    sw t1, TIMECMP_LIST_ENABLE(t0)

    ## check what type of timer interrupt comes next and update next_mtimer_interrupt_is_world
    PROCESS_NEXT_TIMER_INTERRUPT

    # jump to the correct world interrupt vector
    la t1, rworld_ctx_ptr
    lw t1, 0(t1)
    # clearing MSTATUS:MIE
    lw t0, WCB_CTX_VIRTUAL_MSTATUS(t1)
    andi t0, t0, 0xFFFFFFF7
    ori t0, t0, 0x80     #MSTATUS.MPIE
    sw t0, WCB_CTX_VIRTUAL_MSTATUS(t1)
    # jump to the correct world interrupt vector
    lw t1, WCB_CTX_VECT(t1)
    add t1, t1, 0x1c        # timer interrupt offset
    csrw mepc, t1

    RESTORE_TEMP

    mret

timer_interrupt_for_disabled_interrupt_current_world:
    la t0, rworld_ctx_ptr
    lw t0, 0(t0)
    # clearing MSTATUS:MIE
    lw t1, WCB_CTX_VIRTUAL_MSTATUS(t0)
    andi t1, t1, 0xFFFFFFF7
    ori t1, t1, 0x80     #MSTATUS.MPIE
    sw t1, WCB_CTX_VIRTUAL_MSTATUS(t0)

    la t0, next_mtimer_interrupt_is_world
    li t1, -1
    sw t1, 0(t0)

    PROCESS_NEXT_TIMER_INTERRUPT

    RESTORE_TEMP

    mret

timer_interrupt_for_disabled_interrupt_other_world:

.size systick_handler, . - systick_handler

/*----------------------------------------------------------------------------*/ 

context_switch:

    RESTORE_TEMP

    /* Save context of the world being suspended */
    SAVE_WORLD_CTX

    /* Schedule new world to be resumed */
    SCHEDULE

    /* Set SAU configuration for the World resumed */
    PMP_SET

    RESTORE_WORLD_CTX

    la t4, exit_secure_world_request
    lw t5, 0(t4)
    li t4, 1
    beq t4, t5, only_a6
    
    la t4, secure_world_request
    lw t5, 0(t4)
    li t4, -1
    beq t4, t5, skip_assignment  # If no request, do normal scheduling

    la t4, secure_call
    lw t5, 0(t4)
    mv a7, t5        # Load secure_call into x7

    # Clear the world request
    la t0, secure_world_request
    li t1, -1
    sw t1, 0(t0)

    only_a6:
    la t4, secure_cmd
    lw t5, 0(t4)
    mv a6, t5        # Load secure_cmd into x6

    # Make sure this is reset
    li t0, 0
    la t1, exit_secure_world_request
    sw t0, 0(t1)

    skip_assignment:

    j exit_ctx_switch

exit_ctx_switch:

    RESTORE_TEMP

    /* Jump to the new schedule world */
    mret


.section    .utango.stack, "a"
.align      4
.global     perf_cont
.type       perf_cont, %object
perf_cont:   
    .word 0,0,0,0