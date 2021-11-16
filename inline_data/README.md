# Data Inline with Code

This demo walks through a simple x86 assembly source that is modified with data placed inline with code. The idea is to show how a linear disassembly sweep can easily be confused with inline data and the x86 CISC instruction set.

The program is intended to be slightly obscure from the start. The first instruction simply jumps to the instruction at 0x40100b to truly start the program. This is a basic Hello, World program. As such, we need to leverage the write syscall to output text to the terminal. The write syscall needs the EAX register loaded with the value 1. This is done by xor'ing the EDI register with itself. Xor'ing a value with itself will result in a zero. The EDI register is then incremented by 1 by the `inc` instruction. With 1 in the EDI register, we move (copy) the value to the EAX register for the write syscall.

A 1 in the EDI register for the write syscall is convenient. This is the value needed for the write syscall to use the standard output stream, stdout. The standard output stream is usually the terminal, which is exactly what we want.

```
  401000:	eb 09                	jmp    40100b <__bss_start-0xff5>
  401002:	31 ff                	xor    edi,edi
  401004:	b8 3c 00 00 00       	mov    eax,0x3c
  401009:	0f 05                	syscall 
  40100b:	31 ff                	xor    edi,edi
  40100d:	ff c7                	inc    edi
  40100f:	89 f8                	mov    eax,edi
  401011:	eb 14                	jmp    401027 <__bss_start-0xfd9>
  401013:	48                   	rex.W
  401014:	65 6c                	gs ins BYTE PTR es:[rdi],dx
  401016:	6c                   	ins    BYTE PTR es:[rdi],dx
  401017:	6f                   	outs   dx,DWORD PTR ds:[rsi]
  401018:	2c 20                	sub    al,0x20
  40101a:	57                   	push   rdi
  40101b:	6f                   	outs   dx,DWORD PTR ds:[rsi]
  40101c:	72 6c                	jb     40108a <__bss_start-0xf76>
  40101e:	64 21 0a             	and    DWORD PTR fs:[rdx],ecx
  401021:	00 b8 00 45 64 01    	add    BYTE PTR [rax+0x1644500],bh
  401027:	48 8d 34 25 13 10 40 	lea    rsi,ds:0x401013
  40102e:	00 
  40102f:	ba 0e 00 00 00       	mov    edx,0xe
  401034:	0f 05                	syscall 
  401036:	eb ca                	jmp    401002 <__bss_start-0xffe>
```

Next we jump to 0x401027. This instruction loads the address of what looks like the block of code we just jumped or skipped over. For the write syscall, the RSI register contains the address of the string we would like to output or write. We will come back to this. The hexadecimal value 0xe or decimal 14 is placed into the EDX register. This register contains the number of bytes to write. Finally the `syscall` instruction is called. "Hello, World!" is output to the terminal.

A jump is then encountered and places us at 0x401002. This is simply the exit syscall to return control back to the Operating System. EDI is set to zero to indicate successful completion of the program.

Going back to the "instructions" at 0x401013. It looks like a bunch of valid instructions but it is really the byte sequence for the ASCII characters for "Hello, World!" and a bit of random garbage bytes. `objdump` is a linear disassembler and the disassembly above is from running it on the binary.

