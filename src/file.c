#include <stdio.h>  // fprintf, stdout, stderr.
#include <stdlib.h> // exit, EXIT_FAILURE, EXIT_SUCCESS.
#include <string.h> // strerror.
#include <errno.h>  // errno.

int print_hello_world(void) {
    return fprintf(stdout, "Hello, worlddfghjkl!\n");
}

int openFile(char* filename) {
    FILE *fptr;
    int c, i, max;
    int is_ascii = 1;
    int is_iso = 1;
    int is_utf = 1;

    fptr = fopen(filename, "rb");

    if (fptr == NULL){
        fprintf(stdout, "Not able to open the file\n");
        return EXIT_FAILURE;
    }
    for (i = 0, max = 4900; i < max && (c = getc(fptr)) != EOF; i++) {
        printf("%02x", c);
        if (i % 16 == 15)
            putchar('\n'); 
        else if (i % 2 == 1)
            putchar(' ');  
        if (c > 127)
            is_ascii = 0;
    }
    if (i == 0){
        printf("File is empty\n");
        return EXIT_SUCCESS;
    }
    if (i % 16 != 0)
        putchar('\n');  // output a newline if needed


    fclose(fptr);
    return is_ascii;
    return is_iso;
    return is_utf;
}

int main(int argc, char* argv[]) {
    int retval = EXIT_SUCCESS;

    if (argc == 2) {
        int filedata = openFile(argv[1]);
        switch (filedata){
            case 0:
                printf("File is ASCII");
                break;
            case 1:
                printf("File is not ASCII");
                break;
            default:
                printf("Andet format end ASCII");
                break;
        }
        return retval;
    }
    fprintf(stdout, "Usage: file path\n");
    return EXIT_FAILURE;
}
