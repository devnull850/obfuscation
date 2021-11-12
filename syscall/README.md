# Hiding Syscall Instructions

The idea with the assembly instructions below is to hide the syscall instruction `syscall` in other instructions and jump in the middle of the other instructions to run the `syscall` instruction. The program simply prints 'Hello, World!' and a newline to the screen. This is nothing more than the fundamental introduction to a programming language program and paying homage to the work of [Brian Kernighan and Dennis Ritchie](https://en.wikipedia.org/wiki/The_C_Programming_Language). 

The machine code hexadecimal value for `syscall` on a 64 bit Debian based Linux OS is `0x0f 0x05`. In the disassembly below, the byte sequence `0xf 0x5` is seen starting at address 0x401006. The program loads a quad word value at 0x401000. This quad word value has three assembly instructions embedded in it. 0x401000 to 0x401005 is the instruction `movl $0x3c,%eax`. 0x401006 and 0x401007 is the instruction `syscall`. 0x401008 and 0x401009 is the instruction `jmp 401001`.

```
401000:	48 b8 3c 00 00 00 0f 	movabs rax,0xf7eb050f0000003c
401007:	05 eb f7 
40100a:	48 b9 74 65 6c 6c 60 	movabs rcx,0xa0cb29606c6c6574
401011:	29 cb a0 
401014:	48 31 c8             	xor    rax,rcx
401017:	48 89 44 24 f0       	mov    QWORD PTR [rsp-0x10],rax
40101c:	48 b8 6f 72 6c 64 21 	movabs rax,0xa21646c726f
401023:	0a 00 00 
401026:	48 89 44 24 f8       	mov    QWORD PTR [rsp-0x8],rax
40102b:	bf 01 00 00 00       	mov    edi,0x1
401030:	48 8d 74 24 f0       	lea    rsi,[rsp-0x10]
401035:	ba 0e 00 00 00       	mov    edx,0xe
40103a:	b8 01 00 00 00       	mov    eax,0x1
40103f:	eb c5                	jmp    401006 <__bss_start-0xffa>
```

0x40100a has a value moved into the %rcx register that is used to xor the value moved to the %rax register in the instruction at 0x401000. The xor is done to set the value of %rax to the characters 'Hello, W'. That value is then moved onto the stack at the address rsp-0x10. Next the remaining characters are moved onto the stack address rsp-0x8. 

With the string loaded on the stack, the appropriate registers are set for using the write syscall to print the string. The %edi register is set to 1 to use stdout, the standard output stream (the terminal by default). The %rsi has the stack address rsp-0x10 loaded in it. This is the starting address of our 'Hello, World!' string. The %edx register has hexademical 0xe or decimal 14 loaded. This is the number of characters we wish to print. Finally %eax has the value 1 loaded, which is the actual syscall we would like to use. This is the write syscall on a 64 bit Linux OS.

The instruction at 0x40103f is where the fun begins. The instruction jumps into the middle of the 0x401000 `movq` instruction. At the sixth byte of the instruction is the byte sequence `0x0f 0x05`. As discussed before, this is the syscall x64 assembly instruction. This results in the write syscall being called based on the configuration of the registers discussed previously. 'Hello, World!' is thus printed to the terminal. The byte sequence `eb f7` is next encountered at 0x401008, as the instruction pointer is pointed to that address. This is the instruction `jmp 0x401001`. The jumps places the program at the byte sequence `b8 3c 00 00 00`. This is the x64 instruction `movl $0x3c,%eax`. The hexadecimal value $0x3c is the decimal value 60. 60 is the exit syscall on a 64 bit Linux OS. The program then hits the syscall instruction again at 0x401006 and now exits.

