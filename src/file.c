#include <stdio.h>  // fprintf, stdout, stderr.
#include <stdlib.h> // exit, EXIT_FAILURE, EXIT_SUCCESS.
#include <string.h> // strerror.
#include <errno.h>  // errno.

int print_hello_world(void) {
    return fprintf(stdout, "Hello, worlddfghjkl!\n");
}

int openFile(char* filename) {
    FILE *fptr;
    fptr = fopen(filename, "r");
    if (fptr == NULL){
        fprintf(stdout, "Not able to open the file\n");
        return EXIT_FAILURE;
    }
    char stringStore[100];
    fgets(stringStore, 100, fptr);
    fprintf(stdout,"%s\n", stringStore);
    fclose(fptr);
    return 1;
}

int main(int argc, char* argv[]) {
    int retval = EXIT_SUCCESS;

    if (argc == 2) {
      openFile(argv[1]);
      return retval;
    }
    fprintf(stdout, "No eliglbe file to be read\n");
    return EXIT_FAILURE;
}
