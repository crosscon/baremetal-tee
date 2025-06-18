#ifndef __IT_H
#define __IT_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "tee_common.h"
/* Functions to handle the exceptions caused by the instrumented code (SVC, HardFault, MemMenage)*/
/* The SVC handler is used mainly for two execution flows:
*  - An client/unsecure application wants to comunicate with a trusted application (using TEEC_OpenSession, TEEC_InvokeCommand, etc.)
*  - A trusted application wants to call a core service offered by the TEE (TEE_CreatePersistentObject, TEE_CipherInit, etc.)
*/
void Microvisor_HardFault_Handler();
void Microvisor_SVC_Handler();
void Microvisor_MemManage_Handler();
void Microvisor_PendSV_Handler();

extern TEE_Result TA_CreateEntryPoint1(void);
extern void TA_DestroyEntryPoint1(void);
extern TEE_Result TA_CreateEntryPoint2(void);
extern void TA_DestroyEntryPoint2(void);
extern TEE_Result TA_OpenSessionEntryPoint1(uint32_t param_types, TEE_Param params[4], void **sessionContext);
extern TEE_Result TA_OpenSessionEntryPoint2(uint32_t param_types, TEE_Param params[4], void **sessionContext);
extern void TA_CloseSessionEntryPoint1(void* sessionContext);
extern void TA_CloseSessionEntryPoint2(void* sessionContext);
extern TEE_Result TA_InvokeCommandEntryPoint1(void* sessionContext, uint32_t commandID, uint32_t paramTypes, TEE_Param params[4]);
extern TEE_Result TA_InvokeCommandEntryPoint2(void* sessionContext, uint32_t commandID, uint32_t paramTypes, TEE_Param params[4]);


#endif /* __IT_H */