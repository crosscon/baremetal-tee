#include "PPB_handlers.h"
#include "simulator_common.h"

/**
 * @brief Checks the permissions and simulates a load or store instruction given the address.
 *
 * @param auto_frame The frame automatically allocated on exception entry.
 * @param manual_frame The frame previously allocated containing callee preserved general purpose registers.
 * @param is_load Whether this is a load (1) or store (0) instruction.
 * @param address The address the instruction tries to write to or read from.
 * @param halfword_count The size in halfword of the instruction (halfword or double-halfword).
 * @param inst The instruction that should be executed.
 *
 * @return PPB_HANDLER_OK if the simulation was successful (some operations could be write-ignored)
 *         PPB_HANDLER_NO_PPB_ACCESS if the address is not accessible.
 */
static int simulate(unsigned int *auto_frame, unsigned int *manual_frame, uint32_t is_load, unsigned int address, size_t halfword_count, uint32_t inst) {
    switch (Simulator_Get_Permission(address)) {
		case SIMULATOR_RW:
			Simulate_Faulty_Instruction(auto_frame, manual_frame, halfword_count, inst);
			return PPB_HANDLER_OK;
		case SIMULATOR_RO_WI:
            // permit only LOAD operations, STORE are ignored
			if(is_load)	{
				Simulate_Faulty_Instruction(auto_frame, manual_frame, halfword_count, inst);
            } else {
                // increase PC by instruction length (16 bit)
				Set_Register_Value(15, auto_frame, manual_frame, Get_Register_Value(15, auto_frame, manual_frame) + 2 * halfword_count);
            }
			return PPB_HANDLER_OK;
		case SIMULATOR_NO_ACCESS:
		default:
			return PPB_HANDLER_NO_PPB_ACCESS;
    }
}

/**
*
* Simulates the execution of STR (store) and LDR (load) instructions using the original context
* Different version of the function are used to simulate different instruction formats
* 
* Versions: MNEMONIC_XY:
* X indicates whether the instruction is immediate (I) or register (R)
* Y indicates the number of encoding (1 = T1, 2 = T2...)
*
* Parameters (of every version):
* faulty_inst: instruction to simulate (STR or LDR in this case)
* auto_frame: pointer to frame created automatically during exception entry
* manual_frame: pointer to frame created manually before calling this function
*
* Returns (of every version):
*	PPB_HANDLER_OK: if the instruction was successfully simulated
*	PPB_HANDLER_FAIL: if the instruction could not be simulated as involves SP, LR or PC
*	PPB_HANDLER_NO_PPB_ACCESS: if the instruction could not be simulated as the target address is not in the PPB
*
*/

/* 16 bit instruction handlers */



/* LDR and STR, register offset (r1) */
int simulate16_str_ldr_r1(unsigned int faulty_inst, unsigned int *auto_frame, unsigned int *manual_frame) {
	/*
	Rt = register to load or store
	Rn = register that store the base memory address
	Rm = register that contain a value to be used as the offset
	*/
	unsigned int rm = (faulty_inst & STR_LDR_R1_RM_MASK) >> STR_LDR_R1_RM_SHIFT;
	unsigned int rn = (faulty_inst & STR_LDR_R1_RN_MASK ) >> STR_LDR_R1_RN_SHIFT;
	unsigned int rt = (faulty_inst & STR_LDR_R1_RT_MASK) >> STR_LDR_R1_RT_SHIFT;
	uint32_t is_load = (faulty_inst & STR_LDR_R1_LOAD_MASK) >> STR_LDR_R1_LOAD_SHIFT;

	if ((13 <= rn && rn <= 15) || (13 <= rt && rt <= 15) || (13 <= rm && rm <= 15)) {
		/* SP, LR, PC used in original instruction, cannot reproduce original behavior */
		return PPB_HANDLER_FAIL;
	}

	/* Get the value of the register using the Get_Register_Value helper function */
	unsigned int base_reg = Get_Register_Value(rn, auto_frame, manual_frame);
	unsigned int add_reg = Get_Register_Value(rm, auto_frame, manual_frame);
	unsigned int target_address = base_reg + add_reg;

    return simulate(auto_frame, manual_frame, is_load, target_address, INST_16BIT, faulty_inst);
}

/* LDR and STR, immediate offset (i1)*/
int simulate16_str_ldr_i1(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame) {
	unsigned int imm = (faulty_inst & STR_LDR_I1_IMM_MASK) >> STR_LDR_I1_IMM_SHIFT;
	unsigned int rn = (faulty_inst & STR_LDR_I1_RN_MASK ) >> STR_LDR_I1_RN_SHIFT;
	unsigned int rt = (faulty_inst & STR_LDR_I1_RT_MASK) >> STR_LDR_I1_RT_SHIFT;
	uint32_t is_load = (faulty_inst & STR_LDR_I1_LOAD_MASK) >> STR_LDR_I1_LOAD_SHIFT;

	if ((13 <= rn && rn <= 15) || (13 <= rt && rt <= 15)) {
		/* SP, LR, PC used in original instruction, cannot reproduce original behavior */
		return PPB_HANDLER_FAIL;
	}

	unsigned int base_reg = Get_Register_Value(rn, auto_frame, manual_frame);
	unsigned int target_address = base_reg + imm;

    return simulate(auto_frame, manual_frame, is_load, target_address, INST_16BIT, faulty_inst);

}

/* LDR and STR, immediate offset (i1), using bytes (b) */
int simulate16_strb_ldrb_i1(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame) {
	unsigned int imm = (faulty_inst & STRB_LDRB_I1_IMM_MASK) >> STRB_LDRB_I1_IMM_SHIFT;
	unsigned int rn = (faulty_inst & STRB_LDRB_I1_RN_MASK ) >> STRB_LDRB_I1_RN_SHIFT;
	unsigned int rt = (faulty_inst & STRB_LDRB_I1_RT_MASK) >> STRB_LDRB_I1_RT_SHIFT;
	uint32_t is_load = (faulty_inst & STRB_LDRB_I1_LOAD_MASK) >> STRB_LDRB_I1_LOAD_SHIFT;

	if ((13 <= rn && rn <= 15) || (13 <= rt && rt <= 15)) {
		/* SP, LR, PC used in original instruction, cannot reproduce original behavior */
		return PPB_HANDLER_FAIL;
	}

	unsigned int base_reg = Get_Register_Value(rn, auto_frame, manual_frame);
	unsigned int target_address = base_reg + imm;

    return simulate(auto_frame, manual_frame, is_load, target_address, INST_16BIT, faulty_inst);
}

/* LDR and STR, immediate offset (i1), using half-word (h) */
int simulate16_strh_ldrh_i1(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame) {
	unsigned int imm = (faulty_inst & STRH_LDRH_I1_IMM_MASK) >> STRH_LDRH_I1_IMM_SHIFT;
	unsigned int rn = (faulty_inst & STRH_LDRH_I1_RN_MASK ) >> STRH_LDRH_I1_RN_SHIFT;
	unsigned int rt = (faulty_inst & STRH_LDRH_I1_RT_MASK) >> STRH_LDRH_I1_RT_SHIFT;
	uint32_t is_load = (faulty_inst & STRH_LDRH_I1_LOAD_MASK) >> STRH_LDRH_I1_LOAD_SHIFT;

	if ((13 <= rn && rn <= 15) || (13 <= rt && rt <= 15)) {
		/* SP, LR, PC used in original instruction, cannot reproduce original behavior */
		return PPB_HANDLER_FAIL;
	}

	unsigned int base_reg = Get_Register_Value(rn, auto_frame, manual_frame);
	unsigned int target_address = base_reg + imm;

    return simulate(auto_frame, manual_frame, is_load, target_address, INST_16BIT, faulty_inst);
}



/* 32 bit instruction handlers */

/* STR bytes, half-words, words using immediate offset */
int simulate32_strb_strh_i2_str_i3(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame) {
	unsigned int imm = (faulty_inst & STRB_STRH_I2_STR_I3_IMM_MASK) >> STRB_STRH_I2_STR_I3_IMM_SHIFT;
	unsigned int rn = (faulty_inst & STRB_STRH_I2_STR_I3_RN_MASK ) >> STRB_STRH_I2_STR_I3_RN_SHIFT;
	unsigned int rt = (faulty_inst & STRB_STRH_I2_STR_I3_RT_MASK) >> STRB_STRH_I2_STR_I3_RT_SHIFT;

	if ((13 <= rn && rn <= 15) || (13 <= rt && rt <= 15)) {
		/* SP, LR, PC used in original instruction, cannot reproduce original behavior */
		return PPB_HANDLER_FAIL;
	}

	unsigned int base_reg = Get_Register_Value(rn, auto_frame, manual_frame);
	unsigned int target_address = base_reg + imm;

    return simulate(auto_frame, manual_frame, 0, target_address, INST_32BIT, faulty_inst);
}

/* STR bytes, half-words, words using immediate offset (added or substracted) */
int simulate32_strb_strh_i3_str_i4(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame) {
	unsigned int imm = (faulty_inst & STRB_STRH_I3_STR_I4_IMM_MASK) >> STRB_STRH_I3_STR_I4_IMM_SHIFT;
	unsigned int rn = (faulty_inst & STRB_STRH_I3_STR_I4_RN_MASK ) >> STRB_STRH_I3_STR_I4_RN_SHIFT;
	unsigned int rt = (faulty_inst & STRB_STRH_I3_STR_I4_RT_MASK) >> STRB_STRH_I3_STR_I4_RT_SHIFT;
	unsigned int add = (faulty_inst & STRB_STRH_I3_STR_I4_U_MASK) >> STRB_STRH_I3_STR_I4_U_SHIFT;

	if ((13 <= rn && rn <= 15) || (13 <= rt && rt <= 15)) {
		/* SP, LR, PC used in original instruction, cannot reproduce original behavior */
		return PPB_HANDLER_FAIL;
	}

	unsigned int base_reg = Get_Register_Value(rn, auto_frame, manual_frame);
	unsigned int target_address = base_reg;
	if (add) {
		target_address += imm;
	} else {
		target_address -= imm;
	}

    return simulate(auto_frame, manual_frame, 0, target_address, INST_32BIT, faulty_inst);
}

/* STR bytes, half-words, words using register offset (with optional shift) */
int simulate32_strb_strh_str_r2(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame) {
	unsigned int rn = (faulty_inst & STRB_STRH_STR_R2_RN_MASK ) >> STRB_STRH_STR_R2_RN_SHIFT;
	unsigned int rt = (faulty_inst & STRB_STRH_STR_R2_RT_MASK) >> STRB_STRH_STR_R2_RT_SHIFT;
	unsigned int imm = (faulty_inst & STRB_STRH_STR_R2_IMM_MASK) >> STRB_STRH_STR_R2_IMM_SHIFT;
	unsigned int rm = (faulty_inst & STRB_STRH_STR_R2_RM_MASK) >> STRB_STRH_STR_R2_RM_SHIFT;

	if ((13 <= rn && rn <= 15) || (13 <= rt && rt <= 15) || (13 <= rm && rm <= 15)) {
		/* SP, LR, PC used in original instruction, cannot reproduce original behavior */
		return PPB_HANDLER_FAIL;
	}

	unsigned int base_reg = Get_Register_Value(rn, auto_frame, manual_frame);
	unsigned int add_reg = Get_Register_Value(rm, auto_frame, manual_frame) << imm;
	unsigned int target_address = base_reg + add_reg;

    return simulate(auto_frame, manual_frame, 0, target_address, INST_32BIT, faulty_inst);
}

/* LDR bytes, half-words, words using immediate offset */
int simulate32_ldr_i3_ldrh_ldrb_i2_ldrsh_ldrsb_i1(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame) {
	unsigned int imm = (faulty_inst & LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_IMM_MASK) >> LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_IMM_SHIFT;
	unsigned int rn = (faulty_inst & LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_RN_MASK ) >> LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_RN_SHIFT;
	unsigned int rt = (faulty_inst & LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_RT_MASK) >> LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_RT_SHIFT;

	if ((13 <= rn && rn <= 15) || (13 <= rt && rt <= 15)) {
		/* SP, LR, PC used in original instruction, cannot reproduce original behavior */
		return PPB_HANDLER_FAIL;
	}

	unsigned int base_reg = Get_Register_Value(rn, auto_frame, manual_frame);
	unsigned int target_address = base_reg + imm;

    return simulate(auto_frame, manual_frame, 1, target_address, INST_32BIT, faulty_inst);
}

/* LDR bytes, half-words, words using immediate offset (added or subtracted) */
int simulate32_ldr_i4_ldrh_ldrb_i3_ldrsh_ldrsb_i2(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame) {
	unsigned int imm = (faulty_inst & LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_IMM_MASK) >> LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_IMM_SHIFT;
	unsigned int rn = (faulty_inst & LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_RN_MASK ) >> LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_RN_SHIFT;
	unsigned int rt = (faulty_inst & LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_RT_MASK) >> LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_RT_SHIFT;
	unsigned int add = (faulty_inst & LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_U_MASK) >> LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_U_SHIFT;

	if ((13 <= rn && rn <= 15) || (13 <= rt && rt <= 15)) {
		/* SP, LR, PC used in original instruction, cannot reproduce original behavior */
		return PPB_HANDLER_FAIL;
	}

	unsigned int base_reg = Get_Register_Value(rn, auto_frame, manual_frame);
	unsigned int target_address = base_reg;
	if (add) {
		target_address += imm;
	} else {
		target_address -= imm;
	}

    return simulate(auto_frame, manual_frame, 1, target_address, INST_32BIT, faulty_inst);
}

/* LDR bytes, half-words, words using register offset (with optional shift) */
int simulate32_ldr_ldrh_ldrsh_ldrb_ldrsb_r2(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame) {
	unsigned int rn = (faulty_inst & LDR_LDRH_LDRSH_LDRB_LDRSB_R2_RN_MASK ) >> LDR_LDRH_LDRSH_LDRB_LDRSB_R2_RN_SHIFT;
	unsigned int rt = (faulty_inst & LDR_LDRH_LDRSH_LDRB_LDRSB_R2_RT_MASK) >> LDR_LDRH_LDRSH_LDRB_LDRSB_R2_RT_SHIFT;
	unsigned int imm = (faulty_inst & LDR_LDRH_LDRSH_LDRB_LDRSB_R2_IMM_MASK) >> LDR_LDRH_LDRSH_LDRB_LDRSB_R2_IMM_SHIFT;
	unsigned int rm = (faulty_inst & LDR_LDRH_LDRSH_LDRB_LDRSB_R2_RM_MASK) >> LDR_LDRH_LDRSH_LDRB_LDRSB_R2_RM_SHIFT;

	if ((13 <= rn && rn <= 15) || (13 <= rt && rt <= 15) || (13 <= rm && rm <= 15)) {
		/* SP, LR, PC used in original instruction, cannot reproduce original behavior */
		return PPB_HANDLER_FAIL;
	}

	unsigned int base_reg = Get_Register_Value(rn, auto_frame, manual_frame);
	unsigned int add_reg = Get_Register_Value(rm, auto_frame, manual_frame) << imm;
	unsigned int target_address = base_reg + add_reg;

    return simulate(auto_frame, manual_frame, 1, target_address, INST_32BIT, faulty_inst);
}
