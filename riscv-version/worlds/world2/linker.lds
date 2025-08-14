/* Copyright(C) 2020 Hex Five Security, Inc. - All Rights Reserved */

OUTPUT_ARCH( "riscv" )

ENTRY( _start )

MEMORY {
  flash (rx) : ORIGIN = __FLASH_BASE_W2 LENGTH = __FLASH_SIZE_W2
  ram   (rwa) : ORIGIN = __RAM_BASE_W2, LENGTH =  __RAM_SIZE_W2
}

SECTIONS {

  __stack_size = DEFINED(__stack_size) ? __stack_size : 1K;
  PROVIDE(__stack_size = __stack_size);


  /** Init / Fini related code | run once - loaded in slower memory **/

  .init : ALIGN(4)
  {
    KEEP(*(.vectors));
    KEEP (*(SORT_NONE(.init)))
  } >flash

  .fini : ALIGN(4)
  {
    KEEP (*(SORT_NONE(.fini)))
  } >flash

  .preinit_array : ALIGN(4) 
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >flash

  .init_array : ALIGN(4) 
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.init_array.*) SORT_BY_INIT_PRIORITY(.ctors.*)))
    KEEP (*(.init_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .ctors))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >flash

  .fini_array : ALIGN(4)
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT_BY_INIT_PRIORITY(.fini_array.*) SORT_BY_INIT_PRIORITY(.dtors.*)))
    KEEP (*(.fini_array EXCLUDE_FILE (*crtbegin.o *crtbegin?.o *crtend.o *crtend?.o ) .dtors))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >flash

  .ctors : ALIGN(4)
  {
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
  } >flash

  .dtors : ALIGN(4)
  {
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
  } >flash


  /** Text section | program - can be loaded to faster memory **/
  
  .text : ALIGN(4) 
  { 
    *(.text.unlikely .text.*_unlikely .text.unlikely.*)
    *(.text.exit .text.exit.*)
    *(.text.startup .text.startup.*)
    *(.text.hot .text.hot.*)
    *(SORT(.text.sorted.*))
    *(.text .stub .text.* .gnu.linkonce.t.*)
    /* .gnu.warning sections are handled specially by elf.em.  */
    *(.gnu.warning)
  } >flash

  PROVIDE (__etext = .);
  PROVIDE (_etext = .);
  PROVIDE (etext = .);

  .rodata : ALIGN(4)
  {
    *(.rdata)
    *(.rodata .rodata.*)
    *(.gnu.linkonce.r.*)
  } >flash


  /* Data section - copied from rom to ram */

  .lalign : ALIGN(4) 
  {
    PROVIDE( _data_lma = . );
  } >flash

  .data : ALIGN(4)    
  {
    __DATA_BEGIN__ = .;
    _data = .;
    *(.data .data.* .gnu.linkonce.d.*)
  } >ram AT>flash

  .sdata : ALIGN(4)    
  {
    PROVIDE( __global_pointer$ = . + 0x800 );
    __SDATA_BEGIN__ = .;
    *(.srodata.cst16) *(.srodata.cst8) *(.srodata.cst4) *(.srodata.cst2) *(.srodata .srodata.*)
    *(.sdata .sdata.* .sdata* .gnu.linkonce.s.*)
  } >ram AT>flash

  _edata = .; 
  PROVIDE (edata = .);

  .bss (NOLOAD): ALIGN(4)  
  {
    __bss_start = .;
    *(.sbss .sbss.* .gnu.linkonce.sb.*)
    *(.bss .bss.* .gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(. != 0 ? 4 : 1);
  } >ram

  . = ALIGN(4);
  . = SEGMENT_START("ldata-segment", .);
  . = ALIGN(4);
  __bss_end = .;
  __BSS_END__ = .;


  /* Stack definition - change size at top of this script */

  .stack (NOLOAD): ALIGN(16)  
  {
    . += __stack_size;
    PROVIDE( _sp = . );
  } >ram


  /* Heap definition - calculated to use the remaining memory */

  .heap (NOLOAD): ALIGN(4)  
  {
    PROVIDE( _end = . );
    PROVIDE( __end = . );
    PROVIDE( __heap_start = . );
    . += LENGTH(ram) - ( . - ORIGIN(ram));
    PROVIDE( _heap_end = . );
    PROVIDE( __heap_end = . );
  } >ram
}