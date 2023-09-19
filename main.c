#include "lexer.h"

int main(int argc, char* argv[]){

    //list of all the words and symbols I am checking for
    const char *keywords[] = {"accessor", "and", "array", "begin", "bool", "case", "character", "constant", "else", "elsif", "end", "exit", "function","if", "in", "integer", "interface", "is", "loop", "module", "mutator", "natural", "null", "of", "or", "other", "out","positive", "procedure", "range", "return", "struct", "subtype", "then", "type", "when", "while"};
    const char *operators[] = {".", "<", ">", "(", ")", "+", "-", "*", "/", "|", "&", ";", ",", ":", "[", "]", "=", ":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>"};
    
    //assuming passing the file to the lexer will only be passed 1 file at a time through 
    //the arguments of the command line, this is the code.

    
    char *filename = calloc((strlen(argv[1])+8), sizeof(char)); //set the file to the 1st argument (the +8 is for ".lexer\0")
    strcpy(filename, (argv[1]+6));
    printf("%s\n", filename);
    char *fileExtension = ".lexer";
    FILE *inFile = fopen(filename, "r"); //opens the file for readin, file must exist
    strcat(filename, fileExtension); //set filename to <name>.lexer
    printf("%s\n", filename);
    FILE *outFile = fopen(filename, "w"); //create a file with <name>.lexer (write only)

    if(inFile == NULL){
        printf("Error, Input file not found\n");
        exit(0);
    }
    if(outFile == NULL){
        printf("Error, Output file not made\n");
        exit(0);
    }
    

    //check if the beginning of any files isSpace();
    
    //read a character, and check it between operators
        //if no match for an operator, then reset reading position and read again. 
        //if the size of the operator is more than 1, read more than 1 character
            //if match is made, jump into function made for handling that operator
                //write result to <name>.lexer
    
    //if no match for operators, read characters
        //if match is made, then jump into function to handle it
            //classify it as 1 of the 8 categories
                //write result to <name>.lexer

    //if no match is made for operators or keywords, then label UNKOWN
        //write the string from start til isSpace()
        //write UNK category
    
    fclose(inFile);
    fclose(outFile);
    free(filename); //deallocate memory
    return 0;
}