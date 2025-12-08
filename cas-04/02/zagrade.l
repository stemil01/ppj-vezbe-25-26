%option noyywrap

/* Zadatak: Proveriti da li su zagrade na ulazu dobro uparene. */

%{
    #include <iostream>

    int broj_otvorenih = 0;
%}

%%

\( {
    broj_otvorenih++;
}

")" {
    broj_otvorenih--;
    if (broj_otvorenih < 0) {
        return -1;
    }
}

%%

int main() {
    int povratna_vrednost = yylex();
    if (povratna_vrednost == 0 && broj_otvorenih == 0) {
        std::cout << "dobro su uparene" << std::endl;
    }
    else {
        std::cout << "nisu dobro uparene" << std::endl;
    }
    return 0;
}
