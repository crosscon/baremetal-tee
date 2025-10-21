#ifndef __STM32WB55RG_MPU_H
#define __STM32WB55RG_MPU_H

/**
 * Functions to configure the MPU memory regions and perission and to handle MPU
 * violations
 *
 * - Configure_MPU: Configures the MPU in order to protect the secure world and
 * allow the client/fortified/untrusted application (in normal world) to access
 * only its own resources (flash, RAM, peripherals)
 * - Reconfigure_MPU: Reconfigures the MPU in order to allow the execution of
 * one of two trusted applications (TA1 or TA2) to access its resources (flash,
 * RAM, peripherals) and the resources of the client/fortified/untrusted
 * application
 */
void Configure_MPU(void);
void Reconfigure_MPU(int TA_number);
void MPU_Violation_Handler(unsigned int *auto_frame,
                           unsigned int *manual_frame);
void microvisor_memmanage_handler(unsigned int *auto_frame,
                                  unsigned int *manual_frame);

#endif /* __STM32WB55RG_MPU_H */
