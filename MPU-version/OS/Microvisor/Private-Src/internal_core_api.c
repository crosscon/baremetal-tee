#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> //for file handling

#include "internal_core_api.h"
#include "mbedtls/ctr_drbg.h"
#include "stm32l4xx_hal.h"
#include "mbedtls/entropy.h"
#include "flash.h"


/************************** RANDOM VALUES GENERATION FUNCTIONS ********************************* */

// Functions to generate random values using the RNG peripheral of the STM32L475

uint32_t rng_get(void) 
{
	/* Wait until one RNG number is ready */
	while (!(RNG->SR & (RNG_SR_DRDY)));

	/* Get a 32-bit Random number */
	return RNG->DR;
}

uint32_t trng_createNumber(void)
{
	while (!(RNG->SR & (RNG_SR_DRDY)));

	/* Get a 32-bit Random number */
	return RNG->DR;
}

int mbedtls_hardware_poll(void *data, unsigned char *output, size_t len, size_t *olen)
{
    uint32_t random_value;
    size_t i;

    for (i = 0; i < len / 4; i++)
    {
        random_value = rng_get();
        memcpy(output + i * 4, &random_value, 4);
    }

    // Handle the remainder if len is not a multiple of 4
    if (len % 4 != 0)
    {
        random_value = rng_get();
        memcpy(output + i * 4, &random_value, len % 4);
    }

    *olen = len;
    return 0;
}

/************************** TEE MEMORY MANAGEMENT FUNCTIONS ********************************* */

/**
 * Define the heap memory for each TA
 * 
 * The heap memory is allocated as static array and is managed with a list of Blocks
 * Each block contains information about the size and a pointer to the next block
 * 
 * Each TA has a dedicated heap memory area of 10 KB, allocated as uint32_t array
 * uint32_t is used to ensure that every type of variable (with different types)
 * can be stored in the heap memory. The heaps are placed in different memory sections
 * using the (heap_TA1 and heap_TA2) using the linker script file
 * 
 * This memory can be allocated using the TEE_Malloc function and freed using the TEE_Free function
*/
__attribute__((section(".heap_TA1"))) static uint32_t heapTA1[TA_HEAP_SIZE / sizeof(uint32_t)]; 
__attribute__((section(".heap_TA2"))) static uint32_t heapTA2[TA_HEAP_SIZE / sizeof(uint32_t)];

__attribute__((section(".heap_TA1"))) static Block* freeListTA1 = {0};
__attribute__((section(".heap_TA2"))) static Block* freeListTA2 = {0};


// Initialize the heap memory for each TA during the boot process
void heap_erase() 
{
    freeListTA1 = NULL;
    freeListTA2 = NULL;
}

// Set the correct values for the heap memory of each TA when they are first used
static void init_memory(int ta_num) 
{
    if(ta_num == 1) {
        freeListTA1->size = TA_HEAP_SIZE - sizeof(Block);
        freeListTA1->next = NULL;
        freeListTA1->free = 1;
    } 
    
    if(ta_num == 2) {
        freeListTA2->size = TA_HEAP_SIZE - sizeof(Block);
        freeListTA2->next = NULL;
        freeListTA2->free = 1;
    }
}

/**
 * @brief Allocate a memory area of a given size using the heap memory of the TA
 * 
 * @param ta_num TA number (1 or 2)
 * @param size Size of the memory area to allocate
 * @param hint Hint for the allocation (e.g., TEE_MALLOC_FILL_ZERO)
 */
void* internal_TEE_Malloc(int ta_num, size_t size, uint32_t hint)
{   
    Block* curr = NULL;

    if(ta_num == 1) {
        if(!freeListTA1){
            freeListTA1 = (Block*)heapTA1;
            init_memory(ta_num);
        }
        curr = freeListTA1;
    } else if(ta_num == 2) {
        if (!freeListTA2) {
            freeListTA2 = (Block*)heapTA2;
            init_memory(ta_num);
        }
        curr = freeListTA2;   
    }

    while (curr != NULL)
    {
        if ((curr->free) && (curr->size >= size))
        {
            if (curr->size > size + sizeof(Block))
            {
                Block* newBlock = (Block*)((uint32_t*)curr + sizeof(Block) + size); 
                newBlock->size = curr->size - size - sizeof(Block);
                newBlock->next = curr->next;
                newBlock->free = 1;
                curr->size = size;
                curr->next = newBlock;
            }
            curr->free = 0;

            if(hint == TEE_MALLOC_FILL_ZERO)
            	memset((uint32_t*)curr + sizeof(Block) , 0, size); 

            return (void*)((uint32_t*)curr + sizeof(Block));
        }
        curr = curr->next;
    }
    return NULL;
}

/**
 * @brief Free a memory area allocated using the TEE_Malloc function
 * 
 * @param ta_num TA number (1 or 2)
 * @param buffer Pointer to the memory area to be freed
 */
void internal_TEE_Free(int ta_num, void* buffer) 
{
    if (buffer == NULL) {
        goto err;
    }

    if (ta_num == 1) {
        if((buffer < TA1_MEMORY_START_ADDR) || (buffer > TA1_MEMORY_END_ADDR)){
            if (buffer < CA_MEMORY_START_ADDR || buffer > CA_MEMORY_END_ADDR) {
                ERR_MSG("Free function error");
    	        goto err;
            }
        }
    } else if (ta_num == 2) {
        if((buffer < TA2_MEMORY_START_ADDR) || (buffer > TA2_MEMORY_END_ADDR)){
    	    if (buffer < CA_MEMORY_START_ADDR || buffer > CA_MEMORY_END_ADDR) {
                ERR_MSG("Free function error");
    	        goto err;
            }
        }
    }

    Block* block = (Block*)((uint32_t*)buffer - sizeof(Block));
    block->free = 1;

    Block* curr = NULL;
    if (ta_num == 1) {
        curr = freeListTA1;
    } else if (ta_num == 2) {
        curr = freeListTA2;
    }
    while (curr != NULL)
    {
        if (curr->free) {
            curr->size += sizeof(Block) + curr->next->size;
            curr->next = curr->next->next;
            break;
        }
        curr = curr->next;
    }

    err:
}

/**
 * @brief Move a memory area to another location
 * 
 * @param ta_num TA number (1 or 2)
 * @param dest Destination memory area
 * @param src Source memory area
 * @param size Size of the memory area to move
 */
void internal_TEE_MemMove(int ta_num, void* dest, void* src, size_t size)
{
    // TODO: check also if buffer end is in the TA memory range
    if (ta_num == 1) {
        if((dest < TA1_MEMORY_START_ADDR) || (dest > TA1_MEMORY_END_ADDR)){
            if (dest < CA_MEMORY_START_ADDR || dest > CA_MEMORY_END_ADDR) {
                ERR_MSG("Mem move error");
    	        goto end;
            }
        }
    } else if (ta_num == 2) {
        if((dest < TA2_MEMORY_START_ADDR) || (dest > TA2_MEMORY_END_ADDR)){
    	    if (dest < CA_MEMORY_START_ADDR || dest > CA_MEMORY_END_ADDR) {
                ERR_MSG("Mem move function error");
    	        goto end;
            }
        }
    }

	memmove(dest, src, size);

    end:
        // Do nothing
}


/**
 * @brief Fill a memory area with a given value
 * 
 * @param ta_num TA number (1 or 2)
 * @param buffer Pointer to the memory area to fill
 * @param x Value to fill the memory area with
 * @param size Size of the memory area to fill
 */
void internal_TEE_MemFill(int ta_num, void* buffer, uint8_t x, size_t size)
{
    // TODO: check also if buffer end is in the TA memory range
    if (ta_num == 1) {
        if((buffer < TA1_MEMORY_START_ADDR) || (buffer > TA1_MEMORY_END_ADDR)){
            if (buffer < CA_MEMORY_START_ADDR || buffer > CA_MEMORY_END_ADDR) {
                ERR_MSG("Mem fill function error");
    	        goto end;
            }
        }
    } else if (ta_num == 2) {
        if((buffer < TA2_MEMORY_START_ADDR) || (buffer > TA2_MEMORY_END_ADDR)){
    	    if (buffer < CA_MEMORY_START_ADDR || buffer > CA_MEMORY_END_ADDR) {
                ERR_MSG("Mem fill function error");
    	        goto end;
            }
        }
    }

    memset(buffer, x, size);

    end:
        // Do nothing
}


/************************** TEE OBJECTS FUNCTIONS ********************************* */

/**
 * @brief Allocate a transient object with the given type and max size
 * 
 * @param objectType please check the global platform documentation page 141, table 5.9
 * @param maxObjectSize max key size
 * @param object pointer to the object handle
 * 
 * @return TEE_SUCCESS if the object is allocated successfully, TEE_FAILED otherwise
 */
TEE_Result internal_TEE_AllocateTransientObject(uint32_t objectType,
                                        uint32_t maxObjectSize,
                                        TEE_ObjectHandle* object)
{
    if((!object) || (maxObjectSize <= 0)){
        ERR_MSG("Invalid key sizze or null parameter");
        return TEE_FAILED;
    }

    __TEE_ObjectHandle *obj = (__TEE_ObjectHandle*)malloc(sizeof(__TEE_ObjectHandle));
    if(!obj){
        ERR_MSG("Object allocation is failed");
        return TEE_FAILED;
    }

    uint32_t key_size =  maxObjectSize/8;

    //Set all attrs params to zero to indicate they are not initialized
    for (int i=0; i<4; i++)
    {
        obj->attrs[i].attributeID = 0;
        obj->attrs[i].content.ref.buffer = NULL;
        obj->attrs[i].content.ref.length = 0;
    }

    // Allocate memory area to store the key
    obj->buffer = (char*)calloc(key_size, sizeof(char));
    if(!obj->buffer){
        free(obj);
        ERR_MSG("Buffer allocation for transient object failed");
        return TEE_FAILED;
    }

    obj->obj_type = objectType;
    obj->key_len = maxObjectSize;
    obj->obj_id = 0; //For transient objects it must be zero, it is just for persistent one
    obj->obj_storage_type = TEE_OBJ_TYPE_TRANSIENT;
    
    *object = (void*)obj;

    return TEE_SUCCESS;
}


/**
 * @brief Populate the attributes of a transient object
 * 
 * @param object pointer to the object handle
 * @param attrs pointer to the attributes
 * @param attrCount number of attributes
 * 
 * @return TEE_SUCCESS if the attributes are populated successfully, TEE_FAILED otherwise
 */

TEE_Result internal_TEE_PopulateTransientObject(TEE_ObjectHandle object,
                                /*unused*/      TEE_Attribute* attrs, 
                                /*unused*/      uint32_t attrCount)
{
    if(!object){
        ERR_MSG("Object does not exists");
        return TEE_FAILED;
    }

    if(!attrs){
        ERR_MSG("Attributes does not exists");
        return TEE_FAILED;
    }

    __TEE_ObjectHandle *temp_obj = (__TEE_ObjectHandle*)object;

    // Copy the attributes from the parameter to the object
    for(uint32_t i=0; i<attrCount; i++)
    {
        temp_obj->attrs[i].attributeID = attrs[i].attributeID;
        temp_obj->attrs[i].content.ref.buffer = attrs[i].content.ref.buffer;
        temp_obj->attrs[i].content.ref.length = attrs[i].content.ref.length;
        temp_obj->attrs[i].content.value.a = attrs[i].content.value.a;
        temp_obj->attrs[i].content.value.b = attrs[i].content.value.b;
    }

    return TEE_SUCCESS;
}

/**
 * @brief Initialize a reference attribute
 * 
 * @param attr pointer to the attribute
 * @param attributeID attribute ID
 * @param buffer pointer to the buffer
 * @param length length of the buffer
 */
void internal_TEE_InitRefAttribute(TEE_Attribute* attr, uint32_t attributeID, 
                            void* buffer, size_t length)
{
    if(attr)
    {
        attr->attributeID = attributeID;
        attr->content.ref.buffer = buffer;
        attr->content.ref.length = length;
    }
}

/**
 * @brief Initialize a value attribute
 * 
 * @param attr pointer to the attribute
 * @param attributeID attribute ID
 * @param a value a
 * @param b value b
 */
void internal_TEE_InitValueAttribute(TEE_Attribute* attr, uint32_t attributeID,
                                uint32_t a, uint32_t b)
{
    if(attr)
    {
        attr->attributeID = attributeID;
        attr->content.value.a = a;
        attr->content.value.b = b;
    }
}

/**
 * @brief Get the buffer attribute of an object with the given attribute ID
 * 
 * @param object pointer to the object handle
 * @param attributeID attribute ID
 * @param buffer pointer to the buffer to store the attribute
 * @param size pointer to store the size of the attribute
 * 
 * @return TEE_SUCCESS if the attribute is found and returned, TEE_FAILED otherwise
 * 
 */
TEE_Result internal_TEE_GetObjectBufferAttribute(TEE_ObjectHandle object, uint32_t attributeID,
                                 /*[outbuf]*/     void* buffer, size_t* size) 
{
    if(!object){
        ERR_MSG("Object does not exists");
        return TEE_FAILED;
    }

    __TEE_ObjectHandle *obj = (__TEE_ObjectHandle*)object;

    for(int i=0; i<4; i++)
    {
        if(obj->attrs[i].attributeID == attributeID)
        {
            memcpy(buffer, obj->attrs[i].content.ref.buffer, obj->attrs[i].content.ref.length);
            *size = obj->attrs[i].content.ref.length;
            return TEE_SUCCESS;
        }
    }

    return TEE_FAILED;
}


/**
 * @brief Get the value attributes of an object with the given attribute ID
 * 
 * @param object pointer to the object handle
 * @param attributeID attribute ID
 * @param a pointer to store the value a
 * @param b pointer to store the value b
 * 
 * @return TEE_SUCCESS if the attribute is found and returned, TEE_FAILED otherwise
 */
TEE_Result internal_TEE_GetObjectValueAttribute(TEE_ObjectHandle object, uint32_t attributeID,
                                                            uint32_t* a, uint32_t* b)
{
    if(!object){
        //TODO err
        return TEE_FAILED;
    }

    __TEE_ObjectHandle *obj = (__TEE_ObjectHandle*)object;

    for(int i=0; i<4; i++)
    {
        if(obj->attrs[i].attributeID == attributeID)
        {
            *a = obj->attrs[i].content.value.a;
            *b = obj->attrs[i].content.value.b;
            return TEE_SUCCESS;
        }
    }

    return TEE_FAILED;
}


/**
 * @brief Free a transient object
 * 
 * @param object pointer to the object handle
 */
void internal_TEE_FreeTransientObject(TEE_ObjectHandle object)
{
    __TEE_ObjectHandle *temp_obj = (__TEE_ObjectHandle*)object;

    if(temp_obj){
        // Free the attributes if they are buffer
        for (int i=0; i<4; i++)
        {
            if(temp_obj->attrs[i].content.ref.buffer != NULL){
                temp_obj->attrs[i].content.ref.buffer = NULL;
            }     
        }
        // Free the buffer if it is allocated
        if (temp_obj->buffer != NULL){
            free(temp_obj->buffer);
            temp_obj->buffer = NULL;
        }
        free(temp_obj);
    }  
}


/**
 * @brief Close an object (transient or persistent) by freeing the allocated memory
 * 
 * @param object pointer to the object handle
 */
void internal_TEE_CloseObject(TEE_ObjectHandle object)
{
    __TEE_ObjectHandle *temp_obj = (__TEE_ObjectHandle*)object;

    if(!temp_obj) {
        ERR_MSG("Object does not exists");

    } else {
        // If buffer is allocated, release it
        if(temp_obj->buffer != NULL)
            free(temp_obj->buffer);

        // Free the object itself
        free(temp_obj);
    }
}


/**
 * @brief Read the data of a persistent object
 * 
 * @param object pointer to the object handle
 * @param buffer pointer to the buffer to store the data
 * @param size size of the data to read
 * @param count pointer to store the number of bytes read
 * @param ta_num TA number
 * 
 * @return TEE_SUCCESS if the data is read successfully, TEE_FAILED otherwise
 */
TEE_Result internal_TEE_ReadObjectData(TEE_ObjectHandle object,
                            /*[out]*/   void* buffer,
                                        size_t size,
                            /*[out]*/   size_t* count, 
                                        uint32_t ta_num) 
{
    // Check the file reading access right
    if(!object){
        ERR_MSG("Object handle is null");
        return TEE_FAILED;
    }

    __TEE_ObjectHandle *obj = (__TEE_ObjectHandle*)object;

    *count = 0; //Readed size is 0
    if(obj->obj_storage_type == TEE_OBJ_TYPE_PERSISTENT) // Check if it is a persistent object
    {
        // Set secure stroage area parameters
        uint32_t start_addr = 0; // Secure storage area starting address
        uint32_t total_size = 0; // Secure storage area total size
        const int free_size = flash_getFreeSize(ta_num);
        flash_getConfig(ta_num, &start_addr, &total_size);

        // Create a buffer to read raw flash data
        char temp_buff[total_size - free_size];
        memset(temp_buff, 0, total_size - free_size);

        // Read the raw data from the flash memory
        flash_internalRead((uint8_t*)temp_buff, total_size - free_size, start_addr);
        
        // Extract the object data from the raw data
        *count = flash_readObject((const char*)temp_buff, total_size - free_size, obj->obj_id, buffer, size);
        if(*count <= 0)
            return TEE_FAILED;

    }

    return TEE_SUCCESS;
} 


/**
 * @brief Write the data into a persistent object
 * 
 * @param object pointer to the object handle
 * @param buffer pointer to the buffer containing the data to write
 * @param size size of the data to write
 * @param ta_num TA number
 * 
 * @return TEE_SUCCESS if the data is written successfully, TEE_FAILED otherwise
 */
TEE_Result internal_TEE_WriteObjectData(TEE_ObjectHandle object,
                    /*[inbuf]*/ void* buffer, 
                                size_t size, 
                                uint32_t ta_num)
{
    if(!object){
        ERR_MSG("Object handle is null");
        return TEE_FAILED;
    }

    __TEE_ObjectHandle *obj = (__TEE_ObjectHandle*)object;

    // This method can change later according to the core api documentation page 173 and descprition of this function
    // The mechanism in the documentation assume that there is a file system and overwrited data will start at the current position
    // However there is not fs in this case, and for now, if the buffer is already allocated, do not overwrite

    if(!obj->buffer)
        return TEE_FAILED;

    if(obj->obj_storage_type == TEE_OBJ_TYPE_PERSISTENT) // Check if it is a persistent object
    {
        if(flash_writeNewObject(buffer, size, obj->obj_id, ta_num) <= 0)
            return TEE_FAILED;

    }

    return TEE_SUCCESS;
}


/**
 * @brief Create a persistent object in the secure storage area of a TA
 * 
 * @param storageID storage identifier used in this implementation to pass the TA number (as otherwise it is not used)
 * @param objectID pointer to the object identifier
 * @param objectIDLen length of the object identifier
 * @param flags object flags
 * @param attributes pointer to the object attributes
 * @param initialData pointer to the initial data
 * @param initialDataLen length of the initial data
 * @param object pointer to the object handle
 * 
 * @return TEE_SUCCESS if the object is created successfully, TEE_FAILED otherwise
 */
TEE_Result internal_TEE_CreatePersistentObject(uint32_t storageID,
                    /*[in(newObjectIDLen)]*/   void* objectID,
                                               size_t objectIDLen,
                                               uint32_t flags,
                                               TEE_ObjectHandle attributes,
                                 /*[inbuf]*/   void* initialData, 
                                               size_t initialDataLen,
                                /*[outopt]*/   TEE_ObjectHandle* object) 
{
    // Check if the initial data exists and the size is greater than 0
    if((!initialData) || (initialDataLen <= 0))
    {
        ERR_MSG("Initial data param err");
        return TEE_FAILED;
    }

    __TEE_ObjectHandle *temp_obj = (__TEE_ObjectHandle*)malloc(sizeof(__TEE_ObjectHandle));

    if(!temp_obj){
        ERR_MSG("Object hadle is null");
        return TEE_FAILED;
    }

    memcpy(&temp_obj->obj_id, objectID, objectIDLen);

    //Allocate memory to store initial Data
    temp_obj->buffer = (char*)malloc(initialDataLen * sizeof(char));
    memcpy(temp_obj->buffer, initialData, initialDataLen);
    temp_obj->len = initialDataLen;

    // Set the object flags
    temp_obj->flags = flags;
    flags = flags & TEE_OBJ_READ_AND_WRITE;

    if(((flags | TEE_OBJ_JUST_WRITE) == TEE_OBJ_JUST_WRITE) || ((flags | TEE_OBJ_READ_AND_WRITE) == TEE_OBJ_READ_AND_WRITE))
    {
        // Initialize the cJSON hooks (to be able to use cJSON functions and avoid NULL pointer errors)
        cJSON_InitHooks(NULL); 

        // NOTE: storageID was not used in the current implementation so it is used to indicate the TA number        
        // NOTE 2: use int number as a string in objectID parameter
        // If you want to use strings, please use the following:
        //memcpy(&temp_obj->obj_id, objectID, objectIDLen);
        //temp_obj->obj_id = atoi(objectID); 

        if(flash_writeNewObject((const char*)initialData, initialDataLen, temp_obj->obj_id, storageID) < 0)
            return TEE_FAILED;
    }

    // Set the object storage type
    temp_obj->obj_storage_type = TEE_OBJ_TYPE_PERSISTENT;

    *object = (void*)temp_obj;

    return TEE_SUCCESS;
}


/**
 * @brief Open a persistent object in the secure storage area of a TA
 * 
 * @param storageID storage identifier used in this implementation to pass the TA number (as otherwise it is not used)
 * @param objectID pointer to the object identifier
 * @param objectIDLen length of the object identifier
 * @param flags object flags
 * @param object pointer to the object handle
 * 
 * @return TEE_SUCCESS if the object is opened successfully, TEE_FAILED otherwise
 */
TEE_Result internal_TEE_OpenPersistentObject(uint32_t storageID,
                    /*[in(objectIDLength)]*/ void* objectID,
                                             size_t objectIDLen,
                                             uint32_t flags,
                                    /*[out]*/ TEE_ObjectHandle* object) 
{
    // Check object_id and object_id_len to ensure if given object id value
    if((objectIDLen <= 0) || (!objectID)){
        ERR_MSG("Object ID was not given");
        return TEE_FAILED;
    }
    
    if(!object){
        ERR_MSG("Null parameter");
        return TEE_FAILED;
    }

    __TEE_ObjectHandle *temp_obj = (__TEE_ObjectHandle*)malloc(sizeof(__TEE_ObjectHandle));
    if(!temp_obj){
        ERR_MSG("Object handle is null");
        return TEE_FAILED;
    }

    temp_obj->obj_storage_type = TEE_OBJ_TYPE_PERSISTENT;
    temp_obj->flags = flags;
    temp_obj->buffer = NULL;

    flags = flags & TEE_OBJ_READ_AND_WRITE;
    if(((flags | TEE_OBJ_JUST_READ) == TEE_OBJ_JUST_READ) || ((flags | TEE_OBJ_READ_AND_WRITE) == TEE_OBJ_READ_AND_WRITE))
    {
        // Initialize the cJSON hooks (to be able to use cJSON functions and avoid NULL pointer errors)
        cJSON_InitHooks(NULL);

        uint32_t start_addr = 0;
        uint32_t total_size = 0;

        // NOTE: storageID was not used in the current implementation so it is used to indicate the TA number
        // Get information about the secure storage area
        const int free_size = flash_getFreeSize(storageID);

         if(free_size < 0){
            free(temp_obj);
            return TEE_FAILED;
        }

        flash_getConfig(storageID, &start_addr, &total_size);
        char temp_buff[total_size - free_size];
        memset(temp_buff, 0, total_size - free_size);

        // NOTE: use int number as a string in objectID parameter
        // If you want to use strings, please comment below: memcpy(&temp_obj->obj_id, objectID, objectIDLen);
        //and use: temp_obj->obj_id = atoi(objectID);
        memcpy(&temp_obj->obj_id, objectID, objectIDLen);  
        temp_obj->obj_storage_type = TEE_OBJ_TYPE_PERSISTENT;
        *object = (void*)temp_obj;

        flash_internalRead((uint8_t*)temp_buff, total_size - free_size, start_addr);

        int ret = flash_readObject((const char*)temp_buff, total_size - free_size, temp_obj->obj_id, NULL, 0);
        if(ret <= 0)
            return TEE_FAILED;

        return TEE_SUCCESS;
    }

    return TEE_FAILED;
}


/**
 * @brief Close and delete a persistent object in the secure storage area of a TA
 * 
 * @param object pointer to the object handle
 * @param ta_num TA number
 * 
 * @return TEE_SUCCESS if the object is closed and deleted successfully, TEE_FAILED otherwise
 */
TEE_Result internal_TEE_CloseAndDeletePersistentObject1(TEE_ObjectHandle object, uint32_t ta_num)
{
    __TEE_ObjectHandle *temp_obj = (__TEE_ObjectHandle*)object;

    if(!temp_obj){
        ERR_MSG("Object does not exists");
        return TEE_FAILED;
    }

    // Check if the object is persistent and delete it
    if(temp_obj->obj_storage_type == TEE_OBJ_TYPE_PERSISTENT) {
        int res = flash_deleteObject(ta_num, temp_obj->obj_id);
        if(res < 0) {
            ERR_MSG("Object deletion failed");
            return TEE_FAILED;
        }
    }

    // Free the buffer and the object itself
    if(temp_obj->buffer)
        free(temp_obj->buffer);

    free(temp_obj);

    return TEE_SUCCESS;
}


/************************** TEE BIGINT FUNCTIONS ********************************* */

/**
 * @brief Convert a big integer to a int32_t value
 * 
 * @param dest pointer to the destination of the conversion (int32_t)
 * @param src pointer to the source of the conversion (TEE_BigInt)
 * 
 * @return TEE_SUCCESS if the conversion is successful, TEE_ERROR_OVERFLOW otherwise
 */
TEE_Result internal_TEE_BigIntConvertToS32(int32_t *dest, TEE_BigInt *src)
{
    if(*src > 0x7FFFFFFF)
        return TEE_ERROR_OVERFLOW;

    *dest = *src;

    return TEE_SUCCESS;
}

/**
 * @brief Compare a big integer with a uint32_t value
 * 
 * @param op pointer to the big integer
 * @param shortVal uint32_t value
 * 
 * @return -1 if the big integer is less than the short value, 0 if they are equal, 
 *          1 if the big integer is greater than the short value
 */
int32_t internal_TEE_BigIntCmpS32(TEE_BigInt *op, int32_t shortVal)
{
    if(*op < (uint32_t)shortVal){
        return -1;
    }
    
    if(*op > (uint32_t)shortVal){
        return shortVal;
    }

    return 0;
}

/**
 * @brief Execute the modulo operation on two big integers
 * 
 * @param dest pointer to the destination of the operation where the result is stored
 * @param op pointer to the first big integer that is the dividend
 * @param n pointer to the second big integer that is the divisor (modulus)
 */
void internal_TEE_BigIntMod(TEE_BigInt *dest, TEE_BigInt *op, TEE_BigInt *n)
{
    *dest = *op % *n;
}

/**
 * @brief Execute the division operation (with a reminder) on two big integers
 * 
 * @param dest_q pointer to the destination of the quotient
 * @param dest_r pointer to the destination of the reminder
 * @param op1 pointer to the first big integer that is the dividend
 * @param op2 pointer to the second big integer that is the divisor
 */
void internal_TEE_BigIntDiv(TEE_BigInt *dest_q, TEE_BigInt *dest_r, TEE_BigInt *op1, TEE_BigInt *op2)
{
    if (*op2 == 0) {
        ERR_MSG("Zero divided error");
        return;
    }

    // Calculate the quotient and remainder
    *dest_q = *op1 / *op2;
    *dest_r = *op1 % *op2;
}

/**
 * @brief Execute the conversion operation from an octet string to a big integer
 * 
 * @param dest pointer to the destination of the operation where the result is stored
 * @param buffer pointer to the buffer containing the octet string
 * @param bufferLen length of the buffer
 * @param sign sign of the value into the buffer that will be the sign of the big integer
 * 
 * @return TEE_SUCCESS if the conversion is successful, TEE_ERROR_OVERFLOW otherwise
 */
TEE_Result internal_TEE_BigIntConvertFromOctetString(TEE_BigInt *dest, uint8_t *buffer, size_t bufferLen, int32_t sign)
{
    *dest = 0;
    if (bufferLen > sizeof(TEE_BigInt)) {
        return TEE_ERROR_OVERFLOW;
    }

    for (size_t i = 0; i < bufferLen; i++) {
        *dest = (*dest << 8) | buffer[i];
    }

    if (sign < 0) {
        *dest = -*dest;
    }

    return TEE_SUCCESS;
}

/**
 * @brief Initialize a big integer (to 0) with a given length
 * 
 * @param bigInt pointer to the big integer
 * @param len length of the big integer
 */
void internal_TEE_BigIntInit(TEE_BigInt *bigInt, size_t len)
{
    memset(bigInt, 0, len);
}


/************************** SUPPORTING CRYPTO FUNCTIONS ********************************* */

/**
 * @brief Converts Core API algorithm types to MBEDTLS PSA API algorithm types
 * 
 * @param type CORE API algorithm types
 * 
 * @return If it is success, returns MBEDTLS PSA API algorithm types else returns 0
*/
static uint32_t get_algorithmType(uint32_t type)
{    
    switch (type)
    {
        case TEE_ALG_AES_ECB_NOPAD:     return PSA_ALG_ECB_NO_PADDING;
        case TEE_ALG_AES_CBC_NOPAD:     return PSA_ALG_CBC_NO_PADDING;
        case TEE_ALG_AES_CTR:           return PSA_ALG_CTR;
        //case TEE_ALG_AES_CTS:           return 0;
        case TEE_ALG_AES_XTS:           return PSA_ALG_XTS;
        case TEE_ALG_AES_CBC_MAC_NOPAD: return PSA_ALG_CBC_MAC;
        //case TEE_ALG_AES_CBC_MAC_PKCS5: return 0;
        case TEE_ALG_AES_CMAC:          return PSA_ALG_CMAC;
        case TEE_ALG_AES_CCM:           return PSA_ALG_CCM;
        case TEE_ALG_AES_GCM:           return PSA_ALG_GCM;

        case TEE_ALG_SHA3_256:          return PSA_ALG_SHA3_256;
        case TEE_ALG_ECDSA_SHA3_256:    return PSA_ALG_ECDSA(MBEDTLS_MD_SHA3_256);

        case TEE_ALG_SHA256:            return PSA_ALG_SHA_256;
        case TEE_ALG_HMAC_SHA256:       return PSA_ALG_HMAC(PSA_ALG_SHA_256);
        case TEE_ALG_ECDSA_SHA256:      return PSA_ALG_ECDSA(PSA_ALG_SHA_256);

        case TEE_ALG_SHA3_384:          return PSA_ALG_SHA3_384;
        case TEE_ALG_ECDSA_SHA3_384:    return PSA_ALG_ECDSA(PSA_ALG_SHA3_384);

        case TEE_ALG_SHA384:            return PSA_ALG_SHA_384;
        case TEE_ALG_HMAC_SHA384:       return PSA_ALG_HMAC(PSA_ALG_SHA_384);
        case TEE_ALG_ECDSA_SHA384:      return PSA_ALG_ECDSA(PSA_ALG_SHA_384);

        case TEE_ALG_SHA3_512:          return PSA_ALG_SHA3_512;
        case TEE_ALG_ECDSA_SHA3_512:    return PSA_ALG_ECDSA(PSA_ALG_SHA3_512);

        case TEE_ALG_SHA512:            return PSA_ALG_SHA_512;
        case TEE_ALG_HMAC_SHA512:       return PSA_ALG_HMAC(PSA_ALG_SHA_512);
        case TEE_ALG_ECDSA_SHA512:      return PSA_ALG_ECDSA(PSA_ALG_SHA_512);

        default:                        return 0;
    }
}

/**
 * @brief Converts Core API algorithm types to MBEDTLS ECDSA md algorithm types
 * 
 * @param type CORE API algorithm types
 * 
 * @warning This function must use for just asymmetric signature and verification
 * 
 * @return If it is success, returns MBEDTLS PSA API algorithm types else returns 0
*/
static uint32_t get_mdType(uint32_t alg)
{
    switch(alg)
    {
        case TEE_ALG_ECDSA_P256:
        case TEE_ALG_SHA256:            return MBEDTLS_MD_SHA256;
        case TEE_ALG_ECDSA_P384:
        case TEE_ALG_SHA384:            return MBEDTLS_MD_SHA384;
        case TEE_ALG_ECDSA_P521:
        case TEE_ALG_SHA512:            return MBEDTLS_MD_SHA512;
        case TEE_ALG_SHA3_256:          return MBEDTLS_MD_SHA3_256;
        case TEE_ALG_SHA3_384:          return MBEDTLS_MD_SHA3_384;
        case TEE_ALG_SHA3_512:          return MBEDTLS_MD_SHA3_512;

        default:                        return 0;
    }
}

/**
 * @brief Converts TEE Core API ECC (Elliptic Curve Crypto) into to MBEDTLS ECC 
 * 
 * @param alg TEE Core API ECC type
 * 
 * @return If it is success, returns MBEDTLS ECC else returns 0
*/
static uint32_t get_eccAlgorithm(uint32_t alg)
{
    switch (alg)
    {
        case TEE_ECC_CURVE_NIST_P192:  return MBEDTLS_ECP_DP_SECP192R1;
        case TEE_ECC_CURVE_NIST_P224:  return MBEDTLS_ECP_DP_SECP224R1;
        case TEE_ECC_CURVE_NIST_P256:  return MBEDTLS_ECP_DP_SECP256R1;
        case TEE_ECC_CURVE_NIST_P384:  return MBEDTLS_ECP_DP_SECP384R1;
        case TEE_ECC_CURVE_NIST_P521:  return MBEDTLS_ECP_DP_SECP521R1;
        case TEE_ECC_CURVE_BSI_P256r1: return MBEDTLS_ECP_DP_BP256R1;
        case TEE_ECC_CURVE_BSI_P384r1: return MBEDTLS_ECP_DP_BP384R1;
        case TEE_ECC_CURVE_BSI_P512r1: return MBEDTLS_ECP_DP_BP512R1;
        default: return 0;
    }
}

/**
 * @brief Generate a key pair for the given ECC algorithm
 * 
 * @param op pointer to the operation handle, were the context is stored
 * @param key pointer to the object handle, were attributes are stored and were the key will be stored
 * 
 * @return TEE_SUCCESS if the key pair is generated successfully, TEE_FAILED otherwise
*/
static int generate_ecdsaKeyPair(__TEE_OperationHandle *op, __TEE_ObjectHandle *key)
{
    // Initialize neccessary things for set x and y coordinate and generate key pair for eliptic curve
    mbedtls_ecdsa_init(&op->ctx_sign);
    mbedtls_ecdsa_init(&op->ctx_verify);
    mbedtls_ecp_point_init(&op->Q);
    mbedtls_entropy_init(&op->entropy);
    mbedtls_ctr_drbg_init(&op->ctr_drbg);

    // Convert TEE algorithm type to MBED-TLS ECP algorithm type for eliptic curve
    uint32_t alg = get_eccAlgorithm(key->attrs[3].content.value.a);

    // The attributes contains the value of X and Y coordinates of the public key used for key generation of the private key
    int ret = mbedtls_ctr_drbg_seed(&op->ctr_drbg, mbedtls_entropy_func, &op->entropy, NULL, 0);
    if(ret != 0){
        ERR_MSG("Failed mbedtls_ctr_drbg_seed: -0x%04x\n", -ret);
        goto end;
    }

    ret = mbedtls_ecp_group_load(&op->ctx_sign.private_grp, alg);
    if(ret != 0){
        ERR_MSG("Failed mbedtls_ecp_group_load: -0x%04x\n", ret);
        goto end;
    }

    ret = mbedtls_mpi_read_binary(&op->ctx_sign.private_d, (const unsigned char*)key->attrs[0].content.ref.buffer, 
                                        key->attrs[0].content.ref.length); // 32 bytes for SECP256R1
    if(ret != 0){
        ERR_MSG("mbedtls_mpi_read_binary failed for private key\n");
        goto end;
    }
    
    ret = mbedtls_mpi_read_binary(&op->ctx_sign.private_Q.private_X, (const unsigned char*)key->attrs[1].content.ref.buffer, 
                                    key->attrs[1].content.ref.length);
    if(ret != 0){
        ERR_MSG("mbedtls_mpi_read_binary failed for private key\n");
        goto end;
    }

    ret = mbedtls_mpi_read_binary(&op->ctx_sign.private_Q.private_Y, (const unsigned char*)key->attrs[2].content.ref.buffer, 
                                    key->attrs[2].content.ref.length);
    if(ret != 0){
        ERR_MSG("mbedtls_mpi_read_binary failed for private key\n");
        goto end;
    }
    ret = mbedtls_ecdsa_genkey(&op->ctx_sign, alg, mbedtls_ctr_drbg_random, &op->ctr_drbg);
    if(ret != 0){
        ERR_MSG(" failed\n  ! mbedtls_ecdsa_genkey returned %d\n", ret);
        goto end;
    }

    mbedtls_ecp_group_id grp_id = mbedtls_ecp_keypair_get_group_id(&op->ctx_sign);

    ret = mbedtls_ecp_export(&op->ctx_sign, NULL, NULL, &op->Q);
    if(ret != 0){
        ERR_MSG(" failed\n  ! mbedtls_ecp_export returned %d\n", ret);
        goto end;
    }

    ret = mbedtls_ecp_set_public_key(grp_id, &op->ctx_verify, &op->Q);
    if(ret != 0){
        ERR_MSG(" failed\n  ! mbedtls_ecp_set_public_key returned %d\n", ret);
        goto end;
    }
    
    return TEE_SUCCESS;
end:
    mbedtls_ecdsa_free(&op->ctx_sign);
    mbedtls_ecdsa_free(&op->ctx_verify);
    mbedtls_ecp_point_free(&op->Q);
    mbedtls_ctr_drbg_free(&op->ctr_drbg);
    mbedtls_entropy_free(&op->entropy);

    return TEE_FAILED;
}

/**
 * @brief Converts TEE Core API mode to MBEDTLS PSA API key usage type
 * 
 * @param mode TEE Core API mode
 * 
 * @return If it is success, MBEDTLS PSA API key usage type else returns 0
*/
static uint32_t get_modeType(uint32_t mode)
{
    switch (mode)
    {
        case TEE_MODE_ENCRYPT:  return PSA_KEY_USAGE_ENCRYPT;
        case TEE_MODE_DECRYPT:  return PSA_KEY_USAGE_DECRYPT;
        case TEE_MODE_SIGN:     return PSA_KEY_USAGE_SIGN_HASH | PSA_KEY_USAGE_VERIFY_HASH;
        case TEE_MODE_VERIFY:   return PSA_KEY_USAGE_VERIFY_HASH | PSA_KEY_USAGE_SIGN_HASH;
        case TEE_MODE_MAC:      return PSA_KEY_USAGE_SIGN_MESSAGE | PSA_KEY_USAGE_VERIFY_MESSAGE;
        case TEE_MODE_DIGEST:   return 0;
        default:                return 0;
    }
}


/**
 * @brief Converts TEE Core API algorithm to MBEDTLS PSA API key type
 * 
 * @param alg TEE Core API crypto algorithm
 * 
 * @return If it is success, MBEDTLS PSA API key type else PSA_KEY_USAGE_VERIFY_MESSAGE
*/
static uint32_t convert_alg2KeyType(uint32_t alg)
{
    switch (alg)
    {   
        case TEE_ALG_ECDSA_SHA256:  
        case TEE_ALG_ECDSA_SHA384: 
        case TEE_ALG_ECDSA_SHA512:
        case TEE_ALG_ECDSA_SHA3_256:
        case TEE_ALG_ECDSA_SHA3_384:
        case TEE_ALG_ECDSA_SHA3_512:  return PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_FAMILY_SECP_R1);
        
        default: return PSA_KEY_USAGE_VERIFY_MESSAGE;
    }
}

/**
 * @brief Converts TEE Core API mode to MBEDTLS PSA API key type
 * 
 * @param mode TEE Core API mode
 * @param alg TEE Core API crypto algorithm
 * 
 * 
 * @return If it is success, MBEDTLS PSA API key type else returns 0
*/
static uint32_t get_keyType(uint32_t mode, uint32_t alg)
{
    switch (mode)
    {
        case TEE_MODE_ENCRYPT:  
        case TEE_MODE_DECRYPT:  return PSA_KEY_TYPE_AES;
        case TEE_MODE_SIGN:     return convert_alg2KeyType(alg);
        case TEE_MODE_VERIFY:   return PSA_KEY_USAGE_VERIFY_MESSAGE;
        case TEE_MODE_MAC:      return PSA_KEY_TYPE_HMAC;
        case TEE_MODE_DIGEST:   return 0;
        default:                return 0; 
    }
}

/**
 * @brief Returns key len in bytes according to the given TEE CORE API crpyto algorithm type
 * 
 * @param objectType TEE Core API crypto algorithm
 * 
 * @return if it's success, returns key len as a byte else 0
*/

static uint32_t get_keySize(uint32_t objectType)
{
    switch(objectType)
    {
        case TEE_ALG_AES_ECB_NOPAD:     
        case TEE_ALG_AES_CBC_NOPAD:     
        case TEE_ALG_AES_CTR:           
        //case TEE_ALG_AES_CTS:           
        case TEE_ALG_AES_XTS:           
        case TEE_ALG_AES_CBC_MAC_NOPAD: 
        //case TEE_ALG_AES_CBC_MAC_PKCS5: 
        case TEE_ALG_AES_CMAC:           
        case TEE_ALG_AES_CCM:           
        case TEE_ALG_AES_GCM:           return 32;

        case TEE_ALG_SHA3_256:          
        case TEE_ALG_ECDSA_SHA3_256:    
        case TEE_ALG_SHA256:
        case TEE_ALG_HMAC_SHA256:
        case TEE_ALG_ECDSA_SHA256:      return 32;

        case TEE_ALG_SHA3_384:       
        case TEE_ALG_ECDSA_SHA3_384:  
        case TEE_ALG_SHA384:
        case TEE_ALG_HMAC_SHA384:
        case TEE_ALG_ECDSA_SHA384:      return 48;

        case TEE_ALG_SHA3_512:          
        case TEE_ALG_ECDSA_SHA3_512:    
        case TEE_ALG_SHA512:
        case TEE_ALG_HMAC_SHA512:
        case TEE_ALG_ECDSA_SHA512:      return 64;
        
        default:
            return 0;
    }
}

/**
 * @brief Check if the expected key len in bytes, according to the given TEE CORE API crypto algorithm type,
 *  matches the given key len
 * 
 * @param alg TEE Core API crypto algorithm
 * @param key_len key length in bytes to check
 * 
 * @return if it's success, returns 0 else -1
*/
static int8_t check_keySize(uint32_t alg, uint32_t key_len)
{
    uint32_t len = 8 * get_keySize(alg);

    if(key_len != len){
        return -1;
    }

    return 0;
}

/**
 * @brief Allocates the psa cipher operation struct (of MBEDTLS) and sets the default init settings
 * 
 * @return In case of success, it returns psa_cipher_operation_t struct else NULL
*/
static psa_cipher_operation_t* cipher_operationInit(void)
{
    psa_cipher_operation_t* cipher_op = (psa_cipher_operation_t*)calloc(1, sizeof(psa_cipher_operation_t));
    if(!cipher_op){
        return NULL;
    }

    cipher_op->private_default_iv_length = 0;
    cipher_op->private_id = 0;
    cipher_op->private_iv_required = 0;
    cipher_op->private_iv_set = 0;

    return cipher_op;
}

/**
 * @brief This function release the memory allocated by psa_cipher_operation_t struct
*/
static void cipher_operationDeinit(psa_cipher_operation_t* cipher_op)
{
    if(!cipher_op)
        free(cipher_op);
}

/**
 * @brief Allocates the psa hash operation struct and sets the default init settings
 * 
 * @return If it's succes, it returns psa_hash_operation_t struct else NULL
*/
static psa_hash_operation_t* hash_operationInit(uint32_t alg)
{
    psa_hash_operation_t* hash_op = (psa_hash_operation_t*)calloc(1, sizeof(psa_hash_operation_t));
    if(!hash_op)
        return NULL;

    hash_op->private_id = 0;
    if(psa_hash_setup(hash_op, alg) != 0){
        free(hash_op);
        hash_op = NULL;
    }

    return hash_op;
}

/**
 * @brief This function release the memory allocated for the psa_hash_operation_t struct
*/
static void hash_operationDeInit(psa_hash_operation_t* hash_op)
{
    if(hash_op)
        free(hash_op);
}

/**
 * @brief Allocates the psa mac operation struct and sets the default init settings
 * 
 * @return If it's succes, it returns psa_mac_operation_t struct else NULL
*/
static psa_mac_operation_t* mac_operationInit(void)
{
    psa_mac_operation_t *mac_op = (psa_mac_operation_t*)calloc(1, sizeof(psa_mac_operation_t));
    if(!mac_op)
        return NULL;

    mac_op->private_id = 0;
    mac_op->private_is_sign = 0;
    mac_op->private_mac_size = 0;  

    return mac_op;
}

/**
 * @brief This function release the memory allocated for the psa_mac_operation_t struct
*/
static void mac_operationDeInit(psa_mac_operation_t* mac_op)
{
    if(mac_op)
        free(mac_op);
}


/**
 * @brief Initializes the correct PSA API CRYPTO structures based on the given mode and algorithm
 *
 * @param op    TEE operation Handle that holds the relevant parameter for crypto opeartions
 * @param mode  Crypto operations type (e.g., Encrpyt, Decrpyt, Sign, Verify etc.)
 * @param alg   Crypto operation algorithm
 *  
 * @return 0 if the operation is initialized successfully, -1 otherwise
*/
static int mbed_operationsInit(__TEE_OperationHandle *op, uint32_t mode, uint32_t alg)
{
    switch (mode)
    {
        // Symmetric Cipher Functions
        case TEE_MODE_ENCRYPT:  
        case TEE_MODE_DECRYPT:
            op->cipher_op = cipher_operationInit();
            if(!op->cipher_op)
                return -1;
            break;

        // Asymmetric Functios 
        case TEE_MODE_SIGN:    
        case TEE_MODE_VERIFY:  return 0;

        // MAC Functions   
        case TEE_MODE_MAC:
            op->mac_op = mac_operationInit();
            if(!op->mac_op)
                return -1;
            break;

        // Message Digest(HASH) Functions
        case TEE_MODE_DIGEST:
            // If there is no key set for signinf and verification of the proccess, we need to initalize PSA API
            if(psa_crypto_init() != 0)
                return -1;   
            op->hash_op = hash_operationInit(alg);
            if(!op->hash_op)
                return -1;
            break;

        default:
            ERR_MSG("Invalid operation mod");
            return -1;    
    }

    return 0;
}

/**
 * @brief Deinitialize PSA API Crpyto operations based on the given mode and algorithm
 * 
 * @param op    TEE operation Handle that holds the relevant parameters for crypto opeartions
 * @param mode  Crypto operations type (e.g., Encrpyt, Decrpyt, Sign, Verify etc.)
 * 
*/
static void mbed_operationsDeInit(__TEE_OperationHandle *op, uint32_t mode)
{
    switch (mode)
    {
        //   Symmetric Cipher Functions
        case TEE_MODE_ENCRYPT:  
        case TEE_MODE_DECRYPT: cipher_operationDeinit(op->cipher_op); break;
        //   Asymmetric Functios 
        /*case TEE_MODE_SIGN:     
        case TEE_MODE_VERIFY:   return NULL;*/
        //   MAC Functions   
        case TEE_MODE_MAC:      mac_operationDeInit(op->mac_op);  break;
        //  Message Digest(HASH) Functions
        case TEE_MODE_DIGEST:   hash_operationDeInit(op->hash_op); break;
        default:
            ERR_MSG("Invalid operation mod");
            return;    
    }
}


/************************** TEE OPERATIONS FUNCTIONS ********************************* */

/**
 * @brief Allocates a new operation handle for the given algorithm, mode, and maximum key size
 * 
 * @param operation pointer to the operation handle
 * @param algorithm algorithm type (e.g., AES, SHA, ECDSA etc.)
 * @param mode mode type (e.g., Encrypt, Decrypt, Sign, Verify etc.)
 * @param maxKeySize maximum key size
 * 
 * @return TEE_SUCCESS if the operation is allocated successfully, TEE_FAILED otherwise
 */
TEE_Result internal_TEE_AllocateOperation(TEE_OperationHandle* operation,           
                                    uint32_t algorithm,
                                    uint32_t mode, 
                                    uint32_t maxKeySize) 
{
    __TEE_OperationHandle *temp_op = (__TEE_OperationHandle*)malloc(sizeof(__TEE_OperationHandle));
    if(!temp_op){
        ERR_MSG("Allocate operation failed");
        return TEE_FAILED;
    }

    // Intialize the PSA Crypto API
    if(psa_crypto_init() != PSA_SUCCESS){
        ERR_MSG("PSA  cryto init failed");
        free(temp_op);
        return TEE_FAILED;
    }

    // Convert TEE crytpo algortihm to PSA API crypto algorithm
    uint32_t alg = get_algorithmType(algorithm);

    // Initialize relavent mode for psa crytpo api (like encryption, signature, mac etc.)
    if(mbed_operationsInit(temp_op, mode, alg) != 0)
    {
        ERR_MSG("MOD initializing err");
        free(temp_op);
        return TEE_FAILED;
    }

    temp_op->info.algorithm = algorithm;
    temp_op->info.mode = mode;
    temp_op->info.keySize = maxKeySize;
    temp_op->key_id = 0;

    *operation = (void*)temp_op;

    return TEE_SUCCESS;
}

/**
 * @brief Free the operation handle and release the allocated memory
 * 
 * @param operation pointer to the operation handle
 */
void internal_TEE_FreeOperation(TEE_OperationHandle operation) 
{
    if(operation)
    {
        __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;

        // Asymmetric signing and verification proccess might not use the PSA API,
        // if you want to set x and y values for eliptic curve for signature and verification. 
        // The if statement is used to check if the key_id is set or not, which allows us to understand
        // which PSA API was used for the operation and which elements should be freed.
        if((op->key_id != 0) || (op->info.mode == TEE_MODE_DIGEST))
        {
            mbed_operationsDeInit(op, op->info.mode);
            if(op->key_id != 0) 
                psa_destroy_key(op->key_id);
            
            mbedtls_psa_crypto_free();
        }else{
            mbedtls_ecdsa_free(&op->ctx_sign);
            mbedtls_ecdsa_free(&op->ctx_verify);
            mbedtls_ecp_point_free(&op->Q);
            mbedtls_ctr_drbg_free(&op->ctr_drbg);
            mbedtls_entropy_free(&op->entropy);
        }       

        // Free the operation handle
        free(op); 
    }            
}

/**
 * @brief Set the key (stored in a Object) for the given operation
 * 
 * @param operation pointer to the operation handle
 * @param key pointer to the object handle that stores the key 
 * 
 * @return TEE_SUCCESS if the key is set successfully, TEE_FAILED otherwise
 */
TEE_Result internal_TEE_SetOperationKey(TEE_OperationHandle operation,              
                                        TEE_ObjectHandle key)
{
   if(!operation){
        ERR_MSG("Operation is null");
        return TEE_FAILED;
    }

    if(!key){
        ERR_MSG("Key is null");
        return TEE_FAILED;
    }

    __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;  
    __TEE_ObjectHandle *obj = (__TEE_ObjectHandle*)key;

    if(!obj->buffer){
        ERR_MSG("Key or content is null");
        return TEE_FAILED;
    }

    // Extract the attributes from the object to understand if the key should be generated or set
    int attr_flag = (obj->attrs[0].attributeID + obj->attrs[1].attributeID + 
                            obj->attrs[2].attributeID + obj->attrs[3].attributeID) > 0 ? 1 : 0;
    if((obj->obj_type == TEE_TYPE_ECDSA_KEYPAIR) && (attr_flag != 0))
    {
        // If the key is ECDSA key pair and the attributes are set, then the key should be generated
        // starting from the attributes that contain the x and y coordinates of the public key
        op->key_id = 0;
        return generate_ecdsaKeyPair(op, obj);
    }
    
    // Check if the key size (stored in the obj or generated before) is correct according to the algorithm
    if(check_keySize(op->info.algorithm, obj->key_len) != 0){
        ERR_MSG("Key size error");
        return TEE_FAILED;
    }

    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;

    uint32_t key_alg = get_algorithmType(op->info.algorithm);
    uint32_t key_flag = get_modeType(op->info.mode);
    uint32_t key_type = get_keyType(op->info.mode, op->info.algorithm);
    
    psa_set_key_algorithm(&attributes, key_alg);
    psa_set_key_usage_flags(&attributes, key_flag);
    psa_set_key_type(&attributes, key_type);
    psa_set_key_bits(&attributes, obj->key_len);

    // Import the crypto key into the PSA API of MbedTLS
    int res = psa_import_key(&attributes, (const uint8_t*)obj->buffer, obj->key_len/8, &op->key_id);
    if(res != PSA_SUCCESS)
    {
        ERR_MSG("Failed to set key:");
        return TEE_FAILED;
    }

    if(op->key_id != 0)
    {
        op->key1 = key;
    }

    return TEE_SUCCESS;
}                                


/************************** TEE KEY AND RANDOM NUMBER GENERATION FUNCTIONS ********************************* */

/**
 * @brief Generate a key (based on the parameters and key size passed) and stored it inside the object 
 * (persistently or not based on the object type)
 * 
 * @param object pointer to the object handle where the key will be stored
 * @param keySize size of the key to be generated
 * @param params pointer to the attributes used for key generation
 * @param paramCount number of attributes
 * @param ta_num number of the trusted application that identify which secure storage area the object will be stored in (if it is persistent)
 * 
 * @return TEE_SUCCESS if the key is generated successfully, TEE_FAILED otherwise
 */

TEE_Result internal_TEE_GenerateKey(TEE_ObjectHandle object,
                                    uint32_t keySize,
                  /*unused*/        TEE_Attribute* params,
                  /*unused*/        uint32_t paramCount,
                                    uint32_t ta_num)
        {
    if(!object){
        ERR_MSG("Object is null");
        return TEE_FAILED;
    }
    
    __TEE_ObjectHandle *obj = (__TEE_ObjectHandle*)object;

    char temp_buffer[keySize/8];

    // Initialize entropy to generate key
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;

    mbedtls_entropy_init(&entropy);
    mbedtls_ctr_drbg_init(&ctr_drbg);

    if (mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, NULL, 0) != 0) {
        mbedtls_ctr_drbg_free(&ctr_drbg);
        ERR_MSG("Failed to seed RNG");
        TEE_FAILED;
    }

    // Generate Key
    if (mbedtls_ctr_drbg_random(&ctr_drbg, (unsigned char*)temp_buffer, keySize/8) != 0) {
        ERR_MSG("Failed to generate random key");
        return TEE_FAILED;
    }

    // Initialize the parameters of the object
    if(paramCount != 0){
        TEE_PopulateTransientObject(object, params, paramCount);
    }
    
    // If the object is not persistent, store the key in the object buffer
    if(obj->obj_storage_type != TEE_OBJ_TYPE_PERSISTENT)
    {   
        memcpy(obj->buffer, temp_buffer, keySize/8);
    }else{

        // If the object is persistent, write the key to the secure storage area
        obj->flags = TEE_DATA_FLAG_ACCESS_WRITE;

        if(TEE_WriteObjectData(object, temp_buffer, keySize/8) != TEE_SUCCESS){
            ERR_MSG("Failed to write object data");
            mbedtls_ctr_drbg_free(&ctr_drbg);
            mbedtls_entropy_free(&entropy);
            return TEE_FAILED;
        }

        obj->flags = 0;
    }
   
    // Deinit entropy
    mbedtls_ctr_drbg_free(&ctr_drbg);
    mbedtls_entropy_free(&entropy);

    return TEE_SUCCESS;
}


/**
 * @brief Generate a random number (using hardware RNG) and store it in the buffer
 * 
 * @param randomBuffer pointer to the buffer where the random number will be stored
 * @param randomBufferLen length of the random number to be generated
 */
void internal_TEE_GenerateRandom(void* randomBuffer, size_t randomBufferLen)
{
    uint32_t rnum = 0;
    unsigned char val[4] = {0};
    size_t len = 0;
    do
    {
        rnum = trng_createNumber();
        // Remove if there is a number that bigger than 32 because it cause a problem for cjson. 
        // To do that just need to set the first msb zero, 0b01111111
        //rnum = rnum & 0x7F7F7F7F;
        memcpy(val, &rnum, 4);

        // Remove if there is a number that smaller than 32 because it cause a problem for cjson
        /*if((val[0]<32) || (val[1]<32) || (val[2]<32) || (val[3]<32))
            continue;*/

        // copy data according to offset
        if((randomBufferLen - len) < 4)
            memcpy(randomBuffer + len, &val, randomBufferLen - len);
        else
            memcpy(randomBuffer + len, &val, 4);
        
        len = len + 4;// even if offset values is smaller than 4, increase 4 to break the loop

    } while (len < randomBufferLen);
}

// TODO: Implement the following function if needed
void internal_TEE_DeriveKey(TEE_OperationHandle operation,
                    TEE_Attribute* params, 
                    uint32_t paramCount,
                    TEE_ObjectHandle derivedKey)
{
    return;
}


/************************** TEE SYMMETRIC CIPHER FUNCTIONS ********************************* */

/**
 * @brief Initializes the cipher operation for symmetric encryption/decryption given the initialization vector (IV)
 * Supported algorithms: AES ECB, AES CBC, AES CTR, AES XTS, AES CBC MAC, AES CMAC, AES CCM, AES GCM
 * 
 * @param operation pointer to the operation handle
 * @param IV pointer to the initialization vector
 * @param IVLen length of the initialization vector
 */
void internal_TEE_CipherInit(TEE_OperationHandle operation,
                        void* IV, 
                        size_t IVLen)
{
    if(!operation){
        ERR_MSG("Operation is null");    
    }

    __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;

    if(op->key_id == 0){
        ERR_MSG("Key ID is not set");
        goto end;
    }

    if((!IV) || (IVLen <= 0)){
        ERR_MSG("IV is null or IV length is zero");
        goto end;
    }

    // Initialize the cipher operation of the PSA API
    op->cipher_op = cipher_operationInit();
    uint32_t algorithm = get_algorithmType(op->info.algorithm);

    // Setup the PSA cipher operation for encryption or decryption
    if(op->info.mode == TEE_MODE_ENCRYPT){
        if(psa_cipher_encrypt_setup((psa_cipher_operation_t*)op->cipher_op, op->key_id,
                                        algorithm) != PSA_SUCCESS)
        {
            ERR_MSG("Failed to setup cipher encrypt");
            goto end;

        }
    }else if(op->info.mode == TEE_MODE_DECRYPT){
        if(psa_cipher_decrypt_setup((psa_cipher_operation_t*)op->cipher_op, op->key_id,
                                        algorithm) != PSA_SUCCESS)
        {
            ERR_MSG("Failed to setup cipher decrypt");
            goto end;
        }
    } else {
        // Invalid mode (neither encrypt nor decrypt)
        ERR_MSG("Invalid mode in CipherInit");
        goto end;
    }

    // Set the IV for the PSA cipher operation
    if(psa_cipher_set_iv((psa_cipher_operation_t*)op->cipher_op, (const uint8_t*)IV, IVLen) != PSA_SUCCESS)
    {
        ERR_MSG("Failed to set IV");
        // Abort the cipher operation
        psa_cipher_abort((psa_cipher_operation_t*)op->cipher_op);
    }

end:
    // Do nothing
}


/**
 * @brief Updates the cipher operation by computing the cipher of the input data and storing the result in the output buffer
 * 
 * @param operation pointer to the operation handle (with the key, IV and PSA cipher operation set) 
 * @param srcData pointer to the input data 
 * @param srcLen length of the input data
 * @param destData pointer to the output data
 * @param destLen length of the output data
 * 
 * @return TEE_SUCCESS if the cipher operation is updated successfully, TEE_FAILED otherwise
 */
TEE_Result internal_TEE_CipherUpdate(TEE_OperationHandle operation,
                            /*[inbuf]*/ void* srcData, 
                                        size_t srcLen,
                            /*[outbuf]*/ void* destData, 
                                        size_t *destLen)
{
    if((!srcData) || (!destData)){
        ERR_MSG("Source data or Destination data is null");
        return TEE_FAILED;
    }

    if((srcLen <= 0) || (*destLen <= 0)){ // destLen rapresent initially the physical size of the output buffer
        ERR_MSG("Source length problem");
        return TEE_FAILED;
    }

    __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;
    if((!op) || (!op->cipher_op)) {
        ERR_MSG("Cipher operation is null");
        return TEE_FAILED;
    }

    // destLen now rapresent the logical size of the output buffer as a return parameter
    // destSize is the physical size of the output buffer
    // Both len and size are passed as a parameter to the PSA API
    size_t destSize = *destLen;
    *destLen = 0;

    // Compute the actual cipher of the input data and store the result in the output buffer
    if(psa_cipher_update((psa_cipher_operation_t*)op->cipher_op, (const uint8_t*)srcData, srcLen, 
                            destData, destSize, destLen) != PSA_SUCCESS)
    {
        ERR_MSG("Failed to update cipher");
        psa_cipher_abort((psa_cipher_operation_t*)op->cipher_op);
        return TEE_FAILED;
    }

    return TEE_SUCCESS;
}


/**
 * @brief Finalizes the cipher operation by computing the final cipher of the input data (if other data are passed)
 * and storing the result in the output buffer
 * 
 * @param operation pointer to the operation handle (with the key, IV and PSA cipher operation set)
 * @param srcData pointer to the input data
 * @param srcLen length of the input data
 * @param destData pointer to the output data
 * @param destLen length of the output data
 * 
 * @return TEE_SUCCESS if the cipher operation is finalized successfully, TEE_FAILED otherwise
 */
TEE_Result internal_TEE_CipherDoFinal(TEE_OperationHandle operation,
                            /*[inbuf]*/ void* srcData, 
                                        size_t srcLen,
                        /*[outbufopt]*/ void* destData, 
                                        size_t *destLen)
        {

    if(!destData){
        ERR_MSG("Destination data is null");
        return TEE_FAILED;
    }

    if(*destLen <= 0){
        ERR_MSG("Source or Destination length problem");
        return TEE_FAILED;
    }

    __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;
    if ((!op) || (!op->cipher_op)) {
        ERR_MSG("Cipher operation is null");
        return TEE_FAILED;
    }

    // destLen now rapresent the logical size of the output buffer as a return parameter
    // destSize is the physical size of the output buffer
    size_t destSize = *destLen;
    *destLen = 0;

    // If the input data is not empty, update the cipher operation with the input data
    if(srcData && srcLen > 0) {

        if(psa_cipher_update((psa_cipher_operation_t*)op->cipher_op, (const uint8_t*)srcData, srcLen, 
                                destData, destSize, destLen) != PSA_SUCCESS)
        {
            ERR_MSG("Failed to update cipher");
            psa_cipher_abort((psa_cipher_operation_t*)op->cipher_op);
            return TEE_FAILED;
        }
    }

    // Finalize the cipher operation and store the final cipher in the output buffer using the PSA API 
    if(psa_cipher_finish((psa_cipher_operation_t*)op->cipher_op, destData + *destLen, destSize, destLen) != PSA_SUCCESS)
    {
        ERR_MSG("Failed to finish cipher");
        psa_cipher_abort((psa_cipher_operation_t*)op->cipher_op);
        return TEE_FAILED;
    }

    return TEE_SUCCESS;
}


/************************** TEE CYPHER FUNCTIONS ********************************* */

/**
 * @brief Setup the the MAC (Message Authentication Code) operation given the initialization vector (IV)
 * Supported algorithms: HMAC SHA256, HMAC SHA384, HMAC SHA512
 * 
 * @param operation pointer to the operation handle
 * @param IV pointer to the initialization vector
 * @param IVLen length of the initialization vector
 * 
 * @note For HMAC with SHA, the IV is not used
 */
void internal_TEE_MACInit(TEE_OperationHandle operation,                             
                  void* IV, size_t IVLen) 
{
    if(!operation){
        ERR_MSG("Operation is null");
        goto end;
    }

    __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;
    __TEE_ObjectHandle *key = (__TEE_ObjectHandle*)op->key1;
    
    if(check_keySize(op->info.algorithm, key->key_len) != 0){
        ERR_MSG("The given key size is invalid");
        goto end;
    }

    uint32_t alg = get_algorithmType(op->info.algorithm);

    // Initialize the MAC operation of the PSA API 
    // For HMAC with SHA, the IV is not used
    if(psa_mac_sign_setup(op->mac_op, op->key_id, alg) != 0){
        ERR_MSG("MAC Init failed");
        psa_mac_abort(op->mac_op); 
        goto end;       
    }

end:
    // Do nothing
}


/**
 * @brief Updates the MAC operation by computing the MAC of the check given as input
 * 
 * @param operation pointer to the operation handle (with the key and PSA MAC operation set)
 * @param chunk pointer to the input data
 * @param chunkSize length of the input data
 */
void internal_TEE_MACUpdate(TEE_OperationHandle operation,
        /*[inbuf]*/ void* chunk, size_t chunkSize) 
{
    if(!operation){
        ERR_MSG("Error in MAC Update");
        goto end;
    }
    __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;
    
    // Update the MAC operation with the input data using the PSA API
    if(psa_mac_update(op->mac_op, (const uint8_t*)chunk, chunkSize) != 0){
        psa_mac_abort(op->mac_op);
        ERR_MSG("Error in MAC Update");
        goto end;
    }

end:
    // Do nothing
}                       

/**
 * @brief Finalizes the MAC operation by computing the final MAC of the input data (if needed) and storing the result in the output buffer
 * 
 * @param operation pointer to the operation handle (with the key and PSA MAC operation set)
 * @param message pointer to the input data
 * @param messageLen length of the input data
 * @param mac pointer to the output data
 * @param macLen length of the output data
 * 
 * @return TEE_SUCCESS if the MAC operation is finalized successfully, TEE_FAILED otherwise
 */
TEE_Result internal_TEE_MACComputeFinal(TEE_OperationHandle operation,
             /*[inbuf]*/        void* message, size_t messageLen,
             /*[outbuf]*/       void* mac, size_t *macLen) 
{
    if(!operation){
        ERR_MSG("Operation is null");
        return TEE_FAILED;
    }
    __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;

    // If the input data is not empty, update the MAC operation with the input data
    if(message && messageLen > 0) {
        if(psa_mac_update(op->mac_op, (const uint8_t*)message, messageLen) != 0){
            ERR_MSG("MAC Update failed");
            psa_mac_abort(op->mac_op);
            return TEE_FAILED;
        }
    }

    // Swap the physical size of the output buffer with the logical size of the output buffer
    size_t macSize = *macLen;
    *macLen = 0;

    // Finalize the MAC operation and store the final MAC in the output buffer using the PSA API
    if(psa_mac_sign_finish(op->mac_op,(uint8_t *)mac, macSize, macLen) != 0){
        psa_mac_abort(op->mac_op);
        return TEE_FAILED;
    }

    return TEE_SUCCESS;
}   


/************************** TEE DIGEST FUNCTIONS ********************************* */

/**
 * @brief Update the operation for message digest computation (hash)
 * Supported algorithms: SHA256, SHA384, SHA512, SHA3_256, SHA3_384, SHA3_512
 * 
 * @param operation pointer to the operation handle
 * @param chunk pointer to the input data to be hashed
 * @param chunkSize length of the input data
 */
void internal_TEE_DigestUpdate(TEE_OperationHandle operation,
        /*inbuf]*/     void* chunk, size_t chunkSize) 
{
    if(!operation){
        ERR_MSG("NULL parameter");
        goto end;
    }

    if((!chunk) || (chunkSize <= 0)){
        ERR_MSG("Invalid parameter");
        goto end;
    }

    __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;

    // Update the hash operation with the input data using the PSA API
    if(psa_hash_update(op->hash_op,(const uint8_t*) chunk, chunkSize) != 0)
        ERR_MSG("HASH Updated process is failed");
        
end:
    // Do nothing
}


/**
 * @brief Finalizes the hash operation by computing the final hash of the input data (if needed) 
 * and storing the result in the output buffer
 * 
 * @param operation pointer to the operation handle (with the PSA hash operation set)
 * @param chunk pointer to the input data
 * @param chunkLen length of the input data
 * @param hash pointer to the output data
 * @param hashLen length of the output data
 */
TEE_Result internal_TEE_DigestDoFinal(TEE_OperationHandle operation,
            /*[inbuf]*/      void* chunk, size_t chunkLen,
            /*[outbuf]*/     void* hash, size_t *hashLen) 
{
    if(!operation){
        ERR_MSG("Null operation");
        return TEE_FAILED;
    }

    if(!hash){
        ERR_MSG("Null input or output parameter");
        return TEE_FAILED;
    }

    __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;

    // In order to call TEE_DigestDoFinal function multiple time by sequentially, the process should not be ended
    // After calling psa_hash_finish function, operation id param is set to 0 and it prevents to use other hash functions 
    // Hence, we need to clone the hash operation and finalize it or re-call psa_hash_setup function  
    psa_hash_operation_t target = PSA_HASH_OPERATION_INIT;
    if(psa_hash_clone(op->hash_op, &target) != 0){
        ERR_MSG("Digest extraction is failed");
        return TEE_FAILED;
    }

    // If the input data is not empty, update the hash operation with the input data
    if(chunk && chunkLen > 0) {
        psa_status_t err = psa_hash_update(&target, (const uint8_t*) chunk, chunkLen);
        if(err != 0){
            ERR_MSG("Digest finalize failed");
            return TEE_FAILED;
        }
    } 
    
    // Swap the physical size of the output buffer with the logical size of the output buffer
    size_t hashSize = *hashLen;
    *hashLen = 0;

    // Finalize the hash operation and store the final hash in the output buffer using the PSA API
    if(psa_hash_finish(&target, hash, hashSize, hashLen) != 0){
        ERR_MSG("Digest finalize failed");
        psa_hash_abort(&target);
        return TEE_FAILED;
    }

    return TEE_SUCCESS;
}


/**
 * @brief Extract the hash value from the hash operation and store it in the output buffer
 * 
 * @param operation pointer to the operation handle (with the PSA hash operation set)
 * @param hash pointer to the output data
 * @param hashLen length of the output data
 */
TEE_Result internal_TEE_DigestExtract(TEE_OperationHandle operation,
            /*[outbuf]*/       void* hash, size_t *hashLen) 
{
    if(!operation){
        ERR_MSG("Null operation");
        return TEE_FAILED;
    }

    if((!hash) || (*hashLen <= 0)){
        ERR_MSG("Null input parameter");
        return TEE_FAILED;
    }

    __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;
    
    // PSA HASH doesn't support extraction of hash value which is still going on, for this reason
    // we clone the operation and finalized it to extract the digests
    // Using this trick we will not affect the original hash operation
    psa_hash_operation_t target = PSA_HASH_OPERATION_INIT;
    if(psa_hash_clone(op->hash_op, &target) != 0){
        ERR_MSG("Digest extraction failed");
        return TEE_FAILED;
    }

    // Swap the physical size of the output buffer with the logical size of the output buffer
    size_t hashSize = *hashLen;
    *hashLen = 0;

    // Finalize the clone of the hash operation and to be able to store it in the output buffe
    if(psa_hash_finish(&target, hash, hashSize, hashLen) != 0){
        ERR_MSG("Digest extraction failed");
        psa_hash_abort(&target);
        return TEE_FAILED;
    }

    return TEE_SUCCESS;
}


/************************** TEE ASYMMETRIC SIGNATURE FUNCTIONS ********************************* */

/**
 * @brief Initializes the asymmetric signature operation for signing a message given its hash 
 * 
 * @param operation pointer to the operation handle
 * @param params pointer to the attributes used for the signature operation
 * @param paramCount number of attributes
 * @param digest pointer to the input data (hash) to be signed
 * @param digestLen length of the input data
 * @param signature pointer to the output data (signature)
 * @param signatureLen length of the output data
 * 
 */
TEE_Result internal_TEE_AsymmetricSignDigest(TEE_OperationHandle operation,
                    /*[in]*/         TEE_Attribute* params, uint32_t paramCount,
                    /*[inbuf]*/      void* digest, size_t digestLen,
                    /*[outbuf]*/     void* signature, size_t *signatureLen)
{
    if(!operation){
        ERR_MSG("Operation is null");
        return TEE_FAILED;
    }

    if((!digest) || (!signature)){
        ERR_MSG("Digest or Signature is null");
        return TEE_FAILED;
    }

    if((digestLen <= 0) || (*signatureLen <= 0)){
        ERR_MSG("Digest or Signature length is zero");
        return TEE_FAILED;
    }

    __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;

    uint32_t alg = 0;
    // If the key is set, use the PSA API with internal generation of X and Y params for signing the hash
    // (key_id is set in the operation in this case)
    // Otherwise, use the MbedTLS API with custom X and Y params for signing the hash
    if(op->key_id != 0)
    {
        alg = get_algorithmType(op->info.algorithm);
        // Use the PSA API to sign the hash
        psa_status_t status = psa_sign_hash(op->key_id, alg, (const uint8_t*)digest, digestLen, 
                                                (uint8_t*)signature, *signatureLen, signatureLen);
        if(status != PSA_SUCCESS) {
            ERR_MSG("Failed psa_sign_hash");
            return TEE_FAILED;
        }

    }else{
        alg = get_mdType(op->info.algorithm);
        // Use the MbedTLS API to sign the hash
        int ret = mbedtls_ecdsa_write_signature(&op->ctx_sign , alg, digest, digestLen, signature, *signatureLen, signatureLen, 
                                                mbedtls_ctr_drbg_random, &op->ctr_drbg);
        if(ret != 0)
        {
            ERR_MSG("Failed mbedtls_ecdsa_write_signature: -0x%04x\n", -ret);
            return TEE_FAILED;
        }
    }

    return TEE_SUCCESS;
}

/**
 * @brief Initializes the asymmetric verification operation for verifying the signatura of given message hash
 * 
 * @param operation pointer to the operation handle
 * @param params pointer to the attributes used for the verification operation
 * @param paramCount number of attributes
 * @param digest pointer to the input data (hash) to be verified
 * @param digestLen length of the input data
 * @param signature pointer to the input data (signature) to be verified
 * @param signatureLen length of the input data
 * 
 * @return TEE_SUCCESS if the signature is verified successfully, TEE_FAILED otherwise (invalid signature or errors) 
 */
TEE_Result internal_TEE_AsymmetricVerifyDigest(TEE_OperationHandle operation, 
                    /*[in] */ TEE_Attribute* params, uint32_t paramCount,
                    /*[inbuf]*/ void* digest, size_t digestLen,
                    /*[inbuf]*/ void* signature, size_t signatureLen) 
{
     if(!operation){
        ERR_MSG("Operation is null");
        return TEE_FAILED;
    }

    if(!digest){
        ERR_MSG("Digest is null");
        return TEE_FAILED;
    }

    if((digestLen <= 0) || (signatureLen <= 0)){
        ERR_MSG("Digest or Signature length is zero");
        return TEE_FAILED;
    }

    __TEE_OperationHandle *op = (__TEE_OperationHandle*)operation;

    // If the key is set, use the PSA API with internal generation of X and Y params for signing the hash
    // (key_id is set in the operation in this case)
    // Otherwise, use the MbedTLS API with custom X and Y params for signing the hash
    if(op->key_id != 0)
    {
        // Use the PSA API to verify the hash
        uint32_t alg = get_algorithmType(op->info.algorithm);
        psa_status_t status = psa_verify_hash(op->key_id, alg, (const uint8_t*)digest, digestLen, 
                                                (uint8_t*)signature, signatureLen);
        if (status != PSA_SUCCESS) {
            ERR_MSG("Verification of the signture failed");
            return TEE_FAILED;
        }
    }else{
        // Use the MbedTLS API to verify the hash
        int ret = mbedtls_ecdsa_read_signature(&op->ctx_verify, digest, digestLen, signature, signatureLen);
        if (ret != 0) {
            ERR_MSG("Failed mbedtls_ecdsa_read_signature: -0x%04x\n", -ret);
            ERR_MSG("Verification of the signture failed");
            return TEE_FAILED;
        }
    }

    return TEE_SUCCESS;
}
