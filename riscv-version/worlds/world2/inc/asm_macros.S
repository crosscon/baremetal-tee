.macro ENABLE_UART_INTERRUPT base
	/* Turn On Interrupts on UART  */
	/* UART BASE */
 	li t0, \base
	/* IRQ offset */
	li t1, 16
	add t0, t0, t1
	/* Enable all IRQs */
	li t1, 0x02
	sw t1, (t0)
.endm

.macro SET_PLIC_PRIORITY plic_int_offset priority
	/* PLIC BASE */
 	li t0, 0x0c000000
	add t0, t0, \plic_int_offset
	/* Enable all IRQs */
	li t1, \priority
	sw t1, (t0)
.endm

.macro ENABLE_PLIC_INTERRUPT plic_int_num
	/* PLIC BASE */
 	li t0, 0x0c002000
	li t1, \plic_int_num
	sw t1, (t0)
.endm

.macro CLAIM_PLIC_INTERRUPT reg
    li t0, 0x0c200000   # Claim/Complete Register
    lw \reg, 4(t0)
.endm

.macro SET_MTIMERCMP reload
    /* CLINT Base + Reg Offset */
 	li t0, 0x02004000
    sw \reload, (t0)
.endm

.macro SET_MTIMER value
    /* CLINT Base + Reg Offset */
 	li t0, 0x0200bff8
    sw \value, (t0)
.endm

.macro PUSH reg
    sw \reg, 0(sp)
    addi sp, sp, -4
.endm

.macro POP reg
    lw \reg, 4(sp) 
    addi sp, sp, 4
.endm
