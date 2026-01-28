%option noyywrap

%{
    #include <iostream>
    #include <cstdlib>
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
    return ID;
}

[+-]?(0|[1-9][0-9]*) {
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
