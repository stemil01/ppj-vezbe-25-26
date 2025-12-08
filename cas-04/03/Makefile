lexer: lex.yy.c
	g++ lex.yy.c -o lexer

lex.yy.c: komentari.l
	flex komentari.l

.PHONY: clean
clean:
	rm -f lex.yy.c lexer
