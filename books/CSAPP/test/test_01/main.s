	.file	"main.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6

	pushq %rax
	pushq %rdx
	pushq %rdi

	movq $0, %rdx
	movq $0, %rax
	movq $0, %rdi

	movq $8, %rax
	movq $10, %rdx

	cmpq %rdx, %rax
	setl %dil

	popq %rdi
	popq %rdx
	popq %rax

	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$10, -4(%rbp)
	addl	$20, -4(%rbp)
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.1.0-1ubuntu1~20.04) 11.1.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
