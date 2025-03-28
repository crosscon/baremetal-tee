#ifndef __COMMON__
#define __COMMON__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define __maybe_unused  __attribute__((unused))

#define PRINT 1

// This file contains the definition for all the types and constants used in the Microvisor 
// and the TAs following the global platform standard

/*	----------------------------------Constants and Macro Functions ----------------------------------------	*/

/**
 * Defintion of a custom function that encapsulate the TEE parameter types from the four parameters values into a single one
*/
#define TEE_PARAM_TYPES(t0,t1,t2,t3) \
   ((t0) | ((t1) << 4) | ((t2) << 8) | ((t3) << 12))

/**
 * Defintion of a custom function to get the parameters type from the single TEE parameter value
 */
#define TEE_PARAM_GET_TYPES(paramTypes, index) \
   (((paramTypes) >> ((index) * 4)) & 0xF)

/**
 * Wrapper for the SVC instruction (SVC number is passed as an argument)
 */
#define INVOKE_SVC(svc_num)    __asm volatile ("svc %0" : : "I" (svc_num))


/**
 * Definition of custom printing functions that can be used by the TEE and TAs 
 * The printings uses the UART interface 1 to display the messages
 * printf is redefined using the custom_printf as the default printing function
 * uses internal buffers and data structures that were difficult to control and manage
 * 
 * The different printing functions available are:
 * EMSG("..."): that should be used by TAs to print error messages;
 * IMSG("..."): that should be used by TAs display information to the user;
 * DMSG("..."): that should be used by Tas to print debug messages.
 * 
 * Instead:
 * ERR_MSG("..."): is used by the Microvisor to print error messages.
 */
int custom_printf(const char *format, ...);

#define printf custom_printf

#define ERR_MSG(fmt, ...)\
    do{ printf("ERROR INSIDE TEE: %s:%d:%s(): " #fmt "\r\n", \
         __FILE__, __LINE__, __func__, ##__VA_ARGS__); }while (false);

#define EMSG(fmt, ...)\
    do{ printf("ERROR: %s:%d:%s(): " #fmt "\r\n", \
         __FILE__, __LINE__, __func__, ##__VA_ARGS__); }while (false);

#define IMSG(fmt, ...)\
    do { printf("Info: %s(): " fmt "\r\n", \
        __func__, ##__VA_ARGS__); } while (false);

#define DMSG(fmt, ...)\
    do { printf("Debug: %s:%d:%s(): " fmt "\r\n", \
        __FILE__, __LINE__, __func__, ##__VA_ARGS__); }while (false);


/**
 * Macro that calculates the size of the array of uint32_t values needed 
 * to represent an n-bit integer
 */
#define TEE_BigIntSizeInU32(n) ((((n)+31)/32)+2)

/**
 * Definition of the TEE_PARAMETRS constants
 */
#define TEE_PARAM_TYPE_NONE             0
#define TEE_PARAM_TYPE_VALUE_INPUT      1
#define TEE_PARAM_TYPE_VALUE_OUTPUT     2
#define TEE_PARAM_TYPE_VALUE_INOUT      3
#define TEE_PARAM_TYPE_MEMREF_INPUT     5
#define TEE_PARAM_TYPE_MEMREF_OUTPUT    6
#define TEE_PARAM_TYPE_MEMREF_INOUT     7

/**
 * Definition of the TEE_Result constants
 */
#define TEE_SUCCESS            	    0x0000
#define TEE_FAILED             	    0x0001
#define TEE_ERROR_GENERIC       	0xFFFF0000
#define TEE_ERROR_BAD_PARAMETERS    0xFFFF0006
#define TEE_ERROR_OVERFLOW          0xFFFF300F

/*      
 * Definition of Object Storage Constants 
 */
#define TEE_STORAGE_PRIVATE         0x00000001
#define TEE_STORAGE_PERSO           0x00000002
#define TEE_STORAGE_PROTECTED       0x00000003

/*      
 * Definition of Data Flag Constants
*/
#define TEE_DATA_FLAG_ACCESS_READ           0x00000001
#define TEE_DATA_FLAG_ACCESS_WRITE          0x00000002
#define TEE_DATA_FLAG_ACCESS_WRITE_META     0x00000004 
#define TEE_DATA_FLAG_SHARE_READ            0x00000010 
#define TEE_DATA_FLAG_SHARE_WRITE           0x00000020 

/**
 * Definition of the function codes used to call the TA CLIENT APIs in the SVC handler
 * 
 * SVC number from 0x0000 to 0x0004 are reserved for the TA client APIs
 */
#define FUNCTION_INIT_CONTEXT		0x0000
#define FUNCTION_FINALIZE_CONTEXT	0x0001
#define FUNCTION_OPEN_SESSION		0x0002
#define FUNCTION_CLOSE_SESSION		0x0003
#define FUNCTION_INVOKE_COMMAND 	0x0004

/**
 * Definition of the function codes used to call the TA CORE APIs in the SVC handler
 * 
 * SVC number from 0x0005 to 0x002D are reserved for the TA core APIs
 */
#define FUNCTION_MALLOC				0x0005
#define FUNCTION_FREE				0x0006
#define FUNCTION_MEM_MOVE			0x0007
#define FUNCTION_MEM_FILL            0x0024
#define FUNCTION_ALLOCATE_TRANSIENT_OBJECT 0x0008
#define FUNCTION_POPULATE_TRANSIENT_OBJECT  0x0009
#define FUNCTION_READ_OBJECT_DATA 0x000A
#define FUNCTION_WRITE_OBJECT_DATA 0x000B
#define FUNCTION_CLOSE_OBJECT 0x000C
#define FUNCTION_CREATE_PERSISTENT_OBJECT 0x002B
#define FUNCTION_OPEN_PERSISTENT_OBJECT 0x002C
#define FUNCTION_CLOSE_DELETE_PERSISTENT_OBJECT 0x002D
#define FUNCTION_FREE_TRANSIENT_OBJECT 0x000D
#define FUNCTION_GET_OBJECT_BUFFER_ATTRIBUTE 0x000E
#define FUNCTION_GET_OBJECT_VALUE_ATTRIBUTE 0x000F
#define FUNCTION_INIT_REF_ATTRIBUTE 0x00010 
#define FUNCTION_INIT_VALUE_ATTRIBUTE 0x0011
#define FUNCTION_ALLOCATE_OPERATION 0x0012
#define FUNCTION_FREE_OPERATION 0x0013
#define FUNCTION_SET_OPERATION_KEY 0x0014
#define FUNCTION_SET_OPERATION_KEY2 0x0015
#define FUNCTION_GENERATE_KEY 0x0016
#define FUNCTION_GENERATE_RANDOM 0x0017
#define FUNCTION_DERIVE_KEY 0x0018
#define FUNCTION_CIPHER_INIT 0x0019
#define FUNCTION_CIPHER_UPDATE 0x001A
#define FUNCTION_CIPHER_DO_FINAL 0x001B
#define FUNCTION_MAC_INIT 0x001C
#define FUNCTION_MAC_UPDATE 0x001D
#define FUNCTION_MAC_COMPUTE_FINAL 0x001E
#define FUNCTION_DIGEST_EXTRACT 0x001F
#define FUNCTION_DIGEST_UPDATE 0x0020
#define FUNCTION_DIGEST_DO_FINAL 0x0021
#define FUNCTION_ASYMMETRIC_SIGN_DIGEST 0x0022
#define FUNCTION_ASYMMETRIC_VERIFY_DIGEST 0x0023
#define FUNCTION_BIG_INT_CONVERT_TO_S32 0x0025
#define FUNCTION_BIG_INT_CMP_S32 0x0026
#define FUNCTION_BIG_INT_MOD 0x0027
#define FUNCTION_BIG_INT_DIV 0x0028
#define FUNCTION_BIG_INT_CONVERT_FROM_OCTET_STRING 0x0029
#define FUNCTION_BIG_INT_INIT 0x002A

/**     Memory Management Constant   **/
#define TEE_MALLOC_FILL_ZERO		0x00000000

/**
 * Constants used for the Operation State
 */
#define OPERATION_STATE_ACTIVE      0x0000
#define OPERATION_STATE_INITIAL     0x0001
#define OPERATION_STATE_FAILED      0x0002


/**************** Operation Handle Constant **************/

#define TEE_HANDLE_NULL              0x00000000   // NULL handle

/*************** Attributes Constant  *******************/
#define TEE_ATTR_SECRET_VALUE 0xC0000000

/**************** Objects Constants **************/
// Object types
#define TEE_OBJ_TYPE_PERSISTENT     0x0000
#define TEE_OBJ_TYPE_TRANSIENT      0x0001

// Object permissions
#define TEE_OBJ_JUST_READ           0x0011 // 0b 0001 0001
#define TEE_OBJ_JUST_WRITE          0x0026 // 0b 0010 0110
#define TEE_OBJ_READ_AND_WRITE      0x0037 // 0b 0011 0111


// --------------  TEEC types definition (datastructures mainly used by the client application) --------------

/**
 * Type definition for Shared Memory structure
 */
typedef struct {
    uint8_t*    buffer;
    size_t      size;
    uint32_t    flags;
}TEEC_SharedMemory;

/**
 * Type definition for integer parameters
 */
typedef struct {
	uint32_t a;
	uint32_t b; 
}TEEC_Value;

/**
 * Type definition for Temporary shared memory structure
 */
typedef struct {
	void *buffer; 
	size_t size;
}TEEC_TempMemoryReference; 

/**
 * Type definition for Registered shared memory structure
 */
typedef struct {
	TEEC_SharedMemory *parent;
	size_t size;
	size_t offset;
}TEEC_RegisteredMemoryReference;

/**
 * Type definition for the TEEC_Parameter structure that contains the parameters to be passed to the TA
 * The parameters can be of the following types:
 * - Temporary Memory Reference
 * - Registered Memory Reference
 * - Value (integer, a and b)
 */
typedef struct {
	TEEC_TempMemoryReference tmpref;
	TEEC_RegisteredMemoryReference memref;
	TEEC_Value value;
}TEEC_Parameter;


// ---------------------------------- TEE only type definition ---------------------------------

/**
 * Type definition for TEE_UUID (Universally Unique Resource Identifier) 
 * structure according to the Global Platform standard
 */
typedef struct {
	uint32_t timeLow;
	uint16_t timeMid;
	uint16_t timeHiAndVersion;
	uint8_t clockSeqAndNode[8];
}TEE_UUID;


/**
 * Types definition used by the TEE and TAs
 */
typedef int      TEE_Result;
typedef uint32_t TEE_BigInt;
typedef uint32_t TEE_OperationMode;	
typedef uint32_t TEE_Whence;


/**
 * Internal type definition for parameters, used only by the TEE and TAs
 */
typedef struct {
    struct
    {
        void* buffer; 
        size_t size;
    }memref;

    struct
    {
        uint32_t a;
        uint32_t b;
    }value;

}TEE_Param;

// Type definition for the TEE_ObjectHandle structure
typedef struct __TEE_ObjectHandle *TEE_ObjectHandle;


// Type definition for the information about an Operation
typedef struct {
    uint32_t algorithm;
    uint32_t operationClass;
    uint32_t mode;
    uint32_t digestLength;
    uint32_t maxKeySize;
    uint32_t keySize;
    uint32_t requiredKeyUsage;
    uint32_t handleState;
} TEE_OperationInfo;

// Type definition for the TEE_OperationHandle structure
typedef struct __TEE_OperationHandle *TEE_OperationHandle;

// Type definition for the TEE_Attribute structure for storing the attributes of an object
// As the structure is an union, it can store either a reference or values
typedef struct {
	uint32_t attributeID;
	union {
		struct {
			void *buffer;
			size_t length;
		} ref;
		struct {
			uint32_t a, b;
		} value;
	} content;
} TEE_Attribute;

/*	---------------------------------- Internal type definition ----------------------------------------	*/

/**
 * Internal type definition for storing all the information related to a request to a specific TA
 */
typedef struct
{
    void *params[4]; // Stores the TEEC_Parameter to be passed to the TA
    uint32_t  paramTypes; // Parameter types (single number, to be decoded with TEE_PARAM_TYPE_GET)
    const TEE_UUID  *uuid; // Destination uuid of the TA
    int32_t id; // TA number(TA1 or TA2 - possible values are 1 or 2)
}internal_operation_t;


#endif
