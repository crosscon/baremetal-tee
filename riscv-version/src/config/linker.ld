/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */

/* UTANGO FLASH MEMORY (LMA) -------------------------------------------------*/
__FLASH_BASE =  0x20400000;
__FLASH_SIZE =  0x20000000;
/*----------------------------------------------------------------------------*/

/* UTANGO DATA TCM (VMA) -----------------------------------------------------*/
__DTCM_BASE =   0x80000000;
__DTCM_SIZE =   0x4000;
/*----------------------------------------------------------------------------*/
__STACK_SIZE =  0x00000400;
__HEAP_SIZE  =  0x00000C00; /* TODO: heap need for kernel?! */
/*----------------------------------------------------------------------------*/

MEMORY
{
    FLASH  (rx)  : ORIGIN = __FLASH_BASE,    LENGTH = __FLASH_SIZE
    DTCM   (rw) : ORIGIN = __DTCM_BASE,     LENGTH = __DTCM_SIZE

    /* Declare WORLDS memory regions (worlds_mem.lds) */

    WORLD1 (rx)  : ORIGIN = __FLASH_BASE_W1, LENGTH = __FLASH_SIZE_W1
    WORLD2 (rx)  : ORIGIN = __FLASH_BASE_W2, LENGTH = __FLASH_SIZE_W2
    WORLD3 (rx)  : ORIGIN = __FLASH_BASE_W3, LENGTH = __FLASH_SIZE_W3
    WORLD4 (rx)  : ORIGIN = __FLASH_BASE_W4, LENGTH = __FLASH_SIZE_W4
}

ENTRY(reset_handler)

SECTIONS
{
    
    .boot :
    {
        KEEP(*(.utango.boot));
        . = ALIGN(64);
        
        KEEP(*(.utango.vtb));
        __vtb_end = .;
        __vtb_size = ABSOLUTE(__vtb_end - _utango_vtb);
        

    } > FLASH
    
    /* Advance text_lma address to reflect the space needed for the vector table */
    /*. = . + __vtb_size; */
    __text_lma = .;

    .text :
    {
        /* Reserve space for relocation of vector table after boot */
        /* __vtb_start = .; */
        /* . = __vtb_size; */
        
        . = ALIGN(4);
        __text_start = .;

        *(.text*);
        *(.rodata*);
        KEEP(*(.eh_frame*));

        . = ALIGN(4);
        __text_end = .;
    } > FLASH AT>FLASH

    /* TODO: Possible need in the future
    .gnu.sgstubs :
    {
        . = ALIGN(32);
    } > FLASH
    */

    __data_vma_start = LOADADDR(.data);

    .data : 
    {
        . = ALIGN(4);
        __data_start = .;

        *(.data*);
        *(.utango.stack*);

        . = ALIGN(4);
        /*__data_end = .; */
    } > DTCM AT>FLASH

    .sdata :
    {
        *(.sdata*);
        __data_end = .;
    } > DTCM AT>FLASH

    .bss :
    {
        . = ALIGN(4);
        __bss_start__ = .;

        *(.bss*);
        *(COMMON);

        . = ALIGN(4);
        __bss_end__ = .;
    } > DTCM AT>DTCM

    .world1 :
    {
        KEEP(*(.world1*))
    } > WORLD1

    .world2 :
    {
        KEEP(*(.world2*))
    } > WORLD2

    .world3 :
    {
        KEEP(*(.world3*))
    } > WORLD3

    .world4 :
    {
        KEEP(*(.world4*))
    } > WORLD4

    .stack (ORIGIN(DTCM) + LENGTH(DTCM) - __STACK_SIZE) (COPY) :
    {
        . = ALIGN(8);
        __stack_lim = .;
        . = . + __STACK_SIZE;
        . = ALIGN(8);
        __stack_top = .;
    } > DTCM AT>DTCM
}
