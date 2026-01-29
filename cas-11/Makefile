CC = g++
CFLAGS = -Wall -Wextra

parser: parser.tab.o lex.yy.o tabela_simbola.o sintaksno_stablo.o
	$(CC) $(CFLAGS) $^ -o $@

parser.tab.o: parser.tab.cpp parser.tab.hpp
	$(CC) $(CFLAGS) -c $< -o $@

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c $< -o $@

lex.yy.c: lexer.l parser.tab.hpp
	flex --nounput $<

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison --header $<

tabela_simbola.o: tabela_simbola.cpp tabela_simbola.hpp
	$(CC) $(CFLAGS) -c $< -o $@

sintaksno_stablo.o: sintaksno_stablo.cpp sintaksno_stablo.hpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o lex.yy.c parser.tab.* parser
