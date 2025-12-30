#include "izraz.hpp"
#include <iostream>

/*
Zadatak: Napraviti strukturu podataka za rad sa izrazima koji podrzavaju:
- ispis
- racunanje vrednosti izraca
- racunanje izvoda
Izrazi se sastoje od:
- realnih konstanti
- promenljivih
- funkcija sin i cos
- sabiranja
- mnozenja
*/

int main() {
    // (x + 1) * cos(y)
    Izraz *izraz = new Mnozenje(
        new Sabiranje(
            new Promenljiva("x"),
            new Konstanta(1)
        ),
        new Cos(
            new Promenljiva("y")
        )
    );

    std::cout << *izraz << std::endl;

    TabelaSimbola tabela_simbola;
    tabela_simbola.dodaj_promenljivu("x", 3);
    tabela_simbola.dodaj_promenljivu("y", -2);

    std::cout << izraz->izracunaj(tabela_simbola) << std::endl;

    Izraz *izvod = izraz->izvod("y");
    std::cout << *izvod << std::endl;

    delete izraz;
    delete izvod;
    
    return 0;
}
