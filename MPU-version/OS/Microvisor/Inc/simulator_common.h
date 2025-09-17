#ifndef __SIMULATOR_COMMON_H
#define __SIMULATOR_COMMON_H

#include <stddef.h>
#include <stdint.h>

#define BX_LR           0b0100011101110000

// PPB boundaries and components.
#define PPB_START       0xE0000000
#define PPB_END         0xE00FFFFF
#define PPB_MPU_START   0xE000ED94
#define PPB_MPU_END     0xE000EDEF

// Peripherals boundaries and components.
#define PERIPH_START    0x40000000
#define PERIPH_END      0xBFFFFFFF

// APB1 peripherals
#define APB1_START      0x40000000
#define APB1_END        0x400097FF

#define TIM2_START      0x40000000
#define TIM2_END        0x400003FF
#define TIM3_START      0x40000400
#define TIM3_END        0x400007FF
#define TIM4_START      0x40000800
#define TIM4_END        0x40000BFF
#define TIM5_START      0x40000C00
#define TIM5_END        0x40000FFF
#define TIM6_START      0x40001000
#define TIM6_END        0x400013FF
#define TIM7_START      0x40001400
#define TIM7_END        0x400017FF
#define TIM_START       TIM2_START
#define TIM_END         TIM7_END
#define LCD_START       0x40002400
#define LCD_END         0x400027FF
#define RTC_START       0x40002800
#define RTC_END			0x40002BFF
#define WWDC_START      0x40002C00
#define WWDC_END		0x40002FFF
#define IWDC_START      0x40003000
#define IWDC_END		0x400033FF
#define SPI2_START      0x40003800
#define SPI2_END		0x40003BFF
#define SPI3_START      0x40003C00
#define SPI3_END		0x40003FFF
#define USART2_START    0x40004400
#define USART2_END		0x400047FF
#define USART3_START    0x40004800
#define USART3_END		0x40004BFF
#define UART4_START     0x40004C00
#define UART4_END		0x40004FFF
#define UART5_START     0x40005000
#define UART5_END		0x400053FF
#define I2C1_START      0x40005400
#define I2C1_END		0x400057FF
#define I2C2_START      0x40005800
#define I2C2_END	    0x40005BFF
#define I2C3_START      0x40005C00
#define I2C3_END		0x40005FFF
#define CAN1_START      0x40006400
#define CAN1_END		0x400067FF
#define PWR_START       0x40007000
#define PWR_END			0x400073FF
#define DAC1_START      0x40007400
#define DAC1_END		0x400077FF
#define OPAMP_START     0x40007800
#define OPAMP_END		0x40007BFF
#define LPTIM1_START    0x40007C00
#define LPTIM1_END		0x40007FFF
#define LPUART1_START   0x40008000
#define LPUART1_END		0x400083FF
#define SWPMI1_START    0x40008800
#define SWPMI1_END		0x40008BFF
#define LPTIM2_START    0x40009400
#define LPTIM2_END		0x400097FF

// APB2 peripherals
#define APB2_START      0x40010000
#define APB2_END        0x400163FF

#define SYSCFG_START    0x40010000
#define SYSCFG_END		0x4001002F
#define VREFBUF_START	0x40010030
#define VREFBUF_END		0x400101FF
#define COMP_START		0x40010200
#define COMP_END		0x400103FF
#define EXTI_START		0x40010400
#define EXTI_END		0x400107FF
#define FIREWALL_START	0x40011C00
#define FIREWALL_END	0x40011FFF
#define SDMMC1_START	0x40012800
#define SDMMC1_END		0x40012BFF
#define TIM1_START		0x40012C00
#define TIM1_END		0x40012FFF
#define SPI1_START		0x40013000
#define SPI1_END		0x400133FF
#define TIM8_START		0x40013400
#define TIM8_END		0x400137FF
#define USART1_START	0x40013800
#define USART1_END		0x40013BFF
#define TIM15_START		0x40014000
#define TIM15_END		0x400143FF
#define TIM16_START		0x40014400
#define TIM16_END		0x400147FF
#define TIM17_START		0x40014800
#define TIM17_END		0x40014BFF
#define SAI1_START		0x40015400
#define SAI1_END		0x400157FF
#define SAI2_START		0x40015800
#define SAI2_END		0x40015BFF
#define DFSDM1_START	0x40016000
#define DFSDM1_END		0x400163FF

// AHB1 peripherals
#define AHB1_START      0x40020000
#define AHB1_END        0x400243FF

#define DMA1_START      0x40020000
#define DMA1_END		0x400203FF
#define DMA2_START      0x40020400
#define DMA2_END		0x400207FF
#define RCC_START       0x40021000
#define RCC_END			0x400213FF
#define FLASH_START     0x40022000
#define FLASH_END		0x400223FF
#define CRC_START       0x40023000
#define CRC_END			0x400233FF
#define TSC_START       0x40024000
#define TSC_END			0x400243FF

// AHB2 peripherals
#define AHB2_START      0x48000000
#define AHB2_END        0x50060BFF

#define GPIOA_START     0x48000000
#define GPIOA_END		0x480003FF
#define GPIOB_START     0x48000400
#define GPIOB_END		0x480007FF
#define GPIOC_START     0x48000800
#define GPIOC_END		0x48000BFF
#define GPIOD_START     0x48000C00
#define GPIOD_END		0x48000FFF
#define GPIOE_START     0x48001000
#define GPIOE_END		0x480013FF
#define GPIOF_START     0x48001400
#define GPIOF_END		0x480017FF
#define GPIOG_START     0x48001800
#define GPIOG_END		0x48001BFF
#define GPIOH_START     0x48001C00
#define GPIOH_END		0x48001FFF
#define GPIO_START      GPIOA_START
#define GPIO_END        GPIOH_END
#define OTG_FS_START    0x50000000
#define OTG_FS_END		0x5003FFFF
#define ADC_START       0x50040000
#define ADC_END			0x500403FF
#define AES_START       0x50060000
#define AES_END			0x500603FF
#define RNG_START       0x50060800
#define RNG_END			0x50060BFF

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
