#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef int bool;
#define true 1
#define false 0

bool isComment(FILE *inFile, FILE *outFile, char *c);
bool isString(FILE *inFile, FILE *outFile, char *c);
bool isChar(FILE *inFile, FILE *outFile, char *c);
bool isNum(FILE *inFile, FILE *outFile, char *c);
bool isOperators(FILE *inFile, FILE *outFile, char *c, const char *operators[]);
bool isIdentifiers(FILE *inFile, FILE *outFile, char *c, const char *operators[]);
bool isKeywords(FILE *inFile, FILE *outFile, char *build, const char *operators[]);
void setUnknown(FILE *inFile, FILE *outFile, char *c);

#endif