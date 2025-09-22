#include "stm32l475vg_mpu.h"
#include "stm32l4xx_hal.h"
#include "bootloader.h"
#include "permanent_storage.h"
#include "error.h"
#include "PPB_recovery.h"


/**
 * Configures MPU
 * 
 * Higher regions number have more priority in the event of multi-matching,
 * this behavior is used to cover the regions in a coarse-grained approach
 * with higher numbered regions used to further restrict the access.
 * Setting a unique region for each section of memory map is not possible
 * since the regions cannot be of arbitrary size and must also be
 * naturally aligned.
 * 
 * Memory map based on the layout specified by STMicroelectronics in:
 * RM0434 - Multiprotocol wireless 32-bit MCU Arm®-based Cortex®-M4 with FPU, Bluetooth® Low-Energy and 802.15.4 radio solution
 */
void Configure_MPU(void) {
	MPU_Region_InitTypeDef MPU_InitStruct;

	/* Disable interrupts for critical section */
	__disable_irq();  

	/* Disable MPU */
	HAL_MPU_Disable();

	/************************************************************************/
	/* Flash Memory															*/
	/* Region 0		BASE = 0x08000000, SIZE = 0x100000						*/
	/************************************************************************/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	MPU_InitStruct.BaseAddress = 0x08000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_1MB;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;	// executable
	MPU_InitStruct.AccessPermission = MPU_REGION_PRIV_RW_URO;	// privileged read+write, unprivileged read only
	// the subregions for the two TAs (specifically the 2/3/4/5 - each of 128KB) should be disabled
	// value if binary: 0b00011110 = 0x1E
	MPU_InitStruct.SubRegionDisable = 0x1E;
	/* Cache properties and shareability  */
	/* Device type: Normal	Cache: WT */
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	/* Save configuration */
	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/************************************************************************/
	/* Bootloader Reserved Flash Memory										*/
	/* Region 1		BASE = 0x08000000, SIZE = 0x20000						*/
	/************************************************************************/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER1;
	MPU_InitStruct.BaseAddress = 0x08000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_128KB;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
	MPU_InitStruct.AccessPermission = MPU_REGION_PRIV_RW;
	MPU_InitStruct.SubRegionDisable = 0x00;
	/* Cache properties and shareability  */
	/* Device type: Normal	Cache: WT */
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	/* Save configuration */
	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/************************************************************************/
	/* RAM (region for both TAs)																	*/
	/* Region 2		BASE = 0x10000000, SIZE = 0x8000						*/
	/************************************************************************/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER2;
	MPU_InitStruct.BaseAddress = 0x10000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_32KB;	
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
	MPU_InitStruct.AccessPermission = MPU_REGION_PRIV_RW;	// privileged read+write
	MPU_InitStruct.SubRegionDisable = 0x00;
	/* Cache properties and shareability  */
	/* Device type: Normal	Cache: WBWA */
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
	/* Save configuration */
	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/************************************************************************/
	/* RAM	(region for user app)																*/
	/* Region 3		BASE = 0x20000000, SIZE = 0x8000						*/
	/************************************************************************/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER3;
	MPU_InitStruct.BaseAddress = 0x20000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_128KB; //It's 32kb but starting after the Bootloader reserved RAM whose region will have higher priority
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.SubRegionDisable = 0x00;
	/* Cache properties and shareability  */
	/* Device type: Normal	Cache: WBWA */
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
	/* Save configuration */
	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/************************************************************************/
	/* Bootloader Reserved RAM												*/
	/* Region 4		BASE = 0x20000000, SIZE = 0x10000							*/
	/************************************************************************/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER4;
	MPU_InitStruct.BaseAddress = 0x20000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_64KB;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
	MPU_InitStruct.AccessPermission = MPU_REGION_PRIV_RW;
	MPU_InitStruct.SubRegionDisable = 0x00;
	/* Cache properties and shareability  */
	/* Device type: Normal	Cache: WBWA */
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
	/* Save configuration */
	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/************************************************************************/
	/* Peripherals address space											*/
	/* Region 5		BASE = 0x40000000, SIZE = 0x40000000					*/
	/************************************************************************/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER5;
	MPU_InitStruct.BaseAddress = 0x40000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_1GB;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
	MPU_InitStruct.AccessPermission = MPU_REGION_PRIV_RW;
	//MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.SubRegionDisable = 0x00;
	/* Cache properties and shareability  */
	/* Device type: Device */
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL2;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	/* Save configuration */
	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/************************************************************************/
	/* Peripherals address space containuation								*/
	/* Region 6		BASE = 0x80000000, SIZE = 0x40000000					*/
	/************************************************************************/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER6;
	MPU_InitStruct.BaseAddress = 0x80000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_1GB;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
	MPU_InitStruct.AccessPermission = MPU_REGION_PRIV_RW;
	//MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;	// privileged read+write, unprivileged read only
	MPU_InitStruct.SubRegionDisable = 0x00;
	/* Cache properties and shareability  */
	/* Device type: Device */
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL2;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	/* Save configuration */
	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/************************************************************************/
	/* System memory, option bytes, OTP area								*/
	/* Region 7		BASE = 0x1fff0000, SIZE = 0x10000						*/
	/************************************************************************/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER7;
	MPU_InitStruct.BaseAddress = 0x1fff0000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_64KB;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;	// executable
	MPU_InitStruct.AccessPermission = MPU_REGION_PRIV_RW_URO;	// privileged read+write, unprivileged read only
	MPU_InitStruct.SubRegionDisable = 0x00;	// all subregions are enabled
	/* Cache properties and shareability  */
	/* Device type: Normal	Cache: WT */
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	/* Save configuration */
	HAL_MPU_ConfigRegion(&MPU_InitStruct);
	
	/* Enable MPU */
	/* MPU_PRIVILEGED_DEFAULT enable the backgroud region for priviledged processes */
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
	
	/* Enable interrupts */
	__enable_irq();  

	/* Enable MemManage exception */
	SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;
	__DSB();
	__ISB();
}

/**
 * Reconfigure the MPU to enable the execution of TA1 or TA2 based on the TA_number parameter
 * 
 * Higher regions number have more priority in the event of multi-matching,
 * this behavior is used to cover the regions in a coarse-grained approach
 * with higher numbered regions used to further restrict the access.
 * Setting a unique region for each section of memory map is not possible
 * since the regions cannot be of arbitrary size and must also be
 * naturally aligned.
 * 
 * Subregions disable is used to restrict the access to the memory and
 * flash regions of the other TAs and MCU Fortifier.
 * 
 * Memory map based on the layout specified by STMicroelectronics in:
 * RM0434 - Multiprotocol wireless 32-bit MCU Arm®-based Cortex®-M4 with FPU, Bluetooth® Low-Energy and 802.15.4 radio solution
 */
void Reconfigure_MPU(int TA_number) {
	MPU_Region_InitTypeDef MPU_InitStruct;

	/* Disable interrupts for critical section */
	__disable_irq();  
	/* Disable MPU */
	HAL_MPU_Disable();

	/************************************************************************/
	/* Flash Memory															*/
	/* Region 0		BASE = 0x08000000, SIZE = 0x100000						*/
	/************************************************************************/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER0;
	MPU_InitStruct.BaseAddress = 0x08000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_1MB;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;	// executable
	MPU_InitStruct.AccessPermission = MPU_REGION_PRIV_RW_URO;	// privileged read+write, unprivileged read only
	// the subregion for flashboot (specifically the 1) should be disabled
	// but it is not as there is a specific region for the bootloader that has priority 
	// and regulates the access 
	// the subregions for the other TA (each of 128KB) shold be disabled 
	// the ones of fortified app/boot no priority (specifically the 6/7/8) should be disabled but can not 
	// because the region boot no priority is used to perform the jump to the TAs 
	// and it is part of the last region togheter with the fortified app
	// NOTE: Subregion Disable - 0: subregion enabled; - 1: subregion disabled
	// NOTE: Subregions count is from 1 in this case (not 0)
	
	// CASE TA_NUMBER = 1
	// subregions for TA1 (specifically the 2/3) should be enabled
	// subregions for TA2 (specifically the 4/5) should be disabled
	// value in binary: 0b00011000 = 0x18
	// CASE TA_NUMBER = 2
	// subregions for TA1 (specifically the 2/3) should be disabled
	// subregions for TA2 (specifically the 4/5) should be enabled
	// value in binary: 0b00000110 = 0x6
	MPU_InitStruct.SubRegionDisable = (TA_number == 1) ? 0x18 : 0x6;
	/* Cache properties and shareability  */
	/* Device type: Normal	Cache: WT */
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	/* Save configuration */
	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/************************************************************************/
	/* Bootloader Reserved Flash Memory										*/
	/* Region 1		BASE = 0x08000000, SIZE = 0x20000						*/
	/************************************************************************/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER1;
	MPU_InitStruct.BaseAddress = 0x08000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_128KB;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
	MPU_InitStruct.AccessPermission = MPU_REGION_PRIV_RW;
	MPU_InitStruct.SubRegionDisable = 0x00;
	/* Cache properties and shareability  */
	/* Device type: Normal	Cache: WT */
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	/* Save configuration */
	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/************************************************************************/
	/* RAM (region for both TAs)																	*/
	/* Region 2		BASE = 0x10000000, SIZE = 0x8000						*/
	/************************************************************************/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER2;
	MPU_InitStruct.BaseAddress = 0x10000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_32KB;	// cannot create region of size 96KB, do immediately bigger one
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	// 1) give full access to the RAM of TAs
	// 2) disable the subregions dedicated to other TAs	
	// Region 32K -> each subregion is 4K
	// RAM 1 is 32K 
	// Case of 2 TA: 
	// Only TA 1 active: 0b11110000 = 0xF0; 
	// Only TA 2: 0b00001111 = 0x0F; 
	MPU_InitStruct.SubRegionDisable = (TA_number == 1) ? 0xF0 : 0x0F;
	/* Cache properties and shareability  */
	/* Device type: Normal	Cache: WBWA */
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
	/* Save configuration */
	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/************************************************************************/
	/* RAM	(region for user app)																*/
	/* Region 3		BASE = 0x20000000, SIZE = 0x8000						*/
	/************************************************************************/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER3;
	MPU_InitStruct.BaseAddress = 0x20000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_128KB;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
	// access is not disabled due to the current implementation of shared memory
	MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.SubRegionDisable = 0x00;
	/* Cache properties and shareability  */
	/* Device type: Normal	Cache: WBWA */
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
	/* Save configuration */
	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/************************************************************************/
	/* Bootloader Reserved RAM (RAM_BOOT)												*/
	/* Region 4		BASE = 0x20000000, SIZE = 0x10000							*/
	/************************************************************************/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER4;
	MPU_InitStruct.BaseAddress = 0x20000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_64KB;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
	MPU_InitStruct.AccessPermission = MPU_REGION_PRIV_RW;
	MPU_InitStruct.SubRegionDisable = 0x00;
	/* Cache properties and shareability  */
	/* Device type: Normal	Cache: WBWA */
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
	/* Save configuration */
	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/************************************************************************/
	/* Peripherals address space											*/
	/* Region 5		BASE = 0x40000000, SIZE = 0x40000000					*/
	/************************************************************************/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER5;
	MPU_InitStruct.BaseAddress = 0x40000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_1GB;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
	MPU_InitStruct.AccessPermission = MPU_REGION_PRIV_RW;
	//MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
	MPU_InitStruct.SubRegionDisable = 0x00;
	/* Cache properties and shareability  */
	/* Device type: Device */
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL2;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	/* Save configuration */
	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/************************************************************************/
	/* Peripherals address space containuation								*/
	/* Region 6		BASE = 0x80000000, SIZE = 0x40000000					*/
	/************************************************************************/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER6;
	MPU_InitStruct.BaseAddress = 0x80000000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_1GB;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
	MPU_InitStruct.AccessPermission = MPU_REGION_PRIV_RW;
	//MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;	// privileged read+write, unprivileged read only
	MPU_InitStruct.SubRegionDisable = 0x00;
	/* Cache properties and shareability  */
	/* Device type: Device */
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL2;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	/* Save configuration */
	HAL_MPU_ConfigRegion(&MPU_InitStruct);

	/************************************************************************/
	/* System memory, option bytes, OTP area								*/
	/* Region 7		BASE = 0x1fff0000, SIZE = 0x10000						*/
	/************************************************************************/
	MPU_InitStruct.Enable = MPU_REGION_ENABLE;
	MPU_InitStruct.Number = MPU_REGION_NUMBER7;
	MPU_InitStruct.BaseAddress = 0x1fff0000;
	MPU_InitStruct.Size = MPU_REGION_SIZE_64KB;
	MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;	// executable
	MPU_InitStruct.AccessPermission = MPU_REGION_PRIV_RW_URO;	// privileged read+write, unprivileged read only
	MPU_InitStruct.SubRegionDisable = 0x00;	// all subregions are enabled
	/* Cache properties and shareability  */
	/* Device type: Normal	Cache: WT */
	MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
	MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
	MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
	MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
	/* Save configuration */
	HAL_MPU_ConfigRegion(&MPU_InitStruct);
	
	/* Enable MPU */
	/* MPU_PRIVILEGED_DEFAULT enable the backgroud region for priviledged processes */
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

	/* Enable interrupts */
	__enable_irq();
	
	/* Enable MemManage exception */
	SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;
	__DSB();
	__ISB();
}

void microvisor_memmanage_handler(unsigned int *auto_frame, unsigned int *manual_frame) {

    // This could still be a legitimate access.
    // TODO: rename the checking function to be more general.
    if (PPB_RECOVERY_OK != Recover_PPB_Access(auto_frame, manual_frame)) {

        MPU_Violation_Handler(auto_frame, manual_frame);
        __builtin_unreachable();
    }

}

/**
 * Handler to be called when a Memory Protection Unit (MPU) violation occurs
 * 
 * @param auto_frame		Pointer to the automatic frame
 * @param manual_frame		Pointer to the manual frame
 */
void MPU_Violation_Handler(unsigned int* auto_frame, unsigned int* manual_frame) {
	unsigned int STK_Realign = __get_xPSR() & 0x100U;	// Bit 9 of xPSR indicate stack realingment operation during exception entry
	
	/* Compute significant register values */
	unsigned int PreEntry_SP = STK_Realign ? (unsigned int) auto_frame + 0x24 : (unsigned int) auto_frame + 0x20U;	// Recover original value of SP (before exception entry)
	unsigned int PreEntry_PC = auto_frame[6];
	unsigned int PreEntry_LR = auto_frame[5];

	/* Save error in permanent storage */
	uint32_t buffer[ERROR_MPU_VIOLATION_DATA_LEN];
	buffer[0] = SCB->CFSR;	// Configurable Fault Status Register (CFSR)
	buffer[1] = SCB->MMFAR;	// MemManage Fault Address Register (MMFAR)
	buffer[2] = SCB->BFAR;	// Bus Fault Address Register (BFAR)
	buffer[3] = PreEntry_SP;
	buffer[4] = PreEntry_LR;
	buffer[5] = PreEntry_PC;

	perma_storage_store_error(ERROR_MPU_VIOLATION, buffer, ERROR_MPU_VIOLATION_DATA_LEN);

	/* Clear CFSR */
	SCB->CFSR = 0xffffffffU;
	
	/* Reset the board */
	soft_reset();
}
