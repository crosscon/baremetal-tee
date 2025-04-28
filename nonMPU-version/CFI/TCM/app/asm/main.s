	.file	"main.c"
.text
	.balign 2
	.global	main
	.type	main, @function
main:
	; NOP slide!
	NOP
	NOP
	; End NOP slide
	







	
	
	MOVX.W	#23168, &WDTCTL
 
	BR #0xfee4
 
.L2:
	BRA	#.L2
	.size	main, .-main
	.ident	"GCC: (michele) 9.3.1"
	.mspabi_attribute 4, 2
	.mspabi_attribute 6, 2
	.mspabi_attribute 8, 2
	.gnu_attribute 4, 2
