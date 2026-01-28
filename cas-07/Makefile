parser: lex.yy.o parser.tab.o kompleksan_broj.o
	g++ lex.yy.o parser.tab.o kompleksan_broj.o -o parser

lex.yy.o: lex.yy.c
	g++ -c lex.yy.c

parser.tab.o: parser.tab.cpp parser.tab.hpp kompleksan_broj.hpp
	g++ -c parser.tab.cpp

lex.yy.c: lexer.l parser.tab.hpp
	flex lexer.l

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison --header parser.ypp

kompleksan_broj.o: kompleksan_broj.cpp kompleksan_broj.hpp
	g++ -c kompleksan_broj.cpp

PHONY: clean
clean:
	rm -f parser.tab.* parser lex.yy.c *.o

