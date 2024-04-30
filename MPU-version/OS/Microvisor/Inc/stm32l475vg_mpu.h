#ifndef __STM32WB55RG_MPU_H
#define __STM32WB55RG_MPU_H

/**
 * Functions to configure the MPU memory regions and perission and to handle MPU violations
*/
void Configure_MPU(void);
void MPU_Violation_Handler(unsigned int* auto_frame, unsigned int* manual_frame);

#endif /* __STM32WB55RG_MPU_H */