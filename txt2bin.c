/*
*Copyright: http://see-programming.blogspot.com/2013/07/c-program-to-convert-text-file-to-binary.html
*/
#include <stdio.h>
#include <string.h>
#define MAX 256

  int main() {
        int num;
        FILE *fp1, *fp2;
        char ch, src[MAX], tgt[MAX];


        // Open input text file, output
        // binary file.
        // If we cannot open them, work
        // cannot be done, so return -1
        fp1 = fopen("hello.txt", "r");
    
        if (fp1 == NULL) {
            printf("cannot open input file\n");
            return -1;
        }
    
        fp2 = fopen("binFile.bin", "wb");
    
        if (fp2 == NULL) {
            printf("cannot open input file\n");
            return -1;
        }

        /*
         * read data from input file and write
         * the binary form of it in output file
         */
        while (!feof(fp1)) {
                /* reading one byte of data */
                fread(&ch, sizeof(char), 1, fp1);
                /* converting the character to ascii integer value */
                //num = ch;
                /* writing 4 byte of data to the output file */
                fwrite(&ch, sizeof(char), 1, fp2);
        }

        /* close all opened files */
        fclose(fp1);
        fclose(fp2);
        return 0;
  }