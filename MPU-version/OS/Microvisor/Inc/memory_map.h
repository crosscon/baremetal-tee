#ifndef __MEMORY_MAP_H
#define __MEMORY_MAP_H

/* Define the variables to store the start and end addresses for the various region of the memory */
extern unsigned int __flash_boot_start__;
extern unsigned int __flash_boot_size__;
extern unsigned int __flash_boot_nopri_start__;
extern unsigned int __flash_boot_nopri_size__;
extern unsigned int __flash_start__;
extern unsigned int __flash_size__;
extern unsigned int __isr_vector_deprio_start__;
extern uint32_t __ram_boot_start__;

#endif /* __MEMORY_MAP_H */