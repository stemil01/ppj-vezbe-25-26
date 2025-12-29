parser: lex.yy.o parser.tab.o
	g++ lex.yy.o parser.tab.o -o parser

lex.yy.o: lex.yy.c
	g++ -c lex.yy.c

parser.tab.o: parser.tab.cpp parser.tab.hpp
	g++ -c parser.tab.cpp

lex.yy.c: lexer.l parser.tab.hpp
	flex lexer.l

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison --header parser.ypp

PHONY: clean
clean:
	rm -f parser.tab.* parser lex.yy.c *.o

