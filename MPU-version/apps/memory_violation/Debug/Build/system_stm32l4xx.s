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
	.file	"system_stm32l4xx.c"
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.file 1 "../Core/Src/system_stm32l4xx.c"
	.section	.text.SystemInit,"ax",%progbits
	.align	1
	.global	SystemInit
	.syntax unified
	.thumb
	.thumb_func
	.type	SystemInit, %function
SystemInit:
.LFB74:
	.loc 1 198 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 208 1 view .LVU1
	bx	lr
	.cfi_endproc
.LFE74:
	.size	SystemInit, .-SystemInit
	.section	.text.SystemCoreClockUpdate,"ax",%progbits
	.align	1
	.global	SystemCoreClockUpdate
	.syntax unified
	.thumb
	.thumb_func
	.type	SystemCoreClockUpdate, %function
SystemCoreClockUpdate:
.LFB75:
	.loc 1 252 1 view -0
	.cfi_startproc
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	.loc 1 253 3 view .LVU3
	.loc 1 256 3 view .LVU4
	.loc 1 256 11 is_stmt 0 view .LVU5
	ldr	r3, .L17
	ldr	r3, [r3]
	.loc 1 256 6 view .LVU6
	tst	r3, #8
	bne	.L3
	.loc 1 258 5 is_stmt 1 view .LVU7
	.loc 1 258 20 is_stmt 0 view .LVU8
	ldr	r3, .L17
	ldr	r3, [r3, #148]
	.loc 1 258 14 view .LVU9
	ubfx	r3, r3, #8, #4
.LVL0:
.L4:
	.loc 1 265 3 is_stmt 1 view .LVU10
	.loc 1 265 12 is_stmt 0 view .LVU11
	ldr	r2, .L17+4
	ldr	r2, [r2, r3, lsl #2]
.LVL1:
	.loc 1 268 3 is_stmt 1 view .LVU12
	.loc 1 268 14 is_stmt 0 view .LVU13
	ldr	r3, .L17
	ldr	r3, [r3, #8]
	.loc 1 268 21 view .LVU14
	and	r3, r3, #12
	.loc 1 268 3 view .LVU15
	cmp	r3, #12
	bhi	.L5
	tbb	[pc, r3]
.L7:
	.byte	(.L10-.L7)/2
	.byte	(.L5-.L7)/2
	.byte	(.L5-.L7)/2
	.byte	(.L5-.L7)/2
	.byte	(.L9-.L7)/2
	.byte	(.L5-.L7)/2
	.byte	(.L5-.L7)/2
	.byte	(.L5-.L7)/2
	.byte	(.L8-.L7)/2
	.byte	(.L5-.L7)/2
	.byte	(.L5-.L7)/2
	.byte	(.L5-.L7)/2
	.byte	(.L6-.L7)/2
.LVL2:
	.p2align 1
.L3:
	.loc 1 262 5 is_stmt 1 view .LVU16
	.loc 1 262 20 is_stmt 0 view .LVU17
	ldr	r3, .L17
	ldr	r3, [r3]
	.loc 1 262 14 view .LVU18
	ubfx	r3, r3, #4, #4
.LVL3:
	.loc 1 262 14 view .LVU19
	b	.L4
.LVL4:
.L10:
	.loc 1 271 7 is_stmt 1 view .LVU20
	.loc 1 271 23 is_stmt 0 view .LVU21
	ldr	r3, .L17+8
	str	r2, [r3]
	.loc 1 272 7 is_stmt 1 view .LVU22
	b	.L11
.L9:
	.loc 1 275 7 view .LVU23
	.loc 1 275 23 is_stmt 0 view .LVU24
	ldr	r3, .L17+8
	ldr	r2, .L17+12
.LVL5:
	.loc 1 275 23 view .LVU25
	str	r2, [r3]
	.loc 1 276 7 is_stmt 1 view .LVU26
	b	.L11
.LVL6:
.L8:
	.loc 1 279 7 view .LVU27
	.loc 1 279 23 is_stmt 0 view .LVU28
	ldr	r3, .L17+8
	ldr	r2, .L17+16
.LVL7:
	.loc 1 279 23 view .LVU29
	str	r2, [r3]
	.loc 1 280 7 is_stmt 1 view .LVU30
	b	.L11
.LVL8:
.L6:
	.loc 1 286 7 view .LVU31
	.loc 1 286 23 is_stmt 0 view .LVU32
	ldr	r3, .L17
	ldr	r1, [r3, #12]
	.loc 1 286 17 view .LVU33
	and	r1, r1, #3
.LVL9:
	.loc 1 287 7 is_stmt 1 view .LVU34
	.loc 1 287 19 is_stmt 0 view .LVU35
	ldr	r3, [r3, #12]
	.loc 1 287 49 view .LVU36
	ubfx	r3, r3, #4, #3
	.loc 1 287 12 view .LVU37
	adds	r3, r3, #1
.LVL10:
	.loc 1 289 7 is_stmt 1 view .LVU38
	cmp	r1, #2
	beq	.L12
	cmp	r1, #3
	beq	.L13
	.loc 1 300 11 view .LVU39
	.loc 1 300 18 is_stmt 0 view .LVU40
	udiv	r2, r2, r3
.LVL11:
	.loc 1 301 11 is_stmt 1 view .LVU41
	b	.L15
.LVL12:
.L12:
	.loc 1 292 11 view .LVU42
	.loc 1 292 18 is_stmt 0 view .LVU43
	ldr	r2, .L17+12
.LVL13:
	.loc 1 292 18 view .LVU44
	udiv	r2, r2, r3
.LVL14:
	.loc 1 293 11 is_stmt 1 view .LVU45
.L15:
	.loc 1 303 7 view .LVU46
	.loc 1 303 30 is_stmt 0 view .LVU47
	ldr	r1, .L17
.LVL15:
	.loc 1 303 30 view .LVU48
	ldr	r3, [r1, #12]
.LVL16:
	.loc 1 303 60 view .LVU49
	ubfx	r3, r3, #8, #7
	.loc 1 303 14 view .LVU50
	mul	r3, r2, r3
.LVL17:
	.loc 1 304 7 is_stmt 1 view .LVU51
	.loc 1 304 20 is_stmt 0 view .LVU52
	ldr	r2, [r1, #12]
	.loc 1 304 50 view .LVU53
	ubfx	r2, r2, #25, #2
	.loc 1 304 58 view .LVU54
	adds	r2, r2, #1
	.loc 1 304 12 view .LVU55
	lsls	r2, r2, #1
.LVL18:
	.loc 1 305 7 is_stmt 1 view .LVU56
	.loc 1 305 31 is_stmt 0 view .LVU57
	udiv	r3, r3, r2
.LVL19:
	.loc 1 305 23 view .LVU58
	ldr	r2, .L17+8
.LVL20:
	.loc 1 305 23 view .LVU59
	str	r3, [r2]
	.loc 1 306 7 is_stmt 1 view .LVU60
.LVL21:
.L11:
	.loc 1 314 3 view .LVU61
	.loc 1 314 28 is_stmt 0 view .LVU62
	ldr	r3, .L17
	ldr	r3, [r3, #8]
	.loc 1 314 52 view .LVU63
	ubfx	r3, r3, #4, #4
	.loc 1 314 22 view .LVU64
	ldr	r2, .L17+20
	ldrb	r1, [r2, r3]	@ zero_extendqisi2
.LVL22:
	.loc 1 316 3 is_stmt 1 view .LVU65
	.loc 1 316 19 is_stmt 0 view .LVU66
	ldr	r2, .L17+8
	ldr	r3, [r2]
	lsrs	r3, r3, r1
	str	r3, [r2]
	.loc 1 317 1 view .LVU67
	bx	lr
.LVL23:
.L13:
	.loc 1 296 11 is_stmt 1 view .LVU68
	.loc 1 296 18 is_stmt 0 view .LVU69
	ldr	r2, .L17+16
.LVL24:
	.loc 1 296 18 view .LVU70
	udiv	r2, r2, r3
.LVL25:
	.loc 1 297 11 is_stmt 1 view .LVU71
	b	.L15
.LVL26:
.L5:
	.loc 1 309 7 view .LVU72
	.loc 1 309 23 is_stmt 0 view .LVU73
	ldr	r3, .L17+8
	str	r2, [r3]
	.loc 1 310 7 is_stmt 1 view .LVU74
	b	.L11
.L18:
	.align	2
.L17:
	.word	1073876992
	.word	MSIRangeTable
	.word	SystemCoreClock
	.word	16000000
	.word	8000000
	.word	AHBPrescTable
	.cfi_endproc
.LFE75:
	.size	SystemCoreClockUpdate, .-SystemCoreClockUpdate
	.global	MSIRangeTable
	.section	.rodata.MSIRangeTable,"a"
	.align	2
	.type	MSIRangeTable, %object
	.size	MSIRangeTable, 48
MSIRangeTable:
	.word	100000
	.word	200000
	.word	400000
	.word	800000
	.word	1000000
	.word	2000000
	.word	4000000
	.word	8000000
	.word	16000000
	.word	24000000
	.word	32000000
	.word	48000000
	.global	APBPrescTable
	.section	.rodata.APBPrescTable,"a"
	.align	2
	.type	APBPrescTable, %object
	.size	APBPrescTable, 8
APBPrescTable:
	.ascii	"\000\000\000\000\001\002\003\004"
	.global	AHBPrescTable
	.section	.rodata.AHBPrescTable,"a"
	.align	2
	.type	AHBPrescTable, %object
	.size	AHBPrescTable, 16
AHBPrescTable:
	.ascii	"\000\000\000\000\000\000\000\000\001\002\003\004\006"
	.ascii	"\007\010\011"
	.global	SystemCoreClock
	.section	.data.SystemCoreClock,"aw"
	.align	2
	.type	SystemCoreClock, %object
	.size	SystemCoreClock, 4
SystemCoreClock:
	.word	4000000
	.text
.Letext0:
	.file 2 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/arm-none-eabi/include/machine/_default_types.h"
	.file 3 "/home/emanuele/st/stm32cubeide_1.15.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.12.3.rel1.linux64_1.0.200.202406132123/tools/arm-none-eabi/include/sys/_stdint.h"
	.file 4 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/system_stm32l4xx.h"
	.file 5 "../Drivers/CMSIS/Device/ST/STM32L4xx/Include/stm32l475xx.h"
	.section	.debug_info,"",%progbits
.Ldebug_info0:
	.4byte	0x487
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0xc
	.4byte	.LASF61
	.4byte	.LASF62
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
	.uleb128 0x6
	.4byte	0x98
	.uleb128 0x5
	.4byte	0x98
	.uleb128 0x7
	.4byte	.LASF13
	.byte	0x4
	.byte	0x39
	.byte	0x11
	.4byte	0x98
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.4byte	0x93
	.4byte	0xcc
	.uleb128 0x9
	.4byte	0x80
	.byte	0xf
	.byte	0
	.uleb128 0x5
	.4byte	0xbc
	.uleb128 0x7
	.4byte	.LASF14
	.byte	0x4
	.byte	0x3b
	.byte	0x17
	.4byte	0xcc
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.4byte	0x93
	.4byte	0xef
	.uleb128 0x9
	.4byte	0x80
	.byte	0x7
	.byte	0
	.uleb128 0x5
	.4byte	0xdf
	.uleb128 0x7
	.4byte	.LASF15
	.byte	0x4
	.byte	0x3c
	.byte	0x17
	.4byte	0xef
	.byte	0x1
	.byte	0x1
	.uleb128 0x8
	.4byte	0xa9
	.4byte	0x112
	.uleb128 0x9
	.4byte	0x80
	.byte	0xb
	.byte	0
	.uleb128 0x5
	.4byte	0x102
	.uleb128 0x7
	.4byte	.LASF16
	.byte	0x4
	.byte	0x3d
	.byte	0x17
	.4byte	0x112
	.byte	0x1
	.byte	0x1
	.uleb128 0xa
	.byte	0x98
	.byte	0x5
	.2byte	0x29e
	.byte	0x9
	.4byte	0x395
	.uleb128 0xb
	.ascii	"CR\000"
	.byte	0x5
	.2byte	0x2a0
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xc
	.4byte	.LASF17
	.byte	0x5
	.2byte	0x2a1
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xc
	.4byte	.LASF18
	.byte	0x5
	.2byte	0x2a2
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xc
	.4byte	.LASF19
	.byte	0x5
	.2byte	0x2a3
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0xc
	.4byte	.LASF20
	.byte	0x5
	.2byte	0x2a4
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xc
	.4byte	.LASF21
	.byte	0x5
	.2byte	0x2a5
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0xc
	.4byte	.LASF22
	.byte	0x5
	.2byte	0x2a6
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xc
	.4byte	.LASF23
	.byte	0x5
	.2byte	0x2a7
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0xc
	.4byte	.LASF24
	.byte	0x5
	.2byte	0x2a8
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xc
	.4byte	.LASF25
	.byte	0x5
	.2byte	0x2a9
	.byte	0x11
	.4byte	0x98
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0xc
	.4byte	.LASF26
	.byte	0x5
	.2byte	0x2aa
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xc
	.4byte	.LASF27
	.byte	0x5
	.2byte	0x2ab
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0xc
	.4byte	.LASF28
	.byte	0x5
	.2byte	0x2ac
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xc
	.4byte	.LASF29
	.byte	0x5
	.2byte	0x2ad
	.byte	0x11
	.4byte	0x98
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.uleb128 0xc
	.4byte	.LASF30
	.byte	0x5
	.2byte	0x2ae
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0xc
	.4byte	.LASF31
	.byte	0x5
	.2byte	0x2af
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x3c
	.uleb128 0xc
	.4byte	.LASF32
	.byte	0x5
	.2byte	0x2b0
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0xc
	.4byte	.LASF33
	.byte	0x5
	.2byte	0x2b1
	.byte	0x11
	.4byte	0x98
	.byte	0x2
	.byte	0x23
	.uleb128 0x44
	.uleb128 0xc
	.4byte	.LASF34
	.byte	0x5
	.2byte	0x2b2
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0xc
	.4byte	.LASF35
	.byte	0x5
	.2byte	0x2b3
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x4c
	.uleb128 0xc
	.4byte	.LASF36
	.byte	0x5
	.2byte	0x2b4
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0xc
	.4byte	.LASF37
	.byte	0x5
	.2byte	0x2b5
	.byte	0x11
	.4byte	0x98
	.byte	0x2
	.byte	0x23
	.uleb128 0x54
	.uleb128 0xc
	.4byte	.LASF38
	.byte	0x5
	.2byte	0x2b6
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x58
	.uleb128 0xc
	.4byte	.LASF39
	.byte	0x5
	.2byte	0x2b7
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x5c
	.uleb128 0xc
	.4byte	.LASF40
	.byte	0x5
	.2byte	0x2b8
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x60
	.uleb128 0xc
	.4byte	.LASF41
	.byte	0x5
	.2byte	0x2b9
	.byte	0x11
	.4byte	0x98
	.byte	0x2
	.byte	0x23
	.uleb128 0x64
	.uleb128 0xc
	.4byte	.LASF42
	.byte	0x5
	.2byte	0x2ba
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x68
	.uleb128 0xc
	.4byte	.LASF43
	.byte	0x5
	.2byte	0x2bb
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x6c
	.uleb128 0xc
	.4byte	.LASF44
	.byte	0x5
	.2byte	0x2bc
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x70
	.uleb128 0xc
	.4byte	.LASF45
	.byte	0x5
	.2byte	0x2bd
	.byte	0x11
	.4byte	0x98
	.byte	0x2
	.byte	0x23
	.uleb128 0x74
	.uleb128 0xc
	.4byte	.LASF46
	.byte	0x5
	.2byte	0x2be
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x78
	.uleb128 0xc
	.4byte	.LASF47
	.byte	0x5
	.2byte	0x2bf
	.byte	0x11
	.4byte	0xa4
	.byte	0x2
	.byte	0x23
	.uleb128 0x7c
	.uleb128 0xc
	.4byte	.LASF48
	.byte	0x5
	.2byte	0x2c0
	.byte	0x11
	.4byte	0xa4
	.byte	0x3
	.byte	0x23
	.uleb128 0x80
	.uleb128 0xc
	.4byte	.LASF49
	.byte	0x5
	.2byte	0x2c1
	.byte	0x11
	.4byte	0x98
	.byte	0x3
	.byte	0x23
	.uleb128 0x84
	.uleb128 0xc
	.4byte	.LASF50
	.byte	0x5
	.2byte	0x2c2
	.byte	0x11
	.4byte	0xa4
	.byte	0x3
	.byte	0x23
	.uleb128 0x88
	.uleb128 0xc
	.4byte	.LASF51
	.byte	0x5
	.2byte	0x2c3
	.byte	0x11
	.4byte	0x98
	.byte	0x3
	.byte	0x23
	.uleb128 0x8c
	.uleb128 0xc
	.4byte	.LASF52
	.byte	0x5
	.2byte	0x2c4
	.byte	0x11
	.4byte	0xa4
	.byte	0x3
	.byte	0x23
	.uleb128 0x90
	.uleb128 0xb
	.ascii	"CSR\000"
	.byte	0x5
	.2byte	0x2c5
	.byte	0x11
	.4byte	0xa4
	.byte	0x3
	.byte	0x23
	.uleb128 0x94
	.byte	0
	.uleb128 0xd
	.4byte	.LASF53
	.byte	0x5
	.2byte	0x2c6
	.byte	0x3
	.4byte	0x125
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF54
	.uleb128 0xe
	.4byte	0xae
	.byte	0x1
	.byte	0xaa
	.byte	0xc
	.byte	0x5
	.byte	0x3
	.4byte	SystemCoreClock
	.uleb128 0xe
	.4byte	0xd1
	.byte	0x1
	.byte	0xac
	.byte	0x12
	.byte	0x5
	.byte	0x3
	.4byte	AHBPrescTable
	.uleb128 0xe
	.4byte	0xf4
	.byte	0x1
	.byte	0xad
	.byte	0x12
	.byte	0x5
	.byte	0x3
	.4byte	APBPrescTable
	.uleb128 0xe
	.4byte	0x117
	.byte	0x1
	.byte	0xae
	.byte	0x12
	.byte	0x5
	.byte	0x3
	.4byte	MSIRangeTable
	.uleb128 0xf
	.byte	0x1
	.4byte	.LASF63
	.byte	0x1
	.byte	0xfb
	.byte	0x6
	.byte	0x1
	.4byte	.LFB75
	.4byte	.LFE75
	.byte	0x2
	.byte	0x7d
	.sleb128 0
	.byte	0x1
	.4byte	0x474
	.uleb128 0x10
	.ascii	"tmp\000"
	.byte	0x1
	.byte	0xfd
	.byte	0xc
	.4byte	0x98
	.4byte	.LLST0
	.4byte	.LVUS0
	.uleb128 0x11
	.4byte	.LASF55
	.byte	0x1
	.byte	0xfd
	.byte	0x11
	.4byte	0x98
	.4byte	.LLST1
	.4byte	.LVUS1
	.uleb128 0x11
	.4byte	.LASF56
	.byte	0x1
	.byte	0xfd
	.byte	0x1b
	.4byte	0x98
	.4byte	.LLST2
	.4byte	.LVUS2
	.uleb128 0x11
	.4byte	.LASF57
	.byte	0x1
	.byte	0xfd
	.byte	0x23
	.4byte	0x98
	.4byte	.LLST3
	.4byte	.LVUS3
	.uleb128 0x11
	.4byte	.LASF58
	.byte	0x1
	.byte	0xfd
	.byte	0x2e
	.4byte	0x98
	.4byte	.LLST4
	.4byte	.LVUS4
	.uleb128 0x11
	.4byte	.LASF59
	.byte	0x1
	.byte	0xfd
	.byte	0x34
	.4byte	0x98
	.4byte	.LLST5
	.4byte	.LVUS5
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.4byte	.LASF64
	.byte	0x1
	.byte	0xc5
	.byte	0x6
	.byte	0x1
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
	.uleb128 0xf
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
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.uleb128 0x11
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
	.byte	0
	.section	.debug_loc,"",%progbits
.Ldebug_loc0:
.LVUS0:
	.uleb128 .LVU65
	.uleb128 .LVU68
.LLST0:
	.4byte	.LVL22
	.4byte	.LVL23
	.2byte	0x1
	.byte	0x51
	.4byte	0
	.4byte	0
.LVUS1:
	.uleb128 .LVU10
	.uleb128 .LVU12
	.uleb128 .LVU12
	.uleb128 .LVU16
	.uleb128 .LVU19
	.uleb128 .LVU20
	.uleb128 .LVU20
	.uleb128 .LVU25
	.uleb128 .LVU27
	.uleb128 .LVU29
	.uleb128 .LVU31
	.uleb128 .LVU41
	.uleb128 .LVU42
	.uleb128 .LVU44
	.uleb128 .LVU68
	.uleb128 .LVU70
	.uleb128 .LVU72
	.uleb128 0
.LLST1:
	.4byte	.LVL0
	.4byte	.LVL1
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL1
	.4byte	.LVL2
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL3
	.4byte	.LVL4
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL4
	.4byte	.LVL5
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL6
	.4byte	.LVL7
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL8
	.4byte	.LVL11
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL12
	.4byte	.LVL13
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL23
	.4byte	.LVL24
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL26
	.4byte	.LFE75
	.2byte	0x1
	.byte	0x52
	.4byte	0
	.4byte	0
.LVUS2:
	.uleb128 .LVU41
	.uleb128 .LVU42
	.uleb128 .LVU45
	.uleb128 .LVU51
	.uleb128 .LVU51
	.uleb128 .LVU58
	.uleb128 .LVU71
	.uleb128 .LVU72
.LLST2:
	.4byte	.LVL11
	.4byte	.LVL12
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL14
	.4byte	.LVL17
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL17
	.4byte	.LVL19
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL25
	.4byte	.LVL26
	.2byte	0x1
	.byte	0x52
	.4byte	0
	.4byte	0
.LVUS3:
	.uleb128 .LVU34
	.uleb128 .LVU48
	.uleb128 .LVU68
	.uleb128 .LVU72
.LLST3:
	.4byte	.LVL9
	.4byte	.LVL15
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL23
	.4byte	.LVL26
	.2byte	0x1
	.byte	0x51
	.4byte	0
	.4byte	0
.LVUS4:
	.uleb128 .LVU38
	.uleb128 .LVU49
	.uleb128 .LVU68
	.uleb128 .LVU72
.LLST4:
	.4byte	.LVL10
	.4byte	.LVL16
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL23
	.4byte	.LVL26
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LVUS5:
	.uleb128 .LVU56
	.uleb128 .LVU59
.LLST5:
	.4byte	.LVL18
	.4byte	.LVL20
	.2byte	0x1
	.byte	0x52
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",%progbits
	.4byte	0x24
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
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",%progbits
.Ldebug_ranges0:
	.4byte	.LFB74
	.4byte	.LFE74
	.4byte	.LFB75
	.4byte	.LFE75
	.4byte	0
	.4byte	0
	.section	.debug_line,"",%progbits
.Ldebug_line0:
	.section	.debug_str,"MS",%progbits,1
.LASF19:
	.ascii	"PLLCFGR\000"
.LASF30:
	.ascii	"APB1RSTR1\000"
.LASF31:
	.ascii	"APB1RSTR2\000"
.LASF35:
	.ascii	"AHB2ENR\000"
.LASF2:
	.ascii	"short int\000"
.LASF55:
	.ascii	"msirange\000"
.LASF52:
	.ascii	"BDCR\000"
.LASF50:
	.ascii	"CCIPR\000"
.LASF6:
	.ascii	"__uint32_t\000"
.LASF24:
	.ascii	"CICR\000"
.LASF26:
	.ascii	"AHB1RSTR\000"
.LASF18:
	.ascii	"CFGR\000"
.LASF64:
	.ascii	"SystemInit\000"
.LASF11:
	.ascii	"uint8_t\000"
.LASF22:
	.ascii	"CIER\000"
.LASF14:
	.ascii	"AHBPrescTable\000"
.LASF36:
	.ascii	"AHB3ENR\000"
.LASF8:
	.ascii	"long long int\000"
.LASF46:
	.ascii	"APB1SMENR1\000"
.LASF47:
	.ascii	"APB1SMENR2\000"
.LASF4:
	.ascii	"long int\000"
.LASF53:
	.ascii	"RCC_TypeDef\000"
.LASF43:
	.ascii	"AHB2SMENR\000"
.LASF32:
	.ascii	"APB2RSTR\000"
.LASF5:
	.ascii	"__uint8_t\000"
.LASF15:
	.ascii	"APBPrescTable\000"
.LASF57:
	.ascii	"pllsource\000"
.LASF58:
	.ascii	"pllm\000"
.LASF54:
	.ascii	"long double\000"
.LASF59:
	.ascii	"pllr\000"
.LASF1:
	.ascii	"unsigned char\000"
.LASF62:
	.ascii	"/home/emanuele/Desktop/Code/MCU-fortifier/apps/memo"
	.ascii	"ry_violation/Debug\000"
.LASF40:
	.ascii	"APB2ENR\000"
.LASF0:
	.ascii	"signed char\000"
.LASF9:
	.ascii	"long long unsigned int\000"
.LASF12:
	.ascii	"uint32_t\000"
.LASF10:
	.ascii	"unsigned int\000"
.LASF27:
	.ascii	"AHB2RSTR\000"
.LASF21:
	.ascii	"PLLSAI2CFGR\000"
.LASF7:
	.ascii	"long unsigned int\000"
.LASF38:
	.ascii	"APB1ENR1\000"
.LASF39:
	.ascii	"APB1ENR2\000"
.LASF3:
	.ascii	"short unsigned int\000"
.LASF17:
	.ascii	"ICSCR\000"
.LASF56:
	.ascii	"pllvco\000"
.LASF48:
	.ascii	"APB2SMENR\000"
.LASF63:
	.ascii	"SystemCoreClockUpdate\000"
.LASF20:
	.ascii	"PLLSAI1CFGR\000"
.LASF13:
	.ascii	"SystemCoreClock\000"
.LASF25:
	.ascii	"RESERVED0\000"
.LASF29:
	.ascii	"RESERVED1\000"
.LASF33:
	.ascii	"RESERVED2\000"
.LASF37:
	.ascii	"RESERVED3\000"
.LASF41:
	.ascii	"RESERVED4\000"
.LASF45:
	.ascii	"RESERVED5\000"
.LASF49:
	.ascii	"RESERVED6\000"
.LASF51:
	.ascii	"RESERVED7\000"
.LASF23:
	.ascii	"CIFR\000"
.LASF34:
	.ascii	"AHB1ENR\000"
.LASF61:
	.ascii	"../Core/Src/system_stm32l4xx.c\000"
.LASF60:
	.ascii	"GNU C17 12.3.1 20230626 -mcpu=cortex-m3 -mthumb -mf"
	.ascii	"loat-abi=soft -march=armv7-m -g -gdwarf-2 -Og -fdat"
	.ascii	"a-sections -ffunction-sections\000"
.LASF44:
	.ascii	"AHB3SMENR\000"
.LASF16:
	.ascii	"MSIRangeTable\000"
.LASF42:
	.ascii	"AHB1SMENR\000"
.LASF28:
	.ascii	"AHB3RSTR\000"
	.ident	"GCC: (GNU Tools for STM32 12.3.rel1.20240612-1315) 12.3.1 20230626"
