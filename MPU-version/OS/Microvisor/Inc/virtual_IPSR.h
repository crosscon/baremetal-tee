#ifndef __VIRTUAL_IPSR_H
#define __VIRTUAL_IPSR_H

/**
 * Functions to handle the virtual IPSR (Interrupt Program Status Register) 
 * used in combination with the deprioritization of the handlers:
 * - Initialize_Virtual_IPSR: Initializes the virtual IPSR 
 * - Is_Deprioritized_Handler_Active: Returns if the deprioritizations of the handlers is active or not
 * - Get_Virtual_IPSR: Returns the current value of the virtual IPSR
 */
void Initialize_Virtual_IPSR();
int Is_Deprioritized_Handler_Active();
unsigned int Get_Virtual_IPSR();

#endif /* __VIRTUAL_IPSR_H */