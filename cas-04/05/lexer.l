%option noyywrap

/* Zadatak: Generisati tabelu simbola tj. napraviti lekser za jezik nalik Pascal-u (primer `test.mpas`). */

%{
    #include <iostream>
    #include <cstdlib>

    #define ID              1
    #define KLJUCNA_REC     2
    #define KONSTANTA       3
    #define SEPARATOR       4
    #define OPERATOR        5
    #define POREDJENJE      6
    #define DODELA          7
%}

%%

var|begin|end|if|then|integer {
    return KLJUCNA_REC;
}

[_a-zA-Z][_a-zA-Z0-9]* {
    return ID;
}

[1-9][0-9]* {
    return KONSTANTA;
}

[:;.] {
    return SEPARATOR;
}

[+\-*/=] {
    return OPERATOR;
}

:= {
    return DODELA;
}

\<=|>= {
    return POREDJENJE;
}

.|\n {

}

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            std::cerr << "greska pri otvaranju fajla za citanje" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else {
        yyin = stdin;
    }

    if (argc > 2) {
        yyout = fopen(argv[2], "w");
        if (yyout == NULL) {
            std::cerr << "greska pri otvaranju fajla za pisanje" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else {
        yyout = stdout;
    }

    int token;
    while (token = yylex()) {
        switch (token) {
            case ID:
                fprintf(yyout, "%s\tID\n", yytext);
                break;
            case KONSTANTA:
                fprintf(yyout, "%s\tKONSTANTA\n", yytext);
                break;
            case KLJUCNA_REC:
                fprintf(yyout, "%s\tKLJUCNA REC\n", yytext);
                break;
            case SEPARATOR:
                fprintf(yyout, "%s\tSEPARATOR\n", yytext);
                break;
            case OPERATOR:
                fprintf(yyout, "%s\tOPERATOR\n", yytext);
                break;
            case DODELA:
                fprintf(yyout, "%s\tDODELA\n", yytext);
                break;
            case POREDJENJE:
                fprintf(yyout, "%s\tPOREDJENJE\n", yytext);
                break;
        }
    }

    if (yyin != stdin) {
        fclose(yyin);
    }
    if (yyout != stdout) {
        fclose(yyout);
    }

    return 0;
}
