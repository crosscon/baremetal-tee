#ifndef __INTERNAL_CORE_API_H__
#define __INTERNAL_CORE_API_H__

#include "tee_core_api.h"

// Function called during the boot process to ensure the pointers
// for the heap memory of each TA are initialized to NULL
void heap_erase();

/*
* All the following functions are the actual implementation of the TEE Core API functions
* They are called by the TA functions using these steps:
* - call the entry point defined in the tee_core_api files (accessible by the TA)
* - copy the parameters into the CPU registers (from r4 to r11)
* - invoke the SVC instruction to switch to the secure world (with a particular SVC number)
* - based on the SVC number, the secure world will call the corresponding internal function that map the TEE Core API
* 
* The return value of the internal functions is stored in the r0 register and is returned to the TA
*
* The internal functions are defined in this file and are called by the secure world
*/


/**
 * Memory Management functions
 * 
 * The following functions are used to allocate, free, move, and fill 
 * a heap memory area defined for each TA. 
 * The heap memory is allocated as static array and is managed with a list of Blocks, 
 * where each block contains information about the size and a pointer to the next block
 * 
 * Each TA has a dedicated heap memory area of 10 KB, allocated as uint32_t array
 * 
 * Malloc: allocate a memory area of a given size
 * Free: free a memory area (clear the memory from the list of Blocks)
 * MemMove: move a memory area to another location
 * MemFill: fill a memory area with a given value
 */

void* internal_TEE_Malloc(int ta_num, size_t size, uint32_t hint);

void internal_TEE_Free(int ta_num, void* buffer);

void internal_TEE_MemMove(int ta_num, void* dest, void* src, size_t size);

void internal_TEE_MemFill(int ta_num, void* buffer, uint8_t x, size_t size);


/**
 * BigInt Functions
 * 
 * The following functions are used to perform operations on BigInt numbers
 * BigInt numbers are used to represent large numbers that cannot be stored in a standard data type
 * BigInt numbers are needed for cryptographic operations
 * 
 * ConvertToS32: convert a BigInt number to a signed 32-bit integer
 * CmpS32: compare a BigInt number with a signed 32-bit integer
 * Mod: compute the modulo of two BigInt numbers
 * Div: compute the division of two BigInt numbers
 * ConvertFromOctetString: convert an octet string to a BigInt number
 */

TEE_Result internal_TEE_BigIntConvertToS32(int32_t *dest, TEE_BigInt *src);

int32_t internal_TEE_BigIntCmpS32(TEE_BigInt *op, int32_t shortVal);

void internal_TEE_BigIntMod(TEE_BigInt *dest, TEE_BigInt *op, TEE_BigInt *n);

void internal_TEE_BigIntDiv(TEE_BigInt *dest_q, TEE_BigInt *dest_r, TEE_BigInt *op1, TEE_BigInt *op2);

TEE_Result internal_TEE_BigIntConvertFromOctetString(TEE_BigInt *dest, uint8_t *buffer, size_t bufferLen, int32_t sign);

void internal_TEE_BigIntInit(TEE_BigInt *bigInt, size_t len);


/*
* Object Management functions
* 
* The following functions are used to manage two types of objects: transient and persistent
* Transient objects are stored in the stack and heap memory of the TA
* Persistent objects are stored in the secure storage memory of the TA
*
* AllocateTransientObject: allocate a transient object in the memory (attributes and buffer)
* PopulateTransientObject: populate the attributes of a transient object 
* InitRefAttribute: initialize a reference attribute
* InitValueAttribute: initialize a value attribute
* GetObjectBufferAttribute: get the buffer of an object attribute
* GetObjectValueAttribute: get the value of an object attribute
* FreeTransientObject: free a transient object
* CloseObject: close an object
*
* CreatePersistentObject: create a persistent object
* ReadObjectData: read the data of a persistent object
* WriteObjectData: write the data of a persistent object
* OpenPersistentObject: open a persistent object
* CloseAndDeletePersistentObject1: close and delete a persistent object
*
* More information about the functions can be found in the TEE Core API documentation
*/

TEE_Result internal_TEE_AllocateTransientObject(uint32_t objectType,
                                        uint32_t maxObjectSize,
                            /*[out]*/   TEE_ObjectHandle* object);

TEE_Result internal_TEE_PopulateTransientObject(TEE_ObjectHandle object,
                        /*unused*/      TEE_Attribute* attrs, 
                        /*unused*/      uint32_t attrCount);

void internal_TEE_InitRefAttribute(TEE_Attribute* attr, uint32_t attributeID, 
                            void* buffer, size_t length);


void internal_TEE_InitValueAttribute(TEE_Attribute* attr, uint32_t attributeID,
                                uint32_t a, uint32_t b);

TEE_Result internal_TEE_GetObjectBufferAttribute(TEE_ObjectHandle object, uint32_t attributeID,
                        /*[outbuf]*/     void* buffer, size_t* size);

TEE_Result internal_TEE_GetObjectValueAttribute(TEE_ObjectHandle object, uint32_t attributeID,
                                                uint32_t* a, uint32_t* b);

void internal_TEE_FreeTransientObject(TEE_ObjectHandle object);

void internal_TEE_CloseObject(TEE_ObjectHandle object);

TEE_Result internal_TEE_ReadObjectData(TEE_ObjectHandle object,
                                        void* buffer,
                                        size_t size,
                                        size_t* count,
                                        uint32_t ta_num); 

TEE_Result internal_TEE_WriteObjectData(TEE_ObjectHandle object,
                                        void* buffer, 
                                        size_t size,
                                        uint32_t ta_num);

TEE_Result internal_TEE_CreatePersistentObject(uint32_t storageID,
              /*[in(newObjectIDLen)]*/  void* objectID,
                                        size_t objectIDLen,
                                        uint32_t flags,
                                        TEE_ObjectHandle attributes,
                            /*[inbuf]*/ void* initialData, 
                                        size_t initialDataLen,
                           /*[outopt]*/ TEE_ObjectHandle* object );

TEE_Result internal_TEE_OpenPersistentObject(uint32_t storageID,
              /*[in(objectIDLength)]*/ void* objectID,
                                        size_t objectIDLen,
                                        uint32_t flags,
                              /*[out]*/ TEE_ObjectHandle* object );


TEE_Result internal_TEE_CloseAndDeletePersistentObject1(TEE_ObjectHandle object, uint32_t ta_num);


/*
* Operation Management functions
*
* The following functions are used to manage cryptographic operations according to the TEE Core API
*
* AllocateOperation: allocate a cryptographic operation
* FreeOperation: free a cryptographic operation
* SetOperationKey: set a key for a cryptographic operation
* SetOperationKey2: set two keys for a cryptographic operation (NOT IMPLEMENTED)
*
* More information about the functions can be found in the TEE Core API documentation
*/

TEE_Result internal_TEE_AllocateOperation(TEE_OperationHandle* operation,           
                                    uint32_t algorithm,
                                    uint32_t mode, 
                                    uint32_t maxKeySize);

void internal_TEE_FreeOperation(TEE_OperationHandle operation);                         

TEE_Result internal_TEE_SetOperationKey(TEE_OperationHandle operation,              
                                TEE_ObjectHandle key);

TEE_Result internal_TEE_SetOperationKey2(TEE_OperationHandle operation,
                                TEE_ObjectHandle key1,
                                TEE_ObjectHandle key2);


/*
* Random Value generation and Key Generation functions
*
* The following functions are used to generate random values and keys for cryptographic operations 
*
* GenerateKey: generate a key for a cryptographic operation
* GenerateRandom: generate random data
* DeriveKey: derive a key from a cryptographic operation (NOT IMPLEMENTED)
*/

TEE_Result internal_TEE_GenerateKey(TEE_ObjectHandle object,                     
                            uint32_t keySize,
                            TEE_Attribute* params,
                            uint32_t paramCount, 
                            uint32_t ta_num);

void internal_TEE_GenerateRandom(void* randomBuffer, size_t randomBufferLen);  

void internal_TEE_DeriveKey(TEE_OperationHandle operation,
                    TEE_Attribute* params, 
                    uint32_t paramCount,
                    TEE_ObjectHandle derivedKey);


/*
* Symmetric Cipher functions
*
* The following functions are used to perform symmetric cipher operations
* AES algorithm (with different modalities like CTR, GCM, ...) is used and supported for encryption and decryption
* 
* CipherInit: initialize a cipher operation
* CipherUpdate: compute the cipher and update the ciphertext 
* CipherDoFinal: finalize the cipher operation
*
* More information about the functions can be found in the TEE Core API documentation
*/


void internal_TEE_CipherInit(TEE_OperationHandle operation,
                        void* IV, 
                        size_t IVLen);

TEE_Result internal_TEE_CipherUpdate(TEE_OperationHandle operation,
                /*[inbuf]*/ void* srcData, 
                            size_t srcLen,
               /*[outbuf]*/ void* destData, 
                            size_t *destLen);


TEE_Result internal_TEE_CipherDoFinal(TEE_OperationHandle operation,
                    /*[inbuf]*/ void* srcData, 
                                size_t srcLen,
                /*[outbufopt]*/ void* destData, 
                                size_t *destLen);


/*
* MAC functions
* 
* The following functions are used to perform MAC operations on a given message
* HMAC (with SHA) algorithm is supported for MAC operations
*
* MACInit: initialize a MAC operation
* MACUpdate: update the computed MAC with a new chunk of data
* MACComputeFinal: compute the final MAC value
*
* More information about the functions can be found in the TEE Core API documentation
*/

void internal_TEE_MACInit(TEE_OperationHandle operation,                             
                  void* IV, size_t IVLen);


void internal_TEE_MACUpdate(TEE_OperationHandle operation,
        /*[inbuf]*/ void* chunk, size_t chunkSize);                        

TEE_Result internal_TEE_MACComputeFinal(TEE_OperationHandle operation,
             /*[inbuf]*/        void* message, size_t messageLen,
             /*[outbuf]*/       void* mac, size_t *macLen);  


/*
* Asymmetric functions for Sign and Verify operations
*
* The following functions are used to sign a given message and to verify a signature
* ECDSA algorithm (with SHA) is supported for asymmetric operations
*
* AsymmetricSignDigest: sign a given message digest
* AsymmetricVerifyDigest: verify a signature of a given message digest
*
* More information about the functions can be found in the TEE Core API documentation
*/

TEE_Result internal_TEE_AsymmetricSignDigest(TEE_OperationHandle operation,
                    /*[in]*/         TEE_Attribute* params, uint32_t paramCount,
                    /*[inbuf]*/      void* digest, size_t digestLen,
                    /*[outbuf]*/     void* signature, size_t *signatureLen);  


TEE_Result internal_TEE_AsymmetricVerifyDigest(TEE_OperationHandle operation, 
                    /*[in] */ TEE_Attribute* params, uint32_t paramCount,
                    /*[inbuf]*/ void* digest, size_t digestLen,
                    /*[inbuf]*/ void* signature, size_t signatureLen); 



/*
* Message Digest functions 
*
* The following functions are used to compute the hash of a given message
* SHA algorithm is supported for message digest operations
*
* DigestUpdate: update the computed hash with a new chunk of data
* DigestDoFinal: finalize the hash operation
* DigestExtract: extract the hash value
*
* More information about the functions can be found in the TEE Core API documentation
*/

void internal_TEE_DigestUpdate(TEE_OperationHandle operation,
                               void* chunk, size_t chunkSize);

TEE_Result internal_TEE_DigestDoFinal(TEE_OperationHandle operation,
                                      /*[inbuf]*/ void *chunk, size_t chunkLen,
                                      /*[outbuf]*/ void *hash, size_t *hashLen);


TEE_Result internal_TEE_DigestExtract(TEE_OperationHandle operation,
            /*[outbuf]*/       void* hash, size_t *hashLen);

#endif // INTERNAL_CORE_API_H