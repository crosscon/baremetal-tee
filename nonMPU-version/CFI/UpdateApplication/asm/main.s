	.file	"main.c"
.text
	.balign 2
	.global	receivePin
	.type	receivePin, @function
receivePin:
; start of function
; framesize_regs:     4
; framesize_locals:   8
; framesize_outgoing: 0
; framesize:          12
; elim ap -> fp       8
; elim fp -> sp       8
; saved regs: R10
	; start of prologue
	PUSHM.A	#1, R10
	SUBA	#8, R1
	; end of prologue
	MOVA	R12, @R1
	MOV.B	#0, R10
	MOV.B	#0, R10
	BRA	#.L2
.L5:
	MOV.W	R10, R12
	AND.B	#1, R12
	CMP.W	#0, R12 { JNE	.L3
	MOV.B	#202, R13
	BRA	#.L4
.L3:
	MOV.B	#68, R13
.L4:
	MOV.W	R10, R14
	RLAM.A #4, R14 { RRAM.A #4, R14
	MOVA	R14, R12
	MOVA	R1, R14
	ADDA	#4, R14
	ADDA	R14, R12
	MOV.B	R13, @R12
	ADD.W	#1, R10
.L2:
	MOV.B	#9, R12
	CMP.W	R10, R12 { JGE	.L5
	NOP
	NOP
	; start of epilogue
	ADDA	#8, R1
	POPM.A	#1, r10
	RETA
	.size	receivePin, .-receivePin
	.balign 2
	.global	verifyPin
	.type	verifyPin, @function
verifyPin:
; start of function
; framesize_regs:     0
; framesize_locals:   12
; framesize_outgoing: 0
; framesize:          12
; elim ap -> fp       4
; elim fp -> sp       12
; saved regs:(none)
	; start of prologue
	SUBA	#12, R1
	; end of prologue
	MOVA	R12, @R1
	MOV.B	#49, 5(R1)
	MOV.B	#50, 6(R1)
	MOV.B	#51, 7(R1)
	MOV.B	#52, 8(R1)
	MOV.B	#0, 9(R1)
	MOV.W	#0, 10(R1)
	BRA	#.L7
.L10:
	MOV.W	10(R1), R13
	RLAM.A #4, R13 { RRAM.A #4, R13
	MOVA	R13, R12
	ADDX.A	@R1, R12
	MOV.B	@R12, R13
	MOV.W	10(R1), R14
	RLAM.A #4, R14 { RRAM.A #4, R14
	MOVA	R14, R12
	MOVA	R1, R14
	ADDA	#5, R14
	ADDA	R14, R12
	MOV.B	@R12, R12
	CMP.B	R12, R13 { JEQ	.L8
	MOV.B	#0, R12
	BRA	#.L11
.L8:
	ADD.W	#1, 10(R1)
.L7:
	MOV.B	#3, R12
	CMP.W	10(R1), R12 { JGE	.L10
	MOV.B	#1, R12
.L11:
	; start of epilogue
	ADDA	#12, R1
	RETA
	.size	verifyPin, .-verifyPin
	.balign 2
	.global	gadget_pop_r12_ret
	.type	gadget_pop_r12_ret, @function
gadget_pop_r12_ret:
; start of function
; attributes: naked 
; framesize_regs:     0
; framesize_locals:   0
; framesize_outgoing: 0
; framesize:          0
; elim ap -> fp       4
; elim fp -> sp       0
; saved regs:(none)
 ; 28 "src/main.c" 1
	MOV @SP+, R12
	RETA
	
 ; 0 "" 2
	NOP
	.size	gadget_pop_r12_ret, .-gadget_pop_r12_ret
	.balign 2
	.global	gadget_call_r12_ret
	.type	gadget_call_r12_ret, @function
gadget_call_r12_ret:
; start of function
; attributes: naked 
; framesize_regs:     0
; framesize_locals:   0
; framesize_outgoing: 0
; framesize:          0
; elim ap -> fp       4
; elim fp -> sp       0
; saved regs:(none)
 ; 36 "src/main.c" 1
	CALLA R12
	RETA
	
 ; 0 "" 2
	NOP
	.size	gadget_call_r12_ret, .-gadget_call_r12_ret
	.balign 2
	.global	openLock
	.type	openLock, @function
openLock:
; start of function
; framesize_regs:     0
; framesize_locals:   0
; framesize_outgoing: 0
; framesize:          0
; elim ap -> fp       4
; elim fp -> sp       0
; saved regs:(none)
	; start of prologue
	; end of prologue
	MOV.B	&PADIR_L, R12
	BIS.B	#1, R12
	AND	#0xff, R12
	MOV.B	R12, &PADIR_L
	MOV.B	&PAOUT_L, R12
	BIS.B	#1, R12
	AND	#0xff, R12
	MOV.B	R12, &PAOUT_L
	NOP
	; start of epilogue
	RETA
	.size	openLock, .-openLock
	.balign 2
	.global	main
	.type	main, @function
main:
; start of function
; framesize_regs:     0
; framesize_locals:   4
; framesize_outgoing: 0
; framesize:          4
; elim ap -> fp       4
; elim fp -> sp       4
; saved regs:(none)
	; start of prologue
	SUBA	#4, R1
	; end of prologue
	MOV.W	#23168, &WDTCTL
	MOVA	R1, R12
	CALLA	#receivePin
.L17:
	MOVA	R1, R12
	CALLA	#verifyPin
	CMP.W	#0, R12 { JEQ	.L17
	CALLA	#openLock
	BRA	#.L17
	.size	main, .-main
	.ident	"GCC: (michele) 9.3.1"
	.mspabi_attribute 4, 2
	.mspabi_attribute 6, 2
	.mspabi_attribute 8, 2
	.gnu_attribute 4, 1
