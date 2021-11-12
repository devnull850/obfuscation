
all: hello.o
	ld hello.o

hello.o: hello.s
	as -o hello.o hello.s

clean:
	rm hello hello.o
