/* Standard Libs */
#include <stdint.h>
#include <string.h>
#include <stdio.h>

// Include the TEE API header files
#include "tee_client_api.h"
#include "tee_core_api.h"

void access_TEE_RAM(){

	// Sample function to perform Fibonacci sequence and try to access TEE reserved memory
	int n, f, f1, f2;

	n = 10;
	f1 = 0;
	f2 = 1;


	for(int i=2; i<=n; i++){
		f = f1 + f2;
		f1 = f2;
		f2 = f;

		IMSG("TA1 is trying to load data from: 0x10000000 (TEE reserved RAM memory address)\r\n");
		__asm__(
			"ldr r8, =0x10000000\n" // load the address 0x10000000 into r8 (0x10000000 is part of the RAM of TEE)
			"ldr r0, [r8]\n"        // load the value of r8 in r0
		);
	}
}

void access_TA2_RAM(){
	// Try to access RAM area dedicated to TA2 (without having the privileges to do so)

	IMSG("TA1 is trying to load data from: 0x2000C010 (TA2 reserved RAM memory address)\r\n");
	__asm__(
		"ldr r1, =0x2000C010\n" // load the address 0x2000C010 into r1 (0x2000C010 is part of the RAM of TA1)
		"ldr r0, [r1]\n"        // load the value of r1 in r0
	);
}

void trigger_unpermitted_TA2_FLASH_access()
{
	// Try to copy some data from the TA2 flash memory area (without having the privileges to do so)
	IMSG("TA1 is trying to copy some data from: 0x0809C000 (TA2 flash memory address)\r\n");

    unsigned char buffer[16] = {0};
    unsigned char *p = 0x0809C000; // TA2 flash area

    memcpy(buffer, p, 16);
}

void trigger_unpermitted_TEE_FLASH_access()
{
	// Try to copy some data from the TEE flash memory area (without having the privileges to do so)
	IMSG("TA1 trying to copy some data from: 0x08010000 (TEE flash memory address)\r\n");

    unsigned char buffer[16] = {0};
    unsigned char *p = 0x08010000;// TEE flash area

    memcpy(buffer, p, 16);
}

void escalate_priv()
{
	// Try to execute a GP Core API directly from a Client Application
	// without switching to secure world and invoking a Trusted Application
	IMSG("TA1 Trying to modify system registers and gain privileges from the TA\r\n");

	uint32_t control;
	__asm__ volatile ("mrs %0, CONTROL" : "=r" (control) );
	IMSG("Current value of nPRIV bit: %d\r\n", control);

	/* Set CTRL.nPRIV to 0 (try to switch to privileged mode) */
	__asm__(
		"mov r0, #0x00\n"
		"msr CONTROL, r0\n"
	);

	__asm__ volatile ("mrs %0, CONTROL" : "=r" (control) );
	IMSG("Value of nPRIV bit after trying to gain privileges (set register to 0): %d\r\n", control);
}

TEE_Result TA_CreateEntryPoint(void)
{   
	DMSG("has been called");
    return TEE_SUCCESS;
}

void TA_DestroyEntryPoint(void)
{
	DMSG("has been called");
	return;
}


TEE_Result TA_OpenSessionEntryPoint(uint32_t param_types, 
									TEE_Param params[4], 
									void **sessionContext)
{
	DMSG("has been called");
    return TEE_SUCCESS;
}


void TA_CloseSessionEntryPoint(void* sessionContext)
{
	DMSG("has been called");
	return; 
}


TEE_Result TA_InvokeCommandEntryPoint(void* sessionContext,
									uint32_t commandID,
									uint32_t paramTypes,
									TEE_Param params[4])
{
	DMSG("has been called");

	IMSG("Command ID: %d", commandID);

	// Trigger the access to the TEE reserved RAM
	//access_TEE_RAM();

	// Trigger the access to the TA2 reserved RAM
	//access_TA2_RAM();

	// Trigger the access to the TA2 flash memory
	//trigger_unpermitted_TA2_FLASH_access();

	// Trigger the access to the TEE flash memory
	//trigger_unpermitted_TEE_FLASH_access();

	// Trigger the escalation of privileges
	//escalate_priv();

	return TEE_SUCCESS;
}
