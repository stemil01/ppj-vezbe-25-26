CC = g++
CFLAGS = -Wall -Wextra

parser: parser.o lex.yy.o
	$(CC) $(CFLAGS) $^ -o $@

lex.yy.c: lexer.l tokeni.hpp
	flex $<

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c $< -o $@

parser.o: parser.cpp tokeni.hpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f parser *.o lex.yy.*
