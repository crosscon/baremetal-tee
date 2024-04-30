#ifndef __SIMULATOR_COMMON_H
#define __SIMULATOR_COMMON_H

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
void Run_With_Context(unsigned int* address, unsigned int* auto_frame, unsigned int* manual_frame);
void Simulate_Faulty_Instruction(unsigned int* auto_frame, unsigned int* manual_frame, unsigned int inst_len);

/* Function if the address provided is part of the PPB */
int Is_PPB_Address_Valid(unsigned int target_address);

/* Functions to retrieve the permissions of a simulated function on a given address */
uint32_t Simulator_Get_Permission(uint32_t target_address);

#endif /* __SIMULATOR_COMMON_H */