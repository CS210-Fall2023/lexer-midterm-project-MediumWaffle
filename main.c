#include "lexer.h"

int main(int argc, char* argv[]){

    //list of all the words and symbols I am checking for
    const char *keywords[] = {"accessor", "and", "array", "begin", "bool", "case", "character", "constant", "else", "elsif", "end", "exit", "function","if", "in", "integer", "interface", "is", "loop", "module", "mutator", "natural", "null", "of", "or", "other", "out","positive", "procedure", "range", "return", "struct", "subtype", "then", "type", "when", "while"};
    const char *operators[] = {".", "<", ">", "(", ")", "+", "-", "*", "/", "|", "&", ";", ",", ":", "[", "]", "=", ":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>"};
    
    //assuming passing the file to the lexer will only be passed 1 file at a time through 
    //the arguments of the command line, this is my code.

    //open file (read only)
    //create a file with <name>.lexer (write only)

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
    
    
    return 0;
}