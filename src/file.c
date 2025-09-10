#include <stdio.h>  // fprintf, stdout, stderr.
#include <stdlib.h> // exit, EXIT_FAILURE, EXIT_SUCCESS.
#include <string.h> // strerror.
#include <errno.h>  // errno.

int print_hello_world(void) {
    return fprintf(stdout, "Hello, worlddfghjkl!\n");
}

int openFile(void) {
    FILE *fptr;
    fptr = fopen("test_files/ascii.input", "r");
    if (fptr==NULL){
        fprintf(stdout,"Not able to open the file\n");
    }
    char stringStore[100];
    fgets(stringStore, 100, fptr);
    fprintf(stdout,"%s\n", stringStore);
    fclose(fptr);
    return 1;
}

int main(void) {
    int retval = EXIT_SUCCESS;
    if (openFile() >= 0) {
      return 1;
    }
    if (print_hello_world() <= 0) {
        retval = EXIT_FAILURE;
    }

    return retval;
}
