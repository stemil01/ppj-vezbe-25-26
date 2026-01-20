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

}

ASTCvor *PrazanCvor::kloniraj() const {

}

// -------------------------------

KonstantaCvor::KonstantaCvor(double vrednost)
    : m_vrednost(vrednost) {}

void KonstantaCvor::ispisi(std::ostream &os) const {
    
}

Funkcija *KonstantaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    
}

ASTCvor *KonstantaCvor::kloniraj() const {
    
}

// -------------------------------

PromenljivaCvor::PromenljivaCvor(const std::string &id)
    : m_id(id) {}

void PromenljivaCvor::ispisi(std::ostream &os) const {
    
}

Funkcija *PromenljivaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    
}

ASTCvor *PromenljivaCvor::kloniraj() const {
    
}

// -------------------------------

void IdentitetCvor::ispisi(std::ostream &os) const {
    
}

Funkcija *IdentitetCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    
}

ASTCvor *IdentitetCvor::kloniraj() const {
    
}

// -------------------------------

DodelaCvor::DodelaCvor(const std::string &id, ASTCvor *cvor)
    : UnarniCvor(cvor), m_id(id) {}

void DodelaCvor::ispisi(std::ostream &os) const {
    
}

Funkcija *DodelaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {

}

ASTCvor *DodelaCvor::kloniraj() const {
    
}

// -------------------------------

IspisCvor::IspisCvor(ASTCvor *cvor)
    : UnarniCvor(cvor) {}

void IspisCvor::ispisi(std::ostream &os) const {

}

Funkcija *IspisCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {

}

ASTCvor *IspisCvor::kloniraj() const {

}

// -------------------------------

SinCvor::SinCvor(ASTCvor *cvor) : UnarniCvor(cvor) {}

void SinCvor::ispisi(std::ostream &os) const {

}

Funkcija *SinCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {

}

ASTCvor *SinCvor::kloniraj() const {

}

// -------------------------------

CosCvor::CosCvor(ASTCvor *cvor) : UnarniCvor(cvor) {}

void CosCvor::ispisi(std::ostream &os) const {

}

Funkcija *CosCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {

}

ASTCvor *CosCvor::kloniraj() const {

}

// -------------------------------

IzvodCvor::IzvodCvor(ASTCvor *cvor) : UnarniCvor(cvor) {}

void IzvodCvor::ispisi(std::ostream &os) const {

}

Funkcija *IzvodCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {

}

ASTCvor *IzvodCvor::kloniraj() const {

}

// -------------------------------

VrednostCvor::VrednostCvor(ASTCvor *cvor, double vrednost)
    : UnarniCvor(cvor), m_vrednost(vrednost) {}

void VrednostCvor::ispisi(std::ostream &os) const {

}

Funkcija *VrednostCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {

}

ASTCvor *VrednostCvor::kloniraj() const {

}

// -------------------------------

SabiranjeCvor::SabiranjeCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void SabiranjeCvor::ispisi(std::ostream &os) const {

}

Funkcija *SabiranjeCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {

}

ASTCvor *SabiranjeCvor::kloniraj() const {

}

// -------------------------------

MnozenjeCvor::MnozenjeCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void MnozenjeCvor::ispisi(std::ostream &os) const {

}

Funkcija *MnozenjeCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {

}

ASTCvor *MnozenjeCvor::kloniraj() const {

}

// -------------------------------

KompozicijaCvor::KompozicijaCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void KompozicijaCvor::ispisi(std::ostream &os) const {

}

Funkcija *KompozicijaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {

}

ASTCvor *KompozicijaCvor::kloniraj() const {

}

// -------------------------------
