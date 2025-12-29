%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include "kompleksan_broj.hpp"
    #include "parser.tab.hpp"
%}

%%

print {
    return PRINT;
}

def {
    return DEF;
}

re {
    return RE;
}

im {
    return IM;
}

arg {
    return ARG;
}

mod {
    return MOD;
}

[_a-zA-Z][_a-zA-Z0-9]* {
    yylval.niska = new std::string(yytext);
    return ID;
}

[+-]?(0|[1-9][0-9]*)(\.[0-9]*)? {
    yylval.realan_broj = atof(yytext);
    return BROJ;
}

[+\-*/();=~<>,] {
    return *yytext;
}

[ \t\n] {

}

. {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
