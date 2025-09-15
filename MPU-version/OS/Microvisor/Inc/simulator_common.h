#ifndef __SIMULATOR_COMMON_H
#define __SIMULATOR_COMMON_H

#include <stddef.h>
#include <stdint.h>

#define BX_LR 0b0100011101110000
#define PPB_START 0xe0000000
#define PPB_END 0xe00fffff
#define MPU_START 0xE000ED94
#define MPU_END 0xE000EDEF

/* Access permissions */
#define SIMULATOR_RW 0	// read and write access
#define SIMULATOR_RO_WI 1	// read-only, write-ignored access
#define SIMULATOR_NO_ACCESS 2	// no access


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
