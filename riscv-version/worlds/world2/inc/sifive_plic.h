#define PLIC_BASE                   (0x0c000000UL)
#define PLIC_ENABLE_ADDR            (PLIC_BASE + 0x2000UL)
#define PLIC_ENABLE                 ((uint32_t*)PLIC_ENABLE_ADDR)
#define PLIC_CLAIM_ADDR             (PLIC_BASE + 0x200004UL)
#define PLIC_CLAIM                  ((uint32_t*)PLIC_CLAIM_ADDR)


#define COMPLETE_PLIC(interrupt) \
    asm volatile ( \
        "li t0, 0x0c200000\n\t" \
        "sw %0, 4(t0)\n\t" \
        : \
        : "r"(interrupt) \
        : "t0" \
    );

#define READ_CSR(storing, csr) \
    asm volatile ( \
        "csrr t0, " #csr " \n\t" \
        "sw t0, %0 \n\t" \
        : "=m"(storing) \
        : \
        : "t0" \
    );

#define READ_PLIC(storing) \
    asm volatile ( \
        "la t0, 0x0c200004UL\n\t" \
        "lw t0, 0(t0)\n\t" \
        "sw t0, %0 \n\t" \
        : "=m"(storing) \
        : \
        : "t0" \
    );    

void write_plic_priority(uint32_t, uint32_t);