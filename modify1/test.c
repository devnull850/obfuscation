#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	char *buf;
	FILE *fd;
	void *p;
	long size, len;

	if ((fd = fopen("blob", "rb")) == NULL) {
		exit(EXIT_FAILURE);
	}

	fseek(fd, 0, SEEK_END);
	len = ftell(fd);
	fseek(fd, 0, SEEK_SET);

	if ((buf = malloc(len)) == NULL) {
		exit(EXIT_FAILURE);
	}

	fread(buf, 1, len, fd);

	if (fclose(fd) == EOF) {
		exit(EXIT_FAILURE);
	}

	p = (void *) ((size_t) main & 0xfffffffffffff000);
	size = sysconf(_SC_PAGESIZE);

	if (mprotect(p, size, PROT_READ|PROT_WRITE|PROT_EXEC) == -1) {
		exit(EXIT_FAILURE);
	}

	p = (void *) ((size_t) p + 0xa00);

	memcpy(p, buf, len);

	free(buf);

	((void (*)(void)) p)();
}
