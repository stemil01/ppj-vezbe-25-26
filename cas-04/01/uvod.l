%option noyywrap

/* Zadatak: Prebrojati broj redova na ulazu. */

%{
    // C++ kod
    #include <iostream>

    int broj_redova = 0;
%}

%%

\n {
    // C++ kod
    broj_redova++;
}

. {
    // ECHO;
}

%%

// C++ kod

int main() {
    yylex();
    std::cout << broj_redova + 1 << std::endl;
    return 0;
}
