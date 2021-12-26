//
// Created by diego on 20/05/21.
//

#ifndef DIEGOBELARDINELLI109323_BVERNAN_H
#define DIEGOBELARDINELLI109323_BVERNAN_H

extern long keyFileLength;

int getKeyFileLength (FILE *keyFile, long *length);

//fissa la posizione nel file
struct filePosition{
    long index;
    long block;
};

typedef struct filePosition filePosition;

//ricava la struttura "posizione nel file"
filePosition* getFilePosition ();

//aggiorna i campi della struttura file position
int updateFilePosition (long index, filePosition *fp);

//definisce il byte sorgente da criptare
struct sourceByte{
    unsigned char byte;
    filePosition *bytePosition;
};

typedef struct sourceByte sourceByte;

//ricava il byte sorgente
sourceByte* getSourceByte ();

//aggiorna i campi del byte sorgente
int updateSourceByte (unsigned char myByte, sourceByte *sb, filePosition *fp);

//metodo ci cifratura
int encode (sourceByte *byteToCrypt, unsigned char *cryptedByte, FILE *keyFile);

#endif //DIEGOBELARDINELLI109323_BVERNAN_H
