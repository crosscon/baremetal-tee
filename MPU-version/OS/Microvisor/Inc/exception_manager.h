#ifndef __EXCEPTION_MANAGER_H
#define __EXCEPTION_MANAGER_H

/* Handlers for catching and simulating the deprioritized exceptions */
void Exception_Catcher();
void Exception_Simulator(int exception_number, int exception_priority);

#endif /* __EXCEPTION_MANAGER_H */