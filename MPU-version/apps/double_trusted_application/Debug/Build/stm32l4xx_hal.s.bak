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
	.file	"stm32l4xx_hal.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 1 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.c"
	.section	.text.HAL_MspInit,"ax",%progbits
	.align	1
	.weak	HAL_MspInit
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_MspInit, %function
HAL_MspInit:
.LFB76:
	.loc 1 226 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 230 1 view .LVU1
	bx	lr
	.cfi_endproc
.LFE76:
	.size	HAL_MspInit, .-HAL_MspInit
	.section	.text.HAL_MspDeInit,"ax",%progbits
	.align	1
	.weak	HAL_MspDeInit
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_MspDeInit, %function
HAL_MspDeInit:
.LFB77:
	.loc 1 237 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 241 1 view .LVU3
	bx	lr
	.cfi_endproc
.LFE77:
	.size	HAL_MspDeInit, .-HAL_MspDeInit
	.section	.text.HAL_DeInit,"ax",%progbits
	.align	1
	.global	HAL_DeInit
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_DeInit, %function
HAL_DeInit:
.LFB75:
	.loc 1 197 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
.LCFI0:
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	.loc 1 199 3 view .LVU5
	.loc 1 199 3 view .LVU6
	ldr	r3, .L5
	mov	r2, #-1
	str	r2, [r3, #56]
	.loc 1 199 3 view .LVU7
	str	r2, [r3, #60]
	.loc 1 199 3 view .LVU8
	.loc 1 200 3 view .LVU9
	.loc 1 200 3 view .LVU10
	movs	r4, #0
	str	r4, [r3, #56]
	.loc 1 200 3 view .LVU11
	str	r4, [r3, #60]
	.loc 1 200 3 view .LVU12
	.loc 1 202 3 view .LVU13
	str	r2, [r3, #64]
	.loc 1 203 3 view .LVU14
	str	r4, [r3, #64]
	.loc 1 205 3 view .LVU15
	str	r2, [r3, #40]
	.loc 1 206 3 view .LVU16
	str	r4, [r3, #40]
	.loc 1 208 3 view .LVU17
	str	r2, [r3, #44]
	.loc 1 209 3 view .LVU18
	str	r4, [r3, #44]
	.loc 1 211 3 view .LVU19
	str	r2, [r3, #48]
	.loc 1 212 3 view .LVU20
	str	r4, [r3, #48]
	.loc 1 215 3 view .LVU21
	bl	HAL_MspDeInit
.LVL0:
	.loc 1 218 3 view .LVU22
	.loc 1 219 1 is_stmt 0 view .LVU23
	mov	r0, r4
	pop	{r4, pc}
.L6:
	.align	2
.L5:
	.word	1073876992
	.cfi_endproc
.LFE75:
	.size	HAL_DeInit, .-HAL_DeInit
	.section	.text.HAL_InitTick,"ax",%progbits
	.align	1
	.weak	HAL_InitTick
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_InitTick, %function
HAL_InitTick:
.LVL1:
.LFB78:
	.loc 1 260 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 261 3 view .LVU25
	.loc 1 264 3 view .LVU26
	.loc 1 264 28 is_stmt 0 view .LVU27
	ldr	r3, .L18
	ldrb	r3, [r3]	@ zero_extendqisi2
	.loc 1 264 6 view .LVU28
	cbnz	r3, .L16
	.loc 1 287 12 view .LVU29
	movs	r0, #1
.LVL2:
	.loc 1 291 3 is_stmt 1 view .LVU30
	.loc 1 292 1 is_stmt 0 view .LVU31
	bx	lr
.LVL3:
.L16:
	.loc 1 260 1 view .LVU32
	push	{r4, lr}
.LCFI1:
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	mov	r4, r0
	.loc 1 267 5 is_stmt 1 view .LVU33
	.loc 1 267 53 is_stmt 0 view .LVU34
	mov	r0, #1000
.LVL4:
	.loc 1 267 53 view .LVU35
	udiv	r3, r0, r3
	.loc 1 267 9 view .LVU36
	ldr	r2, .L18+4
	ldr	r0, [r2]
	udiv	r0, r0, r3
	bl	HAL_SYSTICK_Config
.LVL5:
	.loc 1 267 8 view .LVU37
	cbnz	r0, .L10
	.loc 1 270 7 is_stmt 1 view .LVU38
	.loc 1 270 10 is_stmt 0 view .LVU39
	cmp	r4, #15
	bls	.L17
	.loc 1 277 16 view .LVU40
	movs	r0, #1
	b	.L8
.L17:
	.loc 1 272 9 is_stmt 1 view .LVU41
	movs	r2, #0
	mov	r1, r4
	mov	r0, #-1
	bl	HAL_NVIC_SetPriority
.LVL6:
	.loc 1 273 9 view .LVU42
	.loc 1 273 20 is_stmt 0 view .LVU43
	ldr	r3, .L18+8
	str	r4, [r3]
	.loc 1 261 22 view .LVU44
	movs	r0, #0
	b	.L8
.L10:
	.loc 1 282 14 view .LVU45
	movs	r0, #1
.L8:
.LVL7:
	.loc 1 291 3 is_stmt 1 view .LVU46
	.loc 1 292 1 is_stmt 0 view .LVU47
	pop	{r4, pc}
.LVL8:
.L19:
	.loc 1 292 1 view .LVU48
	.align	2
.L18:
	.word	uwTickFreq
	.word	SystemCoreClock
	.word	uwTickPrio
	.cfi_endproc
.LFE78:
	.size	HAL_InitTick, .-HAL_InitTick
	.section	.text.HAL_Init,"ax",%progbits
	.align	1
	.global	HAL_Init
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_Init, %function
HAL_Init:
.LFB74:
	.loc 1 153 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
.LCFI2:
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	.loc 1 154 3 view .LVU50
.LVL9:
	.loc 1 174 3 view .LVU51
	movs	r0, #3
	bl	HAL_NVIC_SetPriorityGrouping
.LVL10:
	.loc 1 177 3 view .LVU52
	.loc 1 177 7 is_stmt 0 view .LVU53
	movs	r0, #0
	bl	HAL_InitTick
.LVL11:
	.loc 1 177 6 view .LVU54
	cbz	r0, .L24
	.loc 1 179 12 view .LVU55
	movs	r4, #1
.L21:
.LVL12:
	.loc 1 188 3 is_stmt 1 view .LVU56
	.loc 1 189 1 is_stmt 0 view .LVU57
	mov	r0, r4
	pop	{r4, pc}
.LVL13:
.L24:
	.loc 1 189 1 view .LVU58
	mov	r4, r0
	.loc 1 184 5 is_stmt 1 view .LVU59
	bl	HAL_MspInit
.LVL14:
	b	.L21
	.cfi_endproc
.LFE74:
	.size	HAL_Init, .-HAL_Init
	.section	.text.HAL_IncTick,"ax",%progbits
	.align	1
	.weak	HAL_IncTick
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_IncTick, %function
HAL_IncTick:
.LFB79:
	.loc 1 328 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 329 3 view .LVU61
	.loc 1 329 13 is_stmt 0 view .LVU62
	ldr	r3, .L26
	ldrb	r3, [r3]	@ zero_extendqisi2
	.loc 1 329 10 view .LVU63
	ldr	r2, .L26+4
	ldr	r1, [r2]
	add	r3, r3, r1
	str	r3, [r2]
	.loc 1 330 1 view .LVU64
	bx	lr
.L27:
	.align	2
.L26:
	.word	uwTickFreq
	.word	uwTick
	.cfi_endproc
.LFE79:
	.size	HAL_IncTick, .-HAL_IncTick
	.section	.text.HAL_GetTick,"ax",%progbits
	.align	1
	.weak	HAL_GetTick
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_GetTick, %function
HAL_GetTick:
.LFB80:
	.loc 1 339 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 340 3 view .LVU66
	.loc 1 340 10 is_stmt 0 view .LVU67
	ldr	r3, .L29
	ldr	r0, [r3]
	.loc 1 341 1 view .LVU68
	bx	lr
.L30:
	.align	2
.L29:
	.word	uwTick
	.cfi_endproc
.LFE80:
	.size	HAL_GetTick, .-HAL_GetTick
	.section	.text.HAL_GetTickPrio,"ax",%progbits
	.align	1
	.global	HAL_GetTickPrio
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_GetTickPrio, %function
HAL_GetTickPrio:
.LFB81:
	.loc 1 348 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 349 3 view .LVU70
	.loc 1 350 1 is_stmt 0 view .LVU71
	ldr	r3, .L32
	ldr	r0, [r3]
	bx	lr
.L33:
	.align	2
.L32:
	.word	uwTickPrio
	.cfi_endproc
.LFE81:
	.size	HAL_GetTickPrio, .-HAL_GetTickPrio
	.section	.text.HAL_SetTickFreq,"ax",%progbits
	.align	1
	.global	HAL_SetTickFreq
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_SetTickFreq, %function
HAL_SetTickFreq:
.LVL15:
.LFB82:
	.loc 1 358 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 358 1 is_stmt 0 view .LVU73
	push	{r4, lr}
.LCFI3:
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	.loc 1 359 3 is_stmt 1 view .LVU74
.LVL16:
	.loc 1 360 3 view .LVU75
	.loc 1 362 3 view .LVU76
	.loc 1 362 18 is_stmt 0 view .LVU77
	ldr	r3, .L39
	ldrb	r4, [r3]	@ zero_extendqisi2
	.loc 1 362 6 view .LVU78
	cmp	r4, r0
	bne	.L38
	.loc 1 359 21 view .LVU79
	movs	r0, #0
.LVL17:
.L35:
	.loc 1 379 3 is_stmt 1 view .LVU80
	.loc 1 380 1 is_stmt 0 view .LVU81
	pop	{r4, pc}
.LVL18:
.L38:
	.loc 1 365 5 is_stmt 1 view .LVU82
	.loc 1 368 5 view .LVU83
	.loc 1 368 16 is_stmt 0 view .LVU84
	strb	r0, [r3]
	.loc 1 371 5 is_stmt 1 view .LVU85
	.loc 1 371 14 is_stmt 0 view .LVU86
	ldr	r3, .L39+4
	ldr	r0, [r3]
.LVL19:
	.loc 1 371 14 view .LVU87
	bl	HAL_InitTick
.LVL20:
	.loc 1 372 5 is_stmt 1 view .LVU88
	.loc 1 372 8 is_stmt 0 view .LVU89
	cmp	r0, #0
	beq	.L35
	.loc 1 375 7 is_stmt 1 view .LVU90
	.loc 1 375 18 is_stmt 0 view .LVU91
	ldr	r3, .L39
	strb	r4, [r3]
	b	.L35
.L40:
	.align	2
.L39:
	.word	uwTickFreq
	.word	uwTickPrio
	.cfi_endproc
.LFE82:
	.size	HAL_SetTickFreq, .-HAL_SetTickFreq
	.section	.text.HAL_GetTickFreq,"ax",%progbits
	.align	1
	.global	HAL_GetTickFreq
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_GetTickFreq, %function
HAL_GetTickFreq:
.LFB83:
	.loc 1 388 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 389 3 view .LVU93
	.loc 1 390 1 is_stmt 0 view .LVU94
	ldr	r3, .L42
	ldrb	r0, [r3]	@ zero_extendqisi2
	bx	lr
.L43:
	.align	2
.L42:
	.word	uwTickFreq
	.cfi_endproc
.LFE83:
	.size	HAL_GetTickFreq, .-HAL_GetTickFreq
	.section	.text.HAL_Delay,"ax",%progbits
	.align	1
	.weak	HAL_Delay
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_Delay, %function
HAL_Delay:
.LVL21:
.LFB84:
	.loc 1 404 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	.loc 1 404 1 is_stmt 0 view .LVU96
	push	{r3, r4, r5, lr}
.LCFI4:
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	.cfi_offset 4, -12
	.cfi_offset 5, -8
	.cfi_offset 14, -4
	mov	r4, r0
	.loc 1 405 3 is_stmt 1 view .LVU97
	.loc 1 405 24 is_stmt 0 view .LVU98
	bl	HAL_GetTick
.LVL22:
	.loc 1 405 24 view .LVU99
	mov	r5, r0
.LVL23:
	.loc 1 406 3 is_stmt 1 view .LVU100
	.loc 1 409 3 view .LVU101
	.loc 1 409 6 is_stmt 0 view .LVU102
	cmp	r4, #-1
	beq	.L46
	.loc 1 411 5 is_stmt 1 view .LVU103
	.loc 1 411 13 is_stmt 0 view .LVU104
	ldr	r3, .L48
	ldrb	r3, [r3]	@ zero_extendqisi2
	.loc 1 411 10 view .LVU105
	add	r4, r4, r3
.LVL24:
.L46:
	.loc 1 416 3 is_stmt 1 discriminator 1 view .LVU106
	.loc 1 414 38 discriminator 1 view .LVU107
	.loc 1 414 11 is_stmt 0 discriminator 1 view .LVU108
	bl	HAL_GetTick
.LVL25:
	.loc 1 414 25 discriminator 1 view .LVU109
	subs	r0, r0, r5
	.loc 1 414 38 discriminator 1 view .LVU110
	cmp	r0, r4
	bcc	.L46
	.loc 1 417 1 view .LVU111
	pop	{r3, r4, r5, pc}
.LVL26:
.L49:
	.loc 1 417 1 view .LVU112
	.align	2
.L48:
	.word	uwTickFreq
	.cfi_endproc
.LFE84:
	.size	HAL_Delay, .-HAL_Delay
	.section	.text.HAL_SuspendTick,"ax",%progbits
	.align	1
	.weak	HAL_SuspendTick
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_SuspendTick, %function
HAL_SuspendTick:
.LFB85:
	.loc 1 430 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 432 3 view .LVU114
	.loc 1 432 10 is_stmt 0 view .LVU115
	mov	r2, #-536813568
	ldr	r3, [r2, #16]
	.loc 1 432 17 view .LVU116
	bic	r3, r3, #2
	str	r3, [r2, #16]
	.loc 1 433 1 view .LVU117
	bx	lr
	.cfi_endproc
.LFE85:
	.size	HAL_SuspendTick, .-HAL_SuspendTick
	.section	.text.HAL_ResumeTick,"ax",%progbits
	.align	1
	.weak	HAL_ResumeTick
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_ResumeTick, %function
HAL_ResumeTick:
.LFB86:
	.loc 1 446 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 448 3 view .LVU119
	.loc 1 448 10 is_stmt 0 view .LVU120
	mov	r2, #-536813568
	ldr	r3, [r2, #16]
	.loc 1 448 18 view .LVU121
	orr	r3, r3, #2
	str	r3, [r2, #16]
	.loc 1 449 1 view .LVU122
	bx	lr
	.cfi_endproc
.LFE86:
	.size	HAL_ResumeTick, .-HAL_ResumeTick
	.section	.text.HAL_GetHalVersion,"ax",%progbits
	.align	1
	.global	HAL_GetHalVersion
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_GetHalVersion, %function
HAL_GetHalVersion:
.LFB87:
	.loc 1 456 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 457 3 view .LVU124
	.loc 1 458 1 is_stmt 0 view .LVU125
	ldr	r0, .L53
	bx	lr
.L54:
	.align	2
.L53:
	.word	17630464
	.cfi_endproc
.LFE87:
	.size	HAL_GetHalVersion, .-HAL_GetHalVersion
	.section	.text.HAL_GetREVID,"ax",%progbits
	.align	1
	.global	HAL_GetREVID
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_GetREVID, %function
HAL_GetREVID:
.LFB88:
	.loc 1 465 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 466 3 view .LVU127
	.loc 1 466 17 is_stmt 0 view .LVU128
	ldr	r3, .L56
	ldr	r0, [r3]
	.loc 1 467 1 view .LVU129
	lsrs	r0, r0, #16
	bx	lr
.L57:
	.align	2
.L56:
	.word	-536600576
	.cfi_endproc
.LFE88:
	.size	HAL_GetREVID, .-HAL_GetREVID
	.section	.text.HAL_GetDEVID,"ax",%progbits
	.align	1
	.global	HAL_GetDEVID
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_GetDEVID, %function
HAL_GetDEVID:
.LFB89:
	.loc 1 474 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 475 3 view .LVU131
	.loc 1 475 16 is_stmt 0 view .LVU132
	ldr	r3, .L59
	ldr	r0, [r3]
	.loc 1 476 1 view .LVU133
	ubfx	r0, r0, #0, #12
	bx	lr
.L60:
	.align	2
.L59:
	.word	-536600576
	.cfi_endproc
.LFE89:
	.size	HAL_GetDEVID, .-HAL_GetDEVID
	.section	.text.HAL_GetUIDw0,"ax",%progbits
	.align	1
	.global	HAL_GetUIDw0
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_GetUIDw0, %function
HAL_GetUIDw0:
.LFB90:
	.loc 1 483 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 484 3 view .LVU135
	.loc 1 485 1 is_stmt 0 view .LVU136
	ldr	r3, .L62
	ldr	r0, [r3, #1424]
	bx	lr
.L63:
	.align	2
.L62:
	.word	536834048
	.cfi_endproc
.LFE90:
	.size	HAL_GetUIDw0, .-HAL_GetUIDw0
	.section	.text.HAL_GetUIDw1,"ax",%progbits
	.align	1
	.global	HAL_GetUIDw1
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_GetUIDw1, %function
HAL_GetUIDw1:
.LFB91:
	.loc 1 492 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 493 3 view .LVU138
	.loc 1 494 1 is_stmt 0 view .LVU139
	ldr	r3, .L65
	ldr	r0, [r3, #1428]
	bx	lr
.L66:
	.align	2
.L65:
	.word	536834048
	.cfi_endproc
.LFE91:
	.size	HAL_GetUIDw1, .-HAL_GetUIDw1
	.section	.text.HAL_GetUIDw2,"ax",%progbits
	.align	1
	.global	HAL_GetUIDw2
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_GetUIDw2, %function
HAL_GetUIDw2:
.LFB92:
	.loc 1 501 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 502 3 view .LVU141
	.loc 1 503 1 is_stmt 0 view .LVU142
	ldr	r3, .L68
	ldr	r0, [r3, #1432]
	bx	lr
.L69:
	.align	2
.L68:
	.word	536834048
	.cfi_endproc
.LFE92:
	.size	HAL_GetUIDw2, .-HAL_GetUIDw2
	.section	.text.HAL_DBGMCU_EnableDBGSleepMode,"ax",%progbits
	.align	1
	.global	HAL_DBGMCU_EnableDBGSleepMode
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_DBGMCU_EnableDBGSleepMode, %function
HAL_DBGMCU_EnableDBGSleepMode:
.LFB93:
	.loc 1 530 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 531 3 view .LVU144
	ldr	r2, .L71
	ldr	r3, [r2, #4]
	orr	r3, r3, #1
	str	r3, [r2, #4]
	.loc 1 532 1 is_stmt 0 view .LVU145
	bx	lr
.L72:
	.align	2
.L71:
	.word	-536600576
	.cfi_endproc
.LFE93:
	.size	HAL_DBGMCU_EnableDBGSleepMode, .-HAL_DBGMCU_EnableDBGSleepMode
	.section	.text.HAL_DBGMCU_DisableDBGSleepMode,"ax",%progbits
	.align	1
	.global	HAL_DBGMCU_DisableDBGSleepMode
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_DBGMCU_DisableDBGSleepMode, %function
HAL_DBGMCU_DisableDBGSleepMode:
.LFB94:
	.loc 1 539 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 540 3 view .LVU147
	ldr	r2, .L74
	ldr	r3, [r2, #4]
	bic	r3, r3, #1
	str	r3, [r2, #4]
	.loc 1 541 1 is_stmt 0 view .LVU148
	bx	lr
.L75:
	.align	2
.L74:
	.word	-536600576
	.cfi_endproc
.LFE94:
	.size	HAL_DBGMCU_DisableDBGSleepMode, .-HAL_DBGMCU_DisableDBGSleepMode
	.section	.text.HAL_DBGMCU_EnableDBGStopMode,"ax",%progbits
	.align	1
	.global	HAL_DBGMCU_EnableDBGStopMode
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_DBGMCU_EnableDBGStopMode, %function
HAL_DBGMCU_EnableDBGStopMode:
.LFB95:
	.loc 1 548 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 549 3 view .LVU150
	ldr	r2, .L77
	ldr	r3, [r2, #4]
	orr	r3, r3, #2
	str	r3, [r2, #4]
	.loc 1 550 1 is_stmt 0 view .LVU151
	bx	lr
.L78:
	.align	2
.L77:
	.word	-536600576
	.cfi_endproc
.LFE95:
	.size	HAL_DBGMCU_EnableDBGStopMode, .-HAL_DBGMCU_EnableDBGStopMode
	.section	.text.HAL_DBGMCU_DisableDBGStopMode,"ax",%progbits
	.align	1
	.global	HAL_DBGMCU_DisableDBGStopMode
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_DBGMCU_DisableDBGStopMode, %function
HAL_DBGMCU_DisableDBGStopMode:
.LFB96:
	.loc 1 557 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 558 3 view .LVU153
	ldr	r2, .L80
	ldr	r3, [r2, #4]
	bic	r3, r3, #2
	str	r3, [r2, #4]
	.loc 1 559 1 is_stmt 0 view .LVU154
	bx	lr
.L81:
	.align	2
.L80:
	.word	-536600576
	.cfi_endproc
.LFE96:
	.size	HAL_DBGMCU_DisableDBGStopMode, .-HAL_DBGMCU_DisableDBGStopMode
	.section	.text.HAL_DBGMCU_EnableDBGStandbyMode,"ax",%progbits
	.align	1
	.global	HAL_DBGMCU_EnableDBGStandbyMode
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_DBGMCU_EnableDBGStandbyMode, %function
HAL_DBGMCU_EnableDBGStandbyMode:
.LFB97:
	.loc 1 566 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 567 3 view .LVU156
	ldr	r2, .L83
	ldr	r3, [r2, #4]
	orr	r3, r3, #4
	str	r3, [r2, #4]
	.loc 1 568 1 is_stmt 0 view .LVU157
	bx	lr
.L84:
	.align	2
.L83:
	.word	-536600576
	.cfi_endproc
.LFE97:
	.size	HAL_DBGMCU_EnableDBGStandbyMode, .-HAL_DBGMCU_EnableDBGStandbyMode
	.section	.text.HAL_DBGMCU_DisableDBGStandbyMode,"ax",%progbits
	.align	1
	.global	HAL_DBGMCU_DisableDBGStandbyMode
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_DBGMCU_DisableDBGStandbyMode, %function
HAL_DBGMCU_DisableDBGStandbyMode:
.LFB98:
	.loc 1 575 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 576 3 view .LVU159
	ldr	r2, .L86
	ldr	r3, [r2, #4]
	bic	r3, r3, #4
	str	r3, [r2, #4]
	.loc 1 577 1 is_stmt 0 view .LVU160
	bx	lr
.L87:
	.align	2
.L86:
	.word	-536600576
	.cfi_endproc
.LFE98:
	.size	HAL_DBGMCU_DisableDBGStandbyMode, .-HAL_DBGMCU_DisableDBGStandbyMode
	.section	.text.HAL_SYSCFG_SRAM2Erase,"ax",%progbits
	.align	1
	.global	HAL_SYSCFG_SRAM2Erase
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_SYSCFG_SRAM2Erase, %function
HAL_SYSCFG_SRAM2Erase:
.LFB99:
	.loc 1 608 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 610 3 view .LVU162
	.loc 1 610 15 is_stmt 0 view .LVU163
	ldr	r3, .L89
	movs	r2, #202
	str	r2, [r3, #36]
	.loc 1 611 3 is_stmt 1 view .LVU164
	.loc 1 611 15 is_stmt 0 view .LVU165
	movs	r2, #83
	str	r2, [r3, #36]
	.loc 1 613 3 is_stmt 1 view .LVU166
	.loc 1 613 38 is_stmt 0 view .LVU167
	ldr	r3, .L89+4
	movs	r2, #1
	str	r2, [r3, #768]
	.loc 1 614 1 view .LVU168
	bx	lr
.L90:
	.align	2
.L89:
	.word	1073807360
	.word	1109393408
	.cfi_endproc
.LFE99:
	.size	HAL_SYSCFG_SRAM2Erase, .-HAL_SYSCFG_SRAM2Erase
	.section	.text.HAL_SYSCFG_EnableMemorySwappingBank,"ax",%progbits
	.align	1
	.global	HAL_SYSCFG_EnableMemorySwappingBank
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_SYSCFG_EnableMemorySwappingBank, %function
HAL_SYSCFG_EnableMemorySwappingBank:
.LFB100:
	.loc 1 627 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 628 3 view .LVU170
	.loc 1 628 32 is_stmt 0 view .LVU171
	ldr	r3, .L92
	movs	r2, #1
	str	r2, [r3, #32]
	.loc 1 629 1 view .LVU172
	bx	lr
.L93:
	.align	2
.L92:
	.word	1109393408
	.cfi_endproc
.LFE100:
	.size	HAL_SYSCFG_EnableMemorySwappingBank, .-HAL_SYSCFG_EnableMemorySwappingBank
	.section	.text.HAL_SYSCFG_DisableMemorySwappingBank,"ax",%progbits
	.align	1
	.global	HAL_SYSCFG_DisableMemorySwappingBank
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_SYSCFG_DisableMemorySwappingBank, %function
HAL_SYSCFG_DisableMemorySwappingBank:
.LFB101:
	.loc 1 642 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 644 3 view .LVU174
	.loc 1 644 32 is_stmt 0 view .LVU175
	ldr	r3, .L95
	movs	r2, #0
	str	r2, [r3, #32]
	.loc 1 645 1 view .LVU176
	bx	lr
.L96:
	.align	2
.L95:
	.word	1109393408
	.cfi_endproc
.LFE101:
	.size	HAL_SYSCFG_DisableMemorySwappingBank, .-HAL_SYSCFG_DisableMemorySwappingBank
	.section	.text.HAL_SYSCFG_VREFBUF_VoltageScalingConfig,"ax",%progbits
	.align	1
	.global	HAL_SYSCFG_VREFBUF_VoltageScalingConfig
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_SYSCFG_VREFBUF_VoltageScalingConfig, %function
HAL_SYSCFG_VREFBUF_VoltageScalingConfig:
.LVL27:
.LFB102:
	.loc 1 659 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 661 3 view .LVU178
	.loc 1 663 3 view .LVU179
	ldr	r2, .L98
	ldr	r3, [r2, #48]
	bic	r3, r3, #4
	orrs	r3, r3, r0
	str	r3, [r2, #48]
	.loc 1 664 1 is_stmt 0 view .LVU180
	bx	lr
.L99:
	.align	2
.L98:
	.word	1073807360
	.cfi_endproc
.LFE102:
	.size	HAL_SYSCFG_VREFBUF_VoltageScalingConfig, .-HAL_SYSCFG_VREFBUF_VoltageScalingConfig
	.section	.text.HAL_SYSCFG_VREFBUF_HighImpedanceConfig,"ax",%progbits
	.align	1
	.global	HAL_SYSCFG_VREFBUF_HighImpedanceConfig
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_SYSCFG_VREFBUF_HighImpedanceConfig, %function
HAL_SYSCFG_VREFBUF_HighImpedanceConfig:
.LVL28:
.LFB103:
	.loc 1 675 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 677 3 view .LVU182
	.loc 1 679 3 view .LVU183
	ldr	r2, .L101
	ldr	r3, [r2, #48]
	bic	r3, r3, #2
	orrs	r3, r3, r0
	str	r3, [r2, #48]
	.loc 1 680 1 is_stmt 0 view .LVU184
	bx	lr
.L102:
	.align	2
.L101:
	.word	1073807360
	.cfi_endproc
.LFE103:
	.size	HAL_SYSCFG_VREFBUF_HighImpedanceConfig, .-HAL_SYSCFG_VREFBUF_HighImpedanceConfig
	.section	.text.HAL_SYSCFG_VREFBUF_TrimmingConfig,"ax",%progbits
	.align	1
	.global	HAL_SYSCFG_VREFBUF_TrimmingConfig
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_SYSCFG_VREFBUF_TrimmingConfig, %function
HAL_SYSCFG_VREFBUF_TrimmingConfig:
.LVL29:
.LFB104:
	.loc 1 687 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 689 3 view .LVU186
	.loc 1 691 3 view .LVU187
	ldr	r2, .L104
	ldr	r3, [r2, #52]
	bic	r3, r3, #63
	orrs	r3, r3, r0
	str	r3, [r2, #52]
	.loc 1 692 1 is_stmt 0 view .LVU188
	bx	lr
.L105:
	.align	2
.L104:
	.word	1073807360
	.cfi_endproc
.LFE104:
	.size	HAL_SYSCFG_VREFBUF_TrimmingConfig, .-HAL_SYSCFG_VREFBUF_TrimmingConfig
	.section	.text.HAL_SYSCFG_EnableVREFBUF,"ax",%progbits
	.align	1
	.global	HAL_SYSCFG_EnableVREFBUF
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_SYSCFG_EnableVREFBUF, %function
HAL_SYSCFG_EnableVREFBUF:
.LFB105:
	.loc 1 699 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r4, lr}
.LCFI5:
	.cfi_def_cfa_offset 8
	.cfi_offset 4, -8
	.cfi_offset 14, -4
	.loc 1 700 3 view .LVU190
	.loc 1 702 3 view .LVU191
	ldr	r2, .L113
	ldr	r3, [r2, #48]
	orr	r3, r3, #1
	str	r3, [r2, #48]
	.loc 1 705 3 view .LVU192
	.loc 1 705 15 is_stmt 0 view .LVU193
	bl	HAL_GetTick
.LVL30:
	mov	r4, r0
.LVL31:
	.loc 1 708 3 is_stmt 1 view .LVU194
.L107:
	.loc 1 708 49 view .LVU195
	.loc 1 708 9 is_stmt 0 view .LVU196
	ldr	r3, .L113
	ldr	r3, [r3, #48]
	.loc 1 708 49 view .LVU197
	tst	r3, #8
	bne	.L112
	.loc 1 710 5 is_stmt 1 view .LVU198
	.loc 1 710 9 is_stmt 0 view .LVU199
	bl	HAL_GetTick
.LVL32:
	.loc 1 710 23 view .LVU200
	subs	r0, r0, r4
	.loc 1 710 7 view .LVU201
	cmp	r0, #10
	bls	.L107
	.loc 1 712 14 view .LVU202
	movs	r0, #3
	b	.L108
.L112:
	.loc 1 716 10 view .LVU203
	movs	r0, #0
.L108:
	.loc 1 717 1 view .LVU204
	pop	{r4, pc}
.LVL33:
.L114:
	.loc 1 717 1 view .LVU205
	.align	2
.L113:
	.word	1073807360
	.cfi_endproc
.LFE105:
	.size	HAL_SYSCFG_EnableVREFBUF, .-HAL_SYSCFG_EnableVREFBUF
	.section	.text.HAL_SYSCFG_DisableVREFBUF,"ax",%progbits
	.align	1
	.global	HAL_SYSCFG_DisableVREFBUF
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_SYSCFG_DisableVREFBUF, %function
HAL_SYSCFG_DisableVREFBUF:
.LFB106:
	.loc 1 725 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 726 3 view .LVU207
	ldr	r2, .L116
	ldr	r3, [r2, #48]
	bic	r3, r3, #1
	str	r3, [r2, #48]
	.loc 1 727 1 is_stmt 0 view .LVU208
	bx	lr
.L117:
	.align	2
.L116:
	.word	1073807360
	.cfi_endproc
.LFE106:
	.size	HAL_SYSCFG_DisableVREFBUF, .-HAL_SYSCFG_DisableVREFBUF
	.section	.text.HAL_SYSCFG_EnableIOAnalogSwitchBooster,"ax",%progbits
	.align	1
	.global	HAL_SYSCFG_EnableIOAnalogSwitchBooster
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_SYSCFG_EnableIOAnalogSwitchBooster, %function
HAL_SYSCFG_EnableIOAnalogSwitchBooster:
.LFB107:
	.loc 1 736 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 737 3 view .LVU210
	ldr	r2, .L119
	ldr	r3, [r2, #4]
	orr	r3, r3, #256
	str	r3, [r2, #4]
	.loc 1 738 1 is_stmt 0 view .LVU211
	bx	lr
.L120:
	.align	2
.L119:
	.word	1073807360
	.cfi_endproc
.LFE107:
	.size	HAL_SYSCFG_EnableIOAnalogSwitchBooster, .-HAL_SYSCFG_EnableIOAnalogSwitchBooster
	.section	.text.HAL_SYSCFG_DisableIOAnalogSwitchBooster,"ax",%progbits
	.align	1
	.global	HAL_SYSCFG_DisableIOAnalogSwitchBooster
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_SYSCFG_DisableIOAnalogSwitchBooster, %function
HAL_SYSCFG_DisableIOAnalogSwitchBooster:
.LFB108:
	.loc 1 746 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 747 3 view .LVU213
	ldr	r2, .L122
	ldr	r3, [r2, #4]
	bic	r3, r3, #256
	str	r3, [r2, #4]
	.loc 1 748 1 is_stmt 0 view .LVU214
	bx	lr
.L123:
	.align	2
.L122:
	.word	1073807360
	.cfi_endproc
.LFE108:
	.size	HAL_SYSCFG_DisableIOAnalogSwitchBooster, .-HAL_SYSCFG_DisableIOAnalogSwitchBooster
	.global	uwTickFreq
	.section	.data.uwTickFreq,"aw"
	.type	uwTickFreq, %object
	.size	uwTickFreq, 1
uwTickFreq:
	.byte	1
	.global	uwTickPrio
	.section	.data.uwTickPrio,"aw"
	.align	2
	.type	uwTickPrio, %object
	.size	uwTickPrio, 4
uwTickPrio:
	.word	16
	.global	uwTick
	.section	.bss.uwTick,"aw",%nobits
	.align	2
	.type	uwTick, %object
	.size	uwTick, 4
uwTick:
	.space	4
	.text
.Letext0:
	.file 2 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
	.file 3 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/arm-none-eabi/include/machine/_default_types.h"
	.file 4 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/arm-none-eabi/include/sys/_stdint.h"
	.file 5 "../Drivers/CMSIS/Include/core_cm4.h"
	.file 6 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_def.h"
	.file 7 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal.h"
	.file 8 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/system_stm32l4xx.h"
	.file 9 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_cortex.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0xd01
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF217
	.byte	0xc
	.4byte	.LASF218
	.4byte	.LASF219
	.4byte	.Ldebug_ranges0+0
	.4byte	0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x5
	.byte	0x1
	.4byte	0x24e
	.byte	0x2
	.byte	0x42
	.byte	0x1
	.4byte	0x24e
	.uleb128 0x3
	.4byte	.LASF0
	.sleb128 -14
	.uleb128 0x3
	.4byte	.LASF1
	.sleb128 -13
	.uleb128 0x3
	.4byte	.LASF2
	.sleb128 -12
	.uleb128 0x3
	.4byte	.LASF3
	.sleb128 -11
	.uleb128 0x3
	.4byte	.LASF4
	.sleb128 -10
	.uleb128 0x3
	.4byte	.LASF5
	.sleb128 -5
	.uleb128 0x3
	.4byte	.LASF6
	.sleb128 -4
	.uleb128 0x3
	.4byte	.LASF7
	.sleb128 -2
	.uleb128 0x3
	.4byte	.LASF8
	.sleb128 -1
	.uleb128 0x4
	.4byte	.LASF9
	.byte	0
	.uleb128 0x4
	.4byte	.LASF10
	.byte	0x1
	.uleb128 0x4
	.4byte	.LASF11
	.byte	0x2
	.uleb128 0x4
	.4byte	.LASF12
	.byte	0x3
	.uleb128 0x4
	.4byte	.LASF13
	.byte	0x4
	.uleb128 0x4
	.4byte	.LASF14
	.byte	0x5
	.uleb128 0x4
	.4byte	.LASF15
	.byte	0x6
	.uleb128 0x4
	.4byte	.LASF16
	.byte	0x7
	.uleb128 0x4
	.4byte	.LASF17
	.byte	0x8
	.uleb128 0x4
	.4byte	.LASF18
	.byte	0x9
	.uleb128 0x4
	.4byte	.LASF19
	.byte	0xa
	.uleb128 0x4
	.4byte	.LASF20
	.byte	0xb
	.uleb128 0x4
	.4byte	.LASF21
	.byte	0xc
	.uleb128 0x4
	.4byte	.LASF22
	.byte	0xd
	.uleb128 0x4
	.4byte	.LASF23
	.byte	0xe
	.uleb128 0x4
	.4byte	.LASF24
	.byte	0xf
	.uleb128 0x4
	.4byte	.LASF25
	.byte	0x10
	.uleb128 0x4
	.4byte	.LASF26
	.byte	0x11
	.uleb128 0x4
	.4byte	.LASF27
	.byte	0x12
	.uleb128 0x4
	.4byte	.LASF28
	.byte	0x13
	.uleb128 0x4
	.4byte	.LASF29
	.byte	0x14
	.uleb128 0x4
	.4byte	.LASF30
	.byte	0x15
	.uleb128 0x4
	.4byte	.LASF31
	.byte	0x16
	.uleb128 0x4
	.4byte	.LASF32
	.byte	0x17
	.uleb128 0x4
	.4byte	.LASF33
	.byte	0x18
	.uleb128 0x4
	.4byte	.LASF34
	.byte	0x19
	.uleb128 0x4
	.4byte	.LASF35
	.byte	0x1a
	.uleb128 0x4
	.4byte	.LASF36
	.byte	0x1b
	.uleb128 0x4
	.4byte	.LASF37
	.byte	0x1c
	.uleb128 0x4
	.4byte	.LASF38
	.byte	0x1d
	.uleb128 0x4
	.4byte	.LASF39
	.byte	0x1e
	.uleb128 0x4
	.4byte	.LASF40
	.byte	0x1f
	.uleb128 0x4
	.4byte	.LASF41
	.byte	0x20
	.uleb128 0x4
	.4byte	.LASF42
	.byte	0x21
	.uleb128 0x4
	.4byte	.LASF43
	.byte	0x22
	.uleb128 0x4
	.4byte	.LASF44
	.byte	0x23
	.uleb128 0x4
	.4byte	.LASF45
	.byte	0x24
	.uleb128 0x4
	.4byte	.LASF46
	.byte	0x25
	.uleb128 0x4
	.4byte	.LASF47
	.byte	0x26
	.uleb128 0x4
	.4byte	.LASF48
	.byte	0x27
	.uleb128 0x4
	.4byte	.LASF49
	.byte	0x28
	.uleb128 0x4
	.4byte	.LASF50
	.byte	0x29
	.uleb128 0x4
	.4byte	.LASF51
	.byte	0x2a
	.uleb128 0x4
	.4byte	.LASF52
	.byte	0x2b
	.uleb128 0x4
	.4byte	.LASF53
	.byte	0x2c
	.uleb128 0x4
	.4byte	.LASF54
	.byte	0x2d
	.uleb128 0x4
	.4byte	.LASF55
	.byte	0x2e
	.uleb128 0x4
	.4byte	.LASF56
	.byte	0x2f
	.uleb128 0x4
	.4byte	.LASF57
	.byte	0x30
	.uleb128 0x4
	.4byte	.LASF58
	.byte	0x31
	.uleb128 0x4
	.4byte	.LASF59
	.byte	0x32
	.uleb128 0x4
	.4byte	.LASF60
	.byte	0x33
	.uleb128 0x4
	.4byte	.LASF61
	.byte	0x34
	.uleb128 0x4
	.4byte	.LASF62
	.byte	0x35
	.uleb128 0x4
	.4byte	.LASF63
	.byte	0x36
	.uleb128 0x4
	.4byte	.LASF64
	.byte	0x37
	.uleb128 0x4
	.4byte	.LASF65
	.byte	0x38
	.uleb128 0x4
	.4byte	.LASF66
	.byte	0x39
	.uleb128 0x4
	.4byte	.LASF67
	.byte	0x3a
	.uleb128 0x4
	.4byte	.LASF68
	.byte	0x3b
	.uleb128 0x4
	.4byte	.LASF69
	.byte	0x3c
	.uleb128 0x4
	.4byte	.LASF70
	.byte	0x3d
	.uleb128 0x4
	.4byte	.LASF71
	.byte	0x3e
	.uleb128 0x4
	.4byte	.LASF72
	.byte	0x3f
	.uleb128 0x4
	.4byte	.LASF73
	.byte	0x40
	.uleb128 0x4
	.4byte	.LASF74
	.byte	0x41
	.uleb128 0x4
	.4byte	.LASF75
	.byte	0x42
	.uleb128 0x4
	.4byte	.LASF76
	.byte	0x43
	.uleb128 0x4
	.4byte	.LASF77
	.byte	0x44
	.uleb128 0x4
	.4byte	.LASF78
	.byte	0x45
	.uleb128 0x4
	.4byte	.LASF79
	.byte	0x46
	.uleb128 0x4
	.4byte	.LASF80
	.byte	0x47
	.uleb128 0x4
	.4byte	.LASF81
	.byte	0x48
	.uleb128 0x4
	.4byte	.LASF82
	.byte	0x49
	.uleb128 0x4
	.4byte	.LASF83
	.byte	0x4a
	.uleb128 0x4
	.4byte	.LASF84
	.byte	0x4b
	.uleb128 0x4
	.4byte	.LASF85
	.byte	0x4c
	.uleb128 0x4
	.4byte	.LASF86
	.byte	0x4d
	.uleb128 0x4
	.4byte	.LASF87
	.byte	0x50
	.uleb128 0x4
	.4byte	.LASF88
	.byte	0x51
	.byte	0
	.uleb128 0x5
	.byte	0x1
	.byte	0x6
	.4byte	.LASF89
	.uleb128 0x6
	.4byte	.LASF94
	.byte	0x2
	.byte	0x9e
	.byte	0x3
	.4byte	0x29
	.uleb128 0x5
	.byte	0x1
	.byte	0x8
	.4byte	.LASF90
	.uleb128 0x5
	.byte	0x2
	.byte	0x5
	.4byte	.LASF91
	.uleb128 0x5
	.byte	0x2
	.byte	0x7
	.4byte	.LASF92
	.uleb128 0x5
	.byte	0x4
	.byte	0x5
	.4byte	.LASF93
	.uleb128 0x6
	.4byte	.LASF95
	.byte	0x3
	.byte	0x4f
	.byte	0x19
	.4byte	0x289
	.uleb128 0x5
	.byte	0x4
	.byte	0x7
	.4byte	.LASF96
	.uleb128 0x5
	.byte	0x8
	.byte	0x5
	.4byte	.LASF97
	.uleb128 0x5
	.byte	0x8
	.byte	0x7
	.4byte	.LASF98
	.uleb128 0x7
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x5
	.byte	0x4
	.byte	0x7
	.4byte	.LASF99
	.uleb128 0x6
	.4byte	.LASF100
	.byte	0x4
	.byte	0x30
	.byte	0x14
	.4byte	0x27d
	.uleb128 0x8
	.4byte	0x2ac
	.uleb128 0x9
	.4byte	0x2b8
	.uleb128 0xa
	.byte	0x10
	.byte	0x5
	.2byte	0x2f7
	.byte	0x9
	.4byte	0x30d
	.uleb128 0xb
	.4byte	.LASF101
	.byte	0x5
	.2byte	0x2f9
	.byte	0x12
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xb
	.4byte	.LASF102
	.byte	0x5
	.2byte	0x2fa
	.byte	0x12
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xc
	.ascii	"VAL\000"
	.byte	0x5
	.2byte	0x2fb
	.byte	0x12
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xb
	.4byte	.LASF103
	.byte	0x5
	.2byte	0x2fc
	.byte	0x12
	.4byte	0x2bd
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.byte	0
	.uleb128 0xd
	.4byte	.LASF104
	.byte	0x5
	.2byte	0x2fd
	.byte	0x3
	.4byte	0x2c2
	.uleb128 0xe
	.4byte	.LASF166
	.byte	0x8
	.byte	0x39
	.byte	0x11
	.4byte	0x2ac
	.byte	0x1
	.byte	0x1
	.uleb128 0xa
	.byte	0x14
	.byte	0x2
	.2byte	0x185
	.byte	0x9
	.4byte	0x382
	.uleb128 0xb
	.4byte	.LASF105
	.byte	0x2
	.2byte	0x187
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xc
	.ascii	"CR\000"
	.byte	0x2
	.2byte	0x188
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xb
	.4byte	.LASF106
	.byte	0x2
	.2byte	0x189
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xb
	.4byte	.LASF107
	.byte	0x2
	.2byte	0x18a
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0xb
	.4byte	.LASF108
	.byte	0x2
	.2byte	0x18b
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.byte	0
	.uleb128 0xd
	.4byte	.LASF109
	.byte	0x2
	.2byte	0x18c
	.byte	0x3
	.4byte	0x328
	.uleb128 0xa
	.byte	0x98
	.byte	0x2
	.2byte	0x29e
	.byte	0x9
	.4byte	0x5ff
	.uleb128 0xc
	.ascii	"CR\000"
	.byte	0x2
	.2byte	0x2a0
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xb
	.4byte	.LASF110
	.byte	0x2
	.2byte	0x2a1
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xb
	.4byte	.LASF111
	.byte	0x2
	.2byte	0x2a2
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xb
	.4byte	.LASF112
	.byte	0x2
	.2byte	0x2a3
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0xb
	.4byte	.LASF113
	.byte	0x2
	.2byte	0x2a4
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xb
	.4byte	.LASF114
	.byte	0x2
	.2byte	0x2a5
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0xb
	.4byte	.LASF115
	.byte	0x2
	.2byte	0x2a6
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xb
	.4byte	.LASF116
	.byte	0x2
	.2byte	0x2a7
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0xb
	.4byte	.LASF117
	.byte	0x2
	.2byte	0x2a8
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xb
	.4byte	.LASF118
	.byte	0x2
	.2byte	0x2a9
	.byte	0x11
	.4byte	0x2ac
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0xb
	.4byte	.LASF119
	.byte	0x2
	.2byte	0x2aa
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xb
	.4byte	.LASF120
	.byte	0x2
	.2byte	0x2ab
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0xb
	.4byte	.LASF121
	.byte	0x2
	.2byte	0x2ac
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xb
	.4byte	.LASF122
	.byte	0x2
	.2byte	0x2ad
	.byte	0x11
	.4byte	0x2ac
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.uleb128 0xb
	.4byte	.LASF123
	.byte	0x2
	.2byte	0x2ae
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0xb
	.4byte	.LASF124
	.byte	0x2
	.2byte	0x2af
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x3c
	.uleb128 0xb
	.4byte	.LASF125
	.byte	0x2
	.2byte	0x2b0
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0xb
	.4byte	.LASF126
	.byte	0x2
	.2byte	0x2b1
	.byte	0x11
	.4byte	0x2ac
	.byte	0x2
	.byte	0x23
	.uleb128 0x44
	.uleb128 0xb
	.4byte	.LASF127
	.byte	0x2
	.2byte	0x2b2
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0xb
	.4byte	.LASF128
	.byte	0x2
	.2byte	0x2b3
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x4c
	.uleb128 0xb
	.4byte	.LASF129
	.byte	0x2
	.2byte	0x2b4
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0xb
	.4byte	.LASF130
	.byte	0x2
	.2byte	0x2b5
	.byte	0x11
	.4byte	0x2ac
	.byte	0x2
	.byte	0x23
	.uleb128 0x54
	.uleb128 0xb
	.4byte	.LASF131
	.byte	0x2
	.2byte	0x2b6
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0xb
	.4byte	.LASF132
	.byte	0x2
	.2byte	0x2b7
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x5c
	.uleb128 0xb
	.4byte	.LASF133
	.byte	0x2
	.2byte	0x2b8
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x60
	.uleb128 0xb
	.4byte	.LASF134
	.byte	0x2
	.2byte	0x2b9
	.byte	0x11
	.4byte	0x2ac
	.byte	0x2
	.byte	0x23
	.uleb128 0x64
	.uleb128 0xb
	.4byte	.LASF135
	.byte	0x2
	.2byte	0x2ba
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x68
	.uleb128 0xb
	.4byte	.LASF136
	.byte	0x2
	.2byte	0x2bb
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x6c
	.uleb128 0xb
	.4byte	.LASF137
	.byte	0x2
	.2byte	0x2bc
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x70
	.uleb128 0xb
	.4byte	.LASF138
	.byte	0x2
	.2byte	0x2bd
	.byte	0x11
	.4byte	0x2ac
	.byte	0x2
	.byte	0x23
	.uleb128 0x74
	.uleb128 0xb
	.4byte	.LASF139
	.byte	0x2
	.2byte	0x2be
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x78
	.uleb128 0xb
	.4byte	.LASF140
	.byte	0x2
	.2byte	0x2bf
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x7c
	.uleb128 0xb
	.4byte	.LASF141
	.byte	0x2
	.2byte	0x2c0
	.byte	0x11
	.4byte	0x2b8
	.byte	0x3
	.byte	0x23
	.uleb128 0x80
	.uleb128 0xb
	.4byte	.LASF142
	.byte	0x2
	.2byte	0x2c1
	.byte	0x11
	.4byte	0x2ac
	.byte	0x3
	.byte	0x23
	.uleb128 0x84
	.uleb128 0xb
	.4byte	.LASF143
	.byte	0x2
	.2byte	0x2c2
	.byte	0x11
	.4byte	0x2b8
	.byte	0x3
	.byte	0x23
	.uleb128 0x88
	.uleb128 0xb
	.4byte	.LASF144
	.byte	0x2
	.2byte	0x2c3
	.byte	0x11
	.4byte	0x2ac
	.byte	0x3
	.byte	0x23
	.uleb128 0x8c
	.uleb128 0xb
	.4byte	.LASF145
	.byte	0x2
	.2byte	0x2c4
	.byte	0x11
	.4byte	0x2b8
	.byte	0x3
	.byte	0x23
	.uleb128 0x90
	.uleb128 0xc
	.ascii	"CSR\000"
	.byte	0x2
	.2byte	0x2c5
	.byte	0x11
	.4byte	0x2b8
	.byte	0x3
	.byte	0x23
	.uleb128 0x94
	.byte	0
	.uleb128 0xd
	.4byte	.LASF146
	.byte	0x2
	.2byte	0x2c6
	.byte	0x3
	.4byte	0x38f
	.uleb128 0xa
	.byte	0x28
	.byte	0x2
	.2byte	0x35e
	.byte	0x9
	.4byte	0x687
	.uleb128 0xb
	.4byte	.LASF147
	.byte	0x2
	.2byte	0x360
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xb
	.4byte	.LASF148
	.byte	0x2
	.2byte	0x361
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xb
	.4byte	.LASF149
	.byte	0x2
	.2byte	0x362
	.byte	0x11
	.4byte	0x697
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xb
	.4byte	.LASF150
	.byte	0x2
	.2byte	0x363
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xb
	.4byte	.LASF151
	.byte	0x2
	.2byte	0x364
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0xb
	.4byte	.LASF152
	.byte	0x2
	.2byte	0x365
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xc
	.ascii	"SKR\000"
	.byte	0x2
	.2byte	0x366
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.byte	0
	.uleb128 0xf
	.4byte	0x2b8
	.4byte	0x697
	.uleb128 0x10
	.4byte	0x2a5
	.byte	0x3
	.byte	0
	.uleb128 0x8
	.4byte	0x687
	.uleb128 0xd
	.4byte	.LASF153
	.byte	0x2
	.2byte	0x367
	.byte	0x3
	.4byte	0x60c
	.uleb128 0xa
	.byte	0x8
	.byte	0x2
	.2byte	0x3be
	.byte	0x9
	.4byte	0x6d4
	.uleb128 0xc
	.ascii	"CSR\000"
	.byte	0x2
	.2byte	0x3c0
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xc
	.ascii	"CCR\000"
	.byte	0x2
	.2byte	0x3c1
	.byte	0x11
	.4byte	0x2b8
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0
	.uleb128 0xd
	.4byte	.LASF154
	.byte	0x2
	.2byte	0x3c2
	.byte	0x3
	.4byte	0x6a9
	.uleb128 0x5
	.byte	0x8
	.byte	0x4
	.4byte	.LASF155
	.uleb128 0x2
	.byte	0x7
	.byte	0x1
	.4byte	0x261
	.byte	0x6
	.byte	0x27
	.byte	0x1
	.4byte	0x70f
	.uleb128 0x4
	.4byte	.LASF156
	.byte	0
	.uleb128 0x4
	.4byte	.LASF157
	.byte	0x1
	.uleb128 0x4
	.4byte	.LASF158
	.byte	0x2
	.uleb128 0x4
	.4byte	.LASF159
	.byte	0x3
	.byte	0
	.uleb128 0x6
	.4byte	.LASF160
	.byte	0x6
	.byte	0x2c
	.byte	0x3
	.4byte	0x6e8
	.uleb128 0x2
	.byte	0x7
	.byte	0x1
	.4byte	0x261
	.byte	0x7
	.byte	0x30
	.byte	0x1
	.4byte	0x742
	.uleb128 0x4
	.4byte	.LASF161
	.byte	0x64
	.uleb128 0x4
	.4byte	.LASF162
	.byte	0xa
	.uleb128 0x4
	.4byte	.LASF163
	.byte	0x1
	.uleb128 0x4
	.4byte	.LASF164
	.byte	0x1
	.byte	0
	.uleb128 0x6
	.4byte	.LASF165
	.byte	0x7
	.byte	0x35
	.byte	0x3
	.4byte	0x71b
	.uleb128 0x11
	.4byte	.LASF167
	.byte	0x7
	.2byte	0x26a
	.byte	0x16
	.4byte	0x2b8
	.byte	0x1
	.byte	0x1
	.uleb128 0x11
	.4byte	.LASF168
	.byte	0x7
	.2byte	0x26b
	.byte	0x11
	.4byte	0x2ac
	.byte	0x1
	.byte	0x1
	.uleb128 0x11
	.4byte	.LASF169
	.byte	0x7
	.2byte	0x26c
	.byte	0x1c
	.4byte	0x742
	.byte	0x1
	.byte	0x1
	.uleb128 0x12
	.4byte	0x74e
	.byte	0x1
	.byte	0x5a
	.byte	0xf
	.byte	0x5
	.byte	0x3
	.4byte	uwTick
	.uleb128 0x12
	.4byte	0x75d
	.byte	0x1
	.byte	0x5b
	.byte	0xa
	.byte	0x5
	.byte	0x3
	.4byte	uwTickPrio
	.uleb128 0x12
	.4byte	0x76c
	.byte	0x1
	.byte	0x5c
	.byte	0x15
	.byte	0x5
	.byte	0x3
	.4byte	uwTickFreq
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF170
	.byte	0x9
	.2byte	0x10f
	.byte	0x6
	.byte	0x1
	.byte	0x1
	.4byte	0x7c5
	.uleb128 0x14
	.4byte	0x255
	.uleb128 0x14
	.4byte	0x2ac
	.uleb128 0x14
	.4byte	0x2ac
	.byte	0
	.uleb128 0x15
	.byte	0x1
	.4byte	.LASF220
	.byte	0x9
	.2byte	0x113
	.byte	0xa
	.byte	0x1
	.4byte	0x2ac
	.byte	0x1
	.4byte	0x7df
	.uleb128 0x14
	.4byte	0x2ac
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF171
	.byte	0x9
	.2byte	0x10e
	.byte	0x6
	.byte	0x1
	.byte	0x1
	.4byte	0x7f5
	.uleb128 0x14
	.4byte	0x2ac
	.byte	0
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF172
	.byte	0x1
	.2byte	0x2e9
	.byte	0x6
	.byte	0x1
	.4byte	.LFB108
	.4byte	.LFE108
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF173
	.byte	0x1
	.2byte	0x2df
	.byte	0x6
	.byte	0x1
	.4byte	.LFB107
	.4byte	.LFE107
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF174
	.byte	0x1
	.2byte	0x2d4
	.byte	0x6
	.byte	0x1
	.4byte	.LFB106
	.4byte	.LFE106
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x17
	.byte	0x1
	.4byte	.LASF202
	.byte	0x1
	.2byte	0x2ba
	.byte	0x13
	.byte	0x1
	.4byte	0x70f
	.4byte	.LFB105
	.4byte	.LFE105
	.4byte	.LLST14
	.byte	0x1
	.4byte	0x882
	.uleb128 0x18
	.4byte	.LASF175
	.byte	0x1
	.2byte	0x2bc
	.byte	0xd
	.4byte	0x2ac
	.4byte	.LLST15
	.4byte	.LVUS15
	.uleb128 0x19
	.4byte	.LVL30
	.4byte	0xbaf
	.uleb128 0x19
	.4byte	.LVL32
	.4byte	0xbaf
	.byte	0
	.uleb128 0x1a
	.byte	0x1
	.4byte	.LASF176
	.byte	0x1
	.2byte	0x2ae
	.byte	0x6
	.byte	0x1
	.4byte	.LFB104
	.4byte	.LFE104
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x8ad
	.uleb128 0x1b
	.4byte	.LASF178
	.byte	0x1
	.2byte	0x2ae
	.byte	0x31
	.4byte	0x2ac
	.byte	0x1
	.byte	0x50
	.byte	0
	.uleb128 0x1a
	.byte	0x1
	.4byte	.LASF177
	.byte	0x1
	.2byte	0x2a2
	.byte	0x6
	.byte	0x1
	.4byte	.LFB103
	.4byte	.LFE103
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x8d8
	.uleb128 0x1b
	.4byte	.LASF179
	.byte	0x1
	.2byte	0x2a2
	.byte	0x36
	.4byte	0x2ac
	.byte	0x1
	.byte	0x50
	.byte	0
	.uleb128 0x1a
	.byte	0x1
	.4byte	.LASF180
	.byte	0x1
	.2byte	0x292
	.byte	0x6
	.byte	0x1
	.4byte	.LFB102
	.4byte	.LFE102
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x903
	.uleb128 0x1b
	.4byte	.LASF181
	.byte	0x1
	.2byte	0x292
	.byte	0x37
	.4byte	0x2ac
	.byte	0x1
	.byte	0x50
	.byte	0
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF182
	.byte	0x1
	.2byte	0x281
	.byte	0x6
	.byte	0x1
	.4byte	.LFB101
	.4byte	.LFE101
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF183
	.byte	0x1
	.2byte	0x272
	.byte	0x6
	.byte	0x1
	.4byte	.LFB100
	.4byte	.LFE100
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF184
	.byte	0x1
	.2byte	0x25f
	.byte	0x6
	.byte	0x1
	.4byte	.LFB99
	.4byte	.LFE99
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF185
	.byte	0x1
	.2byte	0x23e
	.byte	0x6
	.byte	0x1
	.4byte	.LFB98
	.4byte	.LFE98
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF186
	.byte	0x1
	.2byte	0x235
	.byte	0x6
	.byte	0x1
	.4byte	.LFB97
	.4byte	.LFE97
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF187
	.byte	0x1
	.2byte	0x22c
	.byte	0x6
	.byte	0x1
	.4byte	.LFB96
	.4byte	.LFE96
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF188
	.byte	0x1
	.2byte	0x223
	.byte	0x6
	.byte	0x1
	.4byte	.LFB95
	.4byte	.LFE95
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF189
	.byte	0x1
	.2byte	0x21a
	.byte	0x6
	.byte	0x1
	.4byte	.LFB94
	.4byte	.LFE94
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF190
	.byte	0x1
	.2byte	0x211
	.byte	0x6
	.byte	0x1
	.4byte	.LFB93
	.4byte	.LFE93
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x1c
	.byte	0x1
	.4byte	.LASF191
	.byte	0x1
	.2byte	0x1f4
	.byte	0xa
	.byte	0x1
	.4byte	0x2ac
	.4byte	.LFB92
	.4byte	.LFE92
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x1c
	.byte	0x1
	.4byte	.LASF192
	.byte	0x1
	.2byte	0x1eb
	.byte	0xa
	.byte	0x1
	.4byte	0x2ac
	.4byte	.LFB91
	.4byte	.LFE91
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x1c
	.byte	0x1
	.4byte	.LASF193
	.byte	0x1
	.2byte	0x1e2
	.byte	0xa
	.byte	0x1
	.4byte	0x2ac
	.4byte	.LFB90
	.4byte	.LFE90
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x1c
	.byte	0x1
	.4byte	.LASF194
	.byte	0x1
	.2byte	0x1d9
	.byte	0xa
	.byte	0x1
	.4byte	0x2ac
	.4byte	.LFB89
	.4byte	.LFE89
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x1c
	.byte	0x1
	.4byte	.LASF195
	.byte	0x1
	.2byte	0x1d0
	.byte	0xa
	.byte	0x1
	.4byte	0x2ac
	.4byte	.LFB88
	.4byte	.LFE88
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x1c
	.byte	0x1
	.4byte	.LASF196
	.byte	0x1
	.2byte	0x1c7
	.byte	0xa
	.byte	0x1
	.4byte	0x2ac
	.4byte	.LFB87
	.4byte	.LFE87
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF197
	.byte	0x1
	.2byte	0x1bd
	.byte	0xd
	.byte	0x1
	.4byte	.LFB86
	.4byte	.LFE86
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF198
	.byte	0x1
	.2byte	0x1ad
	.byte	0xd
	.byte	0x1
	.4byte	.LFB85
	.4byte	.LFE85
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x1d
	.byte	0x1
	.4byte	.LASF199
	.byte	0x1
	.2byte	0x193
	.byte	0xd
	.byte	0x1
	.4byte	.LFB84
	.4byte	.LFE84
	.4byte	.LLST10
	.byte	0x1
	.4byte	0xb10
	.uleb128 0x1e
	.4byte	.LASF204
	.byte	0x1
	.2byte	0x193
	.byte	0x20
	.4byte	0x2ac
	.4byte	.LLST11
	.4byte	.LVUS11
	.uleb128 0x18
	.4byte	.LASF175
	.byte	0x1
	.2byte	0x195
	.byte	0xc
	.4byte	0x2ac
	.4byte	.LLST12
	.4byte	.LVUS12
	.uleb128 0x18
	.4byte	.LASF200
	.byte	0x1
	.2byte	0x196
	.byte	0xc
	.4byte	0x2ac
	.4byte	.LLST13
	.4byte	.LVUS13
	.uleb128 0x19
	.4byte	.LVL22
	.4byte	0xbaf
	.uleb128 0x19
	.4byte	.LVL25
	.4byte	0xbaf
	.byte	0
	.uleb128 0x1c
	.byte	0x1
	.4byte	.LASF201
	.byte	0x1
	.2byte	0x183
	.byte	0x15
	.byte	0x1
	.4byte	0x742
	.4byte	.LFB83
	.4byte	.LFE83
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x17
	.byte	0x1
	.4byte	.LASF203
	.byte	0x1
	.2byte	0x165
	.byte	0x13
	.byte	0x1
	.4byte	0x70f
	.4byte	.LFB82
	.4byte	.LFE82
	.4byte	.LLST6
	.byte	0x1
	.4byte	0xb94
	.uleb128 0x1e
	.4byte	.LASF205
	.byte	0x1
	.2byte	0x165
	.byte	0x37
	.4byte	0x742
	.4byte	.LLST7
	.4byte	.LVUS7
	.uleb128 0x18
	.4byte	.LASF206
	.byte	0x1
	.2byte	0x167
	.byte	0x15
	.4byte	0x70f
	.4byte	.LLST8
	.4byte	.LVUS8
	.uleb128 0x18
	.4byte	.LASF207
	.byte	0x1
	.2byte	0x168
	.byte	0x17
	.4byte	0x742
	.4byte	.LLST9
	.4byte	.LVUS9
	.uleb128 0x19
	.4byte	.LVL20
	.4byte	0xbe1
	.byte	0
	.uleb128 0x1c
	.byte	0x1
	.4byte	.LASF208
	.byte	0x1
	.2byte	0x15b
	.byte	0xa
	.byte	0x1
	.4byte	0x2ac
	.4byte	.LFB81
	.4byte	.LFE81
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x1c
	.byte	0x1
	.4byte	.LASF209
	.byte	0x1
	.2byte	0x152
	.byte	0x11
	.byte	0x1
	.4byte	0x2ac
	.4byte	.LFB80
	.4byte	.LFE80
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF210
	.byte	0x1
	.2byte	0x147
	.byte	0xd
	.byte	0x1
	.4byte	.LFB79
	.4byte	.LFE79
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x17
	.byte	0x1
	.4byte	.LASF211
	.byte	0x1
	.2byte	0x103
	.byte	0x1a
	.byte	0x1
	.4byte	0x70f
	.4byte	.LFB78
	.4byte	.LFE78
	.4byte	.LLST1
	.byte	0x1
	.4byte	0xc50
	.uleb128 0x1e
	.4byte	.LASF212
	.byte	0x1
	.2byte	0x103
	.byte	0x30
	.4byte	0x2ac
	.4byte	.LLST2
	.4byte	.LVUS2
	.uleb128 0x18
	.4byte	.LASF206
	.byte	0x1
	.2byte	0x105
	.byte	0x16
	.4byte	0x70f
	.4byte	.LLST3
	.4byte	.LVUS3
	.uleb128 0x19
	.4byte	.LVL5
	.4byte	0x7c5
	.uleb128 0x1f
	.4byte	.LVL6
	.4byte	0x7a5
	.uleb128 0x20
	.byte	0x1
	.byte	0x50
	.byte	0x2
	.byte	0x9
	.byte	0xff
	.uleb128 0x20
	.byte	0x1
	.byte	0x51
	.byte	0x2
	.byte	0x74
	.sleb128 0
	.uleb128 0x20
	.byte	0x1
	.byte	0x52
	.byte	0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x21
	.byte	0x1
	.4byte	.LASF213
	.byte	0x1
	.byte	0xec
	.byte	0xd
	.byte	0x1
	.4byte	.LFB77
	.4byte	.LFE77
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x21
	.byte	0x1
	.4byte	.LASF214
	.byte	0x1
	.byte	0xe1
	.byte	0xd
	.byte	0x1
	.4byte	.LFB76
	.4byte	.LFE76
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x22
	.byte	0x1
	.4byte	.LASF215
	.byte	0x1
	.byte	0xc4
	.byte	0x13
	.byte	0x1
	.4byte	0x70f
	.4byte	.LFB75
	.4byte	.LFE75
	.4byte	.LLST0
	.byte	0x1
	.4byte	0xca5
	.uleb128 0x19
	.4byte	.LVL0
	.4byte	0xc50
	.byte	0
	.uleb128 0x23
	.byte	0x1
	.4byte	.LASF216
	.byte	0x1
	.byte	0x98
	.byte	0x13
	.byte	0x1
	.4byte	0x70f
	.4byte	.LFB74
	.4byte	.LFE74
	.4byte	.LLST4
	.byte	0x1
	.uleb128 0x24
	.4byte	.LASF206
	.byte	0x1
	.byte	0x9a
	.byte	0x16
	.4byte	0x70f
	.4byte	.LLST5
	.4byte	.LVUS5
	.uleb128 0x25
	.4byte	.LVL10
	.4byte	0x7df
	.4byte	0xce7
	.uleb128 0x20
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.byte	0x33
	.byte	0
	.uleb128 0x25
	.4byte	.LVL11
	.4byte	0xbe1
	.4byte	0xcfa
	.uleb128 0x20
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.byte	0x30
	.byte	0
	.uleb128 0x19
	.4byte	.LVL14
	.4byte	0xc66
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
	.uleb128 0x3
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x5
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
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0x8
	.uleb128 0x35
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0xc
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
	.uleb128 0xf
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x11
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
	.uleb128 0x12
	.uleb128 0x34
	.byte	0
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x2
	.uleb128 0xa
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
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0xc
	.uleb128 0x1
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
	.uleb128 0x19
	.uleb128 0x4109
	.byte	0
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
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1c
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
	.uleb128 0x1e
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
	.uleb128 0x1f
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x2e
	.byte	0
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
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x22
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
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST14:
	.4byte	.LFB105
	.4byte	.LCFI5
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI5
	.4byte	.LFE105
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LVUS15:
	.uleb128 .LVU194
	.uleb128 .LVU195
	.uleb128 .LVU195
	.uleb128 .LVU205
.LLST15:
	.4byte	.LVL31
	.4byte	.LVL31
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL31
	.4byte	.LVL33
	.2byte	0x1
	.byte	0x54
	.4byte	0
	.4byte	0
.LLST10:
	.4byte	.LFB84
	.4byte	.LCFI4
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI4
	.4byte	.LFE84
	.2byte	0x2
	.byte	0x7d
	.sleb128 16
	.4byte	0
	.4byte	0
.LVUS11:
	.uleb128 0
	.uleb128 .LVU99
	.uleb128 .LVU99
	.uleb128 .LVU106
	.uleb128 .LVU106
	.uleb128 0
.LLST11:
	.4byte	.LVL21
	.4byte	.LVL22-1
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL22-1
	.4byte	.LVL24
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL24
	.4byte	.LFE84
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS12:
	.uleb128 .LVU100
	.uleb128 .LVU106
	.uleb128 .LVU106
	.uleb128 .LVU112
.LLST12:
	.4byte	.LVL23
	.4byte	.LVL24
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL24
	.4byte	.LVL26
	.2byte	0x1
	.byte	0x55
	.4byte	0
	.4byte	0
.LVUS13:
	.uleb128 .LVU101
	.uleb128 .LVU112
.LLST13:
	.4byte	.LVL23
	.4byte	.LVL26
	.2byte	0x1
	.byte	0x54
	.4byte	0
	.4byte	0
.LLST6:
	.4byte	.LFB82
	.4byte	.LCFI3
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI3
	.4byte	.LFE82
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LVUS7:
	.uleb128 0
	.uleb128 .LVU80
	.uleb128 .LVU80
	.uleb128 .LVU82
	.uleb128 .LVU82
	.uleb128 .LVU87
	.uleb128 .LVU87
	.uleb128 .LVU88
	.uleb128 .LVU88
	.uleb128 0
.LLST7:
	.4byte	.LVL15
	.4byte	.LVL17
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL17
	.4byte	.LVL18
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL18
	.4byte	.LVL19
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL19
	.4byte	.LVL20-1
	.2byte	0x5
	.byte	0x3
	.4byte	uwTickFreq
	.4byte	.LVL20-1
	.4byte	.LFE82
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS8:
	.uleb128 .LVU75
	.uleb128 .LVU80
	.uleb128 .LVU80
	.uleb128 .LVU82
	.uleb128 .LVU82
	.uleb128 .LVU88
	.uleb128 .LVU88
	.uleb128 0
.LLST8:
	.4byte	.LVL16
	.4byte	.LVL17
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL17
	.4byte	.LVL18
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL18
	.4byte	.LVL20
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL20
	.4byte	.LFE82
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LVUS9:
	.uleb128 .LVU83
	.uleb128 0
.LLST9:
	.4byte	.LVL18
	.4byte	.LFE82
	.2byte	0x1
	.byte	0x54
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LFB78
	.4byte	.LCFI1
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI1
	.4byte	.LFE78
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LVUS2:
	.uleb128 0
	.uleb128 .LVU30
	.uleb128 .LVU30
	.uleb128 .LVU32
	.uleb128 .LVU32
	.uleb128 .LVU35
	.uleb128 .LVU35
	.uleb128 .LVU48
	.uleb128 .LVU48
	.uleb128 0
.LLST2:
	.4byte	.LVL1
	.4byte	.LVL2
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL2
	.4byte	.LVL3
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL3
	.4byte	.LVL4
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL4
	.4byte	.LVL8
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL8
	.4byte	.LFE78
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS3:
	.uleb128 .LVU26
	.uleb128 .LVU30
	.uleb128 .LVU30
	.uleb128 .LVU32
	.uleb128 .LVU32
	.uleb128 .LVU46
	.uleb128 .LVU46
	.uleb128 0
.LLST3:
	.4byte	.LVL1
	.4byte	.LVL2
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL2
	.4byte	.LVL3
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL3
	.4byte	.LVL7
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL7
	.4byte	.LFE78
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LLST0:
	.4byte	.LFB75
	.4byte	.LCFI0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI0
	.4byte	.LFE75
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LLST4:
	.4byte	.LFB74
	.4byte	.LCFI2
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI2
	.4byte	.LFE74
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LVUS5:
	.uleb128 .LVU51
	.uleb128 .LVU56
	.uleb128 .LVU56
	.uleb128 .LVU58
	.uleb128 .LVU58
	.uleb128 0
.LLST5:
	.4byte	.LVL9
	.4byte	.LVL12
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL12
	.4byte	.LVL13
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL13
	.4byte	.LFE74
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x12c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB76
	.4byte	.LFE76-.LFB76
	.4byte	.LFB77
	.4byte	.LFE77-.LFB77
	.4byte	.LFB75
	.4byte	.LFE75-.LFB75
	.4byte	.LFB78
	.4byte	.LFE78-.LFB78
	.4byte	.LFB74
	.4byte	.LFE74-.LFB74
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
	.4byte	.LFB86
	.4byte	.LFE86-.LFB86
	.4byte	.LFB87
	.4byte	.LFE87-.LFB87
	.4byte	.LFB88
	.4byte	.LFE88-.LFB88
	.4byte	.LFB89
	.4byte	.LFE89-.LFB89
	.4byte	.LFB90
	.4byte	.LFE90-.LFB90
	.4byte	.LFB91
	.4byte	.LFE91-.LFB91
	.4byte	.LFB92
	.4byte	.LFE92-.LFB92
	.4byte	.LFB93
	.4byte	.LFE93-.LFB93
	.4byte	.LFB94
	.4byte	.LFE94-.LFB94
	.4byte	.LFB95
	.4byte	.LFE95-.LFB95
	.4byte	.LFB96
	.4byte	.LFE96-.LFB96
	.4byte	.LFB97
	.4byte	.LFE97-.LFB97
	.4byte	.LFB98
	.4byte	.LFE98-.LFB98
	.4byte	.LFB99
	.4byte	.LFE99-.LFB99
	.4byte	.LFB100
	.4byte	.LFE100-.LFB100
	.4byte	.LFB101
	.4byte	.LFE101-.LFB101
	.4byte	.LFB102
	.4byte	.LFE102-.LFB102
	.4byte	.LFB103
	.4byte	.LFE103-.LFB103
	.4byte	.LFB104
	.4byte	.LFE104-.LFB104
	.4byte	.LFB105
	.4byte	.LFE105-.LFB105
	.4byte	.LFB106
	.4byte	.LFE106-.LFB106
	.4byte	.LFB107
	.4byte	.LFE107-.LFB107
	.4byte	.LFB108
	.4byte	.LFE108-.LFB108
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LFB76
	.4byte	.LFE76
	.4byte	.LFB77
	.4byte	.LFE77
	.4byte	.LFB75
	.4byte	.LFE75
	.4byte	.LFB78
	.4byte	.LFE78
	.4byte	.LFB74
	.4byte	.LFE74
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
	.4byte	.LFB86
	.4byte	.LFE86
	.4byte	.LFB87
	.4byte	.LFE87
	.4byte	.LFB88
	.4byte	.LFE88
	.4byte	.LFB89
	.4byte	.LFE89
	.4byte	.LFB90
	.4byte	.LFE90
	.4byte	.LFB91
	.4byte	.LFE91
	.4byte	.LFB92
	.4byte	.LFE92
	.4byte	.LFB93
	.4byte	.LFE93
	.4byte	.LFB94
	.4byte	.LFE94
	.4byte	.LFB95
	.4byte	.LFE95
	.4byte	.LFB96
	.4byte	.LFE96
	.4byte	.LFB97
	.4byte	.LFE97
	.4byte	.LFB98
	.4byte	.LFE98
	.4byte	.LFB99
	.4byte	.LFE99
	.4byte	.LFB100
	.4byte	.LFE100
	.4byte	.LFB101
	.4byte	.LFE101
	.4byte	.LFB102
	.4byte	.LFE102
	.4byte	.LFB103
	.4byte	.LFE103
	.4byte	.LFB104
	.4byte	.LFE104
	.4byte	.LFB105
	.4byte	.LFE105
	.4byte	.LFB106
	.4byte	.LFE106
	.4byte	.LFB107
	.4byte	.LFE107
	.4byte	.LFB108
	.4byte	.LFE108
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF196:
	.ascii	"HAL_GetHalVersion\000"
.LASF35:
	.ascii	"TIM1_TRG_COM_TIM17_IRQn\000"
.LASF51:
	.ascii	"DFSDM1_FLT3_IRQn\000"
.LASF29:
	.ascii	"CAN1_RX0_IRQn\000"
.LASF32:
	.ascii	"EXTI9_5_IRQn\000"
.LASF73:
	.ascii	"COMP_IRQn\000"
.LASF212:
	.ascii	"TickPriority\000"
.LASF40:
	.ascii	"I2C1_EV_IRQn\000"
.LASF220:
	.ascii	"HAL_SYSTICK_Config\000"
.LASF158:
	.ascii	"HAL_BUSY\000"
.LASF203:
	.ascii	"HAL_SetTickFreq\000"
.LASF58:
	.ascii	"SDMMC1_IRQn\000"
.LASF161:
	.ascii	"HAL_TICK_FREQ_10HZ\000"
.LASF147:
	.ascii	"MEMRMP\000"
.LASF30:
	.ascii	"CAN1_RX1_IRQn\000"
.LASF116:
	.ascii	"CIFR\000"
.LASF98:
	.ascii	"long long unsigned int\000"
.LASF65:
	.ascii	"DMA2_Channel1_IRQn\000"
.LASF105:
	.ascii	"IDCODE\000"
.LASF50:
	.ascii	"RTC_Alarm_IRQn\000"
.LASF43:
	.ascii	"I2C2_ER_IRQn\000"
.LASF39:
	.ascii	"TIM4_IRQn\000"
.LASF12:
	.ascii	"RTC_WKUP_IRQn\000"
.LASF177:
	.ascii	"HAL_SYSCFG_VREFBUF_HighImpedanceConfig\000"
.LASF9:
	.ascii	"WWDG_IRQn\000"
.LASF115:
	.ascii	"CIER\000"
.LASF55:
	.ascii	"TIM8_CC_IRQn\000"
.LASF97:
	.ascii	"long long int\000"
.LASF89:
	.ascii	"signed char\000"
.LASF86:
	.ascii	"TSC_IRQn\000"
.LASF117:
	.ascii	"CICR\000"
.LASF186:
	.ascii	"HAL_DBGMCU_EnableDBGStandbyMode\000"
.LASF135:
	.ascii	"AHB1SMENR\000"
.LASF141:
	.ascii	"APB2SMENR\000"
.LASF200:
	.ascii	"wait\000"
.LASF69:
	.ascii	"DMA2_Channel5_IRQn\000"
.LASF93:
	.ascii	"long int\000"
.LASF125:
	.ascii	"APB2RSTR\000"
.LASF123:
	.ascii	"APB1RSTR1\000"
.LASF124:
	.ascii	"APB1RSTR2\000"
.LASF208:
	.ascii	"HAL_GetTickPrio\000"
.LASF218:
	.ascii	"../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal.c"
	.ascii	"\000"
.LASF99:
	.ascii	"unsigned int\000"
.LASF56:
	.ascii	"ADC3_IRQn\000"
.LASF202:
	.ascii	"HAL_SYSCFG_EnableVREFBUF\000"
.LASF174:
	.ascii	"HAL_SYSCFG_DisableVREFBUF\000"
.LASF215:
	.ascii	"HAL_DeInit\000"
.LASF27:
	.ascii	"ADC1_2_IRQn\000"
.LASF63:
	.ascii	"TIM6_DAC_IRQn\000"
.LASF112:
	.ascii	"PLLCFGR\000"
.LASF61:
	.ascii	"UART4_IRQn\000"
.LASF82:
	.ascii	"I2C3_ER_IRQn\000"
.LASF7:
	.ascii	"PendSV_IRQn\000"
.LASF92:
	.ascii	"short unsigned int\000"
.LASF176:
	.ascii	"HAL_SYSCFG_VREFBUF_TrimmingConfig\000"
.LASF213:
	.ascii	"HAL_MspDeInit\000"
.LASF189:
	.ascii	"HAL_DBGMCU_DisableDBGSleepMode\000"
.LASF95:
	.ascii	"__uint32_t\000"
.LASF3:
	.ascii	"BusFault_IRQn\000"
.LASF136:
	.ascii	"AHB2SMENR\000"
.LASF152:
	.ascii	"SWPR\000"
.LASF165:
	.ascii	"HAL_TickFreqTypeDef\000"
.LASF107:
	.ascii	"APB1FZR2\000"
.LASF150:
	.ascii	"SCSR\000"
.LASF77:
	.ascii	"DMA2_Channel6_IRQn\000"
.LASF162:
	.ascii	"HAL_TICK_FREQ_100HZ\000"
.LASF159:
	.ascii	"HAL_TIMEOUT\000"
.LASF127:
	.ascii	"AHB1ENR\000"
.LASF74:
	.ascii	"LPTIM1_IRQn\000"
.LASF187:
	.ascii	"HAL_DBGMCU_DisableDBGStopMode\000"
.LASF10:
	.ascii	"PVD_PVM_IRQn\000"
.LASF70:
	.ascii	"DFSDM1_FLT0_IRQn\000"
.LASF166:
	.ascii	"SystemCoreClock\000"
.LASF169:
	.ascii	"uwTickFreq\000"
.LASF167:
	.ascii	"uwTick\000"
.LASF81:
	.ascii	"I2C3_EV_IRQn\000"
.LASF96:
	.ascii	"long unsigned int\000"
.LASF83:
	.ascii	"SAI1_IRQn\000"
.LASF146:
	.ascii	"RCC_TypeDef\000"
.LASF163:
	.ascii	"HAL_TICK_FREQ_1KHZ\000"
.LASF156:
	.ascii	"HAL_OK\000"
.LASF24:
	.ascii	"DMA1_Channel5_IRQn\000"
.LASF103:
	.ascii	"CALIB\000"
.LASF178:
	.ascii	"TrimmingValue\000"
.LASF188:
	.ascii	"HAL_DBGMCU_EnableDBGStopMode\000"
.LASF28:
	.ascii	"CAN1_TX_IRQn\000"
.LASF137:
	.ascii	"AHB3SMENR\000"
.LASF121:
	.ascii	"AHB3RSTR\000"
.LASF49:
	.ascii	"EXTI15_10_IRQn\000"
.LASF214:
	.ascii	"HAL_MspInit\000"
.LASF206:
	.ascii	"status\000"
.LASF108:
	.ascii	"APB2FZ\000"
.LASF44:
	.ascii	"SPI1_IRQn\000"
.LASF104:
	.ascii	"SysTick_Type\000"
.LASF78:
	.ascii	"DMA2_Channel7_IRQn\000"
.LASF160:
	.ascii	"HAL_StatusTypeDef\000"
.LASF75:
	.ascii	"LPTIM2_IRQn\000"
.LASF91:
	.ascii	"short int\000"
.LASF193:
	.ascii	"HAL_GetUIDw0\000"
.LASF192:
	.ascii	"HAL_GetUIDw1\000"
.LASF191:
	.ascii	"HAL_GetUIDw2\000"
.LASF173:
	.ascii	"HAL_SYSCFG_EnableIOAnalogSwitchBooster\000"
.LASF23:
	.ascii	"DMA1_Channel4_IRQn\000"
.LASF8:
	.ascii	"SysTick_IRQn\000"
.LASF36:
	.ascii	"TIM1_CC_IRQn\000"
.LASF71:
	.ascii	"DFSDM1_FLT1_IRQn\000"
.LASF84:
	.ascii	"SAI2_IRQn\000"
.LASF216:
	.ascii	"HAL_Init\000"
.LASF21:
	.ascii	"DMA1_Channel2_IRQn\000"
.LASF52:
	.ascii	"TIM8_BRK_IRQn\000"
.LASF172:
	.ascii	"HAL_SYSCFG_DisableIOAnalogSwitchBooster\000"
.LASF102:
	.ascii	"LOAD\000"
.LASF209:
	.ascii	"HAL_GetTick\000"
.LASF5:
	.ascii	"SVCall_IRQn\000"
.LASF114:
	.ascii	"PLLSAI2CFGR\000"
.LASF66:
	.ascii	"DMA2_Channel2_IRQn\000"
.LASF154:
	.ascii	"VREFBUF_TypeDef\000"
.LASF129:
	.ascii	"AHB3ENR\000"
.LASF59:
	.ascii	"TIM5_IRQn\000"
.LASF204:
	.ascii	"Delay\000"
.LASF45:
	.ascii	"SPI2_IRQn\000"
.LASF62:
	.ascii	"UART5_IRQn\000"
.LASF76:
	.ascii	"OTG_FS_IRQn\000"
.LASF170:
	.ascii	"HAL_NVIC_SetPriority\000"
.LASF180:
	.ascii	"HAL_SYSCFG_VREFBUF_VoltageScalingConfig\000"
.LASF164:
	.ascii	"HAL_TICK_FREQ_DEFAULT\000"
.LASF131:
	.ascii	"APB1ENR1\000"
.LASF132:
	.ascii	"APB1ENR2\000"
.LASF72:
	.ascii	"DFSDM1_FLT2_IRQn\000"
.LASF20:
	.ascii	"DMA1_Channel1_IRQn\000"
.LASF2:
	.ascii	"MemoryManagement_IRQn\000"
.LASF183:
	.ascii	"HAL_SYSCFG_EnableMemorySwappingBank\000"
.LASF211:
	.ascii	"HAL_InitTick\000"
.LASF118:
	.ascii	"RESERVED0\000"
.LASF122:
	.ascii	"RESERVED1\000"
.LASF126:
	.ascii	"RESERVED2\000"
.LASF130:
	.ascii	"RESERVED3\000"
.LASF134:
	.ascii	"RESERVED4\000"
.LASF138:
	.ascii	"RESERVED5\000"
.LASF142:
	.ascii	"RESERVED6\000"
.LASF144:
	.ascii	"RESERVED7\000"
.LASF67:
	.ascii	"DMA2_Channel3_IRQn\000"
.LASF153:
	.ascii	"SYSCFG_TypeDef\000"
.LASF90:
	.ascii	"unsigned char\000"
.LASF54:
	.ascii	"TIM8_TRG_COM_IRQn\000"
.LASF19:
	.ascii	"EXTI4_IRQn\000"
.LASF143:
	.ascii	"CCIPR\000"
.LASF87:
	.ascii	"RNG_IRQn\000"
.LASF205:
	.ascii	"Freq\000"
.LASF185:
	.ascii	"HAL_DBGMCU_DisableDBGStandbyMode\000"
.LASF175:
	.ascii	"tickstart\000"
.LASF79:
	.ascii	"LPUART1_IRQn\000"
.LASF22:
	.ascii	"DMA1_Channel3_IRQn\000"
.LASF57:
	.ascii	"FMC_IRQn\000"
.LASF17:
	.ascii	"EXTI2_IRQn\000"
.LASF133:
	.ascii	"APB2ENR\000"
.LASF198:
	.ascii	"HAL_SuspendTick\000"
.LASF190:
	.ascii	"HAL_DBGMCU_EnableDBGSleepMode\000"
.LASF26:
	.ascii	"DMA1_Channel7_IRQn\000"
.LASF13:
	.ascii	"FLASH_IRQn\000"
.LASF34:
	.ascii	"TIM1_UP_TIM16_IRQn\000"
.LASF109:
	.ascii	"DBGMCU_TypeDef\000"
.LASF94:
	.ascii	"IRQn_Type\000"
.LASF195:
	.ascii	"HAL_GetREVID\000"
.LASF47:
	.ascii	"USART2_IRQn\000"
.LASF4:
	.ascii	"UsageFault_IRQn\000"
.LASF157:
	.ascii	"HAL_ERROR\000"
.LASF182:
	.ascii	"HAL_SYSCFG_DisableMemorySwappingBank\000"
.LASF155:
	.ascii	"long double\000"
.LASF168:
	.ascii	"uwTickPrio\000"
.LASF68:
	.ascii	"DMA2_Channel4_IRQn\000"
.LASF80:
	.ascii	"QUADSPI_IRQn\000"
.LASF199:
	.ascii	"HAL_Delay\000"
.LASF179:
	.ascii	"Mode\000"
.LASF120:
	.ascii	"AHB2RSTR\000"
.LASF217:
	.ascii	"GNU C17 12.3.1 20230626 -mcpu=cortex-m3 -mthumb -mf"
	.ascii	"loat-abi=soft -march=armv7-m -g -gdwarf-2 -Og -fdat"
	.ascii	"a-sections -ffunction-sections\000"
.LASF64:
	.ascii	"TIM7_IRQn\000"
.LASF201:
	.ascii	"HAL_GetTickFreq\000"
.LASF0:
	.ascii	"NonMaskableInt_IRQn\000"
.LASF25:
	.ascii	"DMA1_Channel6_IRQn\000"
.LASF207:
	.ascii	"prevTickFreq\000"
.LASF128:
	.ascii	"AHB2ENR\000"
.LASF11:
	.ascii	"TAMP_STAMP_IRQn\000"
.LASF1:
	.ascii	"HardFault_IRQn\000"
.LASF6:
	.ascii	"DebugMonitor_IRQn\000"
.LASF101:
	.ascii	"CTRL\000"
.LASF119:
	.ascii	"AHB1RSTR\000"
.LASF210:
	.ascii	"HAL_IncTick\000"
.LASF171:
	.ascii	"HAL_NVIC_SetPriorityGrouping\000"
.LASF42:
	.ascii	"I2C2_EV_IRQn\000"
.LASF48:
	.ascii	"USART3_IRQn\000"
.LASF37:
	.ascii	"TIM2_IRQn\000"
.LASF53:
	.ascii	"TIM8_UP_IRQn\000"
.LASF15:
	.ascii	"EXTI0_IRQn\000"
.LASF46:
	.ascii	"USART1_IRQn\000"
.LASF113:
	.ascii	"PLLSAI1CFGR\000"
.LASF145:
	.ascii	"BDCR\000"
.LASF18:
	.ascii	"EXTI3_IRQn\000"
.LASF106:
	.ascii	"APB1FZR1\000"
.LASF148:
	.ascii	"CFGR1\000"
.LASF151:
	.ascii	"CFGR2\000"
.LASF184:
	.ascii	"HAL_SYSCFG_SRAM2Erase\000"
.LASF14:
	.ascii	"RCC_IRQn\000"
.LASF33:
	.ascii	"TIM1_BRK_TIM15_IRQn\000"
.LASF197:
	.ascii	"HAL_ResumeTick\000"
.LASF110:
	.ascii	"ICSCR\000"
.LASF85:
	.ascii	"SWPMI1_IRQn\000"
.LASF139:
	.ascii	"APB1SMENR1\000"
.LASF16:
	.ascii	"EXTI1_IRQn\000"
.LASF194:
	.ascii	"HAL_GetDEVID\000"
.LASF219:
	.ascii	"/home/emanuele/Desktop/Code/MCU-fortifier/apps/doub"
	.ascii	"le_trusted_application/Debug\000"
.LASF88:
	.ascii	"FPU_IRQn\000"
.LASF111:
	.ascii	"CFGR\000"
.LASF41:
	.ascii	"I2C1_ER_IRQn\000"
.LASF60:
	.ascii	"SPI3_IRQn\000"
.LASF31:
	.ascii	"CAN1_SCE_IRQn\000"
.LASF100:
	.ascii	"uint32_t\000"
.LASF38:
	.ascii	"TIM3_IRQn\000"
.LASF149:
	.ascii	"EXTICR\000"
.LASF181:
	.ascii	"VoltageScaling\000"
.LASF140:
	.ascii	"APB1SMENR2\000"
	.ident	"GCC: (GNU Tools for STM32 12.3.rel1.20240612-1315) 12.3.1 20230626"
