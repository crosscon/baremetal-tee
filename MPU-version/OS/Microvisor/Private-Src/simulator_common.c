#include "simulator_common.h"
#include "bootloader.h"
#include <stdlib.h>

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
__attribute__((naked)) void Run_With_Context(unsigned int* address, unsigned int* auto_frame, unsigned int* manual_frame) {
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
 * Executes the faulty instuction with the original context (except for registers SP,LR and PC)
 * Advances the stacked PC (created on exception entry) by the instruction lenght
 * to ensure the continuation of the execution after returning from exception.
 * The instruction to simulate is the one stored in the PC register (position 6 of the auto_frame).
 * 
 * Parameters:
 *  auto_frame: frame created automatically during exception entry
 *  manual_frame: frame created manually containing rest of context
 *  inst_len: lenght of faulty instruction (in bytes)
 * 
 * Returns:
 * SIMULATION_OK: if the simulation was successful
 * SIMULATION_NOMEM: if there was no memory available for the in-memory function
 *
 */
void Simulate_Faulty_Instruction(unsigned int* auto_frame, unsigned int* manual_frame, unsigned int inst_len) {
	/* Allocate space for in-memory function */
	unsigned char* funct_ptr = (unsigned char*) &simulation_mem;  // create pointer to simulation memory	
	unsigned char* inst_ptr = (unsigned char*) auto_frame[6]; // pointer to faulty instruction (stored in the autoframe, in particular in the PC register)

	/* Copy faulty instruction to simulation memory */
	for(unsigned int i = 0; i < inst_len; i++) {
		funct_ptr[i] = inst_ptr[i];
	}
	/* Add return to function (BX LR) */
	funct_ptr[inst_len] = (BX_LR) & 0xff;
	funct_ptr[inst_len + 1] = (BX_LR >> 0x8) & 0xfff;

	/* Execute in-memory function */
	Run_With_Context((unsigned int*) funct_ptr, auto_frame, manual_frame);

	/* Advance auto_frame PC to next instruction */
	auto_frame[6] = (int)((unsigned char*) auto_frame[6] + inst_len);

	return;
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
		if(MPU_START <= target_address && target_address <= MPU_END)	// invalid when trying to access MPU settings
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
	if(PPB_START <= target_address && target_address <= PPB_END) {
		if(MPU_START <= target_address && target_address <= MPU_END)	// access to MPU configuration not allowed
			return SIMULATOR_NO_ACCESS;
		if(target_address == (uint32_t) &(SCB->VTOR))	// block write access to VTOR
			return SIMULATOR_RO_WI;
		return SIMULATOR_RW;	// allow other accesses (inside the PPB)
	}
	return SIMULATOR_NO_ACCESS;
}