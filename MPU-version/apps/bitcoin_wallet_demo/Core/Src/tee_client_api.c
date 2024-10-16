/*
 * tee_client_api.c
 *
 *  Author: Emanuele Beozzo
 */


#include "tee_client_api.h"
#include "main.h"

// Notes on PARAMETER PASSING CONVENTION FOR SVC:
// - use registers from r4 to r11 to pass parameters to SVC 
// - save the current value of the registers used in a temporary variable before overwriting them
// - restore the value of the registers after the SVC call
// - use r4 to get the return value of the SVC invocation

// Define the structure of internal operation used to pass the parameters to TA
// and to keep track of the different elements of the client application
// The index can be 0 or 1, and it store all the clients currently opened
// The index 0 is used for the first client, the index 1 is used for the second client (the positions are filled in order)
// NOTE: each TA can have only one client at a time
internal_operation_t *internal_op[NUMBER_OF_TA] = {0};
// Keep track of the used shared memory
static size_t used_shm_size = 0; 

/**
 * @brief Support function to get the internal operation from the id number
 *
 * @param id the id of the internal operation
 *
 * @return the internal operation
*/
internal_operation_t* get_internalOperation(uint32_t id)
{
    // If the id is greater than the number of TA, return NULL as the id is invalid
    if(id > NUMBER_OF_TA) 
        return NULL;

    // If the internal operation is not initialized for a given id, return NULL
    if(!internal_op[id])
        return NULL;

    return internal_op[id];
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
        ERR_MSG("Context is null");
        return TEEC_FAILED;
    }

    // check context id if it's valid or not
    if(ctx->id < 0 || ctx->id > NUMBER_OF_TA)
    {
        // TEE Connection err, can not open session
        ERR_MSG("Invalid context id");
        return TEEC_FAILED;
    }

    return TEEC_SUCCESS;
}


/**
 * @brief Gobal Platform standars function, more information on page 30 of Client API documentation
 *
 * @param name
 * @param ctx TEEC_Context type struct
 *
 * @return if it is success, return TEEC_SUCCESS(0) else TEEC_FAILED(1)
*/
TEEC_Result TEEC_InitializeContext(const char* name,
                                    TEEC_Context* ctx)
{
    int ret_val = TEEC_FAILED;

    // Name is not used in this implementation
    /*if(!name)
    {
        ERR_MSG("Context name is not given");
        return TEE_FAILED;
    } */

    // Initialize the internal operation array with the given context on the first empty slot
    for(int i=0; i<NUMBER_OF_TA; i++)
    {
        // Check if internal_op[i] is not null: in that case the slot is used by another CA and context
        // and it was initialized before
        if(internal_op[i]){
            continue;
        }

        // Allocate memory for new internal_op
        internal_op[i] = (internal_operation_t*)calloc(1, sizeof(internal_operation_t));
        if(!internal_op[i]){ // Memory allocation error
            ERR_MSG("Memory allocation is failed");
            return TEEC_FAILED;
        }

        // The id is equal to either 1 or 2, based on the index of the internal operation
        // The id is used to identify the TA and it is assegned based on the order of the call to this function
        internal_op[i]->id = i + 1; // Id assignment for TA
        ctx->id = i + 1; // Id assignment for context (same as internal_op)
        break;
    }

    // Variable used to temporary store the value of r4 register (used to pass the parameter to the SVC)
    uint32_t temp_val = 0;
    // Get the address of the internal operation containing the context, parameters and info about the client application
    uint32_t *param_addr = (uint32_t*)(internal_op[ctx->id -1]);

    // Store r4 in the temporary variable and pass the address of the internal operation in the r4 register
    __asm__("MOV %0, r4" : "=r" (temp_val) : : "r4");
    __asm__("MOV R4, %[param_addr]\n": : [param_addr] "r" (param_addr): "r4");

    // Call the SVC to pass the context to the TA
    INVOKE_SVC(FUNCTION_INIT_CONTEXT);

    // Get the return value of the SVC call from the r4 register and restore the value of r4
    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));
    __asm__("MOV R4, %[temp_val]\n": : [temp_val] "r" (temp_val): "r4");

    // If the return value is different from TEE_SUCCESS, return TEE_FAILED
    if(ret_val != TEEC_SUCCESS)
        return TEEC_FAILED;

    return TEEC_SUCCESS;
}


/**
 * @brief Function from global platform standards, you can check the documentation on page 31
 *
 * @param ctx TEEC_Context type struct
*/
void TEEC_FinalizeContext(TEEC_Context* ctx)
{
	int param = 1;

    // Check the context if it is valid or not, and return an error message if it is not
    if((!ctx) || (ctx->id < 1)){
        ERR_MSG("context finalize err");
    }else{
        // Create a temporary variable to store the id of the context before freeing the memory
        // The id is used to identify the TA that is being closed
    	param = ctx->id;
        free(internal_op[ctx->id -1]);
        ctx->id = 0;
    }

    // Temprary save the value of r4 register
    uint32_t temp_val_r4 = 0;
   __asm__("MOV %[temp_val_r4], R4\n" : [temp_val_r4] "=r" (temp_val_r4));

    // Pass the parameter to the SVC
   __asm__("MOV R4, %[param]\n": : [param] "r" (param): "r4");

   INVOKE_SVC(FUNCTION_FINALIZE_CONTEXT);

    // Restore the value of r4 register
	__asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
}


/**
 * @brief Function from global platform standards, you can check the documentation on page 37
 *
 * @param ctx TEEC_Context type struct
 * @param session TEEC_Session type struct
 * @param destination UUID parameter
 * @param connectionMethod unused parameter
 * @param connectionData unused parameter
 * @param operation TEEC_Operation type struct, it contains payload of data
 * @param returnOrigin unused parameter
 *
 * @return if it is success, return TEEC_SUCCESS(0) else TEEC_FAILED(1)
*/
TEEC_Result TEEC_OpenSession(TEEC_Context* ctx,
								TEEC_Session* session,
								const TEE_UUID* destination,
								uint32_t connectionMethod, //unused
								const void* connectionData,//unused
								TEEC_Operation* operation,
								uint32_t* returnOrigin /*unused*/)
{
    int ret_val = -1;

    // Check if the context is valid or not
    if(check_context(ctx) != TEEC_SUCCESS)
    {
        goto err;
    }

    // Check if the UUID parameter is null or not
    if(!destination)
    {
        ERR_MSG("uuid is null");
        goto err;
    }

    // Assign ctx params to session ctx parameter
    session->ctx = ctx;

	// Context id parameter used to identify TA and internal operation index 
	// Assign the destination uuid parameter to internal operation uuid parameter
	internal_op[ctx->id - 1]->uuid = destination;

	// Check if the operation parameter is null:
	// if not NULL, copy the params from operation to internal_op
	if(operation) {
		// Assign each operation parameter to internal operation parameters
		for(int i=0; i<4; i++)
		{
			internal_op[ctx->id -1]->params[i] = &(operation->params[i]);
		}
		// Assign the paramtypes parameter to internal operation paramtypes parameter
		internal_op[ctx->id -1]->paramTypes = operation->paramTypes;
	} else {
        // If the operation parameter is NULL, set all the params to NULL and the paramTypes to TEEC_NONE
		for(int i=0; i<4; i++)
		{
			internal_op[ctx->id -1]->params[i] = NULL;
		}
		internal_op[ctx->id -1]->paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE , TEEC_NONE, TEEC_NONE);
	}

    // Session id should be 1 if sessions is successfuly created
    session->id = 1;

    //Get internal_operation parameter address value, then pass it on r4 register
    // according to the SVC calling convention
    uint32_t temp_val = 0;
    uint32_t *param_addr = (uint32_t*)(internal_op[ctx->id -1]);
    __asm__("MOV %0, r4" : "=r" (temp_val) : : "r4");
    __asm__("MOV R4, %[param_addr]\n": : [param_addr] "r" (param_addr): "r4");

    INVOKE_SVC(FUNCTION_OPEN_SESSION);

    // Get the return value of the SVC call from the r4 register and restore the value of r4
    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));
    __asm__("MOV R4, %[temp_val]\n": : [temp_val] "r" (temp_val): "r4");

    if(ret_val != TEEC_SUCCESS)
        return TEEC_FAILED;

    return TEEC_SUCCESS;

    // Error handling
	err:
		return TEEC_FAILED;
}

/**
 * @brief Function from global platform standards, you can check the documentation on page 40
 *
 * @param session TEEC_Session type struct
*/
void TEEC_CloseSession(TEEC_Session* session)
{
	int param = 1; // default TA value

    // Check the session if it is valid or not
    if(!session){
        ERR_MSG("Session close err");
    }else{
        // Create a temporary variable to store the id of the context before resetting it
        // The id is used to identify the TA that is being closed
    	param = session->ctx->id;
        session->id = 0;
    }

    // Temporary save the value of r4 register
    uint32_t temp_val_r4 = 0;
   __asm__("MOV %[temp_val_r4], R4\n" : [temp_val_r4] "=r" (temp_val_r4));

    // Pass the parameter to the SVC
   __asm__("MOV R4, %[param]\n": : [param] "r" (param): "r4");

    INVOKE_SVC(FUNCTION_CLOSE_SESSION);

    // Restore the value of r4 register
    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
}


/**
 * @brief Function from global platform standards, you can check the documentation on page 40
 *
 * @param session TEEC_Session type struct
 * @param command_id indicate whatever command you want to execure from the TA 
 * @param operation TEEC_Operation type struct, it contains payload of data
 * @param returnOrigin unused
 *
 * @return None
*/
TEEC_Result TEEC_InvokeCommand(TEEC_Session* session,
                                    uint32_t command_id,
                                    TEEC_Operation* op,
                                    uint32_t* returnOrigin /*unused*/)
{
    int ret_val = -1;

    // Check if session and session's ctx parameter are null
    if((!session) || (!session->ctx))
    {
        ERR_MSG("Null parameter err (session | context)");
        return TEEC_FAILED;
    }

    // Check session if it is initalized, if id different from 0 that means it is initialized
    if(!session->id)
    {
        ERR_MSG("Invalid session id");
        return TEEC_FAILED;
    }

    // Check if operation parameter is null
    if(!op)
    {
        ERR_MSG("operation parameter is null");
        return TEEC_FAILED;
    }

    // Assign each operation params[index] parameter to internal operation each params[index] parameter
    for(int i=0; i<4; i++)
    {
        internal_op[session->ctx->id -1]->params[i] = &(op->params[i]);
    }
    // Assign the paramtypes parameter to internal operation paramtypes parameter
    internal_op[session->ctx->id -1]->paramTypes = op->paramTypes;

    //Get internal_operation parameter address value, then pass it on r4 register
    // Temporarily store the value of r4 and r5 registers 
    uint32_t temp_val_r4 = 0, temp_val_r5;
    __asm__("MOV %[temp_val_r4], R4\n" : [temp_val_r4] "=r" (temp_val_r4));
    __asm__("MOV %[temp_val_r5], R5\n" : [temp_val_r5] "=r" (temp_val_r5));
    uint32_t *param_addr = internal_op[session->ctx->id -1];
    
    // Pass parameters data structure in r4 register
    __asm__("MOV R4, %[param_addr]\n": : [param_addr] "r" (param_addr): "r4");
    // Pass command_id in r5 register
    __asm__("MOV R5, %[command_id]\n": : [command_id] "r" (command_id): "r5");

    // Call the SVC to pass the context
    INVOKE_SVC(FUNCTION_INVOKE_COMMAND);

    // Get the return value of the SVC call from the r4 register and restore the value of r4 and r5
    __asm__("MOV %0, r4" : "=r" (ret_val) : : "r4");
    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");

    // If the return value is different from TEE_SUCCESS, return TEE_FAILED
    if(ret_val != TEEC_SUCCESS)
        return TEEC_FAILED;

    return TEEC_SUCCESS;
}

/**
* @brief Function from Global Platform Client API used to allocate shared memory: 
* - the memory is allocated using the resources of the client application
* - the memory is also accessible by the TAs and TEE
*
* @param ctx TEEC_Context type struct
* @param shm TEEC_SharedMemory struct to allocate memory for the TA
*
* @return if it is success, return TEEC_SUCCESS(0) else TEEC_FAILED(1)
*/
TEEC_Result TEEC_AllocateSharedMemory(TEEC_Context* ctx,
                                      TEEC_SharedMemory* shm)
{   
    // Check if the shared memory and the context are valid
    if((!shm) || (!ctx)){
        ERR_MSG("Invalid parameter");
        return TEEC_FAILED;
    }

    // Check if the context is valid or not
    if(ctx->id == 0)
    {
        // Invalid context id, contex is not initialized
        ERR_MSG("Invalid context id");
        return TEEC_FAILED;
    }

    // Check if the shared memory size is valid or not (greater than the maximum size of 4KB)
    if(SHARED_MEMORY_MAX_SIZE < (shm->size + used_shm_size)){
        // Size err, not enough memory
        ERR_MSG("Memory limit has been reached");
        return TEEC_FAILED;
    }

    // Allocate required size of memory
    shm->buffer = (uint8_t*)calloc(shm->size + 1, sizeof(uint8_t));
    if(!shm->buffer){
        // Shared memory can not be allocated
        ERR_MSG("Shared memory can not allocate");
        return TEEC_FAILED;
    }

    // Fill the shared memory buffer with zero
    memset(shm->buffer, 0, shm->size);

    // Update the used shared memory size
    used_shm_size += shm->size + 8;

    return TEEC_SUCCESS;
}

/**
* @brief Function from Global Platform Client API used to release previously allocated shared memory
*
* @param shm TEEC_SharedMemory struct to allocate memory for the TA
*
* @return if it is success, return TEEC_SUCCESS(0) else TEEC_FAILED(1)
*/
void TEEC_ReleaseSharedMemory(TEEC_SharedMemory *shm)
{
    // If shared memory payload is not equal null, then free the memory area and update the used shared memory
    if(shm->buffer)
    {
        free(shm->buffer);
        used_shm_size = used_shm_size - (shm->size + 8);
    }

    //If used shared memory size is less than 0 due to before operation, then reset it to 0
    if(used_shm_size < 0)
        used_shm_size = 0;
}