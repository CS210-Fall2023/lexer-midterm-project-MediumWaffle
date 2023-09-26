lexer: main.c lexer.c lexer.h
	gcc *.c -g -Wall -o lexer

clean: 
	rm -r files/*.lexer lexer

run:
	./lexer files/complex.cci && ./lexer files/complex.ccx && ./lexer files/date.cci && ./lexer files/date.ccx && ./lexer files/hello_world.ccx && ./lexer files/list.cci && ./lexer files/list.ccx && ./lexer files/natural.cci && ./lexer files/natural.ccx && ./lexer files/trie.cci && ./lexer files/trie.ccx && ./lexer files/widget.cci && ./lexer files/widget.ccx