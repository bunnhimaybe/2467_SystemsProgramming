	.file	"hello.i"
	.intel_syntax noprefix
	.text
	.section	.rodata
.LC0:
	.string	"Hello world."
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp		        # RBP = base of stack frame
	.cfi_def_cfa_register 6
	sub	rsp, 16			        # allocate space on the stack for retval
	mov	DWORD PTR -4[rbp], 67	# value 67 stored in retval (first 4 bytes below rbp)
	lea	rdi, .LC0[rip]          # load string's address in RDI register
	call	puts@PLT            # puts = printf call
	mov	eax, DWORD PTR -4[rbp]  # return value of function
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
