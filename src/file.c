#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

size_t openFile(char* filename, unsigned char *buffer, size_t maxsize) {
    FILE *fptr = fopen(filename, "rb");
    if (fptr == NULL) {
        fprintf(stdout, "Not able to open the file\n");
        return EXIT_FAILURE;
    }

    size_t numberOfBytes = fread(buffer, 1, maxsize, fptr);
    fclose(fptr);
    return numberOfBytes;
}

int analyzeFile(unsigned char *buffer, size_t numberOfBytes) {
    if (numberOfBytes == 0) return -1; 
    for (size_t i = 0; i < numberOfBytes; i++) {
        if (buffer[i] > 127) return 0; 
    }
    return 1;
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
            printf("File is empty\n"); 
            break;
        case 0:  
            printf("File is ISO-8859\n"); 
            break;
        case 1:  
            printf("File is ASCII\n"); 
            break;
        default: 
            printf("Data file detected\n"); 
            break;
    }
    return EXIT_SUCCESS;
}
