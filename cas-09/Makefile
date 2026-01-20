parser: parser.tab.o lex.yy.o sintaksno_stablo.o tabela_simbola.o
	g++ -Wall -Wextra parser.tab.o lex.yy.o sintaksno_stablo.o tabela_simbola.o -o parser

parser.tab.o: parser.tab.cpp parser.tab.hpp
	g++ -Wall -Wextra -c parser.tab.cpp -o parser.tab.o

lex.yy.o: lex.yy.c
	g++ -Wall -Wextra -c lex.yy.c -o lex.yy.o

lex.yy.c: lexer.l parser.tab.hpp sintaksno_stablo.hpp
	flex --nounput lexer.l

parser.tab.cpp parser.tab.hpp: parser.ypp sintaksno_stablo.hpp
	bison --header parser.ypp

sintaksno_stablo.o: sintaksno_stablo.cpp sintaksno_stablo.hpp tabela_simbola.hpp
	g++ -Wall -Wextra -c sintaksno_stablo.cpp -o sintaksno_stablo.o

tabela_simbola.o: tabela_simbola.cpp tabela_simbola.hpp
	g++ -Wall -Wextra -c tabela_simbola.cpp -o tabela_simbola.o

.PHONY: clean
clean:
	rm -f *.o lex.yy.c parser.tab.* parser
