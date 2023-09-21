#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

bool checkComment(FILE *inFile, FILE *outFile);
bool checkString(FILE *inFile, FILE *outFile);
bool checkChar(FILE *inFile, FILE *outFile);
bool checkNum(FILE *inFile, FILE *outFile);
bool checkOperators(FILE *inFile, FILE *outFile);
bool checkIdentifiers(FILE *inFile, FILE *outFile);
bool checkKeywords(FILE *inFile, FILE *outFile);
void setUnknown(FILE *inFile, FILE *outFile);

#endif