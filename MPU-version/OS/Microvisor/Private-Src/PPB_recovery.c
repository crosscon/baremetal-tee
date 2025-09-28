#include "PPB_recovery.h"
#include "PPB_handlers.h"
#include "simulator_common.h"
#include "stm32l4xx_hal.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * Checks whether the HardFault is cause by an unprivileged access to the Peripheral Bus (PPB, APB, AHB).
 * if it is, the access is granted and executed with privileges, otherwise a reset
 * of the device is performed.
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
 *  PPB_RECOVERY_OK: if the matching istruction was found and the instruction was simulated correctly
 *  PPB_RECOVERY_FAIL: if the matching instruction was found but the simulation failed
 *  PPB_RECOVERY_NOMATCH: if the matching instruction to simulate was not found
*/
// TODO: rename as this has been extended to support also AHB and APB.
int Recover_PPB_Access(unsigned int* auto_frame, unsigned int* manual_frame) {
    /* recover faulty instruction */
    uint16_t* faulty_addr = (uint16_t*) (uintptr_t) auto_frame[6];

    size_t halfword_count;
    uint32_t faulty_inst = get_instruction_at(faulty_addr, &halfword_count);

    int result = -1;

    /*
    * Check the the faulty instruction match one of the LDR/STR istructions using the mask and pattern
    * and, in the case, simulate it
    */
    if (1 == halfword_count) {    /* 16 bit instructions matching */
        if (((faulty_inst & STR_LDR_R1_MASK) ^ STR_LDR_R1_PATTERN) == 0) {
            result = simulate16_str_ldr_r1(faulty_inst, auto_frame, manual_frame);
        } else if (((faulty_inst & STR_LDR_I1_MASK) ^ STR_LDR_I1_PATTERN) == 0) {
            result = simulate16_str_ldr_i1(faulty_inst, auto_frame, manual_frame);
        } else if (((faulty_inst & STRB_LDRB_I1_MASK) ^ STRB_LDRB_I1_PATTERN) == 0) {
            result = simulate16_strb_ldrb_i1(faulty_inst, auto_frame, manual_frame);
        } else if (((faulty_inst & STRH_LDRH_I1_MASK) ^ STRH_LDRH_I1_PATTERN) == 0) {
            result = simulate16_strh_ldrh_i1(faulty_inst, auto_frame, manual_frame);
        }
    } else {    /* 32 bit instructions matching */
        if (((faulty_inst & STRB_STRH_I2_STR_I3_MASK) ^ STRB_STRH_I2_STR_I3_PATTERN) == 0) {
            result = simulate32_strb_strh_i2_str_i3(faulty_inst, auto_frame, manual_frame);
        } else if (((faulty_inst & STRB_STRH_I3_STR_I4_MASK) ^ STRB_STRH_I3_STR_I4_PATTERN) == 0) {
            result = simulate32_strb_strh_i3_str_i4(faulty_inst, auto_frame, manual_frame);
        } else if (((faulty_inst & STRB_STRH_STR_R2_MASK) ^ STRB_STRH_STR_R2_PATTERN) == 0) {
            result = simulate32_strb_strh_str_r2(faulty_inst, auto_frame, manual_frame);
        } else if (
                (((faulty_inst & LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_MASK) ^ LDR_I3_PATTERN) == 0) ||
                (((faulty_inst & LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_MASK) ^ LDRH_I2_PATTERN) == 0) ||
                (((faulty_inst & LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_MASK) ^ LDRSH_I1_PATTERN) == 0) ||
                (((faulty_inst & LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_MASK) ^ LDRB_I2_PATTERN) == 0) ||
                (((faulty_inst & LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_MASK) ^ LDRSB_I1_PATTERN) == 0)
            ) {
            result = simulate32_ldr_i3_ldrh_ldrb_i2_ldrsh_ldrsb_i1(faulty_inst, auto_frame, manual_frame);
        } else if (
                (((faulty_inst & LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_MASK) ^ LDR_I4_PATTERN) == 0) ||
                (((faulty_inst & LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_MASK) ^ LDRH_I3_PATTERN) == 0) ||
                (((faulty_inst & LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_MASK) ^ LDRSH_I2_PATTERN) == 0) ||
                (((faulty_inst & LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_MASK) ^ LDRB_I3_PATTERN) == 0) ||
                (((faulty_inst & LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_MASK) ^ LDRSB_I2_PATTERN) == 0)
            ) {
            result = simulate32_ldr_i4_ldrh_ldrb_i3_ldrsh_ldrsb_i2(faulty_inst, auto_frame, manual_frame);
        } else if (
                (((faulty_inst & LDR_LDRH_LDRSH_LDRB_LDRSB_R2_MASK) ^ LDR_R2_PATTERN) == 0) ||
                (((faulty_inst & LDR_LDRH_LDRSH_LDRB_LDRSB_R2_MASK) ^ LDRH_R2_PATTERN) == 0) ||
                (((faulty_inst & LDR_LDRH_LDRSH_LDRB_LDRSB_R2_MASK) ^ LDRSH_R2_PATTERN) == 0) ||
                (((faulty_inst & LDR_LDRH_LDRSH_LDRB_LDRSB_R2_MASK) ^ LDRB_R2_PATTERN) == 0) ||
                (((faulty_inst & LDR_LDRH_LDRSH_LDRB_LDRSB_R2_MASK) ^ LDRSB_R2_PATTERN) == 0)
            ) {
            result = simulate32_ldr_ldrh_ldrsh_ldrb_ldrsb_r2(faulty_inst, auto_frame, manual_frame);
        }
    }

    /* Return a different error code based on the result of the simulation */
    switch (result) {
    case -1:
        return PPB_RECOVERY_NOMATCH;
    case 0:
        /* Clear CFSR */
        SCB->CFSR = 0xffffffffU;
        return PPB_RECOVERY_OK;
    default:
        return PPB_RECOVERY_FAIL;
    }
}
