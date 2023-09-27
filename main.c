/**
 * @name Aaron Jarnes
 * @date 9/27/23
 * @brief This program is designed to be a lexical analyzer. 
 *        Reading from other files and breaking apart each character, 
 *        each word, into a list of 8 classifications. 
    *        1. Comment (/* HELLO WORLD * /)
    *        2. String ("HELLO WORLD")
    *        3. Character Literal ('H')
    *        4. Numeric Literal (60 or 52.3 or 32#54#)
    *        5. Identifiers (hello_world)
    *        6. Operators (+=;)
    *        7. Keywords (const int)
    *        8. Unknown (used to classify any errors the program caught)
 *        Afterwards the program will write the output to a new file labeled as the <filename>.lexer
 *        The output file holds the lexical analasys of the input file
 * @param argc To check the argument count. If the count is too low or too high, 
 *             the correct files may not have been inputted and an error will occur. 
 * @param argv Holds the command line arguments. Used to open the input file and create an output file
*/
#include "lexer.h"

int main(int argc, char* argv[]){

    if (argc == 1){
        printf("Error, no input file was detected.\n");
        exit(0);
    }
    if (argc > 2){
        printf("Error, too many arguments. Please input only 1 file name\n");
        exit(0);
    }

    //list of all the words and symbols I am checking for
    const char *keywords[] = {"accessor", "and", "array", "begin", "bool", "case", "character", "constant", "else", "elsif", "end", "exit", "function","if", "in", "integer", "interface", "is", "loop", "module", "mutator", "natural", "null", "of", "or", "other", "out","positive", "procedure", "range", "return", "struct", "subtype", "then", "type", "when", "while"};
    const char *operators[] = {":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>", ".", "<", ">", "(", ")", "+", "-", "*", "/", "|", "&", ";", ",", ":", "[", "]", "="};

    
    char *filename = calloc((strlen(argv[1])+8), sizeof(char)); //set the file to the 1st argument (the +8 is for ".lexer\0")
    strcpy(filename, argv[1]);
    char *fileExtension = ".lexer";
    FILE *inFile = fopen(argv[1], "r"); //opens the file for readin, file must exist
    strcat(filename, fileExtension); //set filename to <name>.lexer
    FILE *outFile = fopen(filename, "w"); //create a file with <name>.lexer (write only)

    if(inFile == NULL){
        printf("Error, Input file not found\n");
        exit(0);
    }
    if(outFile == NULL){
        printf("Error, Output file not made\n");
        exit(0);
    }
    
    //Main loop. Grap characters, check them with specific functions. 
    char c;
    while((c = fgetc(inFile)) != EOF){
        if(isspace(c)){} //if any whitespace is detected, then loop for next char instead
        else if(isComment(inFile, outFile, &c)){}
        else if(isString(inFile, outFile, &c)){}
        else if(isChar(inFile, outFile, &c)){}
        else if(isNum(inFile, outFile, &c)){}
        else if(isIdentifiers(inFile, outFile, &c, keywords)){} //this function will call isKeywords()
        else if(isOperators(inFile, outFile, &c, operators)){}
        else {setUnknown(inFile, outFile, &c);}
    }
    
    //when done, close files and free memory
    fclose(inFile);
    fclose(outFile);
    free(filename);
    return 0;
}