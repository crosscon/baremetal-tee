/* Define memory areas of MCU, including Bootloader and User Applicaiton areas */
MEMORY
{
FLASH_BOOT (rx)        	   : ORIGIN = 0x08000000, LENGTH = 0x20000   /* Microvisor reserved flash memory */
FLASH_TA1 (rx)             : ORIGIN = 0x08020000, LENGTH = 0x3C000   /* Flash memory for first TA */
FLASH_SECURE_TA1(rw)       : ORIGIN = 0x0805C000, LENGTH = 0x4000    /* Secure Storage (flash memory) for first TA */
FLASH_TA2 (rx)             : ORIGIN = 0x08060000, LENGTH = 0x3C000   /* Flash memory for second TA */
FLASH_SECURE_TA2(rw)       : ORIGIN = 0x0809C000, LENGTH = 0x4000    /* Secure Storage (flash memory) for second TA */
FLASH (rx)                 : ORIGIN = 0x080A0000, LENGTH = 0x58000   /* Flash memory for user application */
FLASH_BOOT_NOPRI (rx)      : ORIGIN = 0x080F8000, LENGTH = 0x8000    /* Microvisor code running without privileges */
RAM_TA1 (xrw)              : ORIGIN = 0x10000000, LENGTH = 0x4000 	 /* RAM for the first TA */
RAM_TA2 (xrw)              : ORIGIN = 0x10004000, LENGTH = 0x4000    /* RAM for the second TA */
RAM_BOOT (xrw)       	   : ORIGIN = 0x20000000, LENGTH = 0x10000   /* Reserved RAM used by the microvisor during user application runtime  */
RAM (xrw)                  : ORIGIN = 0x20010000, LENGTH = 0x8000    /* RAM for the user application */
}


__flash_boot_start__ = ORIGIN(FLASH_BOOT);
__flash_boot_size__ = LENGTH(FLASH_BOOT);
__flash_boot_nopri_start__ = ORIGIN(FLASH_BOOT_NOPRI);
__flash_boot_nopri_size__ = LENGTH(FLASH_BOOT_NOPRI);
__flash_start__ = ORIGIN(FLASH);
__flash_size__ = LENGTH(FLASH);
__flash_TA1_start__ = ORIGIN(FLASH_TA1);
__flash_TA1_size__ = LENGTH(FLASH_TA1);
__flash_TA2_start__ = ORIGIN(FLASH_TA2);
__flash_TA2_size__ = LENGTH(FLASH_TA2);
__flash_secure_TA1_start__ = ORIGIN(FLASH_SECURE_TA1);
__flash_secure_TA1_size__ = LENGTH(FLASH_SECURE_TA1);
__flash_secure_TA2_start__ = ORIGIN(FLASH_SECURE_TA2);
__flash_secure_TA2_size__ = LENGTH(FLASH_SECURE_TA2);


__ram_boot_start__ = ORIGIN(RAM_BOOT);