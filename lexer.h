#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

bool isComment(FILE *inFile, FILE *outFile, char *c);
bool isString(FILE *inFile, FILE *outFile);
bool isChar(FILE *inFile, FILE *outFile);
bool isNum(FILE *inFile, FILE *outFile);
bool isOperators(FILE *inFile, FILE *outFile);
bool isIdentifiers(FILE *inFile, FILE *outFile);
bool isKeywords(FILE *inFile, FILE *outFile);
void setUnknown(FILE *inFile, FILE *outFile);

#endif