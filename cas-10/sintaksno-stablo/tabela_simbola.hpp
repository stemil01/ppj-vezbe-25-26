#ifndef TABELA_SIMBOLA_HPP
#define TABELA_SIMBOLA_HPP

#include "funkcija.hpp"
#include <map>

class TabelaSimbola {
public:
    ~TabelaSimbola();
    void dodeli_vrednost(const std::string &id, Funkcija *funkcija);
    Funkcija *vrednost_promenljive(const std::string &id) const;

private:
    std::map<std::string, Funkcija *> m_tabela;
};

#endif
