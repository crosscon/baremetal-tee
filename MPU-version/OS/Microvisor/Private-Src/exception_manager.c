#include "exception_manager.h"
#include "stm32l4xx_hal.h"
#include "core_cm4.h"
#include "it.h"

#define PRIGROUP_MASK	0b11100000000
#define PRIGROUP_SHIFT	8

/**
 * Given an exception number, returns the execution priority (group priority)
 * of the specified exception.
 * 
 * Parameters:
 * exception_number: number of the exception (1 = Reset)
 * 
 * Returns:
 * execution priority of the specified exception
 */
int Get_Exception_Priority(int exception_number) {
	uint8_t pri_bits;
	/* Fixed priorities handlers */
	switch (exception_number)
	{
		case 1:	// Reset
			return -3;
		case 2:	// NMI
			return -2;
		case 3:	// HardFault
			return -1;
	}
	if (4 <= exception_number && exception_number <= 15) {
		/* System handlers */
		pri_bits = SCB->SHP[exception_number];
	} else {
		/* External interrupts */
		/* The mapping between the extern interrup number and the exception number is shifted by 16 */
		pri_bits = NVIC->IP[exception_number - 16];	// external interrupt 0 = exception 16
	}
	int pri_group = SCB->AIRCR & PRIGROUP_MASK >> PRIGROUP_SHIFT;
	pri_bits = pri_bits >> (pri_group + 1);	// isolate group priority
	
	return pri_bits;
}

/**
 * Default handler used inside Vector Table
 * Catches exception and saves key context information on stack
 * After the execution of this handler the stacks are in the following state
 * (displayed in descending order):
 * 	- pre-entry stack (PSP or MSP)
 * 		...,xPSR,RetAddr,LR,r12,r3,r2,r1,r0
 * 	- MSP additionally contains
 * 		...,EXC_RETURN,BASEPRI,padding,virtual_IPSR,r11,r10,r9,r8,r7,r6,r5,r4
 * The 8-byte alignment of the stack is maintained (if present).
 * 
 * Before ending execution, the functions creates a fake return frame that
 * results in the execution of Exception_Simulator immediately after
 * exception return while passing the parameters required.
 * 
 * Why save BASEPRI and EXC_RETURN?
 * BASEPRI: if the exception pre-empted another deprioritized interrupt execution, than it's necessary
 * to save its priority in order to restore it later (once this new deprioritized interrupt
 * has been handled) otherwise the restored code would execute with the wrong priority!
 * Note that the priority of the pre-empted deprioritized interrupt will be certainly stored in BASEPRI
 * because it must be lower than 0 (since the currently running code cannot have priority
 * higher than 0 and was able to successfully pre-empt the previously executing one)
 * If BASEPRI has value 0, it means that "regular" code running at the lowest possible
 * priority (since BASEPRI set to 0 does not mask priority) was pre-empted.
 * 
 * EXCRETURN: this value must be stored in order to set the correct stack and mode when returning
 * form the Exception_Simulator routine.
 * 
 */
__attribute__((naked)) void Exception_Catcher() {
	__asm__(
		/* Disable interrupts, note that FAULTMASK will be cleared on return from exception */
		"cpsid if\n"

		/* Save BASEPRI (execution priority of pre-empted code) and EXC_RETURN */
		"mrs r0, BASEPRI\n"
		"push {r0,lr}\n"

		/* Save virtual_IPSR and padding (to preserve stack alingment) */
		"ldr r0, =_virtual_IPSR\n"
		"ldr r0, [r0]\n"
		"mvn r1, #0\n"
		"push {r0,r1}\n"
		
		/* Set CTRL.nPRIV to 0 (must allow Execution Simulator to act in privileged mode) */
		"mrs r0, CONTROL\n"
		"and r0, #0\n"
		"msr CONTROL, r0\n"

		/* Save remaining context to MSP */
		"push {r4,r5,r6,r7,r8,r9,r10,r11}\n"

		/* Create fake return frame */
		"mov r7, #0x1000000\n"	// xPSR (thumb bit to 1, everything else 0)
		"ldr r6, =Exception_Simulator\n"	// Set the address of Exception_Simulator function as RetAddr
		// r5 (LR value) dont care
		// r4 (r12 value) dont care
		// r3 SVC number (only during SVC handling)
		// r2 dont care
		"mrs r0, IPSR\n" // set exception to execute
		"push {r3}\n"
		"bl Get_Exception_Priority\n" // get priority of the exception (return value saved in r0)
		"pop {r3}\n"
		"mov r1, r0\n"	// execution priority
		"mrs r0, IPSR\n"	// set exception to execute
		// MSP will point to custom frame after return from exception

		/* Save fake return frame on MSP */
		"push {r0,r1,r2,r3,r4,r5,r6,r7}\n" 
		
		/* Setup EXC_RETURN */
		"ldr lr, =0xfffffff9\n"	// always return to Thread mode with Main stack in use

		/* Return and execute Exception_Simulator right after it (due to the fake return frame created)*/
		"bx lr\n"
	);
}

/**
 * Executes ISR without privileges
 * Works only when two assumptions are satisfied:
 * 1. The ISR never uses any context form the pre-empted code
 * (in particular: registers r0-r3, r12, pre-entry-sp, lr)
 * 2. The ISR leaves the MSP in the same state after its execution
 * (key information needs to be retrieved from stack after execution)
 * 
 * After the execution of the ISR the function should re-gain privileges and setup
 * for the return to the pre-empted execution, unfortunatly this cannot be done
 * straightforward for two reasons:
 * 1. CONTROL.nPRIV is set to 1 (no privileges) and cannot be changed from Thread mode.
 * 2. Writes to EPSR are ignored, meaning that the only way to restore the context is with
 * a proper exception return.
 * 
 * For these reason a HardFault is triggered on purpuse after the ISR request
 * This HardFault is used to perform the return to the pre-empted execution.
 * 
 * Parameters:
 * - exception_number: number of the exception 
 * - exception_priority: execution priority of the exception
 */
__attribute__((naked, section(".microvisor-nopri"))) void Exception_Simulator(int exception_number, int exception_priority) {
	__asm__(
		/* Set virtual IPSR value */
		"ldr r2, =_virtual_IPSR\n"
		"str r0, [r2]\n" // Store in the virtual_IRSR the exception number (passed as parameter in r0)

		/* Set execution priority */
		"cmp r1, #0\n"
		"blt .PRI_ERROR\n"	// requested priority greater than 0 (e.g -1): error
		"cmp r1, #0\n"
		"beq .PRI_SET\n"	// requested priority 0, already set (branch to .PRI_SET label)
		"msr BASEPRI, r1\n"	// requested priority lower than 0, set BASEPRI
		"cpsie i\n"			// and enable interrupts
		"b .PRI_SET\n"
		".PRI_ERROR:\n"   // in case of error, trigger a soft reset
		"bkpt\n"
		"b soft_reset\n"
		".PRI_SET:\n"

		/* Remove privilege inside thread mode */
		"mrs r2, CONTROL\n"
		"orr r2, r2, #1\n"
		"msr CONTROL, r2\n"
		
		/* Execute ISR */
		"ldr r2, =__flash_start__\n"	// load original vector table address
		"ldr r2, [r2, r0, lsl #2]\n"	// load handler address: base vector table (r2) + exception offset(r0)
		"mov r0, r3\n"	// copy SVC num to r0 in case of SVC interrupt being handled
		"pop {r4,r5,r6,r7,r8,r9,r10,r11}\n"	// restore partial context (r4-r11)
		"blx r2\n"	// branch to handler (to perform the ISR)
		
		/* Trigger HardFault to perform return sequence */
		/* Since we are executing unprivileged code, an access to the PPB will trigger a HardFault */
		".global EXC_RET_START\n" // define a globally visible label to be used in the exception return handler
		".global EXC_RET_END\n"  // define a globally visible label to be used in the exception return handler
		"EXC_RET_START:\n"
		"ldr r0, =0xe000e000\n"	// load SCB address
		"ldrt r0, [r0]\n"	// perfom unprivileged read
		".LOOP:\n"	// wait for HardFault
		"b .LOOP\n"
		"EXC_RET_END:\n"
	);
}

/**
 * Performs exception return to previosly pre-empted execution
 * setting correctly the priority and the context.
 * Only done when the HardFault originates form a pre-determined instruction range
 * (within the Exception_Simulator function).
 * 
 * Parameters:
 * - auto_frame: pointer to frame created automatically during exception entry
 */
__attribute__((naked)) void Exception_Return_Handler(unsigned int* auto_frame) {
	__asm__(
		"ldr r2, [r0, #24]\n"	// load faulty address (PC value before exception)
		
		/** 
		  * Check if a exception return was requested after the execution of a deprioritized handler
		  * This is done by comparing the address that caused the Hard Fault with boundries
		  * The addresses boundries are defined globally when simulating an exception 
		*/
		"ldr r3, =EXC_RET_START\n"
		"cmp r2, r3\n"
		"blo .NO_EXC_RET_REQUESTED\n" // PC is less than EXC_RET_START, no exception return was requested
		"ldr r3, =EXC_RET_END\n"
		"cmp r2, r3\n"
		"bhi .NO_EXC_RET_REQUESTED\n" // PC is greater than EXC_RET_END, no exception return was requested

		/* Exception return from deprioritezed handler requested */
		"add sp, #4\n"	// remove pushed LR (before function call) form MSP
		"cmp sp, r0\n"	// check where auto_frame is stored
		"itee eq\n"
		"addeq sp, #32\n"	// auto_frame stored on MSP, remove it
		"addne r0, #32\n"	// auto_frame stored on PSP: decrease pointer
		"msrne PSP, r0\n"	// and update PSP

		/* Clear CFSR (Configurable Fault Status Register) as the value was changed by the HardFault triggered on purpose */
		"ldr r2, =0xE000ED28\n" 
		"ldr r3, =0xFFFFFFFF\n" // clear all bits
		"str r3, [r2]\n"

		/* Restore virtual_IPSR and remove padding (to preserve stack alingment) */
		"pop {r2, r3}\n"	// unstack virtual_IPSR and padding
		"ldr r3, =_virtual_IPSR\n"
		"str r2, [r3]\n"

		/* Read and set BASEPRI */
		"pop {r3}\n"
		"msr BASEPRI, r3\n"
		/* Disable PRIMASK */
		"cpsie i\n"
		/* Write EXC_RETURN value to LR to perform the return from the exception */
		"pop {lr}\n"
		
		/**
		 *  No exeption return requested, check if a return from a Global Platform API was requested instead 
		 *  This is done by comparing the address that caused the Hard Fault with boundries
		 *  The addresses boundries are defined globally when calling the API 
		 */
		".NO_EXC_RET_REQUESTED:\n"
		"ldr r3, =API_RET_START\n"
		"cmp r2, r3\n"
		"blo .NO_API_RET_REQUESTED\n" // PC is less than API_RET_START, no return from api call was requested (return)
		"ldr r3, =API_RET_END\n"
		"cmp r2, r3\n"
		"bhi .NO_API_RET_REQUESTED\n" // PC is greater than API_RET_END, no return from api call was requested (return)

		/* API return requested */
		"add sp, #4\n"	// remove pushed LR (before function call) from MSP
		"cmp sp, r0\n"	// check where auto_frame is stored
		"itee eq\n"
		"addeq sp, #32\n"	// auto_frame stored on MSP, remove it
		"addne r0, #32\n"	// auto_frame stored on PSP: decrease pointer
		"msrne PSP, r0\n"	// and update PSP

		/* Clear CFSR (Configurable Fault Status Register) as the value was changed by the HardFault triggered on purpose */
		"ldr r2, =0xE000ED28\n" 
		"ldr r3, =0xFFFFFFFF\n" // clear all bits
		"str r3, [r2]\n"

        "add sp, #4\n" // remove pushed r4 (during API call) from MSP as we don't want to restore it (return value).
        /* Restore the pre call context to avoid leaks. */
        "pop {r5,r6,r7,r8,r9,r10,r11}\n"


		/* Read and set BASEPRI */
		"pop {r3}\n"
		"msr BASEPRI, r3\n"
		/* Disable PRIMASK */
		"cpsie i\n"
		/** 
		 * Reconfigure back the MPU to the original configuration used before the API call
		 * This enforce isolation and separation between TA and client applications
		 */
		"blx Configure_MPU\n"
		/* Write EXC_RETURN value to LR to perform the return from the exception (to the code called before the API call) */
		"pop {lr}\n"

		".NO_API_RET_REQUESTED:\n"
		"bx lr\n"
	);
}
