#ifndef TABELA_SIMBOLA_HPP
#define TABELA_SIMBOLA_HPP

#include <iostream>
#include <map>

class TabelaSimbola {
public:
    void dodeli_vrednost(const std::string &id, int vrednost);
    int vrednost_promenljive(const std::string &id) const;

private:
    std::map<std::string, int> m_tabela;
};

#endif
