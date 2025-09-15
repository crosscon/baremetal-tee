#ifndef __PPB_HANDLERS_H
#define __PPB_HANDLERS_H

#include <stdint.h>

/* PPB access return codes */
#define PPB_HANDLER_OK 0
#define PPB_HANDLER_FAIL 1
#define PPB_HANDLER_NO_PPB_ACCESS 2

/* Instruction lenght in halfwords */
#define INST_16BIT 1
#define INST_32BIT 2

/**
 * MNEMONIC_XY:
 *  X indicates whether the instruction is immediate (I) or register (R)
 *  Y indicates the number of encoding (1 = T1, 2 = T2...)
*/

/* 16 bit instruction encodings */

#define STR_LDR_R1_RM_MASK  0b111000000
#define STR_LDR_R1_RM_SHIFT 6
#define STR_LDR_R1_RN_MASK  0b111000
#define STR_LDR_R1_RN_SHIFT 3
#define STR_LDR_R1_RT_MASK  0b111
#define STR_LDR_R1_RT_SHIFT 0
#define STR_LDR_R1_LOAD_MASK	0b0000100000000000
#define STR_LDR_R1_LOAD_SHIFT	11

#define STR_LDR_I1_IMM_MASK		0b011111000000
#define STR_LDR_I1_IMM_SHIFT	4
#define STR_LDR_I1_RN_MASK		0b111000
#define STR_LDR_I1_RN_SHIFT		3
#define STR_LDR_I1_RT_MASK		0b111
#define STR_LDR_I1_RT_SHIFT		0
#define STR_LDR_I1_LOAD_MASK	0b0000100000000000
#define STR_LDR_I1_LOAD_SHIFT	11

#define STRB_LDRB_I1_IMM_MASK	0b011111000000
#define STRB_LDRB_I1_IMM_SHIFT	6
#define STRB_LDRB_I1_RN_MASK	0b111000
#define STRB_LDRB_I1_RN_SHIFT	3
#define STRB_LDRB_I1_RT_MASK	0b111
#define STRB_LDRB_I1_RT_SHIFT	0
#define STRB_LDRB_I1_LOAD_MASK	0b0000100000000000
#define STRB_LDRB_I1_LOAD_SHIFT	11

#define STRH_LDRH_I1_IMM_MASK	0b011111000000
#define STRH_LDRH_I1_IMM_SHIFT	5
#define STRH_LDRH_I1_RN_MASK	0b111000
#define STRH_LDRH_I1_RN_SHIFT	3
#define STRH_LDRH_I1_RT_MASK	0b111
#define STRH_LDRH_I1_RT_SHIFT	0
#define STRH_LDRH_I1_LOAD_MASK	0b0000100000000000
#define STRH_LDRH_I1_LOAD_SHIFT	11


/* 32 bit instruction encodings */

#define STRB_STRH_I2_STR_I3_RN_MASK		0b00000000000011110000000000000000
#define STRB_STRH_I2_STR_I3_RN_SHIFT	16
#define STRB_STRH_I2_STR_I3_RT_MASK		0b00000000000000001111000000000000
#define STRB_STRH_I2_STR_I3_RT_SHIFT	12
#define STRB_STRH_I2_STR_I3_IMM_MASK	0b00000000000000000000111111111111
#define STRB_STRH_I2_STR_I3_IMM_SHIFT	0

#define STRB_STRH_I3_STR_I4_U_MASK		0b00000000000000000000001000000000
#define STRB_STRH_I3_STR_I4_U_SHIFT		9
#define STRB_STRH_I3_STR_I4_RN_MASK		0b00000000000011110000000000000000
#define STRB_STRH_I3_STR_I4_RN_SHIFT	16
#define STRB_STRH_I3_STR_I4_RT_MASK		0b00000000000000001111000000000000
#define STRB_STRH_I3_STR_I4_RT_SHIFT	12
#define STRB_STRH_I3_STR_I4_IMM_MASK	0b00000000000000000000000011111111
#define STRB_STRH_I3_STR_I4_IMM_SHIFT	0

#define STRB_STRH_STR_R2_RN_MASK	0b00000000000011110000000000000000
#define STRB_STRH_STR_R2_RN_SHIFT	16
#define STRB_STRH_STR_R2_RT_MASK	0b00000000000000001111000000000000
#define STRB_STRH_STR_R2_RT_SHIFT	12
#define STRB_STRH_STR_R2_IMM_MASK	0b00000000000000000000000000110000
#define STRB_STRH_STR_R2_IMM_SHIFT	4
#define STRB_STRH_STR_R2_RM_MASK	0b00000000000000000000000000001111
#define STRB_STRH_STR_R2_RM_SHIFT	0

#define LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_RN_MASK		0b00000000000011110000000000000000
#define LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_RN_SHIFT		16
#define LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_RT_MASK		0b00000000000000001111000000000000
#define LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_RT_SHIFT		12
#define LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_IMM_MASK		0b00000000000000000000111111111111
#define LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_IMM_SHIFT	0

#define LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_U_MASK		0b00000000000000000000001000000000
#define LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_U_SHIFT		9
#define LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_RN_MASK		0b00000000000011110000000000000000
#define LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_RN_SHIFT		16
#define LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_RT_MASK		0b00000000000000001111000000000000
#define LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_RT_SHIFT		12
#define LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_IMM_MASK		0b00000000000000000000000011111111
#define LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_IMM_SHIFT	0

#define LDR_LDRH_LDRSH_LDRB_LDRSB_R2_RN_MASK		0b00000000000011110000000000000000
#define LDR_LDRH_LDRSH_LDRB_LDRSB_R2_RN_SHIFT		16
#define LDR_LDRH_LDRSH_LDRB_LDRSB_R2_RT_MASK		0b00000000000000001111000000000000
#define LDR_LDRH_LDRSH_LDRB_LDRSB_R2_RT_SHIFT		12
#define LDR_LDRH_LDRSH_LDRB_LDRSB_R2_IMM_MASK		0b00000000000000000000000000110000
#define LDR_LDRH_LDRSH_LDRB_LDRSB_R2_IMM_SHIFT	4
#define LDR_LDRH_LDRSH_LDRB_LDRSB_R2_RM_MASK		0b00000000000000000000000000001111
#define LDR_LDRH_LDRSH_LDRB_LDRSB_R2_RM_SHIFT		0

/* 16 bit instruction handlers */
int simulate16_str_ldr_r1(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame);
int simulate16_str_ldr_i1(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame);
int simulate16_strb_ldrb_i1(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame);
int simulate16_strh_ldrh_i1(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame);

/* 32 bit instruction handlers */
int simulate32_strb_strh_i2_str_i3(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame);
int simulate32_strb_strh_i3_str_i4(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame);
int simulate32_strb_strh_str_r2(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame);
int simulate32_ldr_i3_ldrh_ldrb_i2_ldrsh_ldrsb_i1(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame);
int simulate32_ldr_i4_ldrh_ldrb_i3_ldrsh_ldrsb_i2(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame);
int simulate32_ldr_ldrh_ldrsh_ldrb_ldrsb_r2(unsigned int faulty_inst, unsigned int* auto_frame, unsigned int* manual_frame);

#endif /* __PPB_HANDLERS_H */
