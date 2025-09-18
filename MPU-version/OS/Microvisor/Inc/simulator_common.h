#ifndef __SIMULATOR_COMMON_H
#define __SIMULATOR_COMMON_H

#include <stddef.h>
#include <stdint.h>

#define BX_LR                   0b0100011101110000

// PPB boundaries and components.
#define PPB_START               0xE0000000
#define PPB_END                 0xE00FFFFF
#define PPB_MPU_START           0xE000ED94
#define PPB_MPU_END             0xE000EDEF

// Peripherals boundaries and components.
#define PERIPH_START            0x40000000
#define PERIPH_END              0xBFFFFFFF

// APB1 peripherals
#define APB1_START              0x40000000
#define APB1_END                0x400097FF

#define PERIPH_TIM2_START       0x40000000
#define PERIPH_TIM2_END         0x400003FF
#define PERIPH_TIM3_START       0x40000400
#define PERIPH_TIM3_END         0x400007FF
#define PERIPH_TIM4_START       0x40000800
#define PERIPH_TIM4_END         0x40000BFF
#define PERIPH_TIM5_START       0x40000C00
#define PERIPH_TIM5_END         0x40000FFF
#define PERIPH_TIM6_START       0x40001000
#define PERIPH_TIM6_END         0x400013FF
#define PERIPH_TIM7_START       0x40001400
#define PERIPH_TIM7_END         0x400017FF
#define PERIPH_LCD_START        0x40002400
#define PERIPH_LCD_END          0x400027FF
#define PERIPH_RTC_START        0x40002800
#define PERIPH_RTC_END		    0x40002BFF
#define PERIPH_WWDC_START       0x40002C00
#define PERIPH_WWDC_END		    0x40002FFF
#define PERIPH_IWDC_START       0x40003000
#define PERIPH_IWDC_END		    0x400033FF
#define PERIPH_SPI2_START       0x40003800
#define PERIPH_SPI2_END		    0x40003BFF
#define PERIPH_SPI3_START       0x40003C00
#define PERIPH_SPI3_END		    0x40003FFF
#define PERIPH_USART2_START     0x40004400
#define PERIPH_USART2_END	    0x400047FF
#define PERIPH_USART3_START     0x40004800
#define PERIPH_USART3_END	    0x40004BFF
#define PERIPH_UART4_START      0x40004C00
#define PERIPH_UART4_END	    0x40004FFF
#define PERIPH_UART5_START      0x40005000
#define PERIPH_UART5_END	    0x400053FF
#define PERIPH_I2C1_START       0x40005400
#define PERIPH_I2C1_END		    0x400057FF
#define PERIPH_I2C2_START       0x40005800
#define PERIPH_I2C2_END	        0x40005BFF
#define PERIPH_I2C3_START       0x40005C00
#define PERIPH_I2C3_END		    0x40005FFF
#define PERIPH_CAN1_START       0x40006400
#define PERIPH_CAN1_END		    0x400067FF
#define PERIPH_PWR_START        0x40007000
#define PERIPH_PWR_END		    0x400073FF
#define PERIPH_DAC1_START       0x40007400
#define PERIPH_DAC1_END		    0x400077FF
#define PERIPH_OPAMP_START      0x40007800
#define PERIPH_OPAMP_END	    0x40007BFF
#define PERIPH_LPTIM1_START     0x40007C00
#define PERIPH_LPTIM1_END	    0x40007FFF
#define PERIPH_LPUART1_START    0x40008000
#define PERIPH_LPUART1_END	    0x400083FF
#define PERIPH_SWPMI1_START     0x40008800
#define PERIPH_SWPMI1_END	    0x40008BFF
#define PERIPH_LPTIM2_START     0x40009400
#define PERIPH_LPTIM2_END	    0x400097FF

// APB2 peripherals
#define APB2_START              0x40010000
#define APB2_END                0x400163FF

#define PERIPH_SYSCFG_START     0x40010000
#define PERIPH_SYSCFG_END		0x4001002F
#define PERIPH_VREFBUF_START	0x40010030
#define PERIPH_VREFBUF_END		0x400101FF
#define PERIPH_COMP_START		0x40010200
#define PERIPH_COMP_END		    0x400103FF
#define PERIPH_EXTI_START		0x40010400
#define PERIPH_EXTI_END		    0x400107FF
#define PERIPH_FIREWALL_START	0x40011C00
#define PERIPH_FIREWALL_END	    0x40011FFF
#define PERIPH_SDMMC1_START	    0x40012800
#define PERIPH_SDMMC1_END		0x40012BFF
#define PERIPH_TIM1_START		0x40012C00
#define PERIPH_TIM1_END		    0x40012FFF
#define PERIPH_SPI1_START		0x40013000
#define PERIPH_SPI1_END		    0x400133FF
#define PERIPH_TIM8_START		0x40013400
#define PERIPH_TIM8_END		    0x400137FF
#define PERIPH_USART1_START	    0x40013800
#define PERIPH_USART1_END		0x40013BFF
#define PERIPH_TIM15_START		0x40014000
#define PERIPH_TIM15_END		0x400143FF
#define PERIPH_TIM16_START		0x40014400
#define PERIPH_TIM16_END		0x400147FF
#define PERIPH_TIM17_START		0x40014800
#define PERIPH_TIM17_END		0x40014BFF
#define PERIPH_SAI1_START		0x40015400
#define PERIPH_SAI1_END		    0x400157FF
#define PERIPH_SAI2_START		0x40015800
#define PERIPH_SAI2_END		    0x40015BFF
#define PERIPH_DFSDM1_START	    0x40016000
#define PERIPH_DFSDM1_END		0x400163FF

// AHB1 peripherals
#define AHB1_START              0x40020000
#define AHB1_END                0x400243FF

#define PERIPH_DMA1_START       0x40020000
#define PERIPH_DMA1_END		    0x400203FF
#define PERIPH_DMA2_START       0x40020400
#define PERIPH_DMA2_END		    0x400207FF
#define PERIPH_RCC_START        0x40021000
#define PERIPH_RCC_END			0x400213FF
#define PERIPH_FLASH_START      0x40022000
#define PERIPH_FLASH_END		0x400223FF
#define PERIPH_CRC_START        0x40023000
#define PERIPH_CRC_END			0x400233FF
#define PERIPH_TSC_START        0x40024000
#define PERIPH_TSC_END			0x400243FF

// AHB2 peripherals
#define AHB2_START              0x48000000
#define AHB2_END                0x50060BFF

#define PERIPH_GPIOA_START      0x48000000
#define PERIPH_GPIOA_END		0x480003FF
#define PERIPH_GPIOB_START      0x48000400
#define PERIPH_GPIOB_END		0x480007FF
#define PERIPH_GPIOC_START      0x48000800
#define PERIPH_GPIOC_END		0x48000BFF
#define PERIPH_GPIOD_START      0x48000C00
#define PERIPH_GPIOD_END		0x48000FFF
#define PERIPH_GPIOE_START      0x48001000
#define PERIPH_GPIOE_END		0x480013FF
#define PERIPH_GPIOF_START      0x48001400
#define PERIPH_GPIOF_END		0x480017FF
#define PERIPH_GPIOG_START      0x48001800
#define PERIPH_GPIOG_END		0x48001BFF
#define PERIPH_GPIOH_START      0x48001C00
#define PERIPH_GPIOH_END		0x48001FFF
#define PERIPH_OTG_FS_START     0x50000000
#define PERIPH_OTG_FS_END		0x5003FFFF
#define PERIPH_ADC_START        0x50040000
#define PERIPH_ADC_END			0x500403FF
#define PERIPH_AES_START        0x50060000
#define PERIPH_AES_END			0x500603FF
#define PERIPH_RNG_START        0x50060800
#define PERIPH_RNG_END			0x50060BFF

/* Access permissions */
#define SIMULATOR_RW            0	// read and write access
#define SIMULATOR_RO_WI         1	// read-only, write-ignored access
#define SIMULATOR_NO_ACCESS     2	// no access


/* Empty function, used only in the startup file */
void LoopForever();

/* Functions to get/set the values of the registers */
uint32_t Get_Register_Value(unsigned int reg_num, unsigned int* auto_frame, unsigned int* manual_frame);
void Set_Register_Value(unsigned int reg_num, unsigned int* auto_frame, unsigned int* manual_frame, unsigned int value);

/* Functions to simulate instruction with context */
void Simulate_Faulty_Instruction(unsigned int* auto_frame, unsigned int* manual_frame, size_t halfword_count, uint32_t inst);

/* Function if the address provided is part of the PPB */
int Is_PPB_Address_Valid(unsigned int target_address);

/* Functions to retrieve the permissions of a simulated function on a given address */
uint32_t Simulator_Get_Permission(uint32_t target_address);


/**
 * @brief   Get the instruction allocated at the given address.
 *          Since in thumb mode instructions can be of 16 or 32 bytes, a word is returned.
 *          The actual number of bytes is put in inst_len.
 *
 * @param   address: The starting address of the instruction to extract
 * @param   halfword_count: The variable where the actual instruction length in halfwords is put (1 or 2).
 *
 * @return  The instruction as a word. In case the instruction was an halfword, it is zero-extended.
 *          In case the instruction was a double halfword, the first halfword is in the upper bits
 *          and the second one in the lower ones.
 *          This doesn't serialize correctly in little-endian systems.
 */
uint32_t get_instruction_at(const uint16_t *address, size_t *halfword_count);


#endif /* __SIMULATOR_COMMON_H */
