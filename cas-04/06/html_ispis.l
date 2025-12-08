%option noyywrap

/* Zadatak: Od izvodrnog C fajla napraviti HTML fajl koji boji odgovarajuce reci u zavistnosti od njihove kategorije (pogledati `primer.html`) */

%{
    #include <iostream>

    void ispisi_nisku(FILE *out, char *niska) {
        for (int i = 0; niska[i] != '\0'; i++) {
            if (niska[i] == '\n') {
                fprintf(out, "<br>");
            }
            else if (niska[i] == '<') {
                fprintf(out, "&lt;");
            }
            else if (niska[i] == '>') {
                fprintf(out, "&gt;");
            }
            else if (niska[i] == ' ') {
                fprintf(out, "&nbsp;");
            }
            else {
                fprintf(out, "%c", niska[i]);
            }
        }
    }
%}

PR_BROJ 0|[1-9][0-9]*

%%

#(.|\\\n)* {
    fprintf(yyout, "<span style=\"color: purple;\">");
    ispisi_nisku(yyout, yytext);
    fprintf(yyout, "</span>");
}

\/\/.* {
    fprintf(yyout, "<span style=\"color: green;\">%s</span>", yytext);
}

[+-]?{PR_BROJ}(\.[0-9]*([eE][+-]?{PR_BROJ}))? {
    fprintf(yyout, "<span style=\"color: red;\">");
    ispisi_nisku(yyout, yytext);
    fprintf(yyout, "</span>");
}

\/\*([^*]|\*+[^\/*])*\*+\/ {
    fprintf(yyout, "<span style=\"color: green;\">");
    ispisi_nisku(yyout, yytext);
    fprintf(yyout, "</span>");
}

\"(\\\"|[^"])*\" {
    fprintf(yyout, "<span style=\"color: orange;\">");
    ispisi_nisku(yyout, yytext);
    fprintf(yyout, "</span>");
}

if|else|int|const|char|double {
    fprintf(yyout, "<span style=\"color: blue;\">%s</span>", yytext);
}

[_a-zA-Z][_a-zA-Z0-9]* {
    fprintf(yyout, "<span style=\"color: black;\">%s</span>", yytext);
}

[ ();{},=+><*\n] {
    fprintf(yyout, "<span style=\"color: gray;\">");
    ispisi_nisku(yyout, yytext);
    fprintf(yyout, "</span>");
}

. {

}

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            std::cerr << "greska prilikom otvaranja fajla za citanje" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else {
        yyin = stdin;
    }
    if (argc > 2) {
        yyout = fopen(argv[2], "w");
        if (yyout == NULL) {
            std::cerr << "greska prilikom otvaranja fajla za pisanje" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else {
        yyout = stdout;
    }

    fprintf(yyout, "<html>\n");
    yylex();
    fprintf(yyout, "</html>\n");

    if (yyin != stdin) {
        fclose(yyin);
    }
    if (yyout != stdout) {
        fclose(yyout);
    }

    yylex_destroy();
    return 0;
}
