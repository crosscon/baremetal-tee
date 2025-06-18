#ifndef __CORE__
#define __CORE__

#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#include "tee_common.h"

/* ----------------------------- INTERNAL CORE API FUNCTIONS ---------------------------  */

// Entry point for the TEE Core API: see the tee_core_api.c file to have more details 
// about the implementation and the execution flow of the TEE Core API functions

/** 
* Operation Management functions
*
* The following functions are used to manage cryptographic operations according to the TEE Core API
*/
TEE_Result TEE_AllocateOperation(TEE_OperationHandle* operation,           
                                    uint32_t algorithm,
                                    uint32_t mode, 
                                    uint32_t maxKeySize);

void TEE_FreeOperation(TEE_OperationHandle operation);                         

TEE_Result TEE_SetOperationKey(TEE_OperationHandle operation,              
                                TEE_ObjectHandle key);

// NOT IMPLEMENTED
//TEE_Result TEE_SetOperationKey2(TEE_OperationHandle operation,
//                                TEE_ObjectHandle key1,
//                                TEE_ObjectHandle key2);


/**
 * Message Digest Functions  
 *
 * The following functions are used to compute the hash of a given message
 * SHA algorithm is supported for message digest operations  
 */
void TEE_DigestUpdate(TEE_OperationHandle operation,
        /*inbuf]*/     void* chunk, size_t chunkSize);

TEE_Result TEE_DigestDoFinal(TEE_OperationHandle operation,
            /*[inbuf]*/      void* chunk, size_t chunkLen,
            /*[outbuf]*/     void* hash, size_t *hashLen);

TEE_Result TEE_DigestExtract(TEE_OperationHandle operation,
            /*[outbuf]*/       void* hash, size_t *hashLen);


/**
 * Symmetric Cipher Functions
 * 
 * The following functions are used to perform symmetric cipher operations
 * AES algorithm (with different modalities like CTR, GCM, ...) is used and supported for encryption and decryption
 */
void TEE_CipherInit(TEE_OperationHandle operation,  
                    void* IV, 
                    size_t IVLen);


TEE_Result TEE_CipherUpdate(TEE_OperationHandle operation,
                /*[inbuf]*/ void* srcData, 
                            size_t srcLen,
               /*[outbuf]*/ void* destData, 
                            size_t *destLen);


TEE_Result TEE_CipherDoFinal(TEE_OperationHandle operation,
                    /*[inbuf]*/ void* srcData, 
                                size_t srcLen,
                /*[outbufopt]*/ void* destData, 
                                size_t *destLen);

/*
* Asymmetric functions for Sign and Verify operations
*
* The following functions are used to sign a given message and to verify a signature
* ECDSA algorithm (with SHA) is supported for asymmetric operations
*/
TEE_Result TEE_AsymmetricSignDigest(TEE_OperationHandle operation,
                    /*[in]*/         TEE_Attribute* params, uint32_t paramCount,
                    /*[inbuf]*/      void* digest, size_t digestLen,
                    /*[outbuf]*/     void* signature, size_t *signatureLen);

TEE_Result TEE_AsymmetricVerifyDigest(TEE_OperationHandle operation,
                        /*[in]*/       TEE_Attribute* params, uint32_t paramCount,
                        /*[inbuf]*/    void* digest, size_t digestLen,
                        /*[inbuf]*/    void* signature, size_t signatureLen);


/*
* MAC functions
* 
* The following functions are used to perform MAC operations on a given message
* HMAC (with SHA) algorithm is supported for MAC operations
*/
void TEE_MACInit(TEE_OperationHandle operation,                             
                  void* IV, size_t IVLen);


void TEE_MACUpdate(TEE_OperationHandle operation,
        /*[inbuf]*/ void* chunk, size_t chunkSize);                        

TEE_Result TEE_MACComputeFinal(TEE_OperationHandle operation,
             /*[inbuf]*/        void* message, size_t messageLen,
             /*[outbuf]*/       void* mac, size_t *macLen);                


/*
* Object Management functions
* 
* The following functions are used to manage two types of objects: transient and persistent
* Transient objects are stored in the stack and heap memory of the TA
* Persistent objects are stored in the secure storage memory of the TA
*/
TEE_Result TEE_CreatePersistentObject(uint32_t storageID,
              /*[in(newObjectIDLen)]*/  void* objectID,
                                        size_t objectIDLen,
                                        uint32_t flags,
                                        TEE_ObjectHandle attributes,
                            /*[inbuf]*/ void* initialData, 
                                        size_t initialDataLen,
                           /*[outopt]*/ TEE_ObjectHandle* object );

TEE_Result TEE_OpenPersistentObject(uint32_t storageID,
              /*[in(objectIDLength)]*/ void* objectID,
                                        size_t objectIDLen,
                                        uint32_t flags,
                              /*[out]*/ TEE_ObjectHandle* object );


TEE_Result TEE_CloseAndDeletePersistentObject1(TEE_ObjectHandle object);

void TEE_CloseObject(TEE_ObjectHandle object);                          

TEE_Result TEE_ReadObjectData(TEE_ObjectHandle object,                 
                        /*[out]*/   void* buffer,
                                    size_t size,
                        /*[out]*/   size_t* count);

TEE_Result TEE_WriteObjectData(TEE_ObjectHandle object,                 
                    /*[inbuf]*/ void* buffer, 
                                size_t size );


TEE_Result TEE_AllocateTransientObject(uint32_t objectType,             
                                        uint32_t maxObjectSize,
                            /*[out]*/   TEE_ObjectHandle* object);


void TEE_FreeTransientObject(TEE_ObjectHandle object);                  

TEE_Result TEE_PopulateTransientObject(TEE_ObjectHandle object,         
                                        TEE_Attribute* attrs, 
                                        uint32_t attrCount);


void TEE_InitRefAttribute(TEE_Attribute* attr, uint32_t attributeID,    
                            void* buffer, size_t length);

void TEE_InitValueAttribute(TEE_Attribute* attr, uint32_t attributeID,  
                                uint32_t a, uint32_t b);

TEE_Result TEE_GetObjectBufferAttribute(TEE_ObjectHandle object,        
                                         uint32_t attributeID,
                        /*[outbuf]*/     void* buffer, size_t* size);



/*
* Random Value generation and Key Generation functions
*
* The following functions are used to generate random values and keys for cryptographic operations 
*/
// NOT IMPLEMENTED
//void TEE_DeriveKey(TEE_OperationHandle operation,
//                    TEE_Attribute* params, 
//                    uint32_t paramCount,
//                    TEE_ObjectHandle derivedKey );

TEE_Result TEE_GenerateKey(TEE_ObjectHandle object,                     
                            uint32_t keySize,
                            TEE_Attribute* params,
                            uint32_t paramCount);

void TEE_GenerateRandom(void* randomBuffer, size_t randomBufferLen);   


/**
 * Memory Management functions
 * 
 * The following functions are used to allocate, free, move, and fill 
 * a heap memory area defined for each TA. 
 * The heap memory is allocated as static array and is managed with a list of Blocks, 
 * where each block contains information about the size and a pointer to the next block
 * 
 * Each TA has a dedicated heap memory area of 10 KB, allocated as uint32_t array
 */
void* TEE_Malloc(size_t size, uint32_t hint);

void TEE_Free(void *buffer);

void TEE_MemMove(void* dest, void* src, size_t size);

void TEE_MemFill(void* buffer, uint8_t x, size_t size);


/**
 * BigInt Functions
 * 
 * The following functions are used to perform operations on BigInt numbers
 * BigInt numbers are used to represent large numbers that cannot be stored in a standard data type
 * BigInt numbers are needed for cryptographic operations
 */
TEE_Result TEE_BigIntConvertToS32(int32_t *dest, TEE_BigInt *src);

int32_t TEE_BigIntCmpS32(TEE_BigInt *op, int32_t shortVal);

void TEE_BigIntMod(TEE_BigInt *dest, TEE_BigInt *op, TEE_BigInt *n);

void TEE_BigIntDiv(TEE_BigInt *dest_q, TEE_BigInt *dest_r, TEE_BigInt *op1, TEE_BigInt *op2);

TEE_Result TEE_BigIntConvertFromOctetString(TEE_BigInt *dest, uint8_t *buffer, size_t bufferLen, int32_t sign);

void TEE_BigIntInit(TEE_BigInt *bigInt, size_t len);

#endif