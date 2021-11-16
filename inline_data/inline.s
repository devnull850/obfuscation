	.section .text
	jmp	.text+0xb
	xorl	%edi,%edi
	movl	$0x3c,%eax
	syscall
	xorl	%edi,%edi
	inc	%edi
	movl	%edi,%eax
	jmp	.text+0x27
	movq	$0x7fffffffffffffff,%rax
	movq	$0x7fffffffffffffff,%rax
	leaq	.text+0x13,%rsi
	movl	$0xe,%edx
	syscall
	jmp	.text+2
