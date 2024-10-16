#ifndef __TRUSTED_APP__
#define __TRUSTED_APP__

#include <stdint.h>
#include "tee_common.h"


/* 
* Interface that each TA should implement in order to allow communication with the CA 
* using the GlobalPlatform client API
*
* Flow of execution:
* 1. TA_CreateEntryPoint
* 2. TA_OpenSessionEntryPoint
* 3. TA_InvokeCommandEntryPoint (multiple times)
* 4. TA_CloseSessionEntryPoint
* 5. TA_DestroyEntryPoint
*/

TEE_Result TA_CreateEntryPoint(void);

void TA_DestroyEntryPoint(void);

TEE_Result TA_OpenSessionEntryPoint(uint32_t param_types, 
                                    TEE_Param params[4], 
                                    void **sessionContext);

void TA_CloseSessionEntryPoint(void* sessionContext);

TEE_Result TA_InvokeCommandEntryPoint(void* sessionContext,
                                    uint32_t commandID,
                                    uint32_t paramTypes,
                                    TEE_Param params[4]);

#endif