/* Define memory areas of MCU, including Bootloader and User Applicaiton areas */
MEMORY
{
FLASH_BOOT (rx)            : ORIGIN = 0x08000000, LENGTH = 0x20000  /* Microvisor reserved flash memory */
FLASH_BOOT_NOPRI (rx)      : ORIGIN = 0x08020000, LENGTH = 0x1000   /* Microvisor code running without privileges */
FLASH (rx)                 : ORIGIN = 0x08021000, LENGTH = 0xdf000  /* Flash memory for user application */
RAM_BOOT (xrw)             : ORIGIN = 0x20000000, LENGTH = 0x20     /* Reserved RAM used by the microvisor during user application runtime */
RAM (xrw)                  : ORIGIN = 0x20000020, LENGTH = 0x17FE0
RAM2 (xrw)                 : ORIGIN = 0x10000000, LENGTH = 32K
}


__flash_boot_start__ = ORIGIN(FLASH_BOOT);
__flash_boot_size__ = LENGTH(FLASH_BOOT);
__flash_boot_nopri_start__ = ORIGIN(FLASH_BOOT_NOPRI);
__flash_boot_nopri_size__ = LENGTH(FLASH_BOOT_NOPRI);
__flash_start__ = ORIGIN(FLASH);
__flash_size__ = LENGTH(FLASH);
__ram_boot_start__ = ORIGIN(RAM_BOOT);