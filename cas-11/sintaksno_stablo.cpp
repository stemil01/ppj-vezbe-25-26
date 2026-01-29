#include "sintaksno_stablo.hpp"
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

TernarniCvor::TernarniCvor(ASTCvor *prvi, ASTCvor *drugi, ASTCvor *treci)
    : m_prvi(prvi), m_drugi(drugi), m_treci(treci) {}

TernarniCvor::TernarniCvor(const TernarniCvor &drugi) {
    m_prvi = drugi.m_prvi->kloniraj();
    m_drugi = drugi.m_drugi->kloniraj();
    m_treci = drugi.m_treci->kloniraj();
}

TernarniCvor::~TernarniCvor() {
    delete m_prvi;
    delete m_drugi;
    delete m_treci;
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

int NizNaredbiCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    for (ASTCvor *naredba : m_naredbe) {
        naredba->interpretiraj(tabela_simbola);
    }
    return 0;
}

ASTCvor *NizNaredbiCvor::kloniraj() const {
    return new NizNaredbiCvor(*this);
}

// -------------------------------

KonstantaCvor::KonstantaCvor(int vrednost)
    : m_vrednost(vrednost) {}

void KonstantaCvor::ispisi(std::ostream &os) const {
    os << m_vrednost;
}

int KonstantaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return m_vrednost;
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

int PromenljivaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return tabela_simbola.vrednost_promenljive(m_id);
}

ASTCvor *PromenljivaCvor::kloniraj() const {
    return new PromenljivaCvor(*this);
}

// -------------------------------

DodelaCvor::DodelaCvor(const std::string &id, ASTCvor *cvor)
    : UnarniCvor(cvor), m_id(id) {}

void DodelaCvor::ispisi(std::ostream &os) const {
    os << m_id << " = " << *m_cvor;
}

int DodelaCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    int vrednost = m_cvor->interpretiraj(tabela_simbola);
    tabela_simbola.dodeli_vrednost(m_id, vrednost);

    return 0;
}

ASTCvor *DodelaCvor::kloniraj() const {
    return new DodelaCvor(*this);
}

// -------------------------------

IspisCvor::IspisCvor(ASTCvor *cvor)
    : UnarniCvor(cvor) {}

void IspisCvor::ispisi(std::ostream &os) const {
    os << "print(" << *m_cvor << ")";
}

int IspisCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    int vrednost = m_cvor->interpretiraj(tabela_simbola);
    std::cout << vrednost << std::endl;

    return 0;
}

ASTCvor *IspisCvor::kloniraj() const {
    return new IspisCvor(*this);
}

// -------------------------------

PotprogramCvor::PotprogramCvor(ASTCvor *cvor)
    : UnarniCvor(cvor) {}

void PotprogramCvor::ispisi(std::ostream &os) const {
    os << "BEGIN\n" << *m_cvor << "\nEND";
}

int PotprogramCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    return m_cvor->interpretiraj(tabela_simbola);
}

ASTCvor *PotprogramCvor::kloniraj() const {
    return new PotprogramCvor(*this);
}

// -------------------------------

SabiranjeCvor::SabiranjeCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void SabiranjeCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") + (" << *m_desni << ")";
}

int SabiranjeCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    int leva_vrednost = m_levi->interpretiraj(tabela_simbola);
    int desna_vrednost = m_desni->interpretiraj(tabela_simbola);

    return leva_vrednost + desna_vrednost;
}

ASTCvor *SabiranjeCvor::kloniraj() const {
    return new SabiranjeCvor(*this);
}

// -------------------------------

OduzimanjeCvor::OduzimanjeCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void OduzimanjeCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") - (" << *m_desni << ")";
}

int OduzimanjeCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    int leva_vrednost = m_levi->interpretiraj(tabela_simbola);
    int desna_vrednost = m_desni->interpretiraj(tabela_simbola);

    return leva_vrednost - desna_vrednost;
}

ASTCvor *OduzimanjeCvor::kloniraj() const {
    return new OduzimanjeCvor(*this);
}

// -------------------------------

ManjeCvor::ManjeCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void ManjeCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") < (" << *m_desni << ")";
}

int ManjeCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    int leva_vrednost = m_levi->interpretiraj(tabela_simbola);
    int desna_vrednost = m_desni->interpretiraj(tabela_simbola);

    return leva_vrednost < desna_vrednost;
}

ASTCvor *ManjeCvor::kloniraj() const {
    return new ManjeCvor(*this);
}

// -------------------------------

VeceCvor::VeceCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void VeceCvor::ispisi(std::ostream &os) const {
    os << "(" << *m_levi << ") > (" << *m_desni << ")";
}

int VeceCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    int leva_vrednost = m_levi->interpretiraj(tabela_simbola);
    int desna_vrednost = m_desni->interpretiraj(tabela_simbola);

    return leva_vrednost > desna_vrednost;
}

ASTCvor *VeceCvor::kloniraj() const {
    return new VeceCvor(*this);
}

// -------------------------------

IfCvor::IfCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void IfCvor::ispisi(std::ostream &os) const {
    os << "if (" << *m_levi << ")\n" << *m_desni;
}

int IfCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    if (m_levi->interpretiraj(tabela_simbola)) {
        m_desni->interpretiraj(tabela_simbola);
    }
    return 0;
}

ASTCvor *IfCvor::kloniraj() const {
    return new IfCvor(*this);
}

// -------------------------------

WhileCvor::WhileCvor(ASTCvor *levi, ASTCvor *desni)
    : BinarniCvor(levi, desni) {}

void WhileCvor::ispisi(std::ostream &os) const {
    os << "while (" << *m_levi << ")\n" << *m_desni;
}

int WhileCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    while (m_levi->interpretiraj(tabela_simbola)) {
        m_desni->interpretiraj(tabela_simbola);
    }
    return 0;
}

ASTCvor *WhileCvor::kloniraj() const {
    return new WhileCvor(*this);
}

// -------------------------------

IfElseCvor::IfElseCvor(ASTCvor *prvi, ASTCvor *drugi, ASTCvor *treci)
    : TernarniCvor(prvi, drugi, treci) {}

void IfElseCvor::ispisi(std::ostream &os) const {
    os << "if (" << *m_prvi << ")\n";
    os << *m_drugi;
    os << "\nELSE\n" << *m_treci;
}

int IfElseCvor::interpretiraj(TabelaSimbola &tabela_simbola) const {
    if (m_prvi->interpretiraj(tabela_simbola)) {
        m_drugi->interpretiraj(tabela_simbola);
    }
    else {
        m_treci->interpretiraj(tabela_simbola);
    }
    return 0;
}

ASTCvor *IfElseCvor::kloniraj() const {
    return new IfElseCvor(*this);
}

// -------------------------------
