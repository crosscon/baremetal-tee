#include "simulator_common.h"
#include "PPB_recovery.h"
#include "bootloader.h"
#include <stdlib.h>


#define IF_GUARD(name, address) \
    if (PERIPH_ ## name ## _START <= address && address <= PERIPH_ ## name ## _END)




/**
 * RAM region for instruction simulation
 * Requires 1 word and 1 halfword:
 * - word (32 bit) required for instruction being simulated (at most 32 bit instruction)
 * - halfword (16 bit) required for return (BX LR always 16 bit)
 * */
unsigned short __attribute__((section(".ram-boot"))) simulation_mem[3];

/**
 * Returns value of register before exception occurrance (reading appropriate frame).
 * Values of PC and SP should never be used inside instruction
 * as their original behavior cannot be reproduced
 * (PC-relative addressing does not make sense in a different context)
 * (reading/writing value to SP would use/corrupt our current stack)
 * 
 * Parameters:
 * reg_num: number of the register to read
 * auto_frame: pointer to auto_frame (frame created automatically during exception entry)
 * manual_frame: pointer to manual_frame (frame created manually containing rest of context)
 * 
 * Returns: 
 * value of the register before exception occurrance
 * 
 * Note:
 * Auto_frame contains: R0-R3 (pos 0-3), R12 (pos 4), LR (pos 5), PC (pos 6), xPSR (Program Status Register - pos 7)
 * Manual_frame contains: R4-R11 (pos 0-7), EXC_RETURN (pos 8) 
 */
uint32_t Get_Register_Value(unsigned int reg_num, unsigned int* auto_frame, unsigned int* manual_frame) {
	uint32_t value = 0;
	uint32_t stack_realigned;
	switch (reg_num)
		{
		case 0:
		case 1:
		case 2:
		case 3:
			// recover value from auto_frame
			value = auto_frame[reg_num];
			break;
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
			// recover value from manual_frame
			value = manual_frame[reg_num - 4];
			break;
		case 12:
			// recover value from auto_frame
			value = auto_frame[4];
			break;
		case 13:	// SP prior to exception entry
			stack_realigned = (auto_frame[7] & 0b1000000000) >> 9;	// extract stack realignment bit (bit 9) from xPSR value
			if(stack_realigned)
				value = (uint32_t) &auto_frame[9];	// additional 4 byte realignemnt performed
			else
				value = (uint32_t) &auto_frame[8]; 
			break;
		case 14:	// LR
			value = auto_frame[5];
			break;
		case 15:	// ReturnAddress (PC prior to exception entry)
			value = auto_frame[6];
			break;
		default:
			/* Default case */
			__BKPT();
			break;
		}
	return value;
}

/**
 * Sets value of register before exception occurrance (writing appropriate frame).
 * The value of SP cannot be changed since is not stored explicitely on any frame.
 * Using reg_num==15 (PC) changes the ReturnAddress stored on the stack.
 * 
 * Parameters:
 * reg_num: number of the register to write
 * auto_frame: pointer to auto_frame (frame created automatically during exception entry)
 * manual_frame: pointer to manual_frame (frame created manually containing rest of context)
 * 
 * Note: see the comment for Get_Register_Value to understand the frames structure
 */
void Set_Register_Value(unsigned int reg_num, unsigned int* auto_frame, unsigned int* manual_frame, unsigned int value) {
	switch (reg_num)
		{
		case 0:
			/* fall-through */
		case 1:
			/* fall-through */
		case 2:
			/* fall-through */
		case 3:
			/* write value to auto_frame */
			auto_frame[reg_num] = value;
			break;
		case 4:
			/* fall-through */
		case 5:
			/* fall-through */
		case 6:
			/* fall-through */
		case 7:
			/* fall-through */
		case 8:
			/* fall-through */
		case 9:
			/* fall-through */
		case 10:
			/* fall-through */
		case 11:
			/* write value to manual_frame */
			manual_frame[reg_num - 4] = value;
			break;
		case 12:
			/* write value to auto_frame */
			auto_frame[4] = value;
			break;
		case 13:
			/* SP value cannot be changed as is not stored explicitely */
			__BKPT();
			soft_reset();
			break;
		case 14:
			/* write value to auto_frame */
			auto_frame[5] = value;
			break;
		case 15:
			/* write new ReturnAddress to auto_frame */
			auto_frame[6] = value;
			break;
		default:
			/* Default case */
			__BKPT();
			soft_reset();
		}
	return;
}

/**
 * Executes an in-memory routine ensuring the context
 * is the one before the exception entry (except for registers SP,LR and PC).
 * Additionally before returning the functions saves the modified context onto
 * the pointers and restores all the callee-preserved registers to their original
 * value, thus complying with the AAPCS.
 * 
 * Parameters:
 *  - address: memory location of the in memory routine
 *  - auto_frame: pointer to auto_frame
 *  - manual_frame: pointer to manual_frame
 * 
 */
__attribute__((naked))
static void Run_With_Context(unsigned int* address, unsigned int* auto_frame, unsigned int* manual_frame) {
	__asm__(
		"push {r4,r5,r6,r7,r8,r9,r10,r11,lr}\n"	// save callee-preserved registers into the stack
		"push {r1, r2}\n"						// save auto_frame and manual_frame adresses into the stack
		"mov lr, r0\n"							// mov function address to LR
		"mov r12, r1\n"							// mov auto_frame address to R12
		"mov r11, r2\n"							// mov manual_fram address to R11
		
		/* Restore context */
		"ldr r0, [r12, #28]\n"	  // read stacked APSR (Application Program Status Register)
		"msr APSR_nzcvq, r0\n"	  // restore APSR
		"ldm r12, {r0,r1,r2,r3,r12}\n"
		"ldm r11, {r4,r5,r6,r7,r8,r9,r10,r11}\n"
		
		/* Branch to in-memory routine */
		"orr lr, #1\n"	// thumb instruction set bit
		"blx lr\n"   // branch to in-memory routine to execute it

        // TODO: if LR or PC is modified by the simulated instruction: possible arbitrary (privileged) code execution.
        // TODO: if the SP (MSP) is modified by the instruction: possible adversary-controlled behaviour (privilege escalation).

		/* Save modified context */
		"ldr lr, [sp]\n"				// load auto_frame address to LR
		"stm lr, {r0,r1,r2,r3,r12}\n"	// save modified r0,r1,r2,r3,r12
		"mrs r0, APSR\n"				// read updated APSR
		"ldr r1, [lr, #28]\n"			// read stacked xPSR
		"and r1, #0x07ffffff\n"			// zero all APSR-relative bits
		"orr r0, r0, r1\n"				// compute final xPSR value
		"str r0, [lr, #28]\n"			// update stacked xPSR
		"ldr lr, [sp, 4]\n"				// load manual_fram address to LR
		"stm lr, {r4,r5,r6,r7,r8,r9,r10,r11}\n"	// save modified r4-r11
		
		/* Cleanup and return */
		"pop {r1,r2}\n"		// pop auto_frame and manual_frame values stored in stack
		"pop {r4,r5,r6,r7,r8,r9,r10,r11,lr}\n"	//restore callee-reserved registers
		"bx lr\n"			// return
	);
}

/**
 * @brief   Executes the faulty instuction with the original context (except for registers SP,LR and PC)
 *          Advances the stacked PC (created on exception entry) by the instruction lenght
 *          to ensure the continuation of the execution after returning from exception.
 *          The instruction to simulate is the one stored in the PC register (position 6 of the auto_frame).
 * 
 * @param auto_frame: frame created automatically during exception entry
 * @param manual_frame: frame created manually containing rest of context
 * @param halfword_count: the number of halfword the instruction is composed of (1 or 2).
 * @param inst: the instruction to simulate, this can be both a single halfword or double halfword.
 *              In case of a single halfword, the halfword is stored on the lower bits.
 *              In case of a double halfword, the first halfword is stored on the higher bits.
 *              The instruction should be fetched once to avoid TOCTOU.
 *
 * @warning The caller must ensure that the instruction doesn't modify SP, LR and PC.
 * 
 * // TODO: void doesn't return.
 *
 * Returns:
 * SIMULATION_OK: if the simulation was successful
 * SIMULATION_NOMEM: if there was no memory available for the in-memory function
 *
 */
void Simulate_Faulty_Instruction(unsigned int* auto_frame, unsigned int* manual_frame, size_t halfword_count, uint32_t inst) {
	/* Allocate space for in-memory function */
	uint16_t* funct_ptr = simulation_mem;  // create pointer to simulation memory

    switch (halfword_count) {
        case 2:
            funct_ptr[0] = (inst >> 16) & 0xFFFF;
            /* fall-through */
        case 1:
            funct_ptr[halfword_count - 1] = inst & 0xFFFF;
            break;
        default:
            return /* SIMULATION_NOMEM */;
    }

	/* Add return to function (BX LR) */
	funct_ptr[halfword_count] = BX_LR & 0xFFFF;

	/* Execute in-memory function */
	Run_With_Context((unsigned int*) funct_ptr, auto_frame, manual_frame);

	/* Advance auto_frame PC to next instruction */
	auto_frame[6] = (uintptr_t) ((uint16_t*) (uintptr_t) auto_frame[6] + halfword_count);

	return /* SIMULATION_OK */;
}

/**
 * Checks the address trying to be accessed in order to verify if it is compliant with the ACP (Access Control Policy)
 * In particular, the address should be part of the PPB (Private Peripherals Bus) and not part of the other MPU areas
 * 
 * Parameters:
 * target_address: address to be tested for access
 * 
 * Returns:
 * - 0 for an invalid address (outside PPB, MPU control)
 * - 1 for a valid address (remaining PPB)
 */
int Is_PPB_Address_Valid(unsigned int target_address) {
	if(PPB_START <= target_address && target_address <= PPB_END) {
		if(PPB_MPU_START <= target_address && target_address <= PPB_MPU_END)	// invalid when trying to access MPU settings
			return 0;
		return 1;	// valid for rest of PPB access
	}
	return 0;	// invalid when outside PPB (this function only handles PPB accesses)
}


/**
 * Retrieves the permissions of a simulated function on a given address
 *
 * Parameters:
 * target_address: address to be tested for access
 *
 * Returns:
 * - SIMULATOR_RW for read and write access
 * - SIMULATOR_RO_WI for read-only, write-ignored access
 * - SIMULATOR_NO_ACCESS for no access
 */
uint32_t Simulator_Get_Permission(uint32_t target_address) {

#if ACCESS_PPB
    // TODO: Maybe a whitelist is more appropriate.
    // I'm not sure this blacklist considered all the PPB except for the SCB.
	if(PPB_START <= target_address && target_address <= PPB_END) {
		if(PPB_MPU_START <= target_address && target_address <= PPB_MPU_END)	// access to MPU configuration not allowed
			return SIMULATOR_NO_ACCESS;
        // TODO: an attacker could write just one of the bytes of the PPB at different addresses.
		if(target_address == (uint32_t) &(SCB->VTOR))	// block write access to VTOR
			return SIMULATOR_RO_WI;
		return SIMULATOR_RW;	// allow other accesses (inside the PPB)
	}
#endif /* ACCESS_PPB */

    // Checks to avoid loosing time searching for the peripheral if already out
    // of the peripheral space.
    if (PERIPH_START <= target_address && target_address <= PERIPH_END) {

        // TODO: This peripheral whitelisting is just a proof of work.
        // Only the DMAs have been addressed.

        // Segmented in regions for faster lookup with many peripherals activated.
        // This granularity level is arbitrary.

        if (APB1_START <= target_address && target_address <= APB1_END) {

#if ACCESS_TIM2 || ACCESS_TIM
            IF_GUARD(TIM2, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_TIM2 */
#if ACCESS_TIM3 || ACCESS_TIM
            IF_GUARD(TIM3, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_TIM3 */
#if ACCESS_TIM4 || ACCESS_TIM
            IF_GUARD(TIM4, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_TIM4 */
#if ACCESS_TIM5 || ACCESS_TIM
            IF_GUARD(TIM5, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_TIM5 */
#if ACCESS_TIM6 || ACCESS_TIM
            IF_GUARD(TIM6, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_TIM6 */
#if ACCESS_TIM7 || ACCESS_TIM
            IF_GUARD(TIM7, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_TIM7 */
#if ACCESS_LCD
            IF_GUARD(LCD, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_LCD */
#if ACCESS_RTC
            IF_GUARD(RTC, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_RTC */
#if ACCESS_WWDC
            IF_GUARD(WWDC, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_WWDC */
#if ACCESS_IWDC
            IF_GUARD(IWDC, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_IWDC */
#if ACCESS_SPI2 || ACCESS_SPI
            IF_GUARD(SPI2, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_SPI2 */
#if ACCESS_SPI3 || ACCESS_SPI
            IF_GUARD(SPI3, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_SPI3 */
#if ACCESS_USART2 || ACCESS_UART
            IF_GUARD(USART2, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_USART2 */
#if ACCESS_USART3 || ACCESS_UART
            IF_GUARD(USART3, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_USART3 */
#if ACCESS_UART4 || ACCESS_UART
            IF_GUARD(UART4, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_UART4 */
#if ACCESS_UART5 || ACCESS_UART
            IF_GUARD(UART5, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_UART5 */
#if ACCESS_I2C1 || ACCESS_I2C
            IF_GUARD(I2C1, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_I2C1 */
#if ACCESS_I2C2 || ACCESS_I2C
            IF_GUARD(I2C2, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_I2C2 */
#if ACCESS_I2C3 || ACCESS_I2C
            IF_GUARD(I2C3, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_I2C3 */
#if ACCESS_CAN1 || ACCESS_CAN
            IF_GUARD(CAN1, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_CAN1 */
#if ACCESS_PWR
            IF_GUARD(PWR, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_PWR */
#if ACCESS_DAC1 || ACCESS_DAC
            IF_GUARD(DAC1, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_DAC1 */
#if ACCESS_OPAMP
            IF_GUARD(OPAMP, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_OPAMP */
#if ACCESS_LPTIM1 || ACCESS_TIM
            IF_GUARD(LPTIM1, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_LPTIM1 */
#if ACCESS_LPUART1 || ACCESS_UART
            IF_GUARD(LPUART1, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_LPUART1 */
#if ACCESS_SWPMI1 || ACCESS_SWPMI
            IF_GUARD(SWPMI1, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_SWPMI1 */
#if ACCESS_LPTIM2 || ACCESS_TIM
            IF_GUARD(LPTIM2, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_LPTIM2 */

        } else if (APB2_START <= target_address && target_address <= APB2_END) {

#if ACCESS_SYSCFG
            IF_GUARD(SYSCFG, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_SYSCFG */
#if ACCESS_VREFBUF
            IF_GUARD(VREFBUF, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_VREFBUF */
#if ACCESS_COMP
            IF_GUARD(COMP, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_COMP */
#if ACCESS_EXTI
            IF_GUARD(EXTI, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_EXTI */
#if ACCESS_FIREWALL
            IF_GUARD(FIREWALL, target_address) {
                return SIMULATOR_RO;
            }
#endif /* ACCESS_FIREWALL */
#if ACCESS_SDMMC1 || ACCESS_SDMMC
            IF_GUARD(SDMMC1, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_SDMMC1 */
#if ACCESS_TIM1 || ACCESS_TIM
            IF_GUARD(TIM1, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_TIM1 */
#if ACCESS_SPI1 || ACCESS_SPI
            IF_GUARD(SPI1, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_SPI1 */
#if ACCESS_TIM8 || ACCESS_TIM
            IF_GUARD(TIM8, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_TIM8 */
#if ACCESS_USART1 || ACCESS_UART
            IF_GUARD(USART1, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_USART1 */
#if ACCESS_TIM15 || ACCESS_TIM
            IF_GUARD(TIM15, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_TIM15 */
#if ACCESS_TIM16 || ACCESS_TIM
            IF_GUARD(TIM16, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_TIM16 */
#if ACCESS_TIM17 || ACCESS_TIM
            IF_GUARD(TIM17, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_TIM17 */
#if ACCESS_SAI1 || ACCESS_SAI
            IF_GUARD(SAI1, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_SAI1 */
#if ACCESS_SAI2 || ACCESS_SAI
            IF_GUARD(SAI2, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_SAI2 */
#if ACCESS_DFSDM1 || ACCESS_DFSDM
            IF_GUARD(DFSDM1, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_DFSDM1 */

        } else if (AHB1_START <= target_address && target_address <= AHB1_END) {

#if ACCESS_DMA1 || ACCESS_DMA
            IF_GUARD(DMA1, target_address) {
                return SIMULATOR_SPECIAL_DMA;
            }
#endif /* ACCESS_DMA1 */
#if ACCESS_DMA2 || ACCESS_DMA
            IF_GUARD(DMA2, target_address) {
                return SIMULATOR_SPECIAL_DMA;
            }
#endif /* ACCESS_DMA2 */
#if ACCESS_RCC
            IF_GUARD(RCC, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_RCC */
#if ACCESS_FLASH
            IF_GUARD(FLASH, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_FLASH */
#if ACCESS_CRC
            IF_GUARD(CRC, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_CRC */
#if ACCESS_TSC
            IF_GUARD(TSC, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_TSC */

        } else if (AHB2_START <= target_address && target_address <= AHB2_END) {

#if ACCESS_GPIOA || ACCESS_GPIO
            IF_GUARD(GPIOA, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_GPIOA */
#if ACCESS_GPIOB || ACCESS_GPIO
            IF_GUARD(GPIOB, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_GPIOB */
#if ACCESS_GPIOC || ACCESS_GPIO
            IF_GUARD(GPIOC, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_GPIOC */
#if ACCESS_GPIOD || ACCESS_GPIO
            IF_GUARD(GPIOD, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_GPIOD */
#if ACCESS_GPIOE || ACCESS_GPIO
            IF_GUARD(GPIOE, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_GPIOE */
#if ACCESS_GPIOF || ACCESS_GPIO
            IF_GUARD(GPIOF, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_GPIOF */
#if ACCESS_GPIOG || ACCESS_GPIO
            IF_GUARD(GPIOG, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_GPIOG */
#if ACCESS_GPIOH || ACCESS_GPIO
            IF_GUARD(GPIOH, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_GPIOH */
#if ACCESS_OTG_FS
            IF_GUARD(OTG_FS, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_OTG_FS */
#if ACCESS_ADC
            IF_GUARD(ADC, target_address) {
                return SIMULATOR_RW;
            }
#endif /* ACCESS_ADC */
#if ACCESS_AES
            IF_GUARD(AES, target_address) {
                return SIMULATOR_RO_WI;
            }
#endif /* ACCESS_RNG */
#if ACCESS_RNG
            IF_GUARD(RNG, target_address) {
                return SIMULATOR_RO_WI;
            }
#endif /* ACCESS_RNG */

        }

    }

	return SIMULATOR_NO_ACCESS;
}





/**
 * @brief   Get the instruction allocated at the given address.
 *          Since in thumb mode instructions can be of 16 or 32 bytes, a word is returned.
 *          The actual number of bytes is put in inst_len.
 *
 * @param   address: The starting address of the instruction to extract
 * @param   inst_len: The variable where the actual instruction length in bytes is put.
 *
 * @return  The instruction as a word. In case the instruction was an halfword, it is zero-extended.
 *          In case the instruction was a double halfword, the first halfword is in the upper bits
 *          and the second one in the lower ones.
 *          This doesn't serialize correctly in little-endian systems.
 */
uint32_t get_instruction_at(const uint16_t *address, size_t *halfword_count) {

    // This could be only the first hald of a double-halfword instruction.
    uint32_t instruction = *address;

    // Actually not an opcode, this is (potentially) the pattern to identify two word instructions.
    uint32_t opcode = instruction & TWO_WORD_INST_MASK;

    // TODO: isn't opcode == ... more readable? Is there any reason to do this?
    if (
        (opcode ^ TWO_WORD_INST_PATTERN_1) == 0 ||
        (opcode ^ TWO_WORD_INST_PATTERN_2) == 0 ||
        (opcode ^ TWO_WORD_INST_PATTERN_3) == 0
    ) {
        /* instruction is 32 bit, fetch second halfword */
        *halfword_count = 2;
        instruction = (instruction << 16) | *(address + 1);
    } else {
        /* instruction is 16 bit */
        *halfword_count = 1;
        // No need to fetch more.
    }

    return instruction;
}

