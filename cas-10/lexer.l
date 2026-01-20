%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include "funkcija.hpp"
    #include "parser.tab.hpp"
%}

%%

sin {
    return SIN;
}

cos {
    return COS;
}

[+*()'\n\[\]=x] {
    return *yytext;
}

[_a-zA-Z][_a-zA-Z0-9]* {
    yylval.niska = new std::string(yytext);
    return ID;
}

[+-]?(0|[1-9][0-9]*)(\.[0-9]*)? {
    yylval.realan_broj = atof(yytext);
    return BROJ;
}

[ \t] {

}

. {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
