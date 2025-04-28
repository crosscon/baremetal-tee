	.file	"secureUpdate.c"
.text
	.section	.tcm:code,"ax",@progbits
	.balign 2
	.global	INTERRUPT_ISR
	.section	__interrupt_vector_1,"ax",@progbits
	.word	INTERRUPT_ISR
		.section	.tcm:code
	.type	INTERRUPT_ISR, @function
INTERRUPT_ISR:
; start of function
; attributes: interrupt 
; framesize_regs:     8
; framesize_locals:   0
; framesize_outgoing: 0
; framesize:          8
; elim ap -> fp       12
; elim fp -> sp       0
; saved regs: R12 R13
	; start of prologue
	PUSHM.A	#2, R13
	; end of prologue
	MOVX.W	&rcvBufCount, R12
	MOV.W	R12, R13
	ADD.W	#1, R13
	MOVX.W	R13, &rcvBufCount
	MOV.W	R12, R12
	MOVX.B	&UCA1RXBUF, rcvBuf(R12)
	MOVX.W	&rcvBufCount, R12
	CMP.W	#512, R12 { JEQ	.L4
	; start of epilogue
	POPM.A	#2, r13
	RETI
.L4:
	BICX.B	#1, &UCA1ICTL_L
	; start of epilogue
	POPM.A	#2, r13
	RETI
	.size	INTERRUPT_ISR, .-INTERRUPT_ISR
	.balign 2
	.global	overWriteMemory
	.type	overWriteMemory, @function
overWriteMemory:
; start of function
; attributes: 
; framesize_regs:     8
; framesize_locals:   0
; framesize_outgoing: 0
; framesize:          8
; elim ap -> fp       12
; elim fp -> sp       0
; saved regs: R8 R10
	; start of prologue
	PUSHM.A	#1, R10
	PUSHM.A	#1, R8
	; end of prologue
	MOVX.W	#-23296, &FCTL3
	MOVA	R14, R10
	ANDX.B	#3, R10
	CMPA	#0, R10 { JEQ	.L6
	MOVX.W	#-23232, &FCTL1
	MOV.W	@R12+, @R14
	ADDA	#2, R14
	ADD.W	#-2, R13
.L7:
	MOV.W	R13, R11
	RRUM.W	#2, R11
	MOVA	R12, R8
	MOVA	R14, R10
	MOV.B	#0, R15
.L8:
	MOV.W	@R8+, @R10
	MOV.W	@R8+, 2(R10)
	ADDA	#4, R10
	ADD.W	#1, R15
	CMP.W	R11, R15 { JLO	.L8
	CMP.W	#0, R11 { JNE	.L10
	MOV.B	#1, R11
.L10:
	BIT.W	#3, R13 { JEQ	.L11
	MOVX.W	#-23232, &FCTL1
	RLAM.W	#1, R11
	MOV.W	R11, R10
	RLAM.A	#1, R10
	ADDA	R10, R12
	ADDA	R10, R14
	MOV.W	@R12, @R14
.L11:
	MOV.B	#1, R12
	; start of epilogue
	POPM.A	#1, r8
	POPM.A	#1, r10
	RETA
.L6:
	MOVX.W	#-23168, &FCTL1
	BRA	#.L7
	.size	overWriteMemory, .-overWriteMemory
	.section	.tcm:codeUpper,"ax",@progbits
	.balign 2
	.global	deploy
	.type	deploy, @function
deploy:
; start of function
; attributes: 
; framesize_regs:     28
; framesize_locals:   46
; framesize_outgoing: 0
; framesize:          74
; elim ap -> fp       32
; elim fp -> sp       46
; saved regs: R4 R5 R6 R7 R8 R9 R10
	; start of prologue
	PUSHM.A	#7, R10
	SUBA	#46, R1
	; end of prologue
	MOVA	R12, 20(R1)
	MOV.B	R13, R5
	MOVX.W	&elfAddress, R10
	MOVX.W	&elfAddress+2, R11
	PUSH.W	R11 { PUSH.W	R10 { POPM.A	#1, R14
	MOV.B	@R14, R12
	CMP.B	#0, @R14 { JEQ	.L56
	MOVA	&elfAddress, R6
	ADDA	#1, R6
	ADD.B	#-1, R12
	MOV.B	R12, R12
	MOVA	R12, R14
	RLAM.A	#3, R14
	ADDA	R14, R12
	MOVA	&elfAddress, R4
	ADDA	#10, R4
	ADDA	R12, R4
	MOVX.W	&appBottomRam, R11
	MOV.W	#0,R12
	MOV.W	R11, @R1
	MOV.W	R12, 2(R1)
	MOVX.W	&appBottomText, R10
	MOV.W	#0,R11
	MOV.W	R10, 4(R1)
	MOV.W	R11, 6(R1)
	MOVX.W	&appTopText, R11
	MOV.W	#0,R12
	MOV.W	R11, 12(R1)
	MOV.W	R12, 14(R1)
	MOV.W	R11, 28(R1)
	MOVX.W	&appTopRam, R10
	MOV.W	#0,R11
	MOV.W	R10, 16(R1)
	MOV.W	R11, 18(R1)
	MOV.W	R10, 30(R1)
.L55:
	CMP.W	#1, R5 { JEQ	.L92
	CMP.W	#0, R5 { JNE	.L21
	CMP.B	#0, 6(R6) { JEQ	.L21
	MOV.B	3(R6), R12
	RPT	#8 { RLAX.W	R12
	MOV.B	2(R6), R10
	BIS.W	R12, R10
	MOV.B	5(R6), R12
	RPT	#8 { RLAX.W	R12
	MOV.B	4(R6), R11
	BIS.W	R12, R11
	MOVX.W	&appBottomText, R15
	MOV.W	R15,R12 { MOV.W	#0,R13
	CMP.W	#0, R11 { JNE	.L59
	CMP.W	R12, R10 { JHS	.L59
.L22:
	MOV.B	1(R6), R14
	RPT	#8 { RLAX.W	R14
	MOV.B	@R6, R15
	BIS.W	R15, R14
	CMP.W	#0, R14 { JEQ	.L21
	MOV.B	8(R6), R15
	RPT	#8 { RLAX.W	R15
	MOV.B	7(R6), R12
	BIS.W	R12, R15
	CMP.W	2(R1), R11 { JLO	.L27
	CMP.W	#0, R11 { JNE	.L60
	CMP.W	@R1, R10 { JHS	.L60
.L27:
	CMP.W	6(R1), R11 { JLO	.L30
	CMP.W	#0, R11 { JEQ	.L93
	MOV.W	R14,R12 { MOV.W	#0,R13
	MOV.W	R12, R7
	ADD	R10, R7 ; cy
	MOV.W	R13, R9
	ADDC	R11, R9
	CMP.W	#0, R9 { JEQ	.L94
.L30:
	CMPX.W	&appBottomROdata+2, R11 { JLO	.L40
	CMPX.W	R11, &appBottomROdata+2 { JEQ	.L95
	MOV.W	R14,R12 { MOV.W	#0,R13
	MOV.W	R12, R9
	ADD	R10, R9 ; cy
	MOV.W	R13, R12
	ADDC	R11, R12
	CMPX.W	R12, &appTopROdata+2 { JHS	.L96
.L40:
	CMPX.W	&vectorBottom+2, R11 { JLO	.L58
	CMPX.W	R11, &vectorBottom+2 { JEQ	.L97
.L67:
	MOV.W	R14,R12 { MOV.W	#0,R13
	MOV.W	R12, R9
	ADD	R10, R9 ; cy
	MOV.W	R13, R12
	ADDC	R11, R12
	CMPX.W	R12, &vectorTop+2 { JHS	.L98
.L58:
	MOV.B	#0, R12
.L103:
	; start of epilogue
	ADDA	#46, R1
	POPM.A	#7, r10
	RETA
.L59:
	MOVX.W	&appTopText, R14
	MOV.W	R14,R12 { MOV.W	#0,R13
	CMP.W	#0, R11 { JNE	.L22
	CMP.W	#0, R13 { JEQ	.L99
.L21:
	ADDA	#9, R6
	CMPA	R4, R6 { JNE	.L55
.L56:
	MOV.B	#1, R12
	; start of epilogue
	ADDA	#46, R1
	POPM.A	#7, r10
	RETA
.L60:
	MOV.W	R14,R12 { MOV.W	#0,R13
	MOV.W	R12, R9
	ADD	R10, R9 ; cy
	MOV.W	R13, R12
	ADDC	R11, R12
	CMP.W	#0, R12 { JNE	.L27
	CMP.W	#0, 18(R1) { JNE	.L61
	CMP.W	R9, 30(R1) { JLO	.L27
.L61:
	MOV.W	R15,R12 { MOV.W	#0,R13
	MOV.W	R12, 8(R1)
	MOV.W	R13, 10(R1)
	MOV.W	R14, R14
	MOVA	8(R1), R13
	MOVA	&elfAddress, R15
	ADDA	R15, R13
	PUSH.W	R11 { PUSH.W	R10 { POPM.A	#1, R12
	CALLA	#memcpy
	ADDA	#9, R6
	CMPA	R4, R6 { JNE	.L55
	BRA	#.L56
.L92:
	CMP.B	#1, 6(R6) { JNE	.L21
	MOV.B	3(R6), R12
	RPT	#8 { RLAX.W	R12
	MOV.B	2(R6), R10
	BIS.W	R12, R10
	MOV.B	5(R6), R12
	RPT	#8 { RLAX.W	R12
	MOV.B	4(R6), R11
	BIS.W	R12, R11
	MOVX.W	&appTopText, R14
	MOV.W	R14,R12 { MOV.W	#0,R13
	CMP.W	#0, R11 { JNE	.L21
	CMP.W	R12, R10 { JLO	.L22
	ADDA	#9, R6
	CMPA	R4, R6 { JNE	.L55
	BRA	#.L56
.L93:
	CMP.W	4(R1), R10 { JLO	.L30
	MOV.W	R14,R12 { MOV.W	#0,R13
	MOV.W	R12, R7
	ADD	R10, R7 ; cy
	MOV.W	R13, R9
	ADDC	R11, R9
	CMP.W	#0, R9 { JNE	.L30
.L94:
	CMP.W	#0, 14(R1) { JNE	.L63
	CMP.W	R7, 28(R1) { JLO	.L30
.L63:
	MOV.W	R15,R12 { MOV.W	#0,R13
	MOV.W	R12, 8(R1)
	MOV.W	R13, 10(R1)
	MOVA	8(R1), R12
	MOVA	&elfAddress, R13
	ADDA	R13, R12
	MOVA	R12, 8(R1)
	PUSH.W	R11 { PUSH.W	R10 { POPM.A	#1, R15
	MOVA	R15, 24(R1)
	MOVX.W	#-23296, &FCTL3
	MOV.W	R10, R12
	AND.B	#3, R12
	MOV.W	R12, 32(R1)
	MOV.W	#0, 34(R1)
	MOV.W	32(R1), R12
	MOV.W	34(R1), R13
	PUSH.W	R13 { PUSH.W	R12 { POPM.A	#1, R8
	CMPA	#0, R8 { JNE	.L100
	MOVX.W	#-23168, &FCTL1
	MOV.W	R14, 36(R1)
	MOV.W	R14, R15
.L34:
	RRUM.W	#2, R15
	MOVA	8(R1), R8
	MOVA	24(R1), R12
	MOV.B	#0, R13
.L35:
	MOV.W	@R8+, @R12
	MOV.W	@R8+, 2(R12)
	ADDA	#4, R12
	ADD.W	#1, R13
	CMP.W	R15, R13 { JLO	.L35
	CMP.W	#0, R15 { JNE	.L37
	MOV.B	#1, R15
.L37:
	BITX.W	#3, 36(R1) { JEQ	.L38
	MOVX.W	#-23232, &FCTL1
	RLAM.W	#1, R15
	MOV.W	R15, R12
	RLAM.A	#1, R12
	MOVA	8(R1), R8
	ADDA	R12, R8
	ADDX.A	24(R1), R12
	MOV.W	@R8, @R12
.L38:
	MOVA	20(R1), R15
	MOV.W	@R15, R15
	MOV.W	R15,R12 { MOV.W	#0,R13
	CMP.W	#0, R9 { JEQ	.L101
.L64:
	ADD.W	R10, R14
	MOVA	20(R1), R12
	MOV.W	R14, @R12
	BRA	#.L21
.L99:
	CMP.W	R10, R12 { JLO	.L22
	ADDA	#9, R6
	CMPA	R4, R6 { JNE	.L55
	BRA	#.L56
.L95:
	CMPX.W	&appBottomROdata, R10 { JLO	.L40
	MOV.W	R14,R12 { MOV.W	#0,R13
	MOV.W	R12, R9
	ADD	R10, R9 ; cy
	MOV.W	R13, R12
	ADDC	R11, R12
	CMPX.W	R12, &appTopROdata+2 { JLO	.L40
.L96:
	CMPX.W	R12, &appTopROdata+2 { JNE	.L66
	CMPX.W	R9, &appTopROdata { JLO	.L40
.L66:
	MOV.W	R15,R12 { MOV.W	#0,R13
	MOV.W	R12, 8(R1)
	MOV.W	R13, 10(R1)
	MOVA	8(R1), R9
	MOVA	&elfAddress, R13
	ADDA	R13, R9
	PUSH.W	R11 { PUSH.W	R10 { POPM.A	#1, R8
	MOVX.W	#-23296, &FCTL3
	MOV.W	R10, R15
	AND.B	#3, R15
	MOV.W	R15, 38(R1)
	MOV.W	#0, 40(R1)
	MOV.W	38(R1), R10
	MOV.W	40(R1), R11
	PUSH.W	R11 { PUSH.W	R10 { POPM.A	#1, R12
	CMPA	#0, R12 { JNE	.L102
	MOVX.W	#-23168, &FCTL1
.L44:
	MOV.W	R14, R15
	RRUM.W	#2, R15
	MOVA	R9, R10
	MOVA	R8, R12
	MOV.B	#0, R13
.L45:
	MOV.W	@R10+, @R12
	MOV.W	@R10+, 2(R12)
	ADDA	#4, R12
	ADD.W	#1, R13
	CMP.W	R15, R13 { JLO	.L45
.L89:
	CMP.W	#0, R15 { JNE	.L54
	MOV.B	#1, R15
.L54:
	BIT.W	#3, R14 { JEQ	.L21
	MOVX.W	#-23232, &FCTL1
	RLAM.W	#1, R15
	MOV.W	R15, R12
	RLAM.A	#1, R12
	MOVA	R9, R14
	ADDA	R12, R14
	ADDA	R12, R8
	MOV.W	@R14, @R8
	ADDA	#9, R6
	CMPA	R4, R6 { JNE	.L55
	BRA	#.L56
.L97:
	CMPX.W	&vectorBottom, R10 { JHS	.L67
	MOV.B	#0, R12
	BRA	#.L103
.L98:
	CMPX.W	R12, &vectorTop+2 { JNE	.L68
	CMPX.W	R9, &vectorTop { JLO	.L58
.L68:
	MOV.W	R15,R12 { MOV.W	#0,R13
	MOV.W	R12, 8(R1)
	MOV.W	R13, 10(R1)
	MOVA	8(R1), R9
	MOVA	&elfAddress, R13
	ADDA	R13, R9
	PUSH.W	R11 { PUSH.W	R10 { POPM.A	#1, R8
	MOVX.W	#-23296, &FCTL3
	MOV.W	R10, R15
	AND.B	#3, R15
	MOV.W	R15, 42(R1)
	MOV.W	#0, 44(R1)
	MOV.W	42(R1), R10
	MOV.W	44(R1), R11
	PUSH.W	R11 { PUSH.W	R10 { POPM.A	#1, R12
	CMPA	#0, R12 { JNE	.L104
	MOVX.W	#-23168, &FCTL1
.L51:
	MOV.W	R14, R15
	RRUM.W	#2, R15
	MOVA	R9, R10
	MOVA	R8, R12
	MOV.B	#0, R13
.L52:
	MOV.W	@R10+, @R12
	MOV.W	@R10+, 2(R12)
	ADDA	#4, R12
	ADD.W	#1, R13
	CMP.W	R15, R13 { JLO	.L52
	BRA	#.L89
.L100:
	MOVX.W	#-23232, &FCTL1
	MOVA	8(R1), R12
	ADDX.A	#2, 8(R1)
	MOV.W	@R12+, @R15
	ADDA	#2, R15
	MOVA	R15, 24(R1)
	MOV.W	R14, R13
	ADD.W	#-2, R13
	MOV.W	R13, 36(R1)
	MOV.W	R13, R15
	BRA	#.L34
.L102:
	MOVX.W	#-23232, &FCTL1
	MOV.W	@R9+, @R8
	ADDA	#2, R8
	ADD.W	#-2, R14
	BRA	#.L44
.L104:
	MOVX.W	#-23232, &FCTL1
	MOV.W	@R9+, @R8
	ADDA	#2, R8
	ADD.W	#-2, R14
	BRA	#.L51
.L101:
	CMP.W	#0, R13 { JNE	.L21
	CMP.W	R7, R12 { JHS	.L21
	BRA	#.L64
	.size	deploy, .-deploy
	.balign 2
	.global	load_elf_segment
	.type	load_elf_segment, @function
load_elf_segment:
; start of function
; attributes: 
; framesize_regs:     28
; framesize_locals:   8
; framesize_outgoing: 0
; framesize:          36
; elim ap -> fp       32
; elim fp -> sp       8
; saved regs: R4 R5 R6 R7 R8 R9 R10
	; start of prologue
	PUSHM.A	#7, R10
	SUBA	#8, R1
	; end of prologue
	MOV.W	R12, @R1
	MOV.W	R13, 2(R1)
	MOVA	R15, R4
	MOV.B	1(R14), R13
	RPT	#8 { RLAX.W	R13
	MOV.B	@R14, R6
	BIS.W	R6, R13
	CMP.W	#0, R13 { JEQ	.L160
	MOV.B	3(R14), R12
	RPT	#8 { RLAX.W	R12
	MOV.B	2(R14), R10
	BIS.W	R12, R10
	MOV.B	5(R14), R12
	RPT	#8 { RLAX.W	R12
	MOV.B	4(R14), R11
	BIS.W	R12, R11
	MOV.B	8(R14), R12
	RPT	#8 { RLAX.W	R12
	MOV.B	7(R14), R14
	BIS.W	R14, R12
	MOVX.W	&appBottomRam, R7
	MOV.W	R7,R14 { MOV.W	#0,R15
	CMP.W	#0, R11 { JEQ	.L167
.L139:
	MOV.W	R13,R14 { MOV.W	#0,R15
	MOV.W	R14, R8
	ADD	R10, R8 ; cy
	MOV.W	R15, R9
	ADDC	R11, R9
	MOVX.W	&appTopRam, R6
	MOV.W	R6,R14 { MOV.W	#0,R15
	CMP.W	#0, R9 { JEQ	.L168
.L108:
	MOVX.W	&appBottomText, R6
	MOV.W	R6,R14 { MOV.W	#0,R15
	CMP.W	#0, R11 { JNE	.L141
	CMP.W	R14, R10 { JHS	.L141
.L111:
	CMPX.W	&appBottomROdata+2, R11 { JLO	.L122
	CMPX.W	R11, &appBottomROdata+2 { JEQ	.L169
.L144:
	MOV.W	R13,R14 { MOV.W	#0,R15
	MOV.W	R14, R9
	ADD	R10, R9 ; cy
	MOV.W	R15, R14
	ADDC	R11, R14
	CMPX.W	R14, &appTopROdata+2 { JHS	.L170
.L122:
	CMPX.W	&vectorBottom+2, R11 { JLO	.L138
	CMPX.W	R11, &vectorBottom+2 { JEQ	.L171
.L146:
	MOV.W	R13,R14 { MOV.W	#0,R15
	MOV.W	R14, R9
	ADD	R10, R9 ; cy
	MOV.W	R15, R14
	ADDC	R11, R14
	CMPX.W	R14, &vectorTop+2 { JHS	.L172
.L138:
	MOV.B	#0, R12
.L175:
	; start of epilogue
	ADDA	#8, R1
	POPM.A	#7, r10
	RETA
.L172:
	CMPX.W	R14, &vectorTop+2 { JNE	.L147
	CMPX.W	R9, &vectorTop { JLO	.L138
.L147:
	MOV.W	R12,R6 { MOV.W	#0,R7
	MOV.W	R6, 4(R1)
	MOV.W	R7, 6(R1)
	MOVA	4(R1), R12
	MOVA	@R1, R7
	ADDA	R7, R12
	PUSH.W	R11 { PUSH.W	R10 { POPM.A	#1, R8
	MOVX.W	#-23296, &FCTL3
	MOV.W	R10, R14
	AND.B	#3, R14
	MOV.B	#0, R15
	PUSH.W	R15 { PUSH.W	R14 { POPM.A	#1, R14
	CMPA	#0, R14 { JEQ	.L132
	MOVX.W	#-23232, &FCTL1
	MOV.W	@R12+, @R8
	ADDA	#2, R8
	ADD.W	#-2, R13
.L133:
	MOV.W	R13, R9
	RRUM.W	#2, R9
	MOVA	R12, R10
	MOVA	R8, R14
	MOV.B	#0, R15
.L134:
	MOV.W	@R10+, @R14
	MOV.W	@R10+, 2(R14)
	ADDA	#4, R14
	ADD.W	#1, R15
	CMP.W	R9, R15 { JLO	.L134
.L165:
	CMP.W	#0, R9 { JNE	.L136
	MOV.B	#1, R9
.L136:
	BIT.W	#3, R13 { JEQ	.L160
	MOVX.W	#-23232, &FCTL1
	RLAM.W	#1, R9
	MOV.W	R9, R14
	RLAM.A	#1, R14
	ADDA	R14, R12
	ADDA	R14, R8
	MOV.W	@R12, @R8
.L160:
	MOV.B	#1, R12
.L107:
	; start of epilogue
	ADDA	#8, R1
	POPM.A	#7, r10
	RETA
.L141:
	MOV.W	R13,R14 { MOV.W	#0,R15
	MOV.W	R14, R8
	ADD	R10, R8 ; cy
	ADDC	R11, R15
	MOVX.W	&appTopText, R9
	MOV.W	R9,R6 { MOV.W	#0,R7
	CMP.W	#0, R15 { JNE	.L111
	CMP.W	#0, R7 { JNE	.L142
	CMP.W	R8, R6 { JLO	.L111
.L142:
	MOV.W	R12,R6 { MOV.W	#0,R7
	MOV.W	R6, 4(R1)
	MOV.W	R7, 6(R1)
	MOVA	4(R1), R6
	MOVA	@R1, R7
	ADDA	R7, R6
	MOVA	R6, 4(R1)
	PUSH.W	R11 { PUSH.W	R10 { POPM.A	#1, R5
	MOVX.W	#-23296, &FCTL3
	MOV.W	R10, R6
	AND.B	#3, R6
	MOV.B	#0, R7
	PUSH.W	R7 { PUSH.W	R6 { POPM.A	#1, R6
	CMPA	#0, R6 { JNE	.L173
	MOVX.W	#-23168, &FCTL1
	MOV.W	R13, R6
.L115:
	MOV.W	R6, R7
	RRUM.W	#2, R7
	MOVA	4(R1), R14
	MOVA	R5, R12
	MOV.B	#0, R9
.L116:
	MOV.W	@R14+, @R12
	MOV.W	@R14+, 2(R12)
	ADDA	#4, R12
	ADD.W	#1, R9
	CMP.W	R7, R9 { JLO	.L116
	CMP.W	#0, R7 { JNE	.L118
	MOV.B	#1, R7
.L118:
	BIT.W	#3, R6 { JEQ	.L119
	MOVX.W	#-23232, &FCTL1
	RLAM.W	#1, R7
	MOV.W	R7, R12
	RLAM.A	#1, R12
	MOVA	4(R1), R14
	ADDA	R12, R14
	ADDA	R5, R12
	MOV.W	@R14, @R12
.L119:
	MOV.W	@R4, R9
	MOV.W	R9,R6 { MOV.W	#0,R7
	CMP.W	#0, R15 { JEQ	.L174
.L143:
	ADD.W	R10, R13
	MOV.W	R13, @R4
	MOV.B	#1, R12
	BRA	#.L107
.L167:
	CMP.W	R14, R10 { JLO	.L108
	BRA	#.L139
.L169:
	CMPX.W	&appBottomROdata, R10 { JLO	.L122
	BRA	#.L144
.L171:
	CMPX.W	&vectorBottom, R10 { JHS	.L146
	MOV.B	#0, R12
	BRA	#.L175
.L170:
	CMPX.W	R14, &appTopROdata+2 { JNE	.L145
	CMPX.W	R9, &appTopROdata { JLO	.L122
.L145:
	MOV.W	R12,R14 { MOV.W	#0,R15
	MOV.W	R14, 4(R1)
	MOV.W	R15, 6(R1)
	MOVA	4(R1), R12
	MOVA	@R1, R15
	ADDA	R15, R12
	PUSH.W	R11 { PUSH.W	R10 { POPM.A	#1, R8
	MOVX.W	#-23296, &FCTL3
	MOV.W	R10, R14
	AND.B	#3, R14
	MOV.B	#0, R15
	PUSH.W	R15 { PUSH.W	R14 { POPM.A	#1, R14
	CMPA	#0, R14 { JNE	.L176
	MOVX.W	#-23168, &FCTL1
.L126:
	MOV.W	R13, R9
	RRUM.W	#2, R9
	MOVA	R12, R10
	MOVA	R8, R14
	MOV.B	#0, R15
.L127:
	MOV.W	@R10+, @R14
	MOV.W	@R10+, 2(R14)
	ADDA	#4, R14
	ADD.W	#1, R15
	CMP.W	R9, R15 { JLO	.L127
	BRA	#.L165
.L168:
	CMP.W	#0, R15 { JNE	.L140
	CMP.W	R8, R14 { JLO	.L108
.L140:
	MOV.W	R12,R14 { MOV.W	#0,R15
	MOV.W	R14, 4(R1)
	MOV.W	R15, 6(R1)
	MOV.W	R13, R14
	MOVA	4(R1), R13
	MOVA	@R1, R15
	ADDA	R15, R13
	PUSH.W	R11 { PUSH.W	R10 { POPM.A	#1, R12
	CALLA	#memcpy
	MOV.B	#1, R12
	BRA	#.L107
.L173:
	MOVX.W	#-23232, &FCTL1
	MOVA	4(R1), R6
	ADDX.A	#2, 4(R1)
	MOV.W	@R6+, @R5
	ADDA	#2, R5
	MOV.W	R13, R6
	ADD.W	#-2, R6
	BRA	#.L115
.L176:
	MOVX.W	#-23232, &FCTL1
	MOV.W	@R12+, @R8
	ADDA	#2, R8
	ADD.W	#-2, R13
	BRA	#.L126
.L132:
	MOVX.W	#-23168, &FCTL1
	BRA	#.L133
.L174:
	CMP.W	#0, R7 { JNE	.L160
	CMP.W	R8, R6 { JHS	.L160
	BRA	#.L143
	.size	load_elf_segment, .-load_elf_segment
	.section	.tcm:code
	.balign 2
	.global	launchVerification
	.type	launchVerification, @function
launchVerification:
; start of function
; attributes: 
; framesize_regs:     24
; framesize_locals:   4
; framesize_outgoing: 0
; framesize:          28
; elim ap -> fp       28
; elim fp -> sp       4
; saved regs: R4 R5 R6 R8 R9 R10
	; start of prologue
	PUSHM.A	#3, R10
	PUSHM.A	#3, R6
	SUBA	#4, R1
	; end of prologue
	MOV.W	R12, R8
	BISX.B	#1, &PAOUT_L
	MOV.B	#0, R14
	MOV.W	R12, R13
	MOVX.W	&appBottomText, R12
	CALLA	#verify
	MOV.B	R12, R10
	MOV.B	#1, R14
	MOV.W	R8, R13
	MOVX.W	&appBottomText, R12
	CALLA	#verify
	BIS.B	R12, R10
	CMP.B	#0, R10 { JNE	.L192
	MOVX.W	#-23296, &FCTL3
	MOVX.W	#-23292, &FCTL1
	MOVA	&appBottomROdata, R12
	MOV.W	#0, @R12
.L179:
	BITX.W	#1, &FCTL3 { JNE	.L179
	MOV.W	R8, R8
	MOVX.W	&elfAddress, R12
	MOVX.W	&elfAddress+2, R13
	PUSH.W	R13 { PUSH.W	R12 { POPM.A	#1, R14
	MOV.B	@R14, R12
	CMP.B	#0, @R14 { JEQ	.L181
	MOVA	&elfAddress, R6
	ADDA	#1, R6
	ADD.B	#-1, R12
	MOV.B	R12, R12
	MOVA	R12, R10
	RLAM.A	#3, R10
	ADDA	R10, R12
	MOVA	&elfAddress, R10
	ADDA	#10, R10
	ADDA	R12, R10
	MOVX.W	&appBottomText, R13
	MOV.W	R13,R4 { MOV.W	#0,R5
	MOVX.W	&appTopText, R12
	MOV.W	#0,R13
	MOV.W	R12, @R1
	MOV.W	R13, 2(R1)
	MOV.W	R12, R9
.L183:
	CMP.B	#0, 6(R6) { JEQ	.L187
	MOV.B	3(R6), R12
	RPT	#8 { RLAX.W	R12
	MOV.B	2(R6), R13
	BIS.W	R12, R13
	MOV.B	5(R6), R12
	RPT	#8 { RLAX.W	R12
	MOV.B	4(R6), R14
	BIS.W	R14, R12
	CMP.W	R5, R12 { JLO	.L185
	CMP.W	#0, R12 { JNE	.L185
	CMPX.W	&appBottomText, R13 { JLO	.L185
	CMP.W	#0, 2(R1) { JNE	.L187
	CMP.W	R13, R9 { JHS	.L187
.L185:
	MOVA	R8, R15
	MOVA	R6, R14
	MOVX.W	&elfAddress, R12
	MOVX.W	&elfAddress+2, R13
	CALLA	#load_elf_segment
	CMP.B	#0, R12 { JEQ	.L198
.L187:
	ADDA	#9, R6
	CMPA	R6, R10 { JNE	.L183
.L181:
	CALLA	#launchAppCode
.L199:
	; start of epilogue
	ADDA	#4, R1
	POPM.A	#3, r6
	POPM.A	#3, r10
	RETA
.L192:
	MOV.B	#10, R13
.L178:
	ADDX.B	#-128, &PBOUT_H
	XORX.B	#1, &PAOUT_L
	MOV.W	#10000, R12
.L191:
 ; 292 "core/src_compile/secureUpdate.c" 1
	nop
 ; 0 "" 2
	ADD.W	#-1, R12
	CMP.W	#0, R12 { JNE	.L191
	ADD.W	#-1, R13
	CMP.W	#0, R13 { JNE	.L178
 ; 295 "core/src_compile/secureUpdate.c" 1
	
	BR #secureUpdate
 ; 0 "" 2
	; start of epilogue
	ADDA	#4, R1
	POPM.A	#3, r6
	POPM.A	#3, r10
	RETA
.L198:
	MOVX.W	#6, &WDTCTL
	CALLA	#launchAppCode
	BRA	#.L199
	.size	launchVerification, .-launchVerification
	.balign 2
	.global	secureUpdate
	.type	secureUpdate, @function
secureUpdate:
; start of function
; attributes: 
; framesize_regs:     28
; framesize_locals:   500
; framesize_outgoing: 0
; framesize:          528
; elim ap -> fp       32
; elim fp -> sp       500
; saved regs: R4 R5 R6 R7 R8 R9 R10
	; start of prologue
	PUSHM.A	#7, R10
	SUBA	#500, R1
	; end of prologue
	MOVX.W	#23168, &WDTCTL
 ; 47 "core/src_compile/secureUpdate.c" 1
	dint { nop
 ; 0 "" 2
	MOVX.W	#0, &rcvBufCount
	MOV.W	#512, R14
	MOV.B	#0, R13
	MOVA	#rcvBuf, R12
	CALLA	#memset
	BISX.B	#48, &PBSEL_H
	BISX.B	#1, &UCA1CTLW0_L
	BISX.B	#64, &UCA1CTLW0_L
	MOVX.B	#3, &UCA1BRW_L
	MOVX.B	#6, &UCA1MCTL
	MOVX.B	#0, &UCA1CTLW0_H
	BICX.B	#1, &UCA1CTLW0_L
	BISX.B	#1, &UCA1ICTL_L
	MOVX.W	&elfAddress, R13
	MOVX.W	&elfAddress+2, R14
	PUSH.W	R14 { PUSH.W	R13 { POPM.A	#1, R12
	MOVX.W	#-23296, &FCTL3
	MOVX.W	#-23292, &FCTL1
	MOV.W	#0, @R12
.L201:
	BITX.W	#1, &FCTL3 { JNE	.L201
	MOVA	R1, R14
	ADDA	#36, R14
	MOVA	R14, @R1
	MOVA	R1, R6
	ADDA	#268, R6
	MOV.W	#65024, R10
	SUBA	R14, R10
.L202:
	MOVA	R10, R12
	ADDA	R14, R12
	MOV.W	@R12, @R14
	ADDA	#2, R14
	CMPA	R14, R6 { JNE	.L202
	MOVX.W	#-23296, &FCTL3
	MOVX.W	#-23294, &FCTL1
	MOV.W	#0, &65024
.L203:
	BITX.W	#1, &FCTL3 { JNE	.L203
	MOVX.W	#-23296, &FCTL3
	MOVX.W	#-23232, &FCTL1
	MOVA	#INTERRUPT_ISR, R12
	MOV.W	R12, &65500
	MOV.W	#-15360, &65534
	MOVA	R1, R14
	ADDA	#36, R14
.L204:
	MOVA	R10, R12
	ADDA	R14, R12
	MOV.W	@R14+, @R12
	CMPA	R14, R6 { JNE	.L204
 ; 125 "core/src_compile/secureUpdate.c" 1
	nop { eint { nop
 ; 0 "" 2
	BISX.B	#-128, &PBDIR_H
	ANDX.B	#127, &PBOUT_H
	BICX.B	#1, &PAOUT_L
	MOV.B	#10, R7
.L206:
	ADDX.B	#-128, &PBOUT_H
	MOV.W	#10000, R12
.L205:
 ; 138 "core/src_compile/secureUpdate.c" 1
	nop
 ; 0 "" 2
	ADD.W	#-1, R12
	CMP.W	#0, R12 { JNE	.L205
	ADD.W	#-1, R7
	CMP.W	#0, R7 { JNE	.L206
	BISX.B	#-128, &PBOUT_H
	MOV.B	#0, R9
	MOV.W	#-512, R11
	MOV.W	#0, 4(R1)
	MOV.W	#0, 6(R1)
	MOVX	&appBottomText, R15
	MOVA	R15, 24(R1)
	MOVA	@R1, R12
	MOVX	R12, 28(R1)
	MOVA	#oldISR+128, R4
	MOVX.W	&appTopText, R13
	MOV.W	#0,R14
	MOV.W	R13, 8(R1)
	MOV.W	R14, 10(R1)
	MOVX.W	&elfAddress, R14
	ADD	#1, R14 ; cy
	MOV.W	R14, 30(R1)
	MOVX.W	&elfAddress+2, R15
	ADDC	#0, R15
	MOV.W	R15, 32(R1)
.L207:
	MOVX.W	&rcvBufCount, R12
	MOV.B	#0, R5
	CMP.W	#2, R12 { JEQ	.L272
.L208:
	MOV.W	R9,R14 { MOV.W	#0,R15
	MOV.W	R14, 12(R1)
	MOV.W	R15, 14(R1)
.L210:
	MOVX.W	&rcvBufCount, R12
	CMP.W	#512, R12 { JEQ	.L212
.L274:
	MOVX.W	&rcvBufCount, R12
	MOV.W	#0,R13
	ADDX	4(R1), R12 ; cy
	ADDCX	6(R1), R13
	CMP.W	R9, R12 { JEQ	.L273
.L213:
	CMP.W	#0, R5 { JEQ	.L207
	MOV.W	6(R1), R12
	CMP.W	14(R1), R12 { JLO	.L210
	CMP.W	#0, R12 { JNE	.L238
	MOV.W	4(R1), R12
	CMP.W	12(R1), R12 { JLO	.L210
.L238:
	ANDX.B	#127, &PBOUT_H
	MOV.W	#0, 34(R1)
	BICX.B	#1, &UCA1ICTL_L
 ; 195 "core/src_compile/secureUpdate.c" 1
	dint { nop
 ; 0 "" 2
	MOVX.W	#-23296, &FCTL3
	MOVX.W	#-23292, &FCTL1
	MOVA	24(R1), R12
	MOV.W	#0, @R12
.L224:
	BITX.W	#1, &FCTL3 { JNE	.L224
	MOVX.W	&appBottomROdata, R13
	MOVX.W	&appBottomROdata+2, R14
	PUSH.W	R14 { PUSH.W	R13 { POPM.A	#1, R12
	MOVX.W	#-23296, &FCTL3
	MOVX.W	#-23292, &FCTL1
	MOV.W	#0, @R12
.L225:
	BITX.W	#1, &FCTL3 { JNE	.L225
	MOVX.W	#-23296, &FCTL3
	MOVX.W	#-23294, &FCTL1
	MOV.W	R11, R12
	MOV.W	#0, @R12
.L226:
	BITX.W	#1, &FCTL3 { JNE	.L226
	MOVX.W	#-23296, &FCTL3
	MOVX.W	#-23168, &FCTL1
	MOVA	R1, R14
	ADDA	#36, R14
	SUB.W	28(R1), R11
.L227:
	MOVX	R14, R12
	ADD.W	R11, R12
	MOV.W	R12, R12
	MOV.W	@R14+, @R12
	CMPA	R14, R6 { JNE	.L227
	MOVX.W	#-23296, &FCTL3
	MOVX.W	#-23168, &FCTL1
	MOVA	#oldISR, R14
	MOVX	R14, R12
	MOV.W	#-128, R13 { SUB.W	R12, R13
.L228:
	MOVX	R14, R12
	ADD.W	R13, R12
	MOV.W	R12, R12
	MOV.W	@R14+, @R12
	MOV.W	@R14+, 2(R12)
	CMPA	R14, R4 { JNE	.L228
	MOVX.W	&elfAddress, R14
	MOVX.W	&elfAddress+2, R15
	PUSH.W	R15 { PUSH.W	R14 { POPM.A	#1, R12
	MOV.B	@R12, R8
	CMP.B	#0, @R12 { JEQ	.L230
	MOV.W	30(R1), R12
	MOV.W	32(R1), R13
	PUSH.W	R13 { PUSH.W	R12 { POPM.A	#1, R10
	ADD.B	#-1, R8
	MOV.B	R8, R8
	MOVA	R8, R12
	RLAM.A	#3, R12
	ADDA	R12, R8
	MOVA	R10, R12
	ADDA	#9, R12
	ADDA	R12, R8
	BRA	#.L232
.L234:
	ADDA	#9, R10
	CMPA	R10, R8 { JEQ	.L230
.L232:
	CMP.B	#1, 6(R10) { JNE	.L234
	MOV.B	3(R10), R12
	RPT	#8 { RLAX.W	R12
	MOV.B	2(R10), R13
	BIS.W	R12, R13
	MOV.B	5(R10), R12
	RPT	#8 { RLAX.W	R12
	MOV.B	4(R10), R14
	BIS.W	R14, R12
	CMP.W	10(R1), R12 { JLO	.L239
	CMP.W	#0, R12 { JNE	.L234
	CMP.W	8(R1), R13 { JHS	.L234
.L239:
	MOVA	R1, R15
	ADDA	#34, R15
	MOVA	R10, R14
	MOVX.W	&elfAddress, R12
	MOVX.W	&elfAddress+2, R13
	CALLA	#load_elf_segment
	CMP.B	#0, R12 { JNE	.L234
 ; 244 "core/src_compile/secureUpdate.c" 1
	
	BR #secureUpdate
 ; 0 "" 2
.L230:
	MOV.W	34(R1), R12
	CALLA	#launchVerification
	MOV.W	#-128, R11
	MOVX.W	&rcvBufCount, R12
	CMP.W	#512, R12 { JNE	.L274
.L212:
	MOVX.W	&rcvBufCount, R10
	MOV.W	4(R1), R12
	ADDX	&elfAddress, R12 ; cy
	MOVA	4(R1), R8
	ADDX.A	&elfAddress, R8
	MOVX.W	#-23296, &FCTL3
	AND.B	#3, R12
	MOV.W	R12, 16(R1)
	MOV.W	#0, 18(R1)
	MOV.W	16(R1), R13
	MOV.W	18(R1), R14
	PUSH.W	R14 { PUSH.W	R13 { POPM.A	#1, R12
	CMPA	#0, R12 { JEQ	.L215
	MOVX.W	#-23232, &FCTL1
	MOVX.B	&rcvBuf+1, R12
	RPT	#8 { RLAX.W	R12
	MOVA	#rcvBuf, R14
	MOV.B	@R14, R15
	BIS.W	R12, R15
	MOV.W	R15, @R8
	ADDA	#2, R8
	ADD.W	#-2, R10
	MOVX.A	#rcvBuf+2, 20(R1)
.L216:
	MOV.W	R10, R15
	RRUM.W	#2, R15
	MOVA	20(R1), R14
	MOVA	R8, R12
	MOV.W	R7, R13
.L217:
	MOV.W	@R14+, @R12
	MOV.W	@R14+, 2(R12)
	ADDA	#4, R12
	ADD.W	#1, R13
	CMP.W	R15, R13 { JLO	.L217
	MOV.B	#1, R12
	CMP.W	#0, R15 { JEQ	.L219
	MOV.W	R15, R12
.L219:
	BIT.W	#3, R10 { JEQ	.L220
	MOVX.W	#-23232, &FCTL1
	RLAM.W	#1, R12
	MOV.W	R12, R12
	RLAM.A	#1, R12
	MOVA	20(R1), R14
	ADDA	R12, R14
	ADDA	R8, R12
	MOV.W	@R14, @R12
.L220:
	MOVX.W	&rcvBufCount, R12
	MOV.W	#0,R13
	MOV.W	4(R1), R14
	MOV.W	6(R1), R15
	ADD	R12, R14 ; cy
	ADDC	R13, R15
	MOV.W	R14, 4(R1)
	MOV.W	R15, 6(R1)
	MOVX.W	#0, &rcvBufCount
	BISX.B	#1, &UCA1ICTL_L
	MOVX.B	#84, &UCA1TXBUF
	BRA	#.L221
.L275:
	BITX.B	#1, &UCA1STAT { JEQ	.L213
.L221:
	BITX.B	#2, &UCA1ICTL_H { JEQ	.L275
	BRA	#.L213
.L273:
	CMP.W	14(R1), R13 { JNE	.L213
	CMP.W	#0, R5 { JNE	.L212
	MOVX.W	&rcvBufCount, R12
	MOV.B	#0, R5
	CMP.W	#2, R12 { JNE	.L208
.L272:
	MOVA	#rcvBuf, R13
	MOV.B	@R13, R12
	MOVX.B	&rcvBuf+1, R13
	RPT	#8 { RLAX.W	R12
	MOV.W	R12, R9
	BIS.W	R13, R9
	MOVX.W	#0, &rcvBufCount
	MOVX.B	#84, &UCA1TXBUF
	BRA	#.L211
.L209:
	BITX.B	#1, &UCA1STAT { JEQ	.L270
.L211:
	BITX.B	#2, &UCA1ICTL_H { JEQ	.L209
.L270:
	MOV.B	#1, R5
	BRA	#.L208
.L215:
	MOVX.W	#-23168, &FCTL1
	MOVX.A	#rcvBuf, 20(R1)
	BRA	#.L216
	.size	secureUpdate, .-secureUpdate
	.global	rcvBufCount
	.section .bss
	.balign 2
	.type	rcvBufCount, @object
	.size	rcvBufCount, 2
rcvBufCount:
	.zero	2
	.global	rcvBuf
	.type	rcvBuf, @object
	.size	rcvBuf, 512
rcvBuf:
	.zero	512
	.global	oldISR
	.section	.tcm:rodata,"a"
	.balign 2
	.type	oldISR, @object
	.size	oldISR, 128
oldISR:
	.long	-133629952
	.long	-132581360
	.long	-131532768
	.long	-130484176
	.long	-129435584
	.long	-128386992
	.long	-127338400
	.long	-126289808
	.long	-125241216
	.long	-124192624
	.long	-123144032
	.long	-122095440
	.long	-121046848
	.long	-119998256
	.long	-118949664
	.long	-117901072
	.long	-116852480
	.long	-115803888
	.long	-114755296
	.long	-113706704
	.long	-112658112
	.long	-111609520
	.long	-110560928
	.long	-109512336
	.long	-108463744
	.long	-107415152
	.long	-106366560
	.long	-105317968
	.long	-104269376
	.long	-103220784
	.long	-102172192
	.long	-1006568976
	.global	dataLengthBytes
	.type	dataLengthBytes, @object
	.size	dataLengthBytes, 1
dataLengthBytes:
	.byte	2
	.ident	"GCC: (Mitto Systems Limited - msp430-gcc 9.3.1.11) 9.3.1"
	.mspabi_attribute 4, 2
	.mspabi_attribute 6, 2
	.mspabi_attribute 8, 2
	.gnu_attribute 4, 2
