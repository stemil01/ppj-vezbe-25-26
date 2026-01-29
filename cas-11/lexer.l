%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
    #include "sintaksno_stablo.hpp"
    #include "parser.tab.hpp"
%}

%%

begin {
    return BEGIN_TOKEN;
}

end {
    return END_TOKEN;
}

:= {
    return EQ;
}

print {
    return PRINT;
}

if {
    return IF;
}

then {
    return THEN;
}

else {
    return ELSE;
}

while {
    return WHILE;
}

do {
    return DO;
}

[_a-zA-Z][_a-zA-Z0-9]* {
    yylval.niska = new std::string(yytext);
    return ID;
}

[+-]?(0|[1-9][0-9]*) {
    yylval.ceo_broj = atoi(yytext);
    return BROJ;
}

[;()+\-<>.] {
    return *yytext;
}

[ \t\n] {

}

. {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
