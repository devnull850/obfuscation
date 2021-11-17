# Self Modifying Code

This program demonstrates the use of self modifying code to obscure static analysis of the source and binary. A quick glance of the foo function looks like it should simply print the string literal, "The quick brown fox jumped over the lazy sleeping dog." When one compiles and then runs the executable, "Hello, World!" is printed to the terminal instead.

```
void foo(void) {
    puts("The quick brown fox jumped over the lazy sleeping dog.");
}
```

The byte array seen below is the key to printing "Hello, World!" It contains the raw binary bytes for the x86 machine instructions to print "Hello, World!" to the terminal.

```
const unsigned char BLOB[] = {
         0x48,0xb8,0x6f,0x72,0x6c,0x64,0x21,0x0a
        ,0x00,0x00,0x50,0x48,0xb8,0x48,0x65,0x6c
        ,0x6c,0x6f,0x2c,0x20,0x57,0x50,0x31,0xff
        ,0x57,0xff,0xc7,0x89,0xf8,0x48,0x8d,0x74
        ,0x24,0x08,0x48,0x8d,0x57,0x0d,0x0f,0x05
        ,0x5f,0xb8,0x3c,0x00,0x00,0x00,0xeb,0xf6
    };
```

On a Linux platform, the default operating system behavior is to not allow writing to sections marked as executable. An attempt to do this will result in segfault signal from the operating system. (Trust me I tried this initially.) Thankfully the `mprotect` system API function is provided to manipulate or change this property. `mprotect` is found in the `<sys/mman.h>` header file.

First one needs to acquire the size of a memory page for the respective system. This is done by using `sysconf(_SC_PAGESIZE)` in the `<unistd.h>` header file. Next one needs to find an address to change or modify the bytes/code of. I chose a function that was not `main` to prevent overriding my `main` function. `foo()` is the example function used for the purpose of writing over or modifying its code. Two pointers, `p` and `addr`, are used to store the address of the `foo` function. `p` has arithmetic performed on it to align the address it points to, to the beginning of the page it is in.

```
p = addr = (void *) foo;
pagesize = sysconf(_SC_PAGESIZE);
p -= (size_t) p % pagesize;
```	
`mprotect` is used to change the access protections of the memory page pointed to by `p`. In this case, the code is changing the page containing the executable code and allowing it to be written to.

```
if (mprotect(p, pagesize, PROT_READ|PROT_WRITE|PROT_EXEC) == -1) {
    fprintf(stderr, "error with mprotect\n");
    exit(EXIT_FAILURE);
}
```

The `memcpy` function from the `<string.h>` header file is used to copy the machine code bytes, `BLOB`, from above.

```
memcpy(addr, BLOB, BYTES);
```

With the `foo` function modified, the program then calls the `foo` function. Now the program runs the machine code from `BLOB` instead of the copied over `puts` command.

