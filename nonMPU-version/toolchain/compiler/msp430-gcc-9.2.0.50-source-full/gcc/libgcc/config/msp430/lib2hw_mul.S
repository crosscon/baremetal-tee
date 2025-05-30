;   Copyright (C) 2014-2019 Free Software Foundation, Inc.
;   Contributed by Red Hat.
; 
; This file is free software; you can redistribute it and/or modify it
; under the terms of the GNU General Public License as published by the
; Free Software Foundation; either version 3, or (at your option) any
; later version.
; 
; This file is distributed in the hope that it will be useful, but
; WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
; General Public License for more details.
; 
; Under Section 7 of GPL version 3, you are granted additional
; permissions described in the GCC Runtime Library Exception, version
; 3.1, as published by the Free Software Foundation.
;
; You should have received a copy of the GNU General Public License and
; a copy of the GCC Runtime Library Exception along with this program;
; see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
; <http://www.gnu.org/licenses/>.

	;;  Macro to start a multiply function.  Each function has three
	;; names, and hence three entry points - although they all go
	;; through the same code.  The first name is the version generated
	;; by GCC.  The second is the MSP430 EABI mandated name for the
	;; *software* version of the function.  The third is the EABI
	;; mandated name for the *hardware* version of the function.
	;; 
	;;  Since we are using the hardware and software names to point
	;; to the same code this effectively means that we are mapping
	;; the software function onto the hardware function.  Thus if
	;; the library containing this code is linked into an application
	;; (before the libgcc.a library) *all* multiply functions will
	;; be mapped onto the hardware versions.
	;;
	;;  We construct each function in its own section so that linker
	;; garbage collection can be used to delete any unused functions
	;; from this file.
.macro start_func gcc_name eabi_soft_name eabi_hard_name
	.pushsection .text.\gcc_name,"ax",@progbits
	.p2align 1
	.global \eabi_hard_name
	.type \eabi_hard_name , @function
\eabi_hard_name:
	.global \eabi_soft_name
	.type \eabi_soft_name , @function
\eabi_soft_name:
	.global \gcc_name
	.type \gcc_name , @function
\gcc_name:
	PUSH.W	sr			; Save current interrupt state
	DINT				; Disable interrupts
	NOP				; Account for latency
.endm


	;; End a function started with the start_func macro.
.macro end_func name
#ifdef __MSP430X_LARGE__
	POP.W  sr
        RETA
#else
	RETI
#endif
	.size \name , . - \name
	.popsection
.endm


	;; Like the start_func macro except that it is used to
	;; create a false entry point that just jumps to the
	;; software function (implemented elsewhere).
.macro fake_func gcc_name  eabi_soft_name  eabi_hard_name
 	.pushsection .text.\gcc_name,"ax",@progbits
	.p2align 1
	.global \eabi_hard_name
	.type \eabi_hard_name , @function
\eabi_hard_name:
	.global \gcc_name
	.type \gcc_name , @function
\gcc_name:
#ifdef __MSP430X_LARGE__
	BRA	#\eabi_soft_name
#else
	BR	#\eabi_soft_name
#endif
	.size \gcc_name , . - \gcc_name
	.popsection
.endm


.macro mult16 OP1, OP2, RESULT
;* * 16-bit hardware multiply:  int16 = int16 * int16
;*  
;*   - Operand 1 is in R12
;*   - Operand 2 is in R13
;*   - Result is in R12
;*
;* To ensure that the multiply is performed atomically, interrupts are
;* disabled upon routine entry.  Interrupt state is restored upon exit.
;*
;*   Registers used:  R12, R13
;*
;* Macro arguments are the memory locations of the hardware registers.
	
	MOV.W	r12, &\OP1		; Load operand 1 into multiplier
	MOV.W	r13, &\OP2		; Load operand 2 which triggers MPY
	MOV.W	&\RESULT, r12		; Move result into return register
.endm

.macro mult1632 OP1, OP2, RESLO, RESHI
;* * 16-bit hardware multiply with a 32-bit result:
;*	int32 = int16 * int16
;* 	uint32 = uint16 * uint16
;*  
;*   - Operand 1 is in R12
;*   - Operand 2 is in R13
;*   - Result is in R12, R13
;*
;* To ensure that the multiply is performed atomically, interrupts are
;* disabled upon routine entry.  Interrupt state is restored upon exit.
;*
;*   Registers used:  R12, R13
;*
;* Macro arguments are the memory locations of the hardware registers.
	
	MOV.W	r12, &\OP1		; Load operand 1 into multiplier
	MOV.W	r13, &\OP2		; Load operand 2 which triggers MPY
	MOV.W	&\RESLO, r12		; Move low result into return register
	MOV.W	&\RESHI, r13		; Move high result into return register
.endm

.macro mult32 OP1, OP2, MAC_OP1, MAC_OP2, RESLO, RESHI
;* * 32-bit hardware multiply with a 32-bit result using 16 multiply and accumulate:
;*	int32 = int32 * int32
;*  
;*   - Operand 1 is in R12, R13
;*   - Operand 2 is in R14, R15
;*   - Result    is in R12, R13
;*
;* To ensure that the multiply is performed atomically, interrupts are
;* disabled upon routine entry.  Interrupt state is restored upon exit.
;*
;*   Registers used:  R12, R13, R14, R15
;*
;* Macro arguments are the memory locations of the hardware registers.
	
	MOV.W	r12, &\OP1		; Load operand 1 Low into multiplier
	MOV.W	r14, &\OP2		; Load operand 2 Low which triggers MPY
	MOV.W	r12, &\MAC_OP1		; Load operand 1 Low into mac
	MOV.W   &\RESLO, r12		; Low 16-bits of result ready for return
	MOV.W   &\RESHI, &\RESLO	; MOV intermediate mpy high into low
	MOV.W	r15, &\MAC_OP2		; Load operand 2 High, trigger MAC
	MOV.W	r13, &\MAC_OP1		; Load operand 1 High
	MOV.W	r14, &\MAC_OP2		; Load operand 2 Lo, trigger MAC
	MOV.W	&\RESLO, r13        	; Upper 16-bits result ready for return
.endm


.macro mult32_hw  OP1_LO  OP1_HI  OP2_LO  OP2_HI  RESLO  RESHI
;* * 32-bit hardware multiply with a 32-bit result
;*	int32 = int32 * int32
;*  
;*   - Operand 1 is in R12, R13
;*   - Operand 2 is in R14, R15
;*   - Result    is in R12, R13
;*
;* To ensure that the multiply is performed atomically, interrupts are
;* disabled upon routine entry.  Interrupt state is restored upon exit.
;*
;*   Registers used:  R12, R13, R14, R15
;*
;* Macro arguments are the memory locations of the hardware registers.
	
	MOV.W	r12, &\OP1_LO		; Load operand 1 Low into multiplier
	MOV.W	r13, &\OP1_HI		; Load operand 1 High into multiplier
	MOV.W	r14, &\OP2_LO		; Load operand 2 Low into multiplier
	MOV.W	r15, &\OP2_HI		; Load operand 2 High, trigger MPY
	MOV.W	&\RESLO, r12		; Ready low 16-bits for return
	MOV.W   &\RESHI, r13		; Ready high 16-bits for return
.endm

.macro mult3264_hw  OP1_LO  OP1_HI  OP2_LO  OP2_HI  RES0 RES1 RES2 RES3
;* * 32-bit hardware multiply with a 64-bit result
;*	int64 = int32 * int32
;*	uint64 = uint32 * uint32
;*  
;*   - Operand 1 is in R12, R13
;*   - Operand 2 is in R14, R15
;*   - Result    is in R12, R13, R14, R15
;*
;* To ensure that the multiply is performed atomically, interrupts are
;* disabled upon routine entry.  Interrupt state is restored upon exit.
;*
;*   Registers used:  R12, R13, R14, R15
;*
;* Macro arguments are the memory locations of the hardware registers.
	
	MOV.W	r12, &\OP1_LO		; Load operand 1 Low into multiplier
	MOV.W	r13, &\OP1_HI		; Load operand 1 High into multiplier
	MOV.W	r14, &\OP2_LO		; Load operand 2 Low into multiplier
	MOV.W	r15, &\OP2_HI		; Load operand 2 High, trigger MPY
	MOV.W	&\RES0, R12		; Ready low 16-bits for return
	MOV.W   &\RES1, R13		; 
	MOV.W	&\RES2, R14		; 
	MOV.W   &\RES3, R15		; Ready high 16-bits for return
.endm


;; EABI mandated names:
;; 
;; int16 __mspabi_mpyi (int16 x, int16 y)
;;            Multiply int by int.
;; int16 __mspabi_mpyi_hw (int16 x, int16 y)
;;            Multiply int by int. Uses hardware MPY16 or MPY32.
;; int16 __mspabi_mpyi_f5hw (int16 x, int16 y)
;;            Multiply int by int. Uses hardware MPY32 (F5xx devices and up).
;; 
;; int32 __mspabi_mpyl (int32 x, int32 y);
;;  	      Multiply long by long.
;; int32 __mspabi_mpyl_hw (int32 x, int32 y)
;; 	      Multiply long by long. Uses hardware MPY16.
;; int32 __mspabi_mpyl_hw32 (int32 x, int32 y)
;; 	      Multiply long by long. Uses hardware MPY32 (F4xx devices).
;; int32 __mspabi_mpyl_f5hw (int32 x, int32 y)
;; 	      Multiply long by long. Uses hardware MPY32 (F5xx devices and up).
;; 
;; int64 __mspabi_mpyll (int64 x, int64 y)
;; 	      Multiply long long by long long.
;; int64 __mspabi_mpyll_hw (int64 x, int64 y)
;; 	      Multiply long long by long long. Uses hardware MPY16.
;; int64 __mspabi_mpyll_hw32 (int64 x, int64 y)
;; 	      Multiply long long by long long. Uses hardware MPY32 (F4xx devices).
;; int64 __mspabi_mpyll_f5hw (int64 x, int64 y)
;; 	      Multiply long long by long long. Uses hardware MPY32 (F5xx devices and up).
;;
;; int32 __mspabi_mpysl (int16 x, int16 y)
;;            Multiply int by int; result is long.
;; int32 __mspabi_mpysl_hw(int16 x, int16 y)
;; 	      Multiply int by int; result is long. Uses hardware MPY16 or MPY32
;; int32 __mspabi_mpysl_f5hw(int16 x, int16 y)
;; 	      Multiply int by int; result is long. Uses hardware MPY32 (F5xx devices and up).
;; 
;; int64 __mspabi_mpysll(int32 x, int32 y)
;;            Multiply long by long; result is long long.
;; int64 __mspabi_mpysll_hw(int32 x, int32 y)
;; 	      Multiply long by long; result is long long. Uses hardware MPY16.
;; int64 __mspabi_mpysll_hw32(int32 x, int32 y)
;; 	      Multiply long by long; result is long long. Uses hardware MPY32 (F4xx devices).
;; int64 __mspabi_mpysll_f5hw(int32 x, int32 y)
;; 	      Multiply long by long; result is long long. Uses hardware MPY32 (F5xx devices and up).
;; 
;; uint32 __mspabi_mpyul(uint16 x, uint16 y)
;; 	      Multiply unsigned int by unsigned int; result is unsigned long.
;; uint32 __mspabi_mpyul_hw(uint16 x, uint16 y)
;; 	      Multiply unsigned int by unsigned int; result is unsigned long. Uses hardware MPY16 or MPY32
;; uint32 __mspabi_mpyul_f5hw(uint16 x, uint16 y)
;; 	      Multiply unsigned int by unsigned int; result is unsigned long. Uses hardware MPY32 (F5xx devices and up).
;; 
;; uint64 __mspabi_mpyull(uint32 x, uint32 y)
;; 	      Multiply unsigned long by unsigned long; result is unsigned long long.
;; uint64 __mspabi_mpyull_hw(uint32 x, uint32 y)
;; 	      Multiply unsigned long by unsigned long; result is unsigned long long. Uses hardware MPY16
;; uint64 __mspabi_mpyull_hw32(uint32 x, uint32 y)
;; 	      Multiply unsigned long by unsigned long; result is unsigned long long. Uses hardware MPY32 (F4xx devices).
;; uint64 __mspabi_mpyull_f5hw(uint32 x, uint32 y)
;;            Multiply unsigned long by unsigned long; result is unsigned long long. Uses hardware MPY32 (F5xx devices and up)

;;;; The register names below are the standardised versions used across TI literature.
;; Hardware multiply register addresses for devices with 16-bit hardware multiply
.set MPY,	0x0130
.set MPYS,	0x0132
.set MAC, 	0x0134
.set OP2, 	0x0138
.set RESLO,	0x013A
.set RESHI,	0x013C
;; Hardware multiply register addresses for devices with 32-bit (non-f5) hardware multiply
.set MPY32L,	0x0140
.set MPY32H,	0x0142
.set MPYS32L,	0x0144
.set MPYS32H,	0x0146
.set OP2L,	0x0150
.set OP2H,	0x0152
.set RES0,	0x0154
.set RES1,	0x0156
.set RES2,	0x0158
.set RES3,	0x015A
;; Hardware multiply register addresses for devices with f5series hardware multiply
;; The F5xxx series of MCUs support the same 16-bit and 32-bit multiply
;; as the second generation hardware, but they are accessed from different
;; memory registers.
;; These names AREN'T standard.  We've appended _F5 to the standard names.
.set MPY_F5,		0x04C0
.set MPYS_F5,		0x04C2
.set MAC_F5,		0x04C4
.set OP2_F5,		0x04C8
.set RESLO_F5,		0x04CA
.set RESHI_F5,		0x04CC
.set MPY32L_F5,		0x04D0
.set MPY32H_F5,		0x04D2
.set MPYS32L_F5,	0x04D4
.set MPYS32H_F5,	0x04D6
.set OP2L_F5,		0x04E0
.set OP2H_F5,		0x04E2
.set RES0_F5,		0x04E4
.set RES1_F5,		0x04E6
.set RES2_F5,		0x04E8
.set RES3_F5,		0x04EA

#if defined MUL_16
;;  First generation MSP430 hardware multiplies ...

	start_func __mulhi2 __mspabi_mpyi  __mspabi_mpyi_hw
	mult16 MPY, OP2, RESLO
	end_func   __mulhi2

	start_func __mulhisi2  __mspabi_mpysl  __mspabi_mpysl_hw
	mult1632 MPYS, OP2, RESLO, RESHI
	end_func   __mulhisi2

	start_func __umulhisi2  __mspabi_mpyul  __mspabi_mpyul_hw
	mult1632 MPY, OP2, RESLO, RESHI
	end_func   __umulhisi2

	start_func __mulsi2  __mspabi_mpyl  __mspabi_mpyl_hw
	mult32 MPY, OP2, MAC, OP2, RESLO, RESHI
	end_func   __mulsi2

	;; FIXME: We do not have hardware implementations of these
	;; routines, so just jump to the software versions instead.
	fake_func __mulsidi2   __mspabi_mpysll  __mspabi_mpysll_hw
	fake_func __umulsidi2  __mspabi_mpyull  __mspabi_mpyull_hw
	fake_func __muldi3     __mspabi_mpyll   __mspabi_mpyll_hw

#elif defined MUL_32
;;  Second generation MSP430 hardware multiplies ...

	start_func __mulhi2  __mspabi_mpyi  __mspabi_mpyi_hw
	mult16 MPY, OP2, RESLO
	end_func   __mulhi2

	start_func __mulhisi2  __mspabi_mpysl  __mspabi_mpysl_hw
	mult1632 MPYS, OP2, RESLO, RESHI
	end_func   __mulhisi2

	start_func __umulhisi2  __mspabi_mpyul  __mspabi_mpyul_hw
	mult1632 MPY, OP2, RESLO, RESHI
	end_func   __umulhisi2

	start_func __mulsi2_hw32  __mspabi_mpyl  __mspabi_mpyl_hw32
	mult32_hw MPY32L, MPY32H, OP2L, OP2H, RES0, RES1
	end_func   __mulsi2_hw32

	start_func __mulsidi2  __mspabi_mpysll  __mspabi_mpysll_hw32
	mult3264_hw MPYS32L, MPYS32H, OP2L, OP2H, RES0, RES1, RES2, RES3
	end_func   __mulsidi2

	start_func __umulsidi2 __mspabi_mpyull  __mspabi_mpyull_hw32
	mult3264_hw MPY32L, MPY32H, OP2L, OP2H, RES0, RES1, RES2, RES3
	end_func   __umulsidi2

	;; FIXME: Add a hardware version of this function.
	fake_func __muldi3    __mspabi_mpyll  __mspabi_mpyll_hw32

#elif defined MUL_F5
	;; FIXME: Why do these "GCC names" have _f5 in the name?????

	start_func __mulhi2_f5 __mspabi_mpyi  __mspabi_mpyi_f5hw
	mult16 MPY_F5, OP2_F5, RESLO_F5
	end_func   __mulhi2_f5

	start_func __mulhisi2  __mspabi_mpysl  __mspabi_mpysl_f5hw
	mult1632 MPYS_F5, OP2_F5, RESLO_F5, RESHI_F5
	end_func   __mulhisi2

	start_func __umulhisi2  __mspabi_mpyul  __mspabi_mpyul_f5hw
	mult1632 MPY_F5, OP2_F5, RESLO_F5, RESHI_F5
	end_func   __umulhisi2

	start_func __mulsi2_f5  __mspabi_mpyl  __mspabi_mpyl_f5hw
	mult32_hw MPY32L_F5, MPY32H_F5, OP2L_F5, OP2H_F5, RES0_F5, RES1_F5
	end_func   __mulsi2_f5

	start_func __mulsidi2  __mspabi_mpysll  __mspabi_mpysll_f5hw
	mult3264_hw MPYS32L_F5, MPYS32H_F5, OP2L_F5, OP2H_F5, RES0_F5, RES1_F5, RES2_F5, RES3_F5
	end_func   __mulsidi2

	start_func __umulsidi2  __mspabi_mpyull  __mspabi_mpyull_f5hw
	mult3264_hw MPY32L_F5, MPY32H_F5, OP2L_F5, OP2H_F5, RES0_F5, RES1_F5, RES2_F5, RES3_F5
	end_func   __umulsidi2

	;; FIXME: Add a hardware version of this function.
	fake_func __muldi3   __mspabi_mpyll __mspabi_mpyll_f5hw

#else
#error MUL type not defined
#endif
