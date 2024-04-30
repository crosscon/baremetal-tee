/**
* MCU-Fortifier microvisor HardFault_Handler: 
* - If the hard fault is caused by an unprivileged access to the PPB, 
* 	the access is granted and executed under the control of MCU-Fortifier
* - In case of error during the recovery and simulation, the MCU is reset
*/
void Microvisor_HardFault_Handler() {
	__asm__(
		/* Move pre-exception entry SP to R0 */
		"tst lr, #4\n"
		"ite eq\n"
		"mrseq r0, msp\n"
		"mrsne r0, psp\n"

		/* Check for exception return request */
		/* Only execute when the HardFault originate from the exception simulator */
		"push {lr}\n"
		"blx Exception_Return_Handler\n"

		/* Check for unprioritized access to PPB (Private Peripheral Bus) */
		"push {r4,r5,r6,r7,r8,r9,r10,r11}\n" //push rest of registers to manual_frame
		"mov r1, sp\n"
		"blx Recover_PPB_Access\n"  // branch to the recover PPB access function to perform the simulation 

		"cbnz r0, .PPB_RECOVERY_ERROR\n"		// error during recovery
		"pop {r4,r5,r6,r7,r8,r9,r10,r11,lr}\n"  // in case of no errors, restore stack state
		"bx lr\n"								// return

		".PPB_RECOVERY_ERROR:\n" // in case of error during recovery, trigger a soft reset
		"bkpt\n"
		"b soft_reset\n"
	);
}

/*
* MCU-Fortifier microvisor SVC_Handler can be invoked for 2 reasons: 
* - There is the need to simulate of a system istruction (the SVC was called due to the code instrumentation).  
* 	In that case the instruction is simulated and the exception return is performed 
* - Otherwise the original SVC_Handler is performed
*/
void Microvisor_SVC_Handler() {
	__asm__(
		/* Move pre-exception entry SP to R0 */
		"tst lr, #4\n"
		"ite eq\n"
		"mrseq r0, msp\n"
		"mrsne r0, psp\n"

		/* Check for system instruction usage (after SVC instruction) */
		"push {r4,r5,r6,r7,r8,r9,r10,r11,lr}\n" //push rest of registers to manual_frame
		"mov r1, sp\n"
		/* branch to the recover system instruction function to perform the simulation */
		"blx Recover_System_Instruction\n"
		"pop {r4,r5,r6,r7,r8,r9,r10,r11,lr}\n"  //restore stack state
		
		/* Check if system instruction was simulated */
		"cbnz r0, .EXEC_REAL_SVC\n"	//when no system instruction simulation was requested, execute SVC_Handler
		"bx lr\n"					//system instruction simulated, perform exception return

		/* Execute deprioritized SVC handler */
		".EXEC_REAL_SVC:\n"
		"tst lr, #4\n"
		"ite eq\n"
		"mrseq r0, msp\n"
		"mrsne r0, psp\n"
		"ldr r3,[r0, #24]\n"	// load RetAddr
		"ldrb r3,[r3, #-2]\n"	// load SVC number in r3
		"b Exception_Catcher\n" // branch to the exception catcher to perform the exception handling
	);
}

/**
 *  MCU-Fortifier microvisor MemManage_Handler:
 *  Detect if the fault is caused by an MPU violation and execute the MPU violation handler
 */
void Microvisor_MemManage_Handler() {
	__asm__(
		/* Move pre-exception entry SP to R0 */
		"tst lr, #4\n" // check which stack pointer is in use
		"ite eq\n"
		"mrseq r0, msp\n"
		"mrsne r0, psp\n"

		/* Check for MPU violation */
		"push {r4,r5,r6,r7,r8,r9,r10,r11}\n" //push rest of registers to manual_frame
		"mov r1, sp\n"
		"blx MPU_Violation_Handler\n" // branch to the MPU violation handler
	);
}