#include <cstdlib>
#include <iostream>
#include "tokeni.hpp"

/*
Gramatika (sa skupovima izbora):

NN
    : N NN'             {id, print}

NN'
    : N NN'             {id, print}
    | eps               {EOI}

N
    : id = E ;          {id}
    | print ( E ) ;     {print}

E
    : T E'              {(, id, broj}

E'
    : + T E'            {+}
    | eps               {;, )}

T
    : F T'              {(, id, broj}

T'
    : * F T'            {*}
    | eps               {;, ), +}

F
    : ( E )             {(}
    | id                {id}
    | broj              {broj}

*/

#define DEBUG

extern int yylex();

int preduvid;

void greska(const std::string &poruka) {
    std::cerr << poruka << std::endl;
    exit(EXIT_FAILURE);
}

void NN();
void NNp();
void N();
void E();
void Ep();
void T();
void Tp();
void F();

void NN() {
    if (preduvid == ID || preduvid == PRINT) {
#ifdef DEBUG
        std::cout << "NN => N NN'" << std::endl;
#endif
        N();
        NNp();
    }
    else {
        greska("NN ocekuje: id, print");
    }
}

void NNp() {
    if (preduvid == ID || preduvid == PRINT) {
#ifdef DEBUG
        std::cout << "NN' => N NN'" << std::endl;
#endif
        N();
        NNp();
    }
    else if (preduvid == EOI) {
#ifdef DEBUG
        std::cout << "NN' => eps" << std::endl;
#endif
    }
    else {
        greska("NN' ocekuje: id, print, EOI");
    }
}

void N() {
    if (preduvid == ID) {
#ifdef DEBUG
        std::cout << "N => id = E ;" << std::endl;
#endif
        preduvid = yylex();
        if (preduvid != '=') {
            greska("N ocekuje: =");
        }
        preduvid = yylex();
        E();
        if (preduvid != ';') {
            greska("N ocekuje: ;");
        }
        preduvid = yylex();
    }
    else if (preduvid == PRINT) {
#ifdef DEBUG
        std::cout << "N => print ( E ) ;" << std::endl;
#endif
        preduvid = yylex();
        if (preduvid != '(') {
            greska("N ocekuje: (");
        }
        preduvid = yylex();
        E();
        if (preduvid != ')') {
            greska("N ocekuje: )");
        }
        preduvid = yylex();
        if (preduvid != ';') {
            greska("N ocekuje: ;");
        }
        preduvid = yylex();
    }
    else {
        greska("N ocekuje: id, print");
    }
}

void E() {
    if (preduvid == '(' || preduvid == ID || preduvid == BROJ) {
#ifdef DEBUG
        std::cout << "E => T E'" << std::endl;
#endif
        T();
        Ep();
    }
    else {
        greska("E ocekje: (, id, broj");
    }
}

void Ep() {
    if (preduvid == '+') {
#ifdef DEBUG
        std::cout << "E' => + T E'" << std::endl;
#endif
        preduvid = yylex();
        T();
        Ep();
    }
    else if (preduvid == ';' || preduvid == ')') {
#ifdef DEBUG
        std::cout << "E' => eps" << std::endl;
#endif
    }
    else {
        greska("E' ocekuje: +, ;, )");
    }
}

void T() {
    if (preduvid == '(' || preduvid == ID || preduvid == BROJ) {
#ifdef DEBUG
        std::cout << "T => F T'" << std::endl;
#endif
        F();
        Tp();
    }
    else {
        greska("T ocekuje: (, id, broj");
    }
}

void Tp() {
    if (preduvid == '*') {
#ifdef DEBUG
        std::cout << "T' => * F T'" << std::endl;
#endif
        preduvid = yylex();
        F();
        Tp();
    }
    else if (preduvid == ';' || preduvid == ')' || preduvid == '+') {
#ifdef DEBUG
        std::cout << "T' => eps" << std::endl;
#endif
    }
    else {
        greska("T' ocekuje: *, ;, ), +");
    }
}

void F() {
    if (preduvid == '(') {
#ifdef DEBUG
        std::cout << "F => ( E )" << std::endl;
#endif
        preduvid = yylex();
        E();
        if (preduvid != ')') {
            greska("F ocekuje: )");
        }
        preduvid = yylex();
    }
    else if (preduvid == ID) {
#ifdef DEBUG
        std::cout << "F => id" << std::endl;
#endif
        preduvid = yylex();
    }
    else if (preduvid == BROJ) {
#ifdef DEBUG
        std::cout << "F => broj" << std::endl;
#endif
        preduvid = yylex();
    }
    else {
        greska("F ocekuje: (, id, broj");
    }
}

int main() {
    preduvid = yylex();
    NN();
    if (preduvid == EOI) {
        std::cout << "prihvaceno" << std::endl;
    }
    else {
        std::cout << "nije prihvaceno" << std::endl;
    }
    return 0;
}
