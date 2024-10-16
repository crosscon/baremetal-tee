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
	.file	"stm32l4xx_hal_rng.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 1 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rng.c"
	.section	.text.HAL_RNG_MspInit,"ax",%progbits
	.align	1
	.weak	HAL_RNG_MspInit
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RNG_MspInit, %function
HAL_RNG_MspInit:
.LVL0:
.LFB76:
	.loc 1 389 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 391 3 view .LVU1
	.loc 1 395 1 is_stmt 0 view .LVU2
	bx	lr
	.cfi_endproc
.LFE76:
	.size	HAL_RNG_MspInit, .-HAL_RNG_MspInit
	.section	.text.HAL_RNG_Init,"ax",%progbits
	.align	1
	.global	HAL_RNG_Init
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RNG_Init, %function
HAL_RNG_Init:
.LVL1:
.LFB74:
	.loc 1 168 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 169 3 view .LVU4
	.loc 1 174 3 view .LVU5
	.loc 1 174 6 is_stmt 0 view .LVU6
	cmp	r0, #0
	beq	.L8
	.loc 1 168 1 view .LVU7
	push	{r3, r4, r5, lr}
.LCFI0:
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	.cfi_offset 4, -12
	.cfi_offset 5, -8
	.cfi_offset 14, -4
	mov	r4, r0
	.loc 1 179 3 is_stmt 1 view .LVU8
	.loc 1 202 3 view .LVU9
	.loc 1 202 11 is_stmt 0 view .LVU10
	ldrb	r3, [r0, #5]	@ zero_extendqisi2
	.loc 1 202 6 view .LVU11
	cbz	r3, .L13
.LVL2:
.L4:
	.loc 1 213 3 is_stmt 1 view .LVU12
	.loc 1 213 15 is_stmt 0 view .LVU13
	movs	r3, #2
	strb	r3, [r4, #5]
	.loc 1 264 3 is_stmt 1 view .LVU14
	ldr	r2, [r4]
	ldr	r3, [r2]
	orr	r3, r3, #4
	str	r3, [r2]
	.loc 1 267 3 view .LVU15
	.loc 1 267 7 is_stmt 0 view .LVU16
	ldr	r3, [r4]
	ldr	r3, [r3, #4]
	.loc 1 267 6 view .LVU17
	tst	r3, #64
	beq	.L5
	.loc 1 269 5 is_stmt 1 view .LVU18
	.loc 1 269 17 is_stmt 0 view .LVU19
	movs	r3, #4
	strb	r3, [r4, #5]
	.loc 1 270 5 is_stmt 1 view .LVU20
	.loc 1 270 12 is_stmt 0 view .LVU21
	movs	r0, #1
.L3:
	.loc 1 297 1 view .LVU22
	pop	{r3, r4, r5, pc}
.LVL3:
.L13:
	.loc 1 205 5 is_stmt 1 view .LVU23
	.loc 1 205 16 is_stmt 0 view .LVU24
	strb	r3, [r0, #4]
	.loc 1 208 5 is_stmt 1 view .LVU25
	bl	HAL_RNG_MspInit
.LVL4:
	.loc 1 208 5 is_stmt 0 view .LVU26
	b	.L4
.L5:
	.loc 1 273 3 is_stmt 1 view .LVU27
	.loc 1 273 15 is_stmt 0 view .LVU28
	bl	HAL_GetTick
.LVL5:
	mov	r5, r0
.LVL6:
	.loc 1 275 3 is_stmt 1 view .LVU29
.L6:
	.loc 1 275 50 view .LVU30
	.loc 1 275 10 is_stmt 0 view .LVU31
	ldr	r3, [r4]
	ldr	r3, [r3, #4]
	.loc 1 275 50 view .LVU32
	tst	r3, #1
	bne	.L14
	.loc 1 277 5 is_stmt 1 view .LVU33
	.loc 1 277 10 is_stmt 0 view .LVU34
	bl	HAL_GetTick
.LVL7:
	.loc 1 277 24 view .LVU35
	subs	r0, r0, r5
	.loc 1 277 8 view .LVU36
	cmp	r0, #2
	bls	.L6
	.loc 1 280 7 is_stmt 1 view .LVU37
	.loc 1 280 11 is_stmt 0 view .LVU38
	ldr	r3, [r4]
	ldr	r3, [r3, #4]
	.loc 1 280 10 view .LVU39
	tst	r3, #1
	bne	.L6
	.loc 1 282 9 is_stmt 1 view .LVU40
	.loc 1 282 21 is_stmt 0 view .LVU41
	movs	r3, #4
	strb	r3, [r4, #5]
	.loc 1 283 9 is_stmt 1 view .LVU42
	.loc 1 283 25 is_stmt 0 view .LVU43
	movs	r3, #2
	str	r3, [r4, #8]
	.loc 1 284 9 is_stmt 1 view .LVU44
	.loc 1 284 16 is_stmt 0 view .LVU45
	movs	r0, #1
	b	.L3
.L14:
	.loc 1 290 3 is_stmt 1 view .LVU46
	.loc 1 290 15 is_stmt 0 view .LVU47
	movs	r3, #1
	strb	r3, [r4, #5]
	.loc 1 293 3 is_stmt 1 view .LVU48
	.loc 1 293 19 is_stmt 0 view .LVU49
	movs	r0, #0
	str	r0, [r4, #8]
	.loc 1 296 3 is_stmt 1 view .LVU50
	.loc 1 296 10 is_stmt 0 view .LVU51
	b	.L3
.LVL8:
.L8:
.LCFI1:
	.cfi_def_cfa_offset 0
	.cfi_restore 3
	.cfi_restore 4
	.cfi_restore 5
	.cfi_restore 14
	.loc 1 176 12 view .LVU52
	movs	r0, #1
.LVL9:
	.loc 1 297 1 view .LVU53
	bx	lr
	.cfi_endproc
.LFE74:
	.size	HAL_RNG_Init, .-HAL_RNG_Init
	.section	.text.HAL_RNG_MspDeInit,"ax",%progbits
	.align	1
	.weak	HAL_RNG_MspDeInit
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RNG_MspDeInit, %function
HAL_RNG_MspDeInit:
.LVL10:
.LFB77:
	.loc 1 404 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 406 3 view .LVU55
	.loc 1 410 1 is_stmt 0 view .LVU56
	bx	lr
	.cfi_endproc
.LFE77:
	.size	HAL_RNG_MspDeInit, .-HAL_RNG_MspDeInit
	.section	.text.HAL_RNG_DeInit,"ax",%progbits
	.align	1
	.global	HAL_RNG_DeInit
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RNG_DeInit, %function
HAL_RNG_DeInit:
.LVL11:
.LFB75:
	.loc 1 306 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 312 3 view .LVU58
	.loc 1 312 6 is_stmt 0 view .LVU59
	cbz	r0, .L18
	.loc 1 306 1 view .LVU60
	push	{r4, lr}
.LCFI2:
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	mov	r4, r0
	.loc 1 351 3 is_stmt 1 view .LVU61
	ldr	r2, [r0]
	ldr	r3, [r2]
	bic	r3, r3, #12
	str	r3, [r2]
	.loc 1 354 3 view .LVU62
	ldr	r2, [r0]
	ldr	r3, [r2, #4]
	bic	r3, r3, #96
	str	r3, [r2, #4]
	.loc 1 366 3 view .LVU63
	bl	HAL_RNG_MspDeInit
.LVL12:
	.loc 1 370 3 view .LVU64
	.loc 1 370 15 is_stmt 0 view .LVU65
	movs	r0, #0
	strb	r0, [r4, #5]
	.loc 1 373 3 is_stmt 1 view .LVU66
	.loc 1 373 19 is_stmt 0 view .LVU67
	str	r0, [r4, #8]
	.loc 1 376 3 is_stmt 1 view .LVU68
	.loc 1 376 3 view .LVU69
	strb	r0, [r4, #4]
	.loc 1 376 3 view .LVU70
	.loc 1 379 3 view .LVU71
	.loc 1 380 1 is_stmt 0 view .LVU72
	pop	{r4, pc}
.LVL13:
.L18:
.LCFI3:
	.cfi_def_cfa_offset 0
	.cfi_restore 4
	.cfi_restore 14
	.loc 1 314 12 view .LVU73
	movs	r0, #1
.LVL14:
	.loc 1 380 1 view .LVU74
	bx	lr
	.cfi_endproc
.LFE75:
	.size	HAL_RNG_DeInit, .-HAL_RNG_DeInit
	.section	.text.HAL_RNG_GenerateRandomNumber,"ax",%progbits
	.align	1
	.global	HAL_RNG_GenerateRandomNumber
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RNG_GenerateRandomNumber, %function
HAL_RNG_GenerateRandomNumber:
.LVL15:
.LFB78:
	.loc 1 674 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 674 1 is_stmt 0 view .LVU76
	push	{r3, r4, r5, r6, r7, lr}
.LCFI4:
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	.cfi_offset 4, -20
	.cfi_offset 5, -16
	.cfi_offset 6, -12
	.cfi_offset 7, -8
	.cfi_offset 14, -4
	.loc 1 675 3 is_stmt 1 view .LVU77
	.loc 1 676 3 view .LVU78
.LVL16:
	.loc 1 679 3 view .LVU79
	.loc 1 679 3 view .LVU80
	ldrb	r3, [r0, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L29
	mov	r4, r0
	mov	r6, r1
	.loc 1 679 3 discriminator 2 view .LVU81
	movs	r3, #1
	strb	r3, [r0, #4]
	.loc 1 679 3 discriminator 2 view .LVU82
	.loc 1 682 3 discriminator 2 view .LVU83
	.loc 1 682 11 is_stmt 0 discriminator 2 view .LVU84
	ldrb	r5, [r0, #5]	@ zero_extendqisi2
	uxtb	r5, r5
	.loc 1 682 6 discriminator 2 view .LVU85
	cmp	r5, r3
	beq	.L31
	.loc 1 744 5 is_stmt 1 view .LVU86
	.loc 1 744 21 is_stmt 0 view .LVU87
	movs	r3, #4
	str	r3, [r0, #8]
	.loc 1 745 5 is_stmt 1 view .LVU88
.LVL17:
	.loc 1 745 12 is_stmt 0 view .LVU89
	movs	r5, #1
.LVL18:
.L28:
	.loc 1 749 3 is_stmt 1 view .LVU90
	.loc 1 749 3 view .LVU91
	movs	r3, #0
	strb	r3, [r4, #4]
	.loc 1 749 3 view .LVU92
	.loc 1 751 3 view .LVU93
.LVL19:
.L24:
	.loc 1 752 1 is_stmt 0 view .LVU94
	mov	r0, r5
	pop	{r3, r4, r5, r6, r7, pc}
.LVL20:
.L31:
	.loc 1 685 5 is_stmt 1 view .LVU95
	.loc 1 685 17 is_stmt 0 view .LVU96
	movs	r3, #2
	strb	r3, [r0, #5]
	.loc 1 702 5 is_stmt 1 view .LVU97
	.loc 1 702 17 is_stmt 0 view .LVU98
	bl	HAL_GetTick
.LVL21:
	.loc 1 702 17 view .LVU99
	mov	r7, r0
.LVL22:
	.loc 1 705 5 is_stmt 1 view .LVU100
.L26:
	.loc 1 705 52 view .LVU101
	.loc 1 705 12 is_stmt 0 view .LVU102
	ldr	r3, [r4]
	ldr	r2, [r3, #4]
	.loc 1 705 52 view .LVU103
	tst	r2, #1
	bne	.L32
	.loc 1 707 7 is_stmt 1 view .LVU104
	.loc 1 707 12 is_stmt 0 view .LVU105
	bl	HAL_GetTick
.LVL23:
	.loc 1 707 26 view .LVU106
	subs	r0, r0, r7
	.loc 1 707 10 view .LVU107
	cmp	r0, #2
	bls	.L26
	.loc 1 710 9 is_stmt 1 view .LVU108
	.loc 1 710 13 is_stmt 0 view .LVU109
	ldr	r3, [r4]
	ldr	r3, [r3, #4]
	.loc 1 710 12 view .LVU110
	tst	r3, #1
	bne	.L26
	.loc 1 712 11 is_stmt 1 view .LVU111
	.loc 1 712 23 is_stmt 0 view .LVU112
	movs	r3, #1
	strb	r3, [r4, #5]
	.loc 1 713 11 is_stmt 1 view .LVU113
	.loc 1 713 27 is_stmt 0 view .LVU114
	movs	r3, #2
	str	r3, [r4, #8]
	.loc 1 715 11 is_stmt 1 view .LVU115
	.loc 1 715 11 view .LVU116
	movs	r3, #0
	strb	r3, [r4, #4]
	.loc 1 715 11 view .LVU117
	.loc 1 716 11 view .LVU118
	.loc 1 716 18 is_stmt 0 view .LVU119
	b	.L24
.L32:
	.loc 1 722 5 is_stmt 1 view .LVU120
	.loc 1 722 40 is_stmt 0 view .LVU121
	ldr	r3, [r3, #8]
	.loc 1 722 24 view .LVU122
	str	r3, [r4, #12]
	.loc 1 737 5 is_stmt 1 view .LVU123
	.loc 1 737 18 is_stmt 0 view .LVU124
	str	r3, [r6]
	.loc 1 740 5 is_stmt 1 view .LVU125
	.loc 1 740 17 is_stmt 0 view .LVU126
	movs	r3, #1
	strb	r3, [r4, #5]
	.loc 1 676 21 view .LVU127
	movs	r5, #0
	b	.L28
.LVL24:
.L29:
	.loc 1 679 3 view .LVU128
	movs	r5, #2
	b	.L24
	.cfi_endproc
.LFE78:
	.size	HAL_RNG_GenerateRandomNumber, .-HAL_RNG_GenerateRandomNumber
	.section	.text.HAL_RNG_GenerateRandomNumber_IT,"ax",%progbits
	.align	1
	.global	HAL_RNG_GenerateRandomNumber_IT
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RNG_GenerateRandomNumber_IT, %function
HAL_RNG_GenerateRandomNumber_IT:
.LVL25:
.LFB79:
	.loc 1 761 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 762 3 view .LVU130
	.loc 1 765 3 view .LVU131
	.loc 1 765 3 view .LVU132
	ldrb	r3, [r0, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L36
	.loc 1 765 3 discriminator 2 view .LVU133
	movs	r3, #1
	strb	r3, [r0, #4]
	.loc 1 765 3 discriminator 2 view .LVU134
	.loc 1 768 3 discriminator 2 view .LVU135
	.loc 1 768 11 is_stmt 0 discriminator 2 view .LVU136
	ldrb	r3, [r0, #5]	@ zero_extendqisi2
	uxtb	r3, r3
	.loc 1 768 6 discriminator 2 view .LVU137
	cmp	r3, #1
	beq	.L37
	.loc 1 779 5 is_stmt 1 view .LVU138
	.loc 1 779 5 view .LVU139
	movs	r3, #0
	strb	r3, [r0, #4]
	.loc 1 779 5 view .LVU140
	.loc 1 781 5 view .LVU141
	.loc 1 781 21 is_stmt 0 view .LVU142
	movs	r3, #4
	str	r3, [r0, #8]
	.loc 1 782 5 is_stmt 1 view .LVU143
.LVL26:
	.loc 1 782 12 is_stmt 0 view .LVU144
	movs	r0, #1
.LVL27:
	.loc 1 782 12 view .LVU145
	bx	lr
.LVL28:
.L37:
	.loc 1 771 5 is_stmt 1 view .LVU146
	.loc 1 771 17 is_stmt 0 view .LVU147
	movs	r3, #2
	strb	r3, [r0, #5]
	.loc 1 774 5 is_stmt 1 view .LVU148
	ldr	r2, [r0]
	ldr	r3, [r2]
	orr	r3, r3, #8
	str	r3, [r2]
	.loc 1 762 21 is_stmt 0 view .LVU149
	movs	r0, #0
.LVL29:
	.loc 1 762 21 view .LVU150
	bx	lr
.LVL30:
.L36:
	.loc 1 765 3 view .LVU151
	movs	r0, #2
.LVL31:
	.loc 1 786 1 view .LVU152
	bx	lr
	.cfi_endproc
.LFE79:
	.size	HAL_RNG_GenerateRandomNumber_IT, .-HAL_RNG_GenerateRandomNumber_IT
	.section	.text.HAL_RNG_GetRandomNumber,"ax",%progbits
	.align	1
	.global	HAL_RNG_GetRandomNumber
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RNG_GetRandomNumber, %function
HAL_RNG_GetRandomNumber:
.LVL32:
.LFB80:
	.loc 1 796 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 796 1 is_stmt 0 view .LVU154
	push	{r4, lr}
.LCFI5:
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	mov	r4, r0
	.loc 1 797 3 is_stmt 1 view .LVU155
	.loc 1 797 7 is_stmt 0 view .LVU156
	add	r1, r0, #12
	bl	HAL_RNG_GenerateRandomNumber
.LVL33:
	.loc 1 797 6 view .LVU157
	cbnz	r0, .L40
	.loc 1 799 5 is_stmt 1 view .LVU158
	.loc 1 799 16 is_stmt 0 view .LVU159
	ldr	r0, [r4, #12]
.L38:
	.loc 1 805 1 view .LVU160
	pop	{r4, pc}
.LVL34:
.L40:
	.loc 1 803 12 view .LVU161
	movs	r0, #0
	b	.L38
	.cfi_endproc
.LFE80:
	.size	HAL_RNG_GetRandomNumber, .-HAL_RNG_GetRandomNumber
	.section	.text.HAL_RNG_GetRandomNumber_IT,"ax",%progbits
	.align	1
	.global	HAL_RNG_GetRandomNumber_IT
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RNG_GetRandomNumber_IT, %function
HAL_RNG_GetRandomNumber_IT:
.LVL35:
.LFB81:
	.loc 1 815 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 816 3 view .LVU163
	.loc 1 819 3 view .LVU164
	.loc 1 819 3 view .LVU165
	ldrb	r3, [r0, #4]	@ zero_extendqisi2
	cmp	r3, #1
	beq	.L44
	.loc 1 819 3 discriminator 2 view .LVU166
	movs	r3, #1
	strb	r3, [r0, #4]
	.loc 1 819 3 discriminator 2 view .LVU167
	.loc 1 822 3 discriminator 2 view .LVU168
	.loc 1 822 15 is_stmt 0 discriminator 2 view .LVU169
	movs	r3, #2
	strb	r3, [r0, #5]
	.loc 1 825 3 is_stmt 1 discriminator 2 view .LVU170
	.loc 1 825 21 is_stmt 0 discriminator 2 view .LVU171
	ldr	r3, [r0]
	.loc 1 825 15 discriminator 2 view .LVU172
	ldr	r0, [r3, #8]
.LVL36:
	.loc 1 828 3 is_stmt 1 discriminator 2 view .LVU173
	ldr	r2, [r3]
	orr	r2, r2, #8
	str	r2, [r3]
	.loc 1 831 3 discriminator 2 view .LVU174
	.loc 1 831 10 is_stmt 0 discriminator 2 view .LVU175
	bx	lr
.LVL37:
.L44:
	.loc 1 819 3 view .LVU176
	movs	r0, #2
.LVL38:
	.loc 1 832 1 view .LVU177
	bx	lr
	.cfi_endproc
.LFE81:
	.size	HAL_RNG_GetRandomNumber_IT, .-HAL_RNG_GetRandomNumber_IT
	.section	.text.HAL_RNG_ReadLastRandomNumber,"ax",%progbits
	.align	1
	.global	HAL_RNG_ReadLastRandomNumber
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RNG_ReadLastRandomNumber, %function
HAL_RNG_ReadLastRandomNumber:
.LVL39:
.LFB83:
	.loc 1 943 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 944 3 view .LVU179
	.loc 1 945 1 is_stmt 0 view .LVU180
	ldr	r0, [r0, #12]
.LVL40:
	.loc 1 945 1 view .LVU181
	bx	lr
	.cfi_endproc
.LFE83:
	.size	HAL_RNG_ReadLastRandomNumber, .-HAL_RNG_ReadLastRandomNumber
	.section	.text.HAL_RNG_ReadyDataCallback,"ax",%progbits
	.align	1
	.weak	HAL_RNG_ReadyDataCallback
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RNG_ReadyDataCallback, %function
HAL_RNG_ReadyDataCallback:
.LVL41:
.LFB84:
	.loc 1 961 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 963 3 view .LVU183
	.loc 1 964 3 view .LVU184
	.loc 1 968 1 is_stmt 0 view .LVU185
	bx	lr
	.cfi_endproc
.LFE84:
	.size	HAL_RNG_ReadyDataCallback, .-HAL_RNG_ReadyDataCallback
	.section	.text.HAL_RNG_ErrorCallback,"ax",%progbits
	.align	1
	.weak	HAL_RNG_ErrorCallback
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RNG_ErrorCallback, %function
HAL_RNG_ErrorCallback:
.LVL42:
.LFB85:
	.loc 1 977 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 979 3 view .LVU187
	.loc 1 983 1 is_stmt 0 view .LVU188
	bx	lr
	.cfi_endproc
.LFE85:
	.size	HAL_RNG_ErrorCallback, .-HAL_RNG_ErrorCallback
	.section	.text.HAL_RNG_IRQHandler,"ax",%progbits
	.align	1
	.global	HAL_RNG_IRQHandler
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RNG_IRQHandler, %function
HAL_RNG_IRQHandler:
.LVL43:
.LFB82:
	.loc 1 856 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 856 1 is_stmt 0 view .LVU190
	push	{r4, lr}
.LCFI6:
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	mov	r4, r0
	.loc 1 857 3 is_stmt 1 view .LVU191
.LVL44:
	.loc 1 858 3 view .LVU192
	.loc 1 858 27 is_stmt 0 view .LVU193
	ldr	r2, [r0]
	.loc 1 858 12 view .LVU194
	ldr	r3, [r2, #4]
.LVL45:
	.loc 1 861 3 is_stmt 1 view .LVU195
	.loc 1 861 6 is_stmt 0 view .LVU196
	tst	r3, #32
	bne	.L55
	.loc 1 867 8 is_stmt 1 view .LVU197
	.loc 1 867 11 is_stmt 0 view .LVU198
	tst	r3, #64
	beq	.L51
	.loc 1 870 5 is_stmt 1 view .LVU199
	.loc 1 870 8 is_stmt 0 view .LVU200
	tst	r3, #4
	bne	.L52
	.loc 1 874 7 is_stmt 1 view .LVU201
	ldr	r1, [r2, #4]
	bic	r1, r1, #64
	str	r1, [r2, #4]
	.loc 1 888 3 view .LVU202
	.loc 1 890 3 view .LVU203
.L51:
.LVL46:
	.loc 1 910 3 view .LVU204
	.loc 1 910 6 is_stmt 0 view .LVU205
	tst	r3, #1
	beq	.L48
	.loc 1 913 5 is_stmt 1 view .LVU206
	ldr	r2, [r4]
	ldr	r3, [r2]
.LVL47:
	.loc 1 913 5 is_stmt 0 view .LVU207
	bic	r3, r3, #8
	str	r3, [r2]
	.loc 1 916 5 is_stmt 1 view .LVU208
	.loc 1 916 30 is_stmt 0 view .LVU209
	ldr	r3, [r4]
	.loc 1 916 40 view .LVU210
	ldr	r1, [r3, #8]
	.loc 1 916 24 view .LVU211
	str	r1, [r4, #12]
	.loc 1 918 5 is_stmt 1 view .LVU212
	.loc 1 918 13 is_stmt 0 view .LVU213
	ldrb	r3, [r4, #5]	@ zero_extendqisi2
	uxtb	r3, r3
	.loc 1 918 8 view .LVU214
	cmp	r3, #4
	beq	.L48
	.loc 1 921 7 is_stmt 1 view .LVU215
	.loc 1 921 19 is_stmt 0 view .LVU216
	movs	r3, #1
	strb	r3, [r4, #5]
	.loc 1 923 7 is_stmt 1 view .LVU217
	.loc 1 923 7 view .LVU218
	movs	r3, #0
	strb	r3, [r4, #4]
	.loc 1 923 7 view .LVU219
	.loc 1 930 7 view .LVU220
	mov	r0, r4
.LVL48:
	.loc 1 930 7 is_stmt 0 view .LVU221
	bl	HAL_RNG_ReadyDataCallback
.LVL49:
	b	.L48
.LVL50:
.L55:
	.loc 1 864 5 is_stmt 1 view .LVU222
	.loc 1 864 21 is_stmt 0 view .LVU223
	movs	r3, #16
.LVL51:
	.loc 1 864 21 view .LVU224
	str	r3, [r0, #8]
	.loc 1 865 5 is_stmt 1 view .LVU225
.LVL52:
	.loc 1 888 3 view .LVU226
	.loc 1 890 3 view .LVU227
.L50:
	.loc 1 893 5 view .LVU228
	.loc 1 893 17 is_stmt 0 view .LVU229
	movs	r3, #4
	strb	r3, [r4, #5]
	.loc 1 900 5 is_stmt 1 view .LVU230
	mov	r0, r4
.LVL53:
	.loc 1 900 5 is_stmt 0 view .LVU231
	bl	HAL_RNG_ErrorCallback
.LVL54:
	.loc 1 904 5 is_stmt 1 view .LVU232
	ldr	r3, [r4]
	mvn	r2, #96
	str	r2, [r3, #4]
	.loc 1 906 5 view .LVU233
.LVL55:
.L48:
	.loc 1 934 1 is_stmt 0 view .LVU234
	pop	{r4, pc}
.LVL56:
.L52:
	.loc 1 879 7 is_stmt 1 view .LVU235
	.loc 1 879 23 is_stmt 0 view .LVU236
	movs	r3, #8
.LVL57:
	.loc 1 879 23 view .LVU237
	str	r3, [r0, #8]
	.loc 1 880 7 is_stmt 1 view .LVU238
.LVL58:
	.loc 1 882 7 view .LVU239
	ldr	r3, [r2]
	bic	r3, r3, #8
	str	r3, [r2]
	.loc 1 888 3 view .LVU240
	.loc 1 890 3 view .LVU241
	b	.L50
	.cfi_endproc
.LFE82:
	.size	HAL_RNG_IRQHandler, .-HAL_RNG_IRQHandler
	.section	.text.HAL_RNG_GetState,"ax",%progbits
	.align	1
	.global	HAL_RNG_GetState
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RNG_GetState, %function
HAL_RNG_GetState:
.LVL59:
.LFB86:
	.loc 1 1011 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1012 3 view .LVU243
	.loc 1 1012 14 is_stmt 0 view .LVU244
	ldrb	r0, [r0, #5]	@ zero_extendqisi2
.LVL60:
	.loc 1 1013 1 view .LVU245
	bx	lr
	.cfi_endproc
.LFE86:
	.size	HAL_RNG_GetState, .-HAL_RNG_GetState
	.section	.text.HAL_RNG_GetError,"ax",%progbits
	.align	1
	.global	HAL_RNG_GetError
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RNG_GetError, %function
HAL_RNG_GetError:
.LVL61:
.LFB87:
	.loc 1 1021 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1023 3 view .LVU247
	.loc 1 1023 14 is_stmt 0 view .LVU248
	ldr	r0, [r0, #8]
.LVL62:
	.loc 1 1024 1 view .LVU249
	bx	lr
	.cfi_endproc
.LFE87:
	.size	HAL_RNG_GetError, .-HAL_RNG_GetError
	.text
.Letext0:
	.file 2 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/arm-none-eabi/include/machine/_default_types.h"
	.file 3 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/arm-none-eabi/include/sys/_stdint.h"
	.file 4 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
	.file 5 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l4xx.h"
	.file 6 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_def.h"
	.file 7 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rng.h"
	.file 8 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x607
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF54
	.byte	0xc
	.4byte	.LASF55
	.4byte	.LASF56
	.4byte	.Ldebug_ranges0+0
	.4byte	0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF4
	.uleb128 0x3
	.4byte	.LASF9
	.byte	0x2
	.byte	0x4f
	.byte	0x19
	.4byte	0x58
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF8
	.uleb128 0x3
	.4byte	.LASF10
	.byte	0x3
	.byte	0x30
	.byte	0x14
	.4byte	0x4c
	.uleb128 0x5
	.4byte	0x7b
	.uleb128 0x6
	.byte	0xc
	.byte	0x4
	.2byte	0x3d3
	.byte	0x9
	.4byte	0xc4
	.uleb128 0x7
	.ascii	"CR\000"
	.byte	0x4
	.2byte	0x3d5
	.byte	0x11
	.4byte	0x87
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x7
	.ascii	"SR\000"
	.byte	0x4
	.2byte	0x3d6
	.byte	0x11
	.4byte	0x87
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x7
	.ascii	"DR\000"
	.byte	0x4
	.2byte	0x3d7
	.byte	0x11
	.4byte	0x87
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0x8
	.4byte	.LASF11
	.byte	0x4
	.2byte	0x3d8
	.byte	0x3
	.4byte	0x8c
	.uleb128 0x9
	.byte	0x7
	.byte	0x1
	.4byte	0x30
	.byte	0x5
	.byte	0xba
	.byte	0x1
	.4byte	0xec
	.uleb128 0xa
	.4byte	.LASF12
	.byte	0
	.uleb128 0xb
	.ascii	"SET\000"
	.byte	0x1
	.byte	0
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF13
	.uleb128 0x9
	.byte	0x7
	.byte	0x1
	.4byte	0x30
	.byte	0x6
	.byte	0x27
	.byte	0x1
	.4byte	0x11a
	.uleb128 0xa
	.4byte	.LASF14
	.byte	0
	.uleb128 0xa
	.4byte	.LASF15
	.byte	0x1
	.uleb128 0xa
	.4byte	.LASF16
	.byte	0x2
	.uleb128 0xa
	.4byte	.LASF17
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF18
	.byte	0x6
	.byte	0x2c
	.byte	0x3
	.4byte	0xf3
	.uleb128 0x9
	.byte	0x7
	.byte	0x1
	.4byte	0x30
	.byte	0x6
	.byte	0x32
	.byte	0x1
	.4byte	0x141
	.uleb128 0xa
	.4byte	.LASF19
	.byte	0
	.uleb128 0xa
	.4byte	.LASF20
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF21
	.byte	0x6
	.byte	0x35
	.byte	0x3
	.4byte	0x126
	.uleb128 0x9
	.byte	0x7
	.byte	0x1
	.4byte	0x30
	.byte	0x7
	.byte	0x41
	.byte	0x1
	.4byte	0x17a
	.uleb128 0xa
	.4byte	.LASF22
	.byte	0
	.uleb128 0xa
	.4byte	.LASF23
	.byte	0x1
	.uleb128 0xa
	.4byte	.LASF24
	.byte	0x2
	.uleb128 0xa
	.4byte	.LASF25
	.byte	0x3
	.uleb128 0xa
	.4byte	.LASF26
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF27
	.byte	0x7
	.byte	0x48
	.byte	0x3
	.4byte	0x14d
	.uleb128 0x5
	.4byte	0x17a
	.uleb128 0xc
	.byte	0x10
	.byte	0x7
	.byte	0x54
	.byte	0x9
	.4byte	0x1e0
	.uleb128 0xd
	.4byte	.LASF28
	.byte	0x7
	.byte	0x57
	.byte	0x20
	.4byte	0x1e0
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xd
	.4byte	.LASF29
	.byte	0x7
	.byte	0x5d
	.byte	0x1f
	.4byte	0x141
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xd
	.4byte	.LASF30
	.byte	0x7
	.byte	0x5f
	.byte	0x1f
	.4byte	0x186
	.byte	0x2
	.byte	0x23
	.uleb128 0x5
	.uleb128 0xd
	.4byte	.LASF31
	.byte	0x7
	.byte	0x61
	.byte	0x1f
	.4byte	0x87
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xd
	.4byte	.LASF32
	.byte	0x7
	.byte	0x63
	.byte	0x1f
	.4byte	0x7b
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.4byte	0xc4
	.uleb128 0x3
	.4byte	.LASF33
	.byte	0x7
	.byte	0x6d
	.byte	0x3
	.4byte	0x18b
	.uleb128 0xf
	.4byte	0x1e6
	.uleb128 0x10
	.byte	0x1
	.4byte	.LASF57
	.byte	0x8
	.2byte	0x28d
	.byte	0x14
	.byte	0x1
	.4byte	0x7b
	.byte	0x1
	.uleb128 0x11
	.byte	0x1
	.4byte	.LASF34
	.byte	0x1
	.2byte	0x3fc
	.byte	0xa
	.byte	0x1
	.4byte	0x7b
	.4byte	.LFB87
	.4byte	.LFE87
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x23c
	.uleb128 0x12
	.4byte	.LASF36
	.byte	0x1
	.2byte	0x3fc
	.byte	0x34
	.4byte	0x23c
	.4byte	.LLST22
	.4byte	.LVUS22
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.4byte	0x1f2
	.uleb128 0x11
	.byte	0x1
	.4byte	.LASF35
	.byte	0x1
	.2byte	0x3f2
	.byte	0x16
	.byte	0x1
	.4byte	0x17a
	.4byte	.LFB86
	.4byte	.LFE86
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x277
	.uleb128 0x12
	.4byte	.LASF36
	.byte	0x1
	.2byte	0x3f2
	.byte	0x40
	.4byte	0x23c
	.4byte	.LLST21
	.4byte	.LVUS21
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF37
	.byte	0x1
	.2byte	0x3d0
	.byte	0xd
	.byte	0x1
	.4byte	.LFB85
	.4byte	.LFE85
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x2a2
	.uleb128 0x14
	.4byte	.LASF36
	.byte	0x1
	.2byte	0x3d0
	.byte	0x36
	.4byte	0x2a2
	.byte	0x1
	.byte	0x50
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.4byte	0x1e6
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF38
	.byte	0x1
	.2byte	0x3c0
	.byte	0xd
	.byte	0x1
	.4byte	.LFB84
	.4byte	.LFE84
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x2e2
	.uleb128 0x14
	.4byte	.LASF36
	.byte	0x1
	.2byte	0x3c0
	.byte	0x3a
	.4byte	0x2a2
	.byte	0x1
	.byte	0x50
	.uleb128 0x14
	.4byte	.LASF39
	.byte	0x1
	.2byte	0x3c0
	.byte	0x49
	.4byte	0x7b
	.byte	0x1
	.byte	0x51
	.byte	0
	.uleb128 0x11
	.byte	0x1
	.4byte	.LASF40
	.byte	0x1
	.2byte	0x3ae
	.byte	0xa
	.byte	0x1
	.4byte	0x7b
	.4byte	.LFB83
	.4byte	.LFE83
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x317
	.uleb128 0x12
	.4byte	.LASF36
	.byte	0x1
	.2byte	0x3ae
	.byte	0x40
	.4byte	0x23c
	.4byte	.LLST16
	.4byte	.LVUS16
	.byte	0
	.uleb128 0x15
	.byte	0x1
	.4byte	.LASF41
	.byte	0x1
	.2byte	0x357
	.byte	0x6
	.byte	0x1
	.4byte	.LFB82
	.4byte	.LFE82
	.4byte	.LLST17
	.byte	0x1
	.4byte	0x397
	.uleb128 0x12
	.4byte	.LASF36
	.byte	0x1
	.2byte	0x357
	.byte	0x2c
	.4byte	0x2a2
	.4byte	.LLST18
	.4byte	.LVUS18
	.uleb128 0x16
	.4byte	.LASF42
	.byte	0x1
	.2byte	0x359
	.byte	0xc
	.4byte	0x7b
	.4byte	.LLST19
	.4byte	.LVUS19
	.uleb128 0x16
	.4byte	.LASF43
	.byte	0x1
	.2byte	0x35a
	.byte	0xc
	.4byte	0x7b
	.4byte	.LLST20
	.4byte	.LVUS20
	.uleb128 0x17
	.4byte	.LVL49
	.4byte	0x2a8
	.4byte	0x386
	.uleb128 0x18
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.byte	0
	.uleb128 0x19
	.4byte	.LVL54
	.4byte	0x277
	.uleb128 0x18
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x11
	.byte	0x1
	.4byte	.LASF44
	.byte	0x1
	.2byte	0x32e
	.byte	0xa
	.byte	0x1
	.4byte	0x7b
	.4byte	.LFB81
	.4byte	.LFE81
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x3e1
	.uleb128 0x12
	.4byte	.LASF36
	.byte	0x1
	.2byte	0x32e
	.byte	0x38
	.4byte	0x2a2
	.4byte	.LLST14
	.4byte	.LVUS14
	.uleb128 0x16
	.4byte	.LASF39
	.byte	0x1
	.2byte	0x330
	.byte	0xc
	.4byte	0x7b
	.4byte	.LLST15
	.4byte	.LVUS15
	.byte	0
	.uleb128 0x1a
	.byte	0x1
	.4byte	.LASF45
	.byte	0x1
	.2byte	0x31b
	.byte	0xa
	.byte	0x1
	.4byte	0x7b
	.4byte	.LFB80
	.4byte	.LFE80
	.4byte	.LLST12
	.byte	0x1
	.4byte	0x42d
	.uleb128 0x12
	.4byte	.LASF36
	.byte	0x1
	.2byte	0x31b
	.byte	0x35
	.4byte	0x2a2
	.4byte	.LLST13
	.4byte	.LVUS13
	.uleb128 0x19
	.4byte	.LVL33
	.4byte	0x477
	.uleb128 0x18
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x18
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x74
	.sleb128 12
	.byte	0
	.byte	0
	.uleb128 0x11
	.byte	0x1
	.4byte	.LASF46
	.byte	0x1
	.2byte	0x2f8
	.byte	0x13
	.byte	0x1
	.4byte	0x11a
	.4byte	.LFB79
	.4byte	.LFE79
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x477
	.uleb128 0x12
	.4byte	.LASF36
	.byte	0x1
	.2byte	0x2f8
	.byte	0x46
	.4byte	0x2a2
	.4byte	.LLST10
	.4byte	.LVUS10
	.uleb128 0x16
	.4byte	.LASF47
	.byte	0x1
	.2byte	0x2fa
	.byte	0x15
	.4byte	0x11a
	.4byte	.LLST11
	.4byte	.LVUS11
	.byte	0
	.uleb128 0x1a
	.byte	0x1
	.4byte	.LASF48
	.byte	0x1
	.2byte	0x2a1
	.byte	0x13
	.byte	0x1
	.4byte	0x11a
	.4byte	.LFB78
	.4byte	.LFE78
	.4byte	.LLST5
	.byte	0x1
	.4byte	0x4fe
	.uleb128 0x12
	.4byte	.LASF36
	.byte	0x1
	.2byte	0x2a1
	.byte	0x43
	.4byte	0x2a2
	.4byte	.LLST6
	.4byte	.LVUS6
	.uleb128 0x12
	.4byte	.LASF39
	.byte	0x1
	.2byte	0x2a1
	.byte	0x53
	.4byte	0x4fe
	.4byte	.LLST7
	.4byte	.LVUS7
	.uleb128 0x16
	.4byte	.LASF49
	.byte	0x1
	.2byte	0x2a3
	.byte	0xc
	.4byte	0x7b
	.4byte	.LLST8
	.4byte	.LVUS8
	.uleb128 0x16
	.4byte	.LASF47
	.byte	0x1
	.2byte	0x2a4
	.byte	0x15
	.4byte	0x11a
	.4byte	.LLST9
	.4byte	.LVUS9
	.uleb128 0x1b
	.4byte	.LVL21
	.4byte	0x1f7
	.uleb128 0x1b
	.4byte	.LVL23
	.4byte	0x1f7
	.byte	0
	.uleb128 0xe
	.byte	0x4
	.4byte	0x7b
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF50
	.byte	0x1
	.2byte	0x193
	.byte	0xd
	.byte	0x1
	.4byte	.LFB77
	.4byte	.LFE77
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x52f
	.uleb128 0x14
	.4byte	.LASF36
	.byte	0x1
	.2byte	0x193
	.byte	0x32
	.4byte	0x2a2
	.byte	0x1
	.byte	0x50
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF51
	.byte	0x1
	.2byte	0x184
	.byte	0xd
	.byte	0x1
	.4byte	.LFB76
	.4byte	.LFE76
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x55a
	.uleb128 0x14
	.4byte	.LASF36
	.byte	0x1
	.2byte	0x184
	.byte	0x30
	.4byte	0x2a2
	.byte	0x1
	.byte	0x50
	.byte	0
	.uleb128 0x1a
	.byte	0x1
	.4byte	.LASF52
	.byte	0x1
	.2byte	0x131
	.byte	0x13
	.byte	0x1
	.4byte	0x11a
	.4byte	.LFB75
	.4byte	.LFE75
	.4byte	.LLST3
	.byte	0x1
	.4byte	0x5a0
	.uleb128 0x12
	.4byte	.LASF36
	.byte	0x1
	.2byte	0x131
	.byte	0x35
	.4byte	0x2a2
	.4byte	.LLST4
	.4byte	.LVUS4
	.uleb128 0x19
	.4byte	.LVL12
	.4byte	0x504
	.uleb128 0x18
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x1c
	.byte	0x1
	.4byte	.LASF53
	.byte	0x1
	.byte	0xa7
	.byte	0x13
	.byte	0x1
	.4byte	0x11a
	.4byte	.LFB74
	.4byte	.LFE74
	.4byte	.LLST0
	.byte	0x1
	.uleb128 0x1d
	.4byte	.LASF36
	.byte	0x1
	.byte	0xa7
	.byte	0x33
	.4byte	0x2a2
	.4byte	.LLST1
	.4byte	.LVUS1
	.uleb128 0x1e
	.4byte	.LASF49
	.byte	0x1
	.byte	0xa9
	.byte	0xc
	.4byte	0x7b
	.4byte	.LLST2
	.4byte	.LVUS2
	.uleb128 0x17
	.4byte	.LVL4
	.4byte	0x52f
	.4byte	0x5f7
	.uleb128 0x18
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.byte	0
	.uleb128 0x1b
	.4byte	.LVL5
	.4byte	0x1f7
	.uleb128 0x1b
	.4byte	.LVL7
	.4byte	0x1f7
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
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
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
	.uleb128 0x7
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
	.uleb128 0x8
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
	.uleb128 0x9
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
	.uleb128 0xa
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
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
	.uleb128 0xd
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
	.uleb128 0xe
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.uleb128 0x11
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
	.uleb128 0x12
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
	.uleb128 0x13
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
	.uleb128 0x14
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
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x18
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
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
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
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
	.uleb128 0x1d
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
	.uleb128 0x1e
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
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LVUS22:
	.uleb128 0
	.uleb128 .LVU249
	.uleb128 .LVU249
	.uleb128 0
.LLST22:
	.4byte	.LVL61
	.4byte	.LVL62
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL62
	.4byte	.LFE87
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS21:
	.uleb128 0
	.uleb128 .LVU245
	.uleb128 .LVU245
	.uleb128 0
.LLST21:
	.4byte	.LVL59
	.4byte	.LVL60
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL60
	.4byte	.LFE86
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS16:
	.uleb128 0
	.uleb128 .LVU181
	.uleb128 .LVU181
	.uleb128 0
.LLST16:
	.4byte	.LVL39
	.4byte	.LVL40
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL40
	.4byte	.LFE83
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST17:
	.4byte	.LFB82
	.4byte	.LCFI6
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI6
	.4byte	.LFE82
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LVUS18:
	.uleb128 0
	.uleb128 .LVU221
	.uleb128 .LVU221
	.uleb128 .LVU222
	.uleb128 .LVU222
	.uleb128 .LVU231
	.uleb128 .LVU231
	.uleb128 .LVU235
	.uleb128 .LVU235
	.uleb128 0
.LLST18:
	.4byte	.LVL43
	.4byte	.LVL48
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL48
	.4byte	.LVL50
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL50
	.4byte	.LVL53
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL53
	.4byte	.LVL56
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL56
	.4byte	.LFE82
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LVUS19:
	.uleb128 .LVU192
	.uleb128 .LVU204
	.uleb128 .LVU222
	.uleb128 .LVU226
	.uleb128 .LVU226
	.uleb128 .LVU234
	.uleb128 .LVU235
	.uleb128 .LVU239
	.uleb128 .LVU239
	.uleb128 0
.LLST19:
	.4byte	.LVL44
	.4byte	.LVL46
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL50
	.4byte	.LVL52
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL52
	.4byte	.LVL55
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	.LVL56
	.4byte	.LVL58
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL58
	.4byte	.LFE82
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS20:
	.uleb128 .LVU195
	.uleb128 .LVU207
	.uleb128 .LVU222
	.uleb128 .LVU224
	.uleb128 .LVU235
	.uleb128 .LVU237
.LLST20:
	.4byte	.LVL45
	.4byte	.LVL47
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL50
	.4byte	.LVL51
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL56
	.4byte	.LVL57
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LVUS14:
	.uleb128 0
	.uleb128 .LVU173
	.uleb128 .LVU173
	.uleb128 .LVU176
	.uleb128 .LVU176
	.uleb128 .LVU177
	.uleb128 .LVU177
	.uleb128 0
.LLST14:
	.4byte	.LVL35
	.4byte	.LVL36
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL36
	.4byte	.LVL37
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL37
	.4byte	.LVL38
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL38
	.4byte	.LFE81
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS15:
	.uleb128 .LVU164
	.uleb128 .LVU173
	.uleb128 .LVU173
	.uleb128 .LVU176
	.uleb128 .LVU176
	.uleb128 0
.LLST15:
	.4byte	.LVL35
	.4byte	.LVL36
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL36
	.4byte	.LVL37
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL37
	.4byte	.LFE81
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST12:
	.4byte	.LFB80
	.4byte	.LCFI5
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI5
	.4byte	.LFE80
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LVUS13:
	.uleb128 0
	.uleb128 .LVU157
	.uleb128 .LVU157
	.uleb128 0
.LLST13:
	.4byte	.LVL32
	.4byte	.LVL33-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL33-1
	.4byte	.LFE80
	.2byte	0x1
	.byte	0x54
	.4byte	0
	.4byte	0
.LVUS10:
	.uleb128 0
	.uleb128 .LVU145
	.uleb128 .LVU145
	.uleb128 .LVU146
	.uleb128 .LVU146
	.uleb128 .LVU150
	.uleb128 .LVU150
	.uleb128 .LVU151
	.uleb128 .LVU151
	.uleb128 .LVU152
	.uleb128 .LVU152
	.uleb128 0
.LLST10:
	.4byte	.LVL25
	.4byte	.LVL27
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL27
	.4byte	.LVL28
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL28
	.4byte	.LVL29
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL29
	.4byte	.LVL30
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL30
	.4byte	.LVL31
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL31
	.4byte	.LFE79
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS11:
	.uleb128 .LVU131
	.uleb128 .LVU144
	.uleb128 .LVU144
	.uleb128 .LVU146
	.uleb128 .LVU146
	.uleb128 .LVU152
.LLST11:
	.4byte	.LVL25
	.4byte	.LVL26
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL26
	.4byte	.LVL28
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	.LVL28
	.4byte	.LVL31
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST5:
	.4byte	.LFB78
	.4byte	.LCFI4
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI4
	.4byte	.LFE78
	.2byte	0x2
	.byte	0x7d
	.sleb128 24
	.4byte	0
	.4byte	0
.LVUS6:
	.uleb128 0
	.uleb128 .LVU90
	.uleb128 .LVU90
	.uleb128 .LVU94
	.uleb128 .LVU94
	.uleb128 .LVU95
	.uleb128 .LVU95
	.uleb128 .LVU99
	.uleb128 .LVU99
	.uleb128 .LVU128
	.uleb128 .LVU128
	.uleb128 0
.LLST6:
	.4byte	.LVL15
	.4byte	.LVL18
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL18
	.4byte	.LVL19
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL19
	.4byte	.LVL20
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL20
	.4byte	.LVL21-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL21-1
	.4byte	.LVL24
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL24
	.4byte	.LFE78
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LVUS7:
	.uleb128 0
	.uleb128 .LVU90
	.uleb128 .LVU90
	.uleb128 .LVU94
	.uleb128 .LVU94
	.uleb128 .LVU95
	.uleb128 .LVU95
	.uleb128 .LVU99
	.uleb128 .LVU99
	.uleb128 .LVU128
	.uleb128 .LVU128
	.uleb128 0
.LLST7:
	.4byte	.LVL15
	.4byte	.LVL18
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL18
	.4byte	.LVL19
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL19
	.4byte	.LVL20
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL20
	.4byte	.LVL21-1
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL21-1
	.4byte	.LVL24
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL24
	.4byte	.LFE78
	.2byte	0x1
	.byte	0x51
	.4byte	0
	.4byte	0
.LVUS8:
	.uleb128 .LVU100
	.uleb128 .LVU101
	.uleb128 .LVU101
	.uleb128 .LVU128
.LLST8:
	.4byte	.LVL22
	.4byte	.LVL22
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL22
	.4byte	.LVL24
	.2byte	0x1
	.byte	0x57
	.4byte	0
	.4byte	0
.LVUS9:
	.uleb128 .LVU79
	.uleb128 .LVU89
	.uleb128 .LVU89
	.uleb128 .LVU90
	.uleb128 .LVU90
	.uleb128 .LVU94
	.uleb128 .LVU95
	.uleb128 0
.LLST9:
	.4byte	.LVL16
	.4byte	.LVL17
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL17
	.4byte	.LVL18
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	.LVL18
	.4byte	.LVL19
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL20
	.4byte	.LFE78
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST3:
	.4byte	.LFB75
	.4byte	.LCFI2
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI2
	.4byte	.LCFI3
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	.LCFI3
	.4byte	.LFE75
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	0
	.4byte	0
.LVUS4:
	.uleb128 0
	.uleb128 .LVU64
	.uleb128 .LVU64
	.uleb128 .LVU73
	.uleb128 .LVU73
	.uleb128 .LVU74
	.uleb128 .LVU74
	.uleb128 0
.LLST4:
	.4byte	.LVL11
	.4byte	.LVL12-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL12-1
	.4byte	.LVL13
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL13
	.4byte	.LVL14
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL14
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
	.sleb128 16
	.4byte	.LCFI1
	.4byte	.LFE74
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	0
	.4byte	0
.LVUS1:
	.uleb128 0
	.uleb128 .LVU12
	.uleb128 .LVU12
	.uleb128 .LVU23
	.uleb128 .LVU23
	.uleb128 .LVU26
	.uleb128 .LVU26
	.uleb128 .LVU52
	.uleb128 .LVU52
	.uleb128 .LVU53
	.uleb128 .LVU53
	.uleb128 0
.LLST1:
	.4byte	.LVL1
	.4byte	.LVL2
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL2
	.4byte	.LVL3
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL3
	.4byte	.LVL4-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL4-1
	.4byte	.LVL8
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL8
	.4byte	.LVL9
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL9
	.4byte	.LFE74
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS2:
	.uleb128 .LVU29
	.uleb128 .LVU30
	.uleb128 .LVU30
	.uleb128 .LVU52
.LLST2:
	.4byte	.LVL6
	.4byte	.LVL6
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL6
	.4byte	.LVL8
	.2byte	0x1
	.byte	0x55
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x84
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB76
	.4byte	.LFE76-.LFB76
	.4byte	.LFB74
	.4byte	.LFE74-.LFB74
	.4byte	.LFB77
	.4byte	.LFE77-.LFB77
	.4byte	.LFB75
	.4byte	.LFE75-.LFB75
	.4byte	.LFB78
	.4byte	.LFE78-.LFB78
	.4byte	.LFB79
	.4byte	.LFE79-.LFB79
	.4byte	.LFB80
	.4byte	.LFE80-.LFB80
	.4byte	.LFB81
	.4byte	.LFE81-.LFB81
	.4byte	.LFB83
	.4byte	.LFE83-.LFB83
	.4byte	.LFB84
	.4byte	.LFE84-.LFB84
	.4byte	.LFB85
	.4byte	.LFE85-.LFB85
	.4byte	.LFB82
	.4byte	.LFE82-.LFB82
	.4byte	.LFB86
	.4byte	.LFE86-.LFB86
	.4byte	.LFB87
	.4byte	.LFE87-.LFB87
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LFB76
	.4byte	.LFE76
	.4byte	.LFB74
	.4byte	.LFE74
	.4byte	.LFB77
	.4byte	.LFE77
	.4byte	.LFB75
	.4byte	.LFE75
	.4byte	.LFB78
	.4byte	.LFE78
	.4byte	.LFB79
	.4byte	.LFE79
	.4byte	.LFB80
	.4byte	.LFE80
	.4byte	.LFB81
	.4byte	.LFE81
	.4byte	.LFB83
	.4byte	.LFE83
	.4byte	.LFB84
	.4byte	.LFE84
	.4byte	.LFB85
	.4byte	.LFE85
	.4byte	.LFB82
	.4byte	.LFE82
	.4byte	.LFB86
	.4byte	.LFE86
	.4byte	.LFB87
	.4byte	.LFE87
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF48:
	.ascii	"HAL_RNG_GenerateRandomNumber\000"
.LASF51:
	.ascii	"HAL_RNG_MspInit\000"
.LASF27:
	.ascii	"HAL_RNG_StateTypeDef\000"
.LASF29:
	.ascii	"Lock\000"
.LASF3:
	.ascii	"short unsigned int\000"
.LASF20:
	.ascii	"HAL_LOCKED\000"
.LASF31:
	.ascii	"ErrorCode\000"
.LASF37:
	.ascii	"HAL_RNG_ErrorCallback\000"
.LASF35:
	.ascii	"HAL_RNG_GetState\000"
.LASF47:
	.ascii	"status\000"
.LASF32:
	.ascii	"RandomNumber\000"
.LASF24:
	.ascii	"HAL_RNG_STATE_BUSY\000"
.LASF44:
	.ascii	"HAL_RNG_GetRandomNumber_IT\000"
.LASF56:
	.ascii	"/home/emanuele/Desktop/Code/MCU-fortifier/apps/bitc"
	.ascii	"oin_wallet_demo/Debug\000"
.LASF42:
	.ascii	"rngclockerror\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF52:
	.ascii	"HAL_RNG_DeInit\000"
.LASF5:
	.ascii	"long unsigned int\000"
.LASF12:
	.ascii	"RESET\000"
.LASF30:
	.ascii	"State\000"
.LASF10:
	.ascii	"uint32_t\000"
.LASF53:
	.ascii	"HAL_RNG_Init\000"
.LASF57:
	.ascii	"HAL_GetTick\000"
.LASF23:
	.ascii	"HAL_RNG_STATE_READY\000"
.LASF45:
	.ascii	"HAL_RNG_GetRandomNumber\000"
.LASF40:
	.ascii	"HAL_RNG_ReadLastRandomNumber\000"
.LASF19:
	.ascii	"HAL_UNLOCKED\000"
.LASF13:
	.ascii	"long double\000"
.LASF9:
	.ascii	"__uint32_t\000"
.LASF21:
	.ascii	"HAL_LockTypeDef\000"
.LASF11:
	.ascii	"RNG_TypeDef\000"
.LASF16:
	.ascii	"HAL_BUSY\000"
.LASF50:
	.ascii	"HAL_RNG_MspDeInit\000"
.LASF8:
	.ascii	"unsigned int\000"
.LASF7:
	.ascii	"long long unsigned int\000"
.LASF43:
	.ascii	"itflag\000"
.LASF18:
	.ascii	"HAL_StatusTypeDef\000"
.LASF6:
	.ascii	"long long int\000"
.LASF34:
	.ascii	"HAL_RNG_GetError\000"
.LASF49:
	.ascii	"tickstart\000"
.LASF26:
	.ascii	"HAL_RNG_STATE_ERROR\000"
.LASF41:
	.ascii	"HAL_RNG_IRQHandler\000"
.LASF28:
	.ascii	"Instance\000"
.LASF2:
	.ascii	"short int\000"
.LASF15:
	.ascii	"HAL_ERROR\000"
.LASF33:
	.ascii	"RNG_HandleTypeDef\000"
.LASF25:
	.ascii	"HAL_RNG_STATE_TIMEOUT\000"
.LASF46:
	.ascii	"HAL_RNG_GenerateRandomNumber_IT\000"
.LASF4:
	.ascii	"long int\000"
.LASF17:
	.ascii	"HAL_TIMEOUT\000"
.LASF36:
	.ascii	"hrng\000"
.LASF54:
	.ascii	"GNU C17 12.3.1 20230626 -mcpu=cortex-m3 -mthumb -mf"
	.ascii	"loat-abi=soft -march=armv7-m -g -gdwarf-2 -Og -fdat"
	.ascii	"a-sections -ffunction-sections\000"
.LASF0:
	.ascii	"signed char\000"
.LASF55:
	.ascii	"../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_r"
	.ascii	"ng.c\000"
.LASF38:
	.ascii	"HAL_RNG_ReadyDataCallback\000"
.LASF39:
	.ascii	"random32bit\000"
.LASF22:
	.ascii	"HAL_RNG_STATE_RESET\000"
.LASF14:
	.ascii	"HAL_OK\000"
	.ident	"GCC: (GNU Tools for STM32 12.3.rel1.20240612-1315) 12.3.1 20230626"
