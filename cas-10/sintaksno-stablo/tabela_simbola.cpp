#include "tabela_simbola.hpp"
#include <cstdlib>

TabelaSimbola::~TabelaSimbola() {
    for (auto p : m_tabela) {
        delete p.second;
    }
}

void TabelaSimbola::dodeli_vrednost(const std::string &id, Funkcija *funkcija) {
    if (m_tabela.find(id) != m_tabela.end()) {
        delete m_tabela[id];
    }
    m_tabela[id] = funkcija;
}

Funkcija *TabelaSimbola::vrednost_promenljive(const std::string &id) const {
    if (m_tabela.find(id) == m_tabela.end()) {
        std::cerr << "Promenljiva " << id << " nije definisana" << std::endl;
        exit(EXIT_FAILURE);
    }
    return m_tabela.at(id);
}
