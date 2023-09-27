/**
 * @name Aaron Jarnes
 * @date 9/27/23
 * @brief This is the header file where function headers are stored, 
 *        libraries are included, and the type boolean is defined to return true or false. 
*/
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
bool isIdentifiers(FILE *inFile, FILE *outFile, char *c, const char *keywords[]);
bool isKeywords(FILE *inFile, FILE *outFile, char *build, const char *keywords[]);
bool isOperators(FILE *inFile, FILE *outFile, char *c, const char *operators[]);
void setUnknown(FILE *inFile, FILE *outFile, char *c);

#endif