#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

size_t openFile(char* filename, unsigned char *buffer, size_t maxsize) {
    FILE *fptr = fopen(filename, "rb");                                                      //Åbner fil med filnavn i "read binary" mode   
    if (fptr == NULL) {
        fprintf(stdout, "%s: Not able to open the file (%s)\n", filename, strerror(errno));  //Tjekker om filen kan åbnes, hvis ikke sendes en error besked
        return 0;
    }

    size_t numberOfBytes = fread(buffer, 1, maxsize, fptr);                                 //Filen læses indtil maxsize nås
    fclose(fptr);                                                                           //Filen lukkes når funktionen er færdig
    
    return numberOfBytes;                                                                   //Returnering af de læste bytes
}

int analyzeFile(unsigned char *buffer, size_t numberOfBytes) {
    if (numberOfBytes == 0) {
        return -1;                                                      //Returnere -1 hvis filen er tom
    }

    int isASCII = 1;                                                    //Antager først af filen er ascii
    int isISO = 0;

    for (size_t i = 0; i < numberOfBytes; i++) {                        // Gennemgår hver byte
        unsigned char b = buffer[i];                                    // Henter byte
        if (b > 127) {                                                  // Hvis byte er over ASCII grænsen markeres den som ISO
            isISO = 1;
            isASCII = 0;
        } else if (b < 32 && b != 9 && b != 10 && b != 13) {            // Hvis byte er en karakter der ikke indgår i hverken ascii eller iso markeres den som data
            return 2;
        }
    }

    if (isASCII){               //Returnere en værdi til main
        return 1;
    }
    if (isISO){
        return 0;
    }
    return 2; 
}

int main(int argc, char* argv[]) {
    if (argc != 2) {                                //Hvis der gives et andet antal end 2 argumenter sendes en warning
        fprintf(stdout, "Usage: file path\n");
        return EXIT_FAILURE;
    }

    unsigned char buffer[4900];                                         //Antal bytes der må læses 
    size_t numberOfBytes = openFile(argv[1], buffer, sizeof(buffer));   //Filen læses
    int filetype = analyzeFile(buffer, numberOfBytes);                  //Filen analyseres

    switch (filetype) {                                         //Alt efter hvilken værdi der returneres fra analyse funktionen printes den passende besked.
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
    return EXIT_SUCCESS;                            //programmet afsluttes
}
