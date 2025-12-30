#include "izraz.hpp"
#include <cstdlib>
#include <cmath>

void TabelaSimbola::dodaj_promenljivu(const std::string &id, double vrednost) {
    m_promenljive[id] = vrednost;
}

double TabelaSimbola::vrednost_promenljive(const std::string &id) const {
    if (m_promenljive.find(id) == m_promenljive.end()) {
        std::cerr << "promenljiva " << id << " nije definisana" << std::endl;
        exit(EXIT_FAILURE);
    }
    return m_promenljive.at(id);
}

Izraz::~Izraz() {}

std::ostream &operator<<(std::ostream &os, const Izraz &izraz) {
    izraz.ispisi(os);
    return os;
}

// ---------------------------------

Konstanta::Konstanta(double vrednost)
    : m_vrednost(vrednost) {}

void Konstanta::ispisi(std::ostream &os) const {
    os << m_vrednost;
}

double Konstanta::izracunaj(TabelaSimbola &tabela_simbola) const {
    return m_vrednost;
}

Izraz *Konstanta::izvod(const std::string &promenljiva) const {
    return new Konstanta(0);
}

Izraz *Konstanta::kloniraj() const {
    return new Konstanta(*this);
}

// ---------------------------------

Promenljiva::Promenljiva(const std::string &id)
    : m_id(id) {}

void Promenljiva::ispisi(std::ostream &os) const {
    os << m_id;
}

double Promenljiva::izracunaj(TabelaSimbola &tabela_simbola) const {
    return tabela_simbola.vrednost_promenljive(m_id);
}

Izraz *Promenljiva::izvod(const std::string &promenljiva) const {
    return (m_id == promenljiva) ? new Konstanta(1) : new Konstanta(0);
}

Izraz *Promenljiva::kloniraj() const {
    return new Promenljiva(*this);
}

// ---------------------------------

UnarniIzraz::UnarniIzraz(Izraz *izraz)
    : m_izraz(izraz) {}

UnarniIzraz::UnarniIzraz(const UnarniIzraz &drugi) {
    m_izraz = drugi.m_izraz->kloniraj();
}

UnarniIzraz::~UnarniIzraz() {
    delete m_izraz;
}

// ---------------------------------

Sin::Sin(Izraz *izraz) : UnarniIzraz(izraz) {}

void Sin::ispisi(std::ostream &os) const {
    os << "sin(" << *m_izraz << ")";
}

double Sin::izracunaj(TabelaSimbola &tabela_simbola) const {
    return std::sin(m_izraz->izracunaj(tabela_simbola));
}

Izraz *Sin::izvod(const std::string &promenljiva) const {
    // sin(izraz)' = cos(izraz) * izraz'
    return new Mnozenje(
        new Cos(m_izraz->kloniraj()),
        m_izraz->izvod(promenljiva)
    );
}

Izraz *Sin::kloniraj() const {
    return new Sin(*this);
}

// ---------------------------------

Cos::Cos(Izraz *izraz) : UnarniIzraz(izraz) {}

void Cos::ispisi(std::ostream &os) const {
    os << "cos(" << *m_izraz << ")";
}

double Cos::izracunaj(TabelaSimbola &tabela_simbola) const {
    return std::cos(m_izraz->izracunaj(tabela_simbola));
}

Izraz *Cos::izvod(const std::string &promenljiva) const {
    // cos(izraz)' = - sin(izraz) * izraz'
    return new Mnozenje(
        new Konstanta(-1),
        new Mnozenje(
            new Sin(m_izraz->kloniraj()),
            m_izraz->izvod(promenljiva)
        )
    );
}

Izraz *Cos::kloniraj() const {
    return new Cos(*this);
}

// ---------------------------------

BinarniIzraz::BinarniIzraz(Izraz *levi, Izraz *desni)
    : m_levi(levi), m_desni(desni) {}

BinarniIzraz::BinarniIzraz(const BinarniIzraz &drugi) {
    m_levi = drugi.m_levi->kloniraj();
    m_desni = drugi.m_desni->kloniraj();
}

BinarniIzraz::~BinarniIzraz() {
    delete m_levi;
    delete m_desni;
}

// ---------------------------------

Sabiranje::Sabiranje(Izraz *levi, Izraz *desni)
    : BinarniIzraz(levi, desni) {}

void Sabiranje::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") + (" << *m_desni << ")";
}

double Sabiranje::izracunaj(TabelaSimbola &tabela_simbola) const {
    return m_levi->izracunaj(tabela_simbola) + m_desni->izracunaj(tabela_simbola);
}

Izraz *Sabiranje::izvod(const std::string &promenljiva) const {
    return new Sabiranje(
        m_levi->izvod(promenljiva),
        m_desni->izvod(promenljiva)
    );
}

Izraz *Sabiranje::kloniraj() const {
    return new Sabiranje(*this);
}

// ---------------------------------

Mnozenje::Mnozenje(Izraz *levi, Izraz *desni)
    : BinarniIzraz(levi, desni) {}

void Mnozenje::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") * (" << *m_desni << ")";
}

double Mnozenje::izracunaj(TabelaSimbola &tabela_simbola) const {
    return m_levi->izracunaj(tabela_simbola) * m_desni->izracunaj(tabela_simbola);
}

Izraz *Mnozenje::izvod(const std::string &promenljiva) const {
    // (f * g)' = f' * g + f * g'
    return new Sabiranje(
        new Mnozenje(
            m_levi->izvod(promenljiva),
            m_desni->kloniraj()
        ),
        new Mnozenje(
            m_levi->kloniraj(),
            m_desni->izvod(promenljiva)
        )
    );
}

Izraz *Mnozenje::kloniraj() const {
    return new Mnozenje(*this);
}

// ---------------------------------