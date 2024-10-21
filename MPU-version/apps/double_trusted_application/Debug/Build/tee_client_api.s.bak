	.cpu cortex-m3
	.arch armv7-m
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 1
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"tee_client_api.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 1 "../Core/Src/tee_client_api.c"
	.section	.rodata.check_context.str1.4,"aMS",%progbits,1
	.align	2
.LC0:
	.ascii	"../Core/Src/tee_client_api.c\000"
	.align	2
.LC1:
	.ascii	"\033[0;31mERROR: %s:%d:%s(): \"Context is null\"\015"
	.ascii	"\012\000"
	.align	2
.LC2:
	.ascii	"\033[0;31mERROR: %s:%d:%s(): \"Invalid context id\""
	.ascii	"\015\012\000"
	.section	.text.check_context,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.type	check_context, %function
check_context:
.LVL0:
.LFB78:
	.loc 1 54 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 54 1 is_stmt 0 view .LVU1
	push	{r3, lr}
.LCFI0:
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	.cfi_offset 14, -4
	.loc 1 56 5 is_stmt 1 view .LVU2
	.loc 1 56 7 is_stmt 0 view .LVU3
	cbz	r0, .L6
	.loc 1 63 5 is_stmt 1 view .LVU4
	.loc 1 63 26 is_stmt 0 view .LVU5
	ldr	r3, [r0]
	.loc 1 63 7 view .LVU6
	cmp	r3, #2
	bhi	.L7
	.loc 1 70 12 view .LVU7
	movs	r0, #0
.LVL1:
.L1:
	.loc 1 71 1 view .LVU8
	pop	{r3, pc}
.LVL2:
.L6:
	.loc 1 58 9 is_stmt 1 view .LVU9
	.loc 1 58 9 view .LVU10
	ldr	r3, .L8
	movs	r2, #58
	ldr	r1, .L8+4
	ldr	r0, .L8+8
.LVL3:
	.loc 1 58 9 is_stmt 0 view .LVU11
	bl	printf
.LVL4:
	.loc 1 58 9 is_stmt 1 view .LVU12
	.loc 1 58 35 view .LVU13
	.loc 1 59 9 view .LVU14
	.loc 1 59 16 is_stmt 0 view .LVU15
	movs	r0, #1
	b	.L1
.LVL5:
.L7:
	.loc 1 66 9 is_stmt 1 view .LVU16
	.loc 1 66 9 view .LVU17
	ldr	r3, .L8
	movs	r2, #66
	ldr	r1, .L8+4
	ldr	r0, .L8+12
.LVL6:
	.loc 1 66 9 is_stmt 0 view .LVU18
	bl	printf
.LVL7:
	.loc 1 66 9 is_stmt 1 view .LVU19
	.loc 1 66 38 view .LVU20
	.loc 1 67 9 view .LVU21
	.loc 1 67 16 is_stmt 0 view .LVU22
	movs	r0, #1
	b	.L1
.L9:
	.align	2
.L8:
	.word	__func__.3
	.word	.LC0
	.word	.LC1
	.word	.LC2
	.cfi_endproc
.LFE78:
	.size	check_context, .-check_context
	.section	.text.get_internalOperation,"ax",%progbits
	.align	1
	.global	get_internalOperation
	.syntax unified
	.thumb
	.thumb_func
	.type	get_internalOperation, %function
get_internalOperation:
.LVL8:
.LFB77:
	.loc 1 34 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 36 5 view .LVU24
	.loc 1 36 7 is_stmt 0 view .LVU25
	cmp	r0, #2
	bhi	.L12
	.loc 1 40 5 is_stmt 1 view .LVU26
	.loc 1 40 20 is_stmt 0 view .LVU27
	ldr	r3, .L13
	ldr	r0, [r3, r0, lsl #2]
.LVL9:
	.loc 1 40 20 view .LVU28
	bx	lr
.LVL10:
.L12:
	.loc 1 37 16 view .LVU29
	movs	r0, #0
.LVL11:
	.loc 1 44 1 view .LVU30
	bx	lr
.L14:
	.align	2
.L13:
	.word	internal_op
	.cfi_endproc
.LFE77:
	.size	get_internalOperation, .-get_internalOperation
	.section	.rodata.TEEC_InitializeContext.str1.4,"aMS",%progbits,1
	.align	2
.LC3:
	.ascii	"\033[0;31mERROR: %s:%d:%s(): \"Memory allocation is"
	.ascii	" failed\"\015\012\000"
	.section	.text.TEEC_InitializeContext,"ax",%progbits
	.align	1
	.global	TEEC_InitializeContext
	.syntax unified
	.thumb
	.thumb_func
	.type	TEEC_InitializeContext, %function
TEEC_InitializeContext:
.LVL12:
.LFB79:
	.loc 1 84 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 84 1 is_stmt 0 view .LVU32
	push	{r3, r4, r5, lr}
.LCFI1:
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	.cfi_offset 4, -12
	.cfi_offset 5, -8
	.cfi_offset 14, -4
	mov	r5, r1
	.loc 1 85 5 is_stmt 1 view .LVU33
.LVL13:
	.loc 1 95 5 view .LVU34
.LBB2:
	.loc 1 95 9 view .LVU35
	.loc 1 95 13 is_stmt 0 view .LVU36
	movs	r4, #0
.LVL14:
.L16:
	.loc 1 95 19 is_stmt 1 discriminator 1 view .LVU37
	cmp	r4, #1
	bgt	.L20
	.loc 1 99 9 view .LVU38
	.loc 1 99 23 is_stmt 0 view .LVU39
	ldr	r3, .L26
	ldr	r3, [r3, r4, lsl #2]
	.loc 1 99 11 view .LVU40
	cbz	r3, .L17
	.loc 1 100 13 is_stmt 1 discriminator 1 view .LVU41
	.loc 1 95 35 discriminator 1 view .LVU42
	adds	r4, r4, #1
.LVL15:
	.loc 1 95 35 is_stmt 0 discriminator 1 view .LVU43
	b	.L16
.L17:
	.loc 1 104 9 is_stmt 1 view .LVU44
	.loc 1 104 49 is_stmt 0 view .LVU45
	movs	r1, #28
.LVL16:
	.loc 1 104 49 view .LVU46
	movs	r0, #1
.LVL17:
	.loc 1 104 49 view .LVU47
	bl	calloc
.LVL18:
	.loc 1 104 24 view .LVU48
	ldr	r3, .L26
	str	r0, [r3, r4, lsl #2]
	.loc 1 105 9 is_stmt 1 view .LVU49
	.loc 1 105 11 is_stmt 0 view .LVU50
	cbz	r0, .L24
	.loc 1 112 9 is_stmt 1 view .LVU51
	.loc 1 112 32 is_stmt 0 view .LVU52
	adds	r4, r4, #1
.LVL19:
	.loc 1 112 28 view .LVU53
	str	r4, [r0, #24]
	.loc 1 113 9 is_stmt 1 view .LVU54
	.loc 1 113 17 is_stmt 0 view .LVU55
	str	r4, [r5]
	.loc 1 114 9 is_stmt 1 view .LVU56
.LVL20:
.L20:
	.loc 1 114 9 is_stmt 0 view .LVU57
.LBE2:
	.loc 1 118 5 is_stmt 1 view .LVU58
	.loc 1 120 5 view .LVU59
	.loc 1 120 55 is_stmt 0 view .LVU60
	ldr	r3, [r5]
	.loc 1 120 60 view .LVU61
	subs	r3, r3, #1
	.loc 1 120 15 view .LVU62
	ldr	r2, .L26
	ldr	r2, [r2, r3, lsl #2]
.LVL21:
	.loc 1 123 5 is_stmt 1 view .LVU63
	.syntax unified
@ 123 "../Core/Src/tee_client_api.c" 1
	MOV r3, r4
@ 0 "" 2
.LVL22:
	.loc 1 124 5 view .LVU64
@ 124 "../Core/Src/tee_client_api.c" 1
	MOV R4, r2

@ 0 "" 2
	.loc 1 127 5 view .LVU65
@ 127 "../Core/Src/tee_client_api.c" 1
	svc #0
@ 0 "" 2
	.loc 1 130 5 view .LVU66
@ 130 "../Core/Src/tee_client_api.c" 1
	MOV r0, R4

@ 0 "" 2
.LVL23:
	.loc 1 131 5 view .LVU67
@ 131 "../Core/Src/tee_client_api.c" 1
	MOV R4, r3

@ 0 "" 2
	.loc 1 134 5 view .LVU68
	.loc 1 134 7 is_stmt 0 view .LVU69
	.thumb
	.syntax unified
	cbnz	r0, .L25
.LVL24:
.L15:
	.loc 1 138 1 view .LVU70
	pop	{r3, r4, r5, pc}
.LVL25:
.L24:
.LBB3:
	.loc 1 106 13 is_stmt 1 view .LVU71
	.loc 1 106 13 view .LVU72
	ldr	r3, .L26+4
	movs	r2, #106
	ldr	r1, .L26+8
	ldr	r0, .L26+12
	bl	printf
.LVL26:
	.loc 1 106 13 view .LVU73
	.loc 1 106 51 view .LVU74
	.loc 1 107 13 view .LVU75
	.loc 1 107 20 is_stmt 0 view .LVU76
	movs	r0, #1
	b	.L15
.LVL27:
.L25:
	.loc 1 107 20 view .LVU77
.LBE3:
	.loc 1 135 16 view .LVU78
	movs	r0, #1
.LVL28:
	.loc 1 135 16 view .LVU79
	b	.L15
.L27:
	.align	2
.L26:
	.word	internal_op
	.word	__func__.6
	.word	.LC0
	.word	.LC3
	.cfi_endproc
.LFE79:
	.size	TEEC_InitializeContext, .-TEEC_InitializeContext
	.section	.rodata.TEEC_FinalizeContext.str1.4,"aMS",%progbits,1
	.align	2
.LC4:
	.ascii	"\033[0;31mERROR: %s:%d:%s(): \"context finalize err"
	.ascii	"\"\015\012\000"
	.section	.text.TEEC_FinalizeContext,"ax",%progbits
	.align	1
	.global	TEEC_FinalizeContext
	.syntax unified
	.thumb
	.thumb_func
	.type	TEEC_FinalizeContext, %function
TEEC_FinalizeContext:
.LVL29:
.LFB80:
	.loc 1 147 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 147 1 is_stmt 0 view .LVU81
	push	{r3, r4, r5, lr}
.LCFI2:
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	.cfi_offset 4, -12
	.cfi_offset 5, -8
	.cfi_offset 14, -4
	.loc 1 148 2 is_stmt 1 view .LVU82
.LVL30:
	.loc 1 151 5 view .LVU83
	.loc 1 151 7 is_stmt 0 view .LVU84
	cbz	r0, .L29
	mov	r4, r0
	.loc 1 151 22 discriminator 1 view .LVU85
	ldr	r3, [r0]
	.loc 1 151 15 discriminator 1 view .LVU86
	cbnz	r3, .L30
.L29:
	.loc 1 152 9 is_stmt 1 view .LVU87
	.loc 1 152 9 view .LVU88
	ldr	r3, .L33
	movs	r2, #152
	ldr	r1, .L33+4
	ldr	r0, .L33+8
.LVL31:
	.loc 1 152 9 is_stmt 0 view .LVU89
	bl	printf
.LVL32:
	.loc 1 152 9 is_stmt 1 view .LVU90
	.loc 1 152 40 view .LVU91
	.loc 1 148 6 is_stmt 0 view .LVU92
	movs	r5, #1
.LVL33:
.L31:
	.loc 1 162 5 is_stmt 1 view .LVU93
	.loc 1 163 4 view .LVU94
	.syntax unified
@ 163 "../Core/Src/tee_client_api.c" 1
	MOV r3, R4

@ 0 "" 2
.LVL34:
	.loc 1 166 4 view .LVU95
@ 166 "../Core/Src/tee_client_api.c" 1
	MOV R4, r5

@ 0 "" 2
	.loc 1 168 4 view .LVU96
@ 168 "../Core/Src/tee_client_api.c" 1
	svc #1
@ 0 "" 2
	.loc 1 171 2 view .LVU97
@ 171 "../Core/Src/tee_client_api.c" 1
	MOV R4, r3

@ 0 "" 2
	.loc 1 172 1 is_stmt 0 view .LVU98
	.thumb
	.syntax unified
	pop	{r3, r4, r5, pc}
.LVL35:
.L30:
	.loc 1 156 6 is_stmt 1 view .LVU99
	.loc 1 156 12 is_stmt 0 view .LVU100
	mov	r5, r3
.LVL36:
	.loc 1 157 9 is_stmt 1 view .LVU101
	.loc 1 157 34 is_stmt 0 view .LVU102
	subs	r3, r3, #1
	.loc 1 157 9 view .LVU103
	ldr	r2, .L33+12
	ldr	r0, [r2, r3, lsl #2]
.LVL37:
	.loc 1 157 9 view .LVU104
	bl	free
.LVL38:
	.loc 1 158 9 is_stmt 1 view .LVU105
	.loc 1 158 17 is_stmt 0 view .LVU106
	movs	r3, #0
	str	r3, [r4]
	b	.L31
.L34:
	.align	2
.L33:
	.word	__func__.5
	.word	.LC0
	.word	.LC4
	.word	internal_op
	.cfi_endproc
.LFE80:
	.size	TEEC_FinalizeContext, .-TEEC_FinalizeContext
	.section	.rodata.TEEC_OpenSession.str1.4,"aMS",%progbits,1
	.align	2
.LC5:
	.ascii	"\033[0;31mERROR: %s:%d:%s(): \"uuid is null\"\015\012"
	.ascii	"\000"
	.section	.text.TEEC_OpenSession,"ax",%progbits
	.align	1
	.global	TEEC_OpenSession
	.syntax unified
	.thumb
	.thumb_func
	.type	TEEC_OpenSession, %function
TEEC_OpenSession:
.LVL39:
.LFB81:
	.loc 1 195 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 12, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 195 1 is_stmt 0 view .LVU108
	push	{r3, r4, r5, r6, r7, lr}
.LCFI3:
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	.cfi_offset 4, -20
	.cfi_offset 5, -16
	.cfi_offset 6, -12
	.cfi_offset 7, -8
	.cfi_offset 14, -4
	mov	r4, r0
	mov	r5, r1
	mov	r7, r2
	ldr	r6, [sp, #28]
	.loc 1 196 5 is_stmt 1 view .LVU109
.LVL40:
	.loc 1 199 5 view .LVU110
	.loc 1 199 8 is_stmt 0 view .LVU111
	bl	check_context
.LVL41:
	.loc 1 199 7 view .LVU112
	cmp	r0, #0
	bne	.L43
	mov	r3, r0
	.loc 1 205 5 is_stmt 1 view .LVU113
	.loc 1 205 7 is_stmt 0 view .LVU114
	cbz	r7, .L46
	.loc 1 212 5 is_stmt 1 view .LVU115
	.loc 1 212 18 is_stmt 0 view .LVU116
	str	r4, [r5]
	.loc 1 216 2 is_stmt 1 view .LVU117
	.loc 1 216 17 is_stmt 0 view .LVU118
	ldr	r2, [r4]
	.loc 1 216 22 view .LVU119
	subs	r2, r2, #1
	.loc 1 216 13 view .LVU120
	ldr	r1, .L48
	ldr	r2, [r1, r2, lsl #2]
	.loc 1 216 33 view .LVU121
	str	r7, [r2, #20]
	.loc 1 220 2 is_stmt 1 view .LVU122
	.loc 1 220 4 is_stmt 0 view .LVU123
	cbnz	r6, .L38
	b	.L39
.L46:
	.loc 1 207 9 is_stmt 1 view .LVU124
	.loc 1 207 9 view .LVU125
	ldr	r3, .L48+4
	movs	r2, #207
	ldr	r1, .L48+8
	ldr	r0, .L48+12
	bl	printf
.LVL42:
	.loc 1 207 9 view .LVU126
	.loc 1 207 32 view .LVU127
	.loc 1 208 9 view .LVU128
	.loc 1 260 10 is_stmt 0 view .LVU129
	movs	r0, #1
	.loc 1 208 9 view .LVU130
	b	.L35
.LVL43:
.L40:
.LBB4:
	.loc 1 224 4 is_stmt 1 discriminator 3 view .LVU131
	.loc 1 224 19 is_stmt 0 discriminator 3 view .LVU132
	ldr	r2, [r4]
	.loc 1 224 24 discriminator 3 view .LVU133
	subs	r2, r2, #1
	.loc 1 224 15 discriminator 3 view .LVU134
	ldr	r1, .L48
	ldr	r1, [r1, r2, lsl #2]
	.loc 1 224 41 discriminator 3 view .LVU135
	rsb	r2, r3, r3, lsl #3
	lsls	r2, r2, #2
	adds	r2, r2, #8
	add	r2, r2, r6
	.loc 1 224 39 discriminator 3 view .LVU136
	str	r2, [r1, r3, lsl #2]
	.loc 1 222 22 is_stmt 1 discriminator 3 view .LVU137
	adds	r3, r3, #1
.LVL44:
.L38:
	.loc 1 222 17 discriminator 1 view .LVU138
	cmp	r3, #3
	ble	.L40
.LBE4:
	.loc 1 227 3 view .LVU139
	.loc 1 227 18 is_stmt 0 view .LVU140
	ldr	r3, [r4]
.LVL45:
	.loc 1 227 23 view .LVU141
	subs	r3, r3, #1
	.loc 1 227 14 view .LVU142
	ldr	r2, .L48
	ldr	r3, [r2, r3, lsl #2]
	.loc 1 227 50 view .LVU143
	ldr	r2, [r6, #4]
	.loc 1 227 39 view .LVU144
	str	r2, [r3, #16]
.LVL46:
.L41:
	.loc 1 238 5 is_stmt 1 view .LVU145
	.loc 1 238 17 is_stmt 0 view .LVU146
	movs	r3, #1
	str	r3, [r5, #4]
	.loc 1 242 5 is_stmt 1 view .LVU147
.LVL47:
	.loc 1 243 5 view .LVU148
	.loc 1 243 55 is_stmt 0 view .LVU149
	ldr	r3, [r4]
	.loc 1 243 60 view .LVU150
	subs	r3, r3, #1
	.loc 1 243 15 view .LVU151
	ldr	r2, .L48
	ldr	r2, [r2, r3, lsl #2]
.LVL48:
	.loc 1 244 5 is_stmt 1 view .LVU152
	.syntax unified
@ 244 "../Core/Src/tee_client_api.c" 1
	MOV r3, r4
@ 0 "" 2
.LVL49:
	.loc 1 245 5 view .LVU153
@ 245 "../Core/Src/tee_client_api.c" 1
	MOV R4, r2

@ 0 "" 2
	.loc 1 247 5 view .LVU154
@ 247 "../Core/Src/tee_client_api.c" 1
	svc #2
@ 0 "" 2
	.loc 1 250 5 view .LVU155
@ 250 "../Core/Src/tee_client_api.c" 1
	MOV r0, R4

@ 0 "" 2
.LVL50:
	.loc 1 251 5 view .LVU156
@ 251 "../Core/Src/tee_client_api.c" 1
	MOV R4, r3

@ 0 "" 2
	.loc 1 253 5 view .LVU157
	.loc 1 253 7 is_stmt 0 view .LVU158
	.thumb
	.syntax unified
	cbnz	r0, .L47
.LVL51:
.L35:
	.loc 1 261 1 view .LVU159
	pop	{r3, r4, r5, r6, r7, pc}
.LVL52:
.L42:
.LBB5:
	.loc 1 232 4 is_stmt 1 discriminator 3 view .LVU160
	.loc 1 232 19 is_stmt 0 discriminator 3 view .LVU161
	ldr	r2, [r4]
	.loc 1 232 24 discriminator 3 view .LVU162
	subs	r2, r2, #1
	.loc 1 232 15 discriminator 3 view .LVU163
	ldr	r1, .L48
	ldr	r2, [r1, r2, lsl #2]
	.loc 1 232 39 discriminator 3 view .LVU164
	movs	r1, #0
	str	r1, [r2, r3, lsl #2]
	.loc 1 230 22 is_stmt 1 discriminator 3 view .LVU165
	adds	r3, r3, #1
.LVL53:
.L39:
	.loc 1 230 17 discriminator 1 view .LVU166
	cmp	r3, #3
	ble	.L42
.LBE5:
	.loc 1 234 3 view .LVU167
	.loc 1 234 18 is_stmt 0 view .LVU168
	ldr	r3, [r4]
.LVL54:
	.loc 1 234 23 view .LVU169
	subs	r3, r3, #1
	.loc 1 234 14 view .LVU170
	ldr	r2, .L48
	ldr	r3, [r2, r3, lsl #2]
	.loc 1 234 39 view .LVU171
	movs	r2, #0
	str	r2, [r3, #16]
	b	.L41
.LVL55:
.L43:
	.loc 1 260 10 view .LVU172
	movs	r0, #1
	b	.L35
.LVL56:
.L47:
	.loc 1 254 16 view .LVU173
	movs	r0, #1
.LVL57:
	.loc 1 254 16 view .LVU174
	b	.L35
.L49:
	.align	2
.L48:
	.word	internal_op
	.word	__func__.4
	.word	.LC0
	.word	.LC5
	.cfi_endproc
.LFE81:
	.size	TEEC_OpenSession, .-TEEC_OpenSession
	.section	.rodata.TEEC_CloseSession.str1.4,"aMS",%progbits,1
	.align	2
.LC6:
	.ascii	"\033[0;31mERROR: %s:%d:%s(): \"Session close err\"\015"
	.ascii	"\012\000"
	.section	.text.TEEC_CloseSession,"ax",%progbits
	.align	1
	.global	TEEC_CloseSession
	.syntax unified
	.thumb
	.thumb_func
	.type	TEEC_CloseSession, %function
TEEC_CloseSession:
.LVL58:
.LFB82:
	.loc 1 269 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 269 1 is_stmt 0 view .LVU176
	push	{r4, lr}
.LCFI4:
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	.loc 1 270 2 is_stmt 1 view .LVU177
.LVL59:
	.loc 1 273 5 view .LVU178
	.loc 1 273 7 is_stmt 0 view .LVU179
	cbz	r0, .L54
	.loc 1 278 6 is_stmt 1 view .LVU180
	.loc 1 278 21 is_stmt 0 view .LVU181
	ldr	r2, [r0]
	.loc 1 278 26 view .LVU182
	ldr	r2, [r2]
.LVL60:
	.loc 1 279 9 is_stmt 1 view .LVU183
	.loc 1 279 21 is_stmt 0 view .LVU184
	movs	r1, #0
	str	r1, [r0, #4]
.LVL61:
.L52:
	.loc 1 283 5 is_stmt 1 view .LVU185
	.loc 1 284 4 view .LVU186
	.syntax unified
@ 284 "../Core/Src/tee_client_api.c" 1
	MOV r3, R4

@ 0 "" 2
.LVL62:
	.loc 1 287 4 view .LVU187
@ 287 "../Core/Src/tee_client_api.c" 1
	MOV R4, r2

@ 0 "" 2
	.loc 1 289 5 view .LVU188
@ 289 "../Core/Src/tee_client_api.c" 1
	svc #3
@ 0 "" 2
	.loc 1 292 5 view .LVU189
@ 292 "../Core/Src/tee_client_api.c" 1
	MOV R4, r3

@ 0 "" 2
	.loc 1 293 1 is_stmt 0 view .LVU190
	.thumb
	.syntax unified
	pop	{r4, pc}
.LVL63:
.L54:
	.loc 1 274 9 is_stmt 1 view .LVU191
	.loc 1 274 9 view .LVU192
	ldr	r3, .L55
	mov	r2, #274
	ldr	r1, .L55+4
	ldr	r0, .L55+8
.LVL64:
	.loc 1 274 9 is_stmt 0 view .LVU193
	bl	printf
.LVL65:
	.loc 1 274 9 is_stmt 1 view .LVU194
	.loc 1 274 37 view .LVU195
	.loc 1 270 6 is_stmt 0 view .LVU196
	movs	r2, #1
	b	.L52
.L56:
	.align	2
.L55:
	.word	__func__.2
	.word	.LC0
	.word	.LC6
	.cfi_endproc
.LFE82:
	.size	TEEC_CloseSession, .-TEEC_CloseSession
	.section	.rodata.TEEC_InvokeCommand.str1.4,"aMS",%progbits,1
	.align	2
.LC7:
	.ascii	"\033[0;31mERROR: %s:%d:%s(): \"Null parameter err ("
	.ascii	"session | context)\"\015\012\000"
	.align	2
.LC8:
	.ascii	"\033[0;31mERROR: %s:%d:%s(): \"Invalid session id\""
	.ascii	"\015\012\000"
	.align	2
.LC9:
	.ascii	"\033[0;31mERROR: %s:%d:%s(): \"operation parameter "
	.ascii	"is null\"\015\012\000"
	.section	.text.TEEC_InvokeCommand,"ax",%progbits
	.align	1
	.global	TEEC_InvokeCommand
	.syntax unified
	.thumb
	.thumb_func
	.type	TEEC_InvokeCommand, %function
TEEC_InvokeCommand:
.LVL66:
.LFB83:
	.loc 1 310 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 310 1 is_stmt 0 view .LVU198
	push	{r3, r4, r5, lr}
.LCFI5:
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	.cfi_offset 4, -12
	.cfi_offset 5, -8
	.cfi_offset 14, -4
	.loc 1 311 5 is_stmt 1 view .LVU199
.LVL67:
	.loc 1 314 5 view .LVU200
	.loc 1 314 7 is_stmt 0 view .LVU201
	cbz	r0, .L58
	mov	ip, r0
	.loc 1 314 31 discriminator 1 view .LVU202
	ldr	r3, [r0]
.LVL68:
	.loc 1 314 19 discriminator 1 view .LVU203
	cbz	r3, .L58
	.loc 1 321 5 is_stmt 1 view .LVU204
	.loc 1 321 16 is_stmt 0 view .LVU205
	ldr	r3, [r0, #4]
	.loc 1 321 7 view .LVU206
	cbz	r3, .L67
	.loc 1 328 5 is_stmt 1 view .LVU207
	.loc 1 328 7 is_stmt 0 view .LVU208
	cbz	r2, .L68
.LBB6:
	.loc 1 335 13 view .LVU209
	movs	r0, #0
.LVL69:
	.loc 1 335 13 view .LVU210
	b	.L62
.LVL70:
.L58:
	.loc 1 335 13 view .LVU211
.LBE6:
	.loc 1 316 9 is_stmt 1 view .LVU212
	.loc 1 316 9 view .LVU213
	ldr	r3, .L70
	mov	r2, #316
.LVL71:
	.loc 1 316 9 is_stmt 0 view .LVU214
	ldr	r1, .L70+4
.LVL72:
	.loc 1 316 9 view .LVU215
	ldr	r0, .L70+8
.LVL73:
	.loc 1 316 9 view .LVU216
	bl	printf
.LVL74:
	.loc 1 316 9 is_stmt 1 view .LVU217
	.loc 1 316 58 view .LVU218
	.loc 1 317 9 view .LVU219
	.loc 1 317 16 is_stmt 0 view .LVU220
	movs	r0, #1
	b	.L57
.LVL75:
.L67:
	.loc 1 323 9 is_stmt 1 view .LVU221
	.loc 1 323 9 view .LVU222
	ldr	r3, .L70
	movw	r2, #323
.LVL76:
	.loc 1 323 9 is_stmt 0 view .LVU223
	ldr	r1, .L70+4
.LVL77:
	.loc 1 323 9 view .LVU224
	ldr	r0, .L70+12
.LVL78:
	.loc 1 323 9 view .LVU225
	bl	printf
.LVL79:
	.loc 1 323 9 is_stmt 1 view .LVU226
	.loc 1 323 38 view .LVU227
	.loc 1 324 9 view .LVU228
	.loc 1 324 16 is_stmt 0 view .LVU229
	movs	r0, #1
	b	.L57
.LVL80:
.L68:
	.loc 1 330 9 is_stmt 1 view .LVU230
	.loc 1 330 9 view .LVU231
	ldr	r3, .L70
	mov	r2, #330
.LVL81:
	.loc 1 330 9 is_stmt 0 view .LVU232
	ldr	r1, .L70+4
.LVL82:
	.loc 1 330 9 view .LVU233
	ldr	r0, .L70+16
.LVL83:
	.loc 1 330 9 view .LVU234
	bl	printf
.LVL84:
	.loc 1 330 9 is_stmt 1 view .LVU235
	.loc 1 330 47 view .LVU236
	.loc 1 331 9 view .LVU237
	.loc 1 331 16 is_stmt 0 view .LVU238
	movs	r0, #1
	b	.L57
.LVL85:
.L63:
.LBB7:
	.loc 1 337 9 is_stmt 1 discriminator 3 view .LVU239
	.loc 1 337 28 is_stmt 0 discriminator 3 view .LVU240
	ldr	r3, [ip]
	.loc 1 337 33 discriminator 3 view .LVU241
	ldr	r3, [r3]
	.loc 1 337 38 discriminator 3 view .LVU242
	subs	r3, r3, #1
	.loc 1 337 20 discriminator 3 view .LVU243
	ldr	r4, .L70+20
	ldr	r4, [r4, r3, lsl #2]
	.loc 1 337 55 discriminator 3 view .LVU244
	rsb	r3, r0, r0, lsl #3
	lsls	r3, r3, #2
	adds	r3, r3, #8
	add	r3, r3, r2
	.loc 1 337 53 discriminator 3 view .LVU245
	str	r3, [r4, r0, lsl #2]
	.loc 1 335 24 is_stmt 1 discriminator 3 view .LVU246
	adds	r0, r0, #1
.LVL86:
.L62:
	.loc 1 335 19 discriminator 1 view .LVU247
	cmp	r0, #3
	ble	.L63
.LBE7:
	.loc 1 340 5 view .LVU248
	.loc 1 340 24 is_stmt 0 view .LVU249
	ldr	r3, [ip]
	.loc 1 340 29 view .LVU250
	ldr	r3, [r3]
	.loc 1 340 34 view .LVU251
	subs	r3, r3, #1
	.loc 1 340 16 view .LVU252
	ldr	r4, .L70+20
	ldr	r3, [r4, r3, lsl #2]
	.loc 1 340 54 view .LVU253
	ldr	r2, [r2, #4]
.LVL87:
	.loc 1 340 50 view .LVU254
	str	r2, [r3, #16]
	.loc 1 344 5 is_stmt 1 view .LVU255
.LVL88:
	.loc 1 345 5 view .LVU256
	.syntax unified
@ 345 "../Core/Src/tee_client_api.c" 1
	MOV r2, R4

@ 0 "" 2
.LVL89:
	.loc 1 346 5 view .LVU257
@ 346 "../Core/Src/tee_client_api.c" 1
	MOV r3, R5

@ 0 "" 2
	.loc 1 347 5 view .LVU258
	.loc 1 347 47 is_stmt 0 view .LVU259
	.thumb
	.syntax unified
	ldr	r0, [ip]
.LVL90:
	.loc 1 347 52 view .LVU260
	ldr	r0, [r0]
	.loc 1 347 57 view .LVU261
	subs	r0, r0, #1
	.loc 1 347 15 view .LVU262
	ldr	r0, [r4, r0, lsl #2]
.LVL91:
	.loc 1 350 5 is_stmt 1 view .LVU263
	.syntax unified
@ 350 "../Core/Src/tee_client_api.c" 1
	MOV R4, r0

@ 0 "" 2
	.loc 1 352 5 view .LVU264
@ 352 "../Core/Src/tee_client_api.c" 1
	MOV R5, r1

@ 0 "" 2
	.loc 1 355 5 view .LVU265
@ 355 "../Core/Src/tee_client_api.c" 1
	svc #4
@ 0 "" 2
	.loc 1 358 5 view .LVU266
@ 358 "../Core/Src/tee_client_api.c" 1
	MOV r1, r4
@ 0 "" 2
.LVL92:
	.loc 1 358 5 is_stmt 0 view .LVU267
	.thumb
	.syntax unified
	mov	r0, r1
.LVL93:
	.loc 1 359 5 is_stmt 1 view .LVU268
	.syntax unified
@ 359 "../Core/Src/tee_client_api.c" 1
	MOV R4, r2

@ 0 "" 2
	.loc 1 360 5 view .LVU269
@ 360 "../Core/Src/tee_client_api.c" 1
	MOV R5, r3

@ 0 "" 2
	.loc 1 363 5 view .LVU270
	.loc 1 363 7 is_stmt 0 view .LVU271
	.thumb
	.syntax unified
	cbnz	r1, .L69
.LVL94:
.L57:
	.loc 1 367 1 view .LVU272
	pop	{r3, r4, r5, pc}
.LVL95:
.L69:
	.loc 1 364 16 view .LVU273
	movs	r0, #1
.LVL96:
	.loc 1 364 16 view .LVU274
	b	.L57
.L71:
	.align	2
.L70:
	.word	__func__.1
	.word	.LC0
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.word	internal_op
	.cfi_endproc
.LFE83:
	.size	TEEC_InvokeCommand, .-TEEC_InvokeCommand
	.section	.rodata.TEEC_AllocateSharedMemory.str1.4,"aMS",%progbits,1
	.align	2
.LC10:
	.ascii	"\033[0;31mERROR: %s:%d:%s(): \"Invalid parameter\"\015"
	.ascii	"\012\000"
	.align	2
.LC11:
	.ascii	"\033[0;31mERROR: %s:%d:%s(): \"Memory limit has bee"
	.ascii	"n reached\"\015\012\000"
	.align	2
.LC12:
	.ascii	"\033[0;31mERROR: %s:%d:%s(): \"Shared memory can no"
	.ascii	"t allocate\"\015\012\000"
	.section	.text.TEEC_AllocateSharedMemory,"ax",%progbits
	.align	1
	.global	TEEC_AllocateSharedMemory
	.syntax unified
	.thumb
	.thumb_func
	.type	TEEC_AllocateSharedMemory, %function
TEEC_AllocateSharedMemory:
.LVL97:
.LFB84:
	.loc 1 381 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 381 1 is_stmt 0 view .LVU276
	push	{r4, r5, r6, lr}
.LCFI6:
	.cfi_def_cfa_offset 16
	.cfi_offset 4, -16
	.cfi_offset 5, -12
	.cfi_offset 6, -8
	.cfi_offset 14, -4
	.loc 1 383 5 is_stmt 1 view .LVU277
	.loc 1 383 7 is_stmt 0 view .LVU278
	cbz	r1, .L73
	mov	r5, r1
	.loc 1 383 15 discriminator 1 view .LVU279
	cbz	r0, .L73
	.loc 1 389 5 is_stmt 1 view .LVU280
	.loc 1 389 11 is_stmt 0 view .LVU281
	ldr	r3, [r0]
	.loc 1 389 7 view .LVU282
	cbz	r3, .L80
	.loc 1 397 5 is_stmt 1 view .LVU283
	.loc 1 397 37 is_stmt 0 view .LVU284
	ldr	r6, [r1, #4]
	.loc 1 397 44 view .LVU285
	ldr	r3, .L83
	ldr	r4, [r3]
	adds	r3, r6, r4
	.loc 1 397 7 view .LVU286
	cmp	r3, #4096
	bhi	.L81
	.loc 1 404 5 is_stmt 1 view .LVU287
	.loc 1 404 29 is_stmt 0 view .LVU288
	movs	r1, #1
.LVL98:
	.loc 1 404 29 view .LVU289
	adds	r0, r6, r1
.LVL99:
	.loc 1 404 29 view .LVU290
	bl	calloc
.LVL100:
	.loc 1 404 17 view .LVU291
	str	r0, [r5]
	.loc 1 405 5 is_stmt 1 view .LVU292
	.loc 1 405 7 is_stmt 0 view .LVU293
	cbz	r0, .L82
	.loc 1 412 5 is_stmt 1 view .LVU294
	mov	r2, r6
	movs	r1, #0
	bl	memset
.LVL101:
	.loc 1 415 5 view .LVU295
	.loc 1 415 25 is_stmt 0 view .LVU296
	ldr	r3, [r5, #4]
	.loc 1 415 19 view .LVU297
	add	r4, r4, r3
	adds	r4, r4, #8
	ldr	r3, .L83
	str	r4, [r3]
	.loc 1 417 5 is_stmt 1 view .LVU298
	.loc 1 417 12 is_stmt 0 view .LVU299
	movs	r0, #0
.LVL102:
.L72:
	.loc 1 418 1 view .LVU300
	pop	{r4, r5, r6, pc}
.LVL103:
.L73:
	.loc 1 384 9 is_stmt 1 view .LVU301
	.loc 1 384 9 view .LVU302
	ldr	r3, .L83+4
	mov	r2, #384
	ldr	r1, .L83+8
.LVL104:
	.loc 1 384 9 is_stmt 0 view .LVU303
	ldr	r0, .L83+12
.LVL105:
	.loc 1 384 9 view .LVU304
	bl	printf
.LVL106:
	.loc 1 384 9 is_stmt 1 view .LVU305
	.loc 1 384 37 view .LVU306
	.loc 1 385 9 view .LVU307
	.loc 1 385 16 is_stmt 0 view .LVU308
	movs	r0, #1
	b	.L72
.LVL107:
.L80:
	.loc 1 392 9 is_stmt 1 view .LVU309
	.loc 1 392 9 view .LVU310
	ldr	r3, .L83+4
	mov	r2, #392
	ldr	r1, .L83+8
.LVL108:
	.loc 1 392 9 is_stmt 0 view .LVU311
	ldr	r0, .L83+16
.LVL109:
	.loc 1 392 9 view .LVU312
	bl	printf
.LVL110:
	.loc 1 392 9 is_stmt 1 view .LVU313
	.loc 1 392 38 view .LVU314
	.loc 1 393 9 view .LVU315
	.loc 1 393 16 is_stmt 0 view .LVU316
	movs	r0, #1
	b	.L72
.LVL111:
.L81:
	.loc 1 399 9 is_stmt 1 view .LVU317
	.loc 1 399 9 view .LVU318
	ldr	r3, .L83+4
	movw	r2, #399
	ldr	r1, .L83+8
.LVL112:
	.loc 1 399 9 is_stmt 0 view .LVU319
	ldr	r0, .L83+20
.LVL113:
	.loc 1 399 9 view .LVU320
	bl	printf
.LVL114:
	.loc 1 399 9 is_stmt 1 view .LVU321
	.loc 1 399 49 view .LVU322
	.loc 1 400 9 view .LVU323
	.loc 1 400 16 is_stmt 0 view .LVU324
	movs	r0, #1
	b	.L72
.L82:
	.loc 1 407 9 is_stmt 1 view .LVU325
	.loc 1 407 9 view .LVU326
	ldr	r3, .L83+4
	movw	r2, #407
	ldr	r1, .L83+8
	ldr	r0, .L83+24
	bl	printf
.LVL115:
	.loc 1 407 9 view .LVU327
	.loc 1 407 50 view .LVU328
	.loc 1 408 9 view .LVU329
	.loc 1 408 16 is_stmt 0 view .LVU330
	movs	r0, #1
	b	.L72
.L84:
	.align	2
.L83:
	.word	used_shm_size
	.word	__func__.0
	.word	.LC0
	.word	.LC10
	.word	.LC2
	.word	.LC11
	.word	.LC12
	.cfi_endproc
.LFE84:
	.size	TEEC_AllocateSharedMemory, .-TEEC_AllocateSharedMemory
	.section	.text.TEEC_ReleaseSharedMemory,"ax",%progbits
	.align	1
	.global	TEEC_ReleaseSharedMemory
	.syntax unified
	.thumb
	.thumb_func
	.type	TEEC_ReleaseSharedMemory, %function
TEEC_ReleaseSharedMemory:
.LVL116:
.LFB85:
	.loc 1 428 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 428 1 is_stmt 0 view .LVU332
	push	{r4, lr}
.LCFI7:
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	mov	r4, r0
	.loc 1 430 5 is_stmt 1 view .LVU333
	.loc 1 430 11 is_stmt 0 view .LVU334
	ldr	r0, [r0]
.LVL117:
	.loc 1 430 7 view .LVU335
	cbz	r0, .L85
	.loc 1 432 9 is_stmt 1 view .LVU336
	bl	free
.LVL118:
	.loc 1 433 9 view .LVU337
	.loc 1 433 45 is_stmt 0 view .LVU338
	ldr	r1, [r4, #4]
	.loc 1 433 39 view .LVU339
	ldr	r2, .L88
	ldr	r3, [r2]
	subs	r3, r3, r1
	subs	r3, r3, #8
	.loc 1 433 23 view .LVU340
	str	r3, [r2]
	.loc 1 437 5 is_stmt 1 view .LVU341
.L85:
	.loc 1 439 1 is_stmt 0 view .LVU342
	pop	{r4, pc}
.LVL119:
.L89:
	.loc 1 439 1 view .LVU343
	.align	2
.L88:
	.word	used_shm_size
	.cfi_endproc
.LFE85:
	.size	TEEC_ReleaseSharedMemory, .-TEEC_ReleaseSharedMemory
	.section	.rodata.__func__.0,"a"
	.align	2
	.type	__func__.0, %object
	.size	__func__.0, 26
__func__.0:
	.ascii	"TEEC_AllocateSharedMemory\000"
	.section	.rodata.__func__.1,"a"
	.align	2
	.type	__func__.1, %object
	.size	__func__.1, 19
__func__.1:
	.ascii	"TEEC_InvokeCommand\000"
	.section	.rodata.__func__.2,"a"
	.align	2
	.type	__func__.2, %object
	.size	__func__.2, 18
__func__.2:
	.ascii	"TEEC_CloseSession\000"
	.section	.rodata.__func__.3,"a"
	.align	2
	.type	__func__.3, %object
	.size	__func__.3, 14
__func__.3:
	.ascii	"check_context\000"
	.section	.rodata.__func__.4,"a"
	.align	2
	.type	__func__.4, %object
	.size	__func__.4, 17
__func__.4:
	.ascii	"TEEC_OpenSession\000"
	.section	.rodata.__func__.5,"a"
	.align	2
	.type	__func__.5, %object
	.size	__func__.5, 21
__func__.5:
	.ascii	"TEEC_FinalizeContext\000"
	.section	.rodata.__func__.6,"a"
	.align	2
	.type	__func__.6, %object
	.size	__func__.6, 23
__func__.6:
	.ascii	"TEEC_InitializeContext\000"
	.section	.bss.used_shm_size,"aw",%nobits
	.align	2
	.type	used_shm_size, %object
	.size	used_shm_size, 4
used_shm_size:
	.space	4
	.global	internal_op
	.section	.bss.internal_op,"aw",%nobits
	.align	2
	.type	internal_op, %object
	.size	internal_op, 8
internal_op:
	.space	8
	.text
.Letext0:
	.file 2 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/arm-none-eabi/include/machine/_default_types.h"
	.file 3 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/lib/gcc/arm-none-eabi/12.3.1/include/stddef.h"
	.file 4 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/arm-none-eabi/include/sys/_stdint.h"
	.file 5 "../Core/Inc/tee_common.h"
	.file 6 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/arm-none-eabi/include/string.h"
	.file 7 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/arm-none-eabi/include/stdio.h"
	.file 8 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/arm-none-eabi/include/stdlib.h"
	.file 9 "<built-in>"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0xca2
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF73
	.byte	0xc
	.4byte	.LASF74
	.4byte	.LASF75
	.4byte	.Ldebug_ranges0+0x30
	.4byte	0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x3
	.4byte	.LASF3
	.byte	0x2
	.byte	0x2b
	.byte	0x18
	.4byte	0x3c
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF2
	.uleb128 0x3
	.4byte	.LASF4
	.byte	0x2
	.byte	0x39
	.byte	0x19
	.4byte	0x56
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x3
	.4byte	.LASF6
	.byte	0x2
	.byte	0x4d
	.byte	0x18
	.4byte	0x69
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF7
	.uleb128 0x3
	.4byte	.LASF8
	.byte	0x2
	.byte	0x4f
	.byte	0x19
	.4byte	0x7c
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF12
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x3
	.byte	0xd6
	.byte	0x17
	.4byte	0x98
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF14
	.uleb128 0x5
	.byte	0x4
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF15
	.uleb128 0x6
	.4byte	0xb4
	.uleb128 0x7
	.byte	0x4
	.4byte	0xbb
	.uleb128 0x3
	.4byte	.LASF16
	.byte	0x4
	.byte	0x18
	.byte	0x13
	.4byte	0x30
	.uleb128 0x3
	.4byte	.LASF17
	.byte	0x4
	.byte	0x24
	.byte	0x14
	.4byte	0x4a
	.uleb128 0x3
	.4byte	.LASF18
	.byte	0x4
	.byte	0x2c
	.byte	0x13
	.4byte	0x5d
	.uleb128 0x3
	.4byte	.LASF19
	.byte	0x4
	.byte	0x30
	.byte	0x14
	.4byte	0x70
	.uleb128 0x7
	.byte	0x4
	.4byte	0xfc
	.uleb128 0x8
	.uleb128 0x9
	.byte	0x10
	.byte	0x5
	.byte	0x44
	.byte	0x9
	.4byte	0x143
	.uleb128 0xa
	.4byte	.LASF20
	.byte	0x5
	.byte	0x45
	.byte	0xb
	.4byte	0xea
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xa
	.4byte	.LASF21
	.byte	0x5
	.byte	0x46
	.byte	0xb
	.4byte	0xd2
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xa
	.4byte	.LASF22
	.byte	0x5
	.byte	0x47
	.byte	0xb
	.4byte	0xd2
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.uleb128 0xa
	.4byte	.LASF23
	.byte	0x5
	.byte	0x48
	.byte	0xa
	.4byte	0x143
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0xb
	.4byte	0xc6
	.4byte	0x153
	.uleb128 0xc
	.4byte	0x98
	.byte	0x7
	.byte	0
	.uleb128 0x3
	.4byte	.LASF24
	.byte	0x5
	.byte	0x49
	.byte	0x2
	.4byte	0xfd
	.uleb128 0x6
	.4byte	0x153
	.uleb128 0x9
	.byte	0x1c
	.byte	0x5
	.byte	0x4e
	.byte	0x9
	.4byte	0x1a9
	.uleb128 0xa
	.4byte	.LASF25
	.byte	0x5
	.byte	0x50
	.byte	0xb
	.4byte	0x1a9
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xa
	.4byte	.LASF26
	.byte	0x5
	.byte	0x51
	.byte	0xf
	.4byte	0xea
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xa
	.4byte	.LASF27
	.byte	0x5
	.byte	0x52
	.byte	0x16
	.4byte	0x1b9
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0xd
	.ascii	"id\000"
	.byte	0x5
	.byte	0x53
	.byte	0xe
	.4byte	0xde
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.byte	0
	.uleb128 0xb
	.4byte	0xb2
	.4byte	0x1b9
	.uleb128 0xc
	.4byte	0x98
	.byte	0x3
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x15f
	.uleb128 0x3
	.4byte	.LASF28
	.byte	0x5
	.byte	0x54
	.byte	0x2
	.4byte	0x164
	.uleb128 0x3
	.4byte	.LASF29
	.byte	0x5
	.byte	0x57
	.byte	0xd
	.4byte	0x91
	.uleb128 0x9
	.byte	0xc
	.byte	0x5
	.byte	0x5b
	.byte	0x9
	.4byte	0x20e
	.uleb128 0xa
	.4byte	.LASF30
	.byte	0x5
	.byte	0x5c
	.byte	0x11
	.4byte	0x20e
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xa
	.4byte	.LASF31
	.byte	0x5
	.byte	0x5d
	.byte	0x11
	.4byte	0x9f
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xa
	.4byte	.LASF32
	.byte	0x5
	.byte	0x5e
	.byte	0x11
	.4byte	0xea
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.4byte	0xc6
	.uleb128 0x3
	.4byte	.LASF33
	.byte	0x5
	.byte	0x5f
	.byte	0x2
	.4byte	0x1d7
	.uleb128 0x9
	.byte	0x8
	.byte	0x5
	.byte	0x62
	.byte	0x9
	.4byte	0x248
	.uleb128 0xa
	.4byte	.LASF30
	.byte	0x5
	.byte	0x63
	.byte	0x8
	.4byte	0xb2
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xa
	.4byte	.LASF31
	.byte	0x5
	.byte	0x64
	.byte	0x9
	.4byte	0x9f
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF34
	.byte	0x5
	.byte	0x65
	.byte	0x2
	.4byte	0x220
	.uleb128 0x9
	.byte	0xc
	.byte	0x5
	.byte	0x67
	.byte	0x9
	.4byte	0x28b
	.uleb128 0xa
	.4byte	.LASF35
	.byte	0x5
	.byte	0x69
	.byte	0x15
	.4byte	0x28b
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xa
	.4byte	.LASF31
	.byte	0x5
	.byte	0x6a
	.byte	0x9
	.4byte	0x9f
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xa
	.4byte	.LASF36
	.byte	0x5
	.byte	0x6b
	.byte	0x9
	.4byte	0x9f
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x214
	.uleb128 0x3
	.4byte	.LASF37
	.byte	0x5
	.byte	0x6c
	.byte	0x2
	.4byte	0x254
	.uleb128 0x9
	.byte	0x8
	.byte	0x5
	.byte	0x71
	.byte	0x9
	.4byte	0x2c1
	.uleb128 0xd
	.ascii	"a\000"
	.byte	0x5
	.byte	0x72
	.byte	0xb
	.4byte	0xea
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xd
	.ascii	"b\000"
	.byte	0x5
	.byte	0x73
	.byte	0xb
	.4byte	0xea
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF38
	.byte	0x5
	.byte	0x74
	.byte	0x2
	.4byte	0x29d
	.uleb128 0x9
	.byte	0x1c
	.byte	0x5
	.byte	0x78
	.byte	0x9
	.4byte	0x304
	.uleb128 0xa
	.4byte	.LASF39
	.byte	0x5
	.byte	0x7a
	.byte	0x1b
	.4byte	0x248
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xa
	.4byte	.LASF40
	.byte	0x5
	.byte	0x7b
	.byte	0x21
	.4byte	0x291
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xa
	.4byte	.LASF41
	.byte	0x5
	.byte	0x7c
	.byte	0xd
	.4byte	0x2c1
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.byte	0
	.uleb128 0x3
	.4byte	.LASF42
	.byte	0x5
	.byte	0x7d
	.byte	0x2
	.4byte	0x2cd
	.uleb128 0x9
	.byte	0x8
	.byte	0x5
	.byte	0x80
	.byte	0x9
	.4byte	0x337
	.uleb128 0xd
	.ascii	"id\000"
	.byte	0x5
	.byte	0x83
	.byte	0xe
	.4byte	0xea
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xa
	.4byte	.LASF27
	.byte	0x5
	.byte	0x84
	.byte	0xc
	.4byte	0x337
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x153
	.uleb128 0x3
	.4byte	.LASF43
	.byte	0x5
	.byte	0x85
	.byte	0x2
	.4byte	0x310
	.uleb128 0x9
	.byte	0x8
	.byte	0x5
	.byte	0x88
	.byte	0x9
	.4byte	0x370
	.uleb128 0xd
	.ascii	"ctx\000"
	.byte	0x5
	.byte	0x8a
	.byte	0x10
	.4byte	0x370
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xd
	.ascii	"id\000"
	.byte	0x5
	.byte	0x8b
	.byte	0xb
	.4byte	0xea
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x33d
	.uleb128 0x3
	.4byte	.LASF44
	.byte	0x5
	.byte	0x8c
	.byte	0x2
	.4byte	0x349
	.uleb128 0x9
	.byte	0x78
	.byte	0x5
	.byte	0x8f
	.byte	0x9
	.4byte	0x3b9
	.uleb128 0xa
	.4byte	.LASF45
	.byte	0x5
	.byte	0x90
	.byte	0xb
	.4byte	0xea
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xa
	.4byte	.LASF26
	.byte	0x5
	.byte	0x91
	.byte	0xb
	.4byte	0xea
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xa
	.4byte	.LASF25
	.byte	0x5
	.byte	0x92
	.byte	0x11
	.4byte	0x3b9
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0xb
	.4byte	0x304
	.4byte	0x3c9
	.uleb128 0xc
	.4byte	0x98
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF46
	.byte	0x5
	.byte	0x94
	.byte	0x2
	.4byte	0x382
	.uleb128 0xb
	.4byte	0x3e5
	.4byte	0x3e5
	.uleb128 0xc
	.4byte	0x98
	.byte	0x1
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x1bf
	.uleb128 0xe
	.4byte	.LASF55
	.byte	0x1
	.byte	0x16
	.byte	0x17
	.4byte	0x3d5
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	internal_op
	.uleb128 0xf
	.4byte	.LASF76
	.byte	0x1
	.byte	0x18
	.byte	0xf
	.4byte	0x9f
	.byte	0x5
	.byte	0x3
	.4byte	used_shm_size
	.uleb128 0x10
	.byte	0x1
	.4byte	.LASF47
	.byte	0x6
	.byte	0x21
	.byte	0x9
	.byte	0x1
	.4byte	0xb2
	.byte	0x1
	.4byte	0x433
	.uleb128 0x11
	.4byte	0xb2
	.uleb128 0x11
	.4byte	0x91
	.uleb128 0x11
	.4byte	0x9f
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.4byte	.LASF77
	.byte	0x8
	.byte	0x5e
	.byte	0x6
	.byte	0x1
	.byte	0x1
	.4byte	0x448
	.uleb128 0x11
	.4byte	0xb2
	.byte	0
	.uleb128 0x10
	.byte	0x1
	.4byte	.LASF48
	.byte	0x7
	.byte	0xce
	.byte	0x5
	.byte	0x1
	.4byte	0x91
	.byte	0x1
	.4byte	0x462
	.uleb128 0x11
	.4byte	0xc0
	.uleb128 0x13
	.byte	0
	.uleb128 0x10
	.byte	0x1
	.4byte	.LASF49
	.byte	0x8
	.byte	0x5a
	.byte	0x7
	.byte	0x1
	.4byte	0xb2
	.byte	0x1
	.4byte	0x480
	.uleb128 0x11
	.4byte	0x9f
	.uleb128 0x11
	.4byte	0x9f
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.4byte	.LASF60
	.byte	0x1
	.2byte	0x1ab
	.byte	0x6
	.byte	0x1
	.4byte	.LFB85
	.4byte	.LFE85
	.4byte	.LLST43
	.byte	0x1
	.4byte	0x4bb
	.uleb128 0x15
	.ascii	"shm\000"
	.byte	0x1
	.2byte	0x1ab
	.byte	0x32
	.4byte	0x28b
	.4byte	.LLST44
	.4byte	.LVUS44
	.uleb128 0x16
	.4byte	.LVL118
	.4byte	0x433
	.byte	0
	.uleb128 0x17
	.byte	0x1
	.4byte	.LASF50
	.byte	0x1
	.2byte	0x17b
	.byte	0xd
	.byte	0x1
	.4byte	0x1cb
	.4byte	.LFB84
	.4byte	.LFE84
	.4byte	.LLST40
	.byte	0x1
	.4byte	0x604
	.uleb128 0x15
	.ascii	"ctx\000"
	.byte	0x1
	.2byte	0x17b
	.byte	0x35
	.4byte	0x370
	.4byte	.LLST41
	.4byte	.LVUS41
	.uleb128 0x15
	.ascii	"shm\000"
	.byte	0x1
	.2byte	0x17c
	.byte	0x3a
	.4byte	0x28b
	.4byte	.LLST42
	.4byte	.LVUS42
	.uleb128 0x18
	.4byte	.LASF57
	.4byte	0x614
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__func__.0
	.uleb128 0x19
	.4byte	.LVL100
	.4byte	0x462
	.4byte	0x52e
	.uleb128 0x1a
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x76
	.sleb128 1
	.uleb128 0x1a
	.byte	0x1
	.byte	0x51
	.byte	0x1
	.byte	0x31
	.byte	0
	.uleb128 0x19
	.4byte	.LVL101
	.4byte	0xc98
	.4byte	0x547
	.uleb128 0x1a
	.byte	0x1
	.byte	0x51
	.byte	0x1
	.byte	0x30
	.uleb128 0x1a
	.byte	0x1
	.byte	0x52
	.byte	0x2
	.byte	0x76
	.sleb128 0
	.byte	0
	.uleb128 0x19
	.4byte	.LVL106
	.4byte	0x448
	.4byte	0x577
	.uleb128 0x1a
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC10
	.uleb128 0x1a
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LC0
	.uleb128 0x1a
	.byte	0x1
	.byte	0x52
	.byte	0x3
	.byte	0xa
	.2byte	0x180
	.uleb128 0x1a
	.byte	0x1
	.byte	0x53
	.byte	0x5
	.byte	0x3
	.4byte	__func__.0
	.byte	0
	.uleb128 0x19
	.4byte	.LVL110
	.4byte	0x448
	.4byte	0x5a7
	.uleb128 0x1a
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC2
	.uleb128 0x1a
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LC0
	.uleb128 0x1a
	.byte	0x1
	.byte	0x52
	.byte	0x3
	.byte	0xa
	.2byte	0x188
	.uleb128 0x1a
	.byte	0x1
	.byte	0x53
	.byte	0x5
	.byte	0x3
	.4byte	__func__.0
	.byte	0
	.uleb128 0x19
	.4byte	.LVL114
	.4byte	0x448
	.4byte	0x5d7
	.uleb128 0x1a
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC11
	.uleb128 0x1a
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LC0
	.uleb128 0x1a
	.byte	0x1
	.byte	0x52
	.byte	0x3
	.byte	0xa
	.2byte	0x18f
	.uleb128 0x1a
	.byte	0x1
	.byte	0x53
	.byte	0x5
	.byte	0x3
	.4byte	__func__.0
	.byte	0
	.uleb128 0x1b
	.4byte	.LVL115
	.4byte	0x448
	.uleb128 0x1a
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC12
	.uleb128 0x1a
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LC0
	.uleb128 0x1a
	.byte	0x1
	.byte	0x52
	.byte	0x3
	.byte	0xa
	.2byte	0x197
	.uleb128 0x1a
	.byte	0x1
	.byte	0x53
	.byte	0x5
	.byte	0x3
	.4byte	__func__.0
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	0xbb
	.4byte	0x614
	.uleb128 0xc
	.4byte	0x98
	.byte	0x19
	.byte	0
	.uleb128 0x6
	.4byte	0x604
	.uleb128 0x17
	.byte	0x1
	.4byte	.LASF51
	.byte	0x1
	.2byte	0x132
	.byte	0xd
	.byte	0x1
	.4byte	0x1cb
	.4byte	.LFB83
	.4byte	.LFE83
	.4byte	.LLST31
	.byte	0x1
	.4byte	0x792
	.uleb128 0x1c
	.4byte	.LASF52
	.byte	0x1
	.2byte	0x132
	.byte	0x2e
	.4byte	0x792
	.4byte	.LLST32
	.4byte	.LVUS32
	.uleb128 0x1c
	.4byte	.LASF53
	.byte	0x1
	.2byte	0x133
	.byte	0x2e
	.4byte	0xea
	.4byte	.LLST33
	.4byte	.LVUS33
	.uleb128 0x15
	.ascii	"op\000"
	.byte	0x1
	.2byte	0x134
	.byte	0x35
	.4byte	0x798
	.4byte	.LLST34
	.4byte	.LVUS34
	.uleb128 0x1c
	.4byte	.LASF54
	.byte	0x1
	.2byte	0x135
	.byte	0x2f
	.4byte	0x79e
	.4byte	.LLST35
	.4byte	.LVUS35
	.uleb128 0x1d
	.4byte	.LASF56
	.byte	0x1
	.2byte	0x137
	.byte	0x9
	.4byte	0x91
	.4byte	.LLST36
	.4byte	.LVUS36
	.uleb128 0x18
	.4byte	.LASF57
	.4byte	0x7b4
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__func__.1
	.uleb128 0x1d
	.4byte	.LASF58
	.byte	0x1
	.2byte	0x158
	.byte	0xe
	.4byte	0xea
	.4byte	.LLST37
	.4byte	.LVUS37
	.uleb128 0x1e
	.4byte	.LASF78
	.byte	0x1
	.2byte	0x158
	.byte	0x1f
	.4byte	0xea
	.uleb128 0x1d
	.4byte	.LASF59
	.byte	0x1
	.2byte	0x15b
	.byte	0xf
	.4byte	0x79e
	.4byte	.LLST38
	.4byte	.LVUS38
	.uleb128 0x1f
	.4byte	.Ldebug_ranges0+0x18
	.4byte	0x705
	.uleb128 0x20
	.ascii	"i\000"
	.byte	0x1
	.2byte	0x14f
	.byte	0xd
	.4byte	0x91
	.4byte	.LLST39
	.4byte	.LVUS39
	.byte	0
	.uleb128 0x19
	.4byte	.LVL74
	.4byte	0x448
	.4byte	0x735
	.uleb128 0x1a
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC7
	.uleb128 0x1a
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LC0
	.uleb128 0x1a
	.byte	0x1
	.byte	0x52
	.byte	0x3
	.byte	0xa
	.2byte	0x13c
	.uleb128 0x1a
	.byte	0x1
	.byte	0x53
	.byte	0x5
	.byte	0x3
	.4byte	__func__.1
	.byte	0
	.uleb128 0x19
	.4byte	.LVL79
	.4byte	0x448
	.4byte	0x765
	.uleb128 0x1a
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC8
	.uleb128 0x1a
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LC0
	.uleb128 0x1a
	.byte	0x1
	.byte	0x52
	.byte	0x3
	.byte	0xa
	.2byte	0x143
	.uleb128 0x1a
	.byte	0x1
	.byte	0x53
	.byte	0x5
	.byte	0x3
	.4byte	__func__.1
	.byte	0
	.uleb128 0x1b
	.4byte	.LVL84
	.4byte	0x448
	.uleb128 0x1a
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC9
	.uleb128 0x1a
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LC0
	.uleb128 0x1a
	.byte	0x1
	.byte	0x52
	.byte	0x3
	.byte	0xa
	.2byte	0x14a
	.uleb128 0x1a
	.byte	0x1
	.byte	0x53
	.byte	0x5
	.byte	0x3
	.4byte	__func__.1
	.byte	0
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x376
	.uleb128 0x7
	.byte	0x4
	.4byte	0x3c9
	.uleb128 0x7
	.byte	0x4
	.4byte	0xea
	.uleb128 0xb
	.4byte	0xbb
	.4byte	0x7b4
	.uleb128 0xc
	.4byte	0x98
	.byte	0x12
	.byte	0
	.uleb128 0x6
	.4byte	0x7a4
	.uleb128 0x14
	.byte	0x1
	.4byte	.LASF61
	.byte	0x1
	.2byte	0x10c
	.byte	0x6
	.byte	0x1
	.4byte	.LFB82
	.4byte	.LFE82
	.4byte	.LLST27
	.byte	0x1
	.4byte	0x851
	.uleb128 0x1c
	.4byte	.LASF52
	.byte	0x1
	.2byte	0x10c
	.byte	0x26
	.4byte	0x792
	.4byte	.LLST28
	.4byte	.LVUS28
	.uleb128 0x1d
	.4byte	.LASF62
	.byte	0x1
	.2byte	0x10e
	.byte	0x6
	.4byte	0x91
	.4byte	.LLST29
	.4byte	.LVUS29
	.uleb128 0x18
	.4byte	.LASF57
	.4byte	0x861
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__func__.2
	.uleb128 0x1d
	.4byte	.LASF58
	.byte	0x1
	.2byte	0x11b
	.byte	0xe
	.4byte	0xea
	.4byte	.LLST30
	.4byte	.LVUS30
	.uleb128 0x1b
	.4byte	.LVL65
	.4byte	0x448
	.uleb128 0x1a
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC6
	.uleb128 0x1a
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LC0
	.uleb128 0x1a
	.byte	0x1
	.byte	0x52
	.byte	0x3
	.byte	0xa
	.2byte	0x112
	.uleb128 0x1a
	.byte	0x1
	.byte	0x53
	.byte	0x5
	.byte	0x3
	.4byte	__func__.2
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	0xbb
	.4byte	0x861
	.uleb128 0xc
	.4byte	0x98
	.byte	0x11
	.byte	0
	.uleb128 0x6
	.4byte	0x851
	.uleb128 0x21
	.byte	0x1
	.4byte	.LASF63
	.byte	0x1
	.byte	0xbc
	.byte	0xd
	.byte	0x1
	.4byte	0x1cb
	.4byte	.LFB81
	.4byte	.LFE81
	.4byte	.LLST14
	.byte	0x1
	.4byte	0x9e6
	.uleb128 0x22
	.ascii	"ctx\000"
	.byte	0x1
	.byte	0xbc
	.byte	0x2c
	.4byte	0x370
	.4byte	.LLST15
	.4byte	.LVUS15
	.uleb128 0x23
	.4byte	.LASF52
	.byte	0x1
	.byte	0xbd
	.byte	0x17
	.4byte	0x792
	.4byte	.LLST16
	.4byte	.LVUS16
	.uleb128 0x23
	.4byte	.LASF64
	.byte	0x1
	.byte	0xbe
	.byte	0x19
	.4byte	0x1b9
	.4byte	.LLST17
	.4byte	.LVUS17
	.uleb128 0x23
	.4byte	.LASF65
	.byte	0x1
	.byte	0xbf
	.byte	0x12
	.4byte	0xea
	.4byte	.LLST18
	.4byte	.LVUS18
	.uleb128 0x23
	.4byte	.LASF66
	.byte	0x1
	.byte	0xc0
	.byte	0x15
	.4byte	0xf6
	.4byte	.LLST19
	.4byte	.LVUS19
	.uleb128 0x23
	.4byte	.LASF67
	.byte	0x1
	.byte	0xc1
	.byte	0x19
	.4byte	0x798
	.4byte	.LLST20
	.4byte	.LVUS20
	.uleb128 0x23
	.4byte	.LASF54
	.byte	0x1
	.byte	0xc2
	.byte	0x13
	.4byte	0x79e
	.4byte	.LLST21
	.4byte	.LVUS21
	.uleb128 0x24
	.4byte	.LASF56
	.byte	0x1
	.byte	0xc4
	.byte	0x9
	.4byte	0x91
	.4byte	.LLST22
	.4byte	.LVUS22
	.uleb128 0x25
	.ascii	"err\000"
	.byte	0x1
	.2byte	0x103
	.byte	0x2
	.uleb128 0x18
	.4byte	.LASF57
	.4byte	0x9f6
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__func__.4
	.uleb128 0x24
	.4byte	.LASF68
	.byte	0x1
	.byte	0xf2
	.byte	0xe
	.4byte	0xea
	.4byte	.LLST23
	.4byte	.LVUS23
	.uleb128 0x24
	.4byte	.LASF59
	.byte	0x1
	.byte	0xf3
	.byte	0xf
	.4byte	0x79e
	.4byte	.LLST24
	.4byte	.LVUS24
	.uleb128 0x26
	.4byte	.LBB4
	.4byte	.LBE4
	.4byte	0x986
	.uleb128 0x27
	.ascii	"i\000"
	.byte	0x1
	.byte	0xde
	.byte	0xb
	.4byte	0x91
	.4byte	.LLST25
	.4byte	.LVUS25
	.byte	0
	.uleb128 0x26
	.4byte	.LBB5
	.4byte	.LBE5
	.4byte	0x9a6
	.uleb128 0x27
	.ascii	"i\000"
	.byte	0x1
	.byte	0xe6
	.byte	0xb
	.4byte	0x91
	.4byte	.LLST26
	.4byte	.LVUS26
	.byte	0
	.uleb128 0x19
	.4byte	.LVL41
	.4byte	0xbb4
	.4byte	0x9ba
	.uleb128 0x1a
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.byte	0
	.uleb128 0x1b
	.4byte	.LVL42
	.4byte	0x448
	.uleb128 0x1a
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC5
	.uleb128 0x1a
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LC0
	.uleb128 0x1a
	.byte	0x1
	.byte	0x52
	.byte	0x2
	.byte	0x8
	.byte	0xcf
	.uleb128 0x1a
	.byte	0x1
	.byte	0x53
	.byte	0x5
	.byte	0x3
	.4byte	__func__.4
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	0xbb
	.4byte	0x9f6
	.uleb128 0xc
	.4byte	0x98
	.byte	0x10
	.byte	0
	.uleb128 0x6
	.4byte	0x9e6
	.uleb128 0x28
	.byte	0x1
	.4byte	.LASF69
	.byte	0x1
	.byte	0x92
	.byte	0x6
	.byte	0x1
	.4byte	.LFB80
	.4byte	.LFE80
	.4byte	.LLST10
	.byte	0x1
	.4byte	0xa9b
	.uleb128 0x22
	.ascii	"ctx\000"
	.byte	0x1
	.byte	0x92
	.byte	0x29
	.4byte	0x370
	.4byte	.LLST11
	.4byte	.LVUS11
	.uleb128 0x24
	.4byte	.LASF62
	.byte	0x1
	.byte	0x94
	.byte	0x6
	.4byte	0x91
	.4byte	.LLST12
	.4byte	.LVUS12
	.uleb128 0x18
	.4byte	.LASF57
	.4byte	0xaab
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__func__.5
	.uleb128 0x24
	.4byte	.LASF58
	.byte	0x1
	.byte	0xa2
	.byte	0xe
	.4byte	0xea
	.4byte	.LLST13
	.4byte	.LVUS13
	.uleb128 0x19
	.4byte	.LVL32
	.4byte	0x448
	.4byte	0xa91
	.uleb128 0x1a
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC4
	.uleb128 0x1a
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LC0
	.uleb128 0x1a
	.byte	0x1
	.byte	0x52
	.byte	0x2
	.byte	0x8
	.byte	0x98
	.uleb128 0x1a
	.byte	0x1
	.byte	0x53
	.byte	0x5
	.byte	0x3
	.4byte	__func__.5
	.byte	0
	.uleb128 0x16
	.4byte	.LVL38
	.4byte	0x433
	.byte	0
	.uleb128 0xb
	.4byte	0xbb
	.4byte	0xaab
	.uleb128 0xc
	.4byte	0x98
	.byte	0x14
	.byte	0
	.uleb128 0x6
	.4byte	0xa9b
	.uleb128 0x21
	.byte	0x1
	.4byte	.LASF70
	.byte	0x1
	.byte	0x52
	.byte	0xd
	.byte	0x1
	.4byte	0x1cb
	.4byte	.LFB79
	.4byte	.LFE79
	.4byte	.LLST3
	.byte	0x1
	.4byte	0xb9f
	.uleb128 0x23
	.4byte	.LASF71
	.byte	0x1
	.byte	0x52
	.byte	0x30
	.4byte	0xc0
	.4byte	.LLST4
	.4byte	.LVUS4
	.uleb128 0x22
	.ascii	"ctx\000"
	.byte	0x1
	.byte	0x53
	.byte	0x33
	.4byte	0x370
	.4byte	.LLST5
	.4byte	.LVUS5
	.uleb128 0x24
	.4byte	.LASF56
	.byte	0x1
	.byte	0x55
	.byte	0x9
	.4byte	0x91
	.4byte	.LLST6
	.4byte	.LVUS6
	.uleb128 0x18
	.4byte	.LASF57
	.4byte	0xbaf
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__func__.6
	.uleb128 0x24
	.4byte	.LASF68
	.byte	0x1
	.byte	0x76
	.byte	0xe
	.4byte	0xea
	.4byte	.LLST7
	.4byte	.LVUS7
	.uleb128 0x24
	.4byte	.LASF59
	.byte	0x1
	.byte	0x78
	.byte	0xf
	.4byte	0x79e
	.4byte	.LLST8
	.4byte	.LVUS8
	.uleb128 0x29
	.4byte	.Ldebug_ranges0+0
	.uleb128 0x27
	.ascii	"i\000"
	.byte	0x1
	.byte	0x5f
	.byte	0xd
	.4byte	0x91
	.4byte	.LLST9
	.4byte	.LVUS9
	.uleb128 0x19
	.4byte	.LVL18
	.4byte	0x462
	.4byte	0xb72
	.uleb128 0x1a
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.byte	0x31
	.uleb128 0x1a
	.byte	0x1
	.byte	0x51
	.byte	0x1
	.byte	0x4c
	.byte	0
	.uleb128 0x1b
	.4byte	.LVL26
	.4byte	0x448
	.uleb128 0x1a
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC3
	.uleb128 0x1a
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LC0
	.uleb128 0x1a
	.byte	0x1
	.byte	0x52
	.byte	0x2
	.byte	0x8
	.byte	0x6a
	.uleb128 0x1a
	.byte	0x1
	.byte	0x53
	.byte	0x5
	.byte	0x3
	.4byte	__func__.6
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	0xbb
	.4byte	0xbaf
	.uleb128 0xc
	.4byte	0x98
	.byte	0x16
	.byte	0
	.uleb128 0x6
	.4byte	0xb9f
	.uleb128 0x2a
	.4byte	.LASF79
	.byte	0x1
	.byte	0x35
	.byte	0x14
	.byte	0x1
	.4byte	0x1cb
	.4byte	.LFB78
	.4byte	.LFE78
	.4byte	.LLST0
	.byte	0x1
	.4byte	0xc51
	.uleb128 0x22
	.ascii	"ctx\000"
	.byte	0x1
	.byte	0x35
	.byte	0x30
	.4byte	0x370
	.4byte	.LLST1
	.4byte	.LVUS1
	.uleb128 0x18
	.4byte	.LASF57
	.4byte	0xc61
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.4byte	__func__.3
	.uleb128 0x19
	.4byte	.LVL4
	.4byte	0x448
	.4byte	0xc25
	.uleb128 0x1a
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC1
	.uleb128 0x1a
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LC0
	.uleb128 0x1a
	.byte	0x1
	.byte	0x52
	.byte	0x2
	.byte	0x8
	.byte	0x3a
	.uleb128 0x1a
	.byte	0x1
	.byte	0x53
	.byte	0x5
	.byte	0x3
	.4byte	__func__.3
	.byte	0
	.uleb128 0x1b
	.4byte	.LVL7
	.4byte	0x448
	.uleb128 0x1a
	.byte	0x1
	.byte	0x50
	.byte	0x5
	.byte	0x3
	.4byte	.LC2
	.uleb128 0x1a
	.byte	0x1
	.byte	0x51
	.byte	0x5
	.byte	0x3
	.4byte	.LC0
	.uleb128 0x1a
	.byte	0x1
	.byte	0x52
	.byte	0x2
	.byte	0x8
	.byte	0x42
	.uleb128 0x1a
	.byte	0x1
	.byte	0x53
	.byte	0x5
	.byte	0x3
	.4byte	__func__.3
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	0xbb
	.4byte	0xc61
	.uleb128 0xc
	.4byte	0x98
	.byte	0xd
	.byte	0
	.uleb128 0x6
	.4byte	0xc51
	.uleb128 0x2b
	.byte	0x1
	.4byte	.LASF72
	.byte	0x1
	.byte	0x21
	.byte	0x17
	.byte	0x1
	.4byte	0x3e5
	.4byte	.LFB77
	.4byte	.LFE77
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0xc98
	.uleb128 0x22
	.ascii	"id\000"
	.byte	0x1
	.byte	0x21
	.byte	0x36
	.4byte	0xea
	.4byte	.LLST2
	.4byte	.LVUS2
	.byte	0
	.uleb128 0x2c
	.byte	0x1
	.byte	0x1
	.4byte	.LASF47
	.4byte	.LASF80
	.byte	0x9
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",%progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.uleb128 0x2137
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.uleb128 0x2137
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.uleb128 0x2137
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.uleb128 0x2137
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.uleb128 0x2137
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.uleb128 0x2137
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.uleb128 0x2137
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0xa
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.uleb128 0x2137
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x2007
	.uleb128 0xe
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST43:
	.4byte	.LFB85
	.4byte	.LCFI7
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI7
	.4byte	.LFE85
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LVUS44:
	.uleb128 0
	.uleb128 .LVU335
	.uleb128 .LVU335
	.uleb128 .LVU343
	.uleb128 .LVU343
	.uleb128 0
.LLST44:
	.4byte	.LVL116
	.4byte	.LVL117
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL117
	.4byte	.LVL119
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL119
	.4byte	.LFE85
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST40:
	.4byte	.LFB84
	.4byte	.LCFI6
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI6
	.4byte	.LFE84
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	0
	.4byte	0
.LVUS41:
	.uleb128 0
	.uleb128 .LVU290
	.uleb128 .LVU290
	.uleb128 .LVU301
	.uleb128 .LVU301
	.uleb128 .LVU304
	.uleb128 .LVU304
	.uleb128 .LVU309
	.uleb128 .LVU309
	.uleb128 .LVU312
	.uleb128 .LVU312
	.uleb128 .LVU317
	.uleb128 .LVU317
	.uleb128 .LVU320
	.uleb128 .LVU320
	.uleb128 0
.LLST41:
	.4byte	.LVL97
	.4byte	.LVL99
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL99
	.4byte	.LVL103
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL103
	.4byte	.LVL105
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL105
	.4byte	.LVL107
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL107
	.4byte	.LVL109
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL109
	.4byte	.LVL111
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL111
	.4byte	.LVL113
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL113
	.4byte	.LFE84
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS42:
	.uleb128 0
	.uleb128 .LVU289
	.uleb128 .LVU289
	.uleb128 .LVU300
	.uleb128 .LVU300
	.uleb128 .LVU301
	.uleb128 .LVU301
	.uleb128 .LVU303
	.uleb128 .LVU303
	.uleb128 .LVU309
	.uleb128 .LVU309
	.uleb128 .LVU311
	.uleb128 .LVU311
	.uleb128 .LVU317
	.uleb128 .LVU317
	.uleb128 .LVU319
	.uleb128 .LVU319
	.uleb128 0
.LLST42:
	.4byte	.LVL97
	.4byte	.LVL98
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL98
	.4byte	.LVL102
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL102
	.4byte	.LVL103
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL103
	.4byte	.LVL104
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL104
	.4byte	.LVL107
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL107
	.4byte	.LVL108
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL108
	.4byte	.LVL111
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL111
	.4byte	.LVL112
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL112
	.4byte	.LFE84
	.2byte	0x1
	.byte	0x55
	.4byte	0
	.4byte	0
.LLST31:
	.4byte	.LFB83
	.4byte	.LCFI5
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI5
	.4byte	.LFE83
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	0
	.4byte	0
.LVUS32:
	.uleb128 0
	.uleb128 .LVU210
	.uleb128 .LVU210
	.uleb128 .LVU211
	.uleb128 .LVU211
	.uleb128 .LVU216
	.uleb128 .LVU216
	.uleb128 .LVU221
	.uleb128 .LVU221
	.uleb128 .LVU225
	.uleb128 .LVU225
	.uleb128 .LVU226
	.uleb128 .LVU226
	.uleb128 .LVU230
	.uleb128 .LVU230
	.uleb128 .LVU234
	.uleb128 .LVU234
	.uleb128 .LVU235
	.uleb128 .LVU235
	.uleb128 .LVU239
	.uleb128 .LVU239
	.uleb128 .LVU272
	.uleb128 .LVU272
	.uleb128 .LVU273
	.uleb128 .LVU273
	.uleb128 0
.LLST32:
	.4byte	.LVL66
	.4byte	.LVL69
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL69
	.4byte	.LVL70
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL70
	.4byte	.LVL73
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL73
	.4byte	.LVL75
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL75
	.4byte	.LVL78
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL78
	.4byte	.LVL79-1
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL79-1
	.4byte	.LVL80
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL80
	.4byte	.LVL83
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL83
	.4byte	.LVL84-1
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL84-1
	.4byte	.LVL85
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL85
	.4byte	.LVL94
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL94
	.4byte	.LVL95
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL95
	.4byte	.LFE83
	.2byte	0x1
	.byte	0x5c
	.4byte	0
	.4byte	0
.LVUS33:
	.uleb128 0
	.uleb128 .LVU215
	.uleb128 .LVU215
	.uleb128 .LVU221
	.uleb128 .LVU221
	.uleb128 .LVU224
	.uleb128 .LVU224
	.uleb128 .LVU230
	.uleb128 .LVU230
	.uleb128 .LVU233
	.uleb128 .LVU233
	.uleb128 .LVU239
	.uleb128 .LVU239
	.uleb128 .LVU267
	.uleb128 .LVU267
	.uleb128 0
.LLST33:
	.4byte	.LVL66
	.4byte	.LVL72
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL72
	.4byte	.LVL75
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL75
	.4byte	.LVL77
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL77
	.4byte	.LVL80
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL80
	.4byte	.LVL82
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL82
	.4byte	.LVL85
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL85
	.4byte	.LVL92
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL92
	.4byte	.LFE83
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS34:
	.uleb128 0
	.uleb128 .LVU214
	.uleb128 .LVU214
	.uleb128 .LVU221
	.uleb128 .LVU221
	.uleb128 .LVU223
	.uleb128 .LVU223
	.uleb128 .LVU230
	.uleb128 .LVU230
	.uleb128 .LVU232
	.uleb128 .LVU232
	.uleb128 .LVU239
	.uleb128 .LVU239
	.uleb128 .LVU254
	.uleb128 .LVU254
	.uleb128 0
.LLST34:
	.4byte	.LVL66
	.4byte	.LVL71
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL71
	.4byte	.LVL75
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	.LVL75
	.4byte	.LVL76
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL76
	.4byte	.LVL80
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	.LVL80
	.4byte	.LVL81
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL81
	.4byte	.LVL85
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	.LVL85
	.4byte	.LVL87
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL87
	.4byte	.LFE83
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS35:
	.uleb128 0
	.uleb128 .LVU203
	.uleb128 .LVU203
	.uleb128 0
.LLST35:
	.4byte	.LVL66
	.4byte	.LVL68
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL68
	.4byte	.LFE83
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS36:
	.uleb128 .LVU200
	.uleb128 .LVU268
	.uleb128 .LVU268
	.uleb128 .LVU272
	.uleb128 .LVU273
	.uleb128 .LVU274
	.uleb128 .LVU274
	.uleb128 0
.LLST36:
	.4byte	.LVL67
	.4byte	.LVL93
	.2byte	0x3
	.byte	0x9
	.byte	0xff
	.byte	0x9f
	.4byte	.LVL93
	.4byte	.LVL94
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL95
	.4byte	.LVL96
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL96
	.4byte	.LFE83
	.2byte	0x1
	.byte	0x51
	.4byte	0
	.4byte	0
.LVUS37:
	.uleb128 .LVU256
	.uleb128 .LVU257
.LLST37:
	.4byte	.LVL88
	.4byte	.LVL89
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS38:
	.uleb128 .LVU263
	.uleb128 .LVU268
	.uleb128 .LVU268
	.uleb128 .LVU272
	.uleb128 .LVU273
	.uleb128 0
.LLST38:
	.4byte	.LVL91
	.4byte	.LVL93
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL93
	.4byte	.LVL94
	.2byte	0xe
	.byte	0x7c
	.sleb128 0
	.byte	0x6
	.byte	0x6
	.byte	0x31
	.byte	0x1c
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	internal_op
	.byte	0x22
	.4byte	.LVL95
	.4byte	.LFE83
	.2byte	0xe
	.byte	0x7c
	.sleb128 0
	.byte	0x6
	.byte	0x6
	.byte	0x31
	.byte	0x1c
	.byte	0x32
	.byte	0x24
	.byte	0x3
	.4byte	internal_op
	.byte	0x22
	.4byte	0
	.4byte	0
.LVUS39:
	.uleb128 .LVU239
	.uleb128 .LVU260
.LLST39:
	.4byte	.LVL85
	.4byte	.LVL90
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LLST27:
	.4byte	.LFB82
	.4byte	.LCFI4
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI4
	.4byte	.LFE82
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LVUS28:
	.uleb128 0
	.uleb128 .LVU185
	.uleb128 .LVU185
	.uleb128 .LVU191
	.uleb128 .LVU191
	.uleb128 .LVU193
	.uleb128 .LVU193
	.uleb128 0
.LLST28:
	.4byte	.LVL58
	.4byte	.LVL61
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL61
	.4byte	.LVL63
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL63
	.4byte	.LVL64
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL64
	.4byte	.LFE82
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS29:
	.uleb128 .LVU178
	.uleb128 .LVU183
	.uleb128 .LVU183
	.uleb128 .LVU191
	.uleb128 .LVU191
	.uleb128 0
.LLST29:
	.4byte	.LVL59
	.4byte	.LVL60
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	.LVL60
	.4byte	.LVL63
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL63
	.4byte	.LFE82
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS30:
	.uleb128 .LVU186
	.uleb128 .LVU187
.LLST30:
	.4byte	.LVL61
	.4byte	.LVL62
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST14:
	.4byte	.LFB81
	.4byte	.LCFI3
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI3
	.4byte	.LFE81
	.2byte	0x2
	.byte	0x7d
	.sleb128 24
	.4byte	0
	.4byte	0
.LVUS15:
	.uleb128 0
	.uleb128 .LVU112
	.uleb128 .LVU112
	.uleb128 .LVU153
	.uleb128 .LVU153
	.uleb128 .LVU160
	.uleb128 .LVU160
	.uleb128 .LVU173
	.uleb128 .LVU173
	.uleb128 0
.LLST15:
	.4byte	.LVL39
	.4byte	.LVL41-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL41-1
	.4byte	.LVL49
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL49
	.4byte	.LVL52
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL52
	.4byte	.LVL56
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL56
	.4byte	.LFE81
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS16:
	.uleb128 0
	.uleb128 .LVU112
	.uleb128 .LVU112
	.uleb128 0
.LLST16:
	.4byte	.LVL39
	.4byte	.LVL41-1
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL41-1
	.4byte	.LFE81
	.2byte	0x1
	.byte	0x55
	.4byte	0
	.4byte	0
.LVUS17:
	.uleb128 0
	.uleb128 .LVU112
	.uleb128 .LVU112
	.uleb128 0
.LLST17:
	.4byte	.LVL39
	.4byte	.LVL41-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL41-1
	.4byte	.LFE81
	.2byte	0x1
	.byte	0x57
	.4byte	0
	.4byte	0
.LVUS18:
	.uleb128 0
	.uleb128 .LVU112
	.uleb128 .LVU112
	.uleb128 0
.LLST18:
	.4byte	.LVL39
	.4byte	.LVL41-1
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL41-1
	.4byte	.LFE81
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS19:
	.uleb128 0
	.uleb128 .LVU160
	.uleb128 .LVU160
	.uleb128 0
.LLST19:
	.4byte	.LVL39
	.4byte	.LVL52
	.2byte	0x2
	.byte	0x91
	.sleb128 0
	.4byte	.LVL52
	.4byte	.LFE81
	.2byte	0x2
	.byte	0x91
	.sleb128 0
	.4byte	0
	.4byte	0
.LVUS20:
	.uleb128 0
	.uleb128 .LVU160
	.uleb128 .LVU160
	.uleb128 0
.LLST20:
	.4byte	.LVL39
	.4byte	.LVL52
	.2byte	0x2
	.byte	0x91
	.sleb128 4
	.4byte	.LVL52
	.4byte	.LFE81
	.2byte	0x2
	.byte	0x91
	.sleb128 4
	.4byte	0
	.4byte	0
.LVUS21:
	.uleb128 0
	.uleb128 .LVU160
	.uleb128 .LVU160
	.uleb128 0
.LLST21:
	.4byte	.LVL39
	.4byte	.LVL52
	.2byte	0x2
	.byte	0x91
	.sleb128 8
	.4byte	.LVL52
	.4byte	.LFE81
	.2byte	0x2
	.byte	0x91
	.sleb128 8
	.4byte	0
	.4byte	0
.LVUS22:
	.uleb128 .LVU110
	.uleb128 .LVU156
	.uleb128 .LVU156
	.uleb128 .LVU159
	.uleb128 .LVU160
	.uleb128 .LVU173
	.uleb128 .LVU173
	.uleb128 .LVU174
.LLST22:
	.4byte	.LVL40
	.4byte	.LVL50
	.2byte	0x3
	.byte	0x9
	.byte	0xff
	.byte	0x9f
	.4byte	.LVL50
	.4byte	.LVL51
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL52
	.4byte	.LVL56
	.2byte	0x3
	.byte	0x9
	.byte	0xff
	.byte	0x9f
	.4byte	.LVL56
	.4byte	.LVL57
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LVUS23:
	.uleb128 .LVU148
	.uleb128 .LVU153
	.uleb128 .LVU153
	.uleb128 .LVU159
	.uleb128 .LVU173
	.uleb128 0
.LLST23:
	.4byte	.LVL47
	.4byte	.LVL49
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL49
	.4byte	.LVL51
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL56
	.4byte	.LFE81
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LVUS24:
	.uleb128 .LVU152
	.uleb128 .LVU159
	.uleb128 .LVU173
	.uleb128 0
.LLST24:
	.4byte	.LVL48
	.4byte	.LVL51
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL56
	.4byte	.LFE81
	.2byte	0x1
	.byte	0x52
	.4byte	0
	.4byte	0
.LVUS25:
	.uleb128 .LVU131
	.uleb128 .LVU141
.LLST25:
	.4byte	.LVL43
	.4byte	.LVL45
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LVUS26:
	.uleb128 .LVU160
	.uleb128 .LVU169
.LLST26:
	.4byte	.LVL52
	.4byte	.LVL54
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LLST10:
	.4byte	.LFB80
	.4byte	.LCFI2
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI2
	.4byte	.LFE80
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	0
	.4byte	0
.LVUS11:
	.uleb128 0
	.uleb128 .LVU89
	.uleb128 .LVU89
	.uleb128 .LVU99
	.uleb128 .LVU99
	.uleb128 .LVU104
	.uleb128 .LVU104
	.uleb128 0
.LLST11:
	.4byte	.LVL29
	.4byte	.LVL31
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL31
	.4byte	.LVL35
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL35
	.4byte	.LVL37
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL37
	.4byte	.LFE80
	.2byte	0x1
	.byte	0x54
	.4byte	0
	.4byte	0
.LVUS12:
	.uleb128 .LVU83
	.uleb128 .LVU93
	.uleb128 .LVU93
	.uleb128 .LVU99
	.uleb128 .LVU99
	.uleb128 .LVU101
	.uleb128 .LVU101
	.uleb128 0
.LLST12:
	.4byte	.LVL30
	.4byte	.LVL33
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	.LVL33
	.4byte	.LVL35
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL35
	.4byte	.LVL36
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	.LVL36
	.4byte	.LFE80
	.2byte	0x1
	.byte	0x55
	.4byte	0
	.4byte	0
.LVUS13:
	.uleb128 .LVU94
	.uleb128 .LVU95
.LLST13:
	.4byte	.LVL33
	.4byte	.LVL34
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST3:
	.4byte	.LFB79
	.4byte	.LCFI1
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI1
	.4byte	.LFE79
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	0
	.4byte	0
.LVUS4:
	.uleb128 0
	.uleb128 .LVU47
	.uleb128 .LVU47
	.uleb128 0
.LLST4:
	.4byte	.LVL12
	.4byte	.LVL17
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL17
	.4byte	.LFE79
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS5:
	.uleb128 0
	.uleb128 .LVU46
	.uleb128 .LVU46
	.uleb128 0
.LLST5:
	.4byte	.LVL12
	.4byte	.LVL16
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL16
	.4byte	.LFE79
	.2byte	0x1
	.byte	0x55
	.4byte	0
	.4byte	0
.LVUS6:
	.uleb128 .LVU34
	.uleb128 .LVU67
	.uleb128 .LVU67
	.uleb128 .LVU70
	.uleb128 .LVU71
	.uleb128 .LVU77
	.uleb128 .LVU77
	.uleb128 .LVU79
.LLST6:
	.4byte	.LVL13
	.4byte	.LVL23
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	.LVL23
	.4byte	.LVL24
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL25
	.4byte	.LVL27
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	.LVL27
	.4byte	.LVL28
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LVUS7:
	.uleb128 .LVU59
	.uleb128 .LVU64
	.uleb128 .LVU64
	.uleb128 .LVU70
	.uleb128 .LVU77
	.uleb128 0
.LLST7:
	.4byte	.LVL20
	.4byte	.LVL22
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL22
	.4byte	.LVL24
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL27
	.4byte	.LFE79
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LVUS8:
	.uleb128 .LVU63
	.uleb128 .LVU70
	.uleb128 .LVU77
	.uleb128 0
.LLST8:
	.4byte	.LVL21
	.4byte	.LVL24
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL27
	.4byte	.LFE79
	.2byte	0x1
	.byte	0x52
	.4byte	0
	.4byte	0
.LVUS9:
	.uleb128 .LVU36
	.uleb128 .LVU37
	.uleb128 .LVU37
	.uleb128 .LVU53
	.uleb128 .LVU53
	.uleb128 .LVU57
	.uleb128 .LVU71
	.uleb128 .LVU77
.LLST9:
	.4byte	.LVL13
	.4byte	.LVL14
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL14
	.4byte	.LVL19
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL19
	.4byte	.LVL20
	.2byte	0x3
	.byte	0x74
	.sleb128 -1
	.byte	0x9f
	.4byte	.LVL25
	.4byte	.LVL27
	.2byte	0x1
	.byte	0x54
	.4byte	0
	.4byte	0
.LLST0:
	.4byte	.LFB78
	.4byte	.LCFI0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI0
	.4byte	.LFE78
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LVUS1:
	.uleb128 0
	.uleb128 .LVU8
	.uleb128 .LVU8
	.uleb128 .LVU9
	.uleb128 .LVU9
	.uleb128 .LVU11
	.uleb128 .LVU11
	.uleb128 .LVU16
	.uleb128 .LVU16
	.uleb128 .LVU18
	.uleb128 .LVU18
	.uleb128 0
.LLST1:
	.4byte	.LVL0
	.4byte	.LVL1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL1
	.4byte	.LVL2
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL2
	.4byte	.LVL3
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL3
	.4byte	.LVL5
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL5
	.4byte	.LVL6
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL6
	.4byte	.LFE78
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS2:
	.uleb128 0
	.uleb128 .LVU28
	.uleb128 .LVU28
	.uleb128 .LVU29
	.uleb128 .LVU29
	.uleb128 .LVU30
	.uleb128 .LVU30
	.uleb128 0
.LLST2:
	.4byte	.LVL8
	.4byte	.LVL9
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL9
	.4byte	.LVL10
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL10
	.4byte	.LVL11
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL11
	.4byte	.LFE77
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x5c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB78
	.4byte	.LFE78-.LFB78
	.4byte	.LFB77
	.4byte	.LFE77-.LFB77
	.4byte	.LFB79
	.4byte	.LFE79-.LFB79
	.4byte	.LFB80
	.4byte	.LFE80-.LFB80
	.4byte	.LFB81
	.4byte	.LFE81-.LFB81
	.4byte	.LFB82
	.4byte	.LFE82-.LFB82
	.4byte	.LFB83
	.4byte	.LFE83-.LFB83
	.4byte	.LFB84
	.4byte	.LFE84-.LFB84
	.4byte	.LFB85
	.4byte	.LFE85-.LFB85
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LBB2
	.4byte	.LBE2
	.4byte	.LBB3
	.4byte	.LBE3
	.4byte	0
	.4byte	0
	.4byte	.LBB6
	.4byte	.LBE6
	.4byte	.LBB7
	.4byte	.LBE7
	.4byte	0
	.4byte	0
	.4byte	.LFB78
	.4byte	.LFE78
	.4byte	.LFB77
	.4byte	.LFE77
	.4byte	.LFB79
	.4byte	.LFE79
	.4byte	.LFB80
	.4byte	.LFE80
	.4byte	.LFB81
	.4byte	.LFE81
	.4byte	.LFB82
	.4byte	.LFE82
	.4byte	.LFB83
	.4byte	.LFE83
	.4byte	.LFB84
	.4byte	.LFE84
	.4byte	.LFB85
	.4byte	.LFE85
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF63:
	.ascii	"TEEC_OpenSession\000"
.LASF46:
	.ascii	"TEEC_Operation\000"
.LASF28:
	.ascii	"internal_operation_t\000"
.LASF26:
	.ascii	"paramTypes\000"
.LASF74:
	.ascii	"../Core/Src/tee_client_api.c\000"
.LASF60:
	.ascii	"TEEC_ReleaseSharedMemory\000"
.LASF13:
	.ascii	"size_t\000"
.LASF21:
	.ascii	"timeMid\000"
.LASF56:
	.ascii	"ret_val\000"
.LASF10:
	.ascii	"long long int\000"
.LASF8:
	.ascii	"__uint32_t\000"
.LASF44:
	.ascii	"TEEC_Session\000"
.LASF51:
	.ascii	"TEEC_InvokeCommand\000"
.LASF4:
	.ascii	"__uint16_t\000"
.LASF2:
	.ascii	"short int\000"
.LASF68:
	.ascii	"temp_val\000"
.LASF41:
	.ascii	"value\000"
.LASF37:
	.ascii	"TEEC_RegisteredMemoryReference\000"
.LASF80:
	.ascii	"__builtin_memset\000"
.LASF16:
	.ascii	"uint8_t\000"
.LASF22:
	.ascii	"timeHiAndVersion\000"
.LASF69:
	.ascii	"TEEC_FinalizeContext\000"
.LASF50:
	.ascii	"TEEC_AllocateSharedMemory\000"
.LASF67:
	.ascii	"operation\000"
.LASF77:
	.ascii	"free\000"
.LASF70:
	.ascii	"TEEC_InitializeContext\000"
.LASF78:
	.ascii	"temp_val_r5\000"
.LASF14:
	.ascii	"long double\000"
.LASF34:
	.ascii	"TEEC_TempMemoryReference\000"
.LASF23:
	.ascii	"clockSeqAndNode\000"
.LASF29:
	.ascii	"TEEC_Result\000"
.LASF7:
	.ascii	"long int\000"
.LASF35:
	.ascii	"parent\000"
.LASF48:
	.ascii	"printf\000"
.LASF27:
	.ascii	"uuid\000"
.LASF3:
	.ascii	"__uint8_t\000"
.LASF40:
	.ascii	"memref\000"
.LASF25:
	.ascii	"params\000"
.LASF39:
	.ascii	"tmpref\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF57:
	.ascii	"__func__\000"
.LASF79:
	.ascii	"check_context\000"
.LASF58:
	.ascii	"temp_val_r4\000"
.LASF0:
	.ascii	"signed char\000"
.LASF32:
	.ascii	"flags\000"
.LASF11:
	.ascii	"long long unsigned int\000"
.LASF19:
	.ascii	"uint32_t\000"
.LASF12:
	.ascii	"unsigned int\000"
.LASF17:
	.ascii	"uint16_t\000"
.LASF20:
	.ascii	"timeLow\000"
.LASF62:
	.ascii	"param\000"
.LASF45:
	.ascii	"started\000"
.LASF33:
	.ascii	"TEEC_SharedMemory\000"
.LASF5:
	.ascii	"short unsigned int\000"
.LASF36:
	.ascii	"offset\000"
.LASF42:
	.ascii	"TEEC_Parameter\000"
.LASF72:
	.ascii	"get_internalOperation\000"
.LASF15:
	.ascii	"char\000"
.LASF18:
	.ascii	"int32_t\000"
.LASF6:
	.ascii	"__int32_t\000"
.LASF49:
	.ascii	"calloc\000"
.LASF65:
	.ascii	"connectionMethod\000"
.LASF54:
	.ascii	"returnOrigin\000"
.LASF30:
	.ascii	"buffer\000"
.LASF76:
	.ascii	"used_shm_size\000"
.LASF55:
	.ascii	"internal_op\000"
.LASF9:
	.ascii	"long unsigned int\000"
.LASF64:
	.ascii	"destination\000"
.LASF52:
	.ascii	"session\000"
.LASF24:
	.ascii	"TEE_UUID\000"
.LASF59:
	.ascii	"param_addr\000"
.LASF31:
	.ascii	"size\000"
.LASF38:
	.ascii	"TEEC_Value\000"
.LASF43:
	.ascii	"TEEC_Context\000"
.LASF73:
	.ascii	"GNU C17 12.3.1 20230626 -mcpu=cortex-m3 -mthumb -mf"
	.ascii	"loat-abi=soft -march=armv7-m -g -gdwarf-2 -Og -fdat"
	.ascii	"a-sections -ffunction-sections\000"
.LASF53:
	.ascii	"command_id\000"
.LASF47:
	.ascii	"memset\000"
.LASF71:
	.ascii	"name\000"
.LASF61:
	.ascii	"TEEC_CloseSession\000"
.LASF66:
	.ascii	"connectionData\000"
.LASF75:
	.ascii	"/home/emanuele/Desktop/Code/MCU-fortifier/apps/doub"
	.ascii	"le_trusted_application/Debug\000"
	.ident	"GCC: (GNU Tools for STM32 12.3.rel1.20240612-1315) 12.3.1 20230626"
