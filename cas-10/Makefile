parser: parser.tab.o lex.yy.o tabela_simbola.o funkcija.o
	g++ -Wall -Wextra parser.tab.o lex.yy.o tabela_simbola.o funkcija.o -o parser

parser.tab.o: parser.tab.cpp parser.tab.hpp
	g++ -Wall -Wextra -c parser.tab.cpp -o parser.tab.o

lex.yy.o: lex.yy.c
	g++ -Wall -Wextra -c lex.yy.c -o lex.yy.o

lex.yy.c: lexer.l parser.tab.hpp sintaksno_stablo.hpp
	flex --nounput lexer.l

parser.tab.cpp parser.tab.hpp: parser.ypp sintaksno_stablo.hpp
	bison --header parser.ypp

tabela_simbola.o: tabela_simbola.cpp tabela_simbola.hpp
	g++ -Wall -Wextra -c tabela_simbola.cpp -o tabela_simbola.o

funkcija.o: funkcija.cpp funkcija.hpp
	g++ -Wall -Wextra -c funkcija.cpp -o funkcija.o

.PHONY: clean
clean:
	rm -f *.o lex.yy.c parser.tab.* parser
