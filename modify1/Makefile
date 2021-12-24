all: test

test: test.c blob
	gcc -Wall -Werror test.c

blob: bytes.o
	dd if=bytes.o of=blob skip=64 count=63 bs=1

bytes.o: bytes.s
	as -o bytes.o bytes.s

.PHONY:
clean:
	rm bytes.o blob a.out
