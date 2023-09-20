#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int checkComment(FILE *inFile, FILE *outFile);
int checkString(FILE *inFile, FILE *outFile);
int checkChar(FILE *inFile, FILE *outFile);
int checkNum(FILE *inFile, FILE *outFile);
int checkOperators(FILE *inFile, FILE *outFile);
int checkIdentifiers(FILE *inFile, FILE *outFile);
int checkKeywords(FILE *inFile, FILE *outFile);
void setUnknown(FILE *inFile, FILE *outFile);

#endif