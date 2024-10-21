/*
 * tee_common.h
 *
 * Author: Emanuele Beozzo 
 * 
 * This file contains the common definitions and structures used by the Client Applications
 * to communicate with the Trusted Applications and the TEE
 */

#ifndef INC_TEE_COMMON_H_
#define INC_TEE_COMMON_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/***************** CONSTANTS AND MACROS ****************/

// Constants for the different types of parameters that the client application can pass to the TA
#define TEEC_NONE                   0x00000000
#define TEEC_VALUE_INPUT            0x00000001
#define TEEC_VALUE_OUTPUT           0x00000002
#define TEEC_VALUE_INOUT            0x00000003
#define TEEC_MEMREF_TEMP_INPUT      0x00000005
#define TEEC_MEMREF_TEMP_OUTPUT     0x00000006

// Constant used to indicate the login method for the TA
#define TEEC_LOGIN_PUBLIC			0x00000000

// Define the maximum size of the shared memory that can be allocated by the client application
#define SHARED_MEMORY_MAX_SIZE	1024*4 //Max 4KB shared memory  

// Define a function to serialize the parameters type in a single value 
#define TEEC_PARAM_TYPES(t0,t1,t2,t3) \
   ((t0) | ((t1) << 4) | ((t2) << 8) | ((t3) << 12))

// Define a custom function to print the error messages
#define ERR_MSG(fmt, ...)\
        do{ printf("\033[0;31m" "ERROR: %s:%d:%s(): " #fmt "\r\n", \
            __FILE__, __LINE__, __func__, ##__VA_ARGS__); }while (false);

// Define a wrapper for the SVC instruction, able to invoke the SVC with the given number
#define INVOKE_SVC(svc_num)    __asm volatile ("svc %0" : : "I" (svc_num))

// Define the SVC numbers for the different Client API functions that can be invoked
#define FUNCTION_INIT_CONTEXT		0x0000
#define FUNCTION_FINALIZE_CONTEXT	0x0001
#define FUNCTION_OPEN_SESSION		0x0002
#define FUNCTION_CLOSE_SESSION		0x0003
#define FUNCTION_INVOKE_COMMAND 	0x0004

// Define the return values for the Client API functions
#define TEEC_SUCCESS            	0x0000
#define TEEC_FAILED             	0x0001

// Constants for the Trusted Applications
#define NUMBER_OF_TA                0x0002 // Maximum number of Trusted Applications
#define TRUSTED_APP_1               0x0001
#define TRUSTED_APP_2         	    0x0002


/***************** TYPES AND DATA STRUCTURES ****************/

// Define a structure to store the UUID of the Trusted Applications
typedef struct {
	uint32_t timeLow;
	uint16_t timeMid;
	uint16_t timeHiAndVersion;
	uint8_t clockSeqAndNode[8];
}TEE_UUID;

typedef TEE_UUID TEEC_UUID;

// Define a structure to store the internal operation used to share data and params between the client application and the TA
typedef struct
{
    void *params[4]; 		// TEEC_Parameter
    uint32_t  paramTypes;   // Parameter types
    const TEE_UUID  *uuid;  // Destination uuid
    int32_t  id;            // Id to indicate the TA number (1 for TA1 or 2 for TA2)
}internal_operation_t;

// Define the result type for the Client API functions
typedef int TEEC_Result;

// Define the shared memory structure used to pass references between the client application and the TA
// The shared memory contains a buffer, the size of the buffer and some flags
typedef struct{
    uint8_t*    buffer;
    size_t      size;
    uint32_t    flags;
}TEEC_SharedMemory;

// Define the memory reference structures used to pass data between the client application and the TA
typedef struct {
	void *buffer;
	size_t size;
}TEEC_TempMemoryReference;

typedef struct
{
	TEEC_SharedMemory *parent;
	size_t size;
	size_t offset;
}TEEC_RegisteredMemoryReference;


// Define the value structure used to pass integer data between the client application and the TA 
// It contains two inteparameters (a and b)
typedef struct {
	uint32_t a; /*!< Parameter meaning is defined by the protocol between TA and Client */
	uint32_t b; /*!< Parameter meaning is defined by the protocol between TA and Client */
}TEEC_Value;

// Define the parameter structure used to pass data between the client application and the TA
// The parameter can be a value, a temporary memory reference or a registered memory reference
typedef struct
{
	TEEC_TempMemoryReference tmpref;
	TEEC_RegisteredMemoryReference memref;
	TEEC_Value value;
}TEEC_Parameter;

// Define the context structure used to store the context of the client application
typedef struct
{
    /* Implementation defined */
    uint32_t id; 	// point to TA
	TEE_UUID *uuid;
}TEEC_Context;

// Define the session structure used to store the session of the client application
typedef struct {
	/* Implementation defined */
	TEEC_Context *ctx;
	uint32_t id;
}TEEC_Session;

// Define the operation structure used to store the operation of the client application
typedef struct {
	uint32_t started; // unused, for the cancellation op
	uint32_t paramTypes;
	TEEC_Parameter params[4];
    //<Implementation-Defined Type> imp; // Not used
}TEEC_Operation;


#endif /* INC_TEE_COMMON_H_ */