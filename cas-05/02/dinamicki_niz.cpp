#include "dinamicki_niz.hpp"
#include <cstdlib>

DinamickiNiz::DinamickiNiz() {
    m_kapacitet = 5;
    m_velicina = 0;
    m_niz = new int[m_kapacitet];
}

DinamickiNiz::DinamickiNiz(int velicina, int vrednost) {
    m_kapacitet = velicina;
    m_velicina = velicina;
    m_niz = new int[m_kapacitet];
}

DinamickiNiz::DinamickiNiz(const DinamickiNiz &drugi) {
    m_kapacitet = drugi.m_kapacitet;
    m_velicina = drugi.m_velicina;
    
    m_niz = new int[m_kapacitet];
    for (int i = 0; i < m_velicina; i++) {
        m_niz[i] = drugi.m_niz[i];
    }
}

DinamickiNiz::~DinamickiNiz() {
    delete[] m_niz;
}

DinamickiNiz &DinamickiNiz::operator=(const DinamickiNiz &drugi) {
    if (this != &drugi) {
        m_kapacitet = drugi.m_kapacitet;
        m_velicina = drugi.m_velicina;
        
        delete[] m_niz;
        m_niz = new int[m_kapacitet];
        for (int i = 0; i < m_velicina; i++) {
            m_niz[i] = drugi.m_niz[i];
        }
    }

    return *this;
}

int DinamickiNiz::get_velicina() const {
    return m_velicina;
}

int DinamickiNiz::get_kapacitet() const {
    return m_kapacitet;
}

void DinamickiNiz::dodaj(int vrednost) {
    if (m_velicina == m_kapacitet) {
        m_kapacitet *= 2;
        int *novi_niz = new int[m_kapacitet];
        for (int i = 0; i < m_velicina; i++) {
            novi_niz[i] = m_niz[i];
        }
        delete[] m_niz;
        m_niz = novi_niz;
    }

    m_niz[m_velicina] = vrednost;
    m_velicina++;
}

int DinamickiNiz::operator[](int i) const {
    if (i < 0 || i >= m_velicina) {
        std::cerr << "pogresne granice za indeks" << std::endl;
        exit(EXIT_FAILURE);
    }
    return m_niz[i];
}

std::ostream &operator<<(std::ostream &os, const DinamickiNiz &dn) {
    for (int i = 0; i < dn.get_velicina(); i++) {
        os << dn[i] << " ";
    }
    return os;
}
