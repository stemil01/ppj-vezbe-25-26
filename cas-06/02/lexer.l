%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include "parser.tab.hpp"
%}

%%

print {
    return PRINT;
}

[a-zA-Z_][a-zA-Z_0-9]* {
    yylval.niska = new std::string(yytext);
    return ID;
}

0|[1-9][0-9]* {
    yylval.ceo_broj = atoi(yytext);
    return BROJ;
}

[=+*\-/();] {
    return *yytext;
}

[ \t\n] {

}

. {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
