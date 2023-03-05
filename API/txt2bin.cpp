#include "txt2bin.hpp"

#define MAX 256

void generateBinaryFile(std::string inputFile, std::string outputFile) {
    int num;
    FILE *fp1, *fp2;
    char ch, src[MAX], tgt[MAX];

    fp1 = fopen(inputFile.c_str(), "r");
    if (fp1 == NULL) {
        std::cout << "Cannot open input file" << std::endl;
        exit(EXIT_FAILURE);
    }

    fp2 = fopen(outputFile.c_str(), "wb");
    if (fp2 == NULL) {
        std::cout << "Cannot open output file" << std::endl;
        exit(EXIT_FAILURE);
    }

    while(!feof(fp1)) {
        fread(&ch, sizeof(char), 1, fp1);
        fwrite(&ch, sizeof(char), 1, fp2);
    }

    fclose(fp1);
    fclose(fp2);
}