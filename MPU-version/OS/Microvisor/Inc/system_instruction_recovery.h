#ifndef __SYSTEM_INSTRUCTION_RECOVERY_H
#define __SYSTEM_INSTRUCTION_RECOVERY_H

#include <stddef.h>
#include <stdint.h>

#define SYS_INST_OK 0		// system instruciton simulated correctly
#define SYS_INST_NOREQ 1	// not system instruction execution requested

/* Define patterns and masks to identify the system instructions */
#define CPS_MASK    0b1111111111100000
#define CPS_PATTERN 0b1011011001100000
#define MRS_MASK    0b11111111111111111111000000000000
#define MRS_PATTERN 0b11110011111011111000000000000000
#define MSR_MASK    0b11111111111100001111001100000000
#define MSR_PATTERN 0b11110011100000001000000000000000

/* Define masks to identify the params of the system instruction */
#define SYS_M_MASK		0b00000000000000000000000011111111
#define SYS_M_SHIFT 	0
#define SYS_M_IPSR_MASK	0x1ff

#define MRS_RD_MASK		0b00000000000000000000111100000000
#define MRS_RD_SHIFT	8

#define MSR_RN_MASK		0b00000000000011110000000000000000
#define MSR_RN_SHIFT	16
#define MSR_SYS_M_CTRL_PATTERN	0x14 //SYSm == 0b00010100 indicates write to CONTROL register

/** 
 * Function to determine wheter the SVC was executed to simulate 
 * the usage of a system instruction with privileges.
 */
int Recover_System_Instruction(unsigned int* auto_frame, unsigned int* manual_frame);


#endif /* __SYSTEM_INSTRUCTION_RECOVERY_H */
