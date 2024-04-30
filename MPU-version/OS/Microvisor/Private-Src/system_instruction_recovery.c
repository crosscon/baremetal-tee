#include "system_instruction_recovery.h"
#include "simulator_common.h"
#include "virtual_IPSR.h"

/**
 * Simulates the execution of CPS (system instruction) using the original context 
 * stored in the auto_frame and manual_frame
 * CPS is a 16 bit wide instruction, so it is necessary to set the length to 2
 * 
 * Parameters:
 * faulty_inst: used to maintain the same standard signature 
 * (not used in this context as CPS does not have any parameters)
 * auto_frame: pointer to frame created automatically during exception entry
 * manual_frame: pointer to frame created manually before calling this function
 *
*/
void Simulate_CPS(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame) {
	Simulate_Faulty_Instruction(auto_frame, manual_frame, 2);
	return;
}


/**
* Simulates the execution of MRS (system instruction) using the original context
* stored in the auto_frame and manual_frame
* MRS is a 32 bit wide instruction, so it is necessary to set the length to 4
*
* Parameters: 
* faulty_inst: instruction to simulate (MRS in this case) with the necessary parameters (e.g. destination register) 
* auto_frame: pointer to frame created automatically during exception entry
* manual_frame: pointer to frame created manually before calling this function
*/
void Simulate_MRS(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame) {
	/* 
	* Extract parameters from the MRS instruction:
	* SYSm: system control space (SCS) register
	* read_IPSR: if 1, read IPSR register
	* rd: destination register
	 */
	unsigned int SYSm = (faulty_inst & SYS_M_MASK) >> SYS_M_SHIFT;
	unsigned int read_IPSR = SYSm & 0x1;
	unsigned int rd = (faulty_inst & MRS_RD_MASK) >> MRS_RD_SHIFT;
	
	/* Simulate the instruction */
	Simulate_Faulty_Instruction(auto_frame, manual_frame, 4);
	
	if (read_IPSR) {
		/* When requesting IPSR read, substitute original IPSR value
		with virtual IPSR value. No need to check if we are in unprioritized
		handler or not, because the virtual IPSR will reflect the correct
		state anyway */
		unsigned int rd_value = Get_Register_Value(rd, auto_frame, manual_frame);	// read destination register
		unsigned int virtual_IPSR = Get_Virtual_IPSR();	// get current Virtual IPSR value
		rd_value = (rd_value & (~SYS_M_IPSR_MASK)) | virtual_IPSR;	// compute new destination register value
		Set_Register_Value(rd, auto_frame, manual_frame, rd_value);	// update destination register value
	}

	return;
}

/*
* Simulates the execution of MSR instruction using the original context
* stored in the auto_frame and manual_frame
* MSR is a 32 bit wide instruction, so it is necessary to set the length to 4
*
* Parameters: 
* faulty_inst: instruction to simulate (MSR in this case) with the necessary parameters 
* auto_frame: pointer to frame created automatically during exception entry
* manual_frame: pointer to frame created manually before calling this function
*/
void Simulate_MSR(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame) {
	/* 
	* Extract parameters from the MRS instruction:
	* SYSm: system control space (SCS) register
	* rn: source register
	 */
	unsigned int SYSm = (faulty_inst & SYS_M_MASK) >> SYS_M_SHIFT;
	unsigned int rn = (faulty_inst & MSR_RN_MASK) >> MSR_RN_SHIFT;

	/* Prevent the MSR instruction to override the fileds that control the stack pointer and privilege level */
	if ((SYSm ^ MSR_SYS_M_CTRL_PATTERN) == 0) {
		/* MSR instruction attempting to write CONTROL register, must prevent changes to nPRIV */
		/* nPRIV field controls the privilege level of Thread mode */
		unsigned int rn_value = Get_Register_Value(rn, auto_frame, manual_frame);
		unsigned int curr_CONTROL;
  		__asm__ volatile ("MRS %0, control" : "=r" (curr_CONTROL) );	// read current CONTROL register
		unsigned int curr_nPRIV = curr_CONTROL & 0b1;	// isolate nPRIV bit
		rn_value = (rn_value & ~0b1) | curr_nPRIV;	// overwrite nPRIV target value

		if (Is_Deprioritized_Handler_Active()) {
			/* Code is ment to run in Handler mode, prevent changes to SPSEL */
			/* SPSEL field controls the current stack pointer */
			unsigned int curr_SPSEL = curr_CONTROL & 0b10;	// isolate SPSEL bit
			rn_value = (rn_value & ~0b10) | curr_SPSEL;	// overwrite SPSEL target value
		}

		Set_Register_Value(rn, auto_frame, manual_frame, rn_value);	// save operand register value
	}	

	/* Simulate the instruction */
	Simulate_Faulty_Instruction(auto_frame, manual_frame, 4);
	return;
}

/**
 * Checks whether the SVC was executed in order to simulate the usage of a system
 * instruction (CPS, MRS, MSR) with privileges. If it was, the instruction is simulated
 * while making sure that CONTROL.nPRIV is not altered (unprivileged code should never
 * be able to alter it).
 * 
 * Parameters:
 *  auto_frame:
 *      pointer to frame created automatically during exeption entry
 *      contains R0,R1,R2,R3,R12,LR,PC,XPSR, can be stored on Main Stack or Process Stack
 *      depending on what was used before exception entry.
 *  manual_frame:
 *      pointer to frame created manually before calling this function, contains the rest
 *      of the context not saved automatically by exception entry (R4-R11 and EXC_RETURN (LR))
 *      is always stored on the Main Stack.
 * 
 * Returns:
 * SYS_INST_OK: if the instruction was successfully simulated
 * SYS_INST_FAIL: if the instruction could not be simulated
 * SYS_INST_NOREQ: if no system instruction simulation was requested (normal instruction execution)
*/
int Recover_System_Instruction(unsigned int* auto_frame, unsigned int* manual_frame) {
	/* recover faulty instruction */
	unsigned short* faulty_addr = (unsigned short*) auto_frame[6];
	// unsigned char SVC_imm = *(faulty_addr - 1);	//don't care about SVC value
	unsigned int following_inst = *faulty_addr;

	/* Check if the instruction is a CPS instruction and simulate it*/
	if (((following_inst & CPS_MASK) ^ CPS_PATTERN) == 0) {
		Simulate_CPS(following_inst, auto_frame, manual_frame);
		return SYS_INST_OK;
	}

	// MRS and MSR are 32 bit wide, load second halfword of the following instruction
	following_inst = following_inst << 16 | *(faulty_addr + 1);

	// Check whether the instruction is a MRS or MSR instruction and simulate it
	if (((following_inst & MRS_MASK) ^ MRS_PATTERN) == 0) {
		Simulate_MRS(following_inst, auto_frame, manual_frame);
		return SYS_INST_OK;
	}

	if (((following_inst & MSR_MASK) ^ MSR_PATTERN) == 0) {
		Simulate_MSR(following_inst, auto_frame, manual_frame);
		return SYS_INST_OK;
	}

	/* If the instruction is neither a CPS, MRS or MSR the instruction 
	is not a system one and the simulation is not needed */
	return SYS_INST_NOREQ;
}