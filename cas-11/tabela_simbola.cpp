#include "tabela_simbola.hpp"
#include <cstdlib>

void TabelaSimbola::dodeli_vrednost(const std::string &id, int vrednost) {
    m_tabela[id] = vrednost;
}

int TabelaSimbola::vrednost_promenljive(const std::string &id) const {
    if (m_tabela.find(id) == m_tabela.end()) {
        std::cerr << "Promenljiva " << id << " nije definisana" << std::endl;
        exit(EXIT_FAILURE);
    }
    return m_tabela.at(id);
}
