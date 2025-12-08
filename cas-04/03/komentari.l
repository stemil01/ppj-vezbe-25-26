%option noyywrap

/* Zadatak: Izbaciti viselinijske komentare u Pascal-u. */

%{
    #include <iostream>
%}

%%

\{[^}]*\} {

}

\(\*([^*]|\*+[^)*])*\*+\) {

}

%%

int main() {
    yylex();
    return 0;
}
