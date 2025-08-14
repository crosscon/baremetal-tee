#define UART0_BASE 0x10013000
#define UART1_BASE 0x10014000
#define FLASH 0x20000000
#define DRAM 0x80000000
#define _REG32(base, offset) (*(volatile uint32_t *)((base) + (offset)))
#define UART0_REG(offset) _REG32(UART0_BASE, offset)
#define UART1_REG(offset) _REG32(UART1_BASE, offset)
