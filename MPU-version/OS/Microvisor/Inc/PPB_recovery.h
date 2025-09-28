#ifndef __PPB_RECOVERY_H
#define __PPB_RECOVERY_H

/* PPB recovery return codes */
#define PPB_RECOVERY_OK 0
#define PPB_RECOVERY_FAIL 1
#define PPB_RECOVERY_NOMATCH 2

/* Instruction lenght patterns */
#define TWO_WORD_INST_MASK 0b1111100000000000
#define TWO_WORD_INST_PATTERN_1 0b1110100000000000
#define TWO_WORD_INST_PATTERN_2 0b1111000000000000
#define TWO_WORD_INST_PATTERN_3 0b1111100000000000

/**
 * MNEMONIC_XY:
 *  X indicates whether the instruction is immediate (I) or register (R)
 *  Y indicates the number of encoding (1 = T1, 2 = T2...)
 */

/********************/
/* 16 bit encodings */
/********************/

/**
 * register-version:
 * STR,STRH,STRB,LDRSB,LDR,LDRH,LDRB,LDRSH
 */
#define STR_LDR_R1_MASK 0b1111000000000000
#define STR_LDR_R1_PATTERN 0b0101000000000000

/**
 * immediate-version:
 * STR,LDR
 */
#define STR_LDR_I1_MASK 0b1111000000000000
#define STR_LDR_I1_PATTERN 0b0110000000000000

/**
 * immediate-version:
 * STRB,LDRB
 */
#define STRB_LDRB_I1_MASK 0b1111000000000000
#define STRB_LDRB_I1_PATTERN 0b0111000000000000

/**
 * immediate-version:
 * STRH,LDRH
 */
#define STRH_LDRH_I1_MASK 0b1111000000000000
#define STRH_LDRH_I1_PATTERN 0b1000000000000000

/********************/
/* 32 bit encodings */
/********************/

/**
 * immediate-version:
 * STRB,STRH
 * 2 different encodings can use different offset modes
 */
#define STRB_STRH_I2_STR_I3_MASK 0b11111111100100000000000000000000
#define STRB_STRH_I2_STR_I3_PATTERN 0b11111000100000000000000000000000

#define STRB_STRH_I3_STR_I4_MASK 0b11111111100100000000100000000000
#define STRB_STRH_I3_STR_I4_PATTERN 0b11111000000000000000100000000000

/**
 * register-version:
 * STRB,STRH,STR
 */
#define STRB_STRH_STR_R2_MASK 0b11111111100100000000111111000000
#define STRB_STRH_STR_R2_PATTERN 0b11111000000000000000000000000000

/**
 * immediate-version:
 * LDR T3,LDRH T2,LDRSH T1,LDRB T2,LDRSB T1
 * although they have the same fields, their parttern does not
 * cover all possible combinations so they must be specified manually
 */
#define LDR_I3_LDRH_LDRB_I2_LDRSH_LDRSB_I1_MASK                                \
  0b11111111111100000000000000000000
#define LDR_I3_PATTERN 0b11111000110100000000000000000000
#define LDRH_I2_PATTERN 0b11111000101100000000000000000000
#define LDRSH_I1_PATTERN 0b11111001101100000000000000000000
#define LDRB_I2_PATTERN 0b11111000100100000000000000000000
#define LDRSB_I1_PATTERN 0b11111001100100000000000000000000

/**
 * immediate-version:
 * LDR T4,LDRH T3,LDRSH T2,LDRB T3,LDRSB T2
 * although their operands have the same fields, their parttern does not
 * cover all possible combinations so they must be specified manually
 */
#define LDR_I4_LDRH_LDRB_I3_LDRSH_LDRSB_I2_MASK                                \
  0b11111111111100000000100000000000
#define LDR_I4_PATTERN 0b11111000010100000000100000000000
#define LDRH_I3_PATTERN 0b11111000001100000000100000000000
#define LDRSH_I2_PATTERN 0b11111001001100000000100000000000
#define LDRB_I3_PATTERN 0b11111000000100000000100000000000
#define LDRSB_I2_PATTERN 0b11111001000100000000100000000000

/**
 * register-version:
 * LDR T2,LDRH T2,LDRSH T2,LDRB T2,LDRSB T2
 * although their operands have the same fields, their parttern does not
 * cover all possible combinations so they must be specified manually
 */
#define LDR_LDRH_LDRSH_LDRB_LDRSB_R2_MASK 0b11111111111100000000111111000000
#define LDR_R2_PATTERN 0b11111000010100000000000000000000
#define LDRH_R2_PATTERN 0b11111000001100000000000000000000
#define LDRSH_R2_PATTERN 0b11111001001100000000000000000000
#define LDRB_R2_PATTERN 0b11111000000100000000000000000000
#define LDRSB_R2_PATTERN 0b11111001000100000000000000000000

/**
 * Function that checks if the HardFault is cause by an unprivileged access
 * to the Private Peripheral Bus (PPB).
 * In that case, grant the access and simulate the istruction
 */
int Recover_PPB_Access(unsigned int *fault_frame, unsigned int *fake_frame);

#endif /* __PPB_RECOVERY_H */