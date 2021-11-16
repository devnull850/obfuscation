
#include <stdio.h>
#include <stdlib.h>

#define LEN 20

const char MSG[] = {0x48,0x65,0x6c,0x6c,0x6f,0x2c,0x20,0x57,0x6f,0x72,
                    0x6c,0x64,0x21,0x0a,0x00,0xb8,0x00,0x45,0x64,0x01};
const char FILENAME[] = "a.out";

int main(void) {
    FILE *fd;

    if ((fd = fopen(FILENAME, "rb+")) == NULL) {
        fprintf(stderr, "error opening file [%s]\n", FILENAME);
        exit(EXIT_FAILURE);
    }

    if (fseek(fd, 0x1013, SEEK_SET) == -1) {
        fprintf(stderr, "error advancing file position [%s]\n", FILENAME);
        exit(EXIT_FAILURE);
    }

    if (fwrite(MSG, 1, LEN, fd) != LEN) {
        fprintf(stderr, "error writing to file [%s]\n", FILENAME);
        exit(EXIT_FAILURE);
    }

    if (fclose(fd) == EOF) {
        fprintf(stderr, "error closing file [%s]\n", FILENAME);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

