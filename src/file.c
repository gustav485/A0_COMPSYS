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
    int filetype = 9;

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
            filetype = 2;
    }
    if (i == 0){
        return -1;
    }
    if (i % 16 != 0)
        putchar('\n'); 


    fclose(fptr);
    return filetype;
}

int main(int argc, char* argv[]) {
    int retval = EXIT_SUCCESS;

    if (argc == 2) {
        int filedata = openFile(argv[1]);
        switch (filedata){
            case -1:
                printf("File is empty\n");
                break;
            case 0:
                printf("File is ISO-8859");
                break;
            case 1:
                printf("File is ASCII\n");
                break;
            case 9:
                printf("N/A, cannot determine\n");
                break;
            default:
                printf("Andet format end ASCII\n");
                break;
        }
        return retval;
    }
    fprintf(stdout, "Usage: file path\n");
    return EXIT_FAILURE;
}
