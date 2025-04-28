	.file	"secureContextSwitch.c"
.text
	.section	.tcm:code,"ax",@progbits
	.balign 2
	.global	secureCleaner
	.type	secureCleaner, @function
secureCleaner:
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
 ; 11 "core/src_compile/shadow/secureContextSwitch.c" 1
	BRA &0x10006
 ; 0 "" 2
	; start of epilogue
	RETA
	.size	secureCleaner, .-secureCleaner
	.balign 2
	.global	secureRestorer
	.type	secureRestorer, @function
secureRestorer:
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
	; start of epilogue
	RETA
	.size	secureRestorer, .-secureRestorer
	.ident	"GCC: (michele) 9.3.1"
	.mspabi_attribute 4, 2
	.mspabi_attribute 6, 2
	.mspabi_attribute 8, 2
	.gnu_attribute 4, 2
