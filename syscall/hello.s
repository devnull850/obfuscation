	.section .text
	movq	$0xf7eb050f0000003c,%rax
	movq	$0xa0cb29606c6c6574,%rcx
	xorq	%rcx,%rax
	movq	%rax,0xfffffffffffffff0(%rsp)
	movq	$0xa21646c726f,%rax
	movq	%rax,0xfffffffffffffff8(%rsp)
	movl	$1,%edi
	leaq	0xfffffffffffffff0(%rsp),%rsi
	movl	$0xe,%edx
	movl	$1,%eax
	jmp	.text+6
