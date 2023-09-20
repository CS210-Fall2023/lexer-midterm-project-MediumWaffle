#include "lexer.h"

//how to handle classifications

    int checkComment(FILE *inFile, FILE *outFile){}
    //comment
        //starts with /*
        //read until ending character / is found
        //write the comment as you go
        //when finished write (comment) then newline

    int checkString(FILE *inFile, FILE *outFile){}
    //string
        //starts with "
        //read until ending character " is found
        //make sure current read in character is after "
        //write the string as you go
        //when finished write (string) then newline

    int checkChar(FILE *inFile, FILE *outFile){}
    //character literal
        //starts with a '
        //read the next single character
        //ends with a '
        //write out the character surrounded by the single quotes
        //then write out (character literal) then newline

    int checkNum(FILE *inFile, FILE *outFile){}
    //numeric literal
        //read in character
        //if that character is between the range of 48-57 then it's a number
        //keep reading numbers until either a . or a # is found
            //if . then check +1 to see if next is another .
                //if no then its decimal number, keep reading numbers (2 lines up ^^)
                //if yes then its an operator
                    //print number, (numeric literal), newline
                    //then go to operator loop
            //if # then read more numbers til isSpace() is found
            //afterwards print number, (numeric literal), newline

    int checkOperators(FILE *inFile, FILE *outFile){}
    //operator
        //read until space is found
            //build a word as you go
        //when space is reached the word is finished building
        //append a null terminating character onto the word
        //check size of word
            //if 1 then check for operators[0-16]
            //if 2 then check for operators[17-26]
        //compare 'word' to 'words' in operators list
            //if a match is made, print out word, (operator), and newline

    int checkIdentifiers(FILE *inFile, FILE *outFile){}
    //identifier
        //check if character is a letter (65-90, 97-122)
        //characters after that can be: 
            //letters (65-90, 97-122), digits (48-57), or underscore (95)
                //if they are not found, check word against keywords first
                    //if comes back as not a keyword, then its an identifier
                //if digit or underscore is found, then word is an identifier
        //if the word is an identifier then write word, (identifier), newline

    int checkKeywords(FILE *inFile, FILE *outFile){}
    //keyword
        //read characters until space
            //build a word as you go
        //when space is reached, word is finished building
        //append null terminating character onto word
        //compare word to other words in the keywords list
            //if a match is made then write the word, (keyword), and newline

    void setUnknown(FILE *inFile, FILE *outFile){}
    //unkown
        //if no classification was given to the chosen word, then put it here
        //print out thr word, (UNK), newline

/*
33-47 -   operators
58-64 -   operators
91-96 -   operators
123-126 - operators
48-57 -   numbers 0-9
65-90 -   letters
97-122 -  letters
*/