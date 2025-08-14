/*
 * Copyright (c) 2015-2016, Linaro Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

//#include <errno.h>
//#include <fcntl.h>
//#include <limits.h>
//#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/ioctl.h>
//#include <sys/mman.h>
//#include <sys/stat.h>
//#include <sys/types.h>
//#include <tee_client_api_extensions.h>
#include <tee_client_api.h>
#include "tee.h"
//#include <teec_trace.h>
//#include <unistd.h>

// #include "printf.h"

#ifndef __aligned
#define __aligned(x) __attribute__((__aligned__(x)))
#endif
//#include <linux/tee.h>
//
//#include "teec_benchmark.h"

extern int32_t ioctl(uint32_t cmd, struct tee_ioctl_buf_data *buf_data);

/* How many device sequence numbers will be tried before giving up */
#define TEEC_MAX_DEV_SEQ	1

static TEEC_Result go_to_secure(uint32_t call, uint32_t cmd)
{
    uint32_t ret_val, saved_a6, saved_a7;

    // printf("Going to secure world\n");

	__asm__ (
		"sw a7, %0"    // Store the value of a7 in saved_a7
		:              // No output operands here
		: "m" (saved_a7) // Input operand: the address of saved_a7
		: "a7"         // Clobbered register
	);

	__asm__ (
		"sw a6, %0"    // Store the value of a7 in saved_a7
		:              // No output operands here
		: "m" (saved_a6) // Input operand: the address of saved_a7
		: "a6"         // Clobbered register
	);

    __asm__ (
    	"mv a7, %0"    // Load the immediate value of call into a7
    	:              // Output operands (none here)
    	: "r" (call)   // Input operand: the value of call
    	: "a7"         // Clobbered register
	);

	__asm__ (
    	"mv a6, %0"    // Load the immediate value of call into a7
    	:              // Output operands (none here)
    	: "r" (cmd)   // Input operand: the value of call
    	: "a6"         // Clobbered register
	);

    asm volatile("ecall" ::: "memory");

    __asm__ (
		"sw a6, %0"    // Store the value of a7 in saved_a7
		:              // No output operands here
		: "m" (ret_val) // Input operand: the address of saved_a7
		: "a6"         // Clobbered register
	);

    return ret_val;
}


TEEC_Result TEEC_InitializeContext(const char *name, TEEC_Context *ctx)
{
	static int id = 0;
	int ret_val = TEEC_ERROR_GENERIC;

	if(!ctx){
		return ret_val;
	}

	ctx->fd = id;
	
	go_to_secure(FUNCTION_INIT_CONTEXT, 0); // Force init the world
	return go_to_secure(FUNCTION_INIT_CONTEXT, 0);
}

void TEEC_FinalizeContext(TEEC_Context *ctx)
{
	if (ctx)
	  ctx->fd = -1;

	go_to_secure(FUNCTION_FINALIZE_CONTEXT, 0);
}

/**
 * @brief Supporting function used to chek the contex parameter ( if it null or has invalid id).
 *
 * @param ctx  TEEC_Context type struct
 *
 * @return if it is success return TEEC_SUCCESS, else TEEC_FAILED
*/
static TEEC_Result check_context(TEEC_Context* ctx)
{
    // NULL checking
    if(!ctx)
    {
        EMSG("Context is null");
        return TEEC_ERROR_GENERIC;
    }

    // check context id if it's valid or not
    if(ctx->fd < 0)
    {
        // TEE Connection err, can not open session
        EMSG("Invalid context id");
        return TEEC_ERROR_GENERIC;
    }

    return TEEC_SUCCESS;
}

TEEC_Result TEEC_OpenSession(TEEC_Context *ctx, TEEC_Session *session,
			const TEEC_UUID *destination,
			uint32_t connection_method, const void *connection_data,
			TEEC_Operation *operation, uint32_t *ret_origin)
{
	int ret_val = TEEC_ERROR_GENERIC;

    // Check if the context is valid or not
    if(check_context(ctx) != TEEC_SUCCESS)
    {
        goto err;
    }

    // Check if the UUID parameter is null or not
    if(!destination)
    {
        EMSG("uuid is null");
        goto err;
    }

    // Assign ctx params to session ctx parameter
    session->ctx = ctx;

    // Session id should be 1 if sessions is successfuly created
    session->id = 1;

	return go_to_secure(FUNCTION_OPEN_SESSION, 0);

	err:
		return TEEC_ERROR_GENERIC;
}

void TEEC_CloseSession(TEEC_Session *session)
{
    // Check the session if it is valid or not
    if(!session){
        EMSG("Session close err");
    }

	go_to_secure(FUNCTION_CLOSE_SESSION, 0);
}

TEEC_Result TEEC_InvokeCommand(TEEC_Session *session, uint32_t cmd_id,
			TEEC_Operation *operation, uint32_t *error_origin)
{
	// Check if session and session's ctx parameter are null
    if((!session) || (!session->ctx))
    {
        EMSG("Null parameter err (session | context)");
        return TEEC_ERROR_GENERIC;
    }

    // Check session if it is initalized, if id different from 0 that means it is initialized
    if(!session->id)
    {
        EMSG("Invalid session id");
        return TEEC_ERROR_GENERIC;
    }

    // Check if operation parameter is null
    if(!operation)
    {
        EMSG("operation parameter is null");
        return TEEC_ERROR_BAD_PARAMETERS;
    }

	return go_to_secure(FUNCTION_INVOKE_COMMAND, cmd_id);
}