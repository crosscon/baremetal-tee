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
	.file	"stm32l4xx_hal_pcd_ex.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 1 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pcd_ex.c"
	.section	.text.HAL_PCDEx_SetTxFiFo,"ax",%progbits
	.align	1
	.global	HAL_PCDEx_SetTxFiFo
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PCDEx_SetTxFiFo, %function
HAL_PCDEx_SetTxFiFo:
.LVL0:
.LFB74:
	.loc 1 71 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 71 1 is_stmt 0 view .LVU1
	push	{r4}
.LCFI0:
	.cfi_def_cfa_offset 4
	.cfi_offset 4, -4
	.loc 1 72 3 is_stmt 1 view .LVU2
	.loc 1 73 3 view .LVU3
	.loc 1 85 3 view .LVU4
	.loc 1 85 19 is_stmt 0 view .LVU5
	ldr	r4, [r0]
	.loc 1 85 13 view .LVU6
	ldr	r0, [r4, #36]
.LVL1:
	.loc 1 87 3 is_stmt 1 view .LVU7
	.loc 1 87 6 is_stmt 0 view .LVU8
	cbnz	r1, .L2
	.loc 1 89 5 is_stmt 1 view .LVU9
	.loc 1 89 65 is_stmt 0 view .LVU10
	orr	r0, r0, r2, lsl #16
.LVL2:
	.loc 1 89 40 view .LVU11
	str	r0, [r4, #40]
.LVL3:
.L3:
	.loc 1 103 3 is_stmt 1 view .LVU12
	.loc 1 104 1 is_stmt 0 view .LVU13
	movs	r0, #0
	pop	{r4}
.LCFI1:
	.cfi_remember_state
	.cfi_restore 4
	.cfi_def_cfa_offset 0
	bx	lr
.LVL4:
.L2:
.LCFI2:
	.cfi_restore_state
	.loc 1 104 1 view .LVU14
	mov	ip, r1
	.loc 1 93 5 is_stmt 1 view .LVU15
	.loc 1 93 33 is_stmt 0 view .LVU16
	ldr	r3, [r4, #40]
	.loc 1 93 15 view .LVU17
	add	r0, r0, r3, lsr #16
.LVL5:
	.loc 1 94 5 is_stmt 1 view .LVU18
	.loc 1 94 12 is_stmt 0 view .LVU19
	movs	r3, #0
	.loc 1 94 5 view .LVU20
	b	.L4
.LVL6:
.L5:
	.loc 1 96 7 is_stmt 1 discriminator 3 view .LVU21
	.loc 1 96 44 is_stmt 0 discriminator 3 view .LVU22
	add	r1, r3, #64
	add	r1, r4, r1, lsl #2
	ldr	r1, [r1, #4]
	.loc 1 96 17 discriminator 3 view .LVU23
	add	r0, r0, r1, lsr #16
.LVL7:
	.loc 1 94 36 is_stmt 1 discriminator 3 view .LVU24
	adds	r3, r3, #1
.LVL8:
	.loc 1 94 36 is_stmt 0 discriminator 3 view .LVU25
	uxtb	r3, r3
.LVL9:
.L4:
	.loc 1 94 20 is_stmt 1 discriminator 1 view .LVU26
	.loc 1 94 28 is_stmt 0 discriminator 1 view .LVU27
	add	r1, ip, #-1
	.loc 1 94 20 discriminator 1 view .LVU28
	cmp	r3, r1
	bcc	.L5
	.loc 1 100 5 is_stmt 1 view .LVU29
	.loc 1 100 65 is_stmt 0 view .LVU30
	orr	r0, r0, r2, lsl #16
.LVL10:
	.loc 1 100 40 view .LVU31
	add	r1, ip, #63
	add	r4, r4, r1, lsl #2
	str	r0, [r4, #4]
	b	.L3
	.cfi_endproc
.LFE74:
	.size	HAL_PCDEx_SetTxFiFo, .-HAL_PCDEx_SetTxFiFo
	.section	.text.HAL_PCDEx_SetRxFiFo,"ax",%progbits
	.align	1
	.global	HAL_PCDEx_SetRxFiFo
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PCDEx_SetRxFiFo, %function
HAL_PCDEx_SetRxFiFo:
.LVL11:
.LFB75:
	.loc 1 113 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 114 3 view .LVU33
	.loc 1 114 7 is_stmt 0 view .LVU34
	ldr	r3, [r0]
	.loc 1 114 27 view .LVU35
	str	r1, [r3, #36]
	.loc 1 116 3 is_stmt 1 view .LVU36
	.loc 1 117 1 is_stmt 0 view .LVU37
	movs	r0, #0
.LVL12:
	.loc 1 117 1 view .LVU38
	bx	lr
	.cfi_endproc
.LFE75:
	.size	HAL_PCDEx_SetRxFiFo, .-HAL_PCDEx_SetRxFiFo
	.section	.text.HAL_PCDEx_ActivateLPM,"ax",%progbits
	.align	1
	.global	HAL_PCDEx_ActivateLPM
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PCDEx_ActivateLPM, %function
HAL_PCDEx_ActivateLPM:
.LVL13:
.LFB76:
	.loc 1 125 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 125 1 is_stmt 0 view .LVU40
	mov	r3, r0
	.loc 1 126 3 is_stmt 1 view .LVU41
	.loc 1 126 26 is_stmt 0 view .LVU42
	ldr	r2, [r0]
.LVL14:
	.loc 1 128 3 is_stmt 1 view .LVU43
	.loc 1 128 20 is_stmt 0 view .LVU44
	movs	r1, #1
	str	r1, [r0, #1240]
	.loc 1 129 3 is_stmt 1 view .LVU45
	.loc 1 129 19 is_stmt 0 view .LVU46
	movs	r0, #0
.LVL15:
	.loc 1 129 19 view .LVU47
	strb	r0, [r3, #1228]
	.loc 1 130 3 is_stmt 1 view .LVU48
	.loc 1 130 7 is_stmt 0 view .LVU49
	ldr	r3, [r2, #24]
.LVL16:
	.loc 1 130 17 view .LVU50
	orr	r3, r3, #134217728
	str	r3, [r2, #24]
	.loc 1 131 3 is_stmt 1 view .LVU51
	.loc 1 131 7 is_stmt 0 view .LVU52
	ldr	r3, [r2, #84]
	.loc 1 131 17 view .LVU53
	orr	r3, r3, #268435456
	orr	r3, r3, #3
	str	r3, [r2, #84]
	.loc 1 133 3 is_stmt 1 view .LVU54
	.loc 1 134 1 is_stmt 0 view .LVU55
	bx	lr
	.cfi_endproc
.LFE76:
	.size	HAL_PCDEx_ActivateLPM, .-HAL_PCDEx_ActivateLPM
	.section	.text.HAL_PCDEx_DeActivateLPM,"ax",%progbits
	.align	1
	.global	HAL_PCDEx_DeActivateLPM
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PCDEx_DeActivateLPM, %function
HAL_PCDEx_DeActivateLPM:
.LVL17:
.LFB77:
	.loc 1 142 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 142 1 is_stmt 0 view .LVU57
	mov	r3, r0
	.loc 1 143 3 is_stmt 1 view .LVU58
	.loc 1 143 26 is_stmt 0 view .LVU59
	ldr	r2, [r0]
.LVL18:
	.loc 1 145 3 is_stmt 1 view .LVU60
	.loc 1 145 20 is_stmt 0 view .LVU61
	movs	r0, #0
.LVL19:
	.loc 1 145 20 view .LVU62
	str	r0, [r3, #1240]
	.loc 1 146 3 is_stmt 1 view .LVU63
	.loc 1 146 7 is_stmt 0 view .LVU64
	ldr	r3, [r2, #24]
.LVL20:
	.loc 1 146 17 view .LVU65
	bic	r3, r3, #134217728
	str	r3, [r2, #24]
	.loc 1 147 3 is_stmt 1 view .LVU66
	.loc 1 147 7 is_stmt 0 view .LVU67
	ldr	r3, [r2, #84]
	.loc 1 147 17 view .LVU68
	bic	r3, r3, #268435456
	bic	r3, r3, #3
	str	r3, [r2, #84]
	.loc 1 149 3 is_stmt 1 view .LVU69
	.loc 1 150 1 is_stmt 0 view .LVU70
	bx	lr
	.cfi_endproc
.LFE77:
	.size	HAL_PCDEx_DeActivateLPM, .-HAL_PCDEx_DeActivateLPM
	.section	.text.HAL_PCDEx_ActivateBCD,"ax",%progbits
	.align	1
	.global	HAL_PCDEx_ActivateBCD
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PCDEx_ActivateBCD, %function
HAL_PCDEx_ActivateBCD:
.LVL21:
.LFB79:
	.loc 1 252 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 253 3 view .LVU72
	.loc 1 253 26 is_stmt 0 view .LVU73
	ldr	r3, [r0]
.LVL22:
	.loc 1 255 3 is_stmt 1 view .LVU74
	.loc 1 255 7 is_stmt 0 view .LVU75
	ldr	r2, [r3, #56]
	.loc 1 255 15 view .LVU76
	bic	r2, r2, #524288
	str	r2, [r3, #56]
	.loc 1 256 3 is_stmt 1 view .LVU77
	.loc 1 256 7 is_stmt 0 view .LVU78
	ldr	r2, [r3, #56]
	.loc 1 256 15 view .LVU79
	bic	r2, r2, #1048576
	str	r2, [r3, #56]
	.loc 1 259 3 is_stmt 1 view .LVU80
	.loc 1 259 7 is_stmt 0 view .LVU81
	ldr	r2, [r3, #56]
	.loc 1 259 15 view .LVU82
	bic	r2, r2, #65536
	str	r2, [r3, #56]
	.loc 1 262 3 is_stmt 1 view .LVU83
	.loc 1 262 7 is_stmt 0 view .LVU84
	ldr	r2, [r3, #56]
	.loc 1 262 15 view .LVU85
	orr	r2, r2, #131072
	str	r2, [r3, #56]
	.loc 1 264 3 is_stmt 1 view .LVU86
	.loc 1 264 33 is_stmt 0 view .LVU87
	movs	r3, #1
.LVL23:
	.loc 1 264 33 view .LVU88
	str	r3, [r0, #1244]
	.loc 1 266 3 is_stmt 1 view .LVU89
	.loc 1 267 1 is_stmt 0 view .LVU90
	movs	r0, #0
.LVL24:
	.loc 1 267 1 view .LVU91
	bx	lr
	.cfi_endproc
.LFE79:
	.size	HAL_PCDEx_ActivateBCD, .-HAL_PCDEx_ActivateBCD
	.section	.text.HAL_PCDEx_DeActivateBCD,"ax",%progbits
	.align	1
	.global	HAL_PCDEx_DeActivateBCD
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PCDEx_DeActivateBCD, %function
HAL_PCDEx_DeActivateBCD:
.LVL25:
.LFB80:
	.loc 1 275 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 275 1 is_stmt 0 view .LVU93
	mov	r2, r0
	.loc 1 276 3 is_stmt 1 view .LVU94
	.loc 1 276 26 is_stmt 0 view .LVU95
	ldr	r3, [r0]
.LVL26:
	.loc 1 278 3 is_stmt 1 view .LVU96
	.loc 1 278 7 is_stmt 0 view .LVU97
	ldr	r1, [r3, #56]
	.loc 1 278 15 view .LVU98
	bic	r1, r1, #1048576
	str	r1, [r3, #56]
	.loc 1 279 3 is_stmt 1 view .LVU99
	.loc 1 279 7 is_stmt 0 view .LVU100
	ldr	r1, [r3, #56]
	.loc 1 279 15 view .LVU101
	bic	r1, r1, #524288
	str	r1, [r3, #56]
	.loc 1 282 3 is_stmt 1 view .LVU102
	.loc 1 282 7 is_stmt 0 view .LVU103
	ldr	r1, [r3, #56]
	.loc 1 282 15 view .LVU104
	bic	r1, r1, #131072
	str	r1, [r3, #56]
	.loc 1 284 3 is_stmt 1 view .LVU105
	.loc 1 284 33 is_stmt 0 view .LVU106
	movs	r0, #0
.LVL27:
	.loc 1 284 33 view .LVU107
	str	r0, [r2, #1244]
	.loc 1 286 3 is_stmt 1 view .LVU108
	.loc 1 287 1 is_stmt 0 view .LVU109
	bx	lr
	.cfi_endproc
.LFE80:
	.size	HAL_PCDEx_DeActivateBCD, .-HAL_PCDEx_DeActivateBCD
	.section	.text.HAL_PCDEx_LPM_Callback,"ax",%progbits
	.align	1
	.weak	HAL_PCDEx_LPM_Callback
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PCDEx_LPM_Callback, %function
HAL_PCDEx_LPM_Callback:
.LVL28:
.LFB81:
	.loc 1 516 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 518 3 view .LVU111
	.loc 1 519 3 view .LVU112
	.loc 1 524 1 is_stmt 0 view .LVU113
	bx	lr
	.cfi_endproc
.LFE81:
	.size	HAL_PCDEx_LPM_Callback, .-HAL_PCDEx_LPM_Callback
	.section	.text.HAL_PCDEx_BCD_Callback,"ax",%progbits
	.align	1
	.weak	HAL_PCDEx_BCD_Callback
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PCDEx_BCD_Callback, %function
HAL_PCDEx_BCD_Callback:
.LVL29:
.LFB82:
	.loc 1 533 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 535 3 view .LVU115
	.loc 1 536 3 view .LVU116
	.loc 1 541 1 is_stmt 0 view .LVU117
	bx	lr
	.cfi_endproc
.LFE82:
	.size	HAL_PCDEx_BCD_Callback, .-HAL_PCDEx_BCD_Callback
	.section	.text.HAL_PCDEx_BCD_VBUSDetect,"ax",%progbits
	.align	1
	.global	HAL_PCDEx_BCD_VBUSDetect
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PCDEx_BCD_VBUSDetect, %function
HAL_PCDEx_BCD_VBUSDetect:
.LVL30:
.LFB78:
	.loc 1 159 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 159 1 is_stmt 0 view .LVU119
	push	{r4, r5, r6, lr}
.LCFI3:
	.cfi_def_cfa_offset 16
	.cfi_offset 4, -16
	.cfi_offset 5, -12
	.cfi_offset 6, -8
	.cfi_offset 14, -4
	mov	r5, r0
	.loc 1 160 3 is_stmt 1 view .LVU120
	.loc 1 160 26 is_stmt 0 view .LVU121
	ldr	r4, [r0]
.LVL31:
	.loc 1 161 3 is_stmt 1 view .LVU122
	.loc 1 161 24 is_stmt 0 view .LVU123
	bl	HAL_GetTick
.LVL32:
	.loc 1 161 24 view .LVU124
	mov	r6, r0
.LVL33:
	.loc 1 164 3 is_stmt 1 view .LVU125
	.loc 1 164 7 is_stmt 0 view .LVU126
	ldr	r3, [r4, #56]
	.loc 1 164 15 view .LVU127
	orr	r3, r3, #262144
	str	r3, [r4, #56]
	.loc 1 167 3 is_stmt 1 view .LVU128
	mov	r0, #300
.LVL34:
	.loc 1 167 3 is_stmt 0 view .LVU129
	bl	HAL_Delay
.LVL35:
	.loc 1 170 3 is_stmt 1 view .LVU130
	.loc 1 170 12 is_stmt 0 view .LVU131
	ldr	r3, [r4, #56]
	.loc 1 170 6 view .LVU132
	tst	r3, #1
	bne	.L22
.L15:
	.loc 1 181 3 is_stmt 1 view .LVU133
	.loc 1 181 7 is_stmt 0 view .LVU134
	ldr	r3, [r4, #56]
	.loc 1 181 15 view .LVU135
	bic	r3, r3, #262144
	str	r3, [r4, #56]
	.loc 1 182 3 is_stmt 1 view .LVU136
	movs	r0, #50
	bl	HAL_Delay
.LVL36:
	.loc 1 183 3 view .LVU137
	.loc 1 183 7 is_stmt 0 view .LVU138
	ldr	r3, [r4, #56]
	.loc 1 183 15 view .LVU139
	orr	r3, r3, #524288
	str	r3, [r4, #56]
	.loc 1 184 3 is_stmt 1 view .LVU140
	movs	r0, #50
	bl	HAL_Delay
.LVL37:
	.loc 1 186 3 view .LVU141
	.loc 1 186 12 is_stmt 0 view .LVU142
	ldr	r3, [r4, #56]
	.loc 1 186 6 view .LVU143
	tst	r3, #2
	bne	.L16
	.loc 1 192 5 is_stmt 1 view .LVU144
	movs	r1, #253
	mov	r0, r5
	bl	HAL_PCDEx_BCD_Callback
.LVL38:
.L17:
	.loc 1 225 3 view .LVU145
	.loc 1 225 9 is_stmt 0 view .LVU146
	mov	r0, r5
	bl	HAL_PCDEx_DeActivateBCD
.LVL39:
	.loc 1 228 3 is_stmt 1 view .LVU147
	.loc 1 228 8 is_stmt 0 view .LVU148
	bl	HAL_GetTick
.LVL40:
	.loc 1 228 22 view .LVU149
	subs	r0, r0, r6
	.loc 1 228 6 view .LVU150
	cmp	r0, #1000
	bls	.L19
	.loc 1 233 5 is_stmt 1 view .LVU151
	movs	r1, #255
	mov	r0, r5
	bl	HAL_PCDEx_BCD_Callback
.LVL41:
.L14:
	.loc 1 244 1 is_stmt 0 view .LVU152
	pop	{r4, r5, r6, pc}
.LVL42:
.L22:
	.loc 1 175 5 is_stmt 1 view .LVU153
	movs	r1, #254
	mov	r0, r5
	bl	HAL_PCDEx_BCD_Callback
.LVL43:
	b	.L15
.L16:
	.loc 1 199 5 view .LVU154
	.loc 1 199 9 is_stmt 0 view .LVU155
	ldr	r3, [r4, #56]
	.loc 1 199 17 view .LVU156
	bic	r3, r3, #524288
	str	r3, [r4, #56]
	.loc 1 200 5 is_stmt 1 view .LVU157
	movs	r0, #50
	bl	HAL_Delay
.LVL44:
	.loc 1 201 5 view .LVU158
	.loc 1 201 9 is_stmt 0 view .LVU159
	ldr	r3, [r4, #56]
	.loc 1 201 17 view .LVU160
	orr	r3, r3, #1048576
	str	r3, [r4, #56]
	.loc 1 202 5 is_stmt 1 view .LVU161
	movs	r0, #50
	bl	HAL_Delay
.LVL45:
	.loc 1 204 5 view .LVU162
	.loc 1 204 14 is_stmt 0 view .LVU163
	ldr	r3, [r4, #56]
	.loc 1 204 8 view .LVU164
	tst	r3, #4
	beq	.L18
	.loc 1 210 7 is_stmt 1 view .LVU165
	movs	r1, #251
	mov	r0, r5
	bl	HAL_PCDEx_BCD_Callback
.LVL46:
	b	.L17
.L18:
	.loc 1 219 7 view .LVU166
	movs	r1, #252
	mov	r0, r5
	bl	HAL_PCDEx_BCD_Callback
.LVL47:
	b	.L17
.L19:
	.loc 1 241 5 view .LVU167
	movs	r1, #0
	mov	r0, r5
	bl	HAL_PCDEx_BCD_Callback
.LVL48:
	.loc 1 244 1 is_stmt 0 view .LVU168
	b	.L14
	.cfi_endproc
.LFE78:
	.size	HAL_PCDEx_BCD_VBUSDetect, .-HAL_PCDEx_BCD_VBUSDetect
	.text
.Letext0:
	.file 2 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/arm-none-eabi/include/machine/_default_types.h"
	.file 3 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/arm-none-eabi/include/sys/_stdint.h"
	.file 4 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
	.file 5 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_def.h"
	.file 6 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_ll_usb.h"
	.file 7 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pcd.h"
	.file 8 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0xb1e
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF136
	.byte	0xc
	.4byte	.LASF137
	.4byte	.LASF138
	.4byte	.Ldebug_ranges0+0
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
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x3
	.4byte	.LASF7
	.byte	0x2
	.byte	0x4f
	.byte	0x19
	.4byte	0x70
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF9
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0x3
	.4byte	.LASF12
	.byte	0x3
	.byte	0x18
	.byte	0x13
	.4byte	0x30
	.uleb128 0x5
	.4byte	0x93
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x3
	.byte	0x24
	.byte	0x14
	.4byte	0x4a
	.uleb128 0x3
	.4byte	.LASF14
	.byte	0x3
	.byte	0x30
	.byte	0x14
	.4byte	0x64
	.uleb128 0x5
	.4byte	0xb0
	.uleb128 0x6
	.4byte	0xb0
	.4byte	0xd1
	.uleb128 0x7
	.4byte	0x8c
	.byte	0x1
	.byte	0
	.uleb128 0x6
	.4byte	0xb0
	.4byte	0xe1
	.uleb128 0x7
	.4byte	0x8c
	.byte	0x26
	.byte	0
	.uleb128 0x6
	.4byte	0xb0
	.4byte	0xf1
	.uleb128 0x7
	.4byte	0x8c
	.byte	0xb
	.byte	0
	.uleb128 0x8
	.2byte	0x140
	.byte	0x4
	.2byte	0x3dd
	.byte	0x9
	.4byte	0x2af
	.uleb128 0x9
	.4byte	.LASF15
	.byte	0x4
	.2byte	0x3df
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x9
	.4byte	.LASF16
	.byte	0x4
	.2byte	0x3e0
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x9
	.4byte	.LASF17
	.byte	0x4
	.2byte	0x3e1
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x9
	.4byte	.LASF18
	.byte	0x4
	.2byte	0x3e2
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x9
	.4byte	.LASF19
	.byte	0x4
	.2byte	0x3e3
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x9
	.4byte	.LASF20
	.byte	0x4
	.2byte	0x3e4
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x9
	.4byte	.LASF21
	.byte	0x4
	.2byte	0x3e5
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x9
	.4byte	.LASF22
	.byte	0x4
	.2byte	0x3e6
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0x9
	.4byte	.LASF23
	.byte	0x4
	.2byte	0x3e7
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0x9
	.4byte	.LASF24
	.byte	0x4
	.2byte	0x3e8
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0x9
	.4byte	.LASF25
	.byte	0x4
	.2byte	0x3e9
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0x9
	.4byte	.LASF26
	.byte	0x4
	.2byte	0x3ea
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0x9
	.4byte	.LASF27
	.byte	0x4
	.2byte	0x3eb
	.byte	0xc
	.4byte	0xc1
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0x9
	.4byte	.LASF28
	.byte	0x4
	.2byte	0x3ec
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0xa
	.ascii	"CID\000"
	.byte	0x4
	.2byte	0x3ed
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x3c
	.uleb128 0x9
	.4byte	.LASF29
	.byte	0x4
	.2byte	0x3ee
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0x9
	.4byte	.LASF30
	.byte	0x4
	.2byte	0x3ef
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x44
	.uleb128 0x9
	.4byte	.LASF31
	.byte	0x4
	.2byte	0x3f0
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0x9
	.4byte	.LASF32
	.byte	0x4
	.2byte	0x3f1
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x4c
	.uleb128 0x9
	.4byte	.LASF33
	.byte	0x4
	.2byte	0x3f2
	.byte	0xd
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0x9
	.4byte	.LASF34
	.byte	0x4
	.2byte	0x3f3
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x54
	.uleb128 0x9
	.4byte	.LASF35
	.byte	0x4
	.2byte	0x3f4
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0x9
	.4byte	.LASF36
	.byte	0x4
	.2byte	0x3f5
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x5c
	.uleb128 0x9
	.4byte	.LASF37
	.byte	0x4
	.2byte	0x3f6
	.byte	0x12
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x60
	.uleb128 0x9
	.4byte	.LASF38
	.byte	0x4
	.2byte	0x3f7
	.byte	0xf
	.4byte	0xd1
	.byte	0x2
	.byte	0x23
	.uleb128 0x64
	.uleb128 0x9
	.4byte	.LASF39
	.byte	0x4
	.2byte	0x3f8
	.byte	0x11
	.4byte	0xbc
	.byte	0x3
	.byte	0x23
	.uleb128 0x100
	.uleb128 0x9
	.4byte	.LASF40
	.byte	0x4
	.2byte	0x3f9
	.byte	0x11
	.4byte	0x2bf
	.byte	0x3
	.byte	0x23
	.uleb128 0x104
	.byte	0
	.uleb128 0x6
	.4byte	0xbc
	.4byte	0x2bf
	.uleb128 0x7
	.4byte	0x8c
	.byte	0xe
	.byte	0
	.uleb128 0x5
	.4byte	0x2af
	.uleb128 0xb
	.4byte	.LASF41
	.byte	0x4
	.2byte	0x3fa
	.byte	0x3
	.4byte	0xf1
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF42
	.uleb128 0xc
	.byte	0x7
	.byte	0x1
	.4byte	0x3c
	.byte	0x5
	.byte	0x27
	.byte	0x1
	.4byte	0x2ff
	.uleb128 0xd
	.4byte	.LASF43
	.byte	0
	.uleb128 0xd
	.4byte	.LASF44
	.byte	0x1
	.uleb128 0xd
	.4byte	.LASF45
	.byte	0x2
	.uleb128 0xd
	.4byte	.LASF46
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF47
	.byte	0x5
	.byte	0x2c
	.byte	0x3
	.4byte	0x2d8
	.uleb128 0xc
	.byte	0x7
	.byte	0x1
	.4byte	0x3c
	.byte	0x5
	.byte	0x32
	.byte	0x1
	.4byte	0x326
	.uleb128 0xd
	.4byte	.LASF48
	.byte	0
	.uleb128 0xd
	.4byte	.LASF49
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF50
	.byte	0x5
	.byte	0x35
	.byte	0x3
	.4byte	0x30b
	.uleb128 0xe
	.byte	0x4
	.uleb128 0xf
	.byte	0x4
	.4byte	0x93
	.uleb128 0x10
	.byte	0xd
	.byte	0x6
	.byte	0x5d
	.byte	0x9
	.4byte	0x407
	.uleb128 0x11
	.4byte	.LASF51
	.byte	0x6
	.byte	0x5f
	.byte	0xb
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x11
	.4byte	.LASF52
	.byte	0x6
	.byte	0x64
	.byte	0xb
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x11
	.4byte	.LASF53
	.byte	0x6
	.byte	0x69
	.byte	0xb
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0x11
	.4byte	.LASF54
	.byte	0x6
	.byte	0x6c
	.byte	0xb
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0x3
	.uleb128 0x11
	.4byte	.LASF55
	.byte	0x6
	.byte	0x70
	.byte	0xb
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x11
	.4byte	.LASF56
	.byte	0x6
	.byte	0x72
	.byte	0xb
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0x5
	.uleb128 0x11
	.4byte	.LASF57
	.byte	0x6
	.byte	0x75
	.byte	0xb
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0x6
	.uleb128 0x11
	.4byte	.LASF58
	.byte	0x6
	.byte	0x77
	.byte	0xb
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0x7
	.uleb128 0x11
	.4byte	.LASF59
	.byte	0x6
	.byte	0x79
	.byte	0xb
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x11
	.4byte	.LASF60
	.byte	0x6
	.byte	0x7b
	.byte	0xb
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0x9
	.uleb128 0x11
	.4byte	.LASF61
	.byte	0x6
	.byte	0x7e
	.byte	0xb
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0xa
	.uleb128 0x11
	.4byte	.LASF62
	.byte	0x6
	.byte	0x80
	.byte	0xb
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0xb
	.uleb128 0x11
	.4byte	.LASF63
	.byte	0x6
	.byte	0x82
	.byte	0xb
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.byte	0
	.uleb128 0x3
	.4byte	.LASF64
	.byte	0x6
	.byte	0x84
	.byte	0x3
	.4byte	0x33a
	.uleb128 0x10
	.byte	0x24
	.byte	0x6
	.byte	0x86
	.byte	0x9
	.4byte	0x4ef
	.uleb128 0x12
	.ascii	"num\000"
	.byte	0x6
	.byte	0x88
	.byte	0xd
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x11
	.4byte	.LASF65
	.byte	0x6
	.byte	0x8b
	.byte	0xd
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0x1
	.uleb128 0x11
	.4byte	.LASF66
	.byte	0x6
	.byte	0x8e
	.byte	0xd
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0x2
	.uleb128 0x11
	.4byte	.LASF67
	.byte	0x6
	.byte	0x92
	.byte	0xd
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0x3
	.uleb128 0x11
	.4byte	.LASF68
	.byte	0x6
	.byte	0x96
	.byte	0xd
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x11
	.4byte	.LASF69
	.byte	0x6
	.byte	0x99
	.byte	0xd
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0x5
	.uleb128 0x11
	.4byte	.LASF70
	.byte	0x6
	.byte	0xaa
	.byte	0xd
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x11
	.4byte	.LASF71
	.byte	0x6
	.byte	0xad
	.byte	0xe
	.4byte	0x334
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x11
	.4byte	.LASF72
	.byte	0x6
	.byte	0xaf
	.byte	0xd
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x11
	.4byte	.LASF73
	.byte	0x6
	.byte	0xb1
	.byte	0xd
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x11
	.4byte	.LASF74
	.byte	0x6
	.byte	0xb4
	.byte	0xd
	.4byte	0x93
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x11
	.4byte	.LASF75
	.byte	0x6
	.byte	0xb7
	.byte	0xd
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x1a
	.uleb128 0x11
	.4byte	.LASF76
	.byte	0x6
	.byte	0xba
	.byte	0xd
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0x11
	.4byte	.LASF77
	.byte	0x6
	.byte	0xbc
	.byte	0xd
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.byte	0
	.uleb128 0x3
	.4byte	.LASF78
	.byte	0x6
	.byte	0xc4
	.byte	0x3
	.4byte	0x413
	.uleb128 0xb
	.4byte	.LASF79
	.byte	0x6
	.2byte	0x101
	.byte	0x1d
	.4byte	0x407
	.uleb128 0xb
	.4byte	.LASF80
	.byte	0x6
	.2byte	0x102
	.byte	0x1d
	.4byte	0x4ef
	.uleb128 0xc
	.byte	0x7
	.byte	0x1
	.4byte	0x3c
	.byte	0x7
	.byte	0x31
	.byte	0x1
	.4byte	0x542
	.uleb128 0xd
	.4byte	.LASF81
	.byte	0
	.uleb128 0xd
	.4byte	.LASF82
	.byte	0x1
	.uleb128 0xd
	.4byte	.LASF83
	.byte	0x2
	.uleb128 0xd
	.4byte	.LASF84
	.byte	0x3
	.uleb128 0xd
	.4byte	.LASF85
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF86
	.byte	0x7
	.byte	0x37
	.byte	0x3
	.4byte	0x515
	.uleb128 0x5
	.4byte	0x542
	.uleb128 0xc
	.byte	0x7
	.byte	0x1
	.4byte	0x3c
	.byte	0x7
	.byte	0x3b
	.byte	0x1
	.4byte	0x57a
	.uleb128 0xd
	.4byte	.LASF87
	.byte	0
	.uleb128 0xd
	.4byte	.LASF88
	.byte	0x1
	.uleb128 0xd
	.4byte	.LASF89
	.byte	0x2
	.uleb128 0xd
	.4byte	.LASF90
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF91
	.byte	0x7
	.byte	0x40
	.byte	0x3
	.4byte	0x553
	.uleb128 0xc
	.byte	0x7
	.byte	0x1
	.4byte	0x3c
	.byte	0x7
	.byte	0x43
	.byte	0x1
	.4byte	0x5a1
	.uleb128 0xd
	.4byte	.LASF92
	.byte	0
	.uleb128 0xd
	.4byte	.LASF93
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF94
	.byte	0x7
	.byte	0x46
	.byte	0x3
	.4byte	0x586
	.uleb128 0xc
	.byte	0x7
	.byte	0x1
	.4byte	0x3c
	.byte	0x7
	.byte	0x49
	.byte	0x1
	.4byte	0x5e0
	.uleb128 0xd
	.4byte	.LASF95
	.byte	0xff
	.uleb128 0xd
	.4byte	.LASF96
	.byte	0xfe
	.uleb128 0xd
	.4byte	.LASF97
	.byte	0xfd
	.uleb128 0xd
	.4byte	.LASF98
	.byte	0xfc
	.uleb128 0xd
	.4byte	.LASF99
	.byte	0xfb
	.uleb128 0xd
	.4byte	.LASF100
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	.LASF101
	.byte	0x7
	.byte	0x51
	.byte	0x3
	.4byte	0x5ad
	.uleb128 0x3
	.4byte	.LASF102
	.byte	0x7
	.byte	0x57
	.byte	0x20
	.4byte	0x2c4
	.uleb128 0x3
	.4byte	.LASF103
	.byte	0x7
	.byte	0x58
	.byte	0x20
	.4byte	0x4fb
	.uleb128 0x3
	.4byte	.LASF104
	.byte	0x7
	.byte	0x59
	.byte	0x20
	.4byte	0x508
	.uleb128 0x13
	.2byte	0x4e4
	.byte	0x7
	.byte	0x67
	.byte	0x9
	.4byte	0x707
	.uleb128 0x11
	.4byte	.LASF105
	.byte	0x7
	.byte	0x6a
	.byte	0x1c
	.4byte	0x707
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x11
	.4byte	.LASF106
	.byte	0x7
	.byte	0x6b
	.byte	0x1b
	.4byte	0x5f8
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x11
	.4byte	.LASF107
	.byte	0x7
	.byte	0x6c
	.byte	0x1b
	.4byte	0x9f
	.byte	0x2
	.byte	0x23
	.uleb128 0x11
	.uleb128 0x11
	.4byte	.LASF108
	.byte	0x7
	.byte	0x6e
	.byte	0x1b
	.4byte	0x70d
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x11
	.4byte	.LASF109
	.byte	0x7
	.byte	0x6f
	.byte	0x1b
	.4byte	0x70d
	.byte	0x3
	.byte	0x23
	.uleb128 0x254
	.uleb128 0x11
	.4byte	.LASF110
	.byte	0x7
	.byte	0x75
	.byte	0x1b
	.4byte	0x326
	.byte	0x3
	.byte	0x23
	.uleb128 0x494
	.uleb128 0x11
	.4byte	.LASF111
	.byte	0x7
	.byte	0x76
	.byte	0x1b
	.4byte	0x54e
	.byte	0x3
	.byte	0x23
	.uleb128 0x495
	.uleb128 0x11
	.4byte	.LASF112
	.byte	0x7
	.byte	0x77
	.byte	0x1b
	.4byte	0xbc
	.byte	0x3
	.byte	0x23
	.uleb128 0x498
	.uleb128 0x11
	.4byte	.LASF113
	.byte	0x7
	.byte	0x78
	.byte	0x1b
	.4byte	0xe1
	.byte	0x3
	.byte	0x23
	.uleb128 0x49c
	.uleb128 0x11
	.4byte	.LASF114
	.byte	0x7
	.byte	0x79
	.byte	0x1b
	.4byte	0x57a
	.byte	0x3
	.byte	0x23
	.uleb128 0x4cc
	.uleb128 0x11
	.4byte	.LASF115
	.byte	0x7
	.byte	0x7a
	.byte	0x1b
	.4byte	0xb0
	.byte	0x3
	.byte	0x23
	.uleb128 0x4d0
	.uleb128 0x11
	.4byte	.LASF116
	.byte	0x7
	.byte	0x7b
	.byte	0x1b
	.4byte	0xb0
	.byte	0x3
	.byte	0x23
	.uleb128 0x4d4
	.uleb128 0x11
	.4byte	.LASF117
	.byte	0x7
	.byte	0x7e
	.byte	0xc
	.4byte	0xb0
	.byte	0x3
	.byte	0x23
	.uleb128 0x4d8
	.uleb128 0x11
	.4byte	.LASF118
	.byte	0x7
	.byte	0x81
	.byte	0xc
	.4byte	0xb0
	.byte	0x3
	.byte	0x23
	.uleb128 0x4dc
	.uleb128 0x11
	.4byte	.LASF119
	.byte	0x7
	.byte	0x83
	.byte	0x1c
	.4byte	0x332
	.byte	0x3
	.byte	0x23
	.uleb128 0x4e0
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x5ec
	.uleb128 0x6
	.4byte	0x604
	.4byte	0x71d
	.uleb128 0x7
	.4byte	0x8c
	.byte	0xf
	.byte	0
	.uleb128 0x3
	.4byte	.LASF120
	.byte	0x7
	.byte	0x98
	.byte	0x3
	.4byte	0x610
	.uleb128 0x14
	.byte	0x1
	.4byte	.LASF139
	.byte	0x8
	.2byte	0x28c
	.byte	0x14
	.byte	0x1
	.byte	0x1
	.4byte	0x73f
	.uleb128 0x15
	.4byte	0xb0
	.byte	0
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF140
	.byte	0x8
	.2byte	0x28d
	.byte	0x14
	.byte	0x1
	.4byte	0xb0
	.byte	0x1
	.uleb128 0x17
	.byte	0x1
	.4byte	.LASF122
	.byte	0x1
	.2byte	0x214
	.byte	0xd
	.byte	0x1
	.4byte	.LFB82
	.4byte	.LFE82
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x789
	.uleb128 0x18
	.4byte	.LASF121
	.byte	0x1
	.2byte	0x214
	.byte	0x37
	.4byte	0x789
	.byte	0x1
	.byte	0x50
	.uleb128 0x19
	.ascii	"msg\000"
	.byte	0x1
	.2byte	0x214
	.byte	0x50
	.4byte	0x5e0
	.byte	0x1
	.byte	0x51
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x71d
	.uleb128 0x17
	.byte	0x1
	.4byte	.LASF123
	.byte	0x1
	.2byte	0x203
	.byte	0xd
	.byte	0x1
	.4byte	.LFB81
	.4byte	.LFE81
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x7c9
	.uleb128 0x18
	.4byte	.LASF121
	.byte	0x1
	.2byte	0x203
	.byte	0x37
	.4byte	0x789
	.byte	0x1
	.byte	0x50
	.uleb128 0x19
	.ascii	"msg\000"
	.byte	0x1
	.2byte	0x203
	.byte	0x50
	.4byte	0x5a1
	.byte	0x1
	.byte	0x51
	.byte	0
	.uleb128 0x1a
	.byte	0x1
	.4byte	.LASF124
	.byte	0x1
	.2byte	0x112
	.byte	0x13
	.byte	0x1
	.4byte	0x2ff
	.4byte	.LFB80
	.4byte	.LFE80
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x813
	.uleb128 0x1b
	.4byte	.LASF121
	.byte	0x1
	.2byte	0x112
	.byte	0x3e
	.4byte	0x789
	.4byte	.LLST12
	.4byte	.LVUS12
	.uleb128 0x1c
	.4byte	.LASF126
	.byte	0x1
	.2byte	0x114
	.byte	0x1a
	.4byte	0x813
	.4byte	.LLST13
	.4byte	.LVUS13
	.byte	0
	.uleb128 0xf
	.byte	0x4
	.4byte	0x2c4
	.uleb128 0x1d
	.byte	0x1
	.4byte	.LASF125
	.byte	0x1
	.byte	0xfb
	.byte	0x13
	.byte	0x1
	.4byte	0x2ff
	.4byte	.LFB79
	.4byte	.LFE79
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x860
	.uleb128 0x1e
	.4byte	.LASF121
	.byte	0x1
	.byte	0xfb
	.byte	0x3c
	.4byte	0x789
	.4byte	.LLST10
	.4byte	.LVUS10
	.uleb128 0x1f
	.4byte	.LASF126
	.byte	0x1
	.byte	0xfd
	.byte	0x1a
	.4byte	0x813
	.4byte	.LLST11
	.4byte	.LVUS11
	.byte	0
	.uleb128 0x20
	.byte	0x1
	.4byte	.LASF127
	.byte	0x1
	.byte	0x9e
	.byte	0x6
	.byte	0x1
	.4byte	.LFB78
	.4byte	.LFE78
	.4byte	.LLST14
	.byte	0x1
	.4byte	0x9da
	.uleb128 0x1e
	.4byte	.LASF121
	.byte	0x1
	.byte	0x9e
	.byte	0x32
	.4byte	0x789
	.4byte	.LLST15
	.4byte	.LVUS15
	.uleb128 0x1f
	.4byte	.LASF126
	.byte	0x1
	.byte	0xa0
	.byte	0x1a
	.4byte	0x813
	.4byte	.LLST16
	.4byte	.LVUS16
	.uleb128 0x1f
	.4byte	.LASF128
	.byte	0x1
	.byte	0xa1
	.byte	0xc
	.4byte	0xb0
	.4byte	.LLST17
	.4byte	.LVUS17
	.uleb128 0x21
	.4byte	.LVL32
	.4byte	0x73f
	.uleb128 0x22
	.4byte	.LVL35
	.4byte	0x729
	.4byte	0x8d5
	.uleb128 0x23
	.byte	0x1
	.byte	0x50
	.byte	0x3
	.byte	0xa
	.2byte	0x12c
	.byte	0
	.uleb128 0x22
	.4byte	.LVL36
	.4byte	0x729
	.4byte	0x8e9
	.uleb128 0x23
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x8
	.byte	0x32
	.byte	0
	.uleb128 0x22
	.4byte	.LVL37
	.4byte	0x729
	.4byte	0x8fd
	.uleb128 0x23
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x8
	.byte	0x32
	.byte	0
	.uleb128 0x22
	.4byte	.LVL38
	.4byte	0x74f
	.4byte	0x917
	.uleb128 0x23
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x23
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x9
	.byte	0xfd
	.byte	0
	.uleb128 0x22
	.4byte	.LVL39
	.4byte	0x7c9
	.4byte	0x92b
	.uleb128 0x23
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.byte	0
	.uleb128 0x21
	.4byte	.LVL40
	.4byte	0x73f
	.uleb128 0x22
	.4byte	.LVL41
	.4byte	0x74f
	.4byte	0x94e
	.uleb128 0x23
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x23
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x9
	.byte	0xff
	.byte	0
	.uleb128 0x22
	.4byte	.LVL43
	.4byte	0x74f
	.4byte	0x968
	.uleb128 0x23
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x23
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x9
	.byte	0xfe
	.byte	0
	.uleb128 0x22
	.4byte	.LVL44
	.4byte	0x729
	.4byte	0x97c
	.uleb128 0x23
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x8
	.byte	0x32
	.byte	0
	.uleb128 0x22
	.4byte	.LVL45
	.4byte	0x729
	.4byte	0x990
	.uleb128 0x23
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x8
	.byte	0x32
	.byte	0
	.uleb128 0x22
	.4byte	.LVL46
	.4byte	0x74f
	.4byte	0x9aa
	.uleb128 0x23
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x23
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x9
	.byte	0xfb
	.byte	0
	.uleb128 0x22
	.4byte	.LVL47
	.4byte	0x74f
	.4byte	0x9c4
	.uleb128 0x23
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x23
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x9
	.byte	0xfc
	.byte	0
	.uleb128 0x24
	.4byte	.LVL48
	.4byte	0x74f
	.uleb128 0x23
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x75
	.sleb128 0
	.uleb128 0x23
	.byte	0x1
	.byte	0x51
	.byte	0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x1d
	.byte	0x1
	.4byte	.LASF129
	.byte	0x1
	.byte	0x8d
	.byte	0x13
	.byte	0x1
	.4byte	0x2ff
	.4byte	.LFB77
	.4byte	.LFE77
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0xa21
	.uleb128 0x1e
	.4byte	.LASF121
	.byte	0x1
	.byte	0x8d
	.byte	0x3e
	.4byte	0x789
	.4byte	.LLST8
	.4byte	.LVUS8
	.uleb128 0x1f
	.4byte	.LASF126
	.byte	0x1
	.byte	0x8f
	.byte	0x1a
	.4byte	0x813
	.4byte	.LLST9
	.4byte	.LVUS9
	.byte	0
	.uleb128 0x1d
	.byte	0x1
	.4byte	.LASF130
	.byte	0x1
	.byte	0x7c
	.byte	0x13
	.byte	0x1
	.4byte	0x2ff
	.4byte	.LFB76
	.4byte	.LFE76
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0xa68
	.uleb128 0x1e
	.4byte	.LASF121
	.byte	0x1
	.byte	0x7c
	.byte	0x3c
	.4byte	0x789
	.4byte	.LLST6
	.4byte	.LVUS6
	.uleb128 0x1f
	.4byte	.LASF126
	.byte	0x1
	.byte	0x7e
	.byte	0x1a
	.4byte	0x813
	.4byte	.LLST7
	.4byte	.LVUS7
	.byte	0
	.uleb128 0x1d
	.byte	0x1
	.4byte	.LASF131
	.byte	0x1
	.byte	0x70
	.byte	0x13
	.byte	0x1
	.4byte	0x2ff
	.4byte	.LFB75
	.4byte	.LFE75
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0xaa9
	.uleb128 0x1e
	.4byte	.LASF121
	.byte	0x1
	.byte	0x70
	.byte	0x3a
	.4byte	0x789
	.4byte	.LLST5
	.4byte	.LVUS5
	.uleb128 0x25
	.4byte	.LASF132
	.byte	0x1
	.byte	0x70
	.byte	0x49
	.4byte	0xa4
	.byte	0x1
	.byte	0x51
	.byte	0
	.uleb128 0x26
	.byte	0x1
	.4byte	.LASF133
	.byte	0x1
	.byte	0x46
	.byte	0x13
	.byte	0x1
	.4byte	0x2ff
	.4byte	.LFB74
	.4byte	.LFE74
	.4byte	.LLST0
	.byte	0x1
	.uleb128 0x1e
	.4byte	.LASF121
	.byte	0x1
	.byte	0x46
	.byte	0x3a
	.4byte	0x789
	.4byte	.LLST1
	.4byte	.LVUS1
	.uleb128 0x1e
	.4byte	.LASF134
	.byte	0x1
	.byte	0x46
	.byte	0x48
	.4byte	0x93
	.4byte	.LLST2
	.4byte	.LVUS2
	.uleb128 0x25
	.4byte	.LASF132
	.byte	0x1
	.byte	0x46
	.byte	0x57
	.4byte	0xa4
	.byte	0x1
	.byte	0x52
	.uleb128 0x27
	.ascii	"i\000"
	.byte	0x1
	.byte	0x48
	.byte	0xb
	.4byte	0x93
	.4byte	.LLST3
	.4byte	.LVUS3
	.uleb128 0x1f
	.4byte	.LASF135
	.byte	0x1
	.byte	0x49
	.byte	0xc
	.4byte	0xb0
	.4byte	.LLST4
	.4byte	.LVUS4
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
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0xd
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
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
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
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x16
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
	.uleb128 0xc
	.uleb128 0x4
	.byte	0x1
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0xd
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.uleb128 0x11
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
	.uleb128 0x12
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
	.uleb128 0x13
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
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
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x2e
	.byte	0
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
	.uleb128 0x3c
	.uleb128 0xc
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
	.uleb128 0x18
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
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x19
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
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1a
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
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
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
	.uleb128 0x1c
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
	.uleb128 0x1d
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
	.uleb128 0x1e
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
	.uleb128 0x1f
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
	.uleb128 0x20
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
	.uleb128 0x21
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
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
	.uleb128 0x23
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x25
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
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x26
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
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LVUS12:
	.uleb128 0
	.uleb128 .LVU107
	.uleb128 .LVU107
	.uleb128 0
.LLST12:
	.4byte	.LVL25
	.4byte	.LVL27
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL27
	.4byte	.LFE80
	.2byte	0x1
	.byte	0x52
	.4byte	0
	.4byte	0
.LVUS13:
	.uleb128 .LVU96
	.uleb128 0
.LLST13:
	.4byte	.LVL26
	.4byte	.LFE80
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LVUS10:
	.uleb128 0
	.uleb128 .LVU91
	.uleb128 .LVU91
	.uleb128 0
.LLST10:
	.4byte	.LVL21
	.4byte	.LVL24
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL24
	.4byte	.LFE79
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS11:
	.uleb128 .LVU74
	.uleb128 .LVU88
.LLST11:
	.4byte	.LVL22
	.4byte	.LVL23
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LLST14:
	.4byte	.LFB78
	.4byte	.LCFI3
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI3
	.4byte	.LFE78
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	0
	.4byte	0
.LVUS15:
	.uleb128 0
	.uleb128 .LVU124
	.uleb128 .LVU124
	.uleb128 0
.LLST15:
	.4byte	.LVL30
	.4byte	.LVL32-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL32-1
	.4byte	.LFE78
	.2byte	0x1
	.byte	0x55
	.4byte	0
	.4byte	0
.LVUS16:
	.uleb128 .LVU122
	.uleb128 0
.LLST16:
	.4byte	.LVL31
	.4byte	.LFE78
	.2byte	0x1
	.byte	0x54
	.4byte	0
	.4byte	0
.LVUS17:
	.uleb128 .LVU125
	.uleb128 .LVU129
	.uleb128 .LVU129
	.uleb128 0
.LLST17:
	.4byte	.LVL33
	.4byte	.LVL34
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL34
	.4byte	.LFE78
	.2byte	0x1
	.byte	0x56
	.4byte	0
	.4byte	0
.LVUS8:
	.uleb128 0
	.uleb128 .LVU62
	.uleb128 .LVU62
	.uleb128 .LVU65
	.uleb128 .LVU65
	.uleb128 0
.LLST8:
	.4byte	.LVL17
	.4byte	.LVL19
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL19
	.4byte	.LVL20
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL20
	.4byte	.LFE77
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS9:
	.uleb128 .LVU60
	.uleb128 0
.LLST9:
	.4byte	.LVL18
	.4byte	.LFE77
	.2byte	0x1
	.byte	0x52
	.4byte	0
	.4byte	0
.LVUS6:
	.uleb128 0
	.uleb128 .LVU47
	.uleb128 .LVU47
	.uleb128 .LVU50
	.uleb128 .LVU50
	.uleb128 0
.LLST6:
	.4byte	.LVL13
	.4byte	.LVL15
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL15
	.4byte	.LVL16
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL16
	.4byte	.LFE76
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS7:
	.uleb128 .LVU43
	.uleb128 0
.LLST7:
	.4byte	.LVL14
	.4byte	.LFE76
	.2byte	0x1
	.byte	0x52
	.4byte	0
	.4byte	0
.LVUS5:
	.uleb128 0
	.uleb128 .LVU38
	.uleb128 .LVU38
	.uleb128 0
.LLST5:
	.4byte	.LVL11
	.4byte	.LVL12
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL12
	.4byte	.LFE75
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST0:
	.4byte	.LFB74
	.4byte	.LCFI0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI0
	.4byte	.LCFI1
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	.LCFI1
	.4byte	.LCFI2
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI2
	.4byte	.LFE74
	.2byte	0x2
	.byte	0x7d
	.sleb128 4
	.4byte	0
	.4byte	0
.LVUS1:
	.uleb128 0
	.uleb128 .LVU7
	.uleb128 .LVU7
	.uleb128 0
.LLST1:
	.4byte	.LVL0
	.4byte	.LVL1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL1
	.4byte	.LFE74
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS2:
	.uleb128 0
	.uleb128 .LVU12
	.uleb128 .LVU12
	.uleb128 .LVU14
	.uleb128 .LVU14
	.uleb128 .LVU21
	.uleb128 .LVU21
	.uleb128 0
.LLST2:
	.4byte	.LVL0
	.4byte	.LVL3
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL3
	.4byte	.LVL4
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL4
	.4byte	.LVL6
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL6
	.4byte	.LFE74
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS3:
	.uleb128 .LVU19
	.uleb128 .LVU21
	.uleb128 .LVU21
	.uleb128 .LVU25
	.uleb128 .LVU26
	.uleb128 0
.LLST3:
	.4byte	.LVL5
	.4byte	.LVL6
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL6
	.4byte	.LVL8
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL9
	.4byte	.LFE74
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LVUS4:
	.uleb128 .LVU7
	.uleb128 .LVU11
	.uleb128 .LVU14
	.uleb128 .LVU31
.LLST4:
	.4byte	.LVL1
	.4byte	.LVL2
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL4
	.4byte	.LVL10
	.2byte	0x1
	.byte	0x50
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
	.4byte	.LFB74
	.4byte	.LFE74-.LFB74
	.4byte	.LFB75
	.4byte	.LFE75-.LFB75
	.4byte	.LFB76
	.4byte	.LFE76-.LFB76
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
	.4byte	.LFB78
	.4byte	.LFE78-.LFB78
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LFB74
	.4byte	.LFE74
	.4byte	.LFB75
	.4byte	.LFE75
	.4byte	.LFB76
	.4byte	.LFE76
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
	.4byte	.LFB78
	.4byte	.LFE78
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF121:
	.ascii	"hpcd\000"
.LASF20:
	.ascii	"GINTSTS\000"
.LASF84:
	.ascii	"HAL_PCD_STATE_BUSY\000"
.LASF111:
	.ascii	"State\000"
.LASF122:
	.ascii	"HAL_PCDEx_BCD_Callback\000"
.LASF126:
	.ascii	"USBx\000"
.LASF104:
	.ascii	"PCD_EPTypeDef\000"
.LASF75:
	.ascii	"tx_fifo_num\000"
.LASF74:
	.ascii	"even_odd_frame\000"
.LASF3:
	.ascii	"__uint8_t\000"
.LASF17:
	.ascii	"GAHBCFG\000"
.LASF45:
	.ascii	"HAL_BUSY\000"
.LASF68:
	.ascii	"type\000"
.LASF108:
	.ascii	"IN_ep\000"
.LASF10:
	.ascii	"long long unsigned int\000"
.LASF90:
	.ascii	"LPM_L3\000"
.LASF97:
	.ascii	"PCD_BCD_STD_DOWNSTREAM_PORT\000"
.LASF82:
	.ascii	"HAL_PCD_STATE_READY\000"
.LASF61:
	.ascii	"vbus_sensing_enable\000"
.LASF51:
	.ascii	"dev_endpoints\000"
.LASF67:
	.ascii	"is_iso_incomplete\000"
.LASF113:
	.ascii	"Setup\000"
.LASF9:
	.ascii	"long long int\000"
.LASF0:
	.ascii	"signed char\000"
.LASF33:
	.ascii	"Reserved6\000"
.LASF135:
	.ascii	"Tx_Offset\000"
.LASF114:
	.ascii	"LPM_State\000"
.LASF50:
	.ascii	"HAL_LockTypeDef\000"
.LASF6:
	.ascii	"long int\000"
.LASF98:
	.ascii	"PCD_BCD_CHARGING_DOWNSTREAM_PORT\000"
.LASF129:
	.ascii	"HAL_PCDEx_DeActivateLPM\000"
.LASF94:
	.ascii	"PCD_LPM_MsgTypeDef\000"
.LASF56:
	.ascii	"phy_itface\000"
.LASF18:
	.ascii	"GUSBCFG\000"
.LASF73:
	.ascii	"xfer_count\000"
.LASF13:
	.ascii	"uint16_t\000"
.LASF36:
	.ascii	"GDFIFOCFG\000"
.LASF130:
	.ascii	"HAL_PCDEx_ActivateLPM\000"
.LASF110:
	.ascii	"Lock\000"
.LASF7:
	.ascii	"__uint32_t\000"
.LASF124:
	.ascii	"HAL_PCDEx_DeActivateBCD\000"
.LASF138:
	.ascii	"/home/emanuele/Desktop/CROSSCON/Repo/baremetal-tee/"
	.ascii	"MPU-version/apps/keylogger/Debug\000"
.LASF66:
	.ascii	"is_stall\000"
.LASF25:
	.ascii	"DIEPTXF0_HNPTXFSIZ\000"
.LASF52:
	.ascii	"Host_channels\000"
.LASF16:
	.ascii	"GOTGINT\000"
.LASF34:
	.ascii	"GLPMCFG\000"
.LASF78:
	.ascii	"USB_EPTypeDef\000"
.LASF11:
	.ascii	"unsigned int\000"
.LASF46:
	.ascii	"HAL_TIMEOUT\000"
.LASF87:
	.ascii	"LPM_L0\000"
.LASF88:
	.ascii	"LPM_L1\000"
.LASF89:
	.ascii	"LPM_L2\000"
.LASF79:
	.ascii	"USB_OTG_CfgTypeDef\000"
.LASF116:
	.ascii	"FrameNumber\000"
.LASF125:
	.ascii	"HAL_PCDEx_ActivateBCD\000"
.LASF8:
	.ascii	"long unsigned int\000"
.LASF43:
	.ascii	"HAL_OK\000"
.LASF35:
	.ascii	"GPWRDN\000"
.LASF30:
	.ascii	"GHWCFG1\000"
.LASF31:
	.ascii	"GHWCFG2\000"
.LASF32:
	.ascii	"GHWCFG3\000"
.LASF132:
	.ascii	"size\000"
.LASF5:
	.ascii	"short unsigned int\000"
.LASF131:
	.ascii	"HAL_PCDEx_SetRxFiFo\000"
.LASF91:
	.ascii	"PCD_LPM_StateTypeDef\000"
.LASF96:
	.ascii	"PCD_BCD_CONTACT_DETECTION\000"
.LASF63:
	.ascii	"use_external_vbus\000"
.LASF112:
	.ascii	"ErrorCode\000"
.LASF86:
	.ascii	"PCD_StateTypeDef\000"
.LASF19:
	.ascii	"GRSTCTL\000"
.LASF47:
	.ascii	"HAL_StatusTypeDef\000"
.LASF95:
	.ascii	"PCD_BCD_ERROR\000"
.LASF99:
	.ascii	"PCD_BCD_DEDICATED_CHARGING_PORT\000"
.LASF72:
	.ascii	"xfer_len\000"
.LASF23:
	.ascii	"GRXSTSP\000"
.LASF22:
	.ascii	"GRXSTSR\000"
.LASF29:
	.ascii	"GSNPSID\000"
.LASF140:
	.ascii	"HAL_GetTick\000"
.LASF137:
	.ascii	"../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_p"
	.ascii	"cd_ex.c\000"
.LASF49:
	.ascii	"HAL_LOCKED\000"
.LASF120:
	.ascii	"PCD_HandleTypeDef\000"
.LASF53:
	.ascii	"dma_enable\000"
.LASF27:
	.ascii	"Reserved30\000"
.LASF106:
	.ascii	"Init\000"
.LASF70:
	.ascii	"maxpacket\000"
.LASF105:
	.ascii	"Instance\000"
.LASF102:
	.ascii	"PCD_TypeDef\000"
.LASF41:
	.ascii	"USB_OTG_GlobalTypeDef\000"
.LASF65:
	.ascii	"is_in\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF2:
	.ascii	"short int\000"
.LASF21:
	.ascii	"GINTMSK\000"
.LASF128:
	.ascii	"tickstart\000"
.LASF127:
	.ascii	"HAL_PCDEx_BCD_VBUSDetect\000"
.LASF38:
	.ascii	"Reserved43\000"
.LASF69:
	.ascii	"data_pid_start\000"
.LASF103:
	.ascii	"PCD_InitTypeDef\000"
.LASF107:
	.ascii	"USB_Address\000"
.LASF64:
	.ascii	"USB_CfgTypeDef\000"
.LASF100:
	.ascii	"PCD_BCD_DISCOVERY_COMPLETED\000"
.LASF60:
	.ascii	"battery_charging_enable\000"
.LASF14:
	.ascii	"uint32_t\000"
.LASF117:
	.ascii	"lpm_active\000"
.LASF44:
	.ascii	"HAL_ERROR\000"
.LASF42:
	.ascii	"long double\000"
.LASF80:
	.ascii	"USB_OTG_EPTypeDef\000"
.LASF139:
	.ascii	"HAL_Delay\000"
.LASF4:
	.ascii	"__uint16_t\000"
.LASF136:
	.ascii	"GNU C17 12.3.1 20230626 -mcpu=cortex-m3 -mthumb -mf"
	.ascii	"loat-abi=soft -march=armv7-m -g -gdwarf-2 -Og -fdat"
	.ascii	"a-sections -ffunction-sections\000"
.LASF62:
	.ascii	"use_dedicated_ep1\000"
.LASF93:
	.ascii	"PCD_LPM_L1_ACTIVE\000"
.LASF77:
	.ascii	"xfer_size\000"
.LASF92:
	.ascii	"PCD_LPM_L0_ACTIVE\000"
.LASF109:
	.ascii	"OUT_ep\000"
.LASF24:
	.ascii	"GRXFSIZ\000"
.LASF115:
	.ascii	"BESL\000"
.LASF55:
	.ascii	"ep0_mps\000"
.LASF119:
	.ascii	"pData\000"
.LASF15:
	.ascii	"GOTGCTL\000"
.LASF123:
	.ascii	"HAL_PCDEx_LPM_Callback\000"
.LASF37:
	.ascii	"GADPCTL\000"
.LASF71:
	.ascii	"xfer_buff\000"
.LASF39:
	.ascii	"HPTXFSIZ\000"
.LASF57:
	.ascii	"Sof_enable\000"
.LASF83:
	.ascii	"HAL_PCD_STATE_ERROR\000"
.LASF59:
	.ascii	"lpm_enable\000"
.LASF76:
	.ascii	"dma_addr\000"
.LASF85:
	.ascii	"HAL_PCD_STATE_TIMEOUT\000"
.LASF12:
	.ascii	"uint8_t\000"
.LASF134:
	.ascii	"fifo\000"
.LASF28:
	.ascii	"GCCFG\000"
.LASF101:
	.ascii	"PCD_BCD_MsgTypeDef\000"
.LASF54:
	.ascii	"speed\000"
.LASF133:
	.ascii	"HAL_PCDEx_SetTxFiFo\000"
.LASF48:
	.ascii	"HAL_UNLOCKED\000"
.LASF40:
	.ascii	"DIEPTXF\000"
.LASF118:
	.ascii	"battery_charging_active\000"
.LASF58:
	.ascii	"low_power_enable\000"
.LASF26:
	.ascii	"HNPTXSTS\000"
.LASF81:
	.ascii	"HAL_PCD_STATE_RESET\000"
	.ident	"GCC: (GNU Tools for STM32 12.3.rel1.20240612-1315) 12.3.1 20230626"
