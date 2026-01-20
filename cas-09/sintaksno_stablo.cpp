#include "sintaksno_stablo.hpp"
#include <chrono>
#include <vector>

ASTCvor::~ASTCvor() {}

std::ostream &operator<<(std::ostream &os, const ASTCvor &ast_cvor) {
    ast_cvor.ispisi(os);
    return os;
}

// ---------------------------------------

Promenljiva::Promenljiva(const std::string &id) : m_id(id) {}

double Promenljiva::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return tabela_simbola.vrednost_promenljive(m_id);
}

void Promenljiva::ispisi(std::ostream &os) const {
    os << m_id;
}

ASTCvor *Promenljiva::kloniraj() const {
    return new Promenljiva(*this);
}

// ---------------------------------------

Konstanta::Konstanta(double vrednost)
    : m_vrednost(vrednost) {}

double Konstanta::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return m_vrednost;
}

void Konstanta::ispisi(std::ostream &os) const {
    os << m_vrednost;
}

ASTCvor *Konstanta::kloniraj() const {
    return new Konstanta(*this);
}

// ---------------------------------------

NizNaredbi::NizNaredbi() {}

NizNaredbi::NizNaredbi(const NizNaredbi &drugi) {
    m_naredbe = std::vector<ASTCvor *>(drugi.m_naredbe.size());
    for (size_t i = 0; i < drugi.m_naredbe.size(); i++) {
        m_naredbe[i] = drugi.m_naredbe[i]->kloniraj();
    }
}

NizNaredbi::~NizNaredbi() {
    for (ASTCvor *naredba : m_naredbe) {
        delete naredba;
    }
}

void NizNaredbi::dodaj_naredbu(ASTCvor *naredba) {
    m_naredbe.push_back(naredba);
}

double NizNaredbi::interpretiraj(TabelaSimbola &tabela_simbola) const {
    for (ASTCvor *naredba : m_naredbe) {
        naredba->interpretiraj(tabela_simbola);
    }

    return 0;
}

void NizNaredbi::ispisi(std::ostream &os) const {
    for (ASTCvor *narebda : m_naredbe) {
        os << *narebda << ";\n";
    }
}

ASTCvor *NizNaredbi::kloniraj() const {
    return new NizNaredbi(*this);
}

// ---------------------------------------

Definicija::Definicija(const std::string &id, ASTCvor *izraz)
    : m_id(id), m_izraz(izraz) {}

Definicija::Definicija(const Definicija &drugi) {
    m_id = drugi.m_id;
    m_izraz = drugi.m_izraz->kloniraj();
}

Definicija::~Definicija() {
    delete m_izraz;
}

double Definicija::interpretiraj(TabelaSimbola &tabela_simbola) const {
    double vrednost = m_izraz->interpretiraj(tabela_simbola);
    tabela_simbola.definisi_promenljivu(m_id, vrednost);

    return 0;
}
void Definicija::ispisi(std::ostream &os) const {
    os << "def " << m_id << " = " << *m_izraz;
}

ASTCvor *Definicija::kloniraj() const {
    return new Definicija(*this);
}

// ---------------------------------------

Dodela::Dodela(const std::string &id, ASTCvor *izraz)
    : m_id(id), m_izraz(izraz) {}

Dodela::Dodela(const Dodela &drugi) {
    m_id = drugi.m_id;
    m_izraz = drugi.m_izraz->kloniraj();
}

Dodela::~Dodela() {
    delete m_izraz;
}

double Dodela::interpretiraj(TabelaSimbola &tabela_simbola) const {
    double vrednost = m_izraz->interpretiraj(tabela_simbola);
    tabela_simbola.dodeli_vrednost(m_id, vrednost);

    return 0;
}
void Dodela::ispisi(std::ostream &os) const {
    os << m_id << " = " << *m_izraz;
}

ASTCvor *Dodela::kloniraj() const {
    return new Dodela(*this);
}

// ---------------------------------------

UnarniCvor::UnarniCvor(ASTCvor *cvor)
    : m_cvor(cvor) {}

UnarniCvor::UnarniCvor(const UnarniCvor &drugi) {
    m_cvor = drugi.m_cvor->kloniraj();
}

UnarniCvor::~UnarniCvor() {
    delete m_cvor;
}

// ---------------------------------------

Negacija::Negacija(ASTCvor *cvor)
    : UnarniCvor(cvor) {}

double Negacija::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return - m_cvor->interpretiraj(tabela_simbola);
}

void Negacija::ispisi(std::ostream &os) const {
    os << "- (" << *m_cvor << ")";
}

ASTCvor *Negacija::kloniraj() const {
    return new Negacija(*this);
}

// ---------------------------------------

Ispis::Ispis(ASTCvor *cvor)
    : UnarniCvor(cvor) {}

double Ispis::interpretiraj(TabelaSimbola &tabela_simbola) const {
    double vrednost = m_cvor->interpretiraj(tabela_simbola);
    std::cout << vrednost << std::endl;
    return 0;
}

void Ispis::ispisi(std::ostream &os) const {
    os << "print(" << *m_cvor << ")";
}

ASTCvor *Ispis::kloniraj() const {
    return new Ispis(*this);
}

// ---------------------------------------

BinarniCvor::BinarniCvor(ASTCvor *levi, ASTCvor *desni)
    : m_levi(levi), m_desni(desni) {}

BinarniCvor::BinarniCvor(const BinarniCvor &drugi) {
    m_levi = drugi.m_levi->kloniraj();
    m_desni = drugi.m_desni->kloniraj();
}

BinarniCvor::~BinarniCvor() {
    delete m_levi;
    delete m_desni;
}

// ---------------------------------------

Sabiranje::Sabiranje(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

double Sabiranje::interpretiraj(TabelaSimbola &tabela_simbola) const {
    double levi = m_levi->interpretiraj(tabela_simbola);
    double desni = m_desni->interpretiraj(tabela_simbola);
    return levi + desni;
}

void Sabiranje::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") + (" << *m_desni << ")";
}

ASTCvor *Sabiranje::kloniraj() const {
    return new Sabiranje(*this);
}

// ---------------------------------------

Mnozenje::Mnozenje(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

double Mnozenje::interpretiraj(TabelaSimbola &tabela_simbola) const {
    double levi = m_levi->interpretiraj(tabela_simbola);
    double desni = m_desni->interpretiraj(tabela_simbola);
    return levi * desni;
}

void Mnozenje::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") * (" << *m_desni << ")";
}

ASTCvor *Mnozenje::kloniraj() const {
    return new Mnozenje(*this);
}

// ---------------------------------------

Poredjenje::Poredjenje(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

double Poredjenje::interpretiraj(TabelaSimbola &tabela_simbola) const {
    double levi = m_levi->interpretiraj(tabela_simbola);
    double desni = m_desni->interpretiraj(tabela_simbola);
    if (levi == desni) {
        std::cout << "true" << std::endl;
    }
    else {
        std::cout << "false" << std::endl;
    }

    return 0;
}

void Poredjenje::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") == (" << *m_desni << ")";
}

ASTCvor *Poredjenje::kloniraj() const {
    return new Poredjenje(*this);
}

// ---------------------------------------
