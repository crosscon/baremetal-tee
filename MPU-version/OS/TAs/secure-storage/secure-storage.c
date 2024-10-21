#include <string.h>
#include <stdlib.h>

// Include the TEE API header files
#include "tee_client_api.h"
#include "tee_core_api.h"

#include "include/secure-storage.h"

#define PERSISTENT_OBJ_ID    5

int ta_test_createPersistenObject(void)
{
    TEE_ObjectHandle obj;
    uint32_t flag = TEE_DATA_FLAG_ACCESS_READ | TEE_DATA_FLAG_ACCESS_WRITE;
    char key[128] = {0};
    int ret = -1;
    int obj_id = PERSISTENT_OBJ_ID;

    TEE_GenerateRandom(key, sizeof(key));

    ret = TEE_CreatePersistentObject(TEE_STORAGE_PRIVATE, (void*)&obj_id, sizeof(int), flag, NULL, key, sizeof(key), &obj);
    if(ret != TEE_SUCCESS){
        ERR_MSG("Create persistent object failed");
        return -1;
    } else {
        IMSG("Secure persistent object is created with id %d and content '%s'", obj_id, key);
    }

    TEE_CloseObject(obj);

    return ret;
}

int ta_test_readPersistenObject(void)
{
    TEE_ObjectHandle obj;
    char buffer[128] = {0};
    size_t count = 0;
    int ret = -1;
    int obj_id = PERSISTENT_OBJ_ID;

    ret = TEE_OpenPersistentObject(TEE_STORAGE_PRIVATE, (void*)&obj_id, sizeof(int), TEE_DATA_FLAG_ACCESS_READ, &obj);
    if(ret != TEE_SUCCESS){
        ERR_MSG("Open persistent object failed");
        IMSG("The object with id %d does not exist", obj_id);
        return -1;
    }

    ret = TEE_ReadObjectData(obj, buffer, sizeof(buffer), &count);
    if(ret != TEE_SUCCESS){
        ERR_MSG("Reading object failed");
        return -1;
    } else {
        IMSG("Secure persistent object with id %d has '%s' as content", obj_id, buffer);
    }

    TEE_CloseObject(obj);

    return ret; 
}

int ta_test_updatePersistenObject(void)
{
    TEE_ObjectHandle obj;
    char buffer[128] = "Testing the updating functions of the persistent object\0";
    int ret = -1;
    int obj_id = PERSISTENT_OBJ_ID;

    ret = TEE_OpenPersistentObject(TEE_STORAGE_PRIVATE, (void*)&obj_id, sizeof(int), TEE_DATA_FLAG_ACCESS_WRITE, &obj);
    if(ret != TEE_SUCCESS){
        ERR_MSG("Open persistent object is failed");
        return -1;
    }

    ret = TEE_WriteObjectData(obj, buffer, sizeof(buffer));
    if(ret != TEE_SUCCESS){
        ERR_MSG("Open persistent object failed");
        IMSG("The object with id %d already exists and can not be overwritten", obj_id);
        return -1;
    } 

    TEE_CloseObject(obj);

    return ret; 
}

int ta_test_deletePersistentObject(void)
{
    TEE_ObjectHandle obj;
    int ret = -1;   
    int obj_id = PERSISTENT_OBJ_ID;

    ret = TEE_OpenPersistentObject(TEE_STORAGE_PRIVATE, (void*)&obj_id, sizeof(int), TEE_DATA_FLAG_ACCESS_READ, &obj);
    if(ret != TEE_SUCCESS){
        ERR_MSG("Open persistent object failed");
        return -1;
    }

    ret = TEE_CloseAndDeletePersistentObject1(obj);
    if(ret != TEE_SUCCESS){
        ERR_MSG("Deleting object failed");
        return -1;
    } else {
        IMSG("Secure persistent object with id %d is deleted", obj_id);
    }

    return ret;
}

TEE_Result  TA_CreateEntryPoint(void)
{
    DMSG("Entry point is created");
    
    return TEE_SUCCESS;
}


void TA_DestroyEntryPoint(void)
{
    DMSG("Entry point is destroyed");
}


TEE_Result TA_OpenSessionEntryPoint(uint32_t paramTypes,
									TEE_Param params[4],
									void** sessionContext)
{
    
    DMSG("Session is opened");
    return TEE_SUCCESS;
}


void  TA_CloseSessionEntryPoint(void* sessionContext)
{
    DMSG("Session is closed");    
} 


TEE_Result TA_InvokeCommandEntryPoint(void* sessionContext,
                                            uint32_t commandID,
                                            uint32_t paramTypes,
                                            TEE_Param params[4])
{
    int ret = TEE_SUCCESS;
     
    switch (commandID)
    {
        case TA_COMMAND_READ:         ret = ta_test_readPersistenObject();    break;
        case TA_COMMAND_CREATE:       ret = ta_test_createPersistenObject();  break;
        case TA_COMMAND_DELETE:       ret = ta_test_deletePersistentObject(); break;
        case TA_COMMAND_WRITE:        ret = ta_test_updatePersistenObject();  break;
        default: ERR_MSG("Command id not recognized"); ret = TEE_FAILED;      break;
    }

	return ret;
}
