#include <stdio.h>
#include <stdlib.h>
#include "bvernan.h"

int main(int argc, char **argv) {
    if (argc != 4)
        exit(EXIT_FAILURE);
    char *keyFileArgv = argv[1];
    FILE *keyFile = fopen(keyFileArgv, "rb");
    char *inputFileArgv = argv[2];
    FILE *inputFile = fopen(inputFileArgv, "rb");
    char *outputFileArgv = argv[3];
    FILE *outputFile = fopen(outputFileArgv, "wb");

    getKeyFileLength(keyFile, &keyFileLength);
    long indexSourceFile = 0;
    size_t check;
    unsigned char byteBuffer;
    filePosition *position = getFilePosition();
    sourceByte *mySourceByte = getSourceByte();
    unsigned char cryptedByte;
    while (1){
        check = fread(&byteBuffer, sizeof(unsigned char), 1, inputFile);
        if (check < 1) {
            break;
        }
        updateFilePosition(indexSourceFile, position);
        updateSourceByte(byteBuffer, mySourceByte, position);
        encode(mySourceByte, &cryptedByte, keyFile);
        fwrite(&cryptedByte, sizeof(char), 1, outputFile);
        indexSourceFile++;
    }
    free(position);
    free(mySourceByte);
    fclose(inputFile);
    fclose(keyFile);
    fclose(outputFile);
    return 0;
}
