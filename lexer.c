#include "lexer.h"

/**
 * @brief 
 * @param inFile 
 * @param outFile 
 * @return @param bool 
*/
bool isComment(FILE *inFile, FILE *outFile, char *c){
    if(*c == '/'){
        char ch = fgetc(inFile);
        if(ch == '*'){
            fprintf(outFile, "%c%c", *c, ch);
            *c = fgetc(inFile);
            while(*c != '/'){ //if / then end comment
                fprintf(outFile, "%c", *c);
                *c = fgetc(inFile);
            }
            fprintf(outFile, "%c (comment)\n", *c);
            return true;
        } else {
            //put cursor -2 then set c to / again then return false
            fseek(inFile, -1, SEEK_CUR);
        }
    }
    return false;
}

/**
 * @brief 
 * @param inFile 
 * @param outFile 
 * @return @param bool 
*/
bool isString(FILE *inFile, FILE *outFile, char *c){
    if(*c == '"'){
        fprintf(outFile, "%c", *c); // print first "
        *c = fgetc(inFile);
        while (*c != '"'){
            fprintf(outFile, "%c", *c);
            *c = fgetc(inFile);
        }
        fprintf(outFile, "%c (string)\n", *c); //print last "
        return true;
    }
    return false;
}

/**
 * @brief 
 * @param inFile 
 * @param outFile 
 * @return @param bool 
*/
bool isChar(FILE *inFile, FILE *outFile, char *c){
    if(*c == '\''){
        fprintf(outFile, "%c", *c); // print first '
        *c = fgetc(inFile);
        while (*c != '\''){
            fprintf(outFile, "%c", *c);
            *c = fgetc(inFile);
        }
        fprintf(outFile, "%c (character literal)\n", *c); //print last '
        return true;
    }
    return false;
}

/**
 * @brief 
 * @param inFile 
 * @param outFile 
 * @return @param bool 
*/
bool isNum(FILE *inFile, FILE *outFile, char *c){
    if(isdigit(*c)){
        while(isdigit(*c) || *c == '.' || *c == '#'){
            //if period
            if (*c == '.'){
                char ch = fgetc(inFile);
                if (ch == '.'){ //operator .. not decimal point
                    //move sursor back 2, and print out the numbers
                    fseek(inFile, -2, SEEK_CUR);
                    fprintf(outFile, " (numeric literal)\n");
                    return true; //exit isNum() loop and reloop for the operator ..
                }
                //if decimal then . it will print period then more digits
            }
            //if hashtag then it will print (no case for ##)
            fprintf(outFile, "%c", *c);
            *c = fgetc(inFile);
        }
        fprintf(outFile, " (numeric literal)\n");
        return true;
    }
    return false;
}

/**
 * @brief 
 * @param inFile 
 * @param outFile 
 * @return @param bool 
*/
bool isIdentifiers(FILE *inFile, FILE *outFile, char *c, const char *keywords[]){
    char *build = calloc(266, sizeof(char));
    bool isUnderscoreOrDigit = false;
    if(isalpha(*c)){
        while(isalpha(*c) || *c == '_' || isdigit(*c)){
            strncat(build, c, 1);
            if(isUnderscoreOrDigit || *c == '_' || isdigit(*c)){
                isUnderscoreOrDigit = true;
            }
            *c = fgetc(inFile);
        }
        //append null terminator
        strncat(build, "\0", 1);
        //if there were no underscores or digits, maybe is a keyword, check here
        if(!isUnderscoreOrDigit){
            if(isKeywords(inFile, outFile, build, keywords)){ //if word is a keyword
                free(build);
                return true; //wont finish the rest of the identifier loop
            }
        }
        //if there is an underscore or digit found, then the word is an identifier
        fprintf(outFile, "%s (identifier)\n", build);
        free(build);
        return true;
    }
    free(build);
    return false;
}

/**
 * @brief 
 * @param inFile 
 * @param outFile 
 * @return @param bool 
*/
bool isKeywords(FILE *inFile, FILE *outFile, char *build, const char *keywords[]){
    int length = 37; //length of the list of keywords

    for(int i=0; i<length; ++i){
        if(strncmp(build, keywords[i], strlen(build))){
            fprintf(outFile, "%s (keyword)\n", build);
            return true;
        }
    }
    return false;
}

/**
 * @brief 
 * @param inFile 
 * @param outFile 
 * @param operators 
 * @return @param bool 
*/
bool isOperators(FILE *inFile, FILE *outFile, char *c, const char *operators[]){
    int length = 27; //length of operators

    for(int i=0; i<length; ++i){
        if(*c == operators[i][0]){
            char ch = fgetc(inFile);
            if(ch == operators[i][1]){
                char ch = fgetc(inFile);
                fprintf(outFile, "%c%c (operator)\n", *c, ch);
                return true;
            }
            fseek(inFile, -1,SEEK_CUR);
            fprintf(outFile, "%c (operator)\n", *c);
            return true;
        }
    }
    return false;
}

/**
 * @brief 
 * @param inFile 
 * @param outFile 
 * @return @param bool 
*/
void setUnknown(FILE *inFile, FILE *outFile, char *c){
    fprintf(outFile, "%c (UNK)\n", *c);
    printf("%c (UNK)\n", *c);
}