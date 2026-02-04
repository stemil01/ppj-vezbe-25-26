#include <iostream>
#include <cstdlib>
#include <stack>
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

#define NN      1001
#define NNp     1002
#define N       1003
#define E       1004
#define Ep      1005
#define T       1006
#define Tp      1007
#define F       1008

int preduvid;
std::stack<int> stek;

void greska(const std::string &poruka) {
    std::cerr << poruka << std::endl;
    exit(EXIT_FAILURE);
}

int main() {
    preduvid = yylex();
    stek.push(NN);

    while (!stek.empty()) {
        int top = stek.top();
        stek.pop();

        switch (top) {
            case NN:
                if (preduvid == ID || preduvid == PRINT) {
#ifdef DEBUG
                    std::cout << "NN => N NN'" << std::endl;
#endif
                    stek.push(NNp);
                    stek.push(N);
                }
                else {
                    greska("NN ocekuje: id, print");
                }
                break;
            case NNp:
                if (preduvid == ID || preduvid == PRINT) {
#ifdef DEBUG
                    std::cout << "NN' => N NN'" << std::endl;
#endif
                    stek.push(NNp);
                    stek.push(N);
                }
                else if (preduvid == EOI) {
#ifdef DEBUG
                    std::cout << "NN' => eps" << std::endl;
#endif
                }
                else {
                    greska("NN' ocekuje: id, print, EOI");
                }
                break;
            case N:
                if (preduvid == ID) {
#ifdef DEBUG
                    std::cout << "N => id = E ;" << std::endl;
#endif
                    stek.push(';');
                    stek.push(E);
                    stek.push('=');
                    stek.push(ID);
                }
                else if (preduvid == PRINT) {
#ifdef DEBUG
                    std::cout << "N => print ( E ) ;" << std::endl;
#endif
                    stek.push(';');
                    stek.push(')');
                    stek.push(E);
                    stek.push('(');
                    stek.push(PRINT);
                }
                else {
                    greska("N ocekuje: id, print");
                }
                break;
            case E:
                if (preduvid == '(' || preduvid == ID || preduvid == BROJ) {
#ifdef DEBUG
                    std::cout << "E => T E'" << std::endl;
#endif
                    stek.push(Ep);
                    stek.push(T);
                }
                else {
                    greska("E ocekuje: (, id, broj");
                }
                break;
            case Ep:
                if(preduvid == '+') {
#ifdef DEBUG
                   std::cout << "E' => + T E'" << std::endl;
#endif
                   stek.push(Ep);
                   stek.push(T);
                   stek.push('+');
                }
                else if (preduvid == ';' || preduvid == ')') {
#ifdef DEBUG
                   std::cout << "E' => eps" << std::endl;
#endif
                }
                else {
                    greska("E' ocekuje: +, ;, )");
                }
                break;
            case T:
                if (preduvid == '(' || preduvid == ID || preduvid == BROJ) {
#ifdef DEBUG
                    std::cout << "T => F T'" << std::endl;
#endif
                    stek.push(Tp);
                    stek.push(F);
                }
                else {
                    greska("T ocekuje: (, id, broj");
                }
                break;
            case Tp:
                if (preduvid == '*') {
#ifdef DEBUG
                    std::cout << "T' => * F T'" << std::endl;
#endif
                    stek.push(Tp);
                    stek.push(F);
                    stek.push('*');
                }
                else if (preduvid == ';' || preduvid == ')' || preduvid == '+') {
#ifdef DEBUG
                    std::cout << "T' => eps" << std::endl;
#endif
                }
                else {
                    greska("T' ocekuje: *, ;, ), +");
                }
                break;
            case F:
                if (preduvid == '(') {
#ifdef DEBUG
                    std::cout << "F => ( E )" << std::endl;
#endif
                    stek.push(')');
                    stek.push(E);
                    stek.push('(');
                }
                else if (preduvid == ID) {
#ifdef DEBUG
                    std::cout << "F => id" << std::endl;
#endif
                    stek.push(ID);
                }
                else if (preduvid == BROJ) {
#ifdef DEBUG
                    std::cout << "F => broj" << std::endl;
#endif
                    stek.push(BROJ);
                }
                else {
                    greska("F ocekuje: (, id, broj");
                }
                break;
            default:
                if (top != preduvid) {
                    greska("Vrh steka nije jednak preduvidu.");
                }
                preduvid = yylex();
                break;
        }
    }

    std::cout << "prihvaceno" << std::endl;

    return 0;
}

