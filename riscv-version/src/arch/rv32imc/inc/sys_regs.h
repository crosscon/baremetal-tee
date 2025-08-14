/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) uTango Project and Contributors. All rights reserved.
 */
#ifndef __SYS_REGS_H__
#define __SYS_REGS_H__

/* ==== Core Local Interrupter (CLINT) ========================================== */
#define CLINT_BASE                  (0x02000000UL)
#define MTIME_OFF                   (0xBFF8UL)
#define MTIME_ADDR                  (CLINT_BASE + MTIME_OFF)
#define MTIMECMP_OFF                (0x4000UL)
#define MTIMECMP_ADDR               (CLINT_BASE + MTIMECMP_OFF)

/* ==== Platform Interrupt Controller (PLIC) ======================================== */
#define PLIC_BASE                   (0x0c000000UL)
#define PLIC_PRIORITY_LIMIT         (PLIC_BASE + 0x1000UL)
#define PLIC_ENABLE_ADDR            (PLIC_BASE + 0x2000UL)
#define PLIC_ENABLE                 ((uint32_t*)PLIC_ENABLE_ADDR)
#define PLIC_CLAIM_ADDR             (PLIC_BASE + 0x200004UL)
#define PLIC_PENDING_ADDR           (PLIC_BASE + 0x1000UL)
#define PLIC_CLAIM                  ((uint32_t*)PLIC_CLAIM_ADDR)

#define MRET_OP         0x30200073
#define STORE_OP        0x23
#define SYSTEM_OP       0x73

#define CSRRW_FUNC      0x1
#define CSRRS_FUNC      0x2
#define CSRRC_FUNC      0x3
#define CSRRWI_FUNC     0x5
#define CSRRSI_FUNC     0x6
#define CSRRCI_FUNC     0x7

#define MCAUSE_DEST     0x342
#define MTVAL_DEST      0x343
#define MEPC_DEST       0x341
#define MIE_DEST        0x304
#define MIP_DEST        0x344
#define MTVEC_DEST      0x305
#define MHARTID_DEST    0xf14
#define MISA_DEST       0x301
#define MSTATUS_DEST    0x300
#define MCYCLE_DEST     0xb00
#define MINSTRET_DEST   0xb02

#define MSTATUS_MIE     1 << 3
#define MIE_MTIMER_INTERRUPT    1 << 7


#endif /* __SYS_REGS_H__ */