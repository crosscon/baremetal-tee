#ifndef __IT_H
#define __IT_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/* Functions to handle the exceptions caused by the instrumented code (SVC, HardFault, MemMenage)*/
/* The SVC handler is used mainly for two execution flows:
*  - An client/unsecure application wants to comunicate with a trusted application (using TEEC_OpenSession, TEEC_InvokeCommand, etc.)
*  - A trusted application wants to call a core service offered by the TEE (TEE_CreatePersistentObject, TEE_CipherInit, etc.)
*/
void Microvisor_HardFault_Handler();
void Microvisor_SVC_Handler();
void Microvisor_MemManage_Handler();
void Microvisor_PendSV_Handler();

#endif /* __IT_H */