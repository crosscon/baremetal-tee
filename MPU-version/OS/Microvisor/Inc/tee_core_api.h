#ifndef __CORE__
#define __CORE__

#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

#include "tee_common.h"

#include "psa/crypto.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/md.h" 

/* ----------------------------- TYPES AND CONSTANTS ---------------------  */

/**
 * Constants used to store information about the TAs and CA in the system, namely:
 * - max number of TAs (2)
 * - CA and TAs memory boundaries (start and end addresses in RAM)
 * - TA heap size
 */
#define NUMBER_OF_TA                0x0002
#define TRUSTED_APP_1               0x0001
#define TRUSTED_APP_2         	    0x0002
#define TA_HEAP_SIZE                1024*10 // For the moment, each TA has a dedicated heap of 10KB
#define TA1_MEMORY_START_ADDR        0x20000000
#define TA1_MEMORY_END_ADDR          0x2000BFFF
#define TA2_MEMORY_START_ADDR        0x2000C000
#define TA2_MEMORY_END_ADDR          0x20017FFF
#define CA_MEMORY_START_ADDR         0x10002000
#define CA_MEMORY_END_ADDR           0x10007FFF

/**
 * Basic building block for the heap memory dedicated to each TA 
 * Defines:
 * - the size of the block
 * - a pointer to the next block
 * - a flag to indicate if the block is free or not
 */
typedef struct Block {
    uint32_t size;
    struct Block* next;
    uint8_t free;
} Block;

/**
 * Constants used for Secure Storage 
 *  
 * Define:
 * - the minimu size of a page in the flash memory that can be read or written
 * - the base address where the secure storage area starts for each TA (based on memory map)
 * - the number of pages used for the secure storage area for each TA
 * - the page index where the secure storage area for each TA starts
 * - the size of the secure storage area for each TA
 */   
#define MCU_FLASH_PAGE_SIZE         2048 // Page or sector size, please check the MCU datasheet
#define TA1_SEC_STR_BASE_ADDR       0x0805C000 // Base address of the secure storage area for TA1
#define TA2_SEC_STR_BASE_ADDR       0x0809C000 // Base address of the secure storage area for TA2
#define TA1_PAGE_COUNT              8 // Number of pages used for the secure storage area for TA1
#define TA2_PAGE_COUNT              8 // Number of pages used for the secure storage area for TA2
#define TA1_PAGE_INDEX              184  //Page index where the secure storage area for TA1 starts
#define TA2_PAGE_INDEX              312 //Page index where the secure storage area for TA2 starts
#define TA1_FLASH_SIZE              (MCU_FLASH_PAGE_SIZE * TA1_PAGE_COUNT) // Size of the secure storage area for TA1
#define TA2_FLASH_SIZE              (MCU_FLASH_PAGE_SIZE * TA2_PAGE_COUNT) // Size of the secure storage area for TA2


/** 
 * Definition of the Object Handle structure
 * This structure is used to store the object attributes and the object data
 * 
 * The object data is stored in the buffer field (after reading it from the secure storage in case of persistent objects)
 * The object attributes are stored in the attrs field
 * Object ID, an identification used for each object, is stored in the obj_id field 
 * The flags field is used to define if the payload is readable or writable
 * The obj_type field is used to define the type of the object (AES, ECDSA, HMAC, etc.)
 * The obj_storage_type field is used to define the storage type of the object (transient or persistent)
 * The key_len field is used to store the length of the key (in case a crypto key is stored)
 */
typedef struct{
    TEE_Attribute attrs[4];
    char*     buffer;
    size_t    len;
    uint32_t  obj_id;
    uint32_t  flags;// Define if the payload is readable or writable
    uint32_t  obj_type;
    uint8_t   obj_storage_type;
    uint32_t  key_len;
}__TEE_ObjectHandle;


/**
 * Definition of the Operation Handle structure
 * This structure is used to store the operation attributes and data (different for each operation type)
 * 
 * Each operation stores the info and at least one key (key1)
 * The second key (key2) is used only for some operation types
 */
typedef struct  
{
    TEE_OperationInfo info;
    TEE_ObjectHandle key1; 
    TEE_ObjectHandle key2; 
    uint32_t operationState; /* Operation state : INITIAL or ACTIVE */

    // for Encryption, Decryption, MAC and Hash
    psa_key_id_t key_id;
    psa_cipher_operation_t* cipher_op;
    psa_hash_operation_t*   hash_op;
    psa_mac_operation_t*    mac_op;

    // for signature and verification
    mbedtls_ecdsa_context ctx_sign;
    mbedtls_ecdsa_context ctx_verify;
    mbedtls_ecp_point Q; 

    // for random number generation
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
}__TEE_OperationHandle;


/**************** Object Types ***************************/
#define TEE_TYPE_AES                0xA0000010 // Possible key size 128, 192, 256
#define TEE_TYPE_ECDSA_PUBLIC_KEY   0xA0000041 // Between 160-521 bit
#define TEE_TYPE_ECDSA_KEYPAIR      0xA1000041 // Between 160-521 bit
#define TEE_TYPE_HMAC_SHA256        0xA0000004 // Between 192 and 1024 bits
#define TEE_TYPE_HMAC_SHA384        0xA0000005 // Between 256 and 1024 bits
#define TEE_TYPE_HMAC_SHA512        0xA0000006 // Between 256 and 1024 bits
#define TEE_TYPE_HMAC_SHA3_256      0xA0000009
#define TEE_TYPE_HMAC_SHA3_384      0xA000000A
#define TEE_TYPE_HMAC_SHA3_512      0xA000000B

/**************** Mode Types *****************************/
#define TEE_MODE_ENCRYPT            0x00000000
#define TEE_MODE_DECRYPT            0x00000001
#define TEE_MODE_SIGN               0x00000002
#define TEE_MODE_VERIFY             0x00000003
#define TEE_MODE_MAC                0x00000004
#define TEE_MODE_DIGEST             0x00000005


/**************** Crypto Algorithms Constants ************************/
/**
    @param OBJECT_TYPE  TEE_TYPE_AES
    @param MODE         TEE_MODE_ENCRYPT or TEE_MODE_DECRYPT
*/       
#define TEE_ALG_AES_ECB_NOPAD       0x10000010 // PSA_ALG_ECB_NO_PADDING
#define TEE_ALG_AES_CBC_NOPAD       0x10000110 // PSA_ALG_CBC_NO_PADDING
#define TEE_ALG_AES_CTR             0x10000210 // PSA_ALG_CTR
#define TEE_ALG_AES_CTS             0x10000310 // ?
#define TEE_ALG_AES_XTS             0x10000410 // PSA_ALG_XTS
#define TEE_ALG_AES_CBC_MAC_NOPAD   0x30000110 // PSA_ALG_CBC_MAC
#define TEE_ALG_AES_CBC_MAC_PKCS5   0x30000510 // ?
#define TEE_ALG_AES_CMAC            0x30000610 // PSA_ALG_CMAC
#define TEE_ALG_AES_CCM             0x40000710 // PSA_ALG_CCM    
#define TEE_ALG_AES_GCM             0x40000810 // PSA_ALG_GCM

/**
    @param OBJECT_TYPE  Nan
    @param MODE         TEE_MODE_SIGN or TEE_MODE_VERIFY
*/
#define TEE_ALG_SHA256              0x50000004
#define TEE_ALG_SHA384              0x50000005
#define TEE_ALG_SHA512              0x50000006      
#define TEE_ALG_SHA3_256            0x30000008 // 0x11
#define TEE_ALG_SHA3_384            0x30000009 // 0x12
#define TEE_ALG_SHA3_512            0x3000000B // 0X13

/**
    @param OBJECT_TYPE  TEE_TYPE_ECDSA_PUBLIC_KEY or TEE_TYPE_ECDSA_KEYPAIR
    @param MODE         TEE_MODE_DIGEST
*/      
#define TEE_ALG_ECDSA_SHA256        0x70003042 // 0x11
#define TEE_ALG_ECDSA_SHA384        0x70004042 // 0x12
#define TEE_ALG_ECDSA_SHA512        0x70005042 // 0x13
#define TEE_ALG_ECDSA_SHA3_256      0x70007042 // 0x11
#define TEE_ALG_ECDSA_SHA3_384      0x70008042 // 0x12
#define TEE_ALG_ECDSA_SHA3_512      0x70009042 // 0x13

// Deprecated algorithms identifiers
#define TEE_ALG_ECDSA_P256              TEE_ALG_ECDSA_SHA256 // Replaced with TEE_ALG_ECDSA_SHA256, same value
#define TEE_ALG_ECDSA_P384              TEE_ALG_ECDSA_SHA384
#define TEE_ALG_ECDSA_P521              TEE_ALG_ECDSA_SHA512

/**
    @param OBJECT_TYPE  TEE_TYPE_HMAC_SHA512
    @param MODE         TEE_MODE_MAC
*/ 
#define TEE_ALG_HMAC_SHA256         0x30000004
#define TEE_ALG_HMAC_SHA384         0x30000005
#define TEE_ALG_HMAC_SHA512         0x30000006  // 0x0b(512) 0x0a(384) 0x09(256)


/**************** Attribute Constants *********************/

#define TEE_ATTR_ECC_PRIVATE_VALUE      0xC0000341 
#define TEE_ATTR_ECC_PUBLIC_VALUE_X     0xD0000141 
#define TEE_ATTR_ECC_PUBLIC_VALUE_Y     0xD0000241 
#define TEE_ATTR_ECC_CURVE              0xF0000441

/*      Eliptic Curve Algorithms*/
#define TEE_CRYPTO_ELEMENT_NONE         0x00000000
#define TEE_ECC_CURVE_NIST_P192         0x00000001
#define TEE_ECC_CURVE_NIST_P224         0x00000002
#define TEE_ECC_CURVE_NIST_P256         0x00000003
#define TEE_ECC_CURVE_NIST_P384         0x00000004
#define TEE_ECC_CURVE_NIST_P521         0x00000005
// NOT Supported by mbedtls
/*#define TEE_ECC_CURVE_BSI_P160r1      0x00000101
#define TEE_ECC_CURVE_BSI_P192r1        0x00000102 
#define TEE_ECC_CURVE_BSI_P224r1        0x00000103*/
#define TEE_ECC_CURVE_BSI_P256r1        0x00000104
#define TEE_ECC_CURVE_BSI_P384r1        0x00000105
#define TEE_ECC_CURVE_BSI_P512r1        0x00000106

/**************** Algorithm Usage Constants ***************************/
#define TEE_USAGE_EXTRACTABLE       0x00000001 // ?
#define TEE_USAGE_ENCRYPT           0x00000002 // PSA_KEY_USAGE_ENCRYPT
#define TEE_USAGE_DECRYPT           0x00000004 // PSA_KEY_USAGE_DECRYPT
#define TEE_USAGE_MAC               0x00000008 // ?
#define TEE_USAGE_SIGN              0x00000010 // PSA_KEY_USAGE_SIGN_MESSAGE
#define TEE_USAGE_VERIFY            0x00000020 // PSA_KEY_USAGE_VERIFY_MESSAGE
#define TEE_USAGE_DERIVE            0x00000040 // PSA_KEY_USAGE_DERIVE


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