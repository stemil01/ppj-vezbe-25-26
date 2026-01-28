#include "sintaksno_stablo.hpp"
#include "funkcija.hpp"
#include <vector>

// -------------------------------

ASTCvor::~ASTCvor() {}

std::ostream &operator<<(std::ostream &os, const ASTCvor &ast_cvor) {
    ast_cvor.ispisi(os);
    return os;
}

// -------------------------------

UnarniCvor::UnarniCvor(ASTCvor *cvor) : m_cvor(cvor) {}

UnarniCvor::UnarniCvor(const UnarniCvor &drugi) {
    m_cvor = drugi.m_cvor->kloniraj();
}

UnarniCvor::~UnarniCvor() {
    delete m_cvor;
}

// -------------------------------

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

// -------------------------------

NizNaredbiCvor::NizNaredbiCvor() {}

NizNaredbiCvor::NizNaredbiCvor(const NizNaredbiCvor &drugi) {
    m_naredbe = std::vector<ASTCvor *>(drugi.m_naredbe.size());
    for (size_t i = 0; i < drugi.m_naredbe.size(); i++) {
        m_naredbe[i] = drugi.m_naredbe[i]->kloniraj();
    }
}

NizNaredbiCvor::~NizNaredbiCvor() {
    for (ASTCvor *naredba : m_naredbe) {
        delete naredba;
    }
}

void NizNaredbiCvor::dodaj_naredbu(ASTCvor *naredba) {
    m_naredbe.push_back(naredba);
}

void NizNaredbiCvor::ispisi(std::ostream &os) const {
    for (ASTCvor *cvor : m_naredbe) {
        os << *cvor << "\n";
    }
}

Funkcija *NizNaredbiCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    for (ASTCvor *naredba : m_naredbe) {
        naredba->interpretiraj(tabela_simbola);
    }
    return nullptr;
}

ASTCvor *NizNaredbiCvor::kloniraj() const {
    return new NizNaredbiCvor(*this);
}

// -------------------------------

void PrazanCvor::ispisi(std::ostream &os) const {

}

Funkcija *PrazanCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return nullptr;
}

ASTCvor *PrazanCvor::kloniraj() const {
    return new PrazanCvor(*this);
}

// -------------------------------

KonstantaCvor::KonstantaCvor(double vrednost)
    : m_vrednost(vrednost) {}

void KonstantaCvor::ispisi(std::ostream &os) const {
    os << m_vrednost;
}

Funkcija *KonstantaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return new KonstantnaFunkcija(m_vrednost);
}

ASTCvor *KonstantaCvor::kloniraj() const {
    return new KonstantaCvor(*this);
}

// -------------------------------

PromenljivaCvor::PromenljivaCvor(const std::string &id)
    : m_id(id) {}

void PromenljivaCvor::ispisi(std::ostream &os) const {
    os << m_id;
}

Funkcija *PromenljivaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return tabela_simbola.vrednost_promenljive(m_id)->kloniraj();
}

ASTCvor *PromenljivaCvor::kloniraj() const {
    return new PromenljivaCvor(*this);
}

// -------------------------------

void IdentitetCvor::ispisi(std::ostream &os) const {
    os << "x";
}

Funkcija *IdentitetCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return new IdentickaFunkcija();
}

ASTCvor *IdentitetCvor::kloniraj() const {
    return new IdentitetCvor(*this);
}

// -------------------------------

DodelaCvor::DodelaCvor(const std::string &id, ASTCvor *cvor)
    : UnarniCvor(cvor), m_id(id) {}

void DodelaCvor::ispisi(std::ostream &os) const {
    os << m_id << " = " << *m_cvor;
}

Funkcija *DodelaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    Funkcija *vrednost = m_cvor->interpretiraj(tabela_simbola);
    tabela_simbola.dodeli_vrednost(m_id, vrednost);
    return nullptr;
}

ASTCvor *DodelaCvor::kloniraj() const {
    return new DodelaCvor(*this);
}

// -------------------------------

IspisCvor::IspisCvor(ASTCvor *cvor)
    : UnarniCvor(cvor) {}

void IspisCvor::ispisi(std::ostream &os) const {
    os << *m_cvor;
}

Funkcija *IspisCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    Funkcija *vrednost = m_cvor->interpretiraj(tabela_simbola);
    std::cout << *vrednost << std::endl;
    delete vrednost;
    return nullptr;
}

ASTCvor *IspisCvor::kloniraj() const {
    return new IspisCvor(*this);
}

// -------------------------------

SinCvor::SinCvor(ASTCvor *cvor) : UnarniCvor(cvor) {}

void SinCvor::ispisi(std::ostream &os) const {
    os << "sin(" << *m_cvor << ")";
}

Funkcija *SinCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    Funkcija *vrednost = m_cvor->interpretiraj(tabela_simbola);
    return new SinFunkcija(vrednost);
}

ASTCvor *SinCvor::kloniraj() const {
    return new SinCvor(*this);
}

// -------------------------------

CosCvor::CosCvor(ASTCvor *cvor) : UnarniCvor(cvor) {}

void CosCvor::ispisi(std::ostream &os) const {
    os << "cos(" << *m_cvor << ")";
}

Funkcija *CosCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    Funkcija *vrednost = m_cvor->interpretiraj(tabela_simbola);
    return new CosFunkcija(vrednost);
}

ASTCvor *CosCvor::kloniraj() const {
    return new CosCvor(*this);
}

// -------------------------------

IzvodCvor::IzvodCvor(ASTCvor *cvor) : UnarniCvor(cvor) {}

void IzvodCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_cvor << ")'";
}

Funkcija *IzvodCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    Funkcija *vrednost = m_cvor->interpretiraj(tabela_simbola);
    Funkcija *izvod = vrednost->izvod();
    delete vrednost;
    return izvod;
}

ASTCvor *IzvodCvor::kloniraj() const {
    return new IzvodCvor(*this);
}

// -------------------------------

VrednostCvor::VrednostCvor(ASTCvor *cvor, double vrednost)
    : UnarniCvor(cvor), m_vrednost(vrednost) {}

void VrednostCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_cvor << ")[" << m_vrednost << "]";
}

Funkcija *VrednostCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    Funkcija *funkcija = m_cvor->interpretiraj(tabela_simbola);
    double vrednost = funkcija->izracunaj(m_vrednost);
    Funkcija *rezultat = new KonstantnaFunkcija(vrednost);

    delete funkcija;
    return rezultat;
}

ASTCvor *VrednostCvor::kloniraj() const {
    return new VrednostCvor(*this);
}

// -------------------------------

SabiranjeCvor::SabiranjeCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void SabiranjeCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") + (" << *m_desni << ")";
}

Funkcija *SabiranjeCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    Funkcija *levo = m_levi->interpretiraj(tabela_simbola);
    Funkcija *desno = m_desni->interpretiraj(tabela_simbola);

    return new SabiranjeFunkcija(levo, desno);
}

ASTCvor *SabiranjeCvor::kloniraj() const {
    return new SabiranjeCvor(*this);
}

// -------------------------------

MnozenjeCvor::MnozenjeCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void MnozenjeCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") * (" << *m_desni << ")";
}

Funkcija *MnozenjeCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    Funkcija *levo = m_levi->interpretiraj(tabela_simbola);
    Funkcija *desno = m_desni->interpretiraj(tabela_simbola);

    return new MnozenjeFunkcija(levo, desno);
}

ASTCvor *MnozenjeCvor::kloniraj() const {
    return new MnozenjeCvor(*this);
}

// -------------------------------

KompozicijaCvor::KompozicijaCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void KompozicijaCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") (" << *m_desni << ")";
}

Funkcija *KompozicijaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    Funkcija *levo = m_levi->interpretiraj(tabela_simbola);
    Funkcija *desno = m_desni->interpretiraj(tabela_simbola);

    Funkcija *rezultat = levo->komponuj(desno);
    delete levo;
    delete desno;
    return rezultat;
}

ASTCvor *KompozicijaCvor::kloniraj() const {
    return new KompozicijaCvor(*this);
}

// -------------------------------
