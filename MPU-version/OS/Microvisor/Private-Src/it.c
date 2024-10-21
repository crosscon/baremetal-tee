#include "stm32l475vg_mpu.h"
#include "memory_map.h"
#include "it.h"
#include "tee_common.h"
#include "tee_client_api.h"
#include "internal_core_api.h"

// Declare the structure used to store the parameters passed by the client to the TA
// The structure is placed in the TEE_TA_data section of the binary
// This section is part of the RAM of the client application (see the linker script)
TEE_Param  __attribute__((section(".TEE_TA_data"))) ta_params[4] = {0};


/**
 * @brief Function to call a Trusted Application (TA) Client API from the Client Application (CA)
 * This function is called by the SVC Handler when the SVC number corresponds to a TA Client API
 * and it is responsible to manage the switch of context from the non secure world to the secure world,
 * including the MPU reconfiguration and the stack pointer change
 * 
 * @param auto_frame: pointer to the auto frame (stack frame) 
 * @param manual_frame: pointer to the manual frame (stack frame)
 */
__attribute__((naked,section(".microvisor-nopri"))) void call_TA(unsigned int* auto_frame, unsigned int* manual_frame) {

	/* Restore the partial context (r4-r11) that was there at the moment of the API call */
	__asm__(
		"pop {r4,r5,r6,r7,r8,r9,r10,r11}\n"
	);

	int ret_val = -1; // Declare a variable to store the return value
	int ta_num = 1; // Declare a variable to store the TA number (default value is 1, but can also be 2)

	// Recover the value of SVC number, which was stored in r3 in the SVC Handler
	// Store the value in a C variable
	int svc_num = -1;
	__asm__(
		"mov %[svc_num], r3\n"
		: [svc_num] "=r" (svc_num)
	);

	// If the SVC number is not passed (or is not valid), return with an error
	if (svc_num == -1) {
		ret_val = TEE_FAILED;
		goto exit;
	}
 
	// Declare a variable to store the internal operation (used to pass the parameters from the client to the core)
	internal_operation_t *internal_op = {0};
	// The internal operation is passed only in the case of the following functions: 
	// FUNCTION_INIT_CONTEXT, FUNCTION_OPEN_SESSION, FUNCTION_INVOKE_COMMAND
	// In the other cases (FUNCTION_FINALIZE_CONTEXT, FUNCTION_CLOSE_SESSION), the TA number is passed directly
	if(svc_num == FUNCTION_INIT_CONTEXT || svc_num == FUNCTION_OPEN_SESSION || svc_num == FUNCTION_INVOKE_COMMAND) {

		// Extract the internal operation from r4 (first element of the manual frame) 
		// which contains all the information passed by the TA (UUID, parameters, etc.)
		internal_op = (internal_operation_t*)(manual_frame[0]);

	    // If the internal operation is null, return with an error
	    if(!internal_op){
			ret_val = TEE_FAILED;
	        goto exit;
	    }

		// Extract the TA number from the internal operation
		ta_num = internal_op->id;
	} else {
		// Extract the TA number from the manual frame (passed in r4)
		ta_num = (int) manual_frame[0];
	}

	// Extract the command ID from the manual frame (passed in r5)
	// This is the command_id is used only when the SVC number is equal to FUNCTION_INVOKE_COMMAND (4)
	int command_id = manual_frame[1]; 

	// Check if the SVC number is equal to FUNCTION_OPEN_SESSION (2) or FUNCTION_INVOKE_COMMAND (4)
	// In these cases, the parameters are passed by TA inside the memory area used by the internal operation
	// They need to be extracted and stored in the format used by the TA (TA_Param)
	if((svc_num == FUNCTION_OPEN_SESSION)  || (svc_num == FUNCTION_INVOKE_COMMAND)) {
		for(int i=0; i<4; i++) {
            // internal_op parameter carry the payload as a void pointer so we need to type cast it to TEEC_Parameter
			TEEC_Parameter *ca_params = (TEEC_Parameter*)internal_op->params[i];
			int type = TEE_PARAM_GET_TYPES(internal_op->paramTypes, i);

			if(ca_params) {
				// Copy the memory reference params from the TEEC_Param structure to TA_Param structure
				if(ca_params->memref.parent != NULL) {
					ta_params[i].memref.buffer = ca_params->memref.parent->buffer;
					ta_params[i].memref.size = ca_params->memref.parent->size;
				}
				
				// Copy the temporary memory reference params from the TEEC_Param structure to TA_Param structure
				if(ca_params->tmpref.buffer != NULL) {
					ta_params[i].memref.buffer = ca_params->tmpref.buffer;
					ta_params[i].memref.size = ca_params->tmpref.size;
				}

				// Copy integer params from the TEEC_Param structure to TA_Param structure only if they are input or in-out params
				if(type == TEE_PARAM_TYPE_VALUE_INPUT || type ==  TEE_PARAM_TYPE_VALUE_INOUT) {
					ta_params[i].value.a = ca_params->value.a;
					ta_params[i].value.b = ca_params->value.b;
				}
			}
		} 
	}

	/**
	 * Reconfigure dynamically the MPU and the various region
	 * This allow the execution of the TA code and the access to the TA memory
	 * Access to the client application memory is guaranteed 
	 * Isolation between the TA and the Fortier/other TAs is enforced
	 * The MPU reconfiguration is done based on the TA number passed as parameter (ta_num)
	 */
	Reconfigure_MPU(ta_num);

	// Change the value of the PSP (process stack pointer) to point to the TA memory
	// TODO: evaluate if we need to modify the PSP to a different value after the execution of the first function of the TA 
	if(ta_num == 1){
		__asm__(
			".equ STACK_PSP_START, (0x20000000 + (48 *1024) -1)\n"
			"ldr r0, =STACK_PSP_START\n"
			"msr psp, r0\n"
		);
	} else {
		__asm__(
			".equ STACK_PSP_START, (0x20000000 + (96 *1024) -1)\n"
			"ldr r0, =STACK_PSP_START\n"
			"msr psp, r0\n"
		);	
	}
	
	// Switch the SP used from MSP to PSP and drop privileges before passing the control to the TA function
	__asm__(
		"mov r0, #0X03\n"
		"msr control, r0\n"
	);

	// Call the TA function (API offered by the TA accordingly the GlobalPlatform TEE specification) based on the SVC number and the TA number
	// You can see that the name of the function is composed by:
	// - the prefix TA_ 
	// - and the name of the function in the TEE Client API
	// - 1 or 2
	// The last part refers to the TA number. 
	// As it is not possible to have the same function with the same name at the same time for both TAs (linker error),
	// a simple solution was to append the TA number to the function name while still allowing the TAs to use 
	// the function without the suffix. How is that possible? The makefile is configured to replace the functions name
	// in the TA source code: for the TA1, the function TA_CreateEntryPoint is replaced with TA_CreateEntryPoint1,
	// for the TA2, the function TA_CreateEntryPoint is replaced with TA_CreateEntryPoint2. This applies to all 5 the GP Client
	// API functions
	switch(svc_num)
	{
		case FUNCTION_INIT_CONTEXT:
            // Call TA_CreateEntryPoint, corresponding to the TEEC_InitializeContext() function of the TEE Client API
            ret_val = (ta_num == 1) ? TA_CreateEntryPoint1() : TA_CreateEntryPoint2();
			break; 
		case FUNCTION_FINALIZE_CONTEXT:
            // Call TA_DestroyEntryPoint, corresponding to TEEC_FinalizeContext() function
            (ta_num == 1) ? TA_DestroyEntryPoint1() : TA_DestroyEntryPoint2();
			// The function does not have any return value, so we set the return value to TEE_SUCCESS
			ret_val = TEE_SUCCESS;
			break;

		case FUNCTION_OPEN_SESSION:
            // Call TEE_openTASession, corresponding to TEEC_OpenSession() function
			// TODO: ask if it was an implementation choice to not pass the session
			if (ta_num == 1) 
				ret_val = TA_OpenSessionEntryPoint1(internal_op->paramTypes, ta_params, NULL);
			else 
				ret_val = TA_OpenSessionEntryPoint2(internal_op->paramTypes, ta_params, NULL);
			
			// No out params are used inside this fuction, so there is no need to trasfer back the modifications
			// to the TEEC_Param structure. Just need to reset the TA_Params structure
			for(int i=0; i<4; i++) {
				ta_params[i].memref.buffer = NULL;
				ta_params[i].memref.size = 0;
				ta_params[i].value.a = 0;
				ta_params[i].value.b = 0;
			}
			break;

		case FUNCTION_CLOSE_SESSION:
            // Call TA_closeSessionEntryPoint, corresponding to TEEC_CloseSession() function
			// TODO: ask if it was an implementation choice to not pass the session
            (ta_num == 1) ? TA_CloseSessionEntryPoint1(NULL) : TA_CloseSessionEntryPoint2(NULL);
			// The function does not have any return value, so we set the return value to TEE_SUCCESS
			ret_val = TEE_SUCCESS;
			break;

		case FUNCTION_INVOKE_COMMAND:
            // Call TA_invokeCommandEntryPoint, correspond to TEEC_InvokeCommand() function
			// TODO: ask if it was an implementation choice to not pass the session
			if (ta_num == 1) 
				ret_val = TA_InvokeCommandEntryPoint1(NULL, command_id, internal_op->paramTypes, ta_params);
			else 
				ret_val = TA_InvokeCommandEntryPoint2(NULL, command_id, internal_op->paramTypes, ta_params);

			// Copy back the parameters from the TA_Param structure to the TEEC_Param structure
			// This is done only for the output and in-out parameters
			for(int i=0; i<4; i++) {
			
				TEEC_Parameter *ca_params = (TEEC_Parameter*)internal_op->params[i];
				int type = TEE_PARAM_GET_TYPES(internal_op->paramTypes, i);

				// Copy the integer params from the TA_Param structure to TEEC_Param structure
				if(type == TEE_PARAM_TYPE_VALUE_OUTPUT || type ==  TEE_PARAM_TYPE_VALUE_INOUT) {
					ca_params->value.a = ta_params[i].value.a;
					ca_params->value.b = ta_params[i].value.b;
				}

				// Copy only the size of the memory reference params from the TA_Param structure to TEEC_Param structure
				// The buffer is already allocated in the client application memory and the TA should not modify it
				if(ta_params[i].memref.buffer != NULL && (type == TEE_PARAM_TYPE_MEMREF_OUTPUT || type == TEE_PARAM_TYPE_MEMREF_INOUT)) {
					if (ca_params->memref.parent != NULL) {
						ca_params->memref.parent->size = ta_params[i].memref.size;
						ca_params->memref.size = ta_params[i].memref.size;	
					} else {
						ca_params->tmpref.size = ta_params[i].memref.size;
					}
				}
			}
			
			// Reset the TA_Params structure
			for(int i=0; i<4; i++) {
				ta_params[i].memref.buffer = NULL;
				ta_params[i].memref.size = 0;
				ta_params[i].value.a = 0;
				ta_params[i].value.b = 0;
			}
			break;

		default:
			// None of the Client API functions was called, return with an error
			ret_val = TEE_FAILED;
			goto exit;
	}

exit:
	// Copy the return value to r4, where the value is expected by the client application
	__asm__("MOV R4, %[ret_val]\n": : [ret_val] "r" (ret_val): "r4");
	__asm__(
		/* Trigger HardFault to perform return sequence from API */
		/* Since we are executing unprivileged code, an illegal access to the PPB will trigger a HardFault */
		/* No need to modify back the SP to MSP from the PSP as the Hard Fault handler uses by default the MSP */
		".global API_RET_START\n" // define a globally visible label to be used in the exception return handler
		".global API_RET_END\n"  // define a globally visible label to be used in the exception return handler
		"API_RET_START:\n"
		"ldr r0, =0xe000e000\n"	// load SCB address
		"ldrt r0, [r0]\n"	// perfom unprivileged read
		".LOOP:\n"	// wait for HardFault
		"b .LOOP\n"
		"API_RET_END:\n"
	);
}


/**
 * @brief Function to call the Trusted Execution Environment (TEE) Core API from a Trusted Application (TA)
 */
void call_TEE(unsigned int* auto_frame, unsigned int* manual_frame) {

	int ret_val = 0; // Declare a variable to store the return value

	int svc_num = -1;
	register uintptr_t sp_value = 0;

	// Recover the value of the stack pointer (SP) from r2 register
	// and the value of SVC number from r3 register and store them in C variables
	// These two values were placed in the registers by the SVC Handler
	__asm__(
		"mov %[sp_value], r2\n"
		"mov %[svc_num], r3\n"
		: [sp_value] "=r" (sp_value), [svc_num] "=r" (svc_num)
		: 
		: "r2", "r3"
	);

	// The SP value is used to check if the SP at the moment of the SVC call
	// points to a memory area allocated for a TA or a CA
	// If the SP value is not in the range of the TA memory, return with an error
	// This is done to ensure that only TAs can call TEE Core API 
	// that run in the secure world with privileged access
	if (sp_value < TA1_MEMORY_START_ADDR || sp_value > TA2_MEMORY_END_ADDR) {
		ERR_MSG("Unstrusted applications can not execure privileged TEE Core API directly, exiting");
		ret_val = TEE_FAILED;
		return;
	}

	// If the SVC number is not passed (or is not valid), return with an error
	if (svc_num == -1) {
		ret_val = TEE_FAILED;
		return;
	}

	// Based on the SVC number, call the internal implementation of the TEE Core API
	// Each case corresponds to a function of the TEE Core API that offers services to the TAs
	switch (svc_num) {
		case FUNCTION_MALLOC:
			// Extract the parameters from the manual frame and pass them to the internal implementation of TEE Core API
			// As the values were passed in the registers to the SVC Handler, they are stored in the manual frame
			ret_val = internal_TEE_Malloc(manual_frame[0], manual_frame[1], manual_frame[2]);
			break;
		case FUNCTION_FREE:
			internal_TEE_Free(manual_frame[0], (void*)manual_frame[1]);
			break;
		case FUNCTION_MEM_MOVE:
			internal_TEE_MemMove(manual_frame[0], (void*)manual_frame[1], (void*)manual_frame[2], manual_frame[3]);
			break;
		case FUNCTION_MEM_FILL:
			internal_TEE_MemFill(manual_frame[0], (void*)manual_frame[1], manual_frame[2], manual_frame[3]);
			break;
		case FUNCTION_BIG_INT_CONVERT_TO_S32:
			ret_val = internal_TEE_BigIntConvertToS32((int32_t*)manual_frame[0], (TEE_BigInt*)manual_frame[1]);
			break;
		case FUNCTION_BIG_INT_CMP_S32:
			ret_val = internal_TEE_BigIntCmpS32((TEE_BigInt*)manual_frame[0], manual_frame[1]);
			break;
		case FUNCTION_BIG_INT_MOD:
			internal_TEE_BigIntMod((TEE_BigInt*)manual_frame[0], (TEE_BigInt*)manual_frame[1], (TEE_BigInt*)manual_frame[2]);
			break;
		case FUNCTION_BIG_INT_DIV:
			internal_TEE_BigIntDiv((TEE_BigInt*)manual_frame[0], (TEE_BigInt*)manual_frame[1], (TEE_BigInt*)manual_frame[2], (TEE_BigInt*)manual_frame[3]);
			break;
		case FUNCTION_BIG_INT_CONVERT_FROM_OCTET_STRING:
			ret_val = internal_TEE_BigIntConvertFromOctetString((TEE_BigInt*)manual_frame[0], (uint8_t*)manual_frame[1], manual_frame[2], manual_frame[3]);
			break;
		case FUNCTION_BIG_INT_INIT:
			internal_TEE_BigIntInit((TEE_BigInt*)manual_frame[0], manual_frame[1]);
			break;
		case FUNCTION_ALLOCATE_TRANSIENT_OBJECT:
			ret_val = internal_TEE_AllocateTransientObject(manual_frame[0], manual_frame[1], manual_frame[2]);
			break;
		case FUNCTION_POPULATE_TRANSIENT_OBJECT:
			ret_val = internal_TEE_PopulateTransientObject(manual_frame[0], manual_frame[1], manual_frame[2]);
			break;
		case FUNCTION_INIT_REF_ATTRIBUTE:
			internal_TEE_InitRefAttribute(manual_frame[0], manual_frame[1], manual_frame[2], manual_frame[3]);
			break;
		case FUNCTION_INIT_VALUE_ATTRIBUTE:
			internal_TEE_InitValueAttribute(manual_frame[0], manual_frame[1], manual_frame[2], manual_frame[3]);
			break;
		case FUNCTION_GET_OBJECT_BUFFER_ATTRIBUTE:
			ret_val = internal_TEE_GetObjectBufferAttribute(manual_frame[0], manual_frame[1], (void*)manual_frame[2], manual_frame[3]);
			break;
		case FUNCTION_GET_OBJECT_VALUE_ATTRIBUTE:
			ret_val = internal_TEE_GetObjectValueAttribute(manual_frame[0], manual_frame[1], (uint32_t*)manual_frame[2], (uint32_t*)manual_frame[3]);
			break;
		case FUNCTION_FREE_TRANSIENT_OBJECT:
			internal_TEE_FreeTransientObject(manual_frame[0]);
			break;
		case FUNCTION_CLOSE_OBJECT:
			internal_TEE_CloseObject(manual_frame[0]);
			break;
		case FUNCTION_READ_OBJECT_DATA:
			ret_val = internal_TEE_ReadObjectData(manual_frame[0], (void*)manual_frame[1], manual_frame[2], (size_t*)manual_frame[3], manual_frame[4]);
			break;
		case FUNCTION_WRITE_OBJECT_DATA:
			ret_val = internal_TEE_WriteObjectData(manual_frame[0], (void*)manual_frame[1], manual_frame[2], manual_frame[3]);
			break;
		case FUNCTION_CREATE_PERSISTENT_OBJECT:
			ret_val = internal_TEE_CreatePersistentObject(manual_frame[0], manual_frame[1], manual_frame[2], manual_frame[3], manual_frame[4], manual_frame[5], manual_frame[6], manual_frame[7]);
			break;
		case FUNCTION_OPEN_PERSISTENT_OBJECT:
			ret_val = internal_TEE_OpenPersistentObject(manual_frame[0], manual_frame[1], manual_frame[2], manual_frame[3], manual_frame[4]);
			break;
		case FUNCTION_CLOSE_DELETE_PERSISTENT_OBJECT:
			ret_val = internal_TEE_CloseAndDeletePersistentObject1(manual_frame[0], manual_frame[1]);
			break;
		case FUNCTION_ALLOCATE_OPERATION:
			ret_val = internal_TEE_AllocateOperation(manual_frame[0], manual_frame[1], manual_frame[2], manual_frame[3]);
			break;
		case FUNCTION_FREE_OPERATION:
			internal_TEE_FreeOperation(manual_frame[0]);
			break;
		case FUNCTION_SET_OPERATION_KEY:
			ret_val = internal_TEE_SetOperationKey(manual_frame[0], manual_frame[1]);
			break;
		case FUNCTION_SET_OPERATION_KEY2:
			// NOTE: This function is not implemented in the TEE Core API
			//ret_val = internal_TEE_SetOperationKey2(manual_frame[0], manual_frame[1], manual_frame[2]);
			break;
		case FUNCTION_GENERATE_KEY:
			ret_val = internal_TEE_GenerateKey(manual_frame[0], manual_frame[1], manual_frame[2], manual_frame[3], manual_frame[4]);
			break;
		case FUNCTION_GENERATE_RANDOM:
			internal_TEE_GenerateRandom(manual_frame[0], manual_frame[1]);
			break;
		case FUNCTION_DERIVE_KEY:
			// NOTE: This function is not implemented in the TEE Core API
			//ret_val = internal_TEE_DeriveKey(manual_frame[0], manual_frame[1], manual_frame[2], manual_frame[3]);
			break;
		case FUNCTION_CIPHER_INIT:
			internal_TEE_CipherInit(manual_frame[0], manual_frame[1], manual_frame[2]);
			break;
		case FUNCTION_CIPHER_UPDATE:
			ret_val = internal_TEE_CipherUpdate(manual_frame[0], manual_frame[1], manual_frame[2], manual_frame[3], manual_frame[4]);
			break;
		case FUNCTION_CIPHER_DO_FINAL:
			ret_val = internal_TEE_CipherDoFinal(manual_frame[0], (void*)manual_frame[1], manual_frame[2], (void*)manual_frame[3], manual_frame[4]);
			break;
		case FUNCTION_MAC_INIT:
			internal_TEE_MACInit(manual_frame[0], manual_frame[1], manual_frame[2]);
			break;
		case FUNCTION_MAC_UPDATE:
			internal_TEE_MACUpdate(manual_frame[0], manual_frame[1], manual_frame[2]);
			break;
		case FUNCTION_MAC_COMPUTE_FINAL:
			ret_val = internal_TEE_MACComputeFinal(manual_frame[0], (void*)manual_frame[1], manual_frame[2], (void*)manual_frame[3], manual_frame[4]);
			break;
		case FUNCTION_DIGEST_UPDATE:
			internal_TEE_DigestUpdate(manual_frame[0], (void*)manual_frame[1], manual_frame[2]);
			break;
		case FUNCTION_DIGEST_DO_FINAL:
			ret_val = internal_TEE_DigestDoFinal(manual_frame[0], (void*)manual_frame[1], manual_frame[2], (void*)manual_frame[3], manual_frame[4]);
			break;
		case FUNCTION_DIGEST_EXTRACT:
			ret_val = internal_TEE_DigestExtract(manual_frame[0], manual_frame[1], manual_frame[2]);
			break;
		case FUNCTION_ASYMMETRIC_SIGN_DIGEST:
			ret_val = internal_TEE_AsymmetricSignDigest(manual_frame[0], manual_frame[1], manual_frame[2], manual_frame[3], manual_frame[4], manual_frame[5], manual_frame[6]);
			break;
		case FUNCTION_ASYMMETRIC_VERIFY_DIGEST:
			ret_val = internal_TEE_AsymmetricVerifyDigest(manual_frame[0], manual_frame[1], manual_frame[2], manual_frame[3], manual_frame[4], manual_frame[5], manual_frame[6]);
			break;
		default:
			break;
	}

	// Copy the return value to r4, where the value is expected by entry point of the TEE Core API
	__asm__("MOV R0, %[ret_val]\n": : [ret_val] "r" (ret_val): "r0");
}

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
* - The SVC was called by the client application to perform a Global Platform API call (SVC number is in the range 0-4)
* 	In that case the API call is performed and the exception return is performed
* - The SVC was called by a trusted application to perform a TEE Core API call (SVC number is in the range 5-50)
* 	In that case the API call is performed and the execution is returned to the trusted application
* - Otherwise the original SVC_Handler is performed
* 
* Notes on PARAMETER PASSING CONVENTION FOR SVC for both Client and Core API calls:
* - use registers from r4 to r11 to pass parameters to SVC 
* - save the current value of the registers used in a temporary variable before overwriting them
* - restore the value of the registers after the SVC call
* - use r4 to get the return value of the SVC invocation
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
		".EXEC_REAL_SVC:\n" // check which stack pointer is in use
		"tst lr, #4\n"
		"ite eq\n"
		"mrseq r0, msp\n"
		"mrsne r0, psp\n"
		"ldr r3,[r0, #24]\n"	// load RetAddr
		"ldrb r3,[r3, #-2]\n"	// load SVC number in r3
		
		/** The SVC number is stored in R3 at this point 
		* Need to check if the value is in a particular range (0-50): 
		* - if so, we are in the case of a Global Platform API call and need to perform that call 
		* => in the case of values in the range 0-4 a GP Client API was called and after the execution, 
		*	  the exception return process should be executed
		* => in the case of values in the range 5-50 a TEE Core API was called
		* - otherwise we perform the original SVC_Handler (the one of the Fortfiied application) */
		"cmp r3, #4\n" // compare r3 with 4
		"ble .TA_API\n" // if less or equal, branch to .TA_API (call of a trusted application function)
		"cmp r3, #50\n" // compare r3 with 50
		"ble .TEE_API\n" // if less or equal, branch to .TEE_API (call of a TEE core function)
		"b Exception_Catcher\n" // if greater, branch to the exception catcher to perform the normal exception handling

		// CASE OF TA CLIENT API CALL:
		// Use the same approach used for the Exception_Catcher/Simulation/Return to:
		// - Save the context and create a fake return frame
		// - Exit the current SVC handler (and the relative handler mode)
		// - Reconfigure the MPU
		// - Execute the API call and the API code without privileges
		// - Regain the privileges (using an HardFault exception) 
		// - Reconfigure the MPU to the original configuration
		// - Return to the original context before the SVC
		".TA_API:\n"

		/* Save BASEPRI (execution priority of pre-empted code) and EXC_RETURN */
		"mrs r0, BASEPRI\n"
		"push {r0,lr}\n"

		/* Set CTRL.nPRIV to 0 (the call should happen in privileged mode) */
		"mrs r0, CONTROL\n"
		"and r0, #0\n"
		"msr CONTROL, r0\n"

		/* Save remaining context that was there at the moment of the call to MSP */
		"push {r4,r5,r6,r7,r8,r9,r10,r11}\n"
		"mov r1, sp\n"
		/* Create fake return frame */
		"mov r7, #0x1000000\n"	// xPSR (thumb bit to 1, everything else 0)
		"ldr r6, =call_TA\n"	// Set the address of my_function as RetAddr

		/* Save fake return frame on MSP */
		"push {r0,r1,r2,r3,r4,r5,r6,r7}\n" 
		
		/* Setup EXC_RETURN */
		"ldr lr, =0xfffffff9\n"	// always return to Thread mode with Main stack in use

		/* Return and execute Exception_Simulator right after it (due to the fake return frame created)*/
		"bx lr\n"

		// CASE OF TEE CORE API CALL:
		// Use a simpler approach as the Core API is executed in privileged mode
		// and no reconfguration of the MPU is needed:
		// - Save the value of the SP (stack pointer) in r2
		// - Save the value of the SVC number in r3
		// - Save the context
		// - Call the function to execute the TEE Core API 
		// - Restore the context
		// - Copy the return value to r4, where the value is expected
		// - Switch the PSP used by the TA and drop the privileges
		// - Return to the original context before the SVC
		".TEE_API:\n"

		// copy the value of r0 (which contains information about the stack used at the moment of the call) to r2
		// this information is extracted from the LR (link register) and it is used to test 
		// if the SVC was invoked by a TA or by a CA by checking if the value is in the range
		// of TAs RAM memory (0x20000000 - 0x200FFFFF). Only in this case the Core API is executed
		"mov r2, r0\n"

		/* Set CTRL.nPRIV to 0 (TEE core call should happen in privileged mode) */
		"mrs r0, CONTROL\n"
		"and r0, #0\n"
		"msr CONTROL, r0\n"

		"push {r4,r5,r6,r7,r8,r9,r10,r11,lr}\n" //push rest of registers to manual_frame
		"blx call_TEE\n"  // call an internal TEE Core function
		"pop {r4,r5,r6,r7,r8,r9,r10,r11,lr}\n"  //restore stack state

		"mov R4, R0\n" // copy the return value to r4, where the value is expected by the client application;

		// Switch the SP used from the MPS to PSP and drop the privileges
		// as the TAs uses the PSP and the execution is done in unprivileged mode
		"mov r0, #0X03\n"
		"msr control, r0\n"

		"bx lr\n"
	);
}

/**
 *  MCU-Fortifier microvisor MemManage_Handler:
 *  Detect if the fault is caused by an MPU violation and execute the MPU violation handler
 */
void Microvisor_MemManage_Handler() {
	ERR_MSG("MPU violation detected");
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
