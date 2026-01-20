#ifndef TABELA_SIMBOLA_HPP
#define TABELA_SIMBOLA_HPP

#include <map>
#include <string>

class TabelaSimbola {
public:
    void definisi_promenljivu(const std::string &id, double vrednost);
    void dodeli_vrednost(const std::string &id, double vrednost);
    double vrednost_promenljive(const std::string &id) const;

private:
    std::map<std::string, double> m_tabela;
};

#endif
