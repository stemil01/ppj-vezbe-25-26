%option noyywrap

/* Zadatak: Izbaciti viselinijske komentare u C-u i izbrojati koliko nezakomentarisanih redova ima ulazni fajl. */

%{
    #include <iostream>

    int broj_redova = 0;
%}

%x KOMENTAR

%%

\/\* {
    BEGIN(KOMENTAR);
}

<KOMENTAR>.|\n {

}

<KOMENTAR>\*\/ {
    BEGIN(INITIAL);
}

<INITIAL>\n {
    broj_redova++;
}

%%

int main() {
    yylex();
    std::cout << broj_redova << std::endl;
    return 0;
}
