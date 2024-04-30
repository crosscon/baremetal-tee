#ifndef __IT_H
#define __IT_H

/* Functions to handle the exceptions caused by the instrumented code (SVC, HardFault, MemMenage)*/
void Microvisor_HardFault_Handler();
void Microvisor_SVC_Handler();
void Microvisor_MemManage_Handler();

#endif /* __IT_H */