#include "tabela_simbola.hpp"
#include <cstdlib>
#include <iostream>

void TabelaSimbola::definisi_promenljivu(const std::string &id, double vrednost) {
    if (m_tabela.find(id) != m_tabela.end()) {
        std::cerr << "promenljiva " << id << " je vec definisana" << std::endl;
        exit(EXIT_FAILURE);
    }
    m_tabela[id] = vrednost;
}

void TabelaSimbola::dodeli_vrednost(const std::string &id, double vrednost) {
    if (m_tabela.find(id) == m_tabela.end()) {
        std::cerr << "promenljiva " << id << " nije definisana" << std::endl;
        exit(EXIT_FAILURE);
    }
    m_tabela[id] = vrednost;
}

double TabelaSimbola::vrednost_promenljive(const std::string &id) const {
    if (m_tabela.find(id) == m_tabela.end()) {
        std::cerr << "promenljiva " << id << " nije definisana" << std::endl;
        exit(EXIT_FAILURE);
    }
    return m_tabela.at(id);
}