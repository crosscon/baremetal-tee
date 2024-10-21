/*
 * tee_client_api.h
 *
 * Author: Emanuele Beozzo
 */

#ifndef INC_TEE_CLIENT_API_H_
#define INC_TEE_CLIENT_API_H_

#include "tee_common.h"

/**
 * Standard function that each client application must call in order to communicate with the Trusted Applications
 * This file should be included in each client application developed that wants to run on top of BaremetalTEE and
 * use the services provided by the Trusted Applications.
 * 
 * Functions and flow:
 * 1. TEEC_InitializeContext: Initialize the context for the client application
 * 2. TEEC_OpenSession: Open a session with the Trusted Application
 * 3a. TEEC_InvokeCommand: Invoke a command for the TA on the session
 * 3b. TEEC_AllocateSharedMemory: Allocate a shared memory for data passing between CA and the TAs
 * 3c. TEEC_ReleaseSharedMemory: Release the shared memory previously allocated
 * 4. TEEC_CloseSession: Close the session with the TA
 * 5. TEEC_FinalizeContext: Finalize the context for the client application
 * 
 * The steps 3a, 3b and 3c can be repeated multiple based on the client application needs
 * 
 * The functions are implemented in the tee_client_api.c file and uses the SVC mechanism 
 * to communicate with the TEE and switch the context
 * 
 * More information about the TEE Client API can be found in the GlobalPlatform TEE Client API Specification
 */

TEEC_Result TEEC_InitializeContext(const char* name,
                                    TEEC_Context* ctx);

void TEEC_FinalizeContext(TEEC_Context* ctx);

TEEC_Result TEEC_OpenSession(TEEC_Context* ctx,
                                TEEC_Session* session,
                                const TEE_UUID* destination,
                                uint32_t connectionMethod,
                                const void* connectionData,
                                TEEC_Operation* operation,
                                uint32_t* returnOrigin);

void TEEC_CloseSession(TEEC_Session* session);

TEEC_Result TEEC_InvokeCommand(TEEC_Session* session,
                                    uint32_t commandID,
                                    TEEC_Operation* operation,
                                    uint32_t* returnOrigin);


TEEC_Result TEEC_AllocateSharedMemory(TEEC_Context* context,
                                        TEEC_SharedMemory* sharedMem) ;


void TEEC_ReleaseSharedMemory(TEEC_SharedMemory *shm);


#endif /* INC_TEE_CLIENT_API_H_ */