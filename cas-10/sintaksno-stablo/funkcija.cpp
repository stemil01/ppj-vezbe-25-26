#include "funkcija.hpp"
#include <cmath>

// ---------------------------------

Funkcija::~Funkcija() {}

std::ostream &operator<<(std::ostream &os, const Funkcija &izraz) {
    izraz.ispisi(os);
    return os;
}

// ---------------------------------

KonstantnaFunkcija::KonstantnaFunkcija(double vrednost)
    : m_vrednost(vrednost) {}

void KonstantnaFunkcija::ispisi(std::ostream &os) const {
    os << m_vrednost;
}

double KonstantnaFunkcija::izracunaj(double vrednost) const {
    return m_vrednost;
}

Funkcija *KonstantnaFunkcija::komponuj(Funkcija *funkcija) const {
    return kloniraj();
}

Funkcija *KonstantnaFunkcija::izvod() const {
    return new KonstantnaFunkcija(0);
}

Funkcija *KonstantnaFunkcija::kloniraj() const {
    return new KonstantnaFunkcija(*this);
}

// ---------------------------------

void IdentickaFunkcija::ispisi(std::ostream &os) const {
    os << "x";
}

double IdentickaFunkcija::izracunaj(double vrednost) const {
    return vrednost;
}

Funkcija *IdentickaFunkcija::izvod() const {
    return new KonstantnaFunkcija(1);
}

Funkcija *IdentickaFunkcija::komponuj(Funkcija *funkcija) const {
    return funkcija->kloniraj();
}

Funkcija *IdentickaFunkcija::kloniraj() const {
    return new IdentickaFunkcija(*this);
}

// ---------------------------------

UnarnaFunkcija::UnarnaFunkcija(Funkcija *izraz)
    : m_funkcija(izraz) {}

UnarnaFunkcija::UnarnaFunkcija(const UnarnaFunkcija &drugi) {
    m_funkcija = drugi.m_funkcija->kloniraj();
}

UnarnaFunkcija::~UnarnaFunkcija() {
    delete m_funkcija;
}

// ---------------------------------

SinFunkcija::SinFunkcija(Funkcija *izraz) : UnarnaFunkcija(izraz) {}

void SinFunkcija::ispisi(std::ostream &os) const {
    os << "sin(" << *m_funkcija << ")";
}

double SinFunkcija::izracunaj(double vrednost) const {
    return std::sin(m_funkcija->izracunaj(vrednost));
}

Funkcija *SinFunkcija::izvod() const {
    // sin(izraz)' = cos(izraz) * izraz'
    return new MnozenjeFunkcija(
        new CosFunkcija(m_funkcija->kloniraj()),
        m_funkcija->izvod()
    );
}

Funkcija *SinFunkcija::komponuj(Funkcija *funkcija) const {
    return new SinFunkcija(m_funkcija->komponuj(funkcija));
}

Funkcija *SinFunkcija::kloniraj() const {
    return new SinFunkcija(*this);
}

// ---------------------------------

CosFunkcija::CosFunkcija(Funkcija *izraz) : UnarnaFunkcija(izraz) {}

void CosFunkcija::ispisi(std::ostream &os) const {
    os << "cos(" << *m_funkcija << ")";
}

double CosFunkcija::izracunaj(double vrednost) const {
    return std::cos(m_funkcija->izracunaj(vrednost));
}

Funkcija *CosFunkcija::izvod() const {
    // cos(izraz)' = - sin(izraz) * izraz'
    return new MnozenjeFunkcija(
        new KonstantnaFunkcija(-1),
        new MnozenjeFunkcija(
            new SinFunkcija(m_funkcija->kloniraj()),
            m_funkcija->izvod()
        )
    );
}

Funkcija *CosFunkcija::komponuj(Funkcija *funkcija) const {
    return new CosFunkcija(m_funkcija->komponuj(funkcija));
}

Funkcija *CosFunkcija::kloniraj() const {
    return new CosFunkcija(*this);
}

// ---------------------------------

BinarnaFunkcija::BinarnaFunkcija(Funkcija *levi, Funkcija *desni)
    : m_levi(levi), m_desni(desni) {}

BinarnaFunkcija::BinarnaFunkcija(const BinarnaFunkcija &drugi) {
    m_levi = drugi.m_levi->kloniraj();
    m_desni = drugi.m_desni->kloniraj();
}

BinarnaFunkcija::~BinarnaFunkcija() {
    delete m_levi;
    delete m_desni;
}

// ---------------------------------

SabiranjeFunkcija::SabiranjeFunkcija(Funkcija *levi, Funkcija *desni)
    : BinarnaFunkcija(levi, desni) {}

void SabiranjeFunkcija::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") + (" << *m_desni << ")";
}

double SabiranjeFunkcija::izracunaj(double vrednost) const {
    return m_levi->izracunaj(vrednost) + m_desni->izracunaj(vrednost);
}

Funkcija *SabiranjeFunkcija::izvod() const {
    return new SabiranjeFunkcija(
        m_levi->izvod(),
        m_desni->izvod()
    );
}

Funkcija *SabiranjeFunkcija::komponuj(Funkcija *funkcija) const {
    return new SabiranjeFunkcija(
        m_levi->komponuj(funkcija),
        m_desni->komponuj(funkcija)
    );
}

Funkcija *SabiranjeFunkcija::kloniraj() const {
    return new SabiranjeFunkcija(*this);
}

// ---------------------------------

MnozenjeFunkcija::MnozenjeFunkcija(Funkcija *levi, Funkcija *desni)
    : BinarnaFunkcija(levi, desni) {}

void MnozenjeFunkcija::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") * (" << *m_desni << ")";
}

double MnozenjeFunkcija::izracunaj(double vrednost) const {
    return m_levi->izracunaj(vrednost) * m_desni->izracunaj(vrednost);
}

Funkcija *MnozenjeFunkcija::izvod() const {
    // (f * g)' = f' * g + f * g'
    return new SabiranjeFunkcija(
        new MnozenjeFunkcija(
            m_levi->izvod(),
            m_desni->kloniraj()
        ),
        new MnozenjeFunkcija(
            m_levi->kloniraj(),
            m_desni->izvod()
        )
    );
}

Funkcija *MnozenjeFunkcija::komponuj(Funkcija *funkcija) const {
    return new MnozenjeFunkcija(
        m_levi->komponuj(funkcija),
        m_desni->komponuj(funkcija)
    );
}

Funkcija *MnozenjeFunkcija::kloniraj() const {
    return new MnozenjeFunkcija(*this);
}

// ---------------------------------