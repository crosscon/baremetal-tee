#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "defines.h"
#include "sifive_plic.h"

#include "tee_api_types.h"
#include "tee_client_api.h"
#include "tee_ta_api.h"

TEE_Param ta_params[4] = {0};
TEEC_Operation *shared_mem = (TEEC_Operation *) 0x80003000;

extern int _read(int, char*, size_t);
void uart_recv_handler();

int command = 0;
int32_t command_tokens[3];

extern uint32_t *result = (uint32_t *) 0x80003C00;

TEEC_Result call_TA(int call, int cmd_id);
enum command_token{READ, WRITE, READ_IN_UART, WRITE_IN_UART};

void go_to_normal(TEEC_Result ret_val)
{	
	// printf("Going to normal world\n");
	register uint32_t low;

    asm volatile("li a7, 99");

	__asm__ (
    	"mv a6, %0"    // Load the immediate value of call into a7
    	:              // Output operands (none here)
    	: "r" (ret_val)   // Input operand: the value of call
    	: "a6"         // Clobbered register
	);

    asm volatile("ecall" ::: "memory");
	
}

uint32_t* cycles = (uint32_t*)0x80003C00;

int main()
{
	int call, cmd;
	TEEC_Result ret_val = 0;
	
	while(1)
	{
		__asm__ (
			"sw a7, %0"    // Store the value of a7 in saved_a7
			:              // No output operands here
			: "m" (call) // Input operand: the address of saved_a7
			: "a7"         // Clobbered register
		);

		__asm__ (
			"sw a6, %0"    // Store the value of a7 in saved_a7
			:              // No output operands here
			: "m" (cmd) // Input operand: the address of saved_a7
			: "a6"         // Clobbered register
		);
		register uint32_t low;

		asm volatile (
			"rdcycle %0\n"
			: "=&r" (low)
		);

		*cycles = low;

		ret_val = call_TA(call, cmd);

		go_to_normal(ret_val);
	}

	return 0;
}


TEEC_Result call_TA(int call, int cmd_id){
	int ret_val = -1; // Declare a variable to store the return value
	// Declare a variable to store the internal operation (used to pass the parameters from the client to the TA)
	TEEC_Operation *internal_op = shared_mem;
	
	// Check if the SVC number is equal to FUNCTION_OPEN_SESSION (2) or FUNCTION_INVOKE_COMMAND (4)
	// In these cases, the parameters are passed by TA inside the memory area used by the internal operation
	// They need to be extracted and stored in the format used by the TA (TA_Param)
	if((call == FUNCTION_OPEN_SESSION)  || (call == FUNCTION_INVOKE_COMMAND)) {
		for(int i=0; i<4; i++) {
            // internal_op parameter carry the payload as a void pointer so we need to type cast it to TEEC_Parameter
			TEEC_Parameter *ca_params = &internal_op->params[i];
			int type = TEEC_PARAM_TYPE_GET(internal_op->paramTypes, i);

			if(type == TEEC_VALUE_INPUT || type ==  TEEC_VALUE_INOUT){
				ta_params[i].value.a = ca_params->value.a;
				ta_params[i].value.b = ca_params->value.b;
			} else if (type == TEEC_MEMREF_WHOLE || type == TEEC_MEMREF_PARTIAL_INPUT || type == TEEC_MEMREF_PARTIAL_OUTPUT
						|| type == TEEC_MEMREF_PARTIAL_INOUT) {
				ta_params[i].memref.buffer = ca_params->memref.parent->buffer;
				ta_params[i].memref.size = ca_params->memref.parent->size;
			} else if (type == TEEC_MEMREF_TEMP_INPUT || type == TEEC_MEMREF_TEMP_INOUT || type == TEEC_MEMREF_TEMP_OUTPUT) {
				ta_params[i].memref.buffer = ca_params->tmpref.buffer;
				ta_params[i].memref.size = ca_params->tmpref.size;
			}
		}
	}

	switch(call)
	{
		case FUNCTION_INIT_CONTEXT:
            // Call TA_CreateEntryPoint, corresponding to the TEEC_InitializeContext() function of the TEE Client API
            ret_val = TA_CreateEntryPoint();
			break; 
		case FUNCTION_FINALIZE_CONTEXT:
            // Call TA_DestroyEntryPoint, corresponding to TEEC_FinalizeContext() function
            TA_DestroyEntryPoint();
			// The function does not have any return value, so we set the return value to TEE_SUCCESS
			ret_val = TEE_SUCCESS;
			break;

		case FUNCTION_OPEN_SESSION:
			ret_val = TA_OpenSessionEntryPoint(internal_op->paramTypes, ta_params, NULL);
			
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
            TA_CloseSessionEntryPoint(NULL);
			// The function does not have any return value, so we set the return value to TEE_SUCCESS
			ret_val = TEE_SUCCESS;
			break;

		case FUNCTION_INVOKE_COMMAND:
            // Call TA_invokeCommandEntryPoint, correspond to TEEC_InvokeCommand() function
			// TODO: ask if it was an implementation choice to not pass the session
			ret_val = TA_InvokeCommandEntryPoint(NULL, cmd_id, internal_op->paramTypes, ta_params);

			// Copy back the parameters from the TA_Param structure to the TEEC_Param structure
			// This is done only for the output and in-out parameters
			for(int i=0; i<4; i++) {
			
				TEEC_Parameter *ca_params = &internal_op->params[i];
				int type = TEE_PARAM_TYPE_GET(internal_op->paramTypes, i);

				// Copy the integer params from the TA_Param structure to TEEC_Param structure
				if(type == TEEC_VALUE_OUTPUT || type ==  TEEC_VALUE_INOUT) {
					internal_op->params[i].value.a = ta_params[i].value.a;
					internal_op->params[i].value.b = ta_params[i].value.b;
				} else if(type == TEEC_MEMREF_WHOLE || type == TEEC_MEMREF_PARTIAL_OUTPUT ||
							type == TEEC_MEMREF_PARTIAL_INOUT) {
					internal_op->params[i].memref.parent->size = ta_params[i].memref.size;
					internal_op->params[i].memref.size = ta_params[i].memref.size;	
				} else if(type == TEEC_MEMREF_TEMP_OUTPUT || type == TEEC_MEMREF_TEMP_INOUT) {
					internal_op->params[i].tmpref.size = ta_params[i].memref.size;
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
			ret_val = TEE_ERROR_NOT_SUPPORTED;
	}

	return ret_val;
}

void __attribute__ ((interrupt))  exception_handler();

void exception_handler()
{
	uint32_t mtval = 0, mepc = 0, mcause = 0;
	printf("World 2 Exception Handler! \n");

	READ_CSR(mcause, mcause);
	READ_CSR(mtval, mtval);
	READ_CSR(mepc, mepc);

	printf("MCAUSE = %x\n", mcause);
	printf("MTVAL = %x\n", mtval);
	printf("MEPC = %x\n", mepc);


	printf("Leaving World 2 Exception Handler!\n");

	asm volatile ( \
        "addi t0, %0, 4 \n\t" \
        "csrw mepc, t0\n\t" \
        : \
        : "r"(mepc) \
        : "t0" \
    );
}

void __attribute__ ((interrupt))  msi_handler();

void msi_handler()
{

}

void __attribute__ ((interrupt))  systick_handler();

void systick_handler()
{

}

void __attribute__ ((interrupt))  mei_handler();
void mei_handler()
{
	uint32_t interrupt = 0;

	uint32_t mepc = 0;
	printf("World 2 Exception Handler! \n");

	READ_CSR(mepc, mepc);

	READ_PLIC(interrupt);

	if(!interrupt)
		printf("Running on machine mode, reading 0 from plic\n");

	printf("World 2 External Interrupt Handler!\n");

	switch (interrupt)
	{
	case 3:
		uart_recv_handler();
		break;
	
	default:
		break;
	}
	
	COMPLETE_PLIC(3);

	printf("World 2 leaving External Interrupt Handler!\n");
	
	asm volatile ( \
        "addi t0, %0, 4 \n\t" \
        "csrw mepc, t0\n\t" \
        : \
        : "r"(mepc) \
        : "t0" \
    );
}

void uart_recv_handler()
{
	char received[100];
	char* token;
	int index = 0;
	char tokens[3][10];
	char* pEND;
	
	printf("World 2 leaving UART handler!\n");
}
