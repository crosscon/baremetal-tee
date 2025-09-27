#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "tee_core_api.h"

// This file expose the entry points for the TEE Core API: in particular,
// the functions can be called by the Trusted Applications (TAs) as they are 
// placed in the memory area that is accessible without priority, but they are not
// the real implementation of the TEE Core API functions.
// The core API needs to run in the secure world with privileged access, so the
// there should be a mechanism to switch the context and gain privileges
// before calling the real implementation of the core API functions.

// This is done by the SVC Handler: when a TA calls a TEE Core API function, this entry 
// point is called, and transparently, the context is switched to the secure world
// by using the SVC instruction. The SVC Handler is responsible to pass the parameters
// to the real implementation of the TEE Core API functions, call them,
// and manage the return values.

// The real implementation is in the internal_core_api.c file, which is not directly 
// accessible by the TAs and can not execute without priviledges.

// The functions exposed here are the following.

// Notes on PARAMETER PASSING CONVENTION FOR SVC:
// - use registers from r4 to r11 to pass parameters to SVC 
// - save the current value of the registers used in a temporary variable before overwriting them
// - restore the value of the registers after the SVC call
// - use r4 to get the return value of the SVC invocation

// TEE_Malloc: allocate a memory buffer in the TA heap memory area
 void* TEE_Malloc(size_t size, uint32_t hint)
{
	uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    

    void* ret_val = NULL;



    // Save the values of the registers to restore them after the SVC call
    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");

    // Copy the parameters from the C variables to the registers to pass them to the SVC Handler
    __asm__("MOV R4, %[size]\n": : [size] "r" (size): "r4");
    __asm__("MOV R5, %[hint]\n": : [hint] "r" (hint): "r5");

    // Invoke the SVC Handler to call the TEE Core API function with the correct SVC number
    INVOKE_SVC(FUNCTION_MALLOC);
    
    // Copy the return value from the register to the C variable
    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    // Restore the values of the registers before the SVC call
    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    
    return ret_val;
}

// TEE_Free: free a memory buffer allocated in the TA heap memory area
 void TEE_Free(void* buffer)
{
    uint32_t temp_val_r4 = 0;
    
    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");

    // Copy the parameters from the C variables to the registers to pass them to the SVC Handler
    __asm__("MOV R4, %[buffer]\n": : [buffer] "r" (buffer): "r4");

    // Invoke the SVC Handler to call the TEE Core API function with the correct SVC number
    INVOKE_SVC(FUNCTION_FREE);

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
}


// TEE_MemMove: move a memory buffer from a source to a destination
 void TEE_MemMove(void* dest, void* src, size_t size)
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");

    // Copy the parameters from the C variables to the registers to pass them to the SVC Handler
    __asm__("MOV R4, %[dest]\n": : [dest] "r" (dest): "r4");
    __asm__("MOV R5, %[src]\n": : [src] "r" (src): "r5");
    __asm__("MOV R6, %[size]\n": : [size] "r" (size): "r6");

    // Invoke the SVC Handler to call the TEE Core API function with the correct SVC number
    INVOKE_SVC(FUNCTION_MEM_MOVE);

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    
}

// TEE_MemFill: fill a memory buffer with a specific value
 void TEE_MemFill(void* buffer, uint8_t x, size_t size)
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");

    __asm__("MOV R4, %[buffer]\n": : [buffer] "r" (buffer): "r4");
    __asm__("MOV R5, %[x]\n": : [x] "r" (x): "r5");
    __asm__("MOV R6, %[size]\n": : [size] "r" (size): "r6");

    INVOKE_SVC(FUNCTION_MEM_FILL);

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    
}

// TEE_BigIntConvertToS32: convert a big integer to a signed 32-bit integer
 TEE_Result TEE_BigIntConvertToS32(int32_t *dest, TEE_BigInt *src) 
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;

    int ret_val = -1;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");

    __asm__("MOV R4, %[dest]\n": : [dest] "r" (dest): "r4");
    __asm__("MOV R5, %[src]\n": : [src] "r" (src): "r5");

    INVOKE_SVC(FUNCTION_BIG_INT_CONVERT_TO_S32);

    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");

    return ret_val;
}

// TEE_BigIntCmpS32: compare a big integer with a signed 32-bit integer
 int32_t TEE_BigIntCmpS32(TEE_BigInt *op, int32_t shortVal) 
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;

    int ret_val = -1;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");

    __asm__("MOV R4, %[op]\n": : [op] "r" (op): "r4");
    __asm__("MOV R5, %[shortVal]\n": : [shortVal] "r" (shortVal): "r5");

    INVOKE_SVC(FUNCTION_BIG_INT_CMP_S32);

    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");

    return ret_val;
}

// TEE_BigIntMod: calculate the modulo of two big integers
 void TEE_BigIntMod(TEE_BigInt *dest, TEE_BigInt *op, TEE_BigInt *n) 
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");

    __asm__("MOV R4, %[dest]\n": : [dest] "r" (dest): "r4");
    __asm__("MOV R5, %[op]\n": : [op] "r" (op): "r5");
    __asm__("MOV R6, %[n]\n": : [n] "r" (n): "r6");

    INVOKE_SVC(FUNCTION_BIG_INT_MOD);

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
}

// TEE_BigIntDiv: calculate the division of two big integers
 void TEE_BigIntDiv(TEE_BigInt *dest_q, TEE_BigInt *dest_r, TEE_BigInt *op1, TEE_BigInt *op2) 
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");

    __asm__("MOV R4, %[dest_q]\n": : [dest_q] "r" (dest_q): "r4");
    __asm__("MOV R5, %[dest_r]\n": : [dest_r] "r" (dest_r): "r5");
    __asm__("MOV R6, %[op1]\n": : [op1] "r" (op1): "r6");
    __asm__("MOV R7, %[op2]\n": : [op2] "r" (op2): "r7");

    INVOKE_SVC(FUNCTION_BIG_INT_DIV);

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");
}

// TEE_BigIntConvertFromOctetString: convert an octet string to a big integer
 TEE_Result TEE_BigIntConvertFromOctetString(TEE_BigInt *dest, uint8_t *buffer, size_t bufferLen, int32_t sign)
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;
    
    int ret_val = -1;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");

    __asm__("MOV R4, %[dest]\n": : [dest] "r" (dest): "r4");
    __asm__("MOV R5, %[buffer]\n": : [buffer] "r" (buffer): "r5");
    __asm__("MOV R6, %[bufferLen]\n": : [bufferLen] "r" (bufferLen): "r6");
    __asm__("MOV R7, %[sign]\n": : [sign] "r" (sign): "r7");

    INVOKE_SVC(FUNCTION_BIG_INT_CONVERT_FROM_OCTET_STRING);
    
    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");
    
    return ret_val;
}

// TEE_BigIntInit: initialize a big integer
 void TEE_BigIntInit(TEE_BigInt *bigInt, size_t len)
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    
    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");

    __asm__("MOV R4, %[bigInt]\n": : [bigInt] "r" (bigInt): "r4");
    __asm__("MOV R5, %[len]\n": : [len] "r" (len): "r5");

    INVOKE_SVC(FUNCTION_BIG_INT_INIT);

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
}


// TEE_AllocateTransientObject: allocate a transient object
 TEE_Result TEE_AllocateTransientObject(uint32_t objectType,
                                        uint32_t maxObjectSize,
                            /*[out]*/   TEE_ObjectHandle* object)
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    
    int ret_val = -1;


    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");

    __asm__("MOV R4, %[objectType]\n": : [objectType] "r" (objectType): "r4");
    __asm__("MOV R5, %[maxObjectSize]\n": : [maxObjectSize] "r" (maxObjectSize): "r5");
    __asm__("MOV R6, %[object]\n": : [object] "r" (object): "r6");

    INVOKE_SVC(FUNCTION_ALLOCATE_TRANSIENT_OBJECT);
    
    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    
    return ret_val;
}

// TEE_PopulateTransientObject: populate a transient object
  TEE_Result TEE_PopulateTransientObject(TEE_ObjectHandle object,
                        /*unused*/      TEE_Attribute* attrs, 
                        /*unused*/      uint32_t attrCount) 
{   

    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    
    int ret_val = -1;


    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");

    __asm__("MOV R4, %[object]\n": : [object] "r" (object): "r4");
    __asm__("MOV R5, %[attrs]\n": : [attrs] "r" (attrs): "r5");
    __asm__("MOV R6, %[attrCount]\n": : [attrCount] "r" (attrCount): "r6");

    INVOKE_SVC(FUNCTION_POPULATE_TRANSIENT_OBJECT);
    
    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    
    return ret_val;
}

// TEE_InitRefAttribute: initialize a reference attribute
 void TEE_InitRefAttribute(TEE_Attribute* attr, uint32_t attributeID,    
                            void* buffer, size_t length) 
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");

    __asm__("MOV R4, %[attr]\n": : [attr] "r" (attr): "r4");
    __asm__("MOV R5, %[attributeID]\n": : [attributeID] "r" (attributeID): "r5");
    __asm__("MOV R6, %[buffer]\n": : [buffer] "r" (buffer): "r6");
    __asm__("MOV R7, %[length]\n": : [length] "r" (length): "r7");

    INVOKE_SVC(FUNCTION_INIT_REF_ATTRIBUTE);

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");
}

// TEE_InitValueAttribute: initialize a value attribute
 void TEE_InitValueAttribute(TEE_Attribute* attr, uint32_t attributeID,  
                                uint32_t a, uint32_t b) 
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");

    __asm__("MOV R4, %[attr]\n": : [attr] "r" (attr): "r4");
    __asm__("MOV R5, %[attributeID]\n": : [attributeID] "r" (attributeID): "r5");
    __asm__("MOV R6, %[a]\n": : [a] "r" (a): "r6");
    __asm__("MOV R7, %[b]\n": : [b] "r" (b): "r7");

    INVOKE_SVC(FUNCTION_INIT_VALUE_ATTRIBUTE);

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");
}

// TEE_GetObjectBufferAttribute: get a buffer attribute of an object
 TEE_Result TEE_GetObjectBufferAttribute(TEE_ObjectHandle object, uint32_t attributeID,
                        /*[outbuf]*/     void* buffer, size_t* size)
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;
    
    int ret_val = -1;


    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");

    __asm__("MOV R4, %[object]\n": : [object] "r" (object): "r4");
    __asm__("MOV R5, %[attributeID]\n": : [attributeID] "r" (attributeID): "r5");
    __asm__("MOV R6, %[buffer]\n": : [buffer] "r" (buffer): "r6");
    __asm__("MOV R7, %[size]\n": : [size] "r" (size): "r7");

    INVOKE_SVC(FUNCTION_GET_OBJECT_BUFFER_ATTRIBUTE);
    
    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");
    
    return ret_val;
}

// TEE_GetObjectValueAttribute: get a value attribute of an object
 TEE_Result TEE_GetObjectValueAttribute(TEE_ObjectHandle object, uint32_t attributeID,
                        /*[outbuf]*/     uint32_t* a, uint32_t* b)
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;
    
    int ret_val = -1;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");

    __asm__("MOV R4, %[object]\n": : [object] "r" (object): "r4");
    __asm__("MOV R5, %[attributeID]\n": : [attributeID] "r" (attributeID): "r5");
    __asm__("MOV R6, %[a]\n": : [a] "r" (a): "r6");
    __asm__("MOV R7, %[b]\n": : [b] "r" (b): "r7");

    INVOKE_SVC(FUNCTION_GET_OBJECT_VALUE_ATTRIBUTE);
    
    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");
    
    return ret_val;
}

// TEE_FreeTransientObject: free a transient object
 void TEE_FreeTransientObject(TEE_ObjectHandle object)
{
    uint32_t temp_val_r4 = 0;
    
    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");

    __asm__("MOV R4, %[object]\n": : [object] "r" (object): "r4");

    INVOKE_SVC(FUNCTION_FREE_TRANSIENT_OBJECT);

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
}

// TEE_CloseObject: close an object (transient or persistent)
 void TEE_CloseObject(TEE_ObjectHandle object)
{
    uint32_t temp_val_r4 = 0;
    
    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");

    __asm__("MOV R4, %[object]\n": : [object] "r" (object): "r4");

    INVOKE_SVC(FUNCTION_CLOSE_OBJECT);

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
}

// TEE_ReadObjectData: read data from an object
  TEE_Result TEE_ReadObjectData(TEE_ObjectHandle object,
                                                                            /*[out]*/   void* buffer,
                                                                                        size_t size,
                                                                            /*[out]*/   size_t* count)
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;
    
    int ret_val = -1;



    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");

    __asm__("MOV R4, %[object]\n": : [object] "r" (object): "r4");
    __asm__("MOV R5, %[buffer]\n": : [buffer] "r" (buffer): "r5");
    __asm__("MOV R6, %[size]\n": : [size] "r" (size): "r6");
    __asm__("MOV R7, %[count]\n": : [count] "r" (count): "r7");

    INVOKE_SVC(FUNCTION_READ_OBJECT_DATA);
    
    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");
    
    return ret_val;

}

// TEE_WriteObjectData: write data to an object
 TEE_Result TEE_WriteObjectData(TEE_ObjectHandle object,
                                                                            /*[inbuf]*/ void* buffer, 
                                                                                        size_t size)
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    
    int ret_val = -1;



    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");

    __asm__("MOV R4, %[object]\n": : [object] "r" (object): "r4");
    __asm__("MOV R5, %[buffer]\n": : [buffer] "r" (buffer): "r5");
    __asm__("MOV R6, %[size]\n": : [size] "r" (size): "r6");

    INVOKE_SVC(FUNCTION_WRITE_OBJECT_DATA);
    
    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    
    return ret_val;
}

// TEE_CreatePersistentObject: create a persistent object
 TEE_Result TEE_CreatePersistentObject(uint32_t storageID,
                                                            /*[in(newObjectIDLen)]*/  void* objectID,
                                                                                        size_t objectIDLen,
                                                                                        uint32_t flags,
                                                                                        TEE_ObjectHandle attributes,
                                                                            /*[inbuf]*/ void* initialData, 
                                                                                        size_t initialDataLen,
                                                                        /*[outopt]*/ TEE_ObjectHandle* object )
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;
    uint32_t temp_val_r8 = 0;
    uint32_t temp_val_r9 = 0;
    uint32_t temp_val_r10 = 0;
    uint32_t temp_val_r11 = 0;

    int ret_val = -1;

    // NOTE: the storageID is not used in the function, so it can be used to pass the TA number
    // as no other registers are available in the manual frame. It will be overwritten in the core
    storageID = 0;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");
    __asm__("MOV %0, r8" : "=r" (temp_val_r8) : : "r8");
    __asm__("MOV %0, r9" : "=r" (temp_val_r9) : : "r9");
    __asm__("MOV %0, r10" : "=r" (temp_val_r10) : : "r10");
    __asm__("MOV %0, r11" : "=r" (temp_val_r11) : : "r11");

    __asm__("MOV R4, %[storageID]\n": : [storageID] "r" (storageID): "r4");
    __asm__("MOV R5, %[objectID]\n": : [objectID] "r" (objectID): "r5");
    __asm__("MOV R6, %[objectIDLen]\n": : [objectIDLen] "r" (objectIDLen): "r6");
    __asm__("MOV R7, %[flags]\n": : [flags] "r" (flags): "r7");
    __asm__("MOV R8, %[attributes]\n": : [attributes] "r" (attributes): "r8");
    __asm__("MOV R9, %[initialData]\n": : [initialData] "r" (initialData): "r9");
    __asm__("MOV R10, %[initialDataLen]\n": : [initialDataLen] "r" (initialDataLen): "r10");
    __asm__("MOV R11, %[object]\n": : [object] "r" (object): "r11");


    INVOKE_SVC(FUNCTION_CREATE_PERSISTENT_OBJECT);

    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");
    __asm__("MOV R8, %[temp_val_r8]\n": : [temp_val_r8] "r" (temp_val_r8): "r8");
    __asm__("MOV R9, %[temp_val_r9]\n": : [temp_val_r9] "r" (temp_val_r9): "r9");
    __asm__("MOV R10, %[temp_val_r10]\n": : [temp_val_r10] "r" (temp_val_r10): "r10");
    __asm__("MOV R11, %[temp_val_r11]\n": : [temp_val_r11] "r" (temp_val_r11): "r11");

    return ret_val;
}

// TEE_OpenPersistentObject: open a persistent object
 TEE_Result TEE_OpenPersistentObject(uint32_t storageID,
                                                        /*[in(objectIDLength)]*/ void* objectID,
                                                                                    size_t objectIDLen,
                                                                                    uint32_t flags,
                                                                        /*[out]*/ TEE_ObjectHandle* object ) 
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;
    uint32_t temp_val_r8 = 0;

    int ret_val = -1;


    // NOTE: the storageID is not used in the function, so it can be used to pass the TA number
    // as no other registers are available in the manual frame. It will be overwritten in the core
    storageID = 0;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");
    __asm__("MOV %0, r8" : "=r" (temp_val_r8) : : "r8");

    __asm__("MOV R4, %[storageID]\n": : [storageID] "r" (storageID): "r4");
    __asm__("MOV R5, %[objectID]\n": : [objectID] "r" (objectID): "r5");
    __asm__("MOV R6, %[objectIDLen]\n": : [objectIDLen] "r" (objectIDLen): "r6");
    __asm__("MOV R7, %[flags]\n": : [flags] "r" (flags): "r7");
    __asm__("MOV R8, %[object]\n": : [object] "r" (object): "r8");


    INVOKE_SVC(FUNCTION_OPEN_PERSISTENT_OBJECT);

    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");
    __asm__("MOV R8, %[temp_val_r8]\n": : [temp_val_r8] "r" (temp_val_r8): "r8");

    return ret_val;
}

// TEE_CloseAndDeletePersistentObject: close and delete a persistent object
 TEE_Result TEE_CloseAndDeletePersistentObject1(TEE_ObjectHandle object)
{
    uint32_t temp_val_r4 = 0;

    int ret_val = -1;



    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");

    __asm__("MOV R4, %[object]\n": : [object] "r" (object): "r4");


    INVOKE_SVC(FUNCTION_CLOSE_DELETE_PERSISTENT_OBJECT);

    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");

    return ret_val;
}

// TEE_AllocateOperation: allocate an operation
 TEE_Result TEE_AllocateOperation(TEE_OperationHandle* operation,           
                                                                                uint32_t algorithm,
                                                                                uint32_t mode, 
                                                                                uint32_t maxKeySize) 
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;
    
    int ret_val = -1;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");

    __asm__("MOV R4, %[operation]\n": : [operation] "r" (operation): "r4");
    __asm__("MOV R5, %[algorithm]\n": : [algorithm] "r" (algorithm): "r5");
    __asm__("MOV R6, %[mode]\n": : [mode] "r" (mode): "r6");
    __asm__("MOV R7, %[maxKeySize]\n": : [maxKeySize] "r" (maxKeySize): "r7");

    INVOKE_SVC(FUNCTION_ALLOCATE_OPERATION);
    
    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");
    
    return ret_val;
}

// TEE_FreeOperation: free an operation
 void TEE_FreeOperation(TEE_OperationHandle operation)                         
{
    uint32_t temp_val_r4 = 0;
    
    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");

    __asm__("MOV R4, %[operation]\n": : [operation] "r" (operation): "r4");

    INVOKE_SVC(FUNCTION_FREE_OPERATION);

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
}


// TEE_SetOperationKey: set the key of an operation
 TEE_Result TEE_SetOperationKey(TEE_OperationHandle operation,              
                                                                            TEE_ObjectHandle key)
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    
    int ret_val = -1;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");

    __asm__("MOV R4, %[operation]\n": : [operation] "r" (operation): "r4");
    __asm__("MOV R5, %[key]\n": : [key] "r" (key): "r5");

    INVOKE_SVC(FUNCTION_SET_OPERATION_KEY);
    
    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    
    return ret_val;
}

// TEE_GenerateKey: generate a key
 TEE_Result TEE_GenerateKey(TEE_ObjectHandle object,                     
                                                                        uint32_t keySize,
                                                                        TEE_Attribute* params,
                                                                        uint32_t paramCount)
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;
    
    int ret_val = -1;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");

    __asm__("MOV R4, %[object]\n": : [object] "r" (object): "r4");
    __asm__("MOV R5, %[keySize]\n": : [keySize] "r" (keySize): "r5");
    __asm__("MOV R6, %[params]\n": : [params] "r" (params): "r6");
    __asm__("MOV R7, %[paramCount]\n": : [paramCount] "r" (paramCount): "r7");

    INVOKE_SVC(FUNCTION_GENERATE_KEY);
    
    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");

    return ret_val;
}

// TEE_GenerateRandom: generate random data
 void TEE_GenerateRandom(void* randomBuffer, size_t randomBufferLen)
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    
    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");

    __asm__("MOV R4, %[randomBuffer]\n": : [randomBuffer] "r" (randomBuffer): "r4");
    __asm__("MOV R5, %[randomBufferLen]\n": : [randomBufferLen] "r" (randomBufferLen): "r5");

    INVOKE_SVC(FUNCTION_GENERATE_RANDOM);

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
}

// TEE_DeriveKey: derive a key (NOTE: the function is not implemented in the microvisor)
 void TEE_DeriveKey(TEE_OperationHandle operation, TEE_Attribute* params, uint32_t paramCount, TEE_ObjectHandle derivedKey)
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;
    
    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");

    __asm__("MOV R4, %[operation]\n": : [operation] "r" (operation): "r4");
    __asm__("MOV R5, %[params]\n": : [params] "r" (params): "r5");
    __asm__("MOV R6, %[paramCount]\n": : [paramCount] "r" (paramCount): "r6");
    __asm__("MOV R7, %[derivedKey]\n": : [derivedKey] "r" (derivedKey): "r7");

    INVOKE_SVC(FUNCTION_DERIVE_KEY);

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");
}

// TEE_CipherInit: initialize a cipher operation
 void TEE_CipherInit(TEE_OperationHandle operation,
                                                                    void* IV, 
                                                                    size_t IVLen)
{   
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");

    __asm__("MOV R4, %[operation]\n": : [operation] "r" (operation): "r4");
    __asm__("MOV R5, %[IV]\n": : [IV] "r" (IV): "r5");
    __asm__("MOV R6, %[IVLen]\n": : [IVLen] "r" (IVLen): "r6");

    INVOKE_SVC(FUNCTION_CIPHER_INIT);

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
}

// TEE_CipherUpdate: update a cipher operation
 TEE_Result TEE_CipherUpdate(TEE_OperationHandle operation,
                                                                    void* srcData, 
                                                                    size_t srcLen,
                                                                    void* destData,
                                                                    size_t* destLen)
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;
    uint32_t temp_val_r8 = 0;

    int ret_val = -1;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");
    __asm__("MOV %0, r8" : "=r" (temp_val_r8) : : "r8");

    __asm__("MOV R4, %[operation]\n": : [operation] "r" (operation): "r4");
    __asm__("MOV R5, %[srcData]\n": : [srcData] "r" (srcData): "r5");
    __asm__("MOV R6, %[srcLen]\n": : [srcLen] "r" (srcLen): "r6");
    __asm__("MOV R7, %[destData]\n": : [destData] "r" (destData): "r7");
    __asm__("MOV R8, %[destLen]\n": : [destLen] "r" (destLen): "r8");

    INVOKE_SVC(FUNCTION_CIPHER_UPDATE);

    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");
    __asm__("MOV R8, %[temp_val_r8]\n": : [temp_val_r8] "r" (temp_val_r8): "r8");

    return ret_val;
}

// TEE_CipherDoFinal: finalize a cipher operation
 TEE_Result TEE_CipherDoFinal(TEE_OperationHandle operation,
                                                                    void* srcData, 
                                                                    size_t srcLen,
                                                                    void* destData,
                                                                    size_t* destLen)
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;
    uint32_t temp_val_r8 = 0;

    int ret_val = -1;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");
    __asm__("MOV %0, r8" : "=r" (temp_val_r8) : : "r8");

    __asm__("MOV R4, %[operation]\n": : [operation] "r" (operation): "r4");
    __asm__("MOV R5, %[srcData]\n": : [srcData] "r" (srcData): "r5");
    __asm__("MOV R6, %[srcLen]\n": : [srcLen] "r" (srcLen): "r6");
    __asm__("MOV R7, %[destData]\n": : [destData] "r" (destData): "r7");
    __asm__("MOV R8, %[destLen]\n": : [destLen] "r" (destLen): "r8");

    INVOKE_SVC(FUNCTION_CIPHER_DO_FINAL);

    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");
    __asm__("MOV R8, %[temp_val_r8]\n": : [temp_val_r8] "r" (temp_val_r8): "r8");

    return ret_val;
}

// TEE_MACInit: initialize a MAC operation
 void TEE_MACInit(TEE_OperationHandle operation,                             
                  void* IV, size_t IVLen) 
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");

    __asm__("MOV R4, %[operation]\n": : [operation] "r" (operation): "r4");
    __asm__("MOV R5, %[IV]\n": : [IV] "r" (IV): "r5");
    __asm__("MOV R6, %[IVLen]\n": : [IVLen] "r" (IVLen): "r6");

    INVOKE_SVC(FUNCTION_MAC_INIT);

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
}

// TEE_MACUpdate: update a MAC operation
 void TEE_MACUpdate(TEE_OperationHandle operation,
        /*[inbuf]*/ void* chunk, size_t chunkSize) 
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    
    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");

    __asm__("MOV R4, %[operation]\n": : [operation] "r" (operation): "r4");
    __asm__("MOV R5, %[chunk]\n": : [chunk] "r" (chunk): "r5");
    __asm__("MOV R6, %[chunkSize]\n": : [chunkSize] "r" (chunkSize): "r6");

    INVOKE_SVC(FUNCTION_MAC_UPDATE);

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
}                      

// TEE_MACComputeFinal: finalize a MAC operation
 TEE_Result TEE_MACComputeFinal(TEE_OperationHandle operation,
             /*[inbuf]*/        void* message, size_t messageLen,
             /*[outbuf]*/       void* mac, size_t *macLen) 
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;
    uint32_t temp_val_r8 = 0;

    int ret_val = -1;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");
    __asm__("MOV %0, r8" : "=r" (temp_val_r8) : : "r8");

    __asm__("MOV R4, %[operation]\n": : [operation] "r" (operation): "r4");
    __asm__("MOV R5, %[message]\n": : [message] "r" (message): "r5");
    __asm__("MOV R6, %[messageLen]\n": : [messageLen] "r" (messageLen): "r6");
    __asm__("MOV R7, %[mac]\n": : [mac] "r" (mac): "r7");
    __asm__("MOV R8, %[macLen]\n": : [macLen] "r" (macLen): "r8");

    INVOKE_SVC(FUNCTION_MAC_COMPUTE_FINAL);

    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");
    __asm__("MOV R8, %[temp_val_r8]\n": : [temp_val_r8] "r" (temp_val_r8): "r8");

    return ret_val;
}

// TEE_AsymmetricEncrypt: asymmetric sign a digest of a message
 TEE_Result TEE_AsymmetricSignDigest(TEE_OperationHandle operation,
                    /*[in]*/         TEE_Attribute* params, uint32_t paramCount,
                    /*[inbuf]*/      void* digest, size_t digestLen,
                    /*[outbuf]*/     void* signature, size_t *signatureLen) 
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;
    uint32_t temp_val_r8 = 0;
    uint32_t temp_val_r9 = 0;
    uint32_t temp_val_r10 = 0;

    int ret_val = -1;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");
    __asm__("MOV %0, r8" : "=r" (temp_val_r8) : : "r8");
    __asm__("MOV %0, r9" : "=r" (temp_val_r9) : : "r9");
    __asm__("MOV %0, r10" : "=r" (temp_val_r10) : : "r10");

    __asm__("MOV R4, %[operation]\n": : [operation] "r" (operation): "r4");
    __asm__("MOV R5, %[params]\n": : [params] "r" (params): "r5");
    __asm__("MOV R6, %[paramCount]\n": : [paramCount] "r" (paramCount): "r6");
    __asm__("MOV R7, %[digest]\n": : [digest] "r" (digest): "r7");
    __asm__("MOV R8, %[digestLen]\n": : [digestLen] "r" (digestLen): "r8");
    __asm__("MOV R9, %[signature]\n": : [signature] "r" (signature): "r9");
    __asm__("MOV R10, %[signatureLen]\n": : [signatureLen] "r" (signatureLen): "r10");

    INVOKE_SVC(FUNCTION_ASYMMETRIC_SIGN_DIGEST);

    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");
    __asm__("MOV R8, %[temp_val_r8]\n": : [temp_val_r8] "r" (temp_val_r8): "r8");
    __asm__("MOV R9, %[temp_val_r9]\n": : [temp_val_r9] "r" (temp_val_r9): "r9");
    __asm__("MOV R10, %[temp_val_r10]\n": : [temp_val_r10] "r" (temp_val_r10): "r10");

    return ret_val;
}

// TEE_AsymmetricDecrypt: asymmetric verify a digest of a message
 TEE_Result TEE_AsymmetricVerifyDigest(TEE_OperationHandle operation,
                        /*[in]*/       TEE_Attribute* params, uint32_t paramCount,
                        /*[inbuf]*/    void* digest, size_t digestLen,
                        /*[inbuf]*/    void* signature, size_t signatureLen) 
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;
    uint32_t temp_val_r8 = 0;
    uint32_t temp_val_r9 = 0;
    uint32_t temp_val_r10 = 0;

    int ret_val = -1;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");
    __asm__("MOV %0, r8" : "=r" (temp_val_r8) : : "r8");
    __asm__("MOV %0, r9" : "=r" (temp_val_r9) : : "r9");
    __asm__("MOV %0, r10" : "=r" (temp_val_r10) : : "r10");

    __asm__("MOV R4, %[operation]\n": : [operation] "r" (operation): "r4");
    __asm__("MOV R5, %[params]\n": : [params] "r" (params): "r5");
    __asm__("MOV R6, %[paramCount]\n": : [paramCount] "r" (paramCount): "r6");
    __asm__("MOV R7, %[digest]\n": : [digest] "r" (digest): "r7");
    __asm__("MOV R8, %[digestLen]\n": : [digestLen] "r" (digestLen): "r8");
    __asm__("MOV R9, %[signature]\n": : [signature] "r" (signature): "r9");
    __asm__("MOV R10, %[signatureLen]\n": : [signatureLen] "r" (signatureLen): "r10");

    INVOKE_SVC(FUNCTION_ASYMMETRIC_VERIFY_DIGEST);

    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");
    __asm__("MOV R8, %[temp_val_r8]\n": : [temp_val_r8] "r" (temp_val_r8): "r8");
    __asm__("MOV R9, %[temp_val_r9]\n": : [temp_val_r9] "r" (temp_val_r9): "r9");
    __asm__("MOV R10, %[temp_val_r10]\n": : [temp_val_r10] "r" (temp_val_r10): "r10");

    return ret_val;
}

// TEE_DigestUpdate: update a digest operation
 void TEE_DigestUpdate(TEE_OperationHandle operation,
                                                    /*inbuf]*/     void* chunk, size_t chunkSize)
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    
    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");

    __asm__("MOV R4, %[operation]\n": : [operation] "r" (operation): "r4");
    __asm__("MOV R5, %[chunk]\n": : [chunk] "r" (chunk): "r5");
    __asm__("MOV R6, %[chunkSize]\n": : [chunkSize] "r" (chunkSize): "r6");

    INVOKE_SVC(FUNCTION_DIGEST_UPDATE);

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
}

// TEE_DigestDoFinal: finalize a digest operation
 TEE_Result TEE_DigestDoFinal(TEE_OperationHandle operation,
                                                            /*[inbuf]*/      void* chunk, size_t chunkLen,
                                                            /*[outbuf]*/     void* hash, size_t *hashLen) 
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;
    uint32_t temp_val_r7 = 0;
    uint32_t temp_val_r8 = 0;

    int ret_val = -1;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");
    __asm__("MOV %0, r7" : "=r" (temp_val_r7) : : "r7");
    __asm__("MOV %0, r8" : "=r" (temp_val_r8) : : "r8");

    __asm__("MOV R4, %[operation]\n": : [operation] "r" (operation): "r4");
    __asm__("MOV R5, %[chunk]\n": : [chunk] "r" (chunk): "r5");
    __asm__("MOV R6, %[chunkLen]\n": : [chunkLen] "r" (chunkLen): "r6");
    __asm__("MOV R7, %[hash]\n": : [hash] "r" (hash): "r7");
    __asm__("MOV R8, %[hashLen]\n": : [hashLen] "r" (hashLen): "r8");

    INVOKE_SVC(FUNCTION_DIGEST_DO_FINAL);

    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");
    __asm__("MOV R7, %[temp_val_r7]\n": : [temp_val_r7] "r" (temp_val_r7): "r7");
    __asm__("MOV R8, %[temp_val_r8]\n": : [temp_val_r8] "r" (temp_val_r8): "r8");

    return ret_val;

}

// TEE_DigestExtract: extract the digest from a digest operation
 TEE_Result TEE_DigestExtract(TEE_OperationHandle operation,
                                                         /*[outbuf]*/       void* hash, size_t *hashLen) 
{
    uint32_t temp_val_r4 = 0;
    uint32_t temp_val_r5 = 0;
    uint32_t temp_val_r6 = 0;

    int ret_val = -1;

    __asm__("MOV %0, r4" : "=r" (temp_val_r4) : : "r4");
    __asm__("MOV %0, r5" : "=r" (temp_val_r5) : : "r5");
    __asm__("MOV %0, r6" : "=r" (temp_val_r6) : : "r6");

    __asm__("MOV R4, %[operation]\n": : [operation] "r" (operation): "r4");
    __asm__("MOV R5, %[hash]\n": : [hash] "r" (hash): "r5");
    __asm__("MOV R6, %[hashLen]\n": : [hashLen] "r" (hashLen): "r6");

    INVOKE_SVC(FUNCTION_DIGEST_EXTRACT);

    __asm__("MOV %[ret_val], R4\n" : [ret_val] "=r" (ret_val));

    __asm__("MOV R4, %[temp_val_r4]\n": : [temp_val_r4] "r" (temp_val_r4): "r4");
    __asm__("MOV R5, %[temp_val_r5]\n": : [temp_val_r5] "r" (temp_val_r5): "r5");
    __asm__("MOV R6, %[temp_val_r6]\n": : [temp_val_r6] "r" (temp_val_r6): "r6");

    return ret_val;
}   








