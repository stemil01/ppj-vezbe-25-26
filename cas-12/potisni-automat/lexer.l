%option noyywrap
%option nounput
%option noinput

%{
    #include <iostream>
    #include <cstdlib>
    #include "tokeni.hpp"
%}

%%

print {
    return PRINT;
}

0|[1-9][0-9]* {
    return BROJ;
}

[_a-zA-Z][_a-zA-Z0-9]* {
    return ID;
}

[+*()=;] {
    return *yytext;
}

[ \t\n] {

}

. {
    std::cerr << "Leksicka greska: " << yytext << std::endl;
    exit(EXIT_FAILURE);
}

%%
