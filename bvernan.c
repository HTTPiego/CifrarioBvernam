#include <stdio.h>
#include <stdlib.h>
#include "bvernan.h"

long keyFileLength;

int getKeyFileLength (FILE *keyFile, long *length){
    fseek(keyFile, 0, SEEK_END);
    *length = ftell(keyFile);
    rewind(keyFile);
    return 1;
}

filePosition* getFilePosition(){
    filePosition *fp = malloc(sizeof(filePosition));
    return fp;
}

int updateFilePosition (long index, filePosition *fp){
    long block = index/keyFileLength;
    fp->index = index;
    fp->block = block;
    return 1;
}

sourceByte* getSourceByte (){
    sourceByte *sb = malloc(sizeof(sourceByte));
    return sb;
}

int updateSourceByte (unsigned char myByte, sourceByte *sb, filePosition *fp){
    sb->byte = myByte;
    sb->bytePosition = fp;
    return 1;
}

int encode (sourceByte *byteToCrypt, unsigned char *cryptedByte, FILE *keyFile) {
    //trovo il indice del byte con cui criptare
    //il byte sorgente
    long indexKeyFile;
    indexKeyFile = (byteToCrypt->bytePosition->index +
                    byteToCrypt->bytePosition->block) % keyFileLength;
    fseek(keyFile, indexKeyFile,SEEK_SET);
    char cryptingByte;
    //fisso il byte con cui criptare il file sorgente
    size_t check = fread(&cryptingByte, sizeof(unsigned char), 1, keyFile);
    if (check != 1) {
        return 0;
    }
    //risultato criptato
    *cryptedByte = (unsigned char) byteToCrypt->byte^cryptingByte;
    return 1;
}



