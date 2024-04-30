#include "virtual_IPSR.h"

/*
* Declare the virtual IPSR (Interrupt Program Status Register) that store the exception number
* of the deprioritized interrupt currently being executed
*
* Note: the _attribute__((section(".ram-boot"))) specifies the section where this variable should be placed. 
In this case, the variable will be placed in the .ram-boot section of the memory layout. 
*/ 
unsigned int __attribute__((section(".ram-boot"))) _virtual_IPSR;

/**
 * Fill virtual ISPR with zeros
 */
void Initialize_Virtual_IPSR() {
	_virtual_IPSR = 0;
}

/**
 * Returns true when a deprioritized exception handler
 * is in execution, false otherwise.
 */
int Is_Deprioritized_Handler_Active() {
	return (_virtual_IPSR != 0);
}

/**
 * Returns exception number of the currenly
 * active deprioritized interrupt.
 */
unsigned int Get_Virtual_IPSR() {
	return _virtual_IPSR;
}