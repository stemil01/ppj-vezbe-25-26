#ifndef DINAMICKI_NIZ_HPP
#define DINAMICKI_NIZ_HPP

#include <iostream>
#include <cstdlib>

class DinamickiNiz {
public:
    DinamickiNiz();
    DinamickiNiz(int velicina, int vrednost);
    DinamickiNiz(const DinamickiNiz &drugi);
    ~DinamickiNiz();

    DinamickiNiz &operator=(const DinamickiNiz &drugi);

    int get_velicina() const;
    int get_kapacitet() const;

    void dodaj(int vrednost);

    int operator[](int i) const;

private:
    int *m_niz;
    int m_kapacitet;
    int m_velicina;
};

std::ostream &operator<<(std::ostream &os, const DinamickiNiz &dn);

#endif
