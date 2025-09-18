#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

size_t openFile(char* filename, unsigned char *buffer, size_t maxsize) {
    FILE *fptr = fopen(filename, "rb");
    if (fptr == NULL) {
        fprintf(stdout, "%s: Not able to open the file (%s)\n", filename, strerror(errno));
        return 0;
    }

    size_t numberOfBytes = fread(buffer, 1, maxsize, fptr);
    fclose(fptr);
    return numberOfBytes;
}

int analyzeFile(unsigned char *buffer, size_t numberOfBytes) {
    if (numberOfBytes == 0) return -1; 

    int isASCII = 1;
    int isISO = 0;

    for (size_t i = 0; i < numberOfBytes; i++) {
        unsigned char b = buffer[i];
        if (b > 127) {
            isISO = 1;
            isASCII = 0;
        } else if (b < 32 && b != 9 && b != 10 && b != 13) {
            return 2;
        }
    }

    if (isASCII) return 1;
    if (isISO) return 0;

    return 2; 
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stdout, "Usage: file path\n");
        return EXIT_FAILURE;
    }

    unsigned char buffer[4900];
    size_t numberOfBytes = openFile(argv[1], buffer, sizeof(buffer));
    int filetype = analyzeFile(buffer, numberOfBytes);

    switch (filetype) {
        case -1: 
            printf("%s: empty\n", argv[1]); 
            break;
        case 0:  
            printf("%s: ISO-8859 text\n", argv[1]); 
            break;
        case 1:  
            printf("%s: ASCII text\n", argv[1]); 
            break;
        default: 
            printf("%s: data\n", argv[1]); 
            break;
    }
    return EXIT_SUCCESS;
}
