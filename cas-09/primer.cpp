#include "sintaksno_stablo.hpp"
#include "tabela_simbola.hpp"

/*
  Primer koriscenja klasa definisanih za sintaksno stablo.
  Ovo sluzi za sticanje osecaja kako se one mogu rucno koristiti
  i njih cemo praviti u akcijama u parseru.
*/

int main() {
    NizNaredbi *niz_naredbi = new NizNaredbi();
    
    // def x = 2.5;
    niz_naredbi->dodaj_naredbu(new Definicija("x", new Konstanta(2.5)));

    // print(x);
    niz_naredbi->dodaj_naredbu(new Ispis(new Promenljiva("x")));

    // x = x * x + 2;
    niz_naredbi->dodaj_naredbu(new Dodela("x",
        new Sabiranje(
            new Mnozenje(new Promenljiva("x"), new Promenljiva("x")),
            new Konstanta(2)
        ))
    );

    // 16.5 == 2 * x;
    niz_naredbi->dodaj_naredbu(new Poredjenje(
        new Konstanta(16.5),
        new Mnozenje(new Konstanta(2), new Promenljiva("x"))
    ));

    std::cout << *niz_naredbi << std::endl;

    TabelaSimbola tabela_simbola;
    niz_naredbi->interpretiraj(tabela_simbola);

    delete niz_naredbi;

    return 0;
}
