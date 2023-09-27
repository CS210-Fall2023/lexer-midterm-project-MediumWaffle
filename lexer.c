/**
 * @name Aaron Jarnes
 * @date 9/27/23
 * @brief This is the function file. It holds all the function my program uses to 
 *        lexically analyze the input file. Most of these programs use the input file, 
 *        output file, and a character grabbed from the input to check from. 
 *        If a check is made successful, the function will return true and the output is 
 *        written to the output file.  
*/
#include "lexer.h"

/**
 * @brief Takes the input char C and checks it for '/' if so, 
 *        grab another character then check if it's '*', 
 *        if not its just the operator /, 
 *        if it had /* then read until you get the ending character /. 
 *        Afterwards post the comment and print (comment)
 * @param inFile File in which the program reads from to analyze lexically
 * @param outFile File in which the program writes the analasys to.
 * @param c character grabbed from the input file to check from
 * @return @param bool typedefined to return true or false if the check was sucessful or not
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
 * @brief check the input file for the " symbol, if so then read until you find the ending symbol ", 
 *        afterwards output the string literal to the outputfile and print (string)
 * @param inFile File in which the program reads from to analyze lexically
 * @param outFile File in which the program writes the analasys to.
 * @param c character grabbed from the input file to check from
 * @return @param bool typedefined to return true or false if the check was sucessful or not
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
 * @brief Checks the input character for the symbol ', 
 *        if found then the next letter is a character literal. 
 *        Just read it and the ending ' afterwards print (character literal) to the screen
 * @param inFile File in which the program reads from to analyze lexically
 * @param outFile File in which the program writes the analasys to.
 * @param c character grabbed from the input file to check from
 * @return @param bool typedefined to return true or false if the check was sucessful or not
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
 * @brief checks the first character read for a digit by using the isdigit() funcion. 
 *        If the character is a digit, keep reading and writing characters that are either digits, 
 *        periods, or pound symbols. If it is a period, then the check to see if its supposed to be a 
 *        decimal number or the .. operator. Afterwards print (numeric literal).
 * @param inFile File in which the program reads from to analyze lexically
 * @param outFile File in which the program writes the analasys to.
 * @param c character grabbed from the input file to check from
 * @return @param bool typedefined to return true or false if the check was sucessful or not
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
        fseek(inFile, -1, SEEK_CUR);
        fprintf(outFile, " (numeric literal)\n");
        return true;
    }
    return false;
}

/**
 * @brief checks if the first character is a letter by ising isalpha(). 
 *        Afterwards then check letters after it for alpha, underscore, or digits. 
 *        When finished, if there were no underscores or digits in the word, 
 *        the word could be a keyword and it will call the isKeyword() function. 
 *        If not then it is an identifier and print out (identifier).
 * @param inFile File in which the program reads from to analyze lexically
 * @param outFile File in which the program writes the analasys to.
 * @param c character grabbed from the input file to check from
 * @param keywords list of keywords to check against, if match is made, then the word is a keyword
 * @return @param bool typedefined to return true or false if the check was sucessful or not
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
        fseek(inFile, -1, SEEK_CUR); //always grabs 1 too many characters for check
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
 * @brief checks the word build from the isIdentifier() function. 
 *        If the word matches with any of the list of keywords, then the word is a keyword, 
 *        print it to output file and print (keyword).
 * @param inFile File in which the program reads from to analyze lexically
 * @param outFile File in which the program writes the analasys to.
 * @param c character grabbed from the input file to check from
 * @param keywords list of keywords to check against, if match is made, then the word is a keyword
 * @return @param bool typedefined to return true or false if the check was sucessful or not
*/
bool isKeywords(FILE *inFile, FILE *outFile, char *build, const char *keywords[]){
    int length = 37; //length of the list of keywords
    for(int i=0; i<length; ++i){
        if(!strcmp(build, keywords[i])){
            fprintf(outFile, "%s (keyword)\n", build);
            return true;
        }
    }
    return false;
}

/**
 * @brief Checks the character read if it matches with the first character in the operator list. 
 *        Loop through operator list until a match is made. Check to see if the operator has a size of 2, 
 *        if so then read a character again and check it from the second character in the operator list. 
 *        Keep looping. If operator is found then print it to output file and print (operator)
 * @param inFile File in which the program reads from to analyze lexically
 * @param outFile File in which the program writes the analasys to.
 * @param c character grabbed from the input file to check from
 * @param operators 
 * @return @param bool typedefined to return true or false if the check was sucessful or not
*/
bool isOperators(FILE *inFile, FILE *outFile, char *c, const char *operators[]){
    int length = 27; //length of operators

    for(int i=0; i<length; ++i){
        if(strlen(operators[i]) == 1 && *c == operators[i][0]){
            fprintf(outFile, "%c (operator)\n", *c);
            return true;
        } else if (strlen(operators[i]) == 2 && *c == operators[i][0]){
            char ch = fgetc(inFile);
            if(ch == operators[i][1]){
                fprintf(outFile, "%c%c (operator)\n", *c, ch);
                return true;
            }
            fseek(inFile, -1,SEEK_CUR);
        }
    }
    return false;
}

/**
 * @brief If the function cannot find the correct placement for a character read from a file, 
 *        it will mark it as UNK meaning unknown and the program will loop for the next character. 
 *        (this function should never run unless an issue is happening)
 * @param inFile File in which the program reads from to analyze lexically
 * @param outFile File in which the program writes the analasys to.
 * @return @param bool typedefined to return true or false if the check was sucessful or not
*/
void setUnknown(FILE *inFile, FILE *outFile, char *c){
    fprintf(outFile, "%c (UNK)\n", *c);
    printf("%c (UNK)\n", *c);
}