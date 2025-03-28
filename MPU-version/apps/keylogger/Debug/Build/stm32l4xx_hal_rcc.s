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
	.file	"stm32l4xx_hal_rcc.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 1 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_rcc.c"
	.section	.text.RCC_SetFlashLatencyFromMSIRange,"ax",%progbits
	.align	1
	.syntax unified
	.thumb
	.thumb_func
	.type	RCC_SetFlashLatencyFromMSIRange, %function
RCC_SetFlashLatencyFromMSIRange:
.LVL0:
.LFB88:
	.loc 1 1788 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 1788 1 is_stmt 0 view .LVU1
	push	{r4, r5, lr}
.LCFI0:
	.cfi_def_cfa_offset 12
	.cfi_offset 4, -12
	.cfi_offset 5, -8
	.cfi_offset 14, -4
	sub	sp, sp, #12
.LCFI1:
	.cfi_def_cfa_offset 24
	mov	r4, r0
	.loc 1 1789 3 is_stmt 1 view .LVU2
	.loc 1 1790 3 view .LVU3
.LVL1:
	.loc 1 1792 3 view .LVU4
	.loc 1 1792 6 is_stmt 0 view .LVU5
	ldr	r3, .L15
	ldr	r3, [r3, #88]
	.loc 1 1792 5 view .LVU6
	tst	r3, #268435456
	beq	.L2
	.loc 1 1794 5 is_stmt 1 view .LVU7
	.loc 1 1794 11 is_stmt 0 view .LVU8
	bl	HAL_PWREx_GetVoltageRange
.LVL2:
.L3:
	.loc 1 1803 3 is_stmt 1 view .LVU9
	.loc 1 1803 5 is_stmt 0 view .LVU10
	cmp	r0, #512
	beq	.L14
	.loc 1 1840 5 is_stmt 1 view .LVU11
	.loc 1 1840 7 is_stmt 0 view .LVU12
	cmp	r4, #128
	bhi	.L9
	.loc 1 1847 7 is_stmt 1 view .LVU13
	.loc 1 1847 9 is_stmt 0 view .LVU14
	beq	.L10
	.loc 1 1852 12 is_stmt 1 view .LVU15
	.loc 1 1852 14 is_stmt 0 view .LVU16
	cmp	r4, #112
	beq	.L11
	.loc 1 1790 12 view .LVU17
	movs	r1, #0
	b	.L5
.LVL3:
.L2:
	.loc 1 1798 5 is_stmt 1 view .LVU18
.LBB2:
	.loc 1 1798 5 view .LVU19
	.loc 1 1798 5 view .LVU20
	ldr	r5, .L15
	ldr	r3, [r5, #88]
	orr	r3, r3, #268435456
	str	r3, [r5, #88]
	.loc 1 1798 5 view .LVU21
	ldr	r3, [r5, #88]
	and	r3, r3, #268435456
	str	r3, [sp, #4]
	.loc 1 1798 5 view .LVU22
	ldr	r3, [sp, #4]
.LBE2:
	.loc 1 1798 5 view .LVU23
	.loc 1 1799 5 view .LVU24
	.loc 1 1799 11 is_stmt 0 view .LVU25
	bl	HAL_PWREx_GetVoltageRange
.LVL4:
	.loc 1 1800 5 is_stmt 1 view .LVU26
	ldr	r3, [r5, #88]
	bic	r3, r3, #268435456
	str	r3, [r5, #88]
	b	.L3
.L14:
	.loc 1 1805 5 view .LVU27
	.loc 1 1805 7 is_stmt 0 view .LVU28
	cmp	r4, #128
	bls	.L7
	.loc 1 1808 7 is_stmt 1 view .LVU29
	.loc 1 1808 9 is_stmt 0 view .LVU30
	cmp	r4, #160
	bls	.L8
	.loc 1 1811 17 view .LVU31
	movs	r1, #2
	b	.L5
.L7:
	.loc 1 1790 12 view .LVU32
	movs	r1, #0
	b	.L5
.L8:
	.loc 1 1816 17 view .LVU33
	movs	r1, #1
	b	.L5
.L9:
	.loc 1 1843 15 view .LVU34
	movs	r1, #3
.L5:
.LVL5:
	.loc 1 1861 7 is_stmt 1 view .LVU35
	.loc 1 1866 3 view .LVU36
	ldr	r2, .L15+4
	ldr	r3, [r2]
	bic	r3, r3, #7
	orrs	r3, r3, r1
	str	r3, [r2]
	.loc 1 1870 3 view .LVU37
	.loc 1 1870 6 is_stmt 0 view .LVU38
	ldr	r3, [r2]
	and	r3, r3, #7
	.loc 1 1870 5 view .LVU39
	cmp	r3, r1
	bne	.L12
	.loc 1 1875 10 view .LVU40
	movs	r0, #0
.LVL6:
.L6:
	.loc 1 1876 1 view .LVU41
	add	sp, sp, #12
.LCFI2:
	.cfi_remember_state
	.cfi_def_cfa_offset 12
	@ sp needed
	pop	{r4, r5, pc}
.LVL7:
.L10:
.LCFI3:
	.cfi_restore_state
	.loc 1 1850 17 view .LVU42
	movs	r1, #2
	b	.L5
.L11:
	.loc 1 1855 17 view .LVU43
	movs	r1, #1
	b	.L5
.LVL8:
.L12:
	.loc 1 1872 12 view .LVU44
	movs	r0, #1
.LVL9:
	.loc 1 1872 12 view .LVU45
	b	.L6
.L16:
	.align	2
.L15:
	.word	1073876992
	.word	1073881088
	.cfi_endproc
.LFE88:
	.size	RCC_SetFlashLatencyFromMSIRange, .-RCC_SetFlashLatencyFromMSIRange
	.section	.text.HAL_RCC_DeInit,"ax",%progbits
	.align	1
	.global	HAL_RCC_DeInit
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RCC_DeInit, %function
HAL_RCC_DeInit:
.LFB74:
	.loc 1 266 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, r4, r5, lr}
.LCFI4:
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	.cfi_offset 4, -12
	.cfi_offset 5, -8
	.cfi_offset 14, -4
	.loc 1 267 3 view .LVU47
	.loc 1 271 3 view .LVU48
	ldr	r2, .L34
	ldr	r3, [r2]
	orr	r3, r3, #1
	str	r3, [r2]
	.loc 1 275 3 view .LVU49
	.loc 1 275 15 is_stmt 0 view .LVU50
	bl	HAL_GetTick
.LVL10:
	mov	r4, r0
.LVL11:
	.loc 1 278 3 is_stmt 1 view .LVU51
.L18:
	.loc 1 278 42 view .LVU52
	.loc 1 278 9 is_stmt 0 view .LVU53
	ldr	r3, .L34
	ldr	r3, [r3]
	.loc 1 278 42 view .LVU54
	tst	r3, #2
	bne	.L30
	.loc 1 280 5 is_stmt 1 view .LVU55
	.loc 1 280 9 is_stmt 0 view .LVU56
	bl	HAL_GetTick
.LVL12:
	.loc 1 280 23 view .LVU57
	subs	r0, r0, r4
	.loc 1 280 7 view .LVU58
	cmp	r0, #2
	bls	.L18
	.loc 1 282 14 view .LVU59
	movs	r4, #3
.LVL13:
.L19:
	.loc 1 386 1 view .LVU60
	mov	r0, r4
	pop	{r3, r4, r5, pc}
.LVL14:
.L30:
	.loc 1 287 3 is_stmt 1 view .LVU61
	ldr	r2, .L34
	ldr	r3, [r2]
	bic	r3, r3, #240
	orr	r3, r3, #96
	str	r3, [r2]
	.loc 1 290 3 view .LVU62
	movs	r3, #0
	str	r3, [r2, #8]
	.loc 1 293 3 view .LVU63
	.loc 1 293 19 is_stmt 0 view .LVU64
	ldr	r3, .L34+4
	ldr	r2, .L34+8
	str	r2, [r3]
	.loc 1 296 3 is_stmt 1 view .LVU65
	.loc 1 296 6 is_stmt 0 view .LVU66
	ldr	r3, .L34+12
	ldr	r0, [r3]
	bl	HAL_InitTick
.LVL15:
	.loc 1 296 5 view .LVU67
	mov	r4, r0
.LVL16:
	.loc 1 296 5 view .LVU68
	cbz	r0, .L31
	.loc 1 298 12 view .LVU69
	movs	r4, #1
	b	.L19
.L31:
	.loc 1 303 3 is_stmt 1 view .LVU70
	.loc 1 303 15 is_stmt 0 view .LVU71
	bl	HAL_GetTick
.LVL17:
	mov	r5, r0
.LVL18:
	.loc 1 306 3 is_stmt 1 view .LVU72
.L21:
	.loc 1 306 43 view .LVU73
	.loc 1 306 9 is_stmt 0 view .LVU74
	ldr	r3, .L34
	ldr	r3, [r3, #8]
	.loc 1 306 43 view .LVU75
	tst	r3, #12
	beq	.L32
	.loc 1 308 5 is_stmt 1 view .LVU76
	.loc 1 308 9 is_stmt 0 view .LVU77
	bl	HAL_GetTick
.LVL19:
	.loc 1 308 23 view .LVU78
	subs	r0, r0, r5
	.loc 1 308 7 view .LVU79
	movw	r3, #5000
	cmp	r0, r3
	bls	.L21
	.loc 1 310 14 view .LVU80
	movs	r4, #3
	b	.L19
.L32:
	.loc 1 317 3 is_stmt 1 view .LVU81
	ldr	r2, .L34
	ldr	r1, [r2]
	ldr	r3, .L34+16
	ands	r3, r3, r1
	str	r3, [r2]
	.loc 1 331 3 view .LVU82
	.loc 1 331 15 is_stmt 0 view .LVU83
	bl	HAL_GetTick
.LVL20:
	mov	r5, r0
.LVL21:
	.loc 1 335 3 is_stmt 1 view .LVU84
.L23:
	.loc 1 335 82 view .LVU85
	.loc 1 335 9 is_stmt 0 view .LVU86
	ldr	r3, .L34
	ldr	r3, [r3]
	.loc 1 335 82 view .LVU87
	tst	r3, #704643072
	beq	.L33
	.loc 1 347 5 is_stmt 1 view .LVU88
	.loc 1 347 9 is_stmt 0 view .LVU89
	bl	HAL_GetTick
.LVL22:
	.loc 1 347 23 view .LVU90
	subs	r0, r0, r5
	.loc 1 347 7 view .LVU91
	cmp	r0, #2
	bls	.L23
	.loc 1 349 14 view .LVU92
	movs	r4, #3
	b	.L19
.L33:
	.loc 1 354 3 is_stmt 1 view .LVU93
	ldr	r3, .L34
	movs	r2, #0
	str	r2, [r3, #12]
	.loc 1 355 3 view .LVU94
	ldr	r1, [r3, #12]
	orr	r1, r1, #4096
	str	r1, [r3, #12]
	.loc 1 360 3 view .LVU95
	str	r2, [r3, #16]
	.loc 1 361 3 view .LVU96
	ldr	r1, [r3, #16]
	orr	r1, r1, #4096
	str	r1, [r3, #16]
	.loc 1 368 3 view .LVU97
	str	r2, [r3, #20]
	.loc 1 369 3 view .LVU98
	ldr	r1, [r3, #20]
	orr	r1, r1, #4096
	str	r1, [r3, #20]
	.loc 1 374 3 view .LVU99
	ldr	r1, [r3]
	bic	r1, r1, #262144
	str	r1, [r3]
	.loc 1 377 3 view .LVU100
	str	r2, [r3, #24]
	.loc 1 380 3 view .LVU101
	mov	r2, #-1
	str	r2, [r3, #32]
	.loc 1 383 3 view .LVU102
	ldr	r2, [r3, #148]
	orr	r2, r2, #8388608
	str	r2, [r3, #148]
	.loc 1 385 3 view .LVU103
	.loc 1 385 10 is_stmt 0 view .LVU104
	b	.L19
.L35:
	.align	2
.L34:
	.word	1073876992
	.word	SystemCoreClock
	.word	4000000
	.word	uwTickPrio
	.word	-352389889
	.cfi_endproc
.LFE74:
	.size	HAL_RCC_DeInit, .-HAL_RCC_DeInit
	.section	.text.HAL_RCC_MCOConfig,"ax",%progbits
	.align	1
	.global	HAL_RCC_MCOConfig
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RCC_MCOConfig, %function
HAL_RCC_MCOConfig:
.LVL23:
.LFB77:
	.loc 1 1340 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 1340 1 is_stmt 0 view .LVU106
	push	{r4, r5, r6, lr}
.LCFI5:
	.cfi_def_cfa_offset 16
	.cfi_offset 4, -16
	.cfi_offset 5, -12
	.cfi_offset 6, -8
	.cfi_offset 14, -4
	sub	sp, sp, #24
.LCFI6:
	.cfi_def_cfa_offset 40
	mov	r5, r1
	mov	r6, r2
	.loc 1 1341 3 is_stmt 1 view .LVU107
	.loc 1 1344 3 view .LVU108
	.loc 1 1345 3 view .LVU109
	.loc 1 1346 3 view .LVU110
	.loc 1 1349 3 view .LVU111
	.loc 1 1352 3 view .LVU112
.LBB3:
	.loc 1 1352 3 view .LVU113
	.loc 1 1352 3 view .LVU114
	ldr	r4, .L38
	ldr	r3, [r4, #76]
	orr	r3, r3, #1
	str	r3, [r4, #76]
	.loc 1 1352 3 view .LVU115
	ldr	r3, [r4, #76]
	and	r3, r3, #1
	str	r3, [sp]
	.loc 1 1352 3 view .LVU116
	ldr	r3, [sp]
.LBE3:
	.loc 1 1352 3 view .LVU117
	.loc 1 1355 3 view .LVU118
	.loc 1 1355 23 is_stmt 0 view .LVU119
	mov	r3, #256
	str	r3, [sp, #4]
	.loc 1 1356 3 is_stmt 1 view .LVU120
	.loc 1 1356 24 is_stmt 0 view .LVU121
	movs	r3, #2
	str	r3, [sp, #8]
	.loc 1 1357 3 is_stmt 1 view .LVU122
	.loc 1 1357 25 is_stmt 0 view .LVU123
	str	r3, [sp, #16]
	.loc 1 1358 3 is_stmt 1 view .LVU124
	.loc 1 1358 24 is_stmt 0 view .LVU125
	movs	r3, #0
	str	r3, [sp, #12]
	.loc 1 1359 3 is_stmt 1 view .LVU126
	.loc 1 1359 29 is_stmt 0 view .LVU127
	str	r3, [sp, #20]
	.loc 1 1360 3 is_stmt 1 view .LVU128
	add	r1, sp, #4
.LVL24:
	.loc 1 1360 3 is_stmt 0 view .LVU129
	mov	r0, #1207959552
.LVL25:
	.loc 1 1360 3 view .LVU130
	bl	HAL_GPIO_Init
.LVL26:
	.loc 1 1363 3 is_stmt 1 view .LVU131
	ldr	r3, [r4, #8]
	bic	r3, r3, #1996488704
	orrs	r5, r5, r6
.LVL27:
	.loc 1 1363 3 is_stmt 0 view .LVU132
	orrs	r3, r3, r5
	str	r3, [r4, #8]
	.loc 1 1364 1 view .LVU133
	add	sp, sp, #24
.LCFI7:
	.cfi_def_cfa_offset 16
	@ sp needed
	pop	{r4, r5, r6, pc}
.LVL28:
.L39:
	.loc 1 1364 1 view .LVU134
	.align	2
.L38:
	.word	1073876992
	.cfi_endproc
.LFE77:
	.size	HAL_RCC_MCOConfig, .-HAL_RCC_MCOConfig
	.section	.text.HAL_RCC_GetSysClockFreq,"ax",%progbits
	.align	1
	.global	HAL_RCC_GetSysClockFreq
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RCC_GetSysClockFreq, %function
HAL_RCC_GetSysClockFreq:
.LFB78:
	.loc 1 1399 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1400 3 view .LVU136
.LVL29:
	.loc 1 1401 3 view .LVU137
	.loc 1 1402 3 view .LVU138
	.loc 1 1404 3 view .LVU139
	.loc 1 1404 19 is_stmt 0 view .LVU140
	ldr	r2, .L54
	ldr	r3, [r2, #8]
.LVL30:
	.loc 1 1405 3 is_stmt 1 view .LVU141
	.loc 1 1405 19 is_stmt 0 view .LVU142
	ldr	r2, [r2, #12]
	.loc 1 1405 17 view .LVU143
	and	r2, r2, #3
.LVL31:
	.loc 1 1407 3 is_stmt 1 view .LVU144
	.loc 1 1407 5 is_stmt 0 view .LVU145
	ands	r3, r3, #12
.LVL32:
	.loc 1 1407 5 view .LVU146
	beq	.L41
	.loc 1 1407 42 discriminator 1 view .LVU147
	cmp	r3, #12
	beq	.L52
.L42:
	.loc 1 1430 8 is_stmt 1 view .LVU148
	.loc 1 1430 10 is_stmt 0 view .LVU149
	cmp	r3, #4
	beq	.L49
	.loc 1 1435 8 is_stmt 1 view .LVU150
	.loc 1 1435 10 is_stmt 0 view .LVU151
	cmp	r3, #8
	beq	.L50
	.loc 1 1400 27 view .LVU152
	movs	r0, #0
	.loc 1 1400 12 view .LVU153
	mov	r2, r0
.LVL33:
	.loc 1 1400 12 view .LVU154
	b	.L45
.LVL34:
.L52:
	.loc 1 1408 43 view .LVU155
	cmp	r2, #1
	bne	.L42
.L41:
	.loc 1 1413 5 is_stmt 1 view .LVU156
	.loc 1 1413 8 is_stmt 0 view .LVU157
	ldr	r2, .L54
.LVL35:
	.loc 1 1413 8 view .LVU158
	ldr	r2, [r2]
	.loc 1 1413 7 view .LVU159
	tst	r2, #8
	bne	.L43
	.loc 1 1415 7 is_stmt 1 view .LVU160
	.loc 1 1415 18 is_stmt 0 view .LVU161
	ldr	r2, .L54
	ldr	r2, [r2, #148]
	.loc 1 1415 16 view .LVU162
	ubfx	r2, r2, #8, #4
.LVL36:
.L44:
	.loc 1 1422 5 is_stmt 1 view .LVU163
	.loc 1 1422 14 is_stmt 0 view .LVU164
	ldr	r1, .L54+4
	ldr	r2, [r1, r2, lsl #2]
.LVL37:
	.loc 1 1424 5 is_stmt 1 view .LVU165
	.loc 1 1424 7 is_stmt 0 view .LVU166
	cbz	r3, .L48
	.loc 1 1400 27 view .LVU167
	movs	r0, #0
.LVL38:
.L45:
	.loc 1 1443 3 is_stmt 1 view .LVU168
	.loc 1 1445 3 view .LVU169
	.loc 1 1445 5 is_stmt 0 view .LVU170
	cmp	r3, #12
	beq	.L53
.LVL39:
.L40:
	.loc 1 1476 1 view .LVU171
	bx	lr
.LVL40:
.L43:
	.loc 1 1419 7 is_stmt 1 view .LVU172
	.loc 1 1419 18 is_stmt 0 view .LVU173
	ldr	r2, .L54
	ldr	r2, [r2]
	.loc 1 1419 16 view .LVU174
	ubfx	r2, r2, #4, #4
.LVL41:
	.loc 1 1419 16 view .LVU175
	b	.L44
.L48:
	.loc 1 1427 20 view .LVU176
	mov	r0, r2
	b	.L45
.LVL42:
.L49:
	.loc 1 1433 18 view .LVU177
	ldr	r0, .L54+8
	.loc 1 1400 12 view .LVU178
	movs	r2, #0
.LVL43:
	.loc 1 1400 12 view .LVU179
	b	.L45
.LVL44:
.L50:
	.loc 1 1438 18 view .LVU180
	ldr	r0, .L54+12
	.loc 1 1400 12 view .LVU181
	movs	r2, #0
.LVL45:
	.loc 1 1400 12 view .LVU182
	b	.L45
.LVL46:
.L53:
	.loc 1 1452 5 is_stmt 1 view .LVU183
	.loc 1 1452 17 is_stmt 0 view .LVU184
	ldr	r3, .L54
.LVL47:
	.loc 1 1452 17 view .LVU185
	ldr	r3, [r3, #12]
	.loc 1 1452 15 view .LVU186
	and	r3, r3, #3
.LVL48:
	.loc 1 1454 5 is_stmt 1 view .LVU187
	cmp	r3, #2
	beq	.L51
	cmp	r3, #3
	bne	.L47
	.loc 1 1461 14 is_stmt 0 view .LVU188
	ldr	r2, .L54+12
.LVL49:
.L47:
	.loc 1 1469 5 is_stmt 1 view .LVU189
	.loc 1 1469 13 is_stmt 0 view .LVU190
	ldr	r1, .L54
	ldr	r3, [r1, #12]
.LVL50:
	.loc 1 1469 54 view .LVU191
	ubfx	r3, r3, #4, #3
	.loc 1 1469 10 view .LVU192
	adds	r3, r3, #1
.LVL51:
	.loc 1 1470 5 is_stmt 1 view .LVU193
	.loc 1 1470 25 is_stmt 0 view .LVU194
	ldr	r0, [r1, #12]
.LVL52:
	.loc 1 1470 66 view .LVU195
	ubfx	r0, r0, #8, #7
	.loc 1 1470 22 view .LVU196
	mul	r0, r2, r0
	.loc 1 1470 12 view .LVU197
	udiv	r0, r0, r3
.LVL53:
	.loc 1 1471 5 is_stmt 1 view .LVU198
	.loc 1 1471 14 is_stmt 0 view .LVU199
	ldr	r3, [r1, #12]
.LVL54:
	.loc 1 1471 55 view .LVU200
	ubfx	r3, r3, #25, #2
	.loc 1 1471 80 view .LVU201
	adds	r3, r3, #1
	.loc 1 1471 10 view .LVU202
	lsls	r3, r3, #1
.LVL55:
	.loc 1 1472 5 is_stmt 1 view .LVU203
	.loc 1 1472 18 is_stmt 0 view .LVU204
	udiv	r0, r0, r3
.LVL56:
	.loc 1 1475 3 is_stmt 1 view .LVU205
	.loc 1 1475 10 is_stmt 0 view .LVU206
	b	.L40
.LVL57:
.L51:
	.loc 1 1454 5 view .LVU207
	ldr	r2, .L54+8
.LVL58:
	.loc 1 1454 5 view .LVU208
	b	.L47
.L55:
	.align	2
.L54:
	.word	1073876992
	.word	MSIRangeTable
	.word	16000000
	.word	8000000
	.cfi_endproc
.LFE78:
	.size	HAL_RCC_GetSysClockFreq, .-HAL_RCC_GetSysClockFreq
	.section	.text.HAL_RCC_OscConfig,"ax",%progbits
	.align	1
	.global	HAL_RCC_OscConfig
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RCC_OscConfig, %function
HAL_RCC_OscConfig:
.LVL59:
.LFB75:
	.loc 1 406 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 407 3 view .LVU210
	.loc 1 408 3 view .LVU211
	.loc 1 409 3 view .LVU212
	.loc 1 412 3 view .LVU213
	.loc 1 412 5 is_stmt 0 view .LVU214
	cmp	r0, #0
	beq	.L122
	.loc 1 406 1 view .LVU215
	push	{r4, r5, r6, r7, lr}
.LCFI8:
	.cfi_def_cfa_offset 20
	.cfi_offset 4, -20
	.cfi_offset 5, -16
	.cfi_offset 6, -12
	.cfi_offset 7, -8
	.cfi_offset 14, -4
	sub	sp, sp, #12
.LCFI9:
	.cfi_def_cfa_offset 32
	mov	r4, r0
	.loc 1 418 3 is_stmt 1 view .LVU216
	.loc 1 420 3 view .LVU217
	.loc 1 420 19 is_stmt 0 view .LVU218
	ldr	r3, .L176
	ldr	r5, [r3, #8]
	.loc 1 420 17 view .LVU219
	and	r5, r5, #12
.LVL60:
	.loc 1 421 3 is_stmt 1 view .LVU220
	.loc 1 421 16 is_stmt 0 view .LVU221
	ldr	r6, [r3, #12]
	.loc 1 421 14 view .LVU222
	and	r6, r6, #3
.LVL61:
	.loc 1 424 3 is_stmt 1 view .LVU223
	.loc 1 424 25 is_stmt 0 view .LVU224
	ldr	r3, [r0]
	.loc 1 424 5 view .LVU225
	tst	r3, #16
	beq	.L58
	.loc 1 427 5 is_stmt 1 view .LVU226
	.loc 1 428 5 view .LVU227
	.loc 1 429 5 view .LVU228
	.loc 1 432 5 view .LVU229
	.loc 1 432 7 is_stmt 0 view .LVU230
	cbz	r5, .L59
	.loc 1 432 44 discriminator 1 view .LVU231
	cmp	r5, #12
	beq	.L154
.L60:
	.loc 1 492 7 is_stmt 1 view .LVU232
	.loc 1 492 27 is_stmt 0 view .LVU233
	ldr	r3, [r4, #24]
	.loc 1 492 9 view .LVU234
	cmp	r3, #0
	beq	.L66
	.loc 1 495 9 is_stmt 1 view .LVU235
	ldr	r2, .L176
	ldr	r3, [r2]
	orr	r3, r3, #1
	str	r3, [r2]
	.loc 1 498 9 view .LVU236
	.loc 1 498 21 is_stmt 0 view .LVU237
	bl	HAL_GetTick
.LVL62:
	.loc 1 498 21 view .LVU238
	mov	r7, r0
.LVL63:
	.loc 1 501 9 is_stmt 1 view .LVU239
.L67:
	.loc 1 501 48 view .LVU240
	.loc 1 501 15 is_stmt 0 view .LVU241
	ldr	r3, .L176
	ldr	r3, [r3]
	.loc 1 501 48 view .LVU242
	tst	r3, #2
	bne	.L155
	.loc 1 503 11 is_stmt 1 view .LVU243
	.loc 1 503 15 is_stmt 0 view .LVU244
	bl	HAL_GetTick
.LVL64:
	.loc 1 503 29 view .LVU245
	subs	r0, r0, r7
	.loc 1 503 13 view .LVU246
	cmp	r0, #2
	bls	.L67
	.loc 1 505 20 view .LVU247
	movs	r0, #3
	b	.L57
.LVL65:
.L154:
	.loc 1 433 45 view .LVU248
	cmp	r6, #1
	bne	.L60
.L59:
	.loc 1 435 7 is_stmt 1 view .LVU249
	.loc 1 435 11 is_stmt 0 view .LVU250
	ldr	r3, .L176
	ldr	r3, [r3]
	.loc 1 435 9 view .LVU251
	tst	r3, #2
	beq	.L61
	.loc 1 435 72 discriminator 1 view .LVU252
	ldr	r3, [r4, #24]
	.loc 1 435 51 discriminator 1 view .LVU253
	cmp	r3, #0
	beq	.L123
.L61:
	.loc 1 446 9 is_stmt 1 view .LVU254
	.loc 1 446 29 is_stmt 0 view .LVU255
	ldr	r0, [r4, #32]
.LVL66:
	.loc 1 446 47 view .LVU256
	ldr	r3, .L176
	ldr	r3, [r3]
	tst	r3, #8
	beq	.L62
	.loc 1 446 47 discriminator 1 view .LVU257
	ldr	r3, .L176
	ldr	r3, [r3]
	and	r3, r3, #240
.L63:
	.loc 1 446 11 discriminator 4 view .LVU258
	cmp	r0, r3
	bhi	.L156
	.loc 1 463 11 is_stmt 1 view .LVU259
	.loc 1 463 11 view .LVU260
	ldr	r3, .L176
	ldr	r2, [r3]
	orr	r2, r2, #8
	str	r2, [r3]
	.loc 1 463 11 view .LVU261
	ldr	r2, [r3]
	bic	r2, r2, #240
	ldr	r1, [r4, #32]
	orrs	r2, r2, r1
	str	r2, [r3]
	.loc 1 463 11 view .LVU262
	.loc 1 465 11 view .LVU263
	ldr	r2, [r3, #4]
	bic	r2, r2, #65280
	ldr	r1, [r4, #28]
	orr	r2, r2, r1, lsl #8
	str	r2, [r3, #4]
	.loc 1 469 11 view .LVU264
	.loc 1 469 13 is_stmt 0 view .LVU265
	cmp	r5, #0
	beq	.L157
.L65:
	.loc 1 479 9 is_stmt 1 view .LVU266
	.loc 1 479 27 is_stmt 0 view .LVU267
	bl	HAL_RCC_GetSysClockFreq
.LVL67:
	.loc 1 479 71 view .LVU268
	ldr	r3, .L176
	ldr	r3, [r3, #8]
	.loc 1 479 106 view .LVU269
	ubfx	r3, r3, #4, #4
	.loc 1 479 70 view .LVU270
	ldr	r2, .L176+4
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	.loc 1 479 128 view .LVU271
	and	r3, r3, #31
	.loc 1 479 53 view .LVU272
	lsrs	r0, r0, r3
	.loc 1 479 25 view .LVU273
	ldr	r3, .L176+8
	str	r0, [r3]
	.loc 1 482 9 is_stmt 1 view .LVU274
	.loc 1 482 18 is_stmt 0 view .LVU275
	ldr	r3, .L176+12
	ldr	r0, [r3]
	bl	HAL_InitTick
.LVL68:
	.loc 1 483 9 is_stmt 1 view .LVU276
	.loc 1 483 11 is_stmt 0 view .LVU277
	cmp	r0, #0
	bne	.L57
.LVL69:
.L58:
	.loc 1 534 3 is_stmt 1 view .LVU278
	.loc 1 534 25 is_stmt 0 view .LVU279
	ldr	r3, [r4]
	.loc 1 534 5 view .LVU280
	tst	r3, #1
	beq	.L71
	.loc 1 537 5 is_stmt 1 view .LVU281
	.loc 1 540 5 view .LVU282
	.loc 1 540 7 is_stmt 0 view .LVU283
	cmp	r5, #8
	beq	.L72
	.loc 1 540 44 discriminator 1 view .LVU284
	cmp	r5, #12
	beq	.L158
.L73:
	.loc 1 551 7 is_stmt 1 view .LVU285
	.loc 1 551 7 view .LVU286
	ldr	r3, [r4, #4]
	cmp	r3, #65536
	beq	.L159
	.loc 1 551 7 discriminator 2 view .LVU287
	cmp	r3, #327680
	beq	.L160
	.loc 1 551 7 discriminator 5 view .LVU288
	ldr	r3, .L176
	ldr	r2, [r3]
	bic	r2, r2, #65536
	str	r2, [r3]
	.loc 1 551 7 discriminator 5 view .LVU289
	ldr	r2, [r3]
	bic	r2, r2, #262144
	str	r2, [r3]
.L75:
	.loc 1 551 7 discriminator 7 view .LVU290
	.loc 1 554 7 discriminator 7 view .LVU291
	.loc 1 554 27 is_stmt 0 discriminator 7 view .LVU292
	ldr	r3, [r4, #4]
	.loc 1 554 9 discriminator 7 view .LVU293
	cmp	r3, #0
	beq	.L77
	.loc 1 557 9 is_stmt 1 view .LVU294
	.loc 1 557 21 is_stmt 0 view .LVU295
	bl	HAL_GetTick
.LVL70:
	mov	r7, r0
.LVL71:
	.loc 1 560 9 is_stmt 1 view .LVU296
.L78:
	.loc 1 560 48 view .LVU297
	.loc 1 560 15 is_stmt 0 view .LVU298
	ldr	r3, .L176
	ldr	r3, [r3]
	.loc 1 560 48 view .LVU299
	tst	r3, #131072
	bne	.L71
	.loc 1 562 11 is_stmt 1 view .LVU300
	.loc 1 562 15 is_stmt 0 view .LVU301
	bl	HAL_GetTick
.LVL72:
	.loc 1 562 29 view .LVU302
	subs	r0, r0, r7
	.loc 1 562 13 view .LVU303
	cmp	r0, #100
	bls	.L78
	.loc 1 564 20 view .LVU304
	movs	r0, #3
	b	.L57
.LVL73:
.L62:
	.loc 1 446 47 discriminator 2 view .LVU305
	ldr	r3, .L176
	ldr	r3, [r3, #148]
	lsrs	r3, r3, #4
	and	r3, r3, #240
	b	.L63
.L156:
	.loc 1 449 11 is_stmt 1 view .LVU306
	.loc 1 449 14 is_stmt 0 view .LVU307
	bl	RCC_SetFlashLatencyFromMSIRange
.LVL74:
	.loc 1 449 13 view .LVU308
	cmp	r0, #0
	bne	.L124
	.loc 1 455 11 is_stmt 1 view .LVU309
	.loc 1 455 11 view .LVU310
	ldr	r3, .L176
	ldr	r2, [r3]
	orr	r2, r2, #8
	str	r2, [r3]
	.loc 1 455 11 view .LVU311
	ldr	r2, [r3]
	bic	r2, r2, #240
	ldr	r1, [r4, #32]
	orrs	r2, r2, r1
	str	r2, [r3]
	.loc 1 455 11 view .LVU312
	.loc 1 457 11 view .LVU313
	ldr	r2, [r3, #4]
	bic	r2, r2, #65280
	ldr	r1, [r4, #28]
	orr	r2, r2, r1, lsl #8
	str	r2, [r3, #4]
	b	.L65
.L157:
	.loc 1 471 13 view .LVU314
	.loc 1 471 16 is_stmt 0 view .LVU315
	ldr	r0, [r4, #32]
	bl	RCC_SetFlashLatencyFromMSIRange
.LVL75:
	.loc 1 471 15 view .LVU316
	cmp	r0, #0
	beq	.L65
	.loc 1 473 22 view .LVU317
	movs	r0, #1
	b	.L57
.LVL76:
.L155:
	.loc 1 509 9 is_stmt 1 view .LVU318
	.loc 1 509 9 view .LVU319
	ldr	r3, .L176
	ldr	r2, [r3]
	orr	r2, r2, #8
	str	r2, [r3]
	.loc 1 509 9 view .LVU320
	ldr	r2, [r3]
	bic	r2, r2, #240
	ldr	r1, [r4, #32]
	orrs	r2, r2, r1
	str	r2, [r3]
	.loc 1 509 9 view .LVU321
	.loc 1 511 9 view .LVU322
	ldr	r2, [r3, #4]
	bic	r2, r2, #65280
	ldr	r1, [r4, #28]
	orr	r2, r2, r1, lsl #8
	str	r2, [r3, #4]
	b	.L58
.LVL77:
.L66:
	.loc 1 517 9 view .LVU323
	ldr	r2, .L176
	ldr	r3, [r2]
	bic	r3, r3, #1
	str	r3, [r2]
	.loc 1 520 9 view .LVU324
	.loc 1 520 21 is_stmt 0 view .LVU325
	bl	HAL_GetTick
.LVL78:
	.loc 1 520 21 view .LVU326
	mov	r7, r0
.LVL79:
	.loc 1 523 9 is_stmt 1 view .LVU327
.L69:
	.loc 1 523 48 view .LVU328
	.loc 1 523 15 is_stmt 0 view .LVU329
	ldr	r3, .L176
	ldr	r3, [r3]
	.loc 1 523 48 view .LVU330
	tst	r3, #2
	beq	.L58
	.loc 1 525 11 is_stmt 1 view .LVU331
	.loc 1 525 15 is_stmt 0 view .LVU332
	bl	HAL_GetTick
.LVL80:
	.loc 1 525 29 view .LVU333
	subs	r0, r0, r7
	.loc 1 525 13 view .LVU334
	cmp	r0, #2
	bls	.L69
	.loc 1 527 20 view .LVU335
	movs	r0, #3
	b	.L57
.LVL81:
.L158:
	.loc 1 541 45 view .LVU336
	cmp	r6, #3
	bne	.L73
.L72:
	.loc 1 543 7 is_stmt 1 view .LVU337
	.loc 1 543 11 is_stmt 0 view .LVU338
	ldr	r3, .L176
	ldr	r3, [r3]
	.loc 1 543 9 view .LVU339
	tst	r3, #131072
	beq	.L71
	.loc 1 543 72 discriminator 1 view .LVU340
	ldr	r3, [r4, #4]
	.loc 1 543 51 discriminator 1 view .LVU341
	cmp	r3, #0
	beq	.L161
.L71:
	.loc 1 585 3 is_stmt 1 view .LVU342
	.loc 1 585 25 is_stmt 0 view .LVU343
	ldr	r3, [r4]
	.loc 1 585 5 view .LVU344
	tst	r3, #2
	beq	.L82
	.loc 1 588 5 is_stmt 1 view .LVU345
	.loc 1 589 5 view .LVU346
	.loc 1 592 5 view .LVU347
	.loc 1 592 7 is_stmt 0 view .LVU348
	cmp	r5, #4
	beq	.L83
	.loc 1 592 44 discriminator 1 view .LVU349
	cmp	r5, #12
	beq	.L162
.L84:
	.loc 1 610 7 is_stmt 1 view .LVU350
	.loc 1 610 27 is_stmt 0 view .LVU351
	ldr	r3, [r4, #12]
	.loc 1 610 9 view .LVU352
	cmp	r3, #0
	beq	.L86
	.loc 1 613 9 is_stmt 1 view .LVU353
	ldr	r2, .L176
	ldr	r3, [r2]
	orr	r3, r3, #256
	str	r3, [r2]
	.loc 1 616 9 view .LVU354
	.loc 1 616 21 is_stmt 0 view .LVU355
	bl	HAL_GetTick
.LVL82:
	mov	r6, r0
.LVL83:
	.loc 1 619 9 is_stmt 1 view .LVU356
.L87:
	.loc 1 619 48 view .LVU357
	.loc 1 619 15 is_stmt 0 view .LVU358
	ldr	r3, .L176
	ldr	r3, [r3]
	.loc 1 619 48 view .LVU359
	tst	r3, #1024
	bne	.L163
	.loc 1 621 11 is_stmt 1 view .LVU360
	.loc 1 621 15 is_stmt 0 view .LVU361
	bl	HAL_GetTick
.LVL84:
	.loc 1 621 29 view .LVU362
	subs	r0, r0, r6
	.loc 1 621 13 view .LVU363
	cmp	r0, #2
	bls	.L87
	.loc 1 623 20 view .LVU364
	movs	r0, #3
	b	.L57
.LVL85:
.L159:
	.loc 1 551 7 is_stmt 1 discriminator 1 view .LVU365
	ldr	r2, .L176
	ldr	r3, [r2]
	orr	r3, r3, #65536
	str	r3, [r2]
	b	.L75
.L160:
	.loc 1 551 7 discriminator 4 view .LVU366
	add	r3, r3, #1073741824
	sub	r3, r3, #192512
	ldr	r2, [r3]
	orr	r2, r2, #262144
	str	r2, [r3]
	.loc 1 551 7 discriminator 4 view .LVU367
	ldr	r2, [r3]
	orr	r2, r2, #65536
	str	r2, [r3]
	b	.L75
.L77:
	.loc 1 571 9 view .LVU368
	.loc 1 571 21 is_stmt 0 view .LVU369
	bl	HAL_GetTick
.LVL86:
	mov	r7, r0
.LVL87:
	.loc 1 574 9 is_stmt 1 view .LVU370
.L80:
	.loc 1 574 48 view .LVU371
	.loc 1 574 15 is_stmt 0 view .LVU372
	ldr	r3, .L176
	ldr	r3, [r3]
	.loc 1 574 48 view .LVU373
	tst	r3, #131072
	beq	.L71
	.loc 1 576 11 is_stmt 1 view .LVU374
	.loc 1 576 15 is_stmt 0 view .LVU375
	bl	HAL_GetTick
.LVL88:
	.loc 1 576 29 view .LVU376
	subs	r0, r0, r7
	.loc 1 576 13 view .LVU377
	cmp	r0, #100
	bls	.L80
	.loc 1 578 20 view .LVU378
	movs	r0, #3
	b	.L57
.L177:
	.align	2
.L176:
	.word	1073876992
	.word	AHBPrescTable
	.word	SystemCoreClock
	.word	uwTickPrio
.LVL89:
.L162:
	.loc 1 593 45 view .LVU379
	cmp	r6, #2
	bne	.L84
.L83:
	.loc 1 596 7 is_stmt 1 view .LVU380
	.loc 1 596 11 is_stmt 0 view .LVU381
	ldr	r3, .L178
	ldr	r3, [r3]
	.loc 1 596 9 view .LVU382
	tst	r3, #1024
	beq	.L85
	.loc 1 596 72 discriminator 1 view .LVU383
	ldr	r3, [r4, #12]
	.loc 1 596 51 discriminator 1 view .LVU384
	cmp	r3, #0
	beq	.L131
.L85:
	.loc 1 604 9 is_stmt 1 view .LVU385
	ldr	r2, .L178
	ldr	r3, [r2, #4]
	bic	r3, r3, #520093696
	ldr	r1, [r4, #16]
	orr	r3, r3, r1, lsl #24
	str	r3, [r2, #4]
.LVL90:
.L82:
	.loc 1 650 3 view .LVU386
	.loc 1 650 25 is_stmt 0 view .LVU387
	ldr	r3, [r4]
	.loc 1 650 5 view .LVU388
	tst	r3, #8
	beq	.L91
	.loc 1 653 5 is_stmt 1 view .LVU389
	.loc 1 656 5 view .LVU390
	.loc 1 656 25 is_stmt 0 view .LVU391
	ldr	r3, [r4, #20]
	.loc 1 656 7 view .LVU392
	cbz	r3, .L92
	.loc 1 698 7 is_stmt 1 view .LVU393
	ldr	r2, .L178
	ldr	r3, [r2, #148]
	orr	r3, r3, #1
	str	r3, [r2, #148]
	.loc 1 701 7 view .LVU394
	.loc 1 701 19 is_stmt 0 view .LVU395
	bl	HAL_GetTick
.LVL91:
	mov	r6, r0
.LVL92:
	.loc 1 704 7 is_stmt 1 view .LVU396
.L93:
	.loc 1 704 48 view .LVU397
	.loc 1 704 13 is_stmt 0 view .LVU398
	ldr	r3, .L178
	ldr	r3, [r3, #148]
	.loc 1 704 48 view .LVU399
	tst	r3, #2
	bne	.L91
	.loc 1 706 9 is_stmt 1 view .LVU400
	.loc 1 706 13 is_stmt 0 view .LVU401
	bl	HAL_GetTick
.LVL93:
	.loc 1 706 27 view .LVU402
	subs	r0, r0, r6
	.loc 1 706 11 view .LVU403
	cmp	r0, #2
	bls	.L93
	.loc 1 708 18 view .LVU404
	movs	r0, #3
	b	.L57
.L163:
	.loc 1 628 9 is_stmt 1 view .LVU405
	ldr	r2, .L178
	ldr	r3, [r2, #4]
	bic	r3, r3, #520093696
	ldr	r1, [r4, #16]
	orr	r3, r3, r1, lsl #24
	str	r3, [r2, #4]
	b	.L82
.LVL94:
.L86:
	.loc 1 633 9 view .LVU406
	ldr	r2, .L178
	ldr	r3, [r2]
	bic	r3, r3, #256
	str	r3, [r2]
	.loc 1 636 9 view .LVU407
	.loc 1 636 21 is_stmt 0 view .LVU408
	bl	HAL_GetTick
.LVL95:
	mov	r6, r0
.LVL96:
	.loc 1 639 9 is_stmt 1 view .LVU409
.L89:
	.loc 1 639 48 view .LVU410
	.loc 1 639 15 is_stmt 0 view .LVU411
	ldr	r3, .L178
	ldr	r3, [r3]
	.loc 1 639 48 view .LVU412
	tst	r3, #1024
	beq	.L82
	.loc 1 641 11 is_stmt 1 view .LVU413
	.loc 1 641 15 is_stmt 0 view .LVU414
	bl	HAL_GetTick
.LVL97:
	.loc 1 641 29 view .LVU415
	subs	r0, r0, r6
	.loc 1 641 13 view .LVU416
	cmp	r0, #2
	bls	.L89
	.loc 1 643 20 view .LVU417
	movs	r0, #3
	b	.L57
.LVL98:
.L92:
	.loc 1 715 7 is_stmt 1 view .LVU418
	ldr	r2, .L178
	ldr	r3, [r2, #148]
	bic	r3, r3, #1
	str	r3, [r2, #148]
	.loc 1 718 7 view .LVU419
	.loc 1 718 19 is_stmt 0 view .LVU420
	bl	HAL_GetTick
.LVL99:
	mov	r6, r0
.LVL100:
	.loc 1 721 7 is_stmt 1 view .LVU421
.L95:
	.loc 1 721 48 view .LVU422
	.loc 1 721 13 is_stmt 0 view .LVU423
	ldr	r3, .L178
	ldr	r3, [r3, #148]
	.loc 1 721 48 view .LVU424
	tst	r3, #2
	beq	.L91
	.loc 1 723 9 is_stmt 1 view .LVU425
	.loc 1 723 13 is_stmt 0 view .LVU426
	bl	HAL_GetTick
.LVL101:
	.loc 1 723 27 view .LVU427
	subs	r0, r0, r6
	.loc 1 723 11 view .LVU428
	cmp	r0, #2
	bls	.L95
	.loc 1 725 18 view .LVU429
	movs	r0, #3
	b	.L57
.LVL102:
.L91:
	.loc 1 731 3 is_stmt 1 view .LVU430
	.loc 1 731 25 is_stmt 0 view .LVU431
	ldr	r3, [r4]
	.loc 1 731 5 view .LVU432
	tst	r3, #4
	beq	.L97
.LBB4:
	.loc 1 733 5 is_stmt 1 view .LVU433
.LVL103:
	.loc 1 736 5 view .LVU434
	.loc 1 740 5 view .LVU435
	.loc 1 740 8 is_stmt 0 view .LVU436
	ldr	r3, .L178
	ldr	r3, [r3, #88]
	.loc 1 740 7 view .LVU437
	tst	r3, #268435456
	bne	.L136
	.loc 1 742 7 is_stmt 1 view .LVU438
.LBB5:
	.loc 1 742 7 view .LVU439
	.loc 1 742 7 view .LVU440
	ldr	r3, .L178
	ldr	r2, [r3, #88]
	orr	r2, r2, #268435456
	str	r2, [r3, #88]
	.loc 1 742 7 view .LVU441
	ldr	r3, [r3, #88]
	and	r3, r3, #268435456
	str	r3, [sp, #4]
	.loc 1 742 7 view .LVU442
	ldr	r3, [sp, #4]
.LBE5:
	.loc 1 742 7 view .LVU443
	.loc 1 743 7 view .LVU444
.LVL104:
	.loc 1 743 21 is_stmt 0 view .LVU445
	movs	r6, #1
.LVL105:
.L98:
	.loc 1 746 5 is_stmt 1 view .LVU446
	.loc 1 746 8 is_stmt 0 view .LVU447
	ldr	r3, .L178+4
	ldr	r3, [r3]
	.loc 1 746 7 view .LVU448
	tst	r3, #256
	beq	.L164
.L99:
	.loc 1 788 5 is_stmt 1 view .LVU449
	.loc 1 788 5 view .LVU450
	ldr	r3, [r4, #8]
	cmp	r3, #1
	beq	.L165
	.loc 1 788 5 discriminator 2 view .LVU451
	cmp	r3, #5
	beq	.L166
	.loc 1 788 5 discriminator 5 view .LVU452
	ldr	r3, .L178
	ldr	r2, [r3, #144]
	bic	r2, r2, #1
	str	r2, [r3, #144]
	.loc 1 788 5 discriminator 5 view .LVU453
	ldr	r2, [r3, #144]
	bic	r2, r2, #4
	str	r2, [r3, #144]
.L103:
	.loc 1 788 5 discriminator 7 view .LVU454
	.loc 1 792 5 discriminator 7 view .LVU455
	.loc 1 792 25 is_stmt 0 discriminator 7 view .LVU456
	ldr	r3, [r4, #8]
	.loc 1 792 7 discriminator 7 view .LVU457
	cmp	r3, #0
	beq	.L105
	.loc 1 795 7 is_stmt 1 view .LVU458
	.loc 1 795 19 is_stmt 0 view .LVU459
	bl	HAL_GetTick
.LVL106:
	mov	r7, r0
.LVL107:
	.loc 1 798 7 is_stmt 1 view .LVU460
.L106:
	.loc 1 798 50 view .LVU461
	.loc 1 798 13 is_stmt 0 view .LVU462
	ldr	r3, .L178
	ldr	r3, [r3, #144]
	.loc 1 798 50 view .LVU463
	tst	r3, #2
	bne	.L108
	.loc 1 800 9 is_stmt 1 view .LVU464
	.loc 1 800 13 is_stmt 0 view .LVU465
	bl	HAL_GetTick
.LVL108:
	.loc 1 800 27 view .LVU466
	subs	r0, r0, r7
	.loc 1 800 11 view .LVU467
	movw	r3, #5000
	cmp	r0, r3
	bls	.L106
	.loc 1 802 18 view .LVU468
	movs	r0, #3
	b	.L57
.LVL109:
.L136:
	.loc 1 733 22 view .LVU469
	movs	r6, #0
	b	.L98
.LVL110:
.L164:
	.loc 1 749 7 is_stmt 1 view .LVU470
	ldr	r2, .L178+4
	ldr	r3, [r2]
	orr	r3, r3, #256
	str	r3, [r2]
	.loc 1 752 7 view .LVU471
	.loc 1 752 19 is_stmt 0 view .LVU472
	bl	HAL_GetTick
.LVL111:
	mov	r7, r0
.LVL112:
	.loc 1 754 7 is_stmt 1 view .LVU473
.L100:
	.loc 1 754 13 view .LVU474
	ldr	r3, .L178+4
	ldr	r3, [r3]
	tst	r3, #256
	bne	.L99
	.loc 1 756 9 view .LVU475
	.loc 1 756 13 is_stmt 0 view .LVU476
	bl	HAL_GetTick
.LVL113:
	.loc 1 756 27 view .LVU477
	subs	r0, r0, r7
	.loc 1 756 11 view .LVU478
	cmp	r0, #2
	bls	.L100
	.loc 1 758 18 view .LVU479
	movs	r0, #3
	b	.L57
.LVL114:
.L165:
	.loc 1 788 5 is_stmt 1 discriminator 1 view .LVU480
	ldr	r2, .L178
	ldr	r3, [r2, #144]
	orr	r3, r3, #1
	str	r3, [r2, #144]
	b	.L103
.L166:
	.loc 1 788 5 discriminator 4 view .LVU481
	ldr	r3, .L178
	ldr	r2, [r3, #144]
	orr	r2, r2, #4
	str	r2, [r3, #144]
	.loc 1 788 5 discriminator 4 view .LVU482
	ldr	r2, [r3, #144]
	orr	r2, r2, #1
	str	r2, [r3, #144]
	b	.L103
.L105:
	.loc 1 809 7 view .LVU483
	.loc 1 809 19 is_stmt 0 view .LVU484
	bl	HAL_GetTick
.LVL115:
	mov	r7, r0
.LVL116:
	.loc 1 812 7 is_stmt 1 view .LVU485
.L109:
	.loc 1 812 50 view .LVU486
	.loc 1 812 13 is_stmt 0 view .LVU487
	ldr	r3, .L178
	ldr	r3, [r3, #144]
	.loc 1 812 50 view .LVU488
	tst	r3, #2
	beq	.L108
	.loc 1 814 9 is_stmt 1 view .LVU489
	.loc 1 814 13 is_stmt 0 view .LVU490
	bl	HAL_GetTick
.LVL117:
	.loc 1 814 27 view .LVU491
	subs	r0, r0, r7
	.loc 1 814 11 view .LVU492
	movw	r3, #5000
	cmp	r0, r3
	bls	.L109
	.loc 1 816 18 view .LVU493
	movs	r0, #3
	b	.L57
.L108:
	.loc 1 827 5 is_stmt 1 view .LVU494
	.loc 1 827 7 is_stmt 0 view .LVU495
	cbnz	r6, .L167
.LVL118:
.L97:
	.loc 1 827 7 view .LVU496
.LBE4:
	.loc 1 878 3 is_stmt 1 view .LVU497
	.loc 1 880 3 view .LVU498
	.loc 1 880 28 is_stmt 0 view .LVU499
	ldr	r3, [r4, #40]
	.loc 1 880 5 view .LVU500
	cmp	r3, #0
	beq	.L140
	.loc 1 883 5 is_stmt 1 view .LVU501
	.loc 1 883 7 is_stmt 0 view .LVU502
	cmp	r3, #2
	beq	.L168
	.loc 1 1012 7 is_stmt 1 view .LVU503
	.loc 1 1012 9 is_stmt 0 view .LVU504
	cmp	r5, #12
	beq	.L148
	.loc 1 1015 9 is_stmt 1 view .LVU505
	ldr	r2, .L178
	ldr	r3, [r2]
	bic	r3, r3, #16777216
	str	r3, [r2]
	.loc 1 1018 9 view .LVU506
	.loc 1 1018 21 is_stmt 0 view .LVU507
	bl	HAL_GetTick
.LVL119:
	mov	r4, r0
.LVL120:
	.loc 1 1021 9 is_stmt 1 view .LVU508
.L120:
	.loc 1 1021 48 view .LVU509
	.loc 1 1021 15 is_stmt 0 view .LVU510
	ldr	r3, .L178
	ldr	r3, [r3]
	.loc 1 1021 48 view .LVU511
	tst	r3, #33554432
	beq	.L169
	.loc 1 1023 11 is_stmt 1 view .LVU512
	.loc 1 1023 15 is_stmt 0 view .LVU513
	bl	HAL_GetTick
.LVL121:
	.loc 1 1023 29 view .LVU514
	subs	r0, r0, r4
	.loc 1 1023 13 view .LVU515
	cmp	r0, #2
	bls	.L120
	.loc 1 1025 20 view .LVU516
	movs	r0, #3
	b	.L57
.LVL122:
.L167:
.LBB6:
	.loc 1 829 7 is_stmt 1 view .LVU517
	ldr	r2, .L178
	ldr	r3, [r2, #88]
	bic	r3, r3, #268435456
	str	r3, [r2, #88]
	b	.L97
.LVL123:
.L168:
	.loc 1 829 7 is_stmt 0 view .LVU518
.LBE6:
	.loc 1 886 7 is_stmt 1 view .LVU519
	.loc 1 887 7 view .LVU520
	.loc 1 888 7 view .LVU521
	.loc 1 890 7 view .LVU522
	.loc 1 892 7 view .LVU523
	.loc 1 893 7 view .LVU524
	.loc 1 896 7 view .LVU525
	.loc 1 896 18 is_stmt 0 view .LVU526
	ldr	r3, .L178
	ldr	r3, [r3, #12]
.LVL124:
	.loc 1 897 7 is_stmt 1 view .LVU527
	.loc 1 897 11 is_stmt 0 view .LVU528
	and	r1, r3, #3
	.loc 1 897 78 view .LVU529
	ldr	r2, [r4, #44]
	.loc 1 897 9 view .LVU530
	cmp	r1, r2
	beq	.L170
.LVL125:
.L112:
	.loc 1 911 9 is_stmt 1 view .LVU531
	.loc 1 911 11 is_stmt 0 view .LVU532
	cmp	r5, #12
	beq	.L141
	.loc 1 916 11 is_stmt 1 view .LVU533
	.loc 1 916 15 is_stmt 0 view .LVU534
	ldr	r3, .L178
	ldr	r3, [r3]
	.loc 1 916 13 view .LVU535
	tst	r3, #67108864
	bne	.L142
	.loc 1 918 18 view .LVU536
	ldr	r3, .L178
	ldr	r3, [r3]
	.loc 1 918 14 view .LVU537
	tst	r3, #268435456
	beq	.L171
	.loc 1 922 20 view .LVU538
	movs	r0, #1
	b	.L57
.LVL126:
.L170:
	.loc 1 898 11 discriminator 1 view .LVU539
	and	r2, r3, #112
	.loc 1 898 80 discriminator 1 view .LVU540
	ldr	r1, [r4, #48]
	.loc 1 898 86 discriminator 1 view .LVU541
	subs	r1, r1, #1
	.loc 1 897 90 discriminator 1 view .LVU542
	cmp	r2, r1, lsl #4
	bne	.L112
	.loc 1 899 11 view .LVU543
	and	r2, r3, #32512
	.loc 1 899 79 view .LVU544
	ldr	r1, [r4, #52]
	.loc 1 898 118 view .LVU545
	cmp	r2, r1, lsl #8
	bne	.L112
	.loc 1 904 11 view .LVU546
	and	r1, r3, #131072
	.loc 1 904 80 view .LVU547
	ldr	r2, [r4, #56]
	.loc 1 904 109 view .LVU548
	subs	r2, r2, #7
	it	ne
	movne	r2, #1
	.loc 1 899 111 view .LVU549
	cmp	r1, r2
	bne	.L112
	.loc 1 907 11 view .LVU550
	and	r1, r3, #6291456
	.loc 1 907 82 view .LVU551
	ldr	r2, [r4, #60]
	.loc 1 907 89 view .LVU552
	lsrs	r2, r2, #1
	.loc 1 907 96 view .LVU553
	subs	r2, r2, #1
	.loc 1 904 116 view .LVU554
	cmp	r1, r2, lsl #21
	bne	.L112
	.loc 1 908 11 view .LVU555
	and	r3, r3, #100663296
.LVL127:
	.loc 1 908 82 view .LVU556
	ldr	r2, [r4, #64]
	.loc 1 908 89 view .LVU557
	lsrs	r2, r2, #1
	.loc 1 908 96 view .LVU558
	subs	r2, r2, #1
	.loc 1 907 128 view .LVU559
	cmp	r3, r2, lsl #25
	bne	.L112
	.loc 1 987 9 is_stmt 1 view .LVU560
	.loc 1 987 12 is_stmt 0 view .LVU561
	ldr	r3, .L178
	ldr	r3, [r3]
	.loc 1 987 11 view .LVU562
	tst	r3, #33554432
	beq	.L172
	.loc 1 1044 10 view .LVU563
	movs	r0, #0
	b	.L57
.L179:
	.align	2
.L178:
	.word	1073876992
	.word	1073770496
.L171:
	.loc 1 928 13 is_stmt 1 view .LVU564
	ldr	r2, .L180
	ldr	r3, [r2]
	bic	r3, r3, #16777216
	str	r3, [r2]
	.loc 1 931 13 view .LVU565
	.loc 1 931 25 is_stmt 0 view .LVU566
	bl	HAL_GetTick
.LVL128:
	mov	r5, r0
.LVL129:
	.loc 1 934 13 is_stmt 1 view .LVU567
.L114:
	.loc 1 934 52 view .LVU568
	.loc 1 934 19 is_stmt 0 view .LVU569
	ldr	r3, .L180
	ldr	r3, [r3]
	.loc 1 934 52 view .LVU570
	tst	r3, #33554432
	beq	.L173
	.loc 1 936 15 is_stmt 1 view .LVU571
	.loc 1 936 19 is_stmt 0 view .LVU572
	bl	HAL_GetTick
.LVL130:
	.loc 1 936 33 view .LVU573
	subs	r0, r0, r5
	.loc 1 936 17 view .LVU574
	cmp	r0, #2
	bls	.L114
	.loc 1 938 24 view .LVU575
	movs	r0, #3
	b	.L57
.L173:
	.loc 1 944 13 is_stmt 1 view .LVU576
	ldr	r2, .L180
	ldr	r3, [r2, #12]
	ldr	r1, .L180+4
	ands	r1, r1, r3
	ldr	r3, [r4, #44]
	ldr	r0, [r4, #48]
	subs	r0, r0, #1
	orr	r3, r3, r0, lsl #4
	ldr	r0, [r4, #52]
	orr	r3, r3, r0, lsl #8
	ldr	r0, [r4, #60]
	lsrs	r0, r0, #1
	subs	r0, r0, #1
	orr	r3, r3, r0, lsl #21
	ldr	r0, [r4, #64]
	lsrs	r0, r0, #1
	subs	r0, r0, #1
	orr	r3, r3, r0, lsl #25
	ldr	r0, [r4, #56]
	lsrs	r0, r0, #4
	orr	r3, r3, r0, lsl #17
	orrs	r1, r1, r3
	str	r1, [r2, #12]
	.loc 1 959 13 view .LVU577
	ldr	r3, [r2]
	orr	r3, r3, #16777216
	str	r3, [r2]
	.loc 1 962 13 view .LVU578
	ldr	r3, [r2, #12]
	orr	r3, r3, #16777216
	str	r3, [r2, #12]
	.loc 1 965 13 view .LVU579
	.loc 1 965 25 is_stmt 0 view .LVU580
	bl	HAL_GetTick
.LVL131:
	mov	r4, r0
.LVL132:
	.loc 1 968 13 is_stmt 1 view .LVU581
.L116:
	.loc 1 968 52 view .LVU582
	.loc 1 968 19 is_stmt 0 view .LVU583
	ldr	r3, .L180
	ldr	r3, [r3]
	.loc 1 968 52 view .LVU584
	tst	r3, #33554432
	bne	.L174
	.loc 1 970 15 is_stmt 1 view .LVU585
	.loc 1 970 19 is_stmt 0 view .LVU586
	bl	HAL_GetTick
.LVL133:
	.loc 1 970 33 view .LVU587
	subs	r0, r0, r4
	.loc 1 970 17 view .LVU588
	cmp	r0, #2
	bls	.L116
	.loc 1 972 24 view .LVU589
	movs	r0, #3
	b	.L57
.L174:
	.loc 1 1044 10 view .LVU590
	movs	r0, #0
	b	.L57
.LVL134:
.L172:
	.loc 1 990 11 is_stmt 1 view .LVU591
	ldr	r3, .L180
	ldr	r2, [r3]
	orr	r2, r2, #16777216
	str	r2, [r3]
	.loc 1 993 11 view .LVU592
	ldr	r2, [r3, #12]
	orr	r2, r2, #16777216
	str	r2, [r3, #12]
	.loc 1 996 11 view .LVU593
	.loc 1 996 23 is_stmt 0 view .LVU594
	bl	HAL_GetTick
.LVL135:
	mov	r4, r0
.LVL136:
	.loc 1 999 11 is_stmt 1 view .LVU595
.L118:
	.loc 1 999 50 view .LVU596
	.loc 1 999 17 is_stmt 0 view .LVU597
	ldr	r3, .L180
	ldr	r3, [r3]
	.loc 1 999 50 view .LVU598
	tst	r3, #33554432
	bne	.L175
	.loc 1 1001 13 is_stmt 1 view .LVU599
	.loc 1 1001 17 is_stmt 0 view .LVU600
	bl	HAL_GetTick
.LVL137:
	.loc 1 1001 31 view .LVU601
	subs	r3, r0, r4
	.loc 1 1001 15 view .LVU602
	cmp	r3, #2
	bls	.L118
	.loc 1 1003 22 view .LVU603
	movs	r0, #3
	b	.L57
.L175:
	.loc 1 1044 10 view .LVU604
	movs	r0, #0
	b	.L57
.L169:
	.loc 1 1030 9 is_stmt 1 view .LVU605
	.loc 1 1030 12 is_stmt 0 view .LVU606
	ldr	r2, .L180
	ldr	r1, [r2, #12]
	.loc 1 1030 22 view .LVU607
	ldr	r3, .L180+8
	ands	r3, r3, r1
	str	r3, [r2, #12]
	.loc 1 1044 10 view .LVU608
	movs	r0, #0
	b	.L57
.LVL138:
.L122:
.LCFI10:
	.cfi_def_cfa_offset 0
	.cfi_restore 4
	.cfi_restore 5
	.cfi_restore 6
	.cfi_restore 7
	.cfi_restore 14
	.loc 1 414 12 view .LVU609
	movs	r0, #1
.LVL139:
	.loc 1 1045 1 view .LVU610
	bx	lr
.LVL140:
.L123:
.LCFI11:
	.cfi_def_cfa_offset 32
	.cfi_offset 4, -20
	.cfi_offset 5, -16
	.cfi_offset 6, -12
	.cfi_offset 7, -8
	.cfi_offset 14, -4
	.loc 1 437 16 view .LVU611
	movs	r0, #1
.LVL141:
	.loc 1 437 16 view .LVU612
	b	.L57
.L124:
	.loc 1 451 20 view .LVU613
	movs	r0, #1
	b	.L57
.L161:
	.loc 1 545 16 view .LVU614
	movs	r0, #1
	b	.L57
.L131:
	.loc 1 598 16 view .LVU615
	movs	r0, #1
	b	.L57
.LVL142:
.L140:
	.loc 1 1044 10 view .LVU616
	movs	r0, #0
.LVL143:
.L57:
	.loc 1 1045 1 view .LVU617
	add	sp, sp, #12
.LCFI12:
	.cfi_remember_state
	.cfi_def_cfa_offset 20
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.LVL144:
.L141:
.LCFI13:
	.cfi_restore_state
	.loc 1 980 18 view .LVU618
	movs	r0, #1
	b	.L57
.L142:
	.loc 1 922 20 view .LVU619
	movs	r0, #1
	b	.L57
.L148:
	.loc 1 1040 16 view .LVU620
	movs	r0, #1
	b	.L57
.L181:
	.align	2
.L180:
	.word	1073876992
	.word	-107118452
	.word	-17891332
	.cfi_endproc
.LFE75:
	.size	HAL_RCC_OscConfig, .-HAL_RCC_OscConfig
	.section	.text.HAL_RCC_ClockConfig,"ax",%progbits
	.align	1
	.global	HAL_RCC_ClockConfig
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RCC_ClockConfig, %function
HAL_RCC_ClockConfig:
.LVL145:
.LFB76:
	.loc 1 1098 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 1099 3 view .LVU622
	.loc 1 1104 3 view .LVU623
	.loc 1 1107 3 view .LVU624
	.loc 1 1107 5 is_stmt 0 view .LVU625
	cmp	r0, #0
	beq	.L197
	.loc 1 1098 1 view .LVU626
	push	{r4, r5, r6, lr}
.LCFI14:
	.cfi_def_cfa_offset 16
	.cfi_offset 4, -16
	.cfi_offset 5, -12
	.cfi_offset 6, -8
	.cfi_offset 14, -4
	mov	r5, r1
	mov	r4, r0
	.loc 1 1113 3 is_stmt 1 view .LVU627
	.loc 1 1114 3 view .LVU628
	.loc 1 1121 3 view .LVU629
	.loc 1 1121 17 is_stmt 0 view .LVU630
	ldr	r3, .L212
	ldr	r3, [r3]
	and	r3, r3, #7
	.loc 1 1121 5 view .LVU631
	cmp	r3, r1
	bcs	.L184
	.loc 1 1124 5 is_stmt 1 view .LVU632
	ldr	r2, .L212
	ldr	r3, [r2]
	bic	r3, r3, #7
	orrs	r3, r3, r1
	str	r3, [r2]
	.loc 1 1128 5 view .LVU633
	.loc 1 1128 8 is_stmt 0 view .LVU634
	ldr	r3, [r2]
	and	r3, r3, #7
	.loc 1 1128 7 view .LVU635
	cmp	r3, r1
	bne	.L198
.L184:
	.loc 1 1136 3 is_stmt 1 view .LVU636
	.loc 1 1136 25 is_stmt 0 view .LVU637
	ldr	r3, [r4]
	.loc 1 1136 5 view .LVU638
	tst	r3, #2
	beq	.L185
	.loc 1 1138 5 is_stmt 1 view .LVU639
	.loc 1 1140 5 view .LVU640
	.loc 1 1140 25 is_stmt 0 view .LVU641
	ldr	r2, [r4, #8]
	.loc 1 1140 43 view .LVU642
	ldr	r3, .L212+4
	ldr	r3, [r3, #8]
	and	r3, r3, #240
	.loc 1 1140 7 view .LVU643
	cmp	r2, r3
	bls	.L185
	.loc 1 1142 7 is_stmt 1 view .LVU644
	ldr	r1, .L212+4
.LVL146:
	.loc 1 1142 7 is_stmt 0 view .LVU645
	ldr	r3, [r1, #8]
	bic	r3, r3, #240
	orrs	r2, r2, r3
	str	r2, [r1, #8]
.L185:
	.loc 1 1147 3 is_stmt 1 view .LVU646
	.loc 1 1147 25 is_stmt 0 view .LVU647
	ldr	r3, [r4]
	.loc 1 1147 5 view .LVU648
	tst	r3, #1
	beq	.L186
	.loc 1 1149 5 is_stmt 1 view .LVU649
	.loc 1 1152 5 view .LVU650
	.loc 1 1152 25 is_stmt 0 view .LVU651
	ldr	r3, [r4, #4]
	.loc 1 1152 7 view .LVU652
	cmp	r3, #3
	beq	.L209
	.loc 1 1177 7 is_stmt 1 view .LVU653
	.loc 1 1177 9 is_stmt 0 view .LVU654
	cmp	r3, #2
	beq	.L210
	.loc 1 1186 12 is_stmt 1 view .LVU655
	.loc 1 1186 14 is_stmt 0 view .LVU656
	cbnz	r3, .L190
	.loc 1 1189 9 is_stmt 1 view .LVU657
	.loc 1 1189 12 is_stmt 0 view .LVU658
	ldr	r2, .L212+4
	ldr	r2, [r2]
	.loc 1 1189 11 view .LVU659
	tst	r2, #2
	bne	.L188
	.loc 1 1191 18 view .LVU660
	movs	r0, #1
.LVL147:
	.loc 1 1191 18 view .LVU661
	b	.L183
.LVL148:
.L209:
	.loc 1 1155 7 is_stmt 1 view .LVU662
	.loc 1 1155 10 is_stmt 0 view .LVU663
	ldr	r2, .L212+4
	ldr	r2, [r2]
	.loc 1 1155 9 view .LVU664
	tst	r2, #33554432
	beq	.L211
.L188:
	.loc 1 1219 5 is_stmt 1 view .LVU665
	ldr	r1, .L212+4
	ldr	r2, [r1, #8]
	bic	r2, r2, #3
	orrs	r3, r3, r2
	str	r3, [r1, #8]
	.loc 1 1222 5 view .LVU666
	.loc 1 1222 17 is_stmt 0 view .LVU667
	bl	HAL_GetTick
.LVL149:
	.loc 1 1222 17 view .LVU668
	mov	r6, r0
.LVL150:
	.loc 1 1224 5 is_stmt 1 view .LVU669
.L191:
	.loc 1 1224 41 view .LVU670
	.loc 1 1224 11 is_stmt 0 view .LVU671
	ldr	r3, .L212+4
	ldr	r3, [r3, #8]
	and	r3, r3, #12
	.loc 1 1224 62 view .LVU672
	ldr	r2, [r4, #4]
	.loc 1 1224 41 view .LVU673
	cmp	r3, r2, lsl #2
	beq	.L186
	.loc 1 1226 7 is_stmt 1 view .LVU674
	.loc 1 1226 11 is_stmt 0 view .LVU675
	bl	HAL_GetTick
.LVL151:
	.loc 1 1226 25 view .LVU676
	subs	r0, r0, r6
	.loc 1 1226 9 view .LVU677
	movw	r3, #5000
	cmp	r0, r3
	bls	.L191
	.loc 1 1228 16 view .LVU678
	movs	r0, #3
	b	.L183
.LVL152:
.L210:
	.loc 1 1180 9 is_stmt 1 view .LVU679
	.loc 1 1180 12 is_stmt 0 view .LVU680
	ldr	r2, .L212+4
	ldr	r2, [r2]
	.loc 1 1180 11 view .LVU681
	tst	r2, #131072
	bne	.L188
	.loc 1 1182 18 view .LVU682
	movs	r0, #1
.LVL153:
	.loc 1 1182 18 view .LVU683
	b	.L183
.LVL154:
.L190:
	.loc 1 1198 9 is_stmt 1 view .LVU684
	.loc 1 1198 12 is_stmt 0 view .LVU685
	ldr	r2, .L212+4
	ldr	r2, [r2]
	.loc 1 1198 11 view .LVU686
	tst	r2, #1024
	bne	.L188
	.loc 1 1200 18 view .LVU687
	movs	r0, #1
.LVL155:
	.loc 1 1200 18 view .LVU688
	b	.L183
.L186:
	.loc 1 1244 3 is_stmt 1 view .LVU689
	.loc 1 1244 25 is_stmt 0 view .LVU690
	ldr	r3, [r4]
	.loc 1 1244 5 view .LVU691
	tst	r3, #2
	beq	.L193
	.loc 1 1246 5 is_stmt 1 view .LVU692
	.loc 1 1246 25 is_stmt 0 view .LVU693
	ldr	r2, [r4, #8]
	.loc 1 1246 43 view .LVU694
	ldr	r3, .L212+4
	ldr	r3, [r3, #8]
	and	r3, r3, #240
	.loc 1 1246 7 view .LVU695
	cmp	r2, r3
	bcs	.L193
	.loc 1 1248 7 is_stmt 1 view .LVU696
	ldr	r1, .L212+4
	ldr	r3, [r1, #8]
	bic	r3, r3, #240
	orrs	r2, r2, r3
	str	r2, [r1, #8]
.L193:
	.loc 1 1253 3 view .LVU697
	.loc 1 1253 17 is_stmt 0 view .LVU698
	ldr	r3, .L212
	ldr	r3, [r3]
	and	r3, r3, #7
	.loc 1 1253 5 view .LVU699
	cmp	r3, r5
	bls	.L194
	.loc 1 1256 5 is_stmt 1 view .LVU700
	ldr	r2, .L212
	ldr	r3, [r2]
	bic	r3, r3, #7
	orrs	r3, r3, r5
	str	r3, [r2]
	.loc 1 1260 5 view .LVU701
	.loc 1 1260 8 is_stmt 0 view .LVU702
	ldr	r3, [r2]
	and	r3, r3, #7
	.loc 1 1260 7 view .LVU703
	cmp	r3, r5
	bne	.L204
.L194:
	.loc 1 1267 3 is_stmt 1 view .LVU704
	.loc 1 1267 25 is_stmt 0 view .LVU705
	ldr	r3, [r4]
	.loc 1 1267 5 view .LVU706
	tst	r3, #4
	beq	.L195
	.loc 1 1269 5 is_stmt 1 view .LVU707
	.loc 1 1270 5 view .LVU708
	ldr	r2, .L212+4
	ldr	r3, [r2, #8]
	bic	r3, r3, #1792
	ldr	r1, [r4, #12]
	orrs	r3, r3, r1
	str	r3, [r2, #8]
.L195:
	.loc 1 1274 3 view .LVU709
	.loc 1 1274 25 is_stmt 0 view .LVU710
	ldr	r3, [r4]
	.loc 1 1274 5 view .LVU711
	tst	r3, #8
	beq	.L196
	.loc 1 1276 5 is_stmt 1 view .LVU712
	.loc 1 1277 5 view .LVU713
	ldr	r2, .L212+4
	ldr	r3, [r2, #8]
	bic	r3, r3, #14336
	ldr	r1, [r4, #16]
	orr	r3, r3, r1, lsl #3
	str	r3, [r2, #8]
.L196:
	.loc 1 1281 3 view .LVU714
	.loc 1 1281 21 is_stmt 0 view .LVU715
	bl	HAL_RCC_GetSysClockFreq
.LVL156:
	.loc 1 1281 65 view .LVU716
	ldr	r3, .L212+4
	ldr	r3, [r3, #8]
	.loc 1 1281 100 view .LVU717
	ubfx	r3, r3, #4, #4
	.loc 1 1281 64 view .LVU718
	ldr	r2, .L212+8
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	.loc 1 1281 122 view .LVU719
	and	r3, r3, #31
	.loc 1 1281 47 view .LVU720
	lsrs	r0, r0, r3
	.loc 1 1281 19 view .LVU721
	ldr	r3, .L212+12
	str	r0, [r3]
	.loc 1 1284 3 is_stmt 1 view .LVU722
	.loc 1 1284 12 is_stmt 0 view .LVU723
	ldr	r3, .L212+16
	ldr	r0, [r3]
	bl	HAL_InitTick
.LVL157:
	.loc 1 1286 3 is_stmt 1 view .LVU724
.L183:
	.loc 1 1287 1 is_stmt 0 view .LVU725
	pop	{r4, r5, r6, pc}
.LVL158:
.L197:
.LCFI15:
	.cfi_def_cfa_offset 0
	.cfi_restore 4
	.cfi_restore 5
	.cfi_restore 6
	.cfi_restore 14
	.loc 1 1109 12 view .LVU726
	movs	r0, #1
.LVL159:
	.loc 1 1287 1 view .LVU727
	bx	lr
.LVL160:
.L198:
.LCFI16:
	.cfi_def_cfa_offset 16
	.cfi_offset 4, -16
	.cfi_offset 5, -12
	.cfi_offset 6, -8
	.cfi_offset 14, -4
	.loc 1 1130 14 view .LVU728
	movs	r0, #1
.LVL161:
	.loc 1 1130 14 view .LVU729
	b	.L183
.LVL162:
.L211:
	.loc 1 1157 16 view .LVU730
	movs	r0, #1
.LVL163:
	.loc 1 1157 16 view .LVU731
	b	.L183
.L204:
	.loc 1 1262 14 view .LVU732
	movs	r0, #1
	b	.L183
.L213:
	.align	2
.L212:
	.word	1073881088
	.word	1073876992
	.word	AHBPrescTable
	.word	SystemCoreClock
	.word	uwTickPrio
	.cfi_endproc
.LFE76:
	.size	HAL_RCC_ClockConfig, .-HAL_RCC_ClockConfig
	.section	.text.HAL_RCC_GetHCLKFreq,"ax",%progbits
	.align	1
	.global	HAL_RCC_GetHCLKFreq
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RCC_GetHCLKFreq, %function
HAL_RCC_GetHCLKFreq:
.LFB79:
	.loc 1 1487 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1488 3 view .LVU734
	.loc 1 1489 1 is_stmt 0 view .LVU735
	ldr	r3, .L215
	ldr	r0, [r3]
	bx	lr
.L216:
	.align	2
.L215:
	.word	SystemCoreClock
	.cfi_endproc
.LFE79:
	.size	HAL_RCC_GetHCLKFreq, .-HAL_RCC_GetHCLKFreq
	.section	.text.HAL_RCC_GetPCLK1Freq,"ax",%progbits
	.align	1
	.global	HAL_RCC_GetPCLK1Freq
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RCC_GetPCLK1Freq, %function
HAL_RCC_GetPCLK1Freq:
.LFB80:
	.loc 1 1498 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
.LCFI17:
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	.cfi_offset 14, -4
	.loc 1 1500 3 view .LVU737
	.loc 1 1500 11 is_stmt 0 view .LVU738
	bl	HAL_RCC_GetHCLKFreq
.LVL164:
	.loc 1 1500 51 view .LVU739
	ldr	r3, .L219
	ldr	r3, [r3, #8]
	.loc 1 1500 87 view .LVU740
	ubfx	r3, r3, #8, #3
	.loc 1 1500 50 view .LVU741
	ldr	r2, .L219+4
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	.loc 1 1500 110 view .LVU742
	and	r3, r3, #31
	.loc 1 1501 1 view .LVU743
	lsrs	r0, r0, r3
	pop	{r3, pc}
.L220:
	.align	2
.L219:
	.word	1073876992
	.word	APBPrescTable
	.cfi_endproc
.LFE80:
	.size	HAL_RCC_GetPCLK1Freq, .-HAL_RCC_GetPCLK1Freq
	.section	.text.HAL_RCC_GetPCLK2Freq,"ax",%progbits
	.align	1
	.global	HAL_RCC_GetPCLK2Freq
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RCC_GetPCLK2Freq, %function
HAL_RCC_GetPCLK2Freq:
.LFB81:
	.loc 1 1510 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
.LCFI18:
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	.cfi_offset 14, -4
	.loc 1 1512 3 view .LVU745
	.loc 1 1512 11 is_stmt 0 view .LVU746
	bl	HAL_RCC_GetHCLKFreq
.LVL165:
	.loc 1 1512 50 view .LVU747
	ldr	r3, .L223
	ldr	r3, [r3, #8]
	.loc 1 1512 86 view .LVU748
	ubfx	r3, r3, #11, #3
	.loc 1 1512 49 view .LVU749
	ldr	r2, .L223+4
	ldrb	r3, [r2, r3]	@ zero_extendqisi2
	.loc 1 1512 109 view .LVU750
	and	r3, r3, #31
	.loc 1 1513 1 view .LVU751
	lsrs	r0, r0, r3
	pop	{r3, pc}
.L224:
	.align	2
.L223:
	.word	1073876992
	.word	APBPrescTable
	.cfi_endproc
.LFE81:
	.size	HAL_RCC_GetPCLK2Freq, .-HAL_RCC_GetPCLK2Freq
	.section	.text.HAL_RCC_GetOscConfig,"ax",%progbits
	.align	1
	.global	HAL_RCC_GetOscConfig
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RCC_GetOscConfig, %function
HAL_RCC_GetOscConfig:
.LVL166:
.LFB82:
	.loc 1 1523 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1525 3 view .LVU753
	.loc 1 1532 3 view .LVU754
	.loc 1 1532 37 is_stmt 0 view .LVU755
	movs	r3, #31
	str	r3, [r0]
	.loc 1 1537 3 is_stmt 1 view .LVU756
	.loc 1 1537 6 is_stmt 0 view .LVU757
	ldr	r3, .L242
	ldr	r3, [r3]
	.loc 1 1537 5 view .LVU758
	tst	r3, #262144
	beq	.L226
	.loc 1 1539 5 is_stmt 1 view .LVU759
	.loc 1 1539 33 is_stmt 0 view .LVU760
	mov	r3, #327680
	str	r3, [r0, #4]
.L227:
	.loc 1 1551 3 is_stmt 1 view .LVU761
	.loc 1 1551 6 is_stmt 0 view .LVU762
	ldr	r3, .L242
	ldr	r3, [r3]
	.loc 1 1551 5 view .LVU763
	tst	r3, #1
	beq	.L229
	.loc 1 1553 5 is_stmt 1 view .LVU764
	.loc 1 1553 33 is_stmt 0 view .LVU765
	movs	r3, #1
	str	r3, [r0, #24]
.L230:
	.loc 1 1560 3 is_stmt 1 view .LVU766
	.loc 1 1560 44 is_stmt 0 view .LVU767
	ldr	r3, .L242
	ldr	r2, [r3, #4]
	.loc 1 1560 84 view .LVU768
	ubfx	r2, r2, #8, #8
	.loc 1 1560 42 view .LVU769
	str	r2, [r0, #28]
	.loc 1 1561 3 is_stmt 1 view .LVU770
	.loc 1 1561 38 is_stmt 0 view .LVU771
	ldr	r2, [r3]
	and	r2, r2, #240
	.loc 1 1561 36 view .LVU772
	str	r2, [r0, #32]
	.loc 1 1564 3 is_stmt 1 view .LVU773
	.loc 1 1564 6 is_stmt 0 view .LVU774
	ldr	r3, [r3]
	.loc 1 1564 5 view .LVU775
	tst	r3, #256
	beq	.L231
	.loc 1 1566 5 is_stmt 1 view .LVU776
	.loc 1 1566 33 is_stmt 0 view .LVU777
	mov	r3, #256
	str	r3, [r0, #12]
.L232:
	.loc 1 1573 3 is_stmt 1 view .LVU778
	.loc 1 1573 44 is_stmt 0 view .LVU779
	ldr	r2, .L242
	ldr	r3, [r2, #4]
	.loc 1 1573 84 view .LVU780
	ubfx	r3, r3, #24, #5
	.loc 1 1573 42 view .LVU781
	str	r3, [r0, #16]
	.loc 1 1576 3 is_stmt 1 view .LVU782
	.loc 1 1576 6 is_stmt 0 view .LVU783
	ldr	r3, [r2, #144]
	.loc 1 1576 5 view .LVU784
	tst	r3, #4
	beq	.L233
	.loc 1 1586 7 is_stmt 1 view .LVU785
	.loc 1 1586 35 is_stmt 0 view .LVU786
	movs	r3, #5
	str	r3, [r0, #8]
.L234:
	.loc 1 1608 3 is_stmt 1 view .LVU787
	.loc 1 1608 6 is_stmt 0 view .LVU788
	ldr	r3, .L242
	ldr	r3, [r3, #148]
	.loc 1 1608 5 view .LVU789
	tst	r3, #1
	beq	.L236
	.loc 1 1610 5 is_stmt 1 view .LVU790
	.loc 1 1610 33 is_stmt 0 view .LVU791
	movs	r3, #1
	str	r3, [r0, #20]
.L237:
	.loc 1 1640 3 is_stmt 1 view .LVU792
	.loc 1 1640 33 is_stmt 0 view .LVU793
	movs	r3, #0
	str	r3, [r0, #36]
	.loc 1 1644 3 is_stmt 1 view .LVU794
	.loc 1 1644 6 is_stmt 0 view .LVU795
	add	r3, r3, #1073741824
	add	r3, r3, #135168
	ldr	r3, [r3]
	.loc 1 1644 5 view .LVU796
	tst	r3, #16777216
	beq	.L238
	.loc 1 1646 5 is_stmt 1 view .LVU797
	.loc 1 1646 37 is_stmt 0 view .LVU798
	movs	r3, #2
	str	r3, [r0, #40]
.L239:
	.loc 1 1652 3 is_stmt 1 view .LVU799
	.loc 1 1652 38 is_stmt 0 view .LVU800
	ldr	r2, .L242
	ldr	r3, [r2, #12]
	and	r3, r3, #3
	.loc 1 1652 36 view .LVU801
	str	r3, [r0, #44]
	.loc 1 1653 3 is_stmt 1 view .LVU802
	.loc 1 1653 34 is_stmt 0 view .LVU803
	ldr	r3, [r2, #12]
	.loc 1 1653 75 view .LVU804
	ubfx	r3, r3, #4, #3
	.loc 1 1653 100 view .LVU805
	adds	r3, r3, #1
	.loc 1 1653 31 view .LVU806
	str	r3, [r0, #48]
	.loc 1 1654 3 is_stmt 1 view .LVU807
	.loc 1 1654 33 is_stmt 0 view .LVU808
	ldr	r3, [r2, #12]
	.loc 1 1654 74 view .LVU809
	ubfx	r3, r3, #8, #7
	.loc 1 1654 31 view .LVU810
	str	r3, [r0, #52]
	.loc 1 1655 3 is_stmt 1 view .LVU811
	.loc 1 1655 36 is_stmt 0 view .LVU812
	ldr	r3, [r2, #12]
	.loc 1 1655 77 view .LVU813
	ubfx	r3, r3, #21, #2
	.loc 1 1655 102 view .LVU814
	adds	r3, r3, #1
	.loc 1 1655 108 view .LVU815
	lsls	r3, r3, #1
	.loc 1 1655 31 view .LVU816
	str	r3, [r0, #60]
	.loc 1 1656 3 is_stmt 1 view .LVU817
	.loc 1 1656 36 is_stmt 0 view .LVU818
	ldr	r3, [r2, #12]
	.loc 1 1656 77 view .LVU819
	ubfx	r3, r3, #25, #2
	.loc 1 1656 102 view .LVU820
	adds	r3, r3, #1
	.loc 1 1656 108 view .LVU821
	lsls	r3, r3, #1
	.loc 1 1656 31 view .LVU822
	str	r3, [r0, #64]
	.loc 1 1661 3 is_stmt 1 view .LVU823
	.loc 1 1661 6 is_stmt 0 view .LVU824
	ldr	r3, [r2, #12]
	.loc 1 1661 5 view .LVU825
	tst	r3, #131072
	beq	.L240
	.loc 1 1663 5 is_stmt 1 view .LVU826
	.loc 1 1663 33 is_stmt 0 view .LVU827
	movs	r3, #17
	str	r3, [r0, #56]
	bx	lr
.L226:
	.loc 1 1541 8 is_stmt 1 view .LVU828
	.loc 1 1541 11 is_stmt 0 view .LVU829
	ldr	r3, .L242
	ldr	r3, [r3]
	.loc 1 1541 10 view .LVU830
	tst	r3, #65536
	beq	.L228
	.loc 1 1543 5 is_stmt 1 view .LVU831
	.loc 1 1543 33 is_stmt 0 view .LVU832
	mov	r3, #65536
	str	r3, [r0, #4]
	b	.L227
.L228:
	.loc 1 1547 5 is_stmt 1 view .LVU833
	.loc 1 1547 33 is_stmt 0 view .LVU834
	movs	r3, #0
	str	r3, [r0, #4]
	b	.L227
.L229:
	.loc 1 1557 5 is_stmt 1 view .LVU835
	.loc 1 1557 33 is_stmt 0 view .LVU836
	movs	r3, #0
	str	r3, [r0, #24]
	b	.L230
.L231:
	.loc 1 1570 5 is_stmt 1 view .LVU837
	.loc 1 1570 33 is_stmt 0 view .LVU838
	movs	r3, #0
	str	r3, [r0, #12]
	b	.L232
.L233:
	.loc 1 1589 8 is_stmt 1 view .LVU839
	.loc 1 1589 11 is_stmt 0 view .LVU840
	ldr	r3, .L242
	ldr	r3, [r3, #144]
	.loc 1 1589 10 view .LVU841
	tst	r3, #1
	beq	.L235
	.loc 1 1599 7 is_stmt 1 view .LVU842
	.loc 1 1599 35 is_stmt 0 view .LVU843
	movs	r3, #1
	str	r3, [r0, #8]
	b	.L234
.L235:
	.loc 1 1604 5 is_stmt 1 view .LVU844
	.loc 1 1604 33 is_stmt 0 view .LVU845
	movs	r3, #0
	str	r3, [r0, #8]
	b	.L234
.L236:
	.loc 1 1614 5 is_stmt 1 view .LVU846
	.loc 1 1614 33 is_stmt 0 view .LVU847
	movs	r3, #0
	str	r3, [r0, #20]
	b	.L237
.L238:
	.loc 1 1650 5 is_stmt 1 view .LVU848
	.loc 1 1650 37 is_stmt 0 view .LVU849
	movs	r3, #1
	str	r3, [r0, #40]
	b	.L239
.L240:
	.loc 1 1667 5 is_stmt 1 view .LVU850
	.loc 1 1667 33 is_stmt 0 view .LVU851
	movs	r3, #7
	str	r3, [r0, #56]
	.loc 1 1671 1 view .LVU852
	bx	lr
.L243:
	.align	2
.L242:
	.word	1073876992
	.cfi_endproc
.LFE82:
	.size	HAL_RCC_GetOscConfig, .-HAL_RCC_GetOscConfig
	.section	.text.HAL_RCC_GetClockConfig,"ax",%progbits
	.align	1
	.global	HAL_RCC_GetClockConfig
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RCC_GetClockConfig, %function
HAL_RCC_GetClockConfig:
.LVL167:
.LFB83:
	.loc 1 1682 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1684 3 view .LVU854
	.loc 1 1685 3 view .LVU855
	.loc 1 1688 3 view .LVU856
	.loc 1 1688 32 is_stmt 0 view .LVU857
	movs	r3, #15
	str	r3, [r0]
	.loc 1 1691 3 is_stmt 1 view .LVU858
	.loc 1 1691 37 is_stmt 0 view .LVU859
	ldr	r3, .L245
	ldr	r2, [r3, #8]
	and	r2, r2, #3
	.loc 1 1691 35 view .LVU860
	str	r2, [r0, #4]
	.loc 1 1694 3 is_stmt 1 view .LVU861
	.loc 1 1694 38 is_stmt 0 view .LVU862
	ldr	r2, [r3, #8]
	and	r2, r2, #240
	.loc 1 1694 36 view .LVU863
	str	r2, [r0, #8]
	.loc 1 1697 3 is_stmt 1 view .LVU864
	.loc 1 1697 39 is_stmt 0 view .LVU865
	ldr	r2, [r3, #8]
	and	r2, r2, #1792
	.loc 1 1697 37 view .LVU866
	str	r2, [r0, #12]
	.loc 1 1700 3 is_stmt 1 view .LVU867
	.loc 1 1700 40 is_stmt 0 view .LVU868
	ldr	r3, [r3, #8]
	.loc 1 1700 76 view .LVU869
	lsrs	r3, r3, #3
	and	r3, r3, #1792
	.loc 1 1700 37 view .LVU870
	str	r3, [r0, #16]
	.loc 1 1703 3 is_stmt 1 view .LVU871
	.loc 1 1703 16 is_stmt 0 view .LVU872
	ldr	r3, .L245+4
	ldr	r3, [r3]
	and	r3, r3, #7
	.loc 1 1703 14 view .LVU873
	str	r3, [r1]
	.loc 1 1704 1 view .LVU874
	bx	lr
.L246:
	.align	2
.L245:
	.word	1073876992
	.word	1073881088
	.cfi_endproc
.LFE83:
	.size	HAL_RCC_GetClockConfig, .-HAL_RCC_GetClockConfig
	.section	.text.HAL_RCC_EnableCSS,"ax",%progbits
	.align	1
	.global	HAL_RCC_EnableCSS
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RCC_EnableCSS, %function
HAL_RCC_EnableCSS:
.LFB84:
	.loc 1 1717 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1718 3 view .LVU876
	ldr	r2, .L248
	ldr	r3, [r2]
	orr	r3, r3, #524288
	str	r3, [r2]
	.loc 1 1719 1 is_stmt 0 view .LVU877
	bx	lr
.L249:
	.align	2
.L248:
	.word	1073876992
	.cfi_endproc
.LFE84:
	.size	HAL_RCC_EnableCSS, .-HAL_RCC_EnableCSS
	.section	.text.HAL_RCC_CSSCallback,"ax",%progbits
	.align	1
	.weak	HAL_RCC_CSSCallback
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RCC_CSSCallback, %function
HAL_RCC_CSSCallback:
.LFB86:
	.loc 1 1744 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1748 1 view .LVU879
	bx	lr
	.cfi_endproc
.LFE86:
	.size	HAL_RCC_CSSCallback, .-HAL_RCC_CSSCallback
	.section	.text.HAL_RCC_NMI_IRQHandler,"ax",%progbits
	.align	1
	.global	HAL_RCC_NMI_IRQHandler
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RCC_NMI_IRQHandler, %function
HAL_RCC_NMI_IRQHandler:
.LFB85:
	.loc 1 1727 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
.LCFI19:
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	.cfi_offset 14, -4
	.loc 1 1729 3 view .LVU881
	.loc 1 1729 6 is_stmt 0 view .LVU882
	ldr	r3, .L255
	ldr	r3, [r3, #28]
	.loc 1 1729 5 view .LVU883
	tst	r3, #256
	bne	.L254
.L251:
	.loc 1 1737 1 view .LVU884
	pop	{r3, pc}
.L254:
	.loc 1 1732 5 is_stmt 1 view .LVU885
	bl	HAL_RCC_CSSCallback
.LVL168:
	.loc 1 1735 5 view .LVU886
	ldr	r3, .L255
	mov	r2, #256
	str	r2, [r3, #32]
	.loc 1 1737 1 is_stmt 0 view .LVU887
	b	.L251
.L256:
	.align	2
.L255:
	.word	1073876992
	.cfi_endproc
.LFE85:
	.size	HAL_RCC_NMI_IRQHandler, .-HAL_RCC_NMI_IRQHandler
	.section	.text.HAL_RCC_GetResetSource,"ax",%progbits
	.align	1
	.global	HAL_RCC_GetResetSource
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_RCC_GetResetSource, %function
HAL_RCC_GetResetSource:
.LFB87:
	.loc 1 1758 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1759 3 view .LVU889
	.loc 1 1762 3 view .LVU890
	.loc 1 1762 14 is_stmt 0 view .LVU891
	ldr	r3, .L258
	ldr	r0, [r3, #148]
.LVL169:
	.loc 1 1765 3 is_stmt 1 view .LVU892
	.loc 1 1765 6 is_stmt 0 view .LVU893
	ldr	r2, [r3, #148]
	.loc 1 1765 12 view .LVU894
	orr	r2, r2, #8388608
	str	r2, [r3, #148]
	.loc 1 1767 3 is_stmt 1 view .LVU895
	.loc 1 1768 1 is_stmt 0 view .LVU896
	and	r0, r0, #-33554432
.LVL170:
	.loc 1 1768 1 view .LVU897
	bx	lr
.L259:
	.align	2
.L258:
	.word	1073876992
	.cfi_endproc
.LFE87:
	.size	HAL_RCC_GetResetSource, .-HAL_RCC_GetResetSource
	.text
.Letext0:
	.file 2 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/arm-none-eabi/include/machine/_default_types.h"
	.file 3 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/arm-none-eabi/include/sys/_stdint.h"
	.file 4 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/system_stm32l4xx.h"
	.file 5 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
	.file 6 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l4xx.h"
	.file 7 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_def.h"
	.file 8 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_rcc.h"
	.file 9 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_gpio.h"
	.file 10 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"
	.file 11 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x10a9
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF173
	.byte	0xc
	.4byte	.LASF174
	.4byte	.LASF175
	.4byte	.Ldebug_ranges0+0x18
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
	.uleb128 0x6
	.4byte	0xb0
	.uleb128 0x5
	.4byte	0xb0
	.uleb128 0x7
	.4byte	.LASF15
	.byte	0x4
	.byte	0x39
	.byte	0x11
	.4byte	0xb0
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.4byte	0x9f
	.4byte	0xe4
	.uleb128 0x9
	.4byte	0x8c
	.byte	0xf
	.byte	0
	.uleb128 0x5
	.4byte	0xd4
	.uleb128 0x7
	.4byte	.LASF16
	.byte	0x4
	.byte	0x3b
	.byte	0x17
	.4byte	0xe4
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.4byte	0x9f
	.4byte	0x107
	.uleb128 0x9
	.4byte	0x8c
	.byte	0x7
	.byte	0
	.uleb128 0x5
	.4byte	0xf7
	.uleb128 0x7
	.4byte	.LASF17
	.byte	0x4
	.byte	0x3c
	.byte	0x17
	.4byte	0x107
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.4byte	0xc1
	.4byte	0x12a
	.uleb128 0x9
	.4byte	0x8c
	.byte	0xb
	.byte	0
	.uleb128 0x5
	.4byte	0x11a
	.uleb128 0x7
	.4byte	.LASF18
	.byte	0x4
	.byte	0x3d
	.byte	0x17
	.4byte	0x12a
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.4byte	0xb0
	.4byte	0x14d
	.uleb128 0x9
	.4byte	0x8c
	.byte	0x3
	.byte	0
	.uleb128 0xa
	.byte	0x54
	.byte	0x5
	.2byte	0x1d7
	.byte	0x9
	.4byte	0x276
	.uleb128 0xb
	.ascii	"ACR\000"
	.byte	0x5
	.2byte	0x1d9
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xc
	.4byte	.LASF19
	.byte	0x5
	.2byte	0x1da
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xc
	.4byte	.LASF20
	.byte	0x5
	.2byte	0x1db
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xc
	.4byte	.LASF21
	.byte	0x5
	.2byte	0x1dc
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0xb
	.ascii	"SR\000"
	.byte	0x5
	.2byte	0x1dd
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xb
	.ascii	"CR\000"
	.byte	0x5
	.2byte	0x1de
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0xc
	.4byte	.LASF22
	.byte	0x5
	.2byte	0x1df
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xc
	.4byte	.LASF23
	.byte	0x5
	.2byte	0x1e0
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0xc
	.4byte	.LASF24
	.byte	0x5
	.2byte	0x1e1
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xc
	.4byte	.LASF25
	.byte	0x5
	.2byte	0x1e2
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0xc
	.4byte	.LASF26
	.byte	0x5
	.2byte	0x1e3
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xc
	.4byte	.LASF27
	.byte	0x5
	.2byte	0x1e4
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0xc
	.4byte	.LASF28
	.byte	0x5
	.2byte	0x1e5
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xc
	.4byte	.LASF29
	.byte	0x5
	.2byte	0x1e6
	.byte	0x11
	.4byte	0x13d
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.uleb128 0xc
	.4byte	.LASF30
	.byte	0x5
	.2byte	0x1e7
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x44
	.uleb128 0xc
	.4byte	.LASF31
	.byte	0x5
	.2byte	0x1e8
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0xc
	.4byte	.LASF32
	.byte	0x5
	.2byte	0x1e9
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x4c
	.uleb128 0xc
	.4byte	.LASF33
	.byte	0x5
	.2byte	0x1ea
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.byte	0
	.uleb128 0xd
	.4byte	.LASF34
	.byte	0x5
	.2byte	0x1eb
	.byte	0x3
	.4byte	0x14d
	.uleb128 0xa
	.byte	0x30
	.byte	0x5
	.2byte	0x212
	.byte	0x9
	.4byte	0x33e
	.uleb128 0xc
	.4byte	.LASF35
	.byte	0x5
	.2byte	0x214
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xc
	.4byte	.LASF36
	.byte	0x5
	.2byte	0x215
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xc
	.4byte	.LASF37
	.byte	0x5
	.2byte	0x216
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xc
	.4byte	.LASF38
	.byte	0x5
	.2byte	0x217
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0xb
	.ascii	"IDR\000"
	.byte	0x5
	.2byte	0x218
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xb
	.ascii	"ODR\000"
	.byte	0x5
	.2byte	0x219
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0xc
	.4byte	.LASF39
	.byte	0x5
	.2byte	0x21a
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xc
	.4byte	.LASF40
	.byte	0x5
	.2byte	0x21b
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0xb
	.ascii	"AFR\000"
	.byte	0x5
	.2byte	0x21c
	.byte	0x11
	.4byte	0x34e
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xb
	.ascii	"BRR\000"
	.byte	0x5
	.2byte	0x21d
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xc
	.4byte	.LASF41
	.byte	0x5
	.2byte	0x21e
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.byte	0
	.uleb128 0x8
	.4byte	0xbc
	.4byte	0x34e
	.uleb128 0x9
	.4byte	0x8c
	.byte	0x1
	.byte	0
	.uleb128 0x6
	.4byte	0x33e
	.uleb128 0xd
	.4byte	.LASF42
	.byte	0x5
	.2byte	0x220
	.byte	0x3
	.4byte	0x283
	.uleb128 0xa
	.byte	0x60
	.byte	0x5
	.2byte	0x267
	.byte	0x9
	.4byte	0x4eb
	.uleb128 0xb
	.ascii	"CR1\000"
	.byte	0x5
	.2byte	0x269
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xb
	.ascii	"CR2\000"
	.byte	0x5
	.2byte	0x26a
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xb
	.ascii	"CR3\000"
	.byte	0x5
	.2byte	0x26b
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xb
	.ascii	"CR4\000"
	.byte	0x5
	.2byte	0x26c
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0xb
	.ascii	"SR1\000"
	.byte	0x5
	.2byte	0x26d
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xb
	.ascii	"SR2\000"
	.byte	0x5
	.2byte	0x26e
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0xb
	.ascii	"SCR\000"
	.byte	0x5
	.2byte	0x26f
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xc
	.4byte	.LASF43
	.byte	0x5
	.2byte	0x270
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0xc
	.4byte	.LASF44
	.byte	0x5
	.2byte	0x271
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xc
	.4byte	.LASF45
	.byte	0x5
	.2byte	0x272
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0xc
	.4byte	.LASF46
	.byte	0x5
	.2byte	0x273
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xc
	.4byte	.LASF47
	.byte	0x5
	.2byte	0x274
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0xc
	.4byte	.LASF48
	.byte	0x5
	.2byte	0x275
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xc
	.4byte	.LASF49
	.byte	0x5
	.2byte	0x276
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.uleb128 0xc
	.4byte	.LASF50
	.byte	0x5
	.2byte	0x277
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0xc
	.4byte	.LASF51
	.byte	0x5
	.2byte	0x278
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x3c
	.uleb128 0xc
	.4byte	.LASF52
	.byte	0x5
	.2byte	0x279
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0xc
	.4byte	.LASF53
	.byte	0x5
	.2byte	0x27a
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x44
	.uleb128 0xc
	.4byte	.LASF54
	.byte	0x5
	.2byte	0x27b
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0xc
	.4byte	.LASF55
	.byte	0x5
	.2byte	0x27c
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x4c
	.uleb128 0xc
	.4byte	.LASF56
	.byte	0x5
	.2byte	0x27d
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0xc
	.4byte	.LASF57
	.byte	0x5
	.2byte	0x27e
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x54
	.uleb128 0xc
	.4byte	.LASF58
	.byte	0x5
	.2byte	0x27f
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0xc
	.4byte	.LASF59
	.byte	0x5
	.2byte	0x280
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x5c
	.byte	0
	.uleb128 0xd
	.4byte	.LASF60
	.byte	0x5
	.2byte	0x281
	.byte	0x3
	.4byte	0x360
	.uleb128 0xa
	.byte	0x98
	.byte	0x5
	.2byte	0x29e
	.byte	0x9
	.4byte	0x768
	.uleb128 0xb
	.ascii	"CR\000"
	.byte	0x5
	.2byte	0x2a0
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xc
	.4byte	.LASF61
	.byte	0x5
	.2byte	0x2a1
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xc
	.4byte	.LASF62
	.byte	0x5
	.2byte	0x2a2
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xc
	.4byte	.LASF63
	.byte	0x5
	.2byte	0x2a3
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0xc
	.4byte	.LASF64
	.byte	0x5
	.2byte	0x2a4
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xc
	.4byte	.LASF65
	.byte	0x5
	.2byte	0x2a5
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0xc
	.4byte	.LASF66
	.byte	0x5
	.2byte	0x2a6
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xc
	.4byte	.LASF67
	.byte	0x5
	.2byte	0x2a7
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0xc
	.4byte	.LASF68
	.byte	0x5
	.2byte	0x2a8
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xc
	.4byte	.LASF69
	.byte	0x5
	.2byte	0x2a9
	.byte	0x11
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0xc
	.4byte	.LASF70
	.byte	0x5
	.2byte	0x2aa
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xc
	.4byte	.LASF71
	.byte	0x5
	.2byte	0x2ab
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0xc
	.4byte	.LASF72
	.byte	0x5
	.2byte	0x2ac
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xc
	.4byte	.LASF23
	.byte	0x5
	.2byte	0x2ad
	.byte	0x11
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.uleb128 0xc
	.4byte	.LASF73
	.byte	0x5
	.2byte	0x2ae
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0xc
	.4byte	.LASF74
	.byte	0x5
	.2byte	0x2af
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x3c
	.uleb128 0xc
	.4byte	.LASF75
	.byte	0x5
	.2byte	0x2b0
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0xc
	.4byte	.LASF29
	.byte	0x5
	.2byte	0x2b1
	.byte	0x11
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x44
	.uleb128 0xc
	.4byte	.LASF76
	.byte	0x5
	.2byte	0x2b2
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0xc
	.4byte	.LASF77
	.byte	0x5
	.2byte	0x2b3
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x4c
	.uleb128 0xc
	.4byte	.LASF78
	.byte	0x5
	.2byte	0x2b4
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0xc
	.4byte	.LASF79
	.byte	0x5
	.2byte	0x2b5
	.byte	0x11
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x54
	.uleb128 0xc
	.4byte	.LASF80
	.byte	0x5
	.2byte	0x2b6
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0xc
	.4byte	.LASF81
	.byte	0x5
	.2byte	0x2b7
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x5c
	.uleb128 0xc
	.4byte	.LASF82
	.byte	0x5
	.2byte	0x2b8
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x60
	.uleb128 0xc
	.4byte	.LASF83
	.byte	0x5
	.2byte	0x2b9
	.byte	0x11
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x64
	.uleb128 0xc
	.4byte	.LASF84
	.byte	0x5
	.2byte	0x2ba
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x68
	.uleb128 0xc
	.4byte	.LASF85
	.byte	0x5
	.2byte	0x2bb
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x6c
	.uleb128 0xc
	.4byte	.LASF86
	.byte	0x5
	.2byte	0x2bc
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x70
	.uleb128 0xc
	.4byte	.LASF87
	.byte	0x5
	.2byte	0x2bd
	.byte	0x11
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x74
	.uleb128 0xc
	.4byte	.LASF88
	.byte	0x5
	.2byte	0x2be
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x78
	.uleb128 0xc
	.4byte	.LASF89
	.byte	0x5
	.2byte	0x2bf
	.byte	0x11
	.4byte	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x7c
	.uleb128 0xc
	.4byte	.LASF90
	.byte	0x5
	.2byte	0x2c0
	.byte	0x11
	.4byte	0xbc
	.byte	0x3
	.byte	0x23
	.uleb128 0x80
	.uleb128 0xc
	.4byte	.LASF91
	.byte	0x5
	.2byte	0x2c1
	.byte	0x11
	.4byte	0xb0
	.byte	0x3
	.byte	0x23
	.uleb128 0x84
	.uleb128 0xc
	.4byte	.LASF92
	.byte	0x5
	.2byte	0x2c2
	.byte	0x11
	.4byte	0xbc
	.byte	0x3
	.byte	0x23
	.uleb128 0x88
	.uleb128 0xc
	.4byte	.LASF93
	.byte	0x5
	.2byte	0x2c3
	.byte	0x11
	.4byte	0xb0
	.byte	0x3
	.byte	0x23
	.uleb128 0x8c
	.uleb128 0xc
	.4byte	.LASF94
	.byte	0x5
	.2byte	0x2c4
	.byte	0x11
	.4byte	0xbc
	.byte	0x3
	.byte	0x23
	.uleb128 0x90
	.uleb128 0xb
	.ascii	"CSR\000"
	.byte	0x5
	.2byte	0x2c5
	.byte	0x11
	.4byte	0xbc
	.byte	0x3
	.byte	0x23
	.uleb128 0x94
	.byte	0
	.uleb128 0xd
	.4byte	.LASF95
	.byte	0x5
	.2byte	0x2c6
	.byte	0x3
	.4byte	0x4f8
	.uleb128 0xe
	.byte	0x7
	.byte	0x1
	.4byte	0x3c
	.byte	0x6
	.byte	0xba
	.byte	0x1
	.4byte	0x790
	.uleb128 0xf
	.4byte	.LASF96
	.byte	0
	.uleb128 0x10
	.ascii	"SET\000"
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF97
	.byte	0x6
	.byte	0xbd
	.byte	0x3
	.4byte	0x775
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF98
	.uleb128 0xe
	.byte	0x7
	.byte	0x1
	.4byte	0x3c
	.byte	0x7
	.byte	0x27
	.byte	0x1
	.4byte	0x7ca
	.uleb128 0xf
	.4byte	.LASF99
	.byte	0
	.uleb128 0xf
	.4byte	.LASF100
	.byte	0x1
	.uleb128 0xf
	.4byte	.LASF101
	.byte	0x2
	.uleb128 0xf
	.4byte	.LASF102
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF103
	.byte	0x7
	.byte	0x2c
	.byte	0x3
	.4byte	0x7a3
	.uleb128 0x11
	.byte	0x1c
	.byte	0x8
	.byte	0x2d
	.byte	0x9
	.4byte	0x849
	.uleb128 0x12
	.4byte	.LASF104
	.byte	0x8
	.byte	0x2f
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x12
	.4byte	.LASF105
	.byte	0x8
	.byte	0x32
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x12
	.4byte	.LASF106
	.byte	0x8
	.byte	0x35
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x12
	.4byte	.LASF107
	.byte	0x8
	.byte	0x39
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x12
	.4byte	.LASF108
	.byte	0x8
	.byte	0x3d
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x12
	.4byte	.LASF109
	.byte	0x8
	.byte	0x41
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x12
	.4byte	.LASF110
	.byte	0x8
	.byte	0x44
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.byte	0
	.uleb128 0x3
	.4byte	.LASF111
	.byte	0x8
	.byte	0x49
	.byte	0x2
	.4byte	0x7d6
	.uleb128 0x11
	.byte	0x44
	.byte	0x8
	.byte	0x4e
	.byte	0x9
	.4byte	0x904
	.uleb128 0x12
	.4byte	.LASF112
	.byte	0x8
	.byte	0x50
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x12
	.4byte	.LASF113
	.byte	0x8
	.byte	0x53
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x12
	.4byte	.LASF114
	.byte	0x8
	.byte	0x56
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x12
	.4byte	.LASF115
	.byte	0x8
	.byte	0x59
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x12
	.4byte	.LASF116
	.byte	0x8
	.byte	0x5c
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x12
	.4byte	.LASF117
	.byte	0x8
	.byte	0x62
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x12
	.4byte	.LASF118
	.byte	0x8
	.byte	0x6a
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x12
	.4byte	.LASF119
	.byte	0x8
	.byte	0x6d
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0x12
	.4byte	.LASF120
	.byte	0x8
	.byte	0x70
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0x12
	.4byte	.LASF121
	.byte	0x8
	.byte	0x73
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0x13
	.ascii	"PLL\000"
	.byte	0x8
	.byte	0x76
	.byte	0x16
	.4byte	0x849
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.4byte	.LASF122
	.byte	0x8
	.byte	0x78
	.byte	0x2
	.4byte	0x855
	.uleb128 0x11
	.byte	0x14
	.byte	0x8
	.byte	0x7d
	.byte	0x9
	.4byte	0x965
	.uleb128 0x12
	.4byte	.LASF123
	.byte	0x8
	.byte	0x7f
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x12
	.4byte	.LASF124
	.byte	0x8
	.byte	0x82
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x12
	.4byte	.LASF125
	.byte	0x8
	.byte	0x85
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x12
	.4byte	.LASF126
	.byte	0x8
	.byte	0x88
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x12
	.4byte	.LASF127
	.byte	0x8
	.byte	0x8b
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.byte	0
	.uleb128 0x3
	.4byte	.LASF128
	.byte	0x8
	.byte	0x8e
	.byte	0x2
	.4byte	0x910
	.uleb128 0x11
	.byte	0x14
	.byte	0x9
	.byte	0x2e
	.byte	0x9
	.4byte	0x9c6
	.uleb128 0x13
	.ascii	"Pin\000"
	.byte	0x9
	.byte	0x30
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x12
	.4byte	.LASF129
	.byte	0x9
	.byte	0x33
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x12
	.4byte	.LASF130
	.byte	0x9
	.byte	0x36
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x12
	.4byte	.LASF131
	.byte	0x9
	.byte	0x39
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x12
	.4byte	.LASF132
	.byte	0x9
	.byte	0x3c
	.byte	0xc
	.4byte	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.byte	0
	.uleb128 0x3
	.4byte	.LASF133
	.byte	0x9
	.byte	0x3e
	.byte	0x3
	.4byte	0x971
	.uleb128 0x14
	.4byte	.LASF134
	.byte	0xa
	.2byte	0x26b
	.byte	0x11
	.4byte	0xb0
	.byte	0x1
	.byte	0x1
	.uleb128 0x15
	.byte	0x1
	.4byte	.LASF176
	.byte	0x9
	.2byte	0x11b
	.byte	0x13
	.byte	0x1
	.byte	0x1
	.4byte	0x9fc
	.uleb128 0x16
	.4byte	0x9fc
	.uleb128 0x16
	.4byte	0xa02
	.byte	0
	.uleb128 0x17
	.byte	0x4
	.4byte	0x353
	.uleb128 0x17
	.byte	0x4
	.4byte	0x9c6
	.uleb128 0x18
	.byte	0x1
	.4byte	.LASF135
	.byte	0xb
	.2byte	0x344
	.byte	0xa
	.byte	0x1
	.4byte	0xb0
	.byte	0x1
	.uleb128 0x19
	.byte	0x1
	.4byte	.LASF177
	.byte	0xa
	.2byte	0x280
	.byte	0x13
	.byte	0x1
	.4byte	0x7ca
	.byte	0x1
	.4byte	0xa32
	.uleb128 0x16
	.4byte	0xb0
	.byte	0
	.uleb128 0x18
	.byte	0x1
	.4byte	.LASF136
	.byte	0xa
	.2byte	0x28d
	.byte	0x14
	.byte	0x1
	.4byte	0xb0
	.byte	0x1
	.uleb128 0x1a
	.4byte	.LASF178
	.byte	0x1
	.2byte	0x6fb
	.byte	0x1a
	.byte	0x1
	.4byte	0x7ca
	.4byte	.LFB88
	.4byte	.LFE88
	.4byte	.LLST0
	.byte	0x1
	.4byte	0xad1
	.uleb128 0x1b
	.4byte	.LASF151
	.byte	0x1
	.2byte	0x6fb
	.byte	0x43
	.4byte	0xb0
	.4byte	.LLST1
	.4byte	.LVUS1
	.uleb128 0x1c
	.ascii	"vos\000"
	.byte	0x1
	.2byte	0x6fd
	.byte	0xc
	.4byte	0xb0
	.4byte	.LLST2
	.4byte	.LVUS2
	.uleb128 0x1d
	.4byte	.LASF137
	.byte	0x1
	.2byte	0x6fe
	.byte	0xc
	.4byte	0xb0
	.4byte	.LLST3
	.4byte	.LVUS3
	.uleb128 0x1e
	.4byte	.LBB2
	.4byte	.LBE2
	.4byte	0xabe
	.uleb128 0x1f
	.4byte	.LASF163
	.byte	0x1
	.2byte	0x706
	.byte	0x5
	.4byte	0xbc
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.byte	0
	.uleb128 0x20
	.4byte	.LVL2
	.4byte	0xa08
	.uleb128 0x20
	.4byte	.LVL4
	.4byte	0xa08
	.byte	0
	.uleb128 0x21
	.byte	0x1
	.4byte	.LASF147
	.byte	0x1
	.2byte	0x6dd
	.byte	0xa
	.byte	0x1
	.4byte	0xb0
	.4byte	.LFB87
	.4byte	.LFE87
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0xb06
	.uleb128 0x1d
	.4byte	.LASF138
	.byte	0x1
	.2byte	0x6df
	.byte	0xc
	.4byte	0xb0
	.4byte	.LLST33
	.4byte	.LVUS33
	.byte	0
	.uleb128 0x22
	.byte	0x1
	.4byte	.LASF139
	.byte	0x1
	.2byte	0x6cf
	.byte	0xd
	.byte	0x1
	.4byte	.LFB86
	.4byte	.LFE86
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x23
	.byte	0x1
	.4byte	.LASF141
	.byte	0x1
	.2byte	0x6be
	.byte	0x6
	.byte	0x1
	.4byte	.LFB85
	.4byte	.LFE85
	.4byte	.LLST32
	.byte	0x1
	.4byte	0xb43
	.uleb128 0x20
	.4byte	.LVL168
	.4byte	0xb06
	.byte	0
	.uleb128 0x22
	.byte	0x1
	.4byte	.LASF140
	.byte	0x1
	.2byte	0x6b4
	.byte	0x6
	.byte	0x1
	.4byte	.LFB84
	.4byte	.LFE84
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x24
	.byte	0x1
	.4byte	.LASF142
	.byte	0x1
	.2byte	0x691
	.byte	0x6
	.byte	0x1
	.4byte	.LFB83
	.4byte	.LFE83
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0xb94
	.uleb128 0x25
	.4byte	.LASF143
	.byte	0x1
	.2byte	0x691
	.byte	0x32
	.4byte	0xb94
	.byte	0x1
	.byte	0x50
	.uleb128 0x25
	.4byte	.LASF144
	.byte	0x1
	.2byte	0x691
	.byte	0x4f
	.4byte	0xb9a
	.byte	0x1
	.byte	0x51
	.byte	0
	.uleb128 0x17
	.byte	0x4
	.4byte	0x965
	.uleb128 0x17
	.byte	0x4
	.4byte	0xb0
	.uleb128 0x24
	.byte	0x1
	.4byte	.LASF145
	.byte	0x1
	.2byte	0x5f2
	.byte	0x6
	.byte	0x1
	.4byte	.LFB82
	.4byte	.LFE82
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0xbcb
	.uleb128 0x25
	.4byte	.LASF146
	.byte	0x1
	.2byte	0x5f2
	.byte	0x30
	.4byte	0xbcb
	.byte	0x1
	.byte	0x50
	.byte	0
	.uleb128 0x17
	.byte	0x4
	.4byte	0x904
	.uleb128 0x26
	.byte	0x1
	.4byte	.LASF148
	.byte	0x1
	.2byte	0x5e5
	.byte	0xa
	.byte	0x1
	.4byte	0xb0
	.4byte	.LFB81
	.4byte	.LFE81
	.4byte	.LLST31
	.byte	0x1
	.4byte	0xbfb
	.uleb128 0x20
	.4byte	.LVL165
	.4byte	0xc25
	.byte	0
	.uleb128 0x26
	.byte	0x1
	.4byte	.LASF149
	.byte	0x1
	.2byte	0x5d9
	.byte	0xa
	.byte	0x1
	.4byte	0xb0
	.4byte	.LFB80
	.4byte	.LFE80
	.4byte	.LLST30
	.byte	0x1
	.4byte	0xc25
	.uleb128 0x20
	.4byte	.LVL164
	.4byte	0xc25
	.byte	0
	.uleb128 0x27
	.byte	0x1
	.4byte	.LASF179
	.byte	0x1
	.2byte	0x5ce
	.byte	0xa
	.byte	0x1
	.4byte	0xb0
	.4byte	.LFB79
	.4byte	.LFE79
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x21
	.byte	0x1
	.4byte	.LASF150
	.byte	0x1
	.2byte	0x576
	.byte	0xa
	.byte	0x1
	.4byte	0xb0
	.4byte	.LFB78
	.4byte	.LFE78
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0xd08
	.uleb128 0x1d
	.4byte	.LASF151
	.byte	0x1
	.2byte	0x578
	.byte	0xc
	.4byte	0xb0
	.4byte	.LLST10
	.4byte	.LVUS10
	.uleb128 0x1d
	.4byte	.LASF152
	.byte	0x1
	.2byte	0x578
	.byte	0x1b
	.4byte	0xb0
	.4byte	.LLST11
	.4byte	.LVUS11
	.uleb128 0x1d
	.4byte	.LASF153
	.byte	0x1
	.2byte	0x579
	.byte	0xc
	.4byte	0xb0
	.4byte	.LLST12
	.4byte	.LVUS12
	.uleb128 0x1d
	.4byte	.LASF154
	.byte	0x1
	.2byte	0x579
	.byte	0x14
	.4byte	0xb0
	.4byte	.LLST13
	.4byte	.LVUS13
	.uleb128 0x1d
	.4byte	.LASF155
	.byte	0x1
	.2byte	0x579
	.byte	0x1f
	.4byte	0xb0
	.4byte	.LLST14
	.4byte	.LVUS14
	.uleb128 0x1d
	.4byte	.LASF156
	.byte	0x1
	.2byte	0x579
	.byte	0x25
	.4byte	0xb0
	.4byte	.LLST15
	.4byte	.LVUS15
	.uleb128 0x1d
	.4byte	.LASF157
	.byte	0x1
	.2byte	0x57a
	.byte	0xc
	.4byte	0xb0
	.4byte	.LLST16
	.4byte	.LVUS16
	.uleb128 0x1d
	.4byte	.LASF158
	.byte	0x1
	.2byte	0x57a
	.byte	0x1b
	.4byte	0xb0
	.4byte	.LLST17
	.4byte	.LVUS17
	.byte	0
	.uleb128 0x23
	.byte	0x1
	.4byte	.LASF159
	.byte	0x1
	.2byte	0x53b
	.byte	0x6
	.byte	0x1
	.4byte	.LFB77
	.4byte	.LFE77
	.4byte	.LLST6
	.byte	0x1
	.4byte	0xda9
	.uleb128 0x1b
	.4byte	.LASF160
	.byte	0x1
	.2byte	0x53b
	.byte	0x22
	.4byte	0xb0
	.4byte	.LLST7
	.4byte	.LVUS7
	.uleb128 0x1b
	.4byte	.LASF161
	.byte	0x1
	.2byte	0x53b
	.byte	0x35
	.4byte	0xb0
	.4byte	.LLST8
	.4byte	.LVUS8
	.uleb128 0x1b
	.4byte	.LASF162
	.byte	0x1
	.2byte	0x53b
	.byte	0x4d
	.4byte	0xb0
	.4byte	.LLST9
	.4byte	.LVUS9
	.uleb128 0x1f
	.4byte	.LASF164
	.byte	0x1
	.2byte	0x53d
	.byte	0x14
	.4byte	0x9c6
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x1e
	.4byte	.LBB3
	.4byte	.LBE3
	.4byte	0xd91
	.uleb128 0x1f
	.4byte	.LASF163
	.byte	0x1
	.2byte	0x548
	.byte	0x3
	.4byte	0xbc
	.byte	0x2
	.byte	0x91
	.sleb128 -40
	.byte	0
	.uleb128 0x28
	.4byte	.LVL26
	.4byte	0x9e1
	.uleb128 0x29
	.byte	0x1
	.byte	0x50
	.byte	0x3
	.byte	0x42
	.byte	0x4a
	.byte	0x24
	.uleb128 0x29
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.byte	0
	.byte	0
	.uleb128 0x26
	.byte	0x1
	.4byte	.LASF165
	.byte	0x1
	.2byte	0x449
	.byte	0x13
	.byte	0x1
	.4byte	0x7ca
	.4byte	.LFB76
	.4byte	.LFE76
	.4byte	.LLST25
	.byte	0x1
	.4byte	0xe42
	.uleb128 0x1b
	.4byte	.LASF143
	.byte	0x1
	.2byte	0x449
	.byte	0x3c
	.4byte	0xb94
	.4byte	.LLST26
	.4byte	.LVUS26
	.uleb128 0x1b
	.4byte	.LASF166
	.byte	0x1
	.2byte	0x449
	.byte	0x58
	.4byte	0xb0
	.4byte	.LLST27
	.4byte	.LVUS27
	.uleb128 0x1d
	.4byte	.LASF167
	.byte	0x1
	.2byte	0x44b
	.byte	0xc
	.4byte	0xb0
	.4byte	.LLST28
	.4byte	.LVUS28
	.uleb128 0x1d
	.4byte	.LASF168
	.byte	0x1
	.2byte	0x450
	.byte	0x15
	.4byte	0x7ca
	.4byte	.LLST29
	.4byte	.LVUS29
	.uleb128 0x20
	.4byte	.LVL149
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL151
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL156
	.4byte	0xc40
	.uleb128 0x20
	.4byte	.LVL157
	.4byte	0xa18
	.byte	0
	.uleb128 0x26
	.byte	0x1
	.4byte	.LASF169
	.byte	0x1
	.2byte	0x195
	.byte	0x13
	.byte	0x1
	.4byte	0x7ca
	.4byte	.LFB75
	.4byte	.LFE75
	.4byte	.LLST18
	.byte	0x1
	.4byte	0x103b
	.uleb128 0x1b
	.4byte	.LASF146
	.byte	0x1
	.2byte	0x195
	.byte	0x3a
	.4byte	0xbcb
	.4byte	.LLST19
	.4byte	.LVUS19
	.uleb128 0x1d
	.4byte	.LASF167
	.byte	0x1
	.2byte	0x197
	.byte	0xc
	.4byte	0xb0
	.4byte	.LLST20
	.4byte	.LVUS20
	.uleb128 0x1d
	.4byte	.LASF168
	.byte	0x1
	.2byte	0x198
	.byte	0x15
	.4byte	0x7ca
	.4byte	.LLST21
	.4byte	.LVUS21
	.uleb128 0x1d
	.4byte	.LASF157
	.byte	0x1
	.2byte	0x199
	.byte	0xc
	.4byte	0xb0
	.4byte	.LLST22
	.4byte	.LVUS22
	.uleb128 0x1d
	.4byte	.LASF170
	.byte	0x1
	.2byte	0x199
	.byte	0x1b
	.4byte	0xb0
	.4byte	.LLST23
	.4byte	.LVUS23
	.uleb128 0x2a
	.4byte	.Ldebug_ranges0+0
	.4byte	0xf3e
	.uleb128 0x1d
	.4byte	.LASF171
	.byte	0x1
	.2byte	0x2dd
	.byte	0x16
	.4byte	0x790
	.4byte	.LLST24
	.4byte	.LVUS24
	.uleb128 0x1e
	.4byte	.LBB5
	.4byte	.LBE5
	.4byte	0xf07
	.uleb128 0x1f
	.4byte	.LASF163
	.byte	0x1
	.2byte	0x2e6
	.byte	0x7
	.4byte	0xbc
	.byte	0x2
	.byte	0x91
	.sleb128 -28
	.byte	0
	.uleb128 0x20
	.4byte	.LVL106
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL108
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL111
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL113
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL115
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL117
	.4byte	0xa32
	.byte	0
	.uleb128 0x20
	.4byte	.LVL62
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL64
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL67
	.4byte	0xc40
	.uleb128 0x20
	.4byte	.LVL68
	.4byte	0xa18
	.uleb128 0x20
	.4byte	.LVL70
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL72
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL74
	.4byte	0xa42
	.uleb128 0x20
	.4byte	.LVL75
	.4byte	0xa42
	.uleb128 0x20
	.4byte	.LVL78
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL80
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL82
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL84
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL86
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL88
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL91
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL93
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL95
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL97
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL99
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL101
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL119
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL121
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL128
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL130
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL131
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL133
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL135
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL137
	.4byte	0xa32
	.byte	0
	.uleb128 0x2b
	.byte	0x1
	.4byte	.LASF172
	.byte	0x1
	.2byte	0x109
	.byte	0x13
	.byte	0x1
	.4byte	0x7ca
	.4byte	.LFB74
	.4byte	.LFE74
	.4byte	.LLST4
	.byte	0x1
	.uleb128 0x1d
	.4byte	.LASF167
	.byte	0x1
	.2byte	0x10b
	.byte	0xc
	.4byte	0xb0
	.4byte	.LLST5
	.4byte	.LVUS5
	.uleb128 0x20
	.4byte	.LVL10
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL12
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL15
	.4byte	0xa18
	.uleb128 0x20
	.4byte	.LVL17
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL19
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL20
	.4byte	0xa32
	.uleb128 0x20
	.4byte	.LVL22
	.4byte	0xa32
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
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
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
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
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
	.uleb128 0xb
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
	.uleb128 0xc
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
	.uleb128 0xd
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
	.uleb128 0xe
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
	.uleb128 0xf
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x11
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
	.uleb128 0x12
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
	.uleb128 0x13
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
	.uleb128 0x14
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
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
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
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
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
	.uleb128 0x19
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
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0x1
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
	.uleb128 0x1f
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
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
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
	.uleb128 0x22
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
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x23
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
	.uleb128 0x24
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
	.uleb128 0x25
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
	.uleb128 0x27
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
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
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
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LFB88
	.4byte	.LCFI0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI0
	.4byte	.LCFI1
	.2byte	0x2
	.byte	0x7d
	.sleb128 12
	.4byte	.LCFI1
	.4byte	.LCFI2
	.2byte	0x2
	.byte	0x7d
	.sleb128 24
	.4byte	.LCFI2
	.4byte	.LCFI3
	.2byte	0x2
	.byte	0x7d
	.sleb128 12
	.4byte	.LCFI3
	.4byte	.LFE88
	.2byte	0x2
	.byte	0x7d
	.sleb128 24
	.4byte	0
	.4byte	0
.LVUS1:
	.uleb128 0
	.uleb128 .LVU9
	.uleb128 .LVU9
	.uleb128 .LVU18
	.uleb128 .LVU18
	.uleb128 .LVU26
	.uleb128 .LVU26
	.uleb128 0
.LLST1:
	.4byte	.LVL0
	.4byte	.LVL2-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL2-1
	.4byte	.LVL3
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL3
	.4byte	.LVL4-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL4-1
	.4byte	.LFE88
	.2byte	0x1
	.byte	0x54
	.4byte	0
	.4byte	0
.LVUS2:
	.uleb128 .LVU9
	.uleb128 .LVU18
	.uleb128 .LVU26
	.uleb128 .LVU41
	.uleb128 .LVU42
	.uleb128 .LVU45
.LLST2:
	.4byte	.LVL2
	.4byte	.LVL3
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL4
	.4byte	.LVL6
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL7
	.4byte	.LVL9
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LVUS3:
	.uleb128 .LVU4
	.uleb128 .LVU35
	.uleb128 .LVU35
	.uleb128 .LVU42
	.uleb128 .LVU42
	.uleb128 .LVU44
	.uleb128 .LVU44
	.uleb128 0
.LLST3:
	.4byte	.LVL1
	.4byte	.LVL5
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL5
	.4byte	.LVL7
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL7
	.4byte	.LVL8
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL8
	.4byte	.LFE88
	.2byte	0x1
	.byte	0x51
	.4byte	0
	.4byte	0
.LVUS33:
	.uleb128 .LVU892
	.uleb128 .LVU897
	.uleb128 .LVU897
	.uleb128 0
.LLST33:
	.4byte	.LVL169
	.4byte	.LVL170
	.2byte	0x8
	.byte	0x70
	.sleb128 0
	.byte	0x40
	.byte	0x45
	.byte	0x24
	.byte	0x1f
	.byte	0x1a
	.byte	0x9f
	.4byte	.LVL170
	.4byte	.LFE87
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LLST32:
	.4byte	.LFB85
	.4byte	.LCFI19
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI19
	.4byte	.LFE85
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LLST31:
	.4byte	.LFB81
	.4byte	.LCFI18
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI18
	.4byte	.LFE81
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LLST30:
	.4byte	.LFB80
	.4byte	.LCFI17
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI17
	.4byte	.LFE80
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LVUS10:
	.uleb128 .LVU137
	.uleb128 .LVU163
	.uleb128 .LVU163
	.uleb128 .LVU171
	.uleb128 .LVU172
	.uleb128 .LVU175
	.uleb128 .LVU175
	.uleb128 .LVU177
	.uleb128 .LVU177
	.uleb128 .LVU183
	.uleb128 .LVU183
	.uleb128 .LVU189
	.uleb128 .LVU207
	.uleb128 .LVU208
.LLST10:
	.4byte	.LVL29
	.4byte	.LVL36
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL36
	.4byte	.LVL39
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL40
	.4byte	.LVL41
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL41
	.4byte	.LVL42
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL42
	.4byte	.LVL46
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL46
	.4byte	.LVL49
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL57
	.4byte	.LVL58
	.2byte	0x1
	.byte	0x52
	.4byte	0
	.4byte	0
.LVUS11:
	.uleb128 .LVU137
	.uleb128 .LVU168
	.uleb128 .LVU168
	.uleb128 .LVU172
	.uleb128 .LVU172
	.uleb128 .LVU183
	.uleb128 .LVU183
	.uleb128 .LVU195
	.uleb128 .LVU205
	.uleb128 0
.LLST11:
	.4byte	.LVL29
	.4byte	.LVL38
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL38
	.4byte	.LVL40
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL40
	.4byte	.LVL46
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL46
	.4byte	.LVL52
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL56
	.4byte	.LFE78
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LVUS12:
	.uleb128 .LVU189
	.uleb128 .LVU198
	.uleb128 .LVU198
	.uleb128 .LVU205
.LLST12:
	.4byte	.LVL49
	.4byte	.LVL53
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL53
	.4byte	.LVL56
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LVUS13:
	.uleb128 .LVU187
	.uleb128 .LVU191
	.uleb128 .LVU207
	.uleb128 0
.LLST13:
	.4byte	.LVL48
	.4byte	.LVL50
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL57
	.4byte	.LFE78
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LVUS14:
	.uleb128 .LVU203
	.uleb128 .LVU207
.LLST14:
	.4byte	.LVL55
	.4byte	.LVL57
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LVUS15:
	.uleb128 .LVU193
	.uleb128 .LVU200
.LLST15:
	.4byte	.LVL51
	.4byte	.LVL54
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LVUS16:
	.uleb128 .LVU141
	.uleb128 .LVU146
	.uleb128 .LVU146
	.uleb128 .LVU171
	.uleb128 .LVU172
	.uleb128 .LVU185
.LLST16:
	.4byte	.LVL30
	.4byte	.LVL32
	.2byte	0x5
	.byte	0x73
	.sleb128 0
	.byte	0x3c
	.byte	0x1a
	.byte	0x9f
	.4byte	.LVL32
	.4byte	.LVL39
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL40
	.4byte	.LVL47
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LVUS17:
	.uleb128 .LVU144
	.uleb128 .LVU154
	.uleb128 .LVU155
	.uleb128 .LVU158
	.uleb128 .LVU177
	.uleb128 .LVU179
	.uleb128 .LVU180
	.uleb128 .LVU182
.LLST17:
	.4byte	.LVL31
	.4byte	.LVL33
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL34
	.4byte	.LVL35
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL42
	.4byte	.LVL43
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL44
	.4byte	.LVL45
	.2byte	0x1
	.byte	0x52
	.4byte	0
	.4byte	0
.LLST6:
	.4byte	.LFB77
	.4byte	.LCFI5
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI5
	.4byte	.LCFI6
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	.LCFI6
	.4byte	.LCFI7
	.2byte	0x2
	.byte	0x7d
	.sleb128 40
	.4byte	.LCFI7
	.4byte	.LFE77
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	0
	.4byte	0
.LVUS7:
	.uleb128 0
	.uleb128 .LVU130
	.uleb128 .LVU130
	.uleb128 0
.LLST7:
	.4byte	.LVL23
	.4byte	.LVL25
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL25
	.4byte	.LFE77
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS8:
	.uleb128 0
	.uleb128 .LVU129
	.uleb128 .LVU129
	.uleb128 .LVU132
	.uleb128 .LVU132
	.uleb128 0
.LLST8:
	.4byte	.LVL23
	.4byte	.LVL24
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL24
	.4byte	.LVL27
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL27
	.4byte	.LFE77
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS9:
	.uleb128 0
	.uleb128 .LVU131
	.uleb128 .LVU131
	.uleb128 .LVU134
	.uleb128 .LVU134
	.uleb128 0
.LLST9:
	.4byte	.LVL23
	.4byte	.LVL26-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL26-1
	.4byte	.LVL28
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL28
	.4byte	.LFE77
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST25:
	.4byte	.LFB76
	.4byte	.LCFI14
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI14
	.4byte	.LCFI15
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	.LCFI15
	.4byte	.LCFI16
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI16
	.4byte	.LFE76
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	0
	.4byte	0
.LVUS26:
	.uleb128 0
	.uleb128 .LVU661
	.uleb128 .LVU661
	.uleb128 .LVU662
	.uleb128 .LVU662
	.uleb128 .LVU668
	.uleb128 .LVU668
	.uleb128 .LVU679
	.uleb128 .LVU679
	.uleb128 .LVU683
	.uleb128 .LVU683
	.uleb128 .LVU684
	.uleb128 .LVU684
	.uleb128 .LVU688
	.uleb128 .LVU688
	.uleb128 .LVU726
	.uleb128 .LVU726
	.uleb128 .LVU727
	.uleb128 .LVU727
	.uleb128 .LVU728
	.uleb128 .LVU728
	.uleb128 .LVU729
	.uleb128 .LVU729
	.uleb128 .LVU730
	.uleb128 .LVU730
	.uleb128 .LVU731
	.uleb128 .LVU731
	.uleb128 0
.LLST26:
	.4byte	.LVL145
	.4byte	.LVL147
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL147
	.4byte	.LVL148
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL148
	.4byte	.LVL149-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL149-1
	.4byte	.LVL152
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL152
	.4byte	.LVL153
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL153
	.4byte	.LVL154
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL154
	.4byte	.LVL155
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL155
	.4byte	.LVL158
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL158
	.4byte	.LVL159
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL159
	.4byte	.LVL160
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL160
	.4byte	.LVL161
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL161
	.4byte	.LVL162
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL162
	.4byte	.LVL163
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL163
	.4byte	.LFE76
	.2byte	0x1
	.byte	0x54
	.4byte	0
	.4byte	0
.LVUS27:
	.uleb128 0
	.uleb128 .LVU645
	.uleb128 .LVU645
	.uleb128 .LVU726
	.uleb128 .LVU726
	.uleb128 .LVU730
	.uleb128 .LVU730
	.uleb128 0
.LLST27:
	.4byte	.LVL145
	.4byte	.LVL146
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL146
	.4byte	.LVL158
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL158
	.4byte	.LVL162
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL162
	.4byte	.LFE76
	.2byte	0x1
	.byte	0x55
	.4byte	0
	.4byte	0
.LVUS28:
	.uleb128 .LVU669
	.uleb128 .LVU670
	.uleb128 .LVU670
	.uleb128 .LVU679
.LLST28:
	.4byte	.LVL150
	.4byte	.LVL150
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL150
	.4byte	.LVL152
	.2byte	0x1
	.byte	0x56
	.4byte	0
	.4byte	0
.LVUS29:
	.uleb128 .LVU724
	.uleb128 .LVU725
.LLST29:
	.4byte	.LVL157
	.4byte	.LVL157
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LLST18:
	.4byte	.LFB75
	.4byte	.LCFI8
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI8
	.4byte	.LCFI9
	.2byte	0x2
	.byte	0x7d
	.sleb128 20
	.4byte	.LCFI9
	.4byte	.LCFI10
	.2byte	0x2
	.byte	0x7d
	.sleb128 32
	.4byte	.LCFI10
	.4byte	.LCFI11
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI11
	.4byte	.LCFI12
	.2byte	0x2
	.byte	0x7d
	.sleb128 32
	.4byte	.LCFI12
	.4byte	.LCFI13
	.2byte	0x2
	.byte	0x7d
	.sleb128 20
	.4byte	.LCFI13
	.4byte	.LFE75
	.2byte	0x2
	.byte	0x7d
	.sleb128 32
	.4byte	0
	.4byte	0
.LVUS19:
	.uleb128 0
	.uleb128 .LVU238
	.uleb128 .LVU238
	.uleb128 .LVU248
	.uleb128 .LVU248
	.uleb128 .LVU256
	.uleb128 .LVU256
	.uleb128 .LVU323
	.uleb128 .LVU323
	.uleb128 .LVU326
	.uleb128 .LVU326
	.uleb128 .LVU508
	.uleb128 .LVU508
	.uleb128 .LVU517
	.uleb128 .LVU517
	.uleb128 .LVU581
	.uleb128 .LVU581
	.uleb128 .LVU591
	.uleb128 .LVU591
	.uleb128 .LVU595
	.uleb128 .LVU595
	.uleb128 .LVU609
	.uleb128 .LVU609
	.uleb128 .LVU610
	.uleb128 .LVU610
	.uleb128 .LVU611
	.uleb128 .LVU611
	.uleb128 .LVU612
	.uleb128 .LVU612
	.uleb128 .LVU617
	.uleb128 .LVU617
	.uleb128 .LVU618
	.uleb128 .LVU618
	.uleb128 0
.LLST19:
	.4byte	.LVL59
	.4byte	.LVL62-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL62-1
	.4byte	.LVL65
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL65
	.4byte	.LVL66
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL66
	.4byte	.LVL77
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL77
	.4byte	.LVL78-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL78-1
	.4byte	.LVL120
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL120
	.4byte	.LVL122
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL122
	.4byte	.LVL132
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL132
	.4byte	.LVL134
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL134
	.4byte	.LVL136
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL136
	.4byte	.LVL138
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL138
	.4byte	.LVL139
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL139
	.4byte	.LVL140
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL140
	.4byte	.LVL141
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL141
	.4byte	.LVL143
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL143
	.4byte	.LVL144
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL144
	.4byte	.LFE75
	.2byte	0x1
	.byte	0x54
	.4byte	0
	.4byte	0
.LVUS20:
	.uleb128 .LVU239
	.uleb128 .LVU240
	.uleb128 .LVU240
	.uleb128 .LVU248
	.uleb128 .LVU296
	.uleb128 .LVU297
	.uleb128 .LVU297
	.uleb128 .LVU305
	.uleb128 .LVU318
	.uleb128 .LVU323
	.uleb128 .LVU327
	.uleb128 .LVU328
	.uleb128 .LVU328
	.uleb128 .LVU336
	.uleb128 .LVU356
	.uleb128 .LVU357
	.uleb128 .LVU357
	.uleb128 .LVU365
	.uleb128 .LVU370
	.uleb128 .LVU371
	.uleb128 .LVU371
	.uleb128 .LVU379
	.uleb128 .LVU396
	.uleb128 .LVU397
	.uleb128 .LVU397
	.uleb128 .LVU406
	.uleb128 .LVU409
	.uleb128 .LVU410
	.uleb128 .LVU410
	.uleb128 .LVU418
	.uleb128 .LVU421
	.uleb128 .LVU422
	.uleb128 .LVU422
	.uleb128 .LVU430
	.uleb128 .LVU460
	.uleb128 .LVU461
	.uleb128 .LVU461
	.uleb128 .LVU469
	.uleb128 .LVU473
	.uleb128 .LVU474
	.uleb128 .LVU474
	.uleb128 .LVU480
	.uleb128 .LVU485
	.uleb128 .LVU486
	.uleb128 .LVU486
	.uleb128 .LVU496
	.uleb128 .LVU508
	.uleb128 .LVU509
	.uleb128 .LVU509
	.uleb128 .LVU517
	.uleb128 .LVU517
	.uleb128 .LVU518
	.uleb128 .LVU567
	.uleb128 .LVU568
	.uleb128 .LVU568
	.uleb128 .LVU581
	.uleb128 .LVU581
	.uleb128 .LVU582
	.uleb128 .LVU582
	.uleb128 .LVU591
	.uleb128 .LVU595
	.uleb128 .LVU596
	.uleb128 .LVU596
	.uleb128 .LVU609
.LLST20:
	.4byte	.LVL63
	.4byte	.LVL63
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL63
	.4byte	.LVL65
	.2byte	0x1
	.byte	0x57
	.4byte	.LVL71
	.4byte	.LVL71
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL71
	.4byte	.LVL73
	.2byte	0x1
	.byte	0x57
	.4byte	.LVL76
	.4byte	.LVL77
	.2byte	0x1
	.byte	0x57
	.4byte	.LVL79
	.4byte	.LVL79
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL79
	.4byte	.LVL81
	.2byte	0x1
	.byte	0x57
	.4byte	.LVL83
	.4byte	.LVL83
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL83
	.4byte	.LVL85
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL87
	.4byte	.LVL87
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL87
	.4byte	.LVL89
	.2byte	0x1
	.byte	0x57
	.4byte	.LVL92
	.4byte	.LVL92
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL92
	.4byte	.LVL94
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL96
	.4byte	.LVL96
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL96
	.4byte	.LVL98
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL100
	.4byte	.LVL100
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL100
	.4byte	.LVL102
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL107
	.4byte	.LVL107
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL107
	.4byte	.LVL109
	.2byte	0x1
	.byte	0x57
	.4byte	.LVL112
	.4byte	.LVL112
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL112
	.4byte	.LVL114
	.2byte	0x1
	.byte	0x57
	.4byte	.LVL116
	.4byte	.LVL116
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL116
	.4byte	.LVL118
	.2byte	0x1
	.byte	0x57
	.4byte	.LVL120
	.4byte	.LVL120
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL120
	.4byte	.LVL122
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL122
	.4byte	.LVL123
	.2byte	0x1
	.byte	0x57
	.4byte	.LVL129
	.4byte	.LVL129
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL129
	.4byte	.LVL132
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL132
	.4byte	.LVL132
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL132
	.4byte	.LVL134
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL136
	.4byte	.LVL136
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL136
	.4byte	.LVL138
	.2byte	0x1
	.byte	0x54
	.4byte	0
	.4byte	0
.LVUS21:
	.uleb128 .LVU276
	.uleb128 .LVU278
.LLST21:
	.4byte	.LVL68
	.4byte	.LVL69
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LVUS22:
	.uleb128 .LVU220
	.uleb128 .LVU567
	.uleb128 .LVU591
	.uleb128 .LVU609
	.uleb128 .LVU611
	.uleb128 .LVU617
	.uleb128 .LVU618
	.uleb128 0
.LLST22:
	.4byte	.LVL60
	.4byte	.LVL129
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL134
	.4byte	.LVL138
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL140
	.4byte	.LVL143
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL144
	.4byte	.LFE75
	.2byte	0x1
	.byte	0x55
	.4byte	0
	.4byte	0
.LVUS23:
	.uleb128 .LVU223
	.uleb128 .LVU356
	.uleb128 .LVU365
	.uleb128 .LVU386
	.uleb128 .LVU406
	.uleb128 .LVU409
	.uleb128 .LVU527
	.uleb128 .LVU531
	.uleb128 .LVU539
	.uleb128 .LVU556
	.uleb128 .LVU611
	.uleb128 .LVU616
.LLST23:
	.4byte	.LVL61
	.4byte	.LVL83
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL85
	.4byte	.LVL90
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL94
	.4byte	.LVL96
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL124
	.4byte	.LVL125
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL126
	.4byte	.LVL127
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL140
	.4byte	.LVL142
	.2byte	0x1
	.byte	0x56
	.4byte	0
	.4byte	0
.LVUS24:
	.uleb128 .LVU434
	.uleb128 .LVU445
	.uleb128 .LVU445
	.uleb128 .LVU446
	.uleb128 .LVU446
	.uleb128 .LVU469
	.uleb128 .LVU469
	.uleb128 .LVU470
	.uleb128 .LVU470
	.uleb128 .LVU496
	.uleb128 .LVU517
	.uleb128 .LVU518
.LLST24:
	.4byte	.LVL103
	.4byte	.LVL104
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL104
	.4byte	.LVL105
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	.LVL105
	.4byte	.LVL109
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL109
	.4byte	.LVL110
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL110
	.4byte	.LVL118
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL122
	.4byte	.LVL123
	.2byte	0x1
	.byte	0x56
	.4byte	0
	.4byte	0
.LLST4:
	.4byte	.LFB74
	.4byte	.LCFI4
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI4
	.4byte	.LFE74
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	0
	.4byte	0
.LVUS5:
	.uleb128 .LVU51
	.uleb128 .LVU52
	.uleb128 .LVU52
	.uleb128 .LVU60
	.uleb128 .LVU61
	.uleb128 .LVU68
	.uleb128 .LVU72
	.uleb128 .LVU73
	.uleb128 .LVU73
	.uleb128 .LVU84
	.uleb128 .LVU84
	.uleb128 .LVU85
	.uleb128 .LVU85
	.uleb128 0
.LLST5:
	.4byte	.LVL11
	.4byte	.LVL11
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL11
	.4byte	.LVL13
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL14
	.4byte	.LVL16
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL18
	.4byte	.LVL18
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL18
	.4byte	.LVL21
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL21
	.4byte	.LVL21
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL21
	.4byte	.LFE74
	.2byte	0x1
	.byte	0x55
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x8c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB88
	.4byte	.LFE88-.LFB88
	.4byte	.LFB74
	.4byte	.LFE74-.LFB74
	.4byte	.LFB77
	.4byte	.LFE77-.LFB77
	.4byte	.LFB78
	.4byte	.LFE78-.LFB78
	.4byte	.LFB75
	.4byte	.LFE75-.LFB75
	.4byte	.LFB76
	.4byte	.LFE76-.LFB76
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
	.4byte	.LFB86
	.4byte	.LFE86-.LFB86
	.4byte	.LFB85
	.4byte	.LFE85-.LFB85
	.4byte	.LFB87
	.4byte	.LFE87-.LFB87
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LBB4
	.4byte	.LBE4
	.4byte	.LBB6
	.4byte	.LBE6
	.4byte	0
	.4byte	0
	.4byte	.LFB88
	.4byte	.LFE88
	.4byte	.LFB74
	.4byte	.LFE74
	.4byte	.LFB77
	.4byte	.LFE77
	.4byte	.LFB78
	.4byte	.LFE78
	.4byte	.LFB75
	.4byte	.LFE75
	.4byte	.LFB76
	.4byte	.LFE76
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
	.4byte	.LFB86
	.4byte	.LFE86
	.4byte	.LFB85
	.4byte	.LFE85
	.4byte	.LFB87
	.4byte	.LFE87
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF139:
	.ascii	"HAL_RCC_CSSCallback\000"
.LASF138:
	.ascii	"reset\000"
.LASF30:
	.ascii	"PCROP2SR\000"
.LASF142:
	.ascii	"HAL_RCC_GetClockConfig\000"
.LASF97:
	.ascii	"FlagStatus\000"
.LASF45:
	.ascii	"PDCRA\000"
.LASF47:
	.ascii	"PDCRB\000"
.LASF49:
	.ascii	"PDCRC\000"
.LASF51:
	.ascii	"PDCRD\000"
.LASF53:
	.ascii	"PDCRE\000"
.LASF3:
	.ascii	"__uint8_t\000"
.LASF155:
	.ascii	"pllr\000"
.LASF36:
	.ascii	"OTYPER\000"
.LASF101:
	.ascii	"HAL_BUSY\000"
.LASF166:
	.ascii	"FLatency\000"
.LASF171:
	.ascii	"pwrclkchanged\000"
.LASF17:
	.ascii	"APBPrescTable\000"
.LASF106:
	.ascii	"PLLM\000"
.LASF107:
	.ascii	"PLLN\000"
.LASF108:
	.ascii	"PLLP\000"
.LASF109:
	.ascii	"PLLQ\000"
.LASF110:
	.ascii	"PLLR\000"
.LASF35:
	.ascii	"MODER\000"
.LASF10:
	.ascii	"long long unsigned int\000"
.LASF38:
	.ascii	"PUPDR\000"
.LASF55:
	.ascii	"PDCRF\000"
.LASF114:
	.ascii	"LSEState\000"
.LASF59:
	.ascii	"PDCRH\000"
.LASF73:
	.ascii	"APB1RSTR1\000"
.LASF132:
	.ascii	"Alternate\000"
.LASF122:
	.ascii	"RCC_OscInitTypeDef\000"
.LASF0:
	.ascii	"signed char\000"
.LASF168:
	.ascii	"status\000"
.LASF39:
	.ascii	"BSRR\000"
.LASF70:
	.ascii	"AHB1RSTR\000"
.LASF34:
	.ascii	"FLASH_TypeDef\000"
.LASF84:
	.ascii	"AHB1SMENR\000"
.LASF90:
	.ascii	"APB2SMENR\000"
.LASF44:
	.ascii	"PUCRA\000"
.LASF46:
	.ascii	"PUCRB\000"
.LASF48:
	.ascii	"PUCRC\000"
.LASF50:
	.ascii	"PUCRD\000"
.LASF52:
	.ascii	"PUCRE\000"
.LASF54:
	.ascii	"PUCRF\000"
.LASF56:
	.ascii	"PUCRG\000"
.LASF58:
	.ascii	"PUCRH\000"
.LASF6:
	.ascii	"long int\000"
.LASF75:
	.ascii	"APB2RSTR\000"
.LASF117:
	.ascii	"LSIState\000"
.LASF74:
	.ascii	"APB1RSTR2\000"
.LASF115:
	.ascii	"HSIState\000"
.LASF21:
	.ascii	"OPTKEYR\000"
.LASF57:
	.ascii	"PDCRG\000"
.LASF13:
	.ascii	"uint16_t\000"
.LASF116:
	.ascii	"HSICalibrationValue\000"
.LASF63:
	.ascii	"PLLCFGR\000"
.LASF32:
	.ascii	"WRP2AR\000"
.LASF126:
	.ascii	"APB1CLKDivider\000"
.LASF67:
	.ascii	"CIFR\000"
.LASF19:
	.ascii	"PDKEYR\000"
.LASF37:
	.ascii	"OSPEEDR\000"
.LASF7:
	.ascii	"__uint32_t\000"
.LASF31:
	.ascii	"PCROP2ER\000"
.LASF85:
	.ascii	"AHB2SMENR\000"
.LASF175:
	.ascii	"/home/emanuele/Desktop/CROSSCON/Repo/baremetal-tee/"
	.ascii	"MPU-version/apps/keylogger/Debug\000"
.LASF20:
	.ascii	"KEYR\000"
.LASF25:
	.ascii	"PCROP1SR\000"
.LASF9:
	.ascii	"long long int\000"
.LASF143:
	.ascii	"RCC_ClkInitStruct\000"
.LASF153:
	.ascii	"pllvco\000"
.LASF113:
	.ascii	"HSEState\000"
.LASF11:
	.ascii	"unsigned int\000"
.LASF102:
	.ascii	"HAL_TIMEOUT\000"
.LASF164:
	.ascii	"GPIO_InitStruct\000"
.LASF162:
	.ascii	"RCC_MCODiv\000"
.LASF8:
	.ascii	"long unsigned int\000"
.LASF42:
	.ascii	"GPIO_TypeDef\000"
.LASF26:
	.ascii	"PCROP1ER\000"
.LASF95:
	.ascii	"RCC_TypeDef\000"
.LASF99:
	.ascii	"HAL_OK\000"
.LASF41:
	.ascii	"ASCR\000"
.LASF5:
	.ascii	"short unsigned int\000"
.LASF33:
	.ascii	"WRP2BR\000"
.LASF104:
	.ascii	"PLLState\000"
.LASF86:
	.ascii	"AHB3SMENR\000"
.LASF72:
	.ascii	"AHB3RSTR\000"
.LASF112:
	.ascii	"OscillatorType\000"
.LASF140:
	.ascii	"HAL_RCC_EnableCSS\000"
.LASF103:
	.ascii	"HAL_StatusTypeDef\000"
.LASF27:
	.ascii	"WRP1AR\000"
.LASF16:
	.ascii	"AHBPrescTable\000"
.LASF125:
	.ascii	"AHBCLKDivider\000"
.LASF96:
	.ascii	"RESET\000"
.LASF152:
	.ascii	"sysclockfreq\000"
.LASF119:
	.ascii	"MSICalibrationValue\000"
.LASF156:
	.ascii	"pllm\000"
.LASF136:
	.ascii	"HAL_GetTick\000"
.LASF131:
	.ascii	"Speed\000"
.LASF65:
	.ascii	"PLLSAI2CFGR\000"
.LASF24:
	.ascii	"OPTR\000"
.LASF176:
	.ascii	"HAL_GPIO_Init\000"
.LASF133:
	.ascii	"GPIO_InitTypeDef\000"
.LASF128:
	.ascii	"RCC_ClkInitTypeDef\000"
.LASF159:
	.ascii	"HAL_RCC_MCOConfig\000"
.LASF28:
	.ascii	"WRP1BR\000"
.LASF80:
	.ascii	"APB1ENR1\000"
.LASF81:
	.ascii	"APB1ENR2\000"
.LASF137:
	.ascii	"latency\000"
.LASF15:
	.ascii	"SystemCoreClock\000"
.LASF178:
	.ascii	"RCC_SetFlashLatencyFromMSIRange\000"
.LASF177:
	.ascii	"HAL_InitTick\000"
.LASF69:
	.ascii	"RESERVED0\000"
.LASF23:
	.ascii	"RESERVED1\000"
.LASF29:
	.ascii	"RESERVED2\000"
.LASF79:
	.ascii	"RESERVED3\000"
.LASF83:
	.ascii	"RESERVED4\000"
.LASF87:
	.ascii	"RESERVED5\000"
.LASF91:
	.ascii	"RESERVED6\000"
.LASF93:
	.ascii	"RESERVED7\000"
.LASF148:
	.ascii	"HAL_RCC_GetPCLK2Freq\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF170:
	.ascii	"pll_config\000"
.LASF92:
	.ascii	"CCIPR\000"
.LASF2:
	.ascii	"short int\000"
.LASF147:
	.ascii	"HAL_RCC_GetResetSource\000"
.LASF120:
	.ascii	"MSIClockRange\000"
.LASF167:
	.ascii	"tickstart\000"
.LASF105:
	.ascii	"PLLSource\000"
.LASF43:
	.ascii	"RESERVED\000"
.LASF146:
	.ascii	"RCC_OscInitStruct\000"
.LASF82:
	.ascii	"APB2ENR\000"
.LASF78:
	.ascii	"AHB3ENR\000"
.LASF40:
	.ascii	"LCKR\000"
.LASF14:
	.ascii	"uint32_t\000"
.LASF22:
	.ascii	"ECCR\000"
.LASF100:
	.ascii	"HAL_ERROR\000"
.LASF163:
	.ascii	"tmpreg\000"
.LASF174:
	.ascii	"../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_r"
	.ascii	"cc.c\000"
.LASF98:
	.ascii	"long double\000"
.LASF169:
	.ascii	"HAL_RCC_OscConfig\000"
.LASF134:
	.ascii	"uwTickPrio\000"
.LASF129:
	.ascii	"Mode\000"
.LASF71:
	.ascii	"AHB2RSTR\000"
.LASF4:
	.ascii	"__uint16_t\000"
.LASF173:
	.ascii	"GNU C17 12.3.1 20230626 -mcpu=cortex-m3 -mthumb -mf"
	.ascii	"loat-abi=soft -march=armv7-m -g -gdwarf-2 -Og -fdat"
	.ascii	"a-sections -ffunction-sections\000"
.LASF158:
	.ascii	"pll_oscsource\000"
.LASF172:
	.ascii	"HAL_RCC_DeInit\000"
.LASF127:
	.ascii	"APB2CLKDivider\000"
.LASF161:
	.ascii	"RCC_MCOSource\000"
.LASF150:
	.ascii	"HAL_RCC_GetSysClockFreq\000"
.LASF60:
	.ascii	"PWR_TypeDef\000"
.LASF77:
	.ascii	"AHB2ENR\000"
.LASF66:
	.ascii	"CIER\000"
.LASF179:
	.ascii	"HAL_RCC_GetHCLKFreq\000"
.LASF157:
	.ascii	"sysclk_source\000"
.LASF68:
	.ascii	"CICR\000"
.LASF165:
	.ascii	"HAL_RCC_ClockConfig\000"
.LASF64:
	.ascii	"PLLSAI1CFGR\000"
.LASF94:
	.ascii	"BDCR\000"
.LASF18:
	.ascii	"MSIRangeTable\000"
.LASF12:
	.ascii	"uint8_t\000"
.LASF118:
	.ascii	"MSIState\000"
.LASF111:
	.ascii	"RCC_PLLInitTypeDef\000"
.LASF123:
	.ascii	"ClockType\000"
.LASF61:
	.ascii	"ICSCR\000"
.LASF135:
	.ascii	"HAL_PWREx_GetVoltageRange\000"
.LASF121:
	.ascii	"HSI48State\000"
.LASF76:
	.ascii	"AHB1ENR\000"
.LASF130:
	.ascii	"Pull\000"
.LASF160:
	.ascii	"RCC_MCOx\000"
.LASF62:
	.ascii	"CFGR\000"
.LASF151:
	.ascii	"msirange\000"
.LASF144:
	.ascii	"pFLatency\000"
.LASF145:
	.ascii	"HAL_RCC_GetOscConfig\000"
.LASF141:
	.ascii	"HAL_RCC_NMI_IRQHandler\000"
.LASF149:
	.ascii	"HAL_RCC_GetPCLK1Freq\000"
.LASF154:
	.ascii	"pllsource\000"
.LASF88:
	.ascii	"APB1SMENR1\000"
.LASF89:
	.ascii	"APB1SMENR2\000"
.LASF124:
	.ascii	"SYSCLKSource\000"
	.ident	"GCC: (GNU Tools for STM32 12.3.rel1.20240612-1315) 12.3.1 20230626"
