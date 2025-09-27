/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM) + LENGTH(RAM); /* end of "RAM" Ram type memory */

_Min_Heap_Size = 0x200 ;  /* required amount of heap  */
_Min_Stack_Size = 0x400 ; /* required amount of stack */

INCLUDE memory_map.ld

/* Define output sections */
SECTIONS
{

  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >FLASH_BOOT

  /* Deprioritized interrupt table */
  .isr_vector_deprio :
  {
    . = ALIGN(128); /* Vector table must be aligneded with 128 bytes minimum */
    __isr_vector_deprio_start__ = .;
    KEEP(*(.isr_vector_deprio))
  } >FLASH_BOOT

  /* Section to contain TA1 objects, in this example the keylogger objects, that is accessible only by TA1 or TEE */
  .code_TA1 :
  { 
    . = ALIGN(4);
    /* Build/aes-ta.o(.text .text* .rodata .rodata* .constdata .constdata*)  /* Entry point object for TA1 which include GP Client API*/
    Build/bitcoin_wallet_ta.o(.text .text* .rodata .rodata* .constdata .constdata*)  /* Entry point object for TA1 which include GP Client API*/
    Build/TA/TA1/*.o(.text .text* .rodata .rodata* .constdata .constdata*) /* Other objects of TA1 */ 
    . = ALIGN(4); 
  } >FLASH_TA1

  /* Section to contain TA2 objects */
  .code_TA2 :
  { 
    . = ALIGN(4);
    Build/TA/TA2/*.o(.text .text* .rodata .rodata* .constdata .constdata*)  /* Entry point object for TA2 which include GP Client API*/ 
    Build/ta2.o(.text .text* .rodata .rodata* .constdata .constdata*)  /* Other objects of TA2 */ 
    . = ALIGN(4); 
  } >FLASH_TA2

  /* Section that contains the TEE code and libraries that should be accessible also by CA and TAs */
  .microvisor-nopri :
  {
    . = ALIGN(4);
    *(.microvisor-nopri)           /* .microvisor-nopri sections (code) */
    libc_a-*.o(.text .text*)      /* move libc function in this no priority area (so TAs can use standard functions like malloc, strcmp, etc.) */
    . = ALIGN(4);
  } >FLASH_BOOT_NOPRI


  /* The program code and other data goes into FLASH */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */

    *(EXCLUDE_FILE(Build/TA/*/.o).text .text* .rodata .rodata* .constdata .constdata*) /* Exclude the TAs code already include in other sections */

    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH_BOOT

  /* Reserved flash page for permanent storage */
  .flash_storage :
  {
    . = ALIGN(2048);  /* flash pages are aligned every 2Kb */
    __perma_storage_start__ = .;
    . = . + 1;        /* inscrease pointer by one for ALIGN */
    . = ALIGN(2048);  /* ALIGN to page flash boundry (for STM32L475 MCU) */
  } >FLASH_BOOT

  /* Constant data goes into FLASH */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH_BOOT

  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH_BOOT
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH_BOOT

  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH_BOOT
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH_BOOT
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH_BOOT

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .ram-boot :
  {
    . = ALIGN(4);
    KEEP (*(.ram-boot))
    . = ALIGN(4);
  } >RAM_BOOT

  /* used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* used by the startup to initialize TA1 data */
  _sidata_TA1 = LOADADDR(.data_TA1);

   /* used by the startup to initialize TA1 data */
  _sidata_TA2 = LOADADDR(.data_TA2);

  .data_TA1 :
  {
    . = ALIGN(4);
    _sdata_TA1 = .; 
    *(.data_TA1)
    /* Build/aes-ta.o(.data .data* .RamFunc .RamFunc*) /* Entry point object for TA1 which include GP Client API*/ 
    Build/bitcoin_wallet_ta.o(.data .data* .RamFunc .RamFunc*) /* Entry point object for TA1 which include GP Client API*/ 
    Build/TA/TA1/*.o(.data .data* .RamFunc .RamFunc*) /* Other objects of TA1 */ 
    . = ALIGN(4);
    _edata_TA1 = .;        /* define a global symbol at data end */
  } > RAM_TA1  AT> FLASH_TA1

  .data_TA2 :
  {
    . = ALIGN(4);
    _sdata_TA2 = .; 
    *(.data_TA2)
    Build/ta2.o(.data .data* .RamFunc .RamFunc*) /* Entry point object for TA2 which include GP Client API*/ 
    Build/TA/TA2/*.o(.data .data* .RamFunc .RamFunc*) /* Other objects of TA2 */ 
    . = ALIGN(4);
    _edata_TA2 = .;        /* define a global symbol at data end */
  } > RAM_TA2  AT> FLASH_TA2

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */
    *(.RamFunc)        /* .RamFunc sections */
    *(.RamFunc*)       /* .RamFunc* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RAM_BOOT AT> FLASH_BOOT

  /* Section to store the custom heap memory dedicated to TA1 */
  .heap_TA1 :
  {
    *(.heap_TA1)
  } > RAM_TA1

  /* Section to store the custom heap memory dedicated to TA2 */
  .heap_TA2 :
  {
    *(.heap_TA2)
  } > RAM_TA2

  /* Section to store the custom heap memory dedicated to TEE core */
  .heap_core :
  {
    *(.heap_core)
  } > RAM_BOOT

  /* RAM section to store data that should be accessible by boot TEE and TAs (e.g. passing parameters) */
  .TEE_TA_data :
  {
    *(.TEE_TA_data*);
  } > RAM

  /* Uninitialized data section (BSS) dedicated for TA1 */
  .bss_TA1 :
  {
    . = ALIGN(4);
    _sbss_TA1 = .;         /* define a global symbol at bss start */
    *(.bss_TA1)
    /* Build/aes-ta.o(.bss .bss*) */
    Build/bitcoin_wallet_ta.o(.bss .bss*)
    Build/TA/TA1/*.o(.bss .bss*)
    . = ALIGN(4);
    _ebss_TA1 = .;         /* define a global symbol at bss end */
  } > RAM_TA1

  /* Uninitialized data section (BSS) dedicated for TA2 */
  .bss_TA2 :
  {
    . = ALIGN(4);
    _sbss_TA2 = .; 
    *(.bss_TA2)
    Build/ta2.o(.bss .bss*)  /* Entry point object for TA2 which include GP Client API*/
    Build/TA/TA2/*.o(.bss .bss*) /* Other objects of TA2 */ 
    _ebss_TA2 = .;         /* define a global symbol at bss end */
    . = ALIGN(4);
  } > RAM_TA2

  /* Uninitialized data section */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM_BOOT

  ._boot_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM_BOOT

  /* User_heap_stack section, used to check that there is enough RAM left */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >RAM

  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0       : { *(.ARM.attributes) }
}
