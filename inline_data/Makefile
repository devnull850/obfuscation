
all: inline.o
	ld inline.o

inline.o: inline.s
	as -o inline.o inline.s

clean:
	rm inline inline.o

