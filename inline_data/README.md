# Data Inline with Code


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
