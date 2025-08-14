#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "defines.h"
#include "sifive_plic.h"

#include <tee_client_api.h>
#include "keylogger_ta.h"

#include <trace.h>

void uart_recv_handler();
void init_uart_interrupt(uint32_t);

TEEC_Operation *shared_mem = (TEEC_Operation *) 0x80003000;

int main()
{
	TEEC_Result res;
	TEEC_Context ctx;
	TEEC_Session sess;
	TEEC_UUID uuid = TA_KEYLOGGER_UUID;
	uint32_t err_origin;

	init_uart_interrupt(UART0_BASE);

	memset(shared_mem, 0, sizeof(TEEC_Operation));
	memset(shared_mem->params, 0, sizeof(TEEC_Parameter)*4);

	/* Initialize a context connecting us to the TEE */
	res = TEEC_InitializeContext(NULL, &ctx);
	if (res != TEEC_SUCCESS)
		printf("TEEC_InitializeContext failed with code 0x%x", res);

	/*
	 * Open a session to the "keylogger" TA
	 */
	shared_mem->paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE, TEEC_NONE, TEEC_NONE);
	res = TEEC_OpenSession(&ctx, &sess, &uuid,
			       TEEC_LOGIN_PUBLIC, NULL, NULL, &err_origin);
	if (res != TEEC_SUCCESS)
		printf("TEEC_Opensession failed with code 0x%x origin 0x%x",
			res, err_origin);

	/*
	 * Prepare the argument. Pass a value in the first parameter,
	 * the remaining three parameters are unused.
	 */
	shared_mem->paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);

	/*
	 * TA_KEYLOGGER_CMD_READ_KEY is the actual function in the TA to be
	 * called.
	 */
	res = TEEC_InvokeCommand(&sess, TA_KEYLOGGER_CMD_READ_KEY, shared_mem,
				 &err_origin);
	if (res != TEEC_SUCCESS)
		printf("TEEC_InvokeCommand failed with code 0x%x origin 0x%x",
			res, err_origin);

	/*
	 * We're done with the TA, close the session and
	 * destroy the context.
	 *
	 * The TA will print "Goodbye!" in the log when the
	 * session is closed.
	 */

	TEEC_CloseSession(&sess);

	TEEC_FinalizeContext(&ctx);

	return 0;
}

void init_uart_interrupt(uint32_t uart_base)
{
	asm volatile("li t0, 0x10012000");
	asm volatile("li t1, 0x38");
	asm volatile("add t0, t0, t1");
	/* Enable GPIO */
	asm volatile("li t1, 0x30000");
	asm volatile("sw t1, (t0)");

	asm volatile("li t0, 0x10013000");
	asm volatile("li t1, 8");
	asm volatile("add t0, t0, t1");
	/* Enable TX */
	asm volatile("li t1, 0x01");
	asm volatile("sw t1, (t0)");

	asm volatile("add t0, t0, 4");
	/* Enable RX */
	// asm volatile("li t1, 0x01");
	// asm volatile("sw t1, (t0)");

	asm volatile("add t0, t0, 4");
	// /* Enable RX Int */
	// asm volatile("li t1, 0x2");
	// asm volatile("sw t1, (t0)");

	asm volatile("add t0, t0, 8");
	/* Set Baudrate */
	asm volatile("li t1, 0x233");
	asm volatile("sw t1, (t0)");

}

void __attribute__ ((interrupt))  exception_handler();

void exception_handler()
{
	uint32_t mtval = 0, mepc = 0, mcause = 0;
	printf("World 1 Exception Handler! \n");

	READ_CSR(mcause, mcause);
	READ_CSR(mtval, mtval);
	READ_CSR(mepc, mepc);

	printf("MCAUSE = %x\n", mcause);
	printf("MTVAL = %x\n", mtval);
	printf("MEPC = %x\n", mepc);


	printf("Leaving World 1 Exception Handler!\n");
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
	COMPLETE_PLIC(3);
}

void uart_recv_handler()
{
	char received[100];
	char* token;
	int index = 0;
	char tokens[3][10];
	char* pEND;
	
	printf("World 1 UART handler!\n");

	_read(1, received, 100);
	
	printf("World 1 leaving UART handler!\n");
}
