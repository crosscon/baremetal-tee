	.file	"core.c"
.text
	.section	.tcm:code,"ax",@progbits
	.balign 2
	.global	launchAppCode
	.type	launchAppCode, @function
launchAppCode:
; start of function
; attributes: 
; framesize_regs:     0
; framesize_locals:   0
; framesize_outgoing: 0
; framesize:          0
; elim ap -> fp       4
; elim fp -> sp       0
; saved regs:(none)
	; start of prologue
	; end of prologue
	ANDX.B	#127, &PBOUT_H
	BICX.B	#1, &PAOUT_L
 ; 142 "core/src_compile/core.c" 1
	nop { eint { nop
 ; 0 "" 2
 ; 146 "core/src_compile/core.c" 1
	mov #0x43ff, r1
 ; 0 "" 2
 ; 149 "core/src_compile/core.c" 1
	mov #0, r8
 ; 0 "" 2
	MOVX.W	#-23296, &FCTL3
	MOVX.W	#-23294, &FCTL1
 ; 152 "core/src_compile/core.c" 1
	MOV.W #0, &0xf600
 ; 0 "" 2
.L2:
	BITX.W	#1, &FCTL3 { JNE	.L2
	MOVX.W	#-23280, &FCTL3
 ; 158 "core/src_compile/core.c" 1
	
	BR #4400h
 ; 0 "" 2
	; start of epilogue
	RETA
	.size	launchAppCode, .-launchAppCode
	.balign 2
	.global	cfiCheck
	.type	cfiCheck, @function
cfiCheck:
; start of function
; attributes: 
; framesize_regs:     8
; framesize_locals:   8
; framesize_outgoing: 0
; framesize:          16
; elim ap -> fp       12
; elim fp -> sp       8
; saved regs: R9 R10
	; start of prologue
	PUSHM.A	#2, R10
	SUBA	#8, R1
	; end of prologue
	MOV.W	R12, R11
	MOV.W	R13, R12
	CMP.W	#-1024, R11 { JEQ	.L100
.L58:
	CMP.W	#-986, R11 { JEQ	.L101
.L59:
	MOV.W	R11, R13
	ADD	#948, R13 ; cy
	MOV.W	R12, R14
	ADDC	#-1, R14
	BIC.W	#8, R13
	BIS.W	R14, R13
	CMP.W	#0, R13 { JEQ	.L56
	CMP.W	#-756, R11 { JEQ	.L102
.L60:
	CMP.W	#-666, R11 { JEQ	.L103
.L61:
	CMP.W	#-594, R11 { JEQ	.L104
.L62:
	CMP.W	#-554, R11 { JEQ	.L105
.L63:
	CMP.W	#-536, R11 { JEQ	.L106
.L64:
	CMP.W	#-516, R11 { JEQ	.L107
.L65:
	CMP.W	#-498, R11 { JEQ	.L108
.L66:
	CMP.W	#-478, R11 { JEQ	.L109
.L67:
	CMP.W	#-460, R11 { JEQ	.L110
.L68:
	CMP.W	#-440, R11 { JEQ	.L111
.L69:
	CMP.W	#-422, R11 { JEQ	.L112
.L70:
	CMP.W	#-402, R11 { JEQ	.L113
.L71:
	CMP.W	#-384, R11 { JEQ	.L114
.L72:
	CMP.W	#-364, R11 { JEQ	.L115
.L73:
	CMP.W	#-346, R11 { JEQ	.L116
.L74:
	CMP.W	#-326, R11 { JEQ	.L117
.L75:
	CMP.W	#-308, R11 { JEQ	.L118
.L76:
	CMP.W	#-284, R11 { JEQ	.L119
.L28:
	CMP.W	#0, R12 { JNE	.L77
	MOV.W	#-15362, R12
	CMP.W	R11, R12 { JLO	.L77
	MOVX.B	&counterBuffAlwDst, R12
	MOVX.W	&counterAlwDst, R13
	ADD.W	#-1, R13
	RLAM.W	#1, R13
	RPT	#9 { RLAX.W	R12
	ADD.W	R12, R13
	CMP.W	#0, R13 { JL	.L77
	MOV.B	#0, R15
.L31:
	MOV.W	R15, R12
	ADD.W	R13, R12
	RRUM.W	#1, R12
	BIC.W	#1, R12
	MOVX.W	&cfiDataHolder, @R1
	MOVX.W	&cfiDataHolder+2, 2(R1)
	MOV.W	R12,R9 { MOV.W	#0,R10
	MOV.W	R9, 4(R1)
	MOV.W	R10, 6(R1)
	MOVA	4(R1), R14
	MOVA	@R1, R10
	ADDA	R10, R14
	MOV.W	@R14, R14
	CMP.W	R14, R11 { JEQ	.L56
	CMP.W	R11, R14 { JHS	.L29
	MOV.W	R12, R15
	ADD.W	#2, R15
	CMP.W	R15, R13 { JGE	.L31
.L77:
	MOV.B	#1, R12
.L120:
	; start of epilogue
	ADDA	#8, R1
	POPM.A	#2, r10
	RETA
.L101:
	CMP.W	#0, R12 { JNE	.L59
.L56:
	MOV.B	#0, R12
	; start of epilogue
	ADDA	#8, R1
	POPM.A	#2, r10
	RETA
.L100:
	CMP.W	#0, R13 { JNE	.L58
	BRA	#.L56
.L102:
	CMP.W	#0, R12 { JNE	.L60
	BRA	#.L56
.L105:
	CMP.W	#0, R12 { JNE	.L63
	BRA	#.L56
.L29:
	MOV.W	R12, R13
	ADD.W	#-2, R13
	CMP.W	R15, R13 { JGE	.L31
	MOV.B	#1, R12
	BRA	#.L120
.L103:
	CMP.W	#0, R12 { JNE	.L61
	BRA	#.L56
.L104:
	CMP.W	#0, R12 { JNE	.L62
	BRA	#.L56
.L106:
	CMP.W	#0, R12 { JNE	.L64
	BRA	#.L56
.L107:
	CMP.W	#0, R12 { JNE	.L65
	BRA	#.L56
.L108:
	CMP.W	#0, R12 { JNE	.L66
	BRA	#.L56
.L109:
	CMP.W	#0, R12 { JNE	.L67
	BRA	#.L56
.L110:
	CMP.W	#0, R12 { JNE	.L68
	BRA	#.L56
.L111:
	CMP.W	#0, R12 { JNE	.L69
	BRA	#.L56
.L113:
	CMP.W	#0, R12 { JNE	.L71
	BRA	#.L56
.L112:
	CMP.W	#0, R12 { JNE	.L70
	BRA	#.L56
.L115:
	CMP.W	#0, R12 { JNE	.L73
	BRA	#.L56
.L114:
	CMP.W	#0, R12 { JNE	.L72
	BRA	#.L56
.L119:
	CMP.W	#0, R12 { JNE	.L28
	BRA	#.L56
.L118:
	CMP.W	#0, R12 { JNE	.L76
	BRA	#.L56
.L117:
	CMP.W	#0, R12 { JNE	.L75
	BRA	#.L56
.L116:
	CMP.W	#0, R12 { JNE	.L74
	BRA	#.L56
	.size	cfiCheck, .-cfiCheck
	.balign 2
	.global	binarySearch
	.type	binarySearch, @function
binarySearch:
; start of function
; attributes: 
; framesize_regs:     8
; framesize_locals:   8
; framesize_outgoing: 0
; framesize:          16
; elim ap -> fp       12
; elim fp -> sp       8
; saved regs: R9 R10
	; start of prologue
	PUSHM.A	#2, R10
	SUBA	#8, R1
	; end of prologue
	CMP.W	R12, R13 { JL	.L128
.L126:
	MOV.W	R13, R15
	ADD.W	R12, R15
	RRUM.W	#1, R15
	BIC.W	#1, R15
	MOVX.W	&cfiDataHolder, @R1
	MOVX.W	&cfiDataHolder+2, 2(R1)
	MOV.W	R15,R9 { MOV.W	#0,R10
	MOV.W	R9, 4(R1)
	MOV.W	R10, 6(R1)
	MOVA	4(R1), R10
	MOVA	@R1, R11
	ADDA	R11, R10
	MOV.W	@R10, R10
	CMP.W	R14, R10 { JEQ	.L129
	CMP.W	R14, R10 { JHS	.L124
	MOV.W	R15, R12
	ADD.W	#2, R12
	CMP.W	R12, R13 { JGE	.L126
.L128:
	MOV.W	#-1, R12
	; start of epilogue
	ADDA	#8, R1
	POPM.A	#2, r10
	RETA
.L124:
	MOV.W	R15, R13
	ADD.W	#-2, R13
	CMP.W	R12, R13 { JGE	.L126
	BRA	#.L128
.L129:
	MOV.B	R15, R12
	SXT	R12
	; start of epilogue
	ADDA	#8, R1
	POPM.A	#2, r10
	RETA
	.size	binarySearch, .-binarySearch
	.balign 2
	.global	isImmediateSafeValue
	.type	isImmediateSafeValue, @function
isImmediateSafeValue:
; start of function
; attributes: 
; framesize_regs:     0
; framesize_locals:   0
; framesize_outgoing: 0
; framesize:          0
; elim ap -> fp       4
; elim fp -> sp       0
; saved regs:(none)
	; start of prologue
	; end of prologue
	MOV.W	R13, R15
	MOV.W	R12, R13
	MOV.W	R15, R14
	CMP.W	#-1024, R12 { JEQ	.L228
.L172:
	CMP.W	#-986, R13 { JEQ	.L229
.L173:
	MOV.W	R13, R12
	ADD	#948, R12 ; cy
	MOV.W	R14, R15
	ADDC	#-1, R15
	BIC.W	#8, R12
	BIS.W	R15, R12
	CMP.W	#0, R12 { JEQ	.L209
	CMP.W	#-756, R13 { JEQ	.L230
.L174:
	CMP.W	#-666, R13 { JEQ	.L231
.L175:
	CMP.W	#-594, R13 { JEQ	.L232
.L176:
	CMP.W	#-554, R13 { JEQ	.L233
.L177:
	CMP.W	#-536, R13 { JEQ	.L234
.L178:
	CMP.W	#-516, R13 { JEQ	.L235
.L179:
	CMP.W	#-498, R13 { JEQ	.L236
.L180:
	CMP.W	#-478, R13 { JEQ	.L237
.L181:
	CMP.W	#-460, R13 { JEQ	.L238
.L182:
	CMP.W	#-440, R13 { JEQ	.L239
.L183:
	CMP.W	#-422, R13 { JEQ	.L240
.L184:
	CMP.W	#-402, R13 { JEQ	.L241
.L185:
	CMP.W	#-384, R13 { JEQ	.L242
.L186:
	CMP.W	#-364, R13 { JEQ	.L243
.L187:
	CMP.W	#-346, R13 { JEQ	.L244
.L188:
	CMP.W	#-326, R13 { JEQ	.L245
.L189:
	CMP.W	#-308, R13 { JEQ	.L246
.L190:
	MOV.W	R13, R12
	XOR.W	#-284, R12
	BIS.W	R14, R12
	MOV.W	R12, R13
	ADD.W	#-1, R13
	BIC.W	R12, R13
	MOV.W	R13, R12
	RPT	#15 { RRUX.W	R12
	; start of epilogue
	RETA
.L229:
	CMP.W	#0, R14 { JNE	.L173
.L209:
	MOV.B	#1, R12
.L247:
	; start of epilogue
	RETA
.L228:
	CMP.W	#0, R15 { JNE	.L172
	MOV.B	#1, R12
	BRA	#.L247
.L230:
	CMP.W	#0, R14 { JNE	.L174
	MOV.B	#1, R12
	BRA	#.L247
.L233:
	CMP.W	#0, R14 { JNE	.L177
	MOV.B	#1, R12
	BRA	#.L247
.L231:
	CMP.W	#0, R14 { JNE	.L175
	MOV.B	#1, R12
	BRA	#.L247
.L232:
	CMP.W	#0, R14 { JNE	.L176
	MOV.B	#1, R12
	BRA	#.L247
.L234:
	CMP.W	#0, R14 { JNE	.L178
	MOV.B	#1, R12
	BRA	#.L247
.L235:
	CMP.W	#0, R14 { JNE	.L179
	MOV.B	#1, R12
	BRA	#.L247
.L236:
	CMP.W	#0, R14 { JNE	.L180
	MOV.B	#1, R12
	BRA	#.L247
.L237:
	CMP.W	#0, R14 { JNE	.L181
	MOV.B	#1, R12
	BRA	#.L247
.L238:
	CMP.W	#0, R14 { JNE	.L182
	MOV.B	#1, R12
	BRA	#.L247
.L239:
	CMP.W	#0, R14 { JNE	.L183
	MOV.B	#1, R12
	BRA	#.L247
.L240:
	CMP.W	#0, R14 { JNE	.L184
	MOV.B	#1, R12
	BRA	#.L247
.L241:
	CMP.W	#0, R14 { JNE	.L185
	MOV.B	#1, R12
	BRA	#.L247
.L242:
	CMP.W	#0, R14 { JNE	.L186
	MOV.B	#1, R12
	BRA	#.L247
.L243:
	CMP.W	#0, R14 { JNE	.L187
	MOV.B	#1, R12
	BRA	#.L247
.L244:
	CMP.W	#0, R14 { JNE	.L188
	MOV.B	#1, R12
	BRA	#.L247
.L246:
	CMP.W	#0, R14 { JNE	.L190
	MOV.B	#1, R12
	BRA	#.L247
.L245:
	CMP.W	#0, R14 { JNE	.L189
	MOV.B	#1, R12
	BRA	#.L247
	.size	isImmediateSafeValue, .-isImmediateSafeValue
	.balign 2
	.global	verify
	.type	verify, @function
verify:
; start of function
; attributes: 
; framesize_regs:     28
; framesize_locals:   84
; framesize_outgoing: 0
; framesize:          112
; elim ap -> fp       32
; elim fp -> sp       84
; saved regs: R4 R5 R6 R7 R8 R9 R10
	; start of prologue
	PUSHM.A	#7, R10
	SUBA	#84, R1
	; end of prologue
	MOV.W	R12, 20(R1)
	MOV.W	R13, 18(R1)
	AND	#0xff, R14
	MOV.W	R14, 16(R1)
	CMP.W	#-15361, R13 { JEQ	.L416
	MOV.W	#17408, R12
	MOV.B	#1, R13
.L249:
	MOVX.W	R12, &cfiDataHolder
	MOVX.W	R13, &cfiDataHolder+2
	CMP.W	#0, 16(R1) { JNE	.L250
	MOVX.W	#-23296, &FCTL3
	MOVX.W	#-23292, &FCTL1
	MOVX.W	&cfiDataHolder, R12
	MOVX.W	&cfiDataHolder+2, R13
	PUSH.W	R13 { PUSH.W	R12 { POPM.A	#1, R12
	MOV.W	#0, @R12
.L251:
	BITX.W	#1, &FCTL3 { JNE	.L251
	MOV.W	#256, R14
	MOV.B	#0, R13
	MOVA	#alwDst, R12
	CALLA	#memset
	MOVX.W	#0, &counterAlwDst
	MOVX.B	#0, &counterBuffAlwDst
	MOV.W	16(R1), R5
	CMP.W	18(R1), 20(R1) { JHS	.L494
.L252:
	MOV.W	20(R1), R7
	MOV.B	#0, R6
	MOV.W	#0, 34(R1)
	MOV.W	#0, 40(R1)
	MOV.W	#0, 50(R1)
	MOV.W	#0, 48(R1)
	MOV.B	#0, R12
	MOV.B	#0, R13
	MOV.W	R12, 44(R1)
	MOV.W	R13, 46(R1)
	MOV.W	R6, 28(R1)
	MOV.W	R6, 30(R1)
	MOV.W	#0, 26(R1)
	MOV.W	#0, 24(R1)
	MOV.B	#0, R5
	MOV.W	#0, 22(R1)
	MOV.B	#1, R4
	MOV.B	#0, R15
	MOV.W	R5, 42(R1)
	MOV.W	R7, R6
.L394:
	MOV.W	R6,R7 { MOV.W	#0,R8
	MOV.W	R7, 8(R1)
	MOV.W	R8, 10(R1)
	MOV.W	R6, R10
	MOV.W	@R10, R9
	ADD	#2, R7 ; cy
	MOV.W	R7, 12(R1)
	ADDC	#0, R8
	MOV.W	R8, 14(R1)
	MOVA	8(R1), R14
	MOV.W	2(R14), R7
	ADDA	#2, R14
	MOV.W	R9, R12
	AND.W	#-2048, R12
	MOV.W	R4, R11
	MOV.W	R15, R8
	CMP.W	#6144, R12 { JNE	.L254
	MOV.W	R9, R12
	RPT	#7 { RRUX.W	R12
	AND.B	#15, R12
	MOV.W	R12, 24(R1)
	AND.B	#15, R9
	MOV.W	R9, 26(R1)
	MOV.W	8(R1), R7
	ADD	#4, R7 ; cy
	MOV.W	10(R1), R9
	ADDC	#0, R9
	MOVA	8(R1), R8
	MOV.W	12(R1), 8(R1)
	MOV.W	14(R1), 10(R1)
	MOV.W	R7, 12(R1)
	MOV.W	R9, 14(R1)
	MOV.W	@R10, 32(R1)
	MOV.W	@R14, R9
	MOV.W	4(R8), R7
	MOV.B	#2, R11
	MOV.W	R4, R8
.L254:
	MOV.W	R9, R13
	AND.W	#-256, R13
	MOV.W	R9, R12
	AND.W	#-512, R12
	CMP.W	#4096, R12 { JEQ	.L640
	MOV.W	R9, R14
	AND.W	#-64, R14
	CMP.W	#4608, R14 { JEQ	.L641
	CMP.W	#5120, R12 { JEQ	.L482
	CMP.W	#4736, R14 { JEQ	.L642
	CMP.W	#16688, R9 { JEQ	.L482
	CMP.W	#4864, R9 { JEQ	.L482
	CMP.W	#272, R9 { JEQ	.L482
	MOV.W	R9, R14
	ADD.W	#-8192, R14
	MOV.W	#8191, R10
	CMP.W	R14, R10 { JLO	.L278
	MOV.W	R9, R12
	AND.W	#1023, R12
	RRUM.W	#2, R9
	CMP.B	#0, R9 { JL	.L279
	MOV.W	R12,R7 { MOV.W	#0,R8
	MOV.W	R7, 52(R1)
	MOV.W	R8, 54(R1)
.L280:
	MOV.W	52(R1), R12
	ADD	R12, R12 ; cy
	MOV.W	54(R1), R13
	ADDC	R13, R13
	ADDX	12(R1), R12 ; cy
	ADDCX	14(R1), R13
	CMP.W	#0, 16(R1) { JNE	.L615
	ADD	#-17408, R12 ; cy
	ADDC	#-1, R13
	CMP.W	#0, R13 { JNE	.L617
	MOV.W	#32766, R8
	CMP.W	R12, R8 { JHS	.L258
.L617:
	MOV.B	#1, R5
.L494:
	MOV.B	R5, R12
	; start of epilogue
	ADDA	#84, R1
	POPM.A	#7, r10
	RETA
.L640:
	BIT.W	#63, R9 { JEQ	.L482
	MOV.W	R9, R13
	AND.B	#48, R13
	MOV.W	R9, R12
	AND.B	#15, R12
	BIT.W	#48, R9 { JEQ	.L630
	CMP.W	#32, R13 { JEQ	.L630
	CMP.W	#48, R13 { JEQ	.L643
	CMP.W	#8, R12 { JEQ	.L482
.L261:
	ADD.B	#1, R11
	AND	#0xff, R11
.L258:
	ADD.W	R11, R5
	MOV.W	R5, R13
	RLAM.W	#1, R13
	ADD.W	20(R1), R13
	CMP.W	#0, 16(R1) { JNE	.L387
.L403:
	MOVX.W	&counterAlwDst, R12
	MOV.W	R12, R14
	ADD.W	#1, R14
	MOVX.W	R14, &counterAlwDst
	MOV.W	R12, R12
	RLAM.A	#1, R12
	MOVX.W	R6, alwDst(R12)
	MOVX.W	&counterAlwDst, R12
	MOV.B	#255, R7
	CMP.W	R12, R7 { JLO	.L644
	CMP.W	18(R1), R13 { JHS	.L645
.L391:
	MOV.W	R13, R6
	BRA	#.L394
.L645:
	MOVX.B	&counterBuffAlwDst, R12
	MOVX.W	&cfiDataHolder, 8(R1)
	MOVX.W	&cfiDataHolder+2, 10(R1)
	MOVX.W	#-23296, &FCTL3
	MOVX.W	#-23168, &FCTL1
	RPT	#9 { RLAX.W	R12
	MOV.W	R12, R13 { MOV.W	R12, R14 { RPT	#15 { RRAX.W	R14
	MOV.W	R13, 12(R1)
	MOV.W	R14, 14(R1)
	MOVA	12(R1), R14
	MOVA	8(R1), R7
	ADDA	R7, R14
	MOV.B	#0, R12
.L392:
	MOV.B	R12, R10
	RLAM.A	#2, R10
	MOVA	R10, R8
	ADDA	R14, R8
	MOVX.W	alwDst(R10), @R8
	MOVX.W	alwDst+2(R10), 2(R8)
	ADD.B	#1, R12
	AND	#0xff, R12
	MOVX.W	&counterAlwDst, R13
	RRUM.W	#1, R13
	CMP.W	R13, R12 { JLO	.L392
	BITX.W	#1, &counterAlwDst { JEQ	.L618
	MOVX.W	#-23232, &FCTL1
	RLAM.W	#1, R12
	RLAM.A #4, R12 { RRAM.A #4, R12
	RLAM.A	#1, R12
	ADDA	R12, R14
	MOVX.W	alwDst(R12), @R14
.L618:
	MOV.B	#0, R5
.L648:
	MOV.B	R5, R12
	; start of epilogue
	ADDA	#84, R1
	POPM.A	#7, r10
	RETA
.L666:
	CMP.W	#48, R9 { JEQ	.L370
	CMP.W	#560, R9 { JEQ	.L371
.L482:
	MOV.B	#1, R5
.L256:
	CMP.W	#0, 16(R1) { JEQ	.L494
	MOV.W	22(R1), R5
	MOV.B	R5, R12
	; start of epilogue
	ADDA	#84, R1
	POPM.A	#7, r10
	RETA
.L644:
	MOVX.B	&counterBuffAlwDst, R12
	MOVX.W	&cfiDataHolder, 8(R1)
	MOVX.W	&cfiDataHolder+2, 10(R1)
	MOVX.W	#-23296, &FCTL3
	MOVX.W	#-23168, &FCTL1
	RPT	#9 { RLAX.W	R12
	MOV.W	R12, R10 { MOV.W	R12, R11 { RPT	#15 { RRAX.W	R11
	MOV.W	R10, 36(R1)
	MOV.W	R11, 38(R1)
	MOVA	36(R1), R8
	MOVA	8(R1), R11
	ADDA	R11, R8
	MOV.W	R15, R12
.L389:
	MOV.B	R12, R14
	RLAM.A	#2, R14
	MOVA	R14, R10
	ADDA	R8, R10
	MOVX.W	alwDst(R14), @R10
	MOVX.W	alwDst+2(R14), 2(R10)
	ADD.B	#1, R12
	AND	#0xff, R12
	MOVX.W	&counterAlwDst, R14
	RRUM.W	#1, R14
	CMP.W	R14, R12 { JLO	.L389
	BITX.W	#1, &counterAlwDst { JEQ	.L390
	MOVX.W	#-23232, &FCTL1
	RLAM.W	#1, R12
	RLAM.A #4, R12 { RRAM.A #4, R12
	RLAM.A	#1, R12
	ADDA	R12, R8
	MOVX.W	alwDst(R12), @R8
.L390:
	MOVX.W	R15, &counterAlwDst
	ADDX.B	#1, &counterBuffAlwDst
.L387:
	CMP.W	18(R1), R13 { JLO	.L391
	MOV.B	#0, R5
	BRA	#.L256
.L643:
	CMP.W	#0, R12 { JEQ	.L261
.L630:
	CMP.W	#8, R12 { JNE	.L258
	BRA	#.L482
.L641:
	MOV.W	R9, R14
	AND.B	#48, R14
	CMP.W	#0, 16(R1) { JNE	.L263
	CMP.W	#48, R14 { JEQ	.L646
.L264:
	MOV.W	R9, R12
	AND.B	#63, R12
	CMP.W	#16, R12 { JEQ	.L647
	CMP.W	#18, R12 { JNE	.L617
	MOV.W	R7, R12
	MOV.W	@R12, R12
	AND.W	#-256, R12
	CMP.W	#-23296, R12 { JEQ	.L617
.L263:
	BIT.W	#16, R9 { JEQ	.L258
	CMP.W	#48, R14 { JNE	.L261
	BRA	#.L265
.L250:
	CMP.W	18(R1), 20(R1) { JLO	.L252
	MOV.B	#0, R5
	BRA	#.L648
.L416:
	MOV.W	#-15360, R12
	MOV.B	#1, R13
	BRA	#.L249
.L642:
	CMP.W	#0, 16(R1) { JEQ	.L649
	BIT.W	#16, R9 { JNE	.L411
.L412:
	AND.B	#63, R9
	MOV.W	R7,R12 { MOV.W	#0,R13
	CMP.W	#48, R9 { JEQ	.L615
	CMP.W	#16, R9 { JEQ	.L624
	CMP.W	#18, R9 { JNE	.L258
	MOV.W	R7, R12
	MOV.W	@R12, R12
	MOV.W	#0,R13
.L615:
	MOVA	R11, 4(R1)
	MOVA	R15, @R1
	CALLA	#cfiCheck
	AND	#0xff, R12
	MOV.W	R12, 22(R1)
	MOVA	4(R1), R11
	MOVA	@R1, R15
.L276:
	CMP.W	#1, 22(R1) { JNE	.L258
	MOV.B	#0, R5
	BRA	#.L256
.L647:
	MOV.W	R7,R12 { MOV.W	#0,R13
	MOV.W	R12, 8(R1)
	MOV.W	R13, 10(R1)
	MOVA	8(R1), R12
	MOVA	12(R1), R13
	ADDA	R13, R12
	MOV.W	@R12, R12
	AND.W	#-256, R12
	CMP.W	#-23296, R12 { JNE	.L263
	BRA	#.L617
.L646:
	MOV.W	R7, R12
	AND.W	#-256, R12
	CMP.W	#-23296, R12 { JEQ	.L264
.L265:
	BIT.W	#15, R9 { JNE	.L258
	BRA	#.L261
.L649:
	MOV.W	R9, R12
	AND.B	#63, R12
	CMP.W	#48, R12 { JEQ	.L650
.L271:
	CMP.W	#0, 42(R1) { JNE	.L610
	MOV.W	R4, 42(R1)
.L272:
	BIT.W	#16, R9 { JEQ	.L258
.L411:
	MOV.W	R9, R12
	AND.B	#48, R12
	CMP.W	#48, R12 { JEQ	.L651
.L273:
	ADD.B	#1, R11
	AND	#0xff, R11
.L274:
	CMP.W	#0, 16(R1) { JNE	.L412
	BRA	#.L258
.L278:
	MOV.W	R9, R14
	AND.W	#-4096, R14
	MOV.W	R14, R10
	ADD.W	#-16384, R10
	MOV.W	R10, 36(R1)
	MOV.W	#-20480, R10
	CMP.W	36(R1), R10 { JHS	.L652
	CMP.W	#4864, R13 { JEQ	.L653
	CMP.W	#0, R14 { JNE	.L363
	MOV.W	R9, R12
	RRUM.W	#4, R12
	MOV.W	R9, R10
	AND.B	#240, R10
	BIT.W	#12, R12 { JEQ	.L364
	AND.B	#15, R12
	MOV.W	R12, R13
	ADD.W	#-6, R13
	MOV.B	#2, R8
	CMP.W	R13, R8 { JHS	.L364
	CMP.W	#192, R10 { JEQ	.L654
	ADD.W	#-9, R12
	MOV.B	#2, R13
	CMP.W	R12, R13 { JLO	.L471
	ADD.B	#1, R11
	AND	#0xff, R11
	MOV.B	#0, R12
	MOV.W	R9, R14
	AND.B	#224, R14
.L383:
	MOV.W	R9, R13
	AND.B	#160, R13
	CMP.W	#160, R13 { JEQ	.L384
	CMP.W	#64, R14 { JNE	.L385
.L384:
	AND.B	#15, R9
	CMP.W	#8, R9 { JEQ	.L482
.L385:
	CMP.W	#0, R12 { JEQ	.L276
	MOV.W	R12, R5
	BRA	#.L256
.L279:
	BIS.W	#-1024, R12
	MOV.W	R12, 52(R1)
	MOV.W	#-1, 54(R1)
	BRA	#.L280
.L652:
	MOV.W	8(R1), R14
	ADD	#4, R14 ; cy
	MOV.W	R14, 60(R1)
	MOV.W	10(R1), R10
	ADDC	#0, R10
	MOV.W	R10, 82(R1)
	MOVA	8(R1), R12
	MOV.W	4(R12), 36(R1)
	MOV.W	R7,R12 { MOV.W	#0,R13
	MOV.W	R12, 8(R1)
	MOV.W	R13, 10(R1)
	MOV.W	R9, R12
	AND.B	#48, R12
	MOV.W	R9, R10
	AND.W	#3888, R10
	CMP.W	#16, R12 { JEQ	.L284
	CMP.W	#48, R10 { JEQ	.L285
.L432:
	MOV.W	12(R1), R13
	MOV.W	14(R1), R14
	MOV.W	R13, 60(R1)
	MOV.W	R14, 82(R1)
	MOV.W	8(R1), 36(R1)
	MOV.W	10(R1), 38(R1)
.L286:
	CMP.W	#0, R8 { JEQ	.L287
	MOV.W	8(R1), 28(R1)
	MOV.W	24(R1), R14
	BIS.W	10(R1), R14
	MOV.W	R14, 30(R1)
	MOV.W	28(R1), 44(R1)
	MOV.W	30(R1), 46(R1)
	MOV.W	36(R1), 50(R1)
	MOV.W	26(R1), R14
	BIS.W	38(R1), R14
	MOV.W	R14, 48(R1)
	MOV.W	36(R1), 34(R1)
	MOV.W	R14, 40(R1)
.L287:
	MOV.W	R9, R13
	AND.W	#-3953, R13
	CMP.W	#16384, R13 { JEQ	.L655
	CMP.W	#0, 16(R1) { JNE	.L328
	CMP.W	#20480, R13 { JEQ	.L617
	MOV.W	R9, R12
	AND.W	#-8049, R12
	MOV.W	R9, R13
	AND.W	#24719, R13
	CMP.W	#24576, R13 { JEQ	.L617
	MOV.W	R9, R13
	AND.W	#-12145, R13
	CMP.W	#-32768, R13 { JEQ	.L617
	CMP.W	#-16384, R12 { JEQ	.L617
.L414:
	BIT.W	#64, R9 { JNE	.L328
	MOV.B	#0, R14
.L306:
	MOV.W	R9, R7
	AND.W	#-3904, R7
	MOV.W	R9, R12
	AND.W	#-16192, R12
	CMP.W	#16512, R12 { JEQ	.L338
	CMP.W	#-8064, R7 { JNE	.L656
.L338:
	MOV.W	R9, R12
	AND.B	#143, R12
	CMP.W	#128, R12 { JEQ	.L657
	CMP.W	#130, R12 { JEQ	.L658
	BIT.W	#128, R9 { JNE	.L342
	CMP.B	#1, R14 { JEQ	.L342
.L358:
	AND.B	#15, R9
	CMP.W	#8, R9 { JNE	.L276
	BRA	#.L482
.L650:
	MOV.W	R7,R12 { MOV.W	#0,R13
	MOVA	R11, 4(R1)
	MOVA	R15, @R1
	CALLA	#isImmediateSafeValue
	MOVA	4(R1), R11
	MOVA	@R1, R15
	CMP.B	#0, R12 { JNE	.L272
	BRA	#.L271
.L610:
	MOV.W	42(R1), R5
	BRA	#.L494
.L653:
	MOV.W	R9, R12
	AND.B	#240, R12
	CMP.W	#176, R12 { JEQ	.L659
	CMP.W	#0, 16(R1) { JEQ	.L258
	CMP.W	#144, R12 { JEQ	.L624
	CMP.W	#128, R12 { JNE	.L258
	MOVA	44(R1), R12
	MOVA	12(R1), R14
	ADDA	R14, R12
	MOV.W	2(R12), R13
	MOV.W	@R12, R12
	BRA	#.L615
.L363:
	CMP.W	#0, 16(R1) { JNE	.L258
	CMP.W	#5632, R12 { JNE	.L258
	MOV.W	R9, R12
	AND.B	#15, R12
	CMP.W	#8, R12 { JEQ	.L617
	BIT.W	#239, R9 { JEQ	.L617
	ADD.W	R11, R5
	MOV.W	R5, R13
	RLAM.W	#1, R13
	ADD.W	20(R1), R13
	BRA	#.L403
.L651:
	BIT.W	#15, R9 { JNE	.L274
	BRA	#.L273
.L364:
	MOV.W	R9, R14
	AND.B	#15, R14
	MOV.W	R14, 8(R1)
	BIT.W	#15, R9 { JEQ	.L660
.L367:
	MOV.W	R9, R14
	AND.B	#224, R14
	CMP.W	#32, R10 { JNE	.L409
.L401:
	ADD.B	#1, R11
	AND	#0xff, R11
.L382:
	MOV.W	8(R1), R13
	XOR.W	#8, R13
	MOV.W	R13, R12
	ADD.W	#-1, R12
	BIC.W	R13, R12
	RPT	#15 { RRUX.W	R12
	BRA	#.L383
.L624:
	MOV.W	R7, R12 { MOV.W	R7, R13 { RPT	#15 { RRAX.W	R13
	MOV.W	R12, 8(R1)
	MOV.W	R13, 10(R1)
	MOVA	8(R1), R12
	MOVA	12(R1), R13
	ADDA	R13, R12
	MOV.W	@R12, R12
	MOV.W	#0,R13
	BRA	#.L615
.L284:
	CMP.W	#784, R10 { JEQ	.L432
	MOV.W	R9, R13
	AND.W	#3632, R13
	CMP.W	#560, R13 { JEQ	.L432
.L285:
	MOV.W	36(R1), R13
	MOV.W	#0,R14
	MOV.W	R13, 36(R1)
	MOV.W	R14, 38(R1)
	ADD.B	#1, R11
	AND	#0xff, R11
	BRA	#.L286
.L655:
	CMP.W	#48, R10 { JEQ	.L289
	CMP.W	#816, R10 { JEQ	.L433
	CMP.W	#768, R10 { JEQ	.L434
	CMP.W	#784, R10 { JEQ	.L435
	CMP.W	#800, R10 { JEQ	.L436
	CMP.W	#544, R10 { JEQ	.L437
	CMP.W	#560, R10 { JEQ	.L661
	CMP.W	#0, R12 { JEQ	.L636
	CMP.W	#16, R10 { JEQ	.L662
	CMP.W	#528, R10 { JEQ	.L663
	CMP.W	#32, R12 { JEQ	.L636
	CMP.W	#48, R12 { JEQ	.L636
.L305:
	CMP.W	#0, 16(R1) { JEQ	.L397
.L327:
	MOV.W	R9, R12
	AND.B	#63, R12
	CMP.W	#16, R12 { JEQ	.L664
	CMP.W	#18, R12 { JEQ	.L665
.L328:
	BIT.W	#128, R9 { JEQ	.L358
	ADD.B	#1, R11
	AND	#0xff, R11
	BRA	#.L358
.L660:
	MOV.W	R9, R14
	AND.B	#224, R14
	CMP.W	#96, R14 { JEQ	.L368
	CMP.W	#192, R10 { JEQ	.L482
	CMP.W	#48, R10 { JEQ	.L666
	CMP.W	#0, R14 { JEQ	.L482
	CMP.W	#48, R9 { JEQ	.L370
	CMP.W	#32, R10 { JNE	.L376
	MOV.W	R9, R8
	RPT	#8 { RRUX.W	R8
	MOV.W	R8, 24(R1)
	MOV.W	R7, 28(R1)
	MOV.W	R8, R12
	MOV.W	R8, 30(R1)
	MOV.W	R7, R13
	ADD	#-17408, R13 ; cy
	ADDC	#-1, R12
	CMP.W	#0, R12 { JNE	.L482
	MOV.W	#32767, R7
	CMP.W	R13, R7 { JLO	.L482
	MOV.W	28(R1), R12
	MOV.W	30(R1), R13
	PUSH.W	R13 { PUSH.W	R12 { POPM.A	#1, R8
	MOV.W	@R8, R13
	ADD	#-17408, R13 ; cy
	MOV.W	2(R8), R12
	ADDC	#-1, R12
	CMP.W	#0, R12 { JNE	.L482
	CMP.W	R13, R7 { JLO	.L482
	CMP.W	#0, 16(R1) { JEQ	.L401
	MOV.W	@R8, R12
	MOV.W	2(R8), R13
.L614:
	MOVA	R11, 4(R1)
	MOVA	R15, @R1
	CALLA	#cfiCheck
	AND	#0xff, R12
	MOV.W	R12, 22(R1)
	MOVA	4(R1), R11
	MOVA	@R1, R15
.L368:
	ADD.B	#1, R11
	AND	#0xff, R11
	CMP.W	#96, R10 { JEQ	.L276
	MOV.W	R9, R14
	AND.B	#224, R14
	BRA	#.L382
.L659:
	AND.B	#15, R9
	MOV.B	R9, R8
	MOV.W	R8, 24(R1)
	MOV.W	R7, 28(R1)
	MOV.W	R9, R10
	AND.B	#15, R10
	MOV.W	R10, 30(R1)
	MOV.W	28(R1), R12
	MOV.W	30(R1), R13
	MOVA	R11, 4(R1)
	MOVA	R15, @R1
	CALLA	#isImmediateSafeValue
	MOVA	4(R1), R11
	MOVA	@R1, R15
	CMP.B	#0, R12 { JNE	.L361
	CMP.W	#0, 42(R1) { JNE	.L611
	MOV.W	R4, 42(R1)
.L361:
	ADD.B	#1, R11
	AND	#0xff, R11
	CMP.W	#0, 16(R1) { JEQ	.L258
	MOV.W	28(R1), R12
	MOV.W	30(R1), R13
	BRA	#.L615
.L654:
	MOV.W	R9, R7
	AND.B	#15, R7
	MOV.W	R7, 8(R1)
	BIT.W	#15, R9 { JEQ	.L482
.L409:
	MOV.W	R9, R12
	AND.B	#176, R12
	CMP.W	#48, R12 { JEQ	.L368
	MOV.W	R9, R14
	AND.B	#224, R14
	MOV.W	R10, R12
	ADD.W	#-96, R12
	BIT.W	#-48, R12 { JNE	.L382
	BRA	#.L368
.L611:
	MOV.W	42(R1), R5
	BRA	#.L256
.L471:
	MOV.B	#0, R12
	MOV.W	R9, R14
	AND.B	#224, R14
	BRA	#.L383
.L397:
	MOV.W	R9, R12
	AND.W	#-12145, R12
	CMP.W	#-32768, R12 { JNE	.L414
	MOV.B	#1, R5
	BRA	#.L494
.L636:
	CMP.W	#0, 16(R1) { JNE	.L482
	BIT.W	#64, R9 { JNE	.L617
.L297:
	MOV.W	R9, R7
	AND.W	#-3904, R7
	MOV.B	#1, R14
	MOV.W	R9, R12
	AND.W	#-16192, R12
	CMP.W	#16512, R12 { JEQ	.L338
	MOV.W	R9, R12
	AND.W	#-12096, R12
	CMP.W	#-32640, R12 { JEQ	.L338
	MOV.B	#1, R5
	BRA	#.L494
.L434:
	MOV.W	#0, 56(R1)
	MOV.W	#0, 58(R1)
.L290:
	MOV.W	56(R1), R12
	MOV.W	58(R1), R13
	MOVA	R11, 4(R1)
	MOVA	R15, @R1
	CALLA	#isImmediateSafeValue
	MOVA	4(R1), R11
	MOVA	@R1, R15
	CMP.B	#0, R12 { JEQ	.L636
.L295:
	CMP.W	#0, 16(R1) { JEQ	.L397
	MOV.W	R9, R12
	AND.W	#3376, R12
	CMP.W	#48, R12 { JEQ	.L326
	CMP.W	#816, R10 { JEQ	.L326
	MOV.W	R9, R12
	AND.W	#3872, R12
	CMP.W	#768, R12 { JEQ	.L326
	MOV.W	R9, R12
	AND.W	#3632, R12
	CMP.W	#544, R12 { JNE	.L327
.L326:
	MOV.W	56(R1), R12
	MOV.W	58(R1), R13
.L613:
	MOVA	R11, 4(R1)
	MOVA	R15, @R1
	CALLA	#cfiCheck
	AND	#0xff, R12
	MOV.W	R12, 22(R1)
	MOVA	4(R1), R11
	MOVA	@R1, R15
	BRA	#.L328
.L433:
	MOV.W	#-1, 56(R1)
	MOV.W	#-1, 58(R1)
	BRA	#.L290
.L435:
	MOV.W	#1, 56(R1)
	MOV.W	#0, 58(R1)
	BRA	#.L290
.L289:
	MOV.W	R9, R12
	AND.B	#64, R12
	CMP.W	#0, R8 { JEQ	.L667
	CMP.W	#0, R12 { JEQ	.L612
	BIT.W	#64, 32(R1) { JNE	.L294
.L612:
	MOV.W	28(R1), 56(R1)
	MOV.W	30(R1), 58(R1)
.L399:
	MOV.W	56(R1), R13
	ADD	#-17408, R13 ; cy
	MOV.W	58(R1), R12
	ADDC	#-1, R12
	CMP.W	#0, R12 { JNE	.L290
	MOV.W	#32767, R12
	CMP.W	R13, R12 { JHS	.L295
	BRA	#.L290
.L667:
	CMP.W	#0, R12 { JEQ	.L668
	MOV.W	R7, R12
	AND.B	#255, R12
	MOV.W	R12,R13 { MOV.W	#0,R14
	MOV.W	R13, 56(R1)
	MOV.W	R14, 58(R1)
	BRA	#.L290
.L294:
	MOV.W	28(R1), R14
	AND.B	#255, R14
	MOV.W	R14, 56(R1)
	MOV.W	#0, 58(R1)
	BRA	#.L290
.L668:
	MOV.W	8(R1), 56(R1)
	MOV.W	10(R1), 58(R1)
	BRA	#.L399
.L376:
	CMP.W	#128, R10 { JNE	.L371
	MOV.W	R9, R14
	RPT	#8 { RRUX.W	R14
	MOV.W	R14, 24(R1)
	MOV.W	R7, 28(R1)
	MOV.W	R14, R8
	MOV.W	R14, 30(R1)
	MOV.W	R7, R13
	ADD	#-17408, R13 ; cy
	MOV.W	R14, R12
	ADDC	#-1, R12
	CMP.W	#0, R12 { JNE	.L493
	MOV.W	#32767, R12
	CMP.W	R13, R12 { JHS	.L380
.L493:
	MOV.W	28(R1), R12
	MOV.W	30(R1), R13
	MOVA	R11, 4(R1)
	MOVA	R15, @R1
	CALLA	#isImmediateSafeValue
	MOVA	4(R1), R11
	MOVA	@R1, R15
	CMP.B	#0, R12 { JEQ	.L482
.L380:
	MOV.W	R7,R12 { MOV.W	#0,R13
	CMP.W	#0, 16(R1) { JNE	.L614
	BRA	#.L409
.L371:
	CMP.W	#0, 16(R1) { JEQ	.L367
	BRA	#.L409
.L370:
	MOV.W	R7, R12 { MOV.W	R7, R13 { RPT	#15 { RRAX.W	R13
	MOV.W	R12, R7
	ADDX	12(R1), R7 ; cy
	MOV.W	R7, 78(R1)
	MOV.W	R13, R8
	ADDCX	14(R1), R8
	MOV.W	R8, 80(R1)
	MOV.W	R7, R13
	ADD	#-17408, R13 ; cy
	MOV.W	R8, R12
	ADDC	#-1, R12
	CMP.W	#0, R12 { JNE	.L482
	MOV.W	#32767, R12
	CMP.W	R13, R12 { JLO	.L482
	MOV.W	78(R1), R7
	MOV.W	80(R1), R8
	PUSH.W	R8 { PUSH.W	R7 { POPM.A	#1, R14
	MOV.W	@R14, R13
	ADD	#-17408, R13 ; cy
	MOV.W	2(R14), R12
	ADDC	#-1, R12
	CMP.W	#0, R12 { JNE	.L482
	MOV.W	#32767, R8
	CMP.W	R13, R8 { JLO	.L482
	CMP.W	#0, 16(R1) { JEQ	.L367
	MOV.W	@R14, R12
	MOV.W	2(R14), R13
	BRA	#.L614
.L663:
	CMP.W	#0, R8 { JNE	.L314
	MOV.W	R7, R12
	ADD.W	#-17408, R12
	CMP.W	#0, R12 { JL	.L636
	BIT.W	#64, R9 { JNE	.L482
	MOV.W	R7, R13
	RLAM.A #4, R13 { RRAM.A #4, R13
	MOV.W	@R13, R12
	ADD.W	#-17408, R12
	CMP.W	#0, R12 { JGE	.L305
.L622:
	CMP.W	#0, 16(R1) { JNE	.L482
	MOV.B	#1, R14
	BRA	#.L306
.L662:
	CMP.W	#0, R8 { JNE	.L301
	MOV.W	R7, R12 { MOV.W	R7, R13 { RPT	#15 { RRAX.W	R13
	MOV.W	R12, R14
	ADDX	12(R1), R14 ; cy
	MOV.W	R14, 66(R1)
	MOV.W	R13, R14
	ADDCX	14(R1), R14
	MOV.W	R14, 68(R1)
	MOV.W	66(R1), R13
	ADD	#-17408, R13 ; cy
	MOV.W	R14, R12
	ADDC	#-1, R12
	CMP.W	#0, R12 { JNE	.L636
	MOV.W	#32767, R12
	CMP.W	R13, R12 { JLO	.L636
	BIT.W	#64, R9 { JNE	.L482
	MOV.W	66(R1), R13
	MOV.W	68(R1), R14
	PUSH.W	R14 { PUSH.W	R13 { POPM.A	#1, R12
	MOV.W	@R12, R12
	ADD.W	#-17408, R12
	CMP.W	#0, R12 { JGE	.L305
	BRA	#.L622
.L314:
	MOV.W	28(R1), R13
	ADD	#-17408, R13 ; cy
	MOV.W	30(R1), R12
	ADDC	#-1, R12
	CMP.W	#0, R12 { JNE	.L486
	MOV.W	#32767, R14
	CMP.W	R13, R14 { JLO	.L486
	MOV.W	32(R1), R12
	AND.B	#64, R12
	BIT.W	#64, R9 { JNE	.L669
	CMP.W	#0, R12 { JEQ	.L305
	MOV.W	28(R1), R13
	MOV.W	30(R1), R14
	PUSH.W	R14 { PUSH.W	R13 { POPM.A	#1, R12
	MOV.W	@R12, R12
	ADD.W	#-17408, R12
	CMP.W	#0, R12 { JGE	.L305
.L623:
	CMP.W	#0, 16(R1) { JNE	.L449
	MOV.W	R8, R14
	BRA	#.L306
.L301:
	MOV.W	44(R1), R14
	ADDX	12(R1), R14 ; cy
	MOV.W	R14, 62(R1)
	MOV.W	46(R1), R12
	ADDCX	14(R1), R12
	MOV.W	R12, 64(R1)
	MOV.W	R14, R13
	ADD	#-17408, R13 ; cy
	ADDC	#-1, R12
	CMP.W	#0, R12 { JNE	.L486
	MOV.W	#32767, R14
	CMP.W	R13, R14 { JLO	.L486
	MOV.W	32(R1), R12
	AND.B	#64, R12
	BIT.W	#64, R9 { JNE	.L670
	CMP.W	#0, R12 { JEQ	.L305
	MOV.W	62(R1), R13
	MOV.W	64(R1), R14
	PUSH.W	R14 { PUSH.W	R13 { POPM.A	#1, R12
	MOV.W	@R12, R12
	ADD.W	#-17408, R12
	CMP.W	#0, R12 { JGE	.L305
	BRA	#.L623
.L670:
	CMP.W	#0, R12 { JNE	.L449
	MOV.W	62(R1), R13
	MOV.W	64(R1), R14
.L626:
	PUSH.W	R14 { PUSH.W	R13 { POPM.A	#1, R12
	MOV.W	@R12, R13
	ADD	#-17408, R13 ; cy
	MOV.W	2(R12), R12
	ADDC	#-1, R12
	CMP.W	#0, R12 { JNE	.L449
	MOV.W	#32767, R14
	CMP.W	R13, R14 { JHS	.L305
.L449:
	MOV.W	R8, R5
	BRA	#.L256
.L669:
	CMP.W	#0, R12 { JNE	.L449
	MOV.W	28(R1), R13
	MOV.W	30(R1), R14
	BRA	#.L626
.L486:
	CMP.W	#0, 16(R1) { JNE	.L449
	BIT.W	#64, R9 { JEQ	.L297
	MOV.W	R8, R5
	BRA	#.L494
.L658:
	CMP.W	#0, R8 { JEQ	.L671
	CMP.W	#324, 50(R1) { JEQ	.L672
.L344:
	CMP.B	#1, R14 { JNE	.L328
.L342:
	CMP.W	#48, R10 { JEQ	.L351
	CMP.W	#816, R10 { JEQ	.L455
	CMP.W	#768, R10 { JEQ	.L456
	CMP.W	#784, R10 { JEQ	.L457
	CMP.W	#800, R10 { JEQ	.L458
	CMP.W	#544, R10 { JEQ	.L459
	CMP.W	#560, R10 { JNE	.L617
	MOV.W	#8, 8(R1)
	MOV.W	#0, 10(R1)
.L352:
	MOV.W	R7, R12
	AND.W	#-4097, R12
	CMP.W	#16512, R12 { JEQ	.L328
.L355:
	CMP.W	#24704, R7 { JNE	.L617
	MOV.W	8(R1), R13
	ADD	#-3584, R13 ; cy
	MOV.W	10(R1), R12
	ADDC	#-1, R12
	CMP.W	#0, R12 { JNE	.L328
	MOV.W	#512, R7
	CMP.W	R13, R7 { JLO	.L328
	MOV.B	#1, R5
	BRA	#.L494
.L657:
	CMP.W	#0, R8 { JEQ	.L673
	MOV.W	34(R1), R8
	ADDX	60(R1), R8 ; cy
	MOV.W	R8, 74(R1)
	MOV.W	40(R1), R8
	ADDCX	82(R1), R8
	MOV.W	R8, 76(R1)
	MOV.W	74(R1), R13
	ADD	#-17408, R13 ; cy
	MOV.W	R8, R12
	ADDC	#-1, R12
	CMP.W	#0, R12 { JNE	.L342
	MOV.W	#32767, R12
	CMP.W	R13, R12 { JLO	.L342
	MOV.W	74(R1), R12
	MOV.W	76(R1), R13
	PUSH.W	R13 { PUSH.W	R12 { POPM.A	#1, R8
	CMP.W	#324, @R8 { JNE	.L344
	BRA	#.L342
.L665:
	MOV.W	R9, R13
	AND.B	#64, R13
	CMP.W	#0, R8 { JNE	.L334
	MOV.W	R7, R8
	RLAM.A #4, R8 { RRAM.A #4, R8
	MOV.W	@R8, R12
	CMP.W	#0, R13 { JEQ	.L620
	RPT	#8 { RRUX.W	R12
	MOV.W	#0,R13
	BRA	#.L613
.L673:
	MOV.W	36(R1), R8
	MOV.W	R8, R12 { MOV.W	R8, R13 { RPT	#15 { RRAX.W	R13
	MOV.W	60(R1), R8
	ADD	R12, R8 ; cy
	MOV.W	R8, 70(R1)
	MOV.W	82(R1), R8
	ADDC	R13, R8
	MOV.W	R8, 72(R1)
	MOV.W	70(R1), R13
	ADD	#-17408, R13 ; cy
	MOV.W	R8, R12
	ADDC	#-1, R12
	CMP.W	#0, R12 { JNE	.L342
	MOV.W	#32767, R12
	CMP.W	R13, R12 { JLO	.L342
	MOV.W	70(R1), R12
	MOV.W	72(R1), R13
	PUSH.W	R13 { PUSH.W	R12 { POPM.A	#1, R8
	CMP.W	#324, @R8 { JNE	.L344
	BRA	#.L342
.L336:
	MOV.W	@R12, R12
.L620:
	MOV.W	#0,R13
	BRA	#.L613
.L334:
	MOV.W	28(R1), R7
	MOV.W	30(R1), R8
	PUSH.W	R8 { PUSH.W	R7 { POPM.A	#1, R12
	CMP.W	#0, R13 { JEQ	.L336
	BIT.W	#64, 32(R1) { JNE	.L674
.L337:
	MOV.W	2(R12), R13
	MOV.W	@R12, R12
	BRA	#.L613
.L672:
	CMP.W	#0, 48(R1) { JNE	.L344
	BRA	#.L342
.L671:
	MOV.W	36(R1), R12
	CMP.W	#324, R12 { JNE	.L344
	MOV.W	38(R1), R12
	CMP.W	#0, R12 { JNE	.L344
	BRA	#.L342
.L664:
	MOV.W	R9, R14
	AND.B	#64, R14
	CMP.W	#0, R8 { JNE	.L330
	MOV.W	R7, R12 { MOV.W	R7, R13 { RPT	#15 { RRAX.W	R13
	MOV.W	R12, 8(R1)
	MOV.W	R13, 10(R1)
	MOVA	8(R1), R12
	MOVA	12(R1), R13
	ADDA	R13, R12
	MOV.W	@R12, R12
	CMP.W	#0, R14 { JEQ	.L620
	CLR	R13
	BRA	#.L613
.L661:
	MOV.W	#8, 56(R1)
	MOV.W	#0, 58(R1)
	BRA	#.L290
.L330:
	MOVA	44(R1), R12
	MOVA	12(R1), R7
	ADDA	R7, R12
	CMP.W	#0, R14 { JEQ	.L336
	BITX.W	#64, 32(R1) { JEQ	.L337
	MOVX.B	@R12,R12 { CLR	R13
	BRA	#.L613
.L437:
	MOV.W	#4, 56(R1)
	MOV.W	#0, 58(R1)
	BRA	#.L290
.L436:
	MOV.W	#2, 56(R1)
	MOV.W	#0, 58(R1)
	BRA	#.L290
.L656:
	MOV.W	R9, R12
	AND.W	#-12096, R12
	CMP.W	#-32640, R12 { JEQ	.L338
.L339:
	CMP.B	#1, R14 { JNE	.L328
	MOV.W	R14, R5
	BRA	#.L494
.L457:
	MOV.W	#1, 8(R1)
	MOV.W	#0, 10(R1)
	BRA	#.L352
.L456:
	MOV.W	#0, 8(R1)
	MOV.W	#0, 10(R1)
	BRA	#.L352
.L455:
	MOV.W	#-1, 8(R1)
	MOV.W	#-1, 10(R1)
	BRA	#.L352
.L351:
	CMP.W	#16512, R7 { JNE	.L675
	MOV.W	8(R1), R12
	XOR.W	#165, R12
	MOV.W	10(R1), R13
	BIS.W	R13, R12
	MOV.W	R12, R14
	ADD.W	#-1, R14
	BIC.W	R12, R14
	RPT	#15 { RRUX.W	R14
	BRA	#.L339
.L459:
	MOV.W	#4, 8(R1)
	MOV.W	#0, 10(R1)
	BRA	#.L352
.L674:
	MOV.B	1(R12), R12
	MOV.W	#0,R13
	BRA	#.L613
.L458:
	MOV.W	#2, 8(R1)
	MOV.W	#0, 10(R1)
	BRA	#.L352
.L675:
	CMP.W	#20608, R7 { JNE	.L355
	MOV.W	8(R1), R13
	ADD	#-3585, R13 ; cy
	MOV.W	10(R1), R12
	ADDC	#-1, R12
	CMP.W	#0, R12 { JNE	.L328
	MOV.W	#511, R14
	CMP.W	R13, R14 { JLO	.L328
	MOV.B	#1, R5
	BRA	#.L494
	.size	verify, .-verify
	.section	.tcm:codeStart,"ax",@progbits
	.balign 2
	.global	secureBoot
	.type	secureBoot, @function
secureBoot:
; start of function
; attributes: 
; framesize_regs:     4
; framesize_locals:   0
; framesize_outgoing: 0
; framesize:          4
; elim ap -> fp       8
; elim fp -> sp       0
; saved regs: R10
	; start of prologue
	PUSHM.A	#1, R10
	; end of prologue
	MOVX.W	#23168, &WDTCTL
 ; 95 "core/src_compile/core.c" 1
	mov #0x43ff, r1
 ; 0 "" 2
 ; 100 "core/src_compile/core.c" 1
	dint { nop
 ; 0 "" 2
	BISX.B	#1, &PADIR_L
	MOV.B	#10, R13
.L678:
	XORX.B	#1, &PAOUT_L
	MOV.W	#10000, R12
.L677:
 ; 108 "core/src_compile/core.c" 1
	nop
 ; 0 "" 2
	ADD.W	#-1, R12
	CMP.W	#0, R12 { JNE	.L677
	ADD.W	#-1, R13
	CMP.W	#0, R13 { JNE	.L678
	BISX.B	#1, &PAOUT_L
	MOV.B	#0, R14
	MOV.W	#-15361, R13
	MOV.W	#17408, R12
	CALLA	#verify
	MOV.B	R12, R10
	MOV.B	#1, R14
	MOV.W	#-15361, R13
	MOV.W	#17408, R12
	CALLA	#verify
	BIS.B	R10, R12
	CMP.B	#0, R12 { JEQ	.L685
	MOVX.W	#6, &WDTCTL
	; start of epilogue
	POPM.A	#1, r10
	RETA
.L685:
	ANDX.B	#127, &PBOUT_H
	BICX.B	#1, &PAOUT_L
 ; 142 "core/src_compile/core.c" 1
	nop { eint { nop
 ; 0 "" 2
 ; 146 "core/src_compile/core.c" 1
	mov #0x43ff, r1
 ; 0 "" 2
 ; 149 "core/src_compile/core.c" 1
	mov #0, r8
 ; 0 "" 2
	MOVX.W	#-23296, &FCTL3
	MOVX.W	#-23294, &FCTL1
 ; 152 "core/src_compile/core.c" 1
	MOV.W #0, &0xf600
 ; 0 "" 2
.L680:
	BITX.W	#1, &FCTL3 { JNE	.L680
	MOVX.W	#-23280, &FCTL3
 ; 158 "core/src_compile/core.c" 1
	
	BR #4400h
 ; 0 "" 2
	; start of epilogue
	POPM.A	#1, r10
	RETA
	.size	secureBoot, .-secureBoot
	.section	.tcm:code
	.balign 2
	.global	flushBufferToFlash
	.type	flushBufferToFlash, @function
flushBufferToFlash:
; start of function
; attributes: 
; framesize_regs:     8
; framesize_locals:   8
; framesize_outgoing: 0
; framesize:          16
; elim ap -> fp       12
; elim fp -> sp       8
; saved regs: R8 R10
	; start of prologue
	PUSHM.A	#1, R10
	PUSHM.A	#1, R8
	SUBA	#8, R1
	; end of prologue
	MOVX.B	&counterBuffAlwDst, R12
	MOVX.W	&cfiDataHolder, @R1
	MOVX.W	&cfiDataHolder+2, 2(R1)
	MOVX.W	#-23296, &FCTL3
	MOVX.W	#-23168, &FCTL1
	RPT	#9 { RLAX.W	R12
	MOV.W	R12, R13 { MOV.W	R12, R14 { RPT	#15 { RRAX.W	R14
	MOV.W	R13, 4(R1)
	MOV.W	R14, 6(R1)
	MOVA	4(R1), R14
	MOVA	@R1, R12
	ADDA	R12, R14
	MOV.B	#0, R12
.L687:
	MOV.B	R12, R10
	RLAM.A	#2, R10
	MOVA	R10, R8
	ADDA	R14, R8
	MOVX.W	alwDst(R10), @R8
	MOVX.W	alwDst+2(R10), 2(R8)
	ADD.B	#1, R12
	AND	#0xff, R12
	MOVX.W	&counterAlwDst, R13
	RRUM.W	#1, R13
	CMP.W	R13, R12 { JLO	.L687
	BITX.W	#1, &counterAlwDst { JEQ	.L686
	MOVX.W	#-23232, &FCTL1
	RLAM.W	#1, R12
	RLAM.A #4, R12 { RRAM.A #4, R12
	RLAM.A	#1, R12
	ADDA	R12, R14
	MOVX.W	alwDst(R12), @R14
.L686:
	; start of epilogue
	ADDA	#8, R1
	POPM.A	#1, r8
	POPM.A	#1, r10
	RETA
	.size	flushBufferToFlash, .-flushBufferToFlash
	.global	cfiDataHolder
	.section .bss
	.balign 2
	.type	cfiDataHolder, @object
	.size	cfiDataHolder, 4
cfiDataHolder:
	.zero	4
	.global	counterBuffAlwDst
	.type	counterBuffAlwDst, @object
	.size	counterBuffAlwDst, 1
counterBuffAlwDst:
	.zero	1
	.global	counterAlwDst
	.balign 2
	.type	counterAlwDst, @object
	.size	counterAlwDst, 2
counterAlwDst:
	.zero	2
	.global	alwDst
	.balign 2
	.type	alwDst, @object
	.size	alwDst, 512
alwDst:
	.zero	512
	.global	entryPointBSL
	.section	.tcm:rodata,"a"
	.balign 2
	.type	entryPointBSL, @object
	.size	entryPointBSL, 2
entryPointBSL:
	.short	4098
	.global	receive_update_address
	.balign 2
	.type	receive_update_address, @object
	.size	receive_update_address, 2
receive_update_address:
	.short	-284
	.global	safe_subcx
	.balign 2
	.type	safe_subcx, @object
	.size	safe_subcx, 2
safe_subcx:
	.short	-308
	.global	safe_subc
	.balign 2
	.type	safe_subc, @object
	.size	safe_subc, 2
safe_subc:
	.short	-326
	.global	safe_subx
	.balign 2
	.type	safe_subx, @object
	.size	safe_subx, 2
safe_subx:
	.short	-346
	.global	safe_sub
	.balign 2
	.type	safe_sub, @object
	.size	safe_sub, 2
safe_sub:
	.short	-364
	.global	safe_daddx
	.balign 2
	.type	safe_daddx, @object
	.size	safe_daddx, 2
safe_daddx:
	.short	-384
	.global	safe_dadd
	.balign 2
	.type	safe_dadd, @object
	.size	safe_dadd, 2
safe_dadd:
	.short	-402
	.global	safe_addcx
	.balign 2
	.type	safe_addcx, @object
	.size	safe_addcx, 2
safe_addcx:
	.short	-422
	.global	safe_addc
	.balign 2
	.type	safe_addc, @object
	.size	safe_addc, 2
safe_addc:
	.short	-440
	.global	safe_addx
	.balign 2
	.type	safe_addx, @object
	.size	safe_addx, 2
safe_addx:
	.short	-460
	.global	safe_add
	.balign 2
	.type	safe_add, @object
	.size	safe_add, 2
safe_add:
	.short	-478
	.global	safe_xorx
	.balign 2
	.type	safe_xorx, @object
	.size	safe_xorx, 2
safe_xorx:
	.short	-498
	.global	safe_xor
	.balign 2
	.type	safe_xor, @object
	.size	safe_xor, 2
safe_xor:
	.short	-516
	.global	safe_movx
	.balign 2
	.type	safe_movx, @object
	.size	safe_movx, 2
safe_movx:
	.short	-536
	.global	safe_mov
	.balign 2
	.type	safe_mov, @object
	.size	safe_mov, 2
safe_mov:
	.short	-554
	.global	safe_reta
	.balign 2
	.type	safe_reta, @object
	.size	safe_reta, 2
safe_reta:
	.short	-594
	.global	safe_reti
	.balign 2
	.type	safe_reti, @object
	.size	safe_reti, 2
safe_reti:
	.short	-666
	.global	safe_ret
	.balign 2
	.type	safe_ret, @object
	.size	safe_ret, 2
safe_ret:
	.short	-756
	.global	safe_calla
	.balign 2
	.type	safe_calla, @object
	.size	safe_calla, 2
safe_calla:
	.short	-940
	.global	safe_call
	.balign 2
	.type	safe_call, @object
	.size	safe_call, 2
safe_call:
	.short	-948
	.global	safe_bra
	.balign 2
	.type	safe_bra, @object
	.size	safe_bra, 2
safe_bra:
	.short	-986
	.global	safe_br
	.balign 2
	.type	safe_br, @object
	.size	safe_br, 2
safe_br:
	.short	-1024
	.global	vectorBottom
	.balign 2
	.type	vectorBottom, @object
	.size	vectorBottom, 4
vectorBottom:
	.long	66560
	.global	vectorTop
	.balign 2
	.type	vectorTop, @object
	.size	vectorTop, 4
vectorTop:
	.long	66684
	.global	ramTop
	.balign 2
	.type	ramTop, @object
	.size	ramTop, 2
ramTop:
	.short	17407
	.global	ramBottom
	.balign 2
	.type	ramBottom, @object
	.size	ramBottom, 2
ramBottom:
	.short	9216
	.global	flashBottom
	.balign 2
	.type	flashBottom, @object
	.size	flashBottom, 2
flashBottom:
	.short	17408
	.global	flashTop
	.balign 2
	.type	flashTop, @object
	.size	flashTop, 4
flashTop:
	.long	148479
	.global	bslBottom
	.balign 2
	.type	bslBottom, @object
	.size	bslBottom, 2
bslBottom:
	.short	4096
	.global	bslTop
	.balign 2
	.type	bslTop, @object
	.size	bslTop, 2
bslTop:
	.short	6143
	.global	elfAddress
	.balign 2
	.type	elfAddress, @object
	.size	elfAddress, 4
elfAddress:
	.long	115712
	.global	appTopROdata
	.balign 2
	.type	appTopROdata, @object
	.size	appTopROdata, 4
appTopROdata:
	.long	115711
	.global	appBottomROdata
	.balign 2
	.type	appBottomROdata, @object
	.size	appBottomROdata, 4
appBottomROdata:
	.long	82944
	.global	appTopText
	.balign 2
	.type	appTopText, @object
	.size	appTopText, 2
appTopText:
	.short	-15361
	.global	appBottomText
	.balign 2
	.type	appBottomText, @object
	.size	appBottomText, 2
appBottomText:
	.short	17408
	.global	appBottomRam
	.balign 2
	.type	appBottomRam, @object
	.size	appBottomRam, 2
appBottomRam:
	.short	11264
	.global	appTopRam
	.balign 2
	.type	appTopRam, @object
	.size	appTopRam, 2
appTopRam:
	.short	17407
	.ident	"GCC: (Mitto Systems Limited - msp430-gcc 9.3.1.11) 9.3.1"
	.mspabi_attribute 4, 2
	.mspabi_attribute 6, 2
	.mspabi_attribute 8, 2
	.gnu_attribute 4, 2
