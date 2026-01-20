%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include "sintaksno_stablo.hpp"
    #include "parser.tab.hpp"
%}

%%

def {
    return DEF;
}

print {
    return PRINT;
}

== {
    return EQ;
}

[_a-zA-Z][_a-zA-Z0-9]* {
    yylval.niska = new std::string(yytext);
    return ID;
}

[+-]?(0|[1-9][0-9]*)(\.[0-9]*)? {
    yylval.realan_broj = atof(yytext);
    return BROJ;
}

[=;()\-+*] {
    return *yytext;
}

[ \t\n] {

}

. {
    std::cerr << "leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
