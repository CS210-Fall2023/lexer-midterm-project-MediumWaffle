lexer: main.c lexer.c lexer.h
	gcc *.c -g -Wall -o lexer

clean: 
	rm -r files/*.lexer lexer