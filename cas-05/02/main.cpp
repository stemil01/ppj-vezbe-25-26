#include <iostream>

#include "dinamicki_niz.hpp"

int main() {
    DinamickiNiz dn1;
    dn1.dodaj(1);
    dn1.dodaj(-4);
    dn1.dodaj(10);
    dn1.dodaj(7);
    dn1.dodaj(9);
    dn1.dodaj(13);

    std::cout << dn1.get_kapacitet() << " " << dn1.get_velicina() << std::endl;
    std::cout << dn1 << std::endl;

    std::cout << dn1.get_kapacitet() << " " << dn1.get_velicina() << std::endl;
    std::cout << dn1 << std::endl;

    return 0;
}
