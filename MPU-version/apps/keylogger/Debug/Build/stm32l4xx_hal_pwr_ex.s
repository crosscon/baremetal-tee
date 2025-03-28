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
	.file	"stm32l4xx_hal_pwr_ex.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 1 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c"
	.section	.text.HAL_PWREx_GetVoltageRange,"ax",%progbits
	.align	1
	.global	HAL_PWREx_GetVoltageRange
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_GetVoltageRange, %function
HAL_PWREx_GetVoltageRange:
.LFB74:
	.loc 1 115 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 131 3 view .LVU1
	.loc 1 131 15 is_stmt 0 view .LVU2
	ldr	r3, .L2
	ldr	r0, [r3]
	.loc 1 133 1 view .LVU3
	and	r0, r0, #1536
	bx	lr
.L3:
	.align	2
.L2:
	.word	1073770496
	.cfi_endproc
.LFE74:
	.size	HAL_PWREx_GetVoltageRange, .-HAL_PWREx_GetVoltageRange
	.section	.text.HAL_PWREx_ControlVoltageScaling,"ax",%progbits
	.align	1
	.global	HAL_PWREx_ControlVoltageScaling
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_ControlVoltageScaling, %function
HAL_PWREx_ControlVoltageScaling:
.LVL0:
.LFB75:
	.loc 1 164 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 165 3 view .LVU5
	.loc 1 167 3 view .LVU6
	.loc 1 239 3 view .LVU7
	.loc 1 239 6 is_stmt 0 view .LVU8
	cmp	r0, #512
	beq	.L13
	.loc 1 260 5 is_stmt 1 view .LVU9
	.loc 1 260 9 is_stmt 0 view .LVU10
	ldr	r3, .L14
	ldr	r3, [r3]
	and	r3, r3, #1536
	.loc 1 260 8 view .LVU11
	cmp	r3, #1024
	beq	.L12
	.loc 1 263 7 is_stmt 1 view .LVU12
	ldr	r2, .L14
	ldr	r3, [r2]
	bic	r3, r3, #1536
	orr	r3, r3, #1024
	str	r3, [r2]
	.loc 1 269 10 is_stmt 0 view .LVU13
	movs	r0, #0
.LVL1:
	.loc 1 269 10 view .LVU14
	bx	lr
.LVL2:
.L13:
	.loc 1 241 5 is_stmt 1 view .LVU15
	.loc 1 241 9 is_stmt 0 view .LVU16
	ldr	r3, .L14
	ldr	r3, [r3]
	and	r3, r3, #1536
	.loc 1 241 8 view .LVU17
	cmp	r3, #512
	beq	.L10
	.loc 1 244 7 is_stmt 1 view .LVU18
	ldr	r2, .L14
	ldr	r3, [r2]
	bic	r3, r3, #1536
	orr	r3, r3, #512
	str	r3, [r2]
	.loc 1 247 7 view .LVU19
	.loc 1 247 53 is_stmt 0 view .LVU20
	ldr	r3, .L14+4
	ldr	r3, [r3]
	movs	r2, #50
	mul	r3, r2, r3
	.loc 1 247 72 view .LVU21
	ldr	r2, .L14+8
	umull	r2, r3, r2, r3
	lsrs	r3, r3, #18
	.loc 1 247 23 view .LVU22
	adds	r3, r3, #1
.LVL3:
	.loc 1 248 7 is_stmt 1 view .LVU23
	.loc 1 248 13 is_stmt 0 view .LVU24
	b	.L7
.L9:
	.loc 1 250 9 is_stmt 1 view .LVU25
	.loc 1 250 24 is_stmt 0 view .LVU26
	subs	r3, r3, #1
.LVL4:
.L7:
	.loc 1 248 55 is_stmt 1 view .LVU27
	.loc 1 248 15 is_stmt 0 view .LVU28
	ldr	r2, .L14
	ldr	r2, [r2, #20]
	.loc 1 248 55 view .LVU29
	tst	r2, #1024
	beq	.L8
	.loc 1 248 55 discriminator 1 view .LVU30
	cmp	r3, #0
	bne	.L9
.L8:
	.loc 1 252 7 is_stmt 1 view .LVU31
	.loc 1 252 11 is_stmt 0 view .LVU32
	ldr	r3, .L14
.LVL5:
	.loc 1 252 11 view .LVU33
	ldr	r3, [r3, #20]
	.loc 1 252 10 view .LVU34
	tst	r3, #1024
	bne	.L11
	.loc 1 269 10 view .LVU35
	movs	r0, #0
.LVL6:
	.loc 1 269 10 view .LVU36
	bx	lr
.LVL7:
.L10:
	.loc 1 269 10 view .LVU37
	movs	r0, #0
.LVL8:
	.loc 1 269 10 view .LVU38
	bx	lr
.LVL9:
.L11:
	.loc 1 254 16 view .LVU39
	movs	r0, #3
.LVL10:
	.loc 1 254 16 view .LVU40
	bx	lr
.LVL11:
.L12:
	.loc 1 269 10 view .LVU41
	movs	r0, #0
.LVL12:
	.loc 1 270 1 view .LVU42
	bx	lr
.L15:
	.align	2
.L14:
	.word	1073770496
	.word	SystemCoreClock
	.word	1125899907
	.cfi_endproc
.LFE75:
	.size	HAL_PWREx_ControlVoltageScaling, .-HAL_PWREx_ControlVoltageScaling
	.section	.text.HAL_PWREx_EnableBatteryCharging,"ax",%progbits
	.align	1
	.global	HAL_PWREx_EnableBatteryCharging
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_EnableBatteryCharging, %function
HAL_PWREx_EnableBatteryCharging:
.LVL13:
.LFB76:
	.loc 1 283 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 284 3 view .LVU44
	.loc 1 287 3 view .LVU45
	ldr	r2, .L17
	ldr	r3, [r2, #12]
	bic	r3, r3, #512
	orrs	r3, r3, r0
	str	r3, [r2, #12]
	.loc 1 290 3 view .LVU46
	ldr	r3, [r2, #12]
	orr	r3, r3, #256
	str	r3, [r2, #12]
	.loc 1 291 1 is_stmt 0 view .LVU47
	bx	lr
.L18:
	.align	2
.L17:
	.word	1073770496
	.cfi_endproc
.LFE76:
	.size	HAL_PWREx_EnableBatteryCharging, .-HAL_PWREx_EnableBatteryCharging
	.section	.text.HAL_PWREx_DisableBatteryCharging,"ax",%progbits
	.align	1
	.global	HAL_PWREx_DisableBatteryCharging
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_DisableBatteryCharging, %function
HAL_PWREx_DisableBatteryCharging:
.LFB77:
	.loc 1 299 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 300 3 view .LVU49
	ldr	r2, .L20
	ldr	r3, [r2, #12]
	bic	r3, r3, #256
	str	r3, [r2, #12]
	.loc 1 301 1 is_stmt 0 view .LVU50
	bx	lr
.L21:
	.align	2
.L20:
	.word	1073770496
	.cfi_endproc
.LFE77:
	.size	HAL_PWREx_DisableBatteryCharging, .-HAL_PWREx_DisableBatteryCharging
	.section	.text.HAL_PWREx_EnableVddUSB,"ax",%progbits
	.align	1
	.global	HAL_PWREx_EnableVddUSB
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_EnableVddUSB, %function
HAL_PWREx_EnableVddUSB:
.LFB78:
	.loc 1 311 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 312 3 view .LVU52
	ldr	r2, .L23
	ldr	r3, [r2, #4]
	orr	r3, r3, #1024
	str	r3, [r2, #4]
	.loc 1 313 1 is_stmt 0 view .LVU53
	bx	lr
.L24:
	.align	2
.L23:
	.word	1073770496
	.cfi_endproc
.LFE78:
	.size	HAL_PWREx_EnableVddUSB, .-HAL_PWREx_EnableVddUSB
	.section	.text.HAL_PWREx_DisableVddUSB,"ax",%progbits
	.align	1
	.global	HAL_PWREx_DisableVddUSB
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_DisableVddUSB, %function
HAL_PWREx_DisableVddUSB:
.LFB79:
	.loc 1 321 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 322 3 view .LVU55
	ldr	r2, .L26
	ldr	r3, [r2, #4]
	bic	r3, r3, #1024
	str	r3, [r2, #4]
	.loc 1 323 1 is_stmt 0 view .LVU56
	bx	lr
.L27:
	.align	2
.L26:
	.word	1073770496
	.cfi_endproc
.LFE79:
	.size	HAL_PWREx_DisableVddUSB, .-HAL_PWREx_DisableVddUSB
	.section	.text.HAL_PWREx_EnableVddIO2,"ax",%progbits
	.align	1
	.global	HAL_PWREx_EnableVddIO2
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_EnableVddIO2, %function
HAL_PWREx_EnableVddIO2:
.LFB80:
	.loc 1 333 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 334 3 view .LVU58
	ldr	r2, .L29
	ldr	r3, [r2, #4]
	orr	r3, r3, #512
	str	r3, [r2, #4]
	.loc 1 335 1 is_stmt 0 view .LVU59
	bx	lr
.L30:
	.align	2
.L29:
	.word	1073770496
	.cfi_endproc
.LFE80:
	.size	HAL_PWREx_EnableVddIO2, .-HAL_PWREx_EnableVddIO2
	.section	.text.HAL_PWREx_DisableVddIO2,"ax",%progbits
	.align	1
	.global	HAL_PWREx_DisableVddIO2
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_DisableVddIO2, %function
HAL_PWREx_DisableVddIO2:
.LFB81:
	.loc 1 343 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 344 3 view .LVU61
	ldr	r2, .L32
	ldr	r3, [r2, #4]
	bic	r3, r3, #512
	str	r3, [r2, #4]
	.loc 1 345 1 is_stmt 0 view .LVU62
	bx	lr
.L33:
	.align	2
.L32:
	.word	1073770496
	.cfi_endproc
.LFE81:
	.size	HAL_PWREx_DisableVddIO2, .-HAL_PWREx_DisableVddIO2
	.section	.text.HAL_PWREx_EnableInternalWakeUpLine,"ax",%progbits
	.align	1
	.global	HAL_PWREx_EnableInternalWakeUpLine
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_EnableInternalWakeUpLine, %function
HAL_PWREx_EnableInternalWakeUpLine:
.LFB82:
	.loc 1 354 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 355 3 view .LVU64
	ldr	r2, .L35
	ldr	r3, [r2, #8]
	orr	r3, r3, #32768
	str	r3, [r2, #8]
	.loc 1 356 1 is_stmt 0 view .LVU65
	bx	lr
.L36:
	.align	2
.L35:
	.word	1073770496
	.cfi_endproc
.LFE82:
	.size	HAL_PWREx_EnableInternalWakeUpLine, .-HAL_PWREx_EnableInternalWakeUpLine
	.section	.text.HAL_PWREx_DisableInternalWakeUpLine,"ax",%progbits
	.align	1
	.global	HAL_PWREx_DisableInternalWakeUpLine
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_DisableInternalWakeUpLine, %function
HAL_PWREx_DisableInternalWakeUpLine:
.LFB83:
	.loc 1 364 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 365 3 view .LVU67
	ldr	r2, .L38
	ldr	r3, [r2, #8]
	bic	r3, r3, #32768
	str	r3, [r2, #8]
	.loc 1 366 1 is_stmt 0 view .LVU68
	bx	lr
.L39:
	.align	2
.L38:
	.word	1073770496
	.cfi_endproc
.LFE83:
	.size	HAL_PWREx_DisableInternalWakeUpLine, .-HAL_PWREx_DisableInternalWakeUpLine
	.section	.text.HAL_PWREx_EnableGPIOPullUp,"ax",%progbits
	.align	1
	.global	HAL_PWREx_EnableGPIOPullUp
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_EnableGPIOPullUp, %function
HAL_PWREx_EnableGPIOPullUp:
.LVL14:
.LFB84:
	.loc 1 392 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 393 3 view .LVU70
	.loc 1 395 3 view .LVU71
	.loc 1 396 3 view .LVU72
	.loc 1 398 3 view .LVU73
	cmp	r0, #7
	bhi	.L51
	tbb	[pc, r0]
.L43:
	.byte	(.L50-.L43)/2
	.byte	(.L49-.L43)/2
	.byte	(.L48-.L43)/2
	.byte	(.L47-.L43)/2
	.byte	(.L46-.L43)/2
	.byte	(.L45-.L43)/2
	.byte	(.L44-.L43)/2
	.byte	(.L42-.L43)/2
	.p2align 1
.L50:
	.loc 1 401 8 view .LVU74
	ldr	r3, .L52
	ldr	r2, [r3, #32]
	bic	r0, r1, #16384
.LVL15:
	.loc 1 401 8 is_stmt 0 view .LVU75
	orrs	r2, r2, r0
	str	r2, [r3, #32]
	.loc 1 402 8 is_stmt 1 view .LVU76
	ldr	r2, [r3, #36]
	bic	r1, r1, #40960
.LVL16:
	.loc 1 402 8 is_stmt 0 view .LVU77
	bic	r2, r2, r1
	str	r2, [r3, #36]
	.loc 1 403 8 is_stmt 1 view .LVU78
	.loc 1 393 21 is_stmt 0 view .LVU79
	movs	r0, #0
	.loc 1 403 8 view .LVU80
	bx	lr
.LVL17:
.L49:
	.loc 1 405 8 is_stmt 1 view .LVU81
	ldr	r3, .L52
	ldr	r2, [r3, #40]
	orrs	r2, r2, r1
	str	r2, [r3, #40]
	.loc 1 406 8 view .LVU82
	ldr	r2, [r3, #44]
	bic	r1, r1, #16
.LVL18:
	.loc 1 406 8 is_stmt 0 view .LVU83
	bic	r2, r2, r1
	str	r2, [r3, #44]
	.loc 1 407 8 is_stmt 1 view .LVU84
	.loc 1 393 21 is_stmt 0 view .LVU85
	movs	r0, #0
.LVL19:
	.loc 1 407 8 view .LVU86
	bx	lr
.LVL20:
.L48:
	.loc 1 409 8 is_stmt 1 view .LVU87
	ldr	r3, .L52
	ldr	r2, [r3, #48]
	orrs	r2, r2, r1
	str	r2, [r3, #48]
	.loc 1 410 8 view .LVU88
	ldr	r2, [r3, #52]
	bic	r2, r2, r1
	str	r2, [r3, #52]
	.loc 1 411 8 view .LVU89
	.loc 1 393 21 is_stmt 0 view .LVU90
	movs	r0, #0
.LVL21:
	.loc 1 411 8 view .LVU91
	bx	lr
.LVL22:
.L47:
	.loc 1 414 8 is_stmt 1 view .LVU92
	ldr	r3, .L52
	ldr	r2, [r3, #56]
	orrs	r2, r2, r1
	str	r2, [r3, #56]
	.loc 1 415 8 view .LVU93
	ldr	r2, [r3, #60]
	bic	r2, r2, r1
	str	r2, [r3, #60]
	.loc 1 416 8 view .LVU94
	.loc 1 393 21 is_stmt 0 view .LVU95
	movs	r0, #0
.LVL23:
	.loc 1 416 8 view .LVU96
	bx	lr
.LVL24:
.L46:
	.loc 1 420 8 is_stmt 1 view .LVU97
	ldr	r3, .L52
	ldr	r2, [r3, #64]
	orrs	r2, r2, r1
	str	r2, [r3, #64]
	.loc 1 421 8 view .LVU98
	ldr	r2, [r3, #68]
	bic	r2, r2, r1
	str	r2, [r3, #68]
	.loc 1 422 8 view .LVU99
	.loc 1 393 21 is_stmt 0 view .LVU100
	movs	r0, #0
.LVL25:
	.loc 1 422 8 view .LVU101
	bx	lr
.LVL26:
.L45:
	.loc 1 426 8 is_stmt 1 view .LVU102
	ldr	r3, .L52
	ldr	r2, [r3, #72]
	orrs	r2, r2, r1
	str	r2, [r3, #72]
	.loc 1 427 8 view .LVU103
	ldr	r2, [r3, #76]
	bic	r2, r2, r1
	str	r2, [r3, #76]
	.loc 1 428 8 view .LVU104
	.loc 1 393 21 is_stmt 0 view .LVU105
	movs	r0, #0
.LVL27:
	.loc 1 428 8 view .LVU106
	bx	lr
.LVL28:
.L44:
	.loc 1 432 8 is_stmt 1 view .LVU107
	ldr	r3, .L52
	ldr	r2, [r3, #80]
	orrs	r2, r2, r1
	str	r2, [r3, #80]
	.loc 1 433 8 view .LVU108
	ldr	r2, [r3, #84]
	bic	r2, r2, r1
	str	r2, [r3, #84]
	.loc 1 434 8 view .LVU109
	.loc 1 393 21 is_stmt 0 view .LVU110
	movs	r0, #0
.LVL29:
	.loc 1 434 8 view .LVU111
	bx	lr
.LVL30:
.L42:
	.loc 1 437 8 is_stmt 1 view .LVU112
	ldr	r3, .L52
	ldr	r2, [r3, #88]
	and	r1, r1, #3
.LVL31:
	.loc 1 437 8 is_stmt 0 view .LVU113
	orrs	r2, r2, r1
	str	r2, [r3, #88]
	.loc 1 441 8 is_stmt 1 view .LVU114
	ldr	r2, [r3, #92]
	bic	r2, r2, r1
	str	r2, [r3, #92]
	.loc 1 443 8 view .LVU115
	.loc 1 393 21 is_stmt 0 view .LVU116
	movs	r0, #0
.LVL32:
	.loc 1 443 8 view .LVU117
	bx	lr
.LVL33:
.L51:
	.loc 1 398 3 view .LVU118
	movs	r0, #1
.LVL34:
	.loc 1 455 3 is_stmt 1 view .LVU119
	.loc 1 456 1 is_stmt 0 view .LVU120
	bx	lr
.L53:
	.align	2
.L52:
	.word	1073770496
	.cfi_endproc
.LFE84:
	.size	HAL_PWREx_EnableGPIOPullUp, .-HAL_PWREx_EnableGPIOPullUp
	.section	.text.HAL_PWREx_DisableGPIOPullUp,"ax",%progbits
	.align	1
	.global	HAL_PWREx_DisableGPIOPullUp
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_DisableGPIOPullUp, %function
HAL_PWREx_DisableGPIOPullUp:
.LVL35:
.LFB85:
	.loc 1 475 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 476 3 view .LVU122
	.loc 1 478 3 view .LVU123
	.loc 1 479 3 view .LVU124
	.loc 1 481 3 view .LVU125
	cmp	r0, #7
	bhi	.L65
	tbb	[pc, r0]
.L57:
	.byte	(.L64-.L57)/2
	.byte	(.L63-.L57)/2
	.byte	(.L62-.L57)/2
	.byte	(.L61-.L57)/2
	.byte	(.L60-.L57)/2
	.byte	(.L59-.L57)/2
	.byte	(.L58-.L57)/2
	.byte	(.L56-.L57)/2
	.p2align 1
.L64:
	.loc 1 484 8 view .LVU126
	ldr	r2, .L66
	ldr	r3, [r2, #32]
	bic	r1, r1, #16384
.LVL36:
	.loc 1 484 8 is_stmt 0 view .LVU127
	bic	r1, r3, r1
	str	r1, [r2, #32]
	.loc 1 485 8 is_stmt 1 view .LVU128
	.loc 1 476 21 is_stmt 0 view .LVU129
	movs	r0, #0
.LVL37:
	.loc 1 485 8 view .LVU130
	bx	lr
.LVL38:
.L63:
	.loc 1 487 8 is_stmt 1 view .LVU131
	ldr	r2, .L66
	ldr	r3, [r2, #40]
	bic	r3, r3, r1
	str	r3, [r2, #40]
	.loc 1 488 8 view .LVU132
	.loc 1 476 21 is_stmt 0 view .LVU133
	movs	r0, #0
.LVL39:
	.loc 1 488 8 view .LVU134
	bx	lr
.LVL40:
.L62:
	.loc 1 490 8 is_stmt 1 view .LVU135
	ldr	r2, .L66
	ldr	r3, [r2, #48]
	bic	r3, r3, r1
	str	r3, [r2, #48]
	.loc 1 491 8 view .LVU136
	.loc 1 476 21 is_stmt 0 view .LVU137
	movs	r0, #0
.LVL41:
	.loc 1 491 8 view .LVU138
	bx	lr
.LVL42:
.L61:
	.loc 1 494 8 is_stmt 1 view .LVU139
	ldr	r2, .L66
	ldr	r3, [r2, #56]
	bic	r3, r3, r1
	str	r3, [r2, #56]
	.loc 1 495 8 view .LVU140
	.loc 1 476 21 is_stmt 0 view .LVU141
	movs	r0, #0
.LVL43:
	.loc 1 495 8 view .LVU142
	bx	lr
.LVL44:
.L60:
	.loc 1 499 8 is_stmt 1 view .LVU143
	ldr	r2, .L66
	ldr	r3, [r2, #64]
	bic	r3, r3, r1
	str	r3, [r2, #64]
	.loc 1 500 8 view .LVU144
	.loc 1 476 21 is_stmt 0 view .LVU145
	movs	r0, #0
.LVL45:
	.loc 1 500 8 view .LVU146
	bx	lr
.LVL46:
.L59:
	.loc 1 504 8 is_stmt 1 view .LVU147
	ldr	r2, .L66
	ldr	r3, [r2, #72]
	bic	r3, r3, r1
	str	r3, [r2, #72]
	.loc 1 505 8 view .LVU148
	.loc 1 476 21 is_stmt 0 view .LVU149
	movs	r0, #0
.LVL47:
	.loc 1 505 8 view .LVU150
	bx	lr
.LVL48:
.L58:
	.loc 1 509 8 is_stmt 1 view .LVU151
	ldr	r2, .L66
	ldr	r3, [r2, #80]
	bic	r3, r3, r1
	str	r3, [r2, #80]
	.loc 1 510 8 view .LVU152
	.loc 1 476 21 is_stmt 0 view .LVU153
	movs	r0, #0
.LVL49:
	.loc 1 510 8 view .LVU154
	bx	lr
.LVL50:
.L56:
	.loc 1 513 8 is_stmt 1 view .LVU155
	ldr	r2, .L66
	ldr	r3, [r2, #88]
	and	r1, r1, #3
.LVL51:
	.loc 1 513 8 is_stmt 0 view .LVU156
	bic	r3, r3, r1
	str	r3, [r2, #88]
	.loc 1 514 8 is_stmt 1 view .LVU157
	.loc 1 476 21 is_stmt 0 view .LVU158
	movs	r0, #0
.LVL52:
	.loc 1 514 8 view .LVU159
	bx	lr
.LVL53:
.L65:
	.loc 1 481 3 view .LVU160
	movs	r0, #1
.LVL54:
	.loc 1 525 3 is_stmt 1 view .LVU161
	.loc 1 526 1 is_stmt 0 view .LVU162
	bx	lr
.L67:
	.align	2
.L66:
	.word	1073770496
	.cfi_endproc
.LFE85:
	.size	HAL_PWREx_DisableGPIOPullUp, .-HAL_PWREx_DisableGPIOPullUp
	.section	.text.HAL_PWREx_EnableGPIOPullDown,"ax",%progbits
	.align	1
	.global	HAL_PWREx_EnableGPIOPullDown
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_EnableGPIOPullDown, %function
HAL_PWREx_EnableGPIOPullDown:
.LVL55:
.LFB86:
	.loc 1 552 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 553 3 view .LVU164
	.loc 1 555 3 view .LVU165
	.loc 1 556 3 view .LVU166
	.loc 1 558 3 view .LVU167
	cmp	r0, #7
	bhi	.L79
	tbb	[pc, r0]
.L71:
	.byte	(.L78-.L71)/2
	.byte	(.L77-.L71)/2
	.byte	(.L76-.L71)/2
	.byte	(.L75-.L71)/2
	.byte	(.L74-.L71)/2
	.byte	(.L73-.L71)/2
	.byte	(.L72-.L71)/2
	.byte	(.L70-.L71)/2
	.p2align 1
.L78:
	.loc 1 561 8 view .LVU168
	ldr	r3, .L80
	ldr	r2, [r3, #36]
	bic	r0, r1, #40960
.LVL56:
	.loc 1 561 8 is_stmt 0 view .LVU169
	orrs	r2, r2, r0
	str	r2, [r3, #36]
	.loc 1 562 8 is_stmt 1 view .LVU170
	ldr	r2, [r3, #32]
	bic	r1, r1, #16384
.LVL57:
	.loc 1 562 8 is_stmt 0 view .LVU171
	bic	r2, r2, r1
	str	r2, [r3, #32]
	.loc 1 563 8 is_stmt 1 view .LVU172
	.loc 1 553 21 is_stmt 0 view .LVU173
	movs	r0, #0
	.loc 1 563 8 view .LVU174
	bx	lr
.LVL58:
.L77:
	.loc 1 565 8 is_stmt 1 view .LVU175
	ldr	r3, .L80
	ldr	r2, [r3, #44]
	bic	r0, r1, #16
.LVL59:
	.loc 1 565 8 is_stmt 0 view .LVU176
	orrs	r2, r2, r0
	str	r2, [r3, #44]
	.loc 1 566 8 is_stmt 1 view .LVU177
	ldr	r2, [r3, #40]
	bic	r2, r2, r1
	str	r2, [r3, #40]
	.loc 1 567 8 view .LVU178
	.loc 1 553 21 is_stmt 0 view .LVU179
	movs	r0, #0
	.loc 1 567 8 view .LVU180
	bx	lr
.LVL60:
.L76:
	.loc 1 569 8 is_stmt 1 view .LVU181
	ldr	r3, .L80
	ldr	r2, [r3, #52]
	orrs	r2, r2, r1
	str	r2, [r3, #52]
	.loc 1 570 8 view .LVU182
	ldr	r2, [r3, #48]
	bic	r2, r2, r1
	str	r2, [r3, #48]
	.loc 1 571 8 view .LVU183
	.loc 1 553 21 is_stmt 0 view .LVU184
	movs	r0, #0
.LVL61:
	.loc 1 571 8 view .LVU185
	bx	lr
.LVL62:
.L75:
	.loc 1 574 8 is_stmt 1 view .LVU186
	ldr	r3, .L80
	ldr	r2, [r3, #60]
	orrs	r2, r2, r1
	str	r2, [r3, #60]
	.loc 1 575 8 view .LVU187
	ldr	r2, [r3, #56]
	bic	r2, r2, r1
	str	r2, [r3, #56]
	.loc 1 576 8 view .LVU188
	.loc 1 553 21 is_stmt 0 view .LVU189
	movs	r0, #0
.LVL63:
	.loc 1 576 8 view .LVU190
	bx	lr
.LVL64:
.L74:
	.loc 1 580 8 is_stmt 1 view .LVU191
	ldr	r3, .L80
	ldr	r2, [r3, #68]
	orrs	r2, r2, r1
	str	r2, [r3, #68]
	.loc 1 581 8 view .LVU192
	ldr	r2, [r3, #64]
	bic	r2, r2, r1
	str	r2, [r3, #64]
	.loc 1 582 8 view .LVU193
	.loc 1 553 21 is_stmt 0 view .LVU194
	movs	r0, #0
.LVL65:
	.loc 1 582 8 view .LVU195
	bx	lr
.LVL66:
.L73:
	.loc 1 586 8 is_stmt 1 view .LVU196
	ldr	r3, .L80
	ldr	r2, [r3, #76]
	orrs	r2, r2, r1
	str	r2, [r3, #76]
	.loc 1 587 8 view .LVU197
	ldr	r2, [r3, #72]
	bic	r2, r2, r1
	str	r2, [r3, #72]
	.loc 1 588 8 view .LVU198
	.loc 1 553 21 is_stmt 0 view .LVU199
	movs	r0, #0
.LVL67:
	.loc 1 588 8 view .LVU200
	bx	lr
.LVL68:
.L72:
	.loc 1 592 8 is_stmt 1 view .LVU201
	ldr	r3, .L80
	ldr	r2, [r3, #84]
	orrs	r2, r2, r1
	str	r2, [r3, #84]
	.loc 1 593 8 view .LVU202
	ldr	r2, [r3, #80]
	bic	r2, r2, r1
	str	r2, [r3, #80]
	.loc 1 594 8 view .LVU203
	.loc 1 553 21 is_stmt 0 view .LVU204
	movs	r0, #0
.LVL69:
	.loc 1 594 8 view .LVU205
	bx	lr
.LVL70:
.L70:
	.loc 1 600 8 is_stmt 1 view .LVU206
	ldr	r3, .L80
	ldr	r2, [r3, #92]
	and	r1, r1, #3
.LVL71:
	.loc 1 600 8 is_stmt 0 view .LVU207
	orrs	r2, r2, r1
	str	r2, [r3, #92]
	.loc 1 602 8 is_stmt 1 view .LVU208
	ldr	r2, [r3, #88]
	bic	r2, r2, r1
	str	r2, [r3, #88]
	.loc 1 603 8 view .LVU209
	.loc 1 553 21 is_stmt 0 view .LVU210
	movs	r0, #0
.LVL72:
	.loc 1 603 8 view .LVU211
	bx	lr
.LVL73:
.L79:
	.loc 1 558 3 view .LVU212
	movs	r0, #1
.LVL74:
	.loc 1 615 3 is_stmt 1 view .LVU213
	.loc 1 616 1 is_stmt 0 view .LVU214
	bx	lr
.L81:
	.align	2
.L80:
	.word	1073770496
	.cfi_endproc
.LFE86:
	.size	HAL_PWREx_EnableGPIOPullDown, .-HAL_PWREx_EnableGPIOPullDown
	.section	.text.HAL_PWREx_DisableGPIOPullDown,"ax",%progbits
	.align	1
	.global	HAL_PWREx_DisableGPIOPullDown
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_DisableGPIOPullDown, %function
HAL_PWREx_DisableGPIOPullDown:
.LVL75:
.LFB87:
	.loc 1 635 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 636 3 view .LVU216
	.loc 1 638 3 view .LVU217
	.loc 1 639 3 view .LVU218
	.loc 1 641 3 view .LVU219
	cmp	r0, #7
	bhi	.L93
	tbb	[pc, r0]
.L85:
	.byte	(.L92-.L85)/2
	.byte	(.L91-.L85)/2
	.byte	(.L90-.L85)/2
	.byte	(.L89-.L85)/2
	.byte	(.L88-.L85)/2
	.byte	(.L87-.L85)/2
	.byte	(.L86-.L85)/2
	.byte	(.L84-.L85)/2
	.p2align 1
.L92:
	.loc 1 644 8 view .LVU220
	ldr	r2, .L94
	ldr	r3, [r2, #36]
	bic	r1, r1, #40960
.LVL76:
	.loc 1 644 8 is_stmt 0 view .LVU221
	bic	r1, r3, r1
	str	r1, [r2, #36]
	.loc 1 645 8 is_stmt 1 view .LVU222
	.loc 1 636 21 is_stmt 0 view .LVU223
	movs	r0, #0
.LVL77:
	.loc 1 645 8 view .LVU224
	bx	lr
.LVL78:
.L91:
	.loc 1 647 8 is_stmt 1 view .LVU225
	ldr	r2, .L94
	ldr	r3, [r2, #44]
	bic	r1, r1, #16
.LVL79:
	.loc 1 647 8 is_stmt 0 view .LVU226
	bic	r1, r3, r1
	str	r1, [r2, #44]
	.loc 1 648 8 is_stmt 1 view .LVU227
	.loc 1 636 21 is_stmt 0 view .LVU228
	movs	r0, #0
.LVL80:
	.loc 1 648 8 view .LVU229
	bx	lr
.LVL81:
.L90:
	.loc 1 650 8 is_stmt 1 view .LVU230
	ldr	r2, .L94
	ldr	r3, [r2, #52]
	bic	r3, r3, r1
	str	r3, [r2, #52]
	.loc 1 651 8 view .LVU231
	.loc 1 636 21 is_stmt 0 view .LVU232
	movs	r0, #0
.LVL82:
	.loc 1 651 8 view .LVU233
	bx	lr
.LVL83:
.L89:
	.loc 1 654 8 is_stmt 1 view .LVU234
	ldr	r2, .L94
	ldr	r3, [r2, #60]
	bic	r3, r3, r1
	str	r3, [r2, #60]
	.loc 1 655 8 view .LVU235
	.loc 1 636 21 is_stmt 0 view .LVU236
	movs	r0, #0
.LVL84:
	.loc 1 655 8 view .LVU237
	bx	lr
.LVL85:
.L88:
	.loc 1 659 8 is_stmt 1 view .LVU238
	ldr	r2, .L94
	ldr	r3, [r2, #68]
	bic	r3, r3, r1
	str	r3, [r2, #68]
	.loc 1 660 8 view .LVU239
	.loc 1 636 21 is_stmt 0 view .LVU240
	movs	r0, #0
.LVL86:
	.loc 1 660 8 view .LVU241
	bx	lr
.LVL87:
.L87:
	.loc 1 664 8 is_stmt 1 view .LVU242
	ldr	r2, .L94
	ldr	r3, [r2, #76]
	bic	r3, r3, r1
	str	r3, [r2, #76]
	.loc 1 665 8 view .LVU243
	.loc 1 636 21 is_stmt 0 view .LVU244
	movs	r0, #0
.LVL88:
	.loc 1 665 8 view .LVU245
	bx	lr
.LVL89:
.L86:
	.loc 1 669 8 is_stmt 1 view .LVU246
	ldr	r2, .L94
	ldr	r3, [r2, #84]
	bic	r3, r3, r1
	str	r3, [r2, #84]
	.loc 1 670 8 view .LVU247
	.loc 1 636 21 is_stmt 0 view .LVU248
	movs	r0, #0
.LVL90:
	.loc 1 670 8 view .LVU249
	bx	lr
.LVL91:
.L84:
	.loc 1 676 8 is_stmt 1 view .LVU250
	ldr	r2, .L94
	ldr	r3, [r2, #92]
	and	r1, r1, #3
.LVL92:
	.loc 1 676 8 is_stmt 0 view .LVU251
	bic	r3, r3, r1
	str	r3, [r2, #92]
	.loc 1 678 8 is_stmt 1 view .LVU252
	.loc 1 636 21 is_stmt 0 view .LVU253
	movs	r0, #0
.LVL93:
	.loc 1 678 8 view .LVU254
	bx	lr
.LVL94:
.L93:
	.loc 1 641 3 view .LVU255
	movs	r0, #1
.LVL95:
	.loc 1 689 3 is_stmt 1 view .LVU256
	.loc 1 690 1 is_stmt 0 view .LVU257
	bx	lr
.L95:
	.align	2
.L94:
	.word	1073770496
	.cfi_endproc
.LFE87:
	.size	HAL_PWREx_DisableGPIOPullDown, .-HAL_PWREx_DisableGPIOPullDown
	.section	.text.HAL_PWREx_EnablePullUpPullDownConfig,"ax",%progbits
	.align	1
	.global	HAL_PWREx_EnablePullUpPullDownConfig
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_EnablePullUpPullDownConfig, %function
HAL_PWREx_EnablePullUpPullDownConfig:
.LFB88:
	.loc 1 705 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 706 3 view .LVU259
	ldr	r2, .L97
	ldr	r3, [r2, #8]
	orr	r3, r3, #1024
	str	r3, [r2, #8]
	.loc 1 707 1 is_stmt 0 view .LVU260
	bx	lr
.L98:
	.align	2
.L97:
	.word	1073770496
	.cfi_endproc
.LFE88:
	.size	HAL_PWREx_EnablePullUpPullDownConfig, .-HAL_PWREx_EnablePullUpPullDownConfig
	.section	.text.HAL_PWREx_DisablePullUpPullDownConfig,"ax",%progbits
	.align	1
	.global	HAL_PWREx_DisablePullUpPullDownConfig
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_DisablePullUpPullDownConfig, %function
HAL_PWREx_DisablePullUpPullDownConfig:
.LFB89:
	.loc 1 717 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 718 3 view .LVU262
	ldr	r2, .L100
	ldr	r3, [r2, #8]
	bic	r3, r3, #1024
	str	r3, [r2, #8]
	.loc 1 719 1 is_stmt 0 view .LVU263
	bx	lr
.L101:
	.align	2
.L100:
	.word	1073770496
	.cfi_endproc
.LFE89:
	.size	HAL_PWREx_DisablePullUpPullDownConfig, .-HAL_PWREx_DisablePullUpPullDownConfig
	.section	.text.HAL_PWREx_SetSRAM2ContentRetention,"ax",%progbits
	.align	1
	.global	HAL_PWREx_SetSRAM2ContentRetention
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_SetSRAM2ContentRetention, %function
HAL_PWREx_SetSRAM2ContentRetention:
.LVL96:
.LFB92:
	.loc 1 752 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 753 3 view .LVU265
	.loc 1 755 3 view .LVU266
	.loc 1 755 6 is_stmt 0 view .LVU267
	cbnz	r0, .L103
	.loc 1 757 5 is_stmt 1 view .LVU268
	ldr	r2, .L106
	ldr	r3, [r2, #8]
	bic	r3, r3, #256
	str	r3, [r2, #8]
	bx	lr
.L103:
	.loc 1 759 8 view .LVU269
	.loc 1 759 11 is_stmt 0 view .LVU270
	cmp	r0, #256
	bne	.L105
	.loc 1 761 5 is_stmt 1 view .LVU271
	ldr	r2, .L106
	ldr	r3, [r2, #8]
	orr	r3, r3, #256
	str	r3, [r2, #8]
	.loc 1 773 10 is_stmt 0 view .LVU272
	movs	r0, #0
.LVL97:
	.loc 1 773 10 view .LVU273
	bx	lr
.LVL98:
.L105:
	.loc 1 770 12 view .LVU274
	movs	r0, #1
.LVL99:
	.loc 1 774 1 view .LVU275
	bx	lr
.L107:
	.align	2
.L106:
	.word	1073770496
	.cfi_endproc
.LFE92:
	.size	HAL_PWREx_SetSRAM2ContentRetention, .-HAL_PWREx_SetSRAM2ContentRetention
	.section	.text.HAL_PWREx_EnableSRAM2ContentRetention,"ax",%progbits
	.align	1
	.global	HAL_PWREx_EnableSRAM2ContentRetention
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_EnableSRAM2ContentRetention, %function
HAL_PWREx_EnableSRAM2ContentRetention:
.LFB90:
	.loc 1 728 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
.LCFI0:
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	.cfi_offset 14, -4
	.loc 1 729 3 view .LVU277
	.loc 1 729 10 is_stmt 0 view .LVU278
	mov	r0, #256
	bl	HAL_PWREx_SetSRAM2ContentRetention
.LVL100:
	.loc 1 730 1 view .LVU279
	pop	{r3, pc}
	.cfi_endproc
.LFE90:
	.size	HAL_PWREx_EnableSRAM2ContentRetention, .-HAL_PWREx_EnableSRAM2ContentRetention
	.section	.text.HAL_PWREx_DisableSRAM2ContentRetention,"ax",%progbits
	.align	1
	.global	HAL_PWREx_DisableSRAM2ContentRetention
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_DisableSRAM2ContentRetention, %function
HAL_PWREx_DisableSRAM2ContentRetention:
.LFB91:
	.loc 1 737 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
.LCFI1:
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	.cfi_offset 14, -4
	.loc 1 738 3 view .LVU281
	.loc 1 738 10 is_stmt 0 view .LVU282
	movs	r0, #0
	bl	HAL_PWREx_SetSRAM2ContentRetention
.LVL101:
	.loc 1 739 1 view .LVU283
	pop	{r3, pc}
	.cfi_endproc
.LFE91:
	.size	HAL_PWREx_DisableSRAM2ContentRetention, .-HAL_PWREx_DisableSRAM2ContentRetention
	.section	.text.HAL_PWREx_EnablePVM1,"ax",%progbits
	.align	1
	.global	HAL_PWREx_EnablePVM1
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_EnablePVM1, %function
HAL_PWREx_EnablePVM1:
.LFB93:
	.loc 1 879 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 880 3 view .LVU285
	ldr	r2, .L113
	ldr	r3, [r2, #4]
	orr	r3, r3, #16
	str	r3, [r2, #4]
	.loc 1 881 1 is_stmt 0 view .LVU286
	bx	lr
.L114:
	.align	2
.L113:
	.word	1073770496
	.cfi_endproc
.LFE93:
	.size	HAL_PWREx_EnablePVM1, .-HAL_PWREx_EnablePVM1
	.section	.text.HAL_PWREx_DisablePVM1,"ax",%progbits
	.align	1
	.global	HAL_PWREx_DisablePVM1
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_DisablePVM1, %function
HAL_PWREx_DisablePVM1:
.LFB94:
	.loc 1 888 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 889 3 view .LVU288
	ldr	r2, .L116
	ldr	r3, [r2, #4]
	bic	r3, r3, #16
	str	r3, [r2, #4]
	.loc 1 890 1 is_stmt 0 view .LVU289
	bx	lr
.L117:
	.align	2
.L116:
	.word	1073770496
	.cfi_endproc
.LFE94:
	.size	HAL_PWREx_DisablePVM1, .-HAL_PWREx_DisablePVM1
	.section	.text.HAL_PWREx_EnablePVM2,"ax",%progbits
	.align	1
	.global	HAL_PWREx_EnablePVM2
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_EnablePVM2, %function
HAL_PWREx_EnablePVM2:
.LFB95:
	.loc 1 900 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 901 3 view .LVU291
	ldr	r2, .L119
	ldr	r3, [r2, #4]
	orr	r3, r3, #32
	str	r3, [r2, #4]
	.loc 1 902 1 is_stmt 0 view .LVU292
	bx	lr
.L120:
	.align	2
.L119:
	.word	1073770496
	.cfi_endproc
.LFE95:
	.size	HAL_PWREx_EnablePVM2, .-HAL_PWREx_EnablePVM2
	.section	.text.HAL_PWREx_DisablePVM2,"ax",%progbits
	.align	1
	.global	HAL_PWREx_DisablePVM2
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_DisablePVM2, %function
HAL_PWREx_DisablePVM2:
.LFB96:
	.loc 1 909 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 910 3 view .LVU294
	ldr	r2, .L122
	ldr	r3, [r2, #4]
	bic	r3, r3, #32
	str	r3, [r2, #4]
	.loc 1 911 1 is_stmt 0 view .LVU295
	bx	lr
.L123:
	.align	2
.L122:
	.word	1073770496
	.cfi_endproc
.LFE96:
	.size	HAL_PWREx_DisablePVM2, .-HAL_PWREx_DisablePVM2
	.section	.text.HAL_PWREx_EnablePVM3,"ax",%progbits
	.align	1
	.global	HAL_PWREx_EnablePVM3
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_EnablePVM3, %function
HAL_PWREx_EnablePVM3:
.LFB97:
	.loc 1 920 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 921 3 view .LVU297
	ldr	r2, .L125
	ldr	r3, [r2, #4]
	orr	r3, r3, #64
	str	r3, [r2, #4]
	.loc 1 922 1 is_stmt 0 view .LVU298
	bx	lr
.L126:
	.align	2
.L125:
	.word	1073770496
	.cfi_endproc
.LFE97:
	.size	HAL_PWREx_EnablePVM3, .-HAL_PWREx_EnablePVM3
	.section	.text.HAL_PWREx_DisablePVM3,"ax",%progbits
	.align	1
	.global	HAL_PWREx_DisablePVM3
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_DisablePVM3, %function
HAL_PWREx_DisablePVM3:
.LFB98:
	.loc 1 929 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 930 3 view .LVU300
	ldr	r2, .L128
	ldr	r3, [r2, #4]
	bic	r3, r3, #64
	str	r3, [r2, #4]
	.loc 1 931 1 is_stmt 0 view .LVU301
	bx	lr
.L129:
	.align	2
.L128:
	.word	1073770496
	.cfi_endproc
.LFE98:
	.size	HAL_PWREx_DisablePVM3, .-HAL_PWREx_DisablePVM3
	.section	.text.HAL_PWREx_EnablePVM4,"ax",%progbits
	.align	1
	.global	HAL_PWREx_EnablePVM4
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_EnablePVM4, %function
HAL_PWREx_EnablePVM4:
.LFB99:
	.loc 1 939 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 940 3 view .LVU303
	ldr	r2, .L131
	ldr	r3, [r2, #4]
	orr	r3, r3, #128
	str	r3, [r2, #4]
	.loc 1 941 1 is_stmt 0 view .LVU304
	bx	lr
.L132:
	.align	2
.L131:
	.word	1073770496
	.cfi_endproc
.LFE99:
	.size	HAL_PWREx_EnablePVM4, .-HAL_PWREx_EnablePVM4
	.section	.text.HAL_PWREx_DisablePVM4,"ax",%progbits
	.align	1
	.global	HAL_PWREx_DisablePVM4
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_DisablePVM4, %function
HAL_PWREx_DisablePVM4:
.LFB100:
	.loc 1 948 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 949 3 view .LVU306
	ldr	r2, .L134
	ldr	r3, [r2, #4]
	bic	r3, r3, #128
	str	r3, [r2, #4]
	.loc 1 950 1 is_stmt 0 view .LVU307
	bx	lr
.L135:
	.align	2
.L134:
	.word	1073770496
	.cfi_endproc
.LFE100:
	.size	HAL_PWREx_DisablePVM4, .-HAL_PWREx_DisablePVM4
	.section	.text.HAL_PWREx_ConfigPVM,"ax",%progbits
	.align	1
	.global	HAL_PWREx_ConfigPVM
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_ConfigPVM, %function
HAL_PWREx_ConfigPVM:
.LVL102:
.LFB101:
	.loc 1 968 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 969 3 view .LVU309
	.loc 1 972 3 view .LVU310
	.loc 1 973 3 view .LVU311
	.loc 1 979 3 view .LVU312
	.loc 1 979 21 is_stmt 0 view .LVU313
	ldr	r3, [r0]
	.loc 1 979 3 view .LVU314
	cmp	r3, #64
	beq	.L137
	bhi	.L138
	cmp	r3, #16
	beq	.L139
	cmp	r3, #32
	bne	.L159
	.loc 1 1017 7 is_stmt 1 view .LVU315
	ldr	r3, .L161
	ldr	r2, [r3, #36]
	bic	r2, r2, #16
	str	r2, [r3, #36]
	.loc 1 1018 7 view .LVU316
	ldr	r2, [r3, #32]
	bic	r2, r2, #16
	str	r2, [r3, #32]
	.loc 1 1019 7 view .LVU317
	ldr	r2, [r3, #44]
	bic	r2, r2, #16
	str	r2, [r3, #44]
	.loc 1 1020 7 view .LVU318
	ldr	r2, [r3, #40]
	bic	r2, r2, #16
	str	r2, [r3, #40]
	.loc 1 1023 7 view .LVU319
	.loc 1 1023 21 is_stmt 0 view .LVU320
	ldr	r3, [r0, #4]
	.loc 1 1023 9 view .LVU321
	tst	r3, #65536
	beq	.L146
	.loc 1 1025 9 is_stmt 1 view .LVU322
	ldr	r2, .L161
	ldr	r3, [r2, #32]
	orr	r3, r3, #16
	str	r3, [r2, #32]
.L146:
	.loc 1 1029 7 view .LVU323
	.loc 1 1029 21 is_stmt 0 view .LVU324
	ldr	r3, [r0, #4]
	.loc 1 1029 9 view .LVU325
	tst	r3, #131072
	beq	.L147
	.loc 1 1031 9 is_stmt 1 view .LVU326
	ldr	r2, .L161
	ldr	r3, [r2, #36]
	orr	r3, r3, #16
	str	r3, [r2, #36]
.L147:
	.loc 1 1035 7 view .LVU327
	.loc 1 1035 21 is_stmt 0 view .LVU328
	ldr	r3, [r0, #4]
	.loc 1 1035 9 view .LVU329
	tst	r3, #1
	beq	.L148
	.loc 1 1037 9 is_stmt 1 view .LVU330
	ldr	r2, .L161
	ldr	r3, [r2, #40]
	orr	r3, r3, #16
	str	r3, [r2, #40]
.L148:
	.loc 1 1040 7 view .LVU331
	.loc 1 1040 21 is_stmt 0 view .LVU332
	ldr	r3, [r0, #4]
	.loc 1 1040 9 view .LVU333
	tst	r3, #2
	beq	.L156
	.loc 1 1042 9 is_stmt 1 view .LVU334
	ldr	r2, .L161
	ldr	r3, [r2, #44]
	orr	r3, r3, #16
	str	r3, [r2, #44]
	.loc 1 969 21 is_stmt 0 view .LVU335
	movs	r0, #0
.LVL103:
	.loc 1 969 21 view .LVU336
	bx	lr
.LVL104:
.L159:
	.loc 1 979 3 view .LVU337
	movs	r0, #1
.LVL105:
	.loc 1 979 3 view .LVU338
	bx	lr
.LVL106:
.L138:
	.loc 1 979 3 view .LVU339
	cmp	r3, #128
	bne	.L160
	.loc 1 1080 7 is_stmt 1 view .LVU340
	ldr	r3, .L161
	ldr	r2, [r3, #36]
	bic	r2, r2, #64
	str	r2, [r3, #36]
	.loc 1 1081 7 view .LVU341
	ldr	r2, [r3, #32]
	bic	r2, r2, #64
	str	r2, [r3, #32]
	.loc 1 1082 7 view .LVU342
	ldr	r2, [r3, #44]
	bic	r2, r2, #64
	str	r2, [r3, #44]
	.loc 1 1083 7 view .LVU343
	ldr	r2, [r3, #40]
	bic	r2, r2, #64
	str	r2, [r3, #40]
	.loc 1 1086 7 view .LVU344
	.loc 1 1086 21 is_stmt 0 view .LVU345
	ldr	r3, [r0, #4]
	.loc 1 1086 9 view .LVU346
	tst	r3, #65536
	beq	.L152
	.loc 1 1088 9 is_stmt 1 view .LVU347
	ldr	r2, .L161
	ldr	r3, [r2, #32]
	orr	r3, r3, #64
	str	r3, [r2, #32]
.L152:
	.loc 1 1092 7 view .LVU348
	.loc 1 1092 21 is_stmt 0 view .LVU349
	ldr	r3, [r0, #4]
	.loc 1 1092 9 view .LVU350
	tst	r3, #131072
	beq	.L153
	.loc 1 1094 9 is_stmt 1 view .LVU351
	ldr	r2, .L161
	ldr	r3, [r2, #36]
	orr	r3, r3, #64
	str	r3, [r2, #36]
.L153:
	.loc 1 1098 7 view .LVU352
	.loc 1 1098 21 is_stmt 0 view .LVU353
	ldr	r3, [r0, #4]
	.loc 1 1098 9 view .LVU354
	tst	r3, #1
	beq	.L154
	.loc 1 1100 9 is_stmt 1 view .LVU355
	ldr	r2, .L161
	ldr	r3, [r2, #40]
	orr	r3, r3, #64
	str	r3, [r2, #40]
.L154:
	.loc 1 1103 7 view .LVU356
	.loc 1 1103 21 is_stmt 0 view .LVU357
	ldr	r3, [r0, #4]
	.loc 1 1103 9 view .LVU358
	tst	r3, #2
	beq	.L158
	.loc 1 1105 9 is_stmt 1 view .LVU359
	ldr	r2, .L161
	ldr	r3, [r2, #44]
	orr	r3, r3, #64
	str	r3, [r2, #44]
	.loc 1 969 21 is_stmt 0 view .LVU360
	movs	r0, #0
.LVL107:
	.loc 1 969 21 view .LVU361
	bx	lr
.LVL108:
.L160:
	.loc 1 979 3 view .LVU362
	movs	r0, #1
.LVL109:
	.loc 1 979 3 view .LVU363
	bx	lr
.LVL110:
.L139:
	.loc 1 984 7 is_stmt 1 view .LVU364
	ldr	r3, .L161
	ldr	r2, [r3, #36]
	bic	r2, r2, #8
	str	r2, [r3, #36]
	.loc 1 985 7 view .LVU365
	ldr	r2, [r3, #32]
	bic	r2, r2, #8
	str	r2, [r3, #32]
	.loc 1 986 7 view .LVU366
	ldr	r2, [r3, #44]
	bic	r2, r2, #8
	str	r2, [r3, #44]
	.loc 1 987 7 view .LVU367
	ldr	r2, [r3, #40]
	bic	r2, r2, #8
	str	r2, [r3, #40]
	.loc 1 990 7 view .LVU368
	.loc 1 990 21 is_stmt 0 view .LVU369
	ldr	r3, [r0, #4]
	.loc 1 990 9 view .LVU370
	tst	r3, #65536
	beq	.L143
	.loc 1 992 9 is_stmt 1 view .LVU371
	ldr	r2, .L161
	ldr	r3, [r2, #32]
	orr	r3, r3, #8
	str	r3, [r2, #32]
.L143:
	.loc 1 996 7 view .LVU372
	.loc 1 996 21 is_stmt 0 view .LVU373
	ldr	r3, [r0, #4]
	.loc 1 996 9 view .LVU374
	tst	r3, #131072
	beq	.L144
	.loc 1 998 9 is_stmt 1 view .LVU375
	ldr	r2, .L161
	ldr	r3, [r2, #36]
	orr	r3, r3, #8
	str	r3, [r2, #36]
.L144:
	.loc 1 1002 7 view .LVU376
	.loc 1 1002 21 is_stmt 0 view .LVU377
	ldr	r3, [r0, #4]
	.loc 1 1002 9 view .LVU378
	tst	r3, #1
	beq	.L145
	.loc 1 1004 9 is_stmt 1 view .LVU379
	ldr	r2, .L161
	ldr	r3, [r2, #40]
	orr	r3, r3, #8
	str	r3, [r2, #40]
.L145:
	.loc 1 1007 7 view .LVU380
	.loc 1 1007 21 is_stmt 0 view .LVU381
	ldr	r3, [r0, #4]
	.loc 1 1007 9 view .LVU382
	tst	r3, #2
	beq	.L155
	.loc 1 1009 9 is_stmt 1 view .LVU383
	ldr	r2, .L161
	ldr	r3, [r2, #44]
	orr	r3, r3, #8
	str	r3, [r2, #44]
	.loc 1 969 21 is_stmt 0 view .LVU384
	movs	r0, #0
.LVL111:
	.loc 1 969 21 view .LVU385
	bx	lr
.LVL112:
.L137:
	.loc 1 1049 7 is_stmt 1 view .LVU386
	ldr	r3, .L161
	ldr	r2, [r3, #36]
	bic	r2, r2, #32
	str	r2, [r3, #36]
	.loc 1 1050 7 view .LVU387
	ldr	r2, [r3, #32]
	bic	r2, r2, #32
	str	r2, [r3, #32]
	.loc 1 1051 7 view .LVU388
	ldr	r2, [r3, #44]
	bic	r2, r2, #32
	str	r2, [r3, #44]
	.loc 1 1052 7 view .LVU389
	ldr	r2, [r3, #40]
	bic	r2, r2, #32
	str	r2, [r3, #40]
	.loc 1 1055 7 view .LVU390
	.loc 1 1055 21 is_stmt 0 view .LVU391
	ldr	r3, [r0, #4]
	.loc 1 1055 9 view .LVU392
	tst	r3, #65536
	beq	.L149
	.loc 1 1057 9 is_stmt 1 view .LVU393
	ldr	r2, .L161
	ldr	r3, [r2, #32]
	orr	r3, r3, #32
	str	r3, [r2, #32]
.L149:
	.loc 1 1061 7 view .LVU394
	.loc 1 1061 21 is_stmt 0 view .LVU395
	ldr	r3, [r0, #4]
	.loc 1 1061 9 view .LVU396
	tst	r3, #131072
	beq	.L150
	.loc 1 1063 9 is_stmt 1 view .LVU397
	ldr	r2, .L161
	ldr	r3, [r2, #36]
	orr	r3, r3, #32
	str	r3, [r2, #36]
.L150:
	.loc 1 1067 7 view .LVU398
	.loc 1 1067 21 is_stmt 0 view .LVU399
	ldr	r3, [r0, #4]
	.loc 1 1067 9 view .LVU400
	tst	r3, #1
	beq	.L151
	.loc 1 1069 9 is_stmt 1 view .LVU401
	ldr	r2, .L161
	ldr	r3, [r2, #40]
	orr	r3, r3, #32
	str	r3, [r2, #40]
.L151:
	.loc 1 1072 7 view .LVU402
	.loc 1 1072 21 is_stmt 0 view .LVU403
	ldr	r3, [r0, #4]
	.loc 1 1072 9 view .LVU404
	tst	r3, #2
	beq	.L157
	.loc 1 1074 9 is_stmt 1 view .LVU405
	ldr	r2, .L161
	ldr	r3, [r2, #44]
	orr	r3, r3, #32
	str	r3, [r2, #44]
	.loc 1 969 21 is_stmt 0 view .LVU406
	movs	r0, #0
.LVL113:
	.loc 1 969 21 view .LVU407
	bx	lr
.LVL114:
.L155:
	.loc 1 969 21 view .LVU408
	movs	r0, #0
.LVL115:
	.loc 1 969 21 view .LVU409
	bx	lr
.LVL116:
.L156:
	.loc 1 969 21 view .LVU410
	movs	r0, #0
.LVL117:
	.loc 1 969 21 view .LVU411
	bx	lr
.LVL118:
.L157:
	.loc 1 969 21 view .LVU412
	movs	r0, #0
.LVL119:
	.loc 1 969 21 view .LVU413
	bx	lr
.LVL120:
.L158:
	.loc 1 969 21 view .LVU414
	movs	r0, #0
.LVL121:
	.loc 1 1114 3 is_stmt 1 view .LVU415
	.loc 1 1115 1 is_stmt 0 view .LVU416
	bx	lr
.L162:
	.align	2
.L161:
	.word	1073808384
	.cfi_endproc
.LFE101:
	.size	HAL_PWREx_ConfigPVM, .-HAL_PWREx_ConfigPVM
	.section	.text.HAL_PWREx_EnableLowPowerRunMode,"ax",%progbits
	.align	1
	.global	HAL_PWREx_EnableLowPowerRunMode
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_EnableLowPowerRunMode, %function
HAL_PWREx_EnableLowPowerRunMode:
.LFB102:
	.loc 1 1130 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1132 3 view .LVU418
	ldr	r2, .L164
	ldr	r3, [r2]
	orr	r3, r3, #16384
	str	r3, [r2]
	.loc 1 1133 1 is_stmt 0 view .LVU419
	bx	lr
.L165:
	.align	2
.L164:
	.word	1073770496
	.cfi_endproc
.LFE102:
	.size	HAL_PWREx_EnableLowPowerRunMode, .-HAL_PWREx_EnableLowPowerRunMode
	.section	.text.HAL_PWREx_DisableLowPowerRunMode,"ax",%progbits
	.align	1
	.global	HAL_PWREx_DisableLowPowerRunMode
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_DisableLowPowerRunMode, %function
HAL_PWREx_DisableLowPowerRunMode:
.LFB103:
	.loc 1 1145 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1146 3 view .LVU421
	.loc 1 1149 3 view .LVU422
	ldr	r2, .L172
	ldr	r3, [r2]
	bic	r3, r3, #16384
	str	r3, [r2]
	.loc 1 1152 3 view .LVU423
	.loc 1 1152 49 is_stmt 0 view .LVU424
	ldr	r3, .L172+4
	ldr	r3, [r3]
	movs	r2, #50
	mul	r3, r2, r3
	.loc 1 1152 68 view .LVU425
	ldr	r2, .L172+8
	umull	r2, r3, r2, r3
	lsrs	r3, r3, #18
	.loc 1 1152 19 view .LVU426
	adds	r3, r3, #1
.LVL122:
	.loc 1 1153 3 is_stmt 1 view .LVU427
	.loc 1 1153 9 is_stmt 0 view .LVU428
	b	.L167
.L169:
	.loc 1 1155 5 is_stmt 1 view .LVU429
	.loc 1 1155 20 is_stmt 0 view .LVU430
	subs	r3, r3, #1
.LVL123:
.L167:
	.loc 1 1153 53 is_stmt 1 view .LVU431
	.loc 1 1153 11 is_stmt 0 view .LVU432
	ldr	r2, .L172
	ldr	r2, [r2, #20]
	.loc 1 1153 53 view .LVU433
	tst	r2, #512
	beq	.L168
	.loc 1 1153 53 discriminator 1 view .LVU434
	cmp	r3, #0
	bne	.L169
.L168:
	.loc 1 1157 3 is_stmt 1 view .LVU435
	.loc 1 1157 7 is_stmt 0 view .LVU436
	ldr	r3, .L172
.LVL124:
	.loc 1 1157 7 view .LVU437
	ldr	r3, [r3, #20]
	.loc 1 1157 6 view .LVU438
	tst	r3, #512
	bne	.L171
	.loc 1 1162 10 view .LVU439
	movs	r0, #0
	bx	lr
.L171:
	.loc 1 1159 12 view .LVU440
	movs	r0, #3
	.loc 1 1163 1 view .LVU441
	bx	lr
.L173:
	.align	2
.L172:
	.word	1073770496
	.word	SystemCoreClock
	.word	1125899907
	.cfi_endproc
.LFE103:
	.size	HAL_PWREx_DisableLowPowerRunMode, .-HAL_PWREx_DisableLowPowerRunMode
	.section	.text.HAL_PWREx_EnterSTOP0Mode,"ax",%progbits
	.align	1
	.global	HAL_PWREx_EnterSTOP0Mode
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_EnterSTOP0Mode, %function
HAL_PWREx_EnterSTOP0Mode:
.LVL125:
.LFB104:
	.loc 1 1189 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1191 3 view .LVU443
	.loc 1 1194 3 view .LVU444
	ldr	r2, .L178
	ldr	r3, [r2]
	bic	r3, r3, #7
	str	r3, [r2]
	.loc 1 1197 3 view .LVU445
	ldr	r2, .L178+4
	ldr	r3, [r2, #16]
	orr	r3, r3, #4
	str	r3, [r2, #16]
	.loc 1 1200 3 view .LVU446
	.loc 1 1200 5 is_stmt 0 view .LVU447
	cmp	r0, #1
	beq	.L177
	.loc 1 1208 5 is_stmt 1 view .LVU448
	.syntax unified
@ 1208 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c" 1
	sev
@ 0 "" 2
	.loc 1 1209 5 view .LVU449
@ 1209 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c" 1
	wfe
@ 0 "" 2
	.loc 1 1210 5 view .LVU450
@ 1210 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c" 1
	wfe
@ 0 "" 2
	.thumb
	.syntax unified
.L176:
	.loc 1 1214 3 view .LVU451
	ldr	r2, .L178+4
	ldr	r3, [r2, #16]
	bic	r3, r3, #4
	str	r3, [r2, #16]
	.loc 1 1215 1 is_stmt 0 view .LVU452
	bx	lr
.L177:
	.loc 1 1203 5 is_stmt 1 view .LVU453
	.syntax unified
@ 1203 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c" 1
	wfi
@ 0 "" 2
	.thumb
	.syntax unified
	b	.L176
.L179:
	.align	2
.L178:
	.word	1073770496
	.word	-536810240
	.cfi_endproc
.LFE104:
	.size	HAL_PWREx_EnterSTOP0Mode, .-HAL_PWREx_EnterSTOP0Mode
	.section	.text.HAL_PWREx_EnterSTOP1Mode,"ax",%progbits
	.align	1
	.global	HAL_PWREx_EnterSTOP1Mode
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_EnterSTOP1Mode, %function
HAL_PWREx_EnterSTOP1Mode:
.LVL126:
.LFB105:
	.loc 1 1240 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1242 3 view .LVU455
	.loc 1 1245 3 view .LVU456
	ldr	r2, .L184
	ldr	r3, [r2]
	bic	r3, r3, #7
	orr	r3, r3, #1
	str	r3, [r2]
	.loc 1 1248 3 view .LVU457
	ldr	r2, .L184+4
	ldr	r3, [r2, #16]
	orr	r3, r3, #4
	str	r3, [r2, #16]
	.loc 1 1251 3 view .LVU458
	.loc 1 1251 5 is_stmt 0 view .LVU459
	cmp	r0, #1
	beq	.L183
	.loc 1 1259 5 is_stmt 1 view .LVU460
	.syntax unified
@ 1259 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c" 1
	sev
@ 0 "" 2
	.loc 1 1260 5 view .LVU461
@ 1260 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c" 1
	wfe
@ 0 "" 2
	.loc 1 1261 5 view .LVU462
@ 1261 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c" 1
	wfe
@ 0 "" 2
	.thumb
	.syntax unified
.L182:
	.loc 1 1265 3 view .LVU463
	ldr	r2, .L184+4
	ldr	r3, [r2, #16]
	bic	r3, r3, #4
	str	r3, [r2, #16]
	.loc 1 1266 1 is_stmt 0 view .LVU464
	bx	lr
.L183:
	.loc 1 1254 5 is_stmt 1 view .LVU465
	.syntax unified
@ 1254 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c" 1
	wfi
@ 0 "" 2
	.thumb
	.syntax unified
	b	.L182
.L185:
	.align	2
.L184:
	.word	1073770496
	.word	-536810240
	.cfi_endproc
.LFE105:
	.size	HAL_PWREx_EnterSTOP1Mode, .-HAL_PWREx_EnterSTOP1Mode
	.section	.text.HAL_PWREx_EnterSTOP2Mode,"ax",%progbits
	.align	1
	.global	HAL_PWREx_EnterSTOP2Mode
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_EnterSTOP2Mode, %function
HAL_PWREx_EnterSTOP2Mode:
.LVL127:
.LFB106:
	.loc 1 1293 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1295 3 view .LVU467
	.loc 1 1298 3 view .LVU468
	ldr	r2, .L190
	ldr	r3, [r2]
	bic	r3, r3, #7
	orr	r3, r3, #2
	str	r3, [r2]
	.loc 1 1301 3 view .LVU469
	ldr	r2, .L190+4
	ldr	r3, [r2, #16]
	orr	r3, r3, #4
	str	r3, [r2, #16]
	.loc 1 1304 3 view .LVU470
	.loc 1 1304 5 is_stmt 0 view .LVU471
	cmp	r0, #1
	beq	.L189
	.loc 1 1312 5 is_stmt 1 view .LVU472
	.syntax unified
@ 1312 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c" 1
	sev
@ 0 "" 2
	.loc 1 1313 5 view .LVU473
@ 1313 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c" 1
	wfe
@ 0 "" 2
	.loc 1 1314 5 view .LVU474
@ 1314 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c" 1
	wfe
@ 0 "" 2
	.thumb
	.syntax unified
.L188:
	.loc 1 1318 3 view .LVU475
	ldr	r2, .L190+4
	ldr	r3, [r2, #16]
	bic	r3, r3, #4
	str	r3, [r2, #16]
	.loc 1 1319 1 is_stmt 0 view .LVU476
	bx	lr
.L189:
	.loc 1 1307 5 is_stmt 1 view .LVU477
	.syntax unified
@ 1307 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c" 1
	wfi
@ 0 "" 2
	.thumb
	.syntax unified
	b	.L188
.L191:
	.align	2
.L190:
	.word	1073770496
	.word	-536810240
	.cfi_endproc
.LFE106:
	.size	HAL_PWREx_EnterSTOP2Mode, .-HAL_PWREx_EnterSTOP2Mode
	.section	.text.HAL_PWREx_EnterSHUTDOWNMode,"ax",%progbits
	.align	1
	.global	HAL_PWREx_EnterSHUTDOWNMode
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_EnterSHUTDOWNMode, %function
HAL_PWREx_EnterSHUTDOWNMode:
.LFB107:
	.loc 1 1335 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1338 3 view .LVU479
	ldr	r2, .L193
	ldr	r3, [r2]
	bic	r3, r3, #7
	orr	r3, r3, #4
	str	r3, [r2]
	.loc 1 1341 3 view .LVU480
	ldr	r2, .L193+4
	ldr	r3, [r2, #16]
	orr	r3, r3, #4
	str	r3, [r2, #16]
	.loc 1 1348 3 view .LVU481
	.syntax unified
@ 1348 "../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_pwr_ex.c" 1
	wfi
@ 0 "" 2
	.loc 1 1349 1 is_stmt 0 view .LVU482
	.thumb
	.syntax unified
	bx	lr
.L194:
	.align	2
.L193:
	.word	1073770496
	.word	-536810240
	.cfi_endproc
.LFE107:
	.size	HAL_PWREx_EnterSHUTDOWNMode, .-HAL_PWREx_EnterSHUTDOWNMode
	.section	.text.HAL_PWREx_PVM1Callback,"ax",%progbits
	.align	1
	.weak	HAL_PWREx_PVM1Callback
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_PVM1Callback, %function
HAL_PWREx_PVM1Callback:
.LFB109:
	.loc 1 1416 1 is_stmt 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1420 1 view .LVU484
	bx	lr
	.cfi_endproc
.LFE109:
	.size	HAL_PWREx_PVM1Callback, .-HAL_PWREx_PVM1Callback
	.section	.text.HAL_PWREx_PVM2Callback,"ax",%progbits
	.align	1
	.weak	HAL_PWREx_PVM2Callback
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_PVM2Callback, %function
HAL_PWREx_PVM2Callback:
.LFB110:
	.loc 1 1429 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1433 1 view .LVU486
	bx	lr
	.cfi_endproc
.LFE110:
	.size	HAL_PWREx_PVM2Callback, .-HAL_PWREx_PVM2Callback
	.section	.text.HAL_PWREx_PVM3Callback,"ax",%progbits
	.align	1
	.weak	HAL_PWREx_PVM3Callback
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_PVM3Callback, %function
HAL_PWREx_PVM3Callback:
.LFB111:
	.loc 1 1441 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1445 1 view .LVU488
	bx	lr
	.cfi_endproc
.LFE111:
	.size	HAL_PWREx_PVM3Callback, .-HAL_PWREx_PVM3Callback
	.section	.text.HAL_PWREx_PVM4Callback,"ax",%progbits
	.align	1
	.weak	HAL_PWREx_PVM4Callback
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_PVM4Callback, %function
HAL_PWREx_PVM4Callback:
.LFB112:
	.loc 1 1452 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 1456 1 view .LVU490
	bx	lr
	.cfi_endproc
.LFE112:
	.size	HAL_PWREx_PVM4Callback, .-HAL_PWREx_PVM4Callback
	.section	.text.HAL_PWREx_PVD_PVM_IRQHandler,"ax",%progbits
	.align	1
	.global	HAL_PWREx_PVD_PVM_IRQHandler
	.syntax unified
	.thumb
	.thumb_func
	.type	HAL_PWREx_PVD_PVM_IRQHandler, %function
HAL_PWREx_PVD_PVM_IRQHandler:
.LFB108:
	.loc 1 1360 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	push	{r3, lr}
.LCFI2:
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	.cfi_offset 14, -4
	.loc 1 1362 3 view .LVU492
	.loc 1 1362 6 is_stmt 0 view .LVU493
	ldr	r3, .L211
	ldr	r3, [r3, #20]
	.loc 1 1362 5 view .LVU494
	tst	r3, #65536
	bne	.L206
.L200:
	.loc 1 1372 3 is_stmt 1 view .LVU495
	.loc 1 1372 6 is_stmt 0 view .LVU496
	ldr	r3, .L211
	ldr	r3, [r3, #52]
	.loc 1 1372 5 view .LVU497
	tst	r3, #8
	bne	.L207
.L201:
	.loc 1 1382 3 is_stmt 1 view .LVU498
	.loc 1 1382 6 is_stmt 0 view .LVU499
	ldr	r3, .L211
	ldr	r3, [r3, #52]
	.loc 1 1382 5 view .LVU500
	tst	r3, #16
	bne	.L208
.L202:
	.loc 1 1391 3 is_stmt 1 view .LVU501
	.loc 1 1391 6 is_stmt 0 view .LVU502
	ldr	r3, .L211
	ldr	r3, [r3, #52]
	.loc 1 1391 5 view .LVU503
	tst	r3, #32
	bne	.L209
.L203:
	.loc 1 1399 3 is_stmt 1 view .LVU504
	.loc 1 1399 6 is_stmt 0 view .LVU505
	ldr	r3, .L211
	ldr	r3, [r3, #52]
	.loc 1 1399 5 view .LVU506
	tst	r3, #64
	bne	.L210
.L199:
	.loc 1 1407 1 view .LVU507
	pop	{r3, pc}
.L206:
	.loc 1 1365 5 is_stmt 1 view .LVU508
	bl	HAL_PWR_PVDCallback
.LVL128:
	.loc 1 1368 5 view .LVU509
	ldr	r3, .L211
	mov	r2, #65536
	str	r2, [r3, #20]
	b	.L200
.L207:
	.loc 1 1375 5 view .LVU510
	bl	HAL_PWREx_PVM1Callback
.LVL129:
	.loc 1 1378 5 view .LVU511
	ldr	r3, .L211
	movs	r2, #8
	str	r2, [r3, #52]
	b	.L201
.L208:
	.loc 1 1385 5 view .LVU512
	bl	HAL_PWREx_PVM2Callback
.LVL130:
	.loc 1 1388 5 view .LVU513
	ldr	r3, .L211
	movs	r2, #16
	str	r2, [r3, #52]
	b	.L202
.L209:
	.loc 1 1394 5 view .LVU514
	bl	HAL_PWREx_PVM3Callback
.LVL131:
	.loc 1 1397 5 view .LVU515
	ldr	r3, .L211
	movs	r2, #32
	str	r2, [r3, #52]
	b	.L203
.L210:
	.loc 1 1402 5 view .LVU516
	bl	HAL_PWREx_PVM4Callback
.LVL132:
	.loc 1 1405 5 view .LVU517
	ldr	r3, .L211
	movs	r2, #64
	str	r2, [r3, #52]
	.loc 1 1407 1 is_stmt 0 view .LVU518
	b	.L199
.L212:
	.align	2
.L211:
	.word	1073808384
	.cfi_endproc
.LFE108:
	.size	HAL_PWREx_PVD_PVM_IRQHandler, .-HAL_PWREx_PVD_PVM_IRQHandler
	.text
.Letext0:
	.file 2 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/arm-none-eabi/include/machine/_default_types.h"
	.file 3 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/arm-none-eabi/include/sys/_stdint.h"
	.file 4 "../Drivers/CMSIS/Include/core_cm4.h"
	.file 5 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
	.file 6 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_def.h"
	.file 7 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr_ex.h"
	.file 8 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/system_stm32l4xx.h"
	.file 9 "../Drivers/STM32L4xx_HAL_Driver/Inc/stm32l4xx_hal_pwr.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0xb97
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF117
	.byte	0xc
	.4byte	.LASF118
	.4byte	.LASF119
	.4byte	.Ldebug_ranges0+0
	.4byte	0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x3
	.4byte	.LASF5
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
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF4
	.uleb128 0x3
	.4byte	.LASF6
	.byte	0x2
	.byte	0x4f
	.byte	0x19
	.4byte	0x64
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.ascii	"int\000"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x3
	.4byte	.LASF11
	.byte	0x3
	.byte	0x18
	.byte	0x13
	.4byte	0x30
	.uleb128 0x5
	.4byte	0x87
	.uleb128 0x3
	.4byte	.LASF12
	.byte	0x3
	.byte	0x30
	.byte	0x14
	.4byte	0x58
	.uleb128 0x5
	.4byte	0x98
	.uleb128 0x6
	.4byte	0xa4
	.uleb128 0x7
	.byte	0x8c
	.byte	0x4
	.2byte	0x1b8
	.byte	0x9
	.4byte	0x20a
	.uleb128 0x8
	.4byte	.LASF13
	.byte	0x4
	.2byte	0x1ba
	.byte	0x12
	.4byte	0xa9
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF14
	.byte	0x4
	.2byte	0x1bb
	.byte	0x12
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.4byte	.LASF15
	.byte	0x4
	.2byte	0x1bc
	.byte	0x12
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x8
	.4byte	.LASF16
	.byte	0x4
	.2byte	0x1bd
	.byte	0x12
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x9
	.ascii	"SCR\000"
	.byte	0x4
	.2byte	0x1be
	.byte	0x12
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x9
	.ascii	"CCR\000"
	.byte	0x4
	.2byte	0x1bf
	.byte	0x12
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x9
	.ascii	"SHP\000"
	.byte	0x4
	.2byte	0x1c0
	.byte	0x12
	.4byte	0x21a
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x8
	.4byte	.LASF17
	.byte	0x4
	.2byte	0x1c1
	.byte	0x12
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0x8
	.4byte	.LASF18
	.byte	0x4
	.2byte	0x1c2
	.byte	0x12
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0x8
	.4byte	.LASF19
	.byte	0x4
	.2byte	0x1c3
	.byte	0x12
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0x8
	.4byte	.LASF20
	.byte	0x4
	.2byte	0x1c4
	.byte	0x12
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0x8
	.4byte	.LASF21
	.byte	0x4
	.2byte	0x1c5
	.byte	0x12
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.uleb128 0x8
	.4byte	.LASF22
	.byte	0x4
	.2byte	0x1c6
	.byte	0x12
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0x8
	.4byte	.LASF23
	.byte	0x4
	.2byte	0x1c7
	.byte	0x12
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x3c
	.uleb128 0x9
	.ascii	"PFR\000"
	.byte	0x4
	.2byte	0x1c8
	.byte	0x12
	.4byte	0x234
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0x9
	.ascii	"DFR\000"
	.byte	0x4
	.2byte	0x1c9
	.byte	0x12
	.4byte	0xa9
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0x9
	.ascii	"ADR\000"
	.byte	0x4
	.2byte	0x1ca
	.byte	0x12
	.4byte	0xa9
	.byte	0x2
	.byte	0x23
	.uleb128 0x4c
	.uleb128 0x8
	.4byte	.LASF24
	.byte	0x4
	.2byte	0x1cb
	.byte	0x12
	.4byte	0x24e
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0x8
	.4byte	.LASF25
	.byte	0x4
	.2byte	0x1cc
	.byte	0x12
	.4byte	0x268
	.byte	0x2
	.byte	0x23
	.uleb128 0x60
	.uleb128 0x8
	.4byte	.LASF26
	.byte	0x4
	.2byte	0x1cd
	.byte	0x12
	.4byte	0x26d
	.byte	0x2
	.byte	0x23
	.uleb128 0x74
	.uleb128 0x8
	.4byte	.LASF27
	.byte	0x4
	.2byte	0x1ce
	.byte	0x12
	.4byte	0xa4
	.byte	0x3
	.byte	0x23
	.uleb128 0x88
	.byte	0
	.uleb128 0xa
	.4byte	0x93
	.4byte	0x21a
	.uleb128 0xb
	.4byte	0x80
	.byte	0xb
	.byte	0
	.uleb128 0x5
	.4byte	0x20a
	.uleb128 0xa
	.4byte	0xa9
	.4byte	0x22f
	.uleb128 0xb
	.4byte	0x80
	.byte	0x1
	.byte	0
	.uleb128 0x6
	.4byte	0x21f
	.uleb128 0x5
	.4byte	0x22f
	.uleb128 0xa
	.4byte	0xa9
	.4byte	0x249
	.uleb128 0xb
	.4byte	0x80
	.byte	0x3
	.byte	0
	.uleb128 0x6
	.4byte	0x239
	.uleb128 0x5
	.4byte	0x249
	.uleb128 0xa
	.4byte	0xa9
	.4byte	0x263
	.uleb128 0xb
	.4byte	0x80
	.byte	0x4
	.byte	0
	.uleb128 0x6
	.4byte	0x253
	.uleb128 0x5
	.4byte	0x263
	.uleb128 0xa
	.4byte	0x98
	.4byte	0x27d
	.uleb128 0xb
	.4byte	0x80
	.byte	0x4
	.byte	0
	.uleb128 0xc
	.4byte	.LASF28
	.byte	0x4
	.2byte	0x1cf
	.byte	0x3
	.4byte	0xae
	.uleb128 0xd
	.4byte	.LASF79
	.byte	0x8
	.byte	0x39
	.byte	0x11
	.4byte	0x98
	.byte	0x1
	.byte	0x1
	.uleb128 0x7
	.byte	0x38
	.byte	0x5
	.2byte	0x1ae
	.byte	0x9
	.4byte	0x383
	.uleb128 0x8
	.4byte	.LASF29
	.byte	0x5
	.2byte	0x1b0
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x8
	.4byte	.LASF30
	.byte	0x5
	.2byte	0x1b1
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x8
	.4byte	.LASF31
	.byte	0x5
	.2byte	0x1b2
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x8
	.4byte	.LASF32
	.byte	0x5
	.2byte	0x1b3
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x8
	.4byte	.LASF33
	.byte	0x5
	.2byte	0x1b4
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x9
	.ascii	"PR1\000"
	.byte	0x5
	.2byte	0x1b5
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x8
	.4byte	.LASF34
	.byte	0x5
	.2byte	0x1b6
	.byte	0x11
	.4byte	0x98
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x8
	.4byte	.LASF35
	.byte	0x5
	.2byte	0x1b7
	.byte	0x11
	.4byte	0x98
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0x8
	.4byte	.LASF36
	.byte	0x5
	.2byte	0x1b8
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0x8
	.4byte	.LASF37
	.byte	0x5
	.2byte	0x1b9
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0x8
	.4byte	.LASF38
	.byte	0x5
	.2byte	0x1ba
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0x8
	.4byte	.LASF39
	.byte	0x5
	.2byte	0x1bb
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0x8
	.4byte	.LASF40
	.byte	0x5
	.2byte	0x1bc
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0x9
	.ascii	"PR2\000"
	.byte	0x5
	.2byte	0x1bd
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.byte	0
	.uleb128 0xc
	.4byte	.LASF41
	.byte	0x5
	.2byte	0x1be
	.byte	0x3
	.4byte	0x298
	.uleb128 0x7
	.byte	0x60
	.byte	0x5
	.2byte	0x267
	.byte	0x9
	.4byte	0x51b
	.uleb128 0x9
	.ascii	"CR1\000"
	.byte	0x5
	.2byte	0x269
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x9
	.ascii	"CR2\000"
	.byte	0x5
	.2byte	0x26a
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x9
	.ascii	"CR3\000"
	.byte	0x5
	.2byte	0x26b
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0x9
	.ascii	"CR4\000"
	.byte	0x5
	.2byte	0x26c
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0x9
	.ascii	"SR1\000"
	.byte	0x5
	.2byte	0x26d
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0x9
	.ascii	"SR2\000"
	.byte	0x5
	.2byte	0x26e
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0x9
	.ascii	"SCR\000"
	.byte	0x5
	.2byte	0x26f
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0x8
	.4byte	.LASF42
	.byte	0x5
	.2byte	0x270
	.byte	0xc
	.4byte	0x98
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0x8
	.4byte	.LASF43
	.byte	0x5
	.2byte	0x271
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0x8
	.4byte	.LASF44
	.byte	0x5
	.2byte	0x272
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0x8
	.4byte	.LASF45
	.byte	0x5
	.2byte	0x273
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0x8
	.4byte	.LASF46
	.byte	0x5
	.2byte	0x274
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0x8
	.4byte	.LASF47
	.byte	0x5
	.2byte	0x275
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0x8
	.4byte	.LASF48
	.byte	0x5
	.2byte	0x276
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.uleb128 0x8
	.4byte	.LASF49
	.byte	0x5
	.2byte	0x277
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0x8
	.4byte	.LASF50
	.byte	0x5
	.2byte	0x278
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x3c
	.uleb128 0x8
	.4byte	.LASF51
	.byte	0x5
	.2byte	0x279
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0x8
	.4byte	.LASF52
	.byte	0x5
	.2byte	0x27a
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x44
	.uleb128 0x8
	.4byte	.LASF53
	.byte	0x5
	.2byte	0x27b
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0x8
	.4byte	.LASF54
	.byte	0x5
	.2byte	0x27c
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x4c
	.uleb128 0x8
	.4byte	.LASF55
	.byte	0x5
	.2byte	0x27d
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0x8
	.4byte	.LASF56
	.byte	0x5
	.2byte	0x27e
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x54
	.uleb128 0x8
	.4byte	.LASF57
	.byte	0x5
	.2byte	0x27f
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0x8
	.4byte	.LASF58
	.byte	0x5
	.2byte	0x280
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x5c
	.byte	0
	.uleb128 0xc
	.4byte	.LASF59
	.byte	0x5
	.2byte	0x281
	.byte	0x3
	.4byte	0x390
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF60
	.uleb128 0xe
	.byte	0x7
	.byte	0x1
	.4byte	0x3c
	.byte	0x6
	.byte	0x27
	.byte	0x1
	.4byte	0x556
	.uleb128 0xf
	.4byte	.LASF61
	.byte	0
	.uleb128 0xf
	.4byte	.LASF62
	.byte	0x1
	.uleb128 0xf
	.4byte	.LASF63
	.byte	0x2
	.uleb128 0xf
	.4byte	.LASF64
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF65
	.byte	0x6
	.byte	0x2c
	.byte	0x3
	.4byte	0x52f
	.uleb128 0x10
	.byte	0x8
	.byte	0x7
	.byte	0x31
	.byte	0x9
	.4byte	0x58a
	.uleb128 0x11
	.4byte	.LASF66
	.byte	0x7
	.byte	0x33
	.byte	0xc
	.4byte	0x98
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x11
	.4byte	.LASF67
	.byte	0x7
	.byte	0x3c
	.byte	0xc
	.4byte	0x98
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF68
	.byte	0x7
	.byte	0x3e
	.byte	0x2
	.4byte	0x562
	.uleb128 0x12
	.byte	0x1
	.4byte	.LASF120
	.byte	0x9
	.2byte	0x183
	.byte	0x6
	.byte	0x1
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF69
	.byte	0x1
	.2byte	0x5ab
	.byte	0xd
	.byte	0x1
	.4byte	.LFB112
	.4byte	.LFE112
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF70
	.byte	0x1
	.2byte	0x5a0
	.byte	0xd
	.byte	0x1
	.4byte	.LFB111
	.4byte	.LFE111
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF71
	.byte	0x1
	.2byte	0x594
	.byte	0xd
	.byte	0x1
	.4byte	.LFB110
	.4byte	.LFE110
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF72
	.byte	0x1
	.2byte	0x587
	.byte	0xd
	.byte	0x1
	.4byte	.LFB109
	.4byte	.LFE109
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x14
	.byte	0x1
	.4byte	.LASF74
	.byte	0x1
	.2byte	0x54f
	.byte	0x6
	.byte	0x1
	.4byte	.LFB108
	.4byte	.LFE108
	.4byte	.LLST20
	.byte	0x1
	.4byte	0x648
	.uleb128 0x15
	.4byte	.LVL128
	.4byte	0x596
	.uleb128 0x15
	.4byte	.LVL129
	.4byte	0x5e7
	.uleb128 0x15
	.4byte	.LVL130
	.4byte	0x5d0
	.uleb128 0x15
	.4byte	.LVL131
	.4byte	0x5b9
	.uleb128 0x15
	.4byte	.LVL132
	.4byte	0x5a2
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF73
	.byte	0x1
	.2byte	0x536
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
	.4byte	.LASF75
	.byte	0x1
	.2byte	0x50c
	.byte	0x6
	.byte	0x1
	.4byte	.LFB106
	.4byte	.LFE106
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x68a
	.uleb128 0x17
	.4byte	.LASF77
	.byte	0x1
	.2byte	0x50c
	.byte	0x27
	.4byte	0x87
	.byte	0x1
	.byte	0x50
	.byte	0
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF76
	.byte	0x1
	.2byte	0x4d7
	.byte	0x6
	.byte	0x1
	.4byte	.LFB105
	.4byte	.LFE105
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x6b5
	.uleb128 0x17
	.4byte	.LASF77
	.byte	0x1
	.2byte	0x4d7
	.byte	0x27
	.4byte	0x87
	.byte	0x1
	.byte	0x50
	.byte	0
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF78
	.byte	0x1
	.2byte	0x4a4
	.byte	0x6
	.byte	0x1
	.4byte	.LFB104
	.4byte	.LFE104
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x6e0
	.uleb128 0x17
	.4byte	.LASF77
	.byte	0x1
	.2byte	0x4a4
	.byte	0x27
	.4byte	0x87
	.byte	0x1
	.byte	0x50
	.byte	0
	.uleb128 0x18
	.byte	0x1
	.4byte	.LASF82
	.byte	0x1
	.2byte	0x478
	.byte	0x13
	.byte	0x1
	.4byte	0x556
	.4byte	.LFB103
	.4byte	.LFE103
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x715
	.uleb128 0x19
	.4byte	.LASF80
	.byte	0x1
	.2byte	0x47a
	.byte	0xc
	.4byte	0x98
	.4byte	.LLST19
	.4byte	.LVUS19
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF81
	.byte	0x1
	.2byte	0x469
	.byte	0x6
	.byte	0x1
	.4byte	.LFB102
	.4byte	.LFE102
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x18
	.byte	0x1
	.4byte	.LASF83
	.byte	0x1
	.2byte	0x3c7
	.byte	0x13
	.byte	0x1
	.4byte	0x556
	.4byte	.LFB101
	.4byte	.LFE101
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x776
	.uleb128 0x1a
	.4byte	.LASF94
	.byte	0x1
	.2byte	0x3c7
	.byte	0x37
	.4byte	0x776
	.4byte	.LLST17
	.4byte	.LVUS17
	.uleb128 0x19
	.4byte	.LASF84
	.byte	0x1
	.2byte	0x3c9
	.byte	0x15
	.4byte	0x556
	.4byte	.LLST18
	.4byte	.LVUS18
	.byte	0
	.uleb128 0x1b
	.byte	0x4
	.4byte	0x58a
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF85
	.byte	0x1
	.2byte	0x3b3
	.byte	0x6
	.byte	0x1
	.4byte	.LFB100
	.4byte	.LFE100
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF86
	.byte	0x1
	.2byte	0x3aa
	.byte	0x6
	.byte	0x1
	.4byte	.LFB99
	.4byte	.LFE99
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF87
	.byte	0x1
	.2byte	0x3a0
	.byte	0x6
	.byte	0x1
	.4byte	.LFB98
	.4byte	.LFE98
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF88
	.byte	0x1
	.2byte	0x397
	.byte	0x6
	.byte	0x1
	.4byte	.LFB97
	.4byte	.LFE97
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF89
	.byte	0x1
	.2byte	0x38c
	.byte	0x6
	.byte	0x1
	.4byte	.LFB96
	.4byte	.LFE96
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF90
	.byte	0x1
	.2byte	0x383
	.byte	0x6
	.byte	0x1
	.4byte	.LFB95
	.4byte	.LFE95
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF91
	.byte	0x1
	.2byte	0x377
	.byte	0x6
	.byte	0x1
	.4byte	.LFB94
	.4byte	.LFE94
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF92
	.byte	0x1
	.2byte	0x36e
	.byte	0x6
	.byte	0x1
	.4byte	.LFB93
	.4byte	.LFE93
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x18
	.byte	0x1
	.4byte	.LASF93
	.byte	0x1
	.2byte	0x2ef
	.byte	0x13
	.byte	0x1
	.4byte	0x556
	.4byte	.LFB92
	.4byte	.LFE92
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x869
	.uleb128 0x1a
	.4byte	.LASF95
	.byte	0x1
	.2byte	0x2ef
	.byte	0x3f
	.4byte	0x98
	.4byte	.LLST14
	.4byte	.LVUS14
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.4byte	.LASF96
	.byte	0x1
	.2byte	0x2e0
	.byte	0x6
	.byte	0x1
	.4byte	.LFB91
	.4byte	.LFE91
	.4byte	.LLST16
	.byte	0x1
	.4byte	0x895
	.uleb128 0x1c
	.4byte	.LVL101
	.4byte	0x834
	.uleb128 0x1d
	.byte	0x1
	.byte	0x50
	.byte	0x1
	.byte	0x30
	.byte	0
	.byte	0
	.uleb128 0x14
	.byte	0x1
	.4byte	.LASF97
	.byte	0x1
	.2byte	0x2d7
	.byte	0x6
	.byte	0x1
	.4byte	.LFB90
	.4byte	.LFE90
	.4byte	.LLST15
	.byte	0x1
	.4byte	0x8c3
	.uleb128 0x1c
	.4byte	.LVL100
	.4byte	0x834
	.uleb128 0x1d
	.byte	0x1
	.byte	0x50
	.byte	0x3
	.byte	0xa
	.2byte	0x100
	.byte	0
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF98
	.byte	0x1
	.2byte	0x2cc
	.byte	0x6
	.byte	0x1
	.4byte	.LFB89
	.4byte	.LFE89
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF99
	.byte	0x1
	.2byte	0x2c0
	.byte	0x6
	.byte	0x1
	.4byte	.LFB88
	.4byte	.LFE88
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x18
	.byte	0x1
	.4byte	.LASF100
	.byte	0x1
	.2byte	0x27a
	.byte	0x13
	.byte	0x1
	.4byte	0x556
	.4byte	.LFB87
	.4byte	.LFE87
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x950
	.uleb128 0x1a
	.4byte	.LASF101
	.byte	0x1
	.2byte	0x27a
	.byte	0x3a
	.4byte	0x98
	.4byte	.LLST11
	.4byte	.LVUS11
	.uleb128 0x1a
	.4byte	.LASF102
	.byte	0x1
	.2byte	0x27a
	.byte	0x49
	.4byte	0x98
	.4byte	.LLST12
	.4byte	.LVUS12
	.uleb128 0x19
	.4byte	.LASF84
	.byte	0x1
	.2byte	0x27c
	.byte	0x15
	.4byte	0x556
	.4byte	.LLST13
	.4byte	.LVUS13
	.byte	0
	.uleb128 0x18
	.byte	0x1
	.4byte	.LASF103
	.byte	0x1
	.2byte	0x227
	.byte	0x13
	.byte	0x1
	.4byte	0x556
	.4byte	.LFB86
	.4byte	.LFE86
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x9af
	.uleb128 0x1a
	.4byte	.LASF101
	.byte	0x1
	.2byte	0x227
	.byte	0x39
	.4byte	0x98
	.4byte	.LLST8
	.4byte	.LVUS8
	.uleb128 0x1a
	.4byte	.LASF102
	.byte	0x1
	.2byte	0x227
	.byte	0x48
	.4byte	0x98
	.4byte	.LLST9
	.4byte	.LVUS9
	.uleb128 0x19
	.4byte	.LASF84
	.byte	0x1
	.2byte	0x229
	.byte	0x15
	.4byte	0x556
	.4byte	.LLST10
	.4byte	.LVUS10
	.byte	0
	.uleb128 0x18
	.byte	0x1
	.4byte	.LASF104
	.byte	0x1
	.2byte	0x1da
	.byte	0x13
	.byte	0x1
	.4byte	0x556
	.4byte	.LFB85
	.4byte	.LFE85
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0xa0e
	.uleb128 0x1a
	.4byte	.LASF101
	.byte	0x1
	.2byte	0x1da
	.byte	0x38
	.4byte	0x98
	.4byte	.LLST5
	.4byte	.LVUS5
	.uleb128 0x1a
	.4byte	.LASF102
	.byte	0x1
	.2byte	0x1da
	.byte	0x47
	.4byte	0x98
	.4byte	.LLST6
	.4byte	.LVUS6
	.uleb128 0x19
	.4byte	.LASF84
	.byte	0x1
	.2byte	0x1dc
	.byte	0x15
	.4byte	0x556
	.4byte	.LLST7
	.4byte	.LVUS7
	.byte	0
	.uleb128 0x18
	.byte	0x1
	.4byte	.LASF105
	.byte	0x1
	.2byte	0x187
	.byte	0x13
	.byte	0x1
	.4byte	0x556
	.4byte	.LFB84
	.4byte	.LFE84
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0xa6d
	.uleb128 0x1a
	.4byte	.LASF101
	.byte	0x1
	.2byte	0x187
	.byte	0x37
	.4byte	0x98
	.4byte	.LLST2
	.4byte	.LVUS2
	.uleb128 0x1a
	.4byte	.LASF102
	.byte	0x1
	.2byte	0x187
	.byte	0x46
	.4byte	0x98
	.4byte	.LLST3
	.4byte	.LVUS3
	.uleb128 0x19
	.4byte	.LASF84
	.byte	0x1
	.2byte	0x189
	.byte	0x15
	.4byte	0x556
	.4byte	.LLST4
	.4byte	.LVUS4
	.byte	0
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF106
	.byte	0x1
	.2byte	0x16b
	.byte	0x6
	.byte	0x1
	.4byte	.LFB83
	.4byte	.LFE83
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF107
	.byte	0x1
	.2byte	0x161
	.byte	0x6
	.byte	0x1
	.4byte	.LFB82
	.4byte	.LFE82
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF108
	.byte	0x1
	.2byte	0x156
	.byte	0x6
	.byte	0x1
	.4byte	.LFB81
	.4byte	.LFE81
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF109
	.byte	0x1
	.2byte	0x14c
	.byte	0x6
	.byte	0x1
	.4byte	.LFB80
	.4byte	.LFE80
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF110
	.byte	0x1
	.2byte	0x140
	.byte	0x6
	.byte	0x1
	.4byte	.LFB79
	.4byte	.LFE79
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF111
	.byte	0x1
	.2byte	0x136
	.byte	0x6
	.byte	0x1
	.4byte	.LFB78
	.4byte	.LFE78
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x13
	.byte	0x1
	.4byte	.LASF112
	.byte	0x1
	.2byte	0x12a
	.byte	0x6
	.byte	0x1
	.4byte	.LFB77
	.4byte	.LFE77
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.uleb128 0x16
	.byte	0x1
	.4byte	.LASF113
	.byte	0x1
	.2byte	0x11a
	.byte	0x6
	.byte	0x1
	.4byte	.LFB76
	.4byte	.LFE76
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0xb39
	.uleb128 0x17
	.4byte	.LASF114
	.byte	0x1
	.2byte	0x11a
	.byte	0x2f
	.4byte	0x98
	.byte	0x1
	.byte	0x50
	.byte	0
	.uleb128 0x1e
	.byte	0x1
	.4byte	.LASF115
	.byte	0x1
	.byte	0xa3
	.byte	0x13
	.byte	0x1
	.4byte	0x556
	.4byte	.LFB75
	.4byte	.LFE75
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0xb80
	.uleb128 0x1f
	.4byte	.LASF116
	.byte	0x1
	.byte	0xa3
	.byte	0x3c
	.4byte	0x98
	.4byte	.LLST0
	.4byte	.LVUS0
	.uleb128 0x20
	.4byte	.LASF80
	.byte	0x1
	.byte	0xa5
	.byte	0xc
	.4byte	0x98
	.4byte	.LLST1
	.4byte	.LVUS1
	.byte	0
	.uleb128 0x21
	.byte	0x1
	.4byte	.LASF121
	.byte	0x1
	.byte	0x72
	.byte	0xa
	.byte	0x1
	.4byte	0x98
	.4byte	.LFB74
	.4byte	.LFE74
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
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
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
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
	.uleb128 0x8
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
	.uleb128 0x9
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
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
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
	.uleb128 0xd
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
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x13
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
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x18
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
	.uleb128 0x19
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
	.uleb128 0x1a
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
	.uleb128 0x1b
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1e
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
	.uleb128 0x1f
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
	.uleb128 0x20
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
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LLST20:
	.4byte	.LFB108
	.4byte	.LCFI2
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI2
	.4byte	.LFE108
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LVUS19:
	.uleb128 .LVU427
	.uleb128 .LVU437
.LLST19:
	.4byte	.LVL122
	.4byte	.LVL124
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LVUS17:
	.uleb128 0
	.uleb128 .LVU336
	.uleb128 .LVU336
	.uleb128 .LVU337
	.uleb128 .LVU337
	.uleb128 .LVU338
	.uleb128 .LVU338
	.uleb128 .LVU339
	.uleb128 .LVU339
	.uleb128 .LVU361
	.uleb128 .LVU361
	.uleb128 .LVU362
	.uleb128 .LVU362
	.uleb128 .LVU363
	.uleb128 .LVU363
	.uleb128 .LVU364
	.uleb128 .LVU364
	.uleb128 .LVU385
	.uleb128 .LVU385
	.uleb128 .LVU386
	.uleb128 .LVU386
	.uleb128 .LVU407
	.uleb128 .LVU407
	.uleb128 .LVU408
	.uleb128 .LVU408
	.uleb128 .LVU409
	.uleb128 .LVU409
	.uleb128 .LVU410
	.uleb128 .LVU410
	.uleb128 .LVU411
	.uleb128 .LVU411
	.uleb128 .LVU412
	.uleb128 .LVU412
	.uleb128 .LVU413
	.uleb128 .LVU413
	.uleb128 .LVU414
	.uleb128 .LVU414
	.uleb128 .LVU415
	.uleb128 .LVU415
	.uleb128 0
.LLST17:
	.4byte	.LVL102
	.4byte	.LVL103
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL103
	.4byte	.LVL104
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL104
	.4byte	.LVL105
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL105
	.4byte	.LVL106
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL106
	.4byte	.LVL107
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL107
	.4byte	.LVL108
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL108
	.4byte	.LVL109
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL109
	.4byte	.LVL110
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL110
	.4byte	.LVL111
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL111
	.4byte	.LVL112
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL112
	.4byte	.LVL113
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL113
	.4byte	.LVL114
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL114
	.4byte	.LVL115
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL115
	.4byte	.LVL116
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL116
	.4byte	.LVL117
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL117
	.4byte	.LVL118
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL118
	.4byte	.LVL119
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL119
	.4byte	.LVL120
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL120
	.4byte	.LVL121
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL121
	.4byte	.LFE101
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS18:
	.uleb128 .LVU310
	.uleb128 .LVU415
	.uleb128 .LVU415
	.uleb128 0
.LLST18:
	.4byte	.LVL102
	.4byte	.LVL121
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL121
	.4byte	.LFE101
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LVUS14:
	.uleb128 0
	.uleb128 .LVU273
	.uleb128 .LVU273
	.uleb128 .LVU274
	.uleb128 .LVU274
	.uleb128 .LVU275
	.uleb128 .LVU275
	.uleb128 0
.LLST14:
	.4byte	.LVL96
	.4byte	.LVL97
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL97
	.4byte	.LVL98
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL98
	.4byte	.LVL99
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL99
	.4byte	.LFE92
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST16:
	.4byte	.LFB91
	.4byte	.LCFI1
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI1
	.4byte	.LFE91
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LLST15:
	.4byte	.LFB90
	.4byte	.LCFI0
	.2byte	0x2
	.byte	0x7d
	.sleb128 0
	.4byte	.LCFI0
	.4byte	.LFE90
	.2byte	0x2
	.byte	0x7d
	.sleb128 8
	.4byte	0
	.4byte	0
.LVUS11:
	.uleb128 0
	.uleb128 .LVU224
	.uleb128 .LVU224
	.uleb128 .LVU225
	.uleb128 .LVU225
	.uleb128 .LVU229
	.uleb128 .LVU229
	.uleb128 .LVU230
	.uleb128 .LVU230
	.uleb128 .LVU233
	.uleb128 .LVU233
	.uleb128 .LVU234
	.uleb128 .LVU234
	.uleb128 .LVU237
	.uleb128 .LVU237
	.uleb128 .LVU238
	.uleb128 .LVU238
	.uleb128 .LVU241
	.uleb128 .LVU241
	.uleb128 .LVU242
	.uleb128 .LVU242
	.uleb128 .LVU245
	.uleb128 .LVU245
	.uleb128 .LVU246
	.uleb128 .LVU246
	.uleb128 .LVU249
	.uleb128 .LVU249
	.uleb128 .LVU250
	.uleb128 .LVU250
	.uleb128 .LVU254
	.uleb128 .LVU254
	.uleb128 .LVU255
	.uleb128 .LVU255
	.uleb128 .LVU256
	.uleb128 .LVU256
	.uleb128 0
.LLST11:
	.4byte	.LVL75
	.4byte	.LVL77
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL77
	.4byte	.LVL78
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL78
	.4byte	.LVL80
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL80
	.4byte	.LVL81
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL81
	.4byte	.LVL82
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL82
	.4byte	.LVL83
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL83
	.4byte	.LVL84
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL84
	.4byte	.LVL85
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL85
	.4byte	.LVL86
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL86
	.4byte	.LVL87
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL87
	.4byte	.LVL88
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL88
	.4byte	.LVL89
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL89
	.4byte	.LVL90
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL90
	.4byte	.LVL91
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL91
	.4byte	.LVL93
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL93
	.4byte	.LVL94
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL94
	.4byte	.LVL95
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL95
	.4byte	.LFE87
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS12:
	.uleb128 0
	.uleb128 .LVU221
	.uleb128 .LVU221
	.uleb128 .LVU225
	.uleb128 .LVU225
	.uleb128 .LVU226
	.uleb128 .LVU226
	.uleb128 .LVU230
	.uleb128 .LVU230
	.uleb128 .LVU251
	.uleb128 .LVU251
	.uleb128 .LVU255
	.uleb128 .LVU255
	.uleb128 0
.LLST12:
	.4byte	.LVL75
	.4byte	.LVL76
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL76
	.4byte	.LVL78
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL78
	.4byte	.LVL79
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL79
	.4byte	.LVL81
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL81
	.4byte	.LVL92
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL92
	.4byte	.LVL94
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL94
	.4byte	.LFE87
	.2byte	0x1
	.byte	0x51
	.4byte	0
	.4byte	0
.LVUS13:
	.uleb128 .LVU217
	.uleb128 .LVU256
	.uleb128 .LVU256
	.uleb128 0
.LLST13:
	.4byte	.LVL75
	.4byte	.LVL95
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL95
	.4byte	.LFE87
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LVUS8:
	.uleb128 0
	.uleb128 .LVU169
	.uleb128 .LVU169
	.uleb128 .LVU175
	.uleb128 .LVU175
	.uleb128 .LVU176
	.uleb128 .LVU176
	.uleb128 .LVU181
	.uleb128 .LVU181
	.uleb128 .LVU185
	.uleb128 .LVU185
	.uleb128 .LVU186
	.uleb128 .LVU186
	.uleb128 .LVU190
	.uleb128 .LVU190
	.uleb128 .LVU191
	.uleb128 .LVU191
	.uleb128 .LVU195
	.uleb128 .LVU195
	.uleb128 .LVU196
	.uleb128 .LVU196
	.uleb128 .LVU200
	.uleb128 .LVU200
	.uleb128 .LVU201
	.uleb128 .LVU201
	.uleb128 .LVU205
	.uleb128 .LVU205
	.uleb128 .LVU206
	.uleb128 .LVU206
	.uleb128 .LVU211
	.uleb128 .LVU211
	.uleb128 .LVU212
	.uleb128 .LVU212
	.uleb128 .LVU213
	.uleb128 .LVU213
	.uleb128 0
.LLST8:
	.4byte	.LVL55
	.4byte	.LVL56
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL56
	.4byte	.LVL58
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL58
	.4byte	.LVL59
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL59
	.4byte	.LVL60
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL60
	.4byte	.LVL61
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL61
	.4byte	.LVL62
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL62
	.4byte	.LVL63
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL63
	.4byte	.LVL64
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL64
	.4byte	.LVL65
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL65
	.4byte	.LVL66
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL66
	.4byte	.LVL67
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL67
	.4byte	.LVL68
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL68
	.4byte	.LVL69
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL69
	.4byte	.LVL70
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL70
	.4byte	.LVL72
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL72
	.4byte	.LVL73
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL73
	.4byte	.LVL74
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL74
	.4byte	.LFE86
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS9:
	.uleb128 0
	.uleb128 .LVU171
	.uleb128 .LVU171
	.uleb128 .LVU175
	.uleb128 .LVU175
	.uleb128 .LVU207
	.uleb128 .LVU207
	.uleb128 .LVU212
	.uleb128 .LVU212
	.uleb128 0
.LLST9:
	.4byte	.LVL55
	.4byte	.LVL57
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL57
	.4byte	.LVL58
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL58
	.4byte	.LVL71
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL71
	.4byte	.LVL73
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL73
	.4byte	.LFE86
	.2byte	0x1
	.byte	0x51
	.4byte	0
	.4byte	0
.LVUS10:
	.uleb128 .LVU165
	.uleb128 .LVU213
	.uleb128 .LVU213
	.uleb128 0
.LLST10:
	.4byte	.LVL55
	.4byte	.LVL74
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL74
	.4byte	.LFE86
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LVUS5:
	.uleb128 0
	.uleb128 .LVU130
	.uleb128 .LVU130
	.uleb128 .LVU131
	.uleb128 .LVU131
	.uleb128 .LVU134
	.uleb128 .LVU134
	.uleb128 .LVU135
	.uleb128 .LVU135
	.uleb128 .LVU138
	.uleb128 .LVU138
	.uleb128 .LVU139
	.uleb128 .LVU139
	.uleb128 .LVU142
	.uleb128 .LVU142
	.uleb128 .LVU143
	.uleb128 .LVU143
	.uleb128 .LVU146
	.uleb128 .LVU146
	.uleb128 .LVU147
	.uleb128 .LVU147
	.uleb128 .LVU150
	.uleb128 .LVU150
	.uleb128 .LVU151
	.uleb128 .LVU151
	.uleb128 .LVU154
	.uleb128 .LVU154
	.uleb128 .LVU155
	.uleb128 .LVU155
	.uleb128 .LVU159
	.uleb128 .LVU159
	.uleb128 .LVU160
	.uleb128 .LVU160
	.uleb128 .LVU161
	.uleb128 .LVU161
	.uleb128 0
.LLST5:
	.4byte	.LVL35
	.4byte	.LVL37
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL37
	.4byte	.LVL38
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL38
	.4byte	.LVL39
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL39
	.4byte	.LVL40
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL40
	.4byte	.LVL41
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL41
	.4byte	.LVL42
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL42
	.4byte	.LVL43
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL43
	.4byte	.LVL44
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL44
	.4byte	.LVL45
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL45
	.4byte	.LVL46
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL46
	.4byte	.LVL47
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL47
	.4byte	.LVL48
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL48
	.4byte	.LVL49
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL49
	.4byte	.LVL50
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL50
	.4byte	.LVL52
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL52
	.4byte	.LVL53
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL53
	.4byte	.LVL54
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL54
	.4byte	.LFE85
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS6:
	.uleb128 0
	.uleb128 .LVU127
	.uleb128 .LVU127
	.uleb128 .LVU131
	.uleb128 .LVU131
	.uleb128 .LVU156
	.uleb128 .LVU156
	.uleb128 .LVU160
	.uleb128 .LVU160
	.uleb128 0
.LLST6:
	.4byte	.LVL35
	.4byte	.LVL36
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL36
	.4byte	.LVL38
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL38
	.4byte	.LVL51
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL51
	.4byte	.LVL53
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL53
	.4byte	.LFE85
	.2byte	0x1
	.byte	0x51
	.4byte	0
	.4byte	0
.LVUS7:
	.uleb128 .LVU123
	.uleb128 .LVU161
	.uleb128 .LVU161
	.uleb128 0
.LLST7:
	.4byte	.LVL35
	.4byte	.LVL54
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL54
	.4byte	.LFE85
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LVUS2:
	.uleb128 0
	.uleb128 .LVU75
	.uleb128 .LVU75
	.uleb128 .LVU81
	.uleb128 .LVU81
	.uleb128 .LVU86
	.uleb128 .LVU86
	.uleb128 .LVU87
	.uleb128 .LVU87
	.uleb128 .LVU91
	.uleb128 .LVU91
	.uleb128 .LVU92
	.uleb128 .LVU92
	.uleb128 .LVU96
	.uleb128 .LVU96
	.uleb128 .LVU97
	.uleb128 .LVU97
	.uleb128 .LVU101
	.uleb128 .LVU101
	.uleb128 .LVU102
	.uleb128 .LVU102
	.uleb128 .LVU106
	.uleb128 .LVU106
	.uleb128 .LVU107
	.uleb128 .LVU107
	.uleb128 .LVU111
	.uleb128 .LVU111
	.uleb128 .LVU112
	.uleb128 .LVU112
	.uleb128 .LVU117
	.uleb128 .LVU117
	.uleb128 .LVU118
	.uleb128 .LVU118
	.uleb128 .LVU119
	.uleb128 .LVU119
	.uleb128 0
.LLST2:
	.4byte	.LVL14
	.4byte	.LVL15
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL15
	.4byte	.LVL17
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL17
	.4byte	.LVL19
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL19
	.4byte	.LVL20
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL20
	.4byte	.LVL21
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL21
	.4byte	.LVL22
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL22
	.4byte	.LVL23
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL23
	.4byte	.LVL24
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL24
	.4byte	.LVL25
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL25
	.4byte	.LVL26
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL26
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
	.4byte	.LVL32
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL32
	.4byte	.LVL33
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL33
	.4byte	.LVL34
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL34
	.4byte	.LFE84
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	0
	.4byte	0
.LVUS3:
	.uleb128 0
	.uleb128 .LVU77
	.uleb128 .LVU77
	.uleb128 .LVU81
	.uleb128 .LVU81
	.uleb128 .LVU83
	.uleb128 .LVU83
	.uleb128 .LVU87
	.uleb128 .LVU87
	.uleb128 .LVU113
	.uleb128 .LVU113
	.uleb128 .LVU118
	.uleb128 .LVU118
	.uleb128 0
.LLST3:
	.4byte	.LVL14
	.4byte	.LVL16
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL16
	.4byte	.LVL17
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL17
	.4byte	.LVL18
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL18
	.4byte	.LVL20
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL20
	.4byte	.LVL31
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL31
	.4byte	.LVL33
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x51
	.byte	0x9f
	.4byte	.LVL33
	.4byte	.LFE84
	.2byte	0x1
	.byte	0x51
	.4byte	0
	.4byte	0
.LVUS4:
	.uleb128 .LVU71
	.uleb128 .LVU119
	.uleb128 .LVU119
	.uleb128 0
.LLST4:
	.4byte	.LVL14
	.4byte	.LVL34
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL34
	.4byte	.LFE84
	.2byte	0x1
	.byte	0x50
	.4byte	0
	.4byte	0
.LVUS0:
	.uleb128 0
	.uleb128 .LVU14
	.uleb128 .LVU14
	.uleb128 .LVU15
	.uleb128 .LVU15
	.uleb128 .LVU36
	.uleb128 .LVU36
	.uleb128 .LVU37
	.uleb128 .LVU37
	.uleb128 .LVU38
	.uleb128 .LVU38
	.uleb128 .LVU39
	.uleb128 .LVU39
	.uleb128 .LVU40
	.uleb128 .LVU40
	.uleb128 .LVU41
	.uleb128 .LVU41
	.uleb128 .LVU42
	.uleb128 .LVU42
	.uleb128 0
.LLST0:
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
	.4byte	.LVL6
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL6
	.4byte	.LVL7
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL7
	.4byte	.LVL8
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL8
	.4byte	.LVL9
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
	.4byte	.LVL9
	.4byte	.LVL10
	.2byte	0x1
	.byte	0x50
	.4byte	.LVL10
	.4byte	.LVL11
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x50
	.byte	0x9f
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
.LVUS1:
	.uleb128 .LVU23
	.uleb128 .LVU33
.LLST1:
	.4byte	.LVL3
	.4byte	.LVL5
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x14c
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
	.4byte	.LFB78
	.4byte	.LFE78-.LFB78
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
	.4byte	.LFB92
	.4byte	.LFE92-.LFB92
	.4byte	.LFB90
	.4byte	.LFE90-.LFB90
	.4byte	.LFB91
	.4byte	.LFE91-.LFB91
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
	.4byte	.LFB109
	.4byte	.LFE109-.LFB109
	.4byte	.LFB110
	.4byte	.LFE110-.LFB110
	.4byte	.LFB111
	.4byte	.LFE111-.LFB111
	.4byte	.LFB112
	.4byte	.LFE112-.LFB112
	.4byte	.LFB108
	.4byte	.LFE108-.LFB108
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
	.4byte	.LFB78
	.4byte	.LFE78
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
	.4byte	.LFB92
	.4byte	.LFE92
	.4byte	.LFB90
	.4byte	.LFE90
	.4byte	.LFB91
	.4byte	.LFE91
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
	.4byte	.LFB109
	.4byte	.LFE109
	.4byte	.LFB110
	.4byte	.LFE110
	.4byte	.LFB111
	.4byte	.LFE111
	.4byte	.LFB112
	.4byte	.LFE112
	.4byte	.LFB108
	.4byte	.LFE108
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF118:
	.ascii	"../Drivers/STM32L4xx_HAL_Driver/Src/stm32l4xx_hal_p"
	.ascii	"wr_ex.c\000"
.LASF44:
	.ascii	"PDCRA\000"
.LASF46:
	.ascii	"PDCRB\000"
.LASF48:
	.ascii	"PDCRC\000"
.LASF50:
	.ascii	"PDCRD\000"
.LASF52:
	.ascii	"PDCRE\000"
.LASF54:
	.ascii	"PDCRF\000"
.LASF5:
	.ascii	"__uint8_t\000"
.LASF58:
	.ascii	"PDCRH\000"
.LASF63:
	.ascii	"HAL_BUSY\000"
.LASF32:
	.ascii	"FTSR1\000"
.LASF39:
	.ascii	"FTSR2\000"
.LASF107:
	.ascii	"HAL_PWREx_EnableInternalWakeUpLine\000"
.LASF81:
	.ascii	"HAL_PWREx_EnableLowPowerRunMode\000"
.LASF9:
	.ascii	"long long unsigned int\000"
.LASF103:
	.ascii	"HAL_PWREx_EnableGPIOPullDown\000"
.LASF91:
	.ascii	"HAL_PWREx_DisablePVM1\000"
.LASF87:
	.ascii	"HAL_PWREx_DisablePVM3\000"
.LASF85:
	.ascii	"HAL_PWREx_DisablePVM4\000"
.LASF13:
	.ascii	"CPUID\000"
.LASF72:
	.ascii	"HAL_PWREx_PVM1Callback\000"
.LASF33:
	.ascii	"SWIER1\000"
.LASF40:
	.ascii	"SWIER2\000"
.LASF106:
	.ascii	"HAL_PWREx_DisableInternalWakeUpLine\000"
.LASF25:
	.ascii	"ISAR\000"
.LASF8:
	.ascii	"long long int\000"
.LASF0:
	.ascii	"signed char\000"
.LASF104:
	.ascii	"HAL_PWREx_DisableGPIOPullUp\000"
.LASF43:
	.ascii	"PUCRA\000"
.LASF45:
	.ascii	"PUCRB\000"
.LASF47:
	.ascii	"PUCRC\000"
.LASF49:
	.ascii	"PUCRD\000"
.LASF51:
	.ascii	"PUCRE\000"
.LASF53:
	.ascii	"PUCRF\000"
.LASF55:
	.ascii	"PUCRG\000"
.LASF57:
	.ascii	"PUCRH\000"
.LASF4:
	.ascii	"long int\000"
.LASF98:
	.ascii	"HAL_PWREx_DisablePullUpPullDownConfig\000"
.LASF56:
	.ascii	"PDCRG\000"
.LASF22:
	.ascii	"BFAR\000"
.LASF71:
	.ascii	"HAL_PWREx_PVM2Callback\000"
.LASF6:
	.ascii	"__uint32_t\000"
.LASF67:
	.ascii	"Mode\000"
.LASF119:
	.ascii	"/home/emanuele/Desktop/CROSSCON/Repo/baremetal-tee/"
	.ascii	"MPU-version/apps/keylogger/Debug\000"
.LASF28:
	.ascii	"SCB_Type\000"
.LASF97:
	.ascii	"HAL_PWREx_EnableSRAM2ContentRetention\000"
.LASF64:
	.ascii	"HAL_TIMEOUT\000"
.LASF92:
	.ascii	"HAL_PWREx_EnablePVM1\000"
.LASF90:
	.ascii	"HAL_PWREx_EnablePVM2\000"
.LASF88:
	.ascii	"HAL_PWREx_EnablePVM3\000"
.LASF86:
	.ascii	"HAL_PWREx_EnablePVM4\000"
.LASF79:
	.ascii	"SystemCoreClock\000"
.LASF7:
	.ascii	"long unsigned int\000"
.LASF66:
	.ascii	"PVMType\000"
.LASF95:
	.ascii	"SRAM2Size\000"
.LASF113:
	.ascii	"HAL_PWREx_EnableBatteryCharging\000"
.LASF61:
	.ascii	"HAL_OK\000"
.LASF15:
	.ascii	"VTOR\000"
.LASF109:
	.ascii	"HAL_PWREx_EnableVddIO2\000"
.LASF108:
	.ascii	"HAL_PWREx_DisableVddIO2\000"
.LASF29:
	.ascii	"IMR1\000"
.LASF36:
	.ascii	"IMR2\000"
.LASF14:
	.ascii	"ICSR\000"
.LASF16:
	.ascii	"AIRCR\000"
.LASF20:
	.ascii	"DFSR\000"
.LASF70:
	.ascii	"HAL_PWREx_PVM3Callback\000"
.LASF21:
	.ascii	"MMFAR\000"
.LASF80:
	.ascii	"wait_loop_index\000"
.LASF65:
	.ascii	"HAL_StatusTypeDef\000"
.LASF73:
	.ascii	"HAL_PWREx_EnterSHUTDOWNMode\000"
.LASF24:
	.ascii	"MMFR\000"
.LASF120:
	.ascii	"HAL_PWR_PVDCallback\000"
.LASF75:
	.ascii	"HAL_PWREx_EnterSTOP2Mode\000"
.LASF18:
	.ascii	"CFSR\000"
.LASF76:
	.ascii	"HAL_PWREx_EnterSTOP1Mode\000"
.LASF69:
	.ascii	"HAL_PWREx_PVM4Callback\000"
.LASF115:
	.ascii	"HAL_PWREx_ControlVoltageScaling\000"
.LASF96:
	.ascii	"HAL_PWREx_DisableSRAM2ContentRetention\000"
.LASF100:
	.ascii	"HAL_PWREx_DisableGPIOPullDown\000"
.LASF26:
	.ascii	"RESERVED0\000"
.LASF34:
	.ascii	"RESERVED1\000"
.LASF35:
	.ascii	"RESERVED2\000"
.LASF31:
	.ascii	"RTSR1\000"
.LASF38:
	.ascii	"RTSR2\000"
.LASF82:
	.ascii	"HAL_PWREx_DisableLowPowerRunMode\000"
.LASF89:
	.ascii	"HAL_PWREx_DisablePVM2\000"
.LASF83:
	.ascii	"HAL_PWREx_ConfigPVM\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF17:
	.ascii	"SHCSR\000"
.LASF2:
	.ascii	"short int\000"
.LASF42:
	.ascii	"RESERVED\000"
.LASF12:
	.ascii	"uint32_t\000"
.LASF23:
	.ascii	"AFSR\000"
.LASF62:
	.ascii	"HAL_ERROR\000"
.LASF105:
	.ascii	"HAL_PWREx_EnableGPIOPullUp\000"
.LASF60:
	.ascii	"long double\000"
.LASF94:
	.ascii	"sConfigPVM\000"
.LASF111:
	.ascii	"HAL_PWREx_EnableVddUSB\000"
.LASF10:
	.ascii	"unsigned int\000"
.LASF110:
	.ascii	"HAL_PWREx_DisableVddUSB\000"
.LASF117:
	.ascii	"GNU C17 12.3.1 20230626 -mcpu=cortex-m3 -mthumb -mf"
	.ascii	"loat-abi=soft -march=armv7-m -g -gdwarf-2 -Og -fdat"
	.ascii	"a-sections -ffunction-sections\000"
.LASF68:
	.ascii	"PWR_PVMTypeDef\000"
.LASF102:
	.ascii	"GPIONumber\000"
.LASF59:
	.ascii	"PWR_TypeDef\000"
.LASF3:
	.ascii	"short unsigned int\000"
.LASF74:
	.ascii	"HAL_PWREx_PVD_PVM_IRQHandler\000"
.LASF30:
	.ascii	"EMR1\000"
.LASF37:
	.ascii	"EMR2\000"
.LASF84:
	.ascii	"status\000"
.LASF11:
	.ascii	"uint8_t\000"
.LASF77:
	.ascii	"STOPEntry\000"
.LASF78:
	.ascii	"HAL_PWREx_EnterSTOP0Mode\000"
.LASF112:
	.ascii	"HAL_PWREx_DisableBatteryCharging\000"
.LASF121:
	.ascii	"HAL_PWREx_GetVoltageRange\000"
.LASF93:
	.ascii	"HAL_PWREx_SetSRAM2ContentRetention\000"
.LASF114:
	.ascii	"ResistorSelection\000"
.LASF99:
	.ascii	"HAL_PWREx_EnablePullUpPullDownConfig\000"
.LASF101:
	.ascii	"GPIO\000"
.LASF41:
	.ascii	"EXTI_TypeDef\000"
.LASF27:
	.ascii	"CPACR\000"
.LASF19:
	.ascii	"HFSR\000"
.LASF116:
	.ascii	"VoltageScaling\000"
	.ident	"GCC: (GNU Tools for STM32 12.3.rel1.20240612-1315) 12.3.1 20230626"
