#ifndef SINTAKSNO_STABLO_HPP
#define SINTAKSNO_STABLO_HPP

#include "tabela_simbola.hpp"
#include <iostream>
#include <vector>

// -------------------------------

class ASTCvor {
public:
    virtual ~ASTCvor();
    virtual void ispisi(std::ostream &os) const = 0;
    virtual int interpretiraj(TabelaSimbola &tabela_simbola) const = 0;
    virtual ASTCvor *kloniraj() const = 0;
};

std::ostream &operator<<(std::ostream &os, const ASTCvor &ast_cvor);

// -------------------------------

class UnarniCvor : public ASTCvor {
public:
    UnarniCvor(ASTCvor *cvor);
    UnarniCvor(const UnarniCvor &drugi);
    ~UnarniCvor();

    virtual void ispisi(std::ostream &os) const = 0;
    virtual int interpretiraj(TabelaSimbola &tabela_simbola) const = 0;
    virtual ASTCvor *kloniraj() const = 0;

protected:
    ASTCvor *m_cvor;
};

// -------------------------------

class BinarniCvor : public ASTCvor {
public:
    BinarniCvor(ASTCvor *levi, ASTCvor *desni);
    BinarniCvor(const BinarniCvor &drugi);
    ~BinarniCvor();

    virtual void ispisi(std::ostream &os) const = 0;
    virtual int interpretiraj(TabelaSimbola &tabela_simbola) const = 0;
    virtual ASTCvor *kloniraj() const = 0;

protected:
    ASTCvor *m_levi, *m_desni;
};

// -------------------------------

class TernarniCvor : public ASTCvor {
public:
    TernarniCvor(ASTCvor *prvi, ASTCvor *drugi, ASTCvor *treci);
    TernarniCvor(const TernarniCvor &drugi);
    ~TernarniCvor();

    virtual void ispisi(std::ostream &os) const = 0;
    virtual int interpretiraj(TabelaSimbola &tabela_simbola) const = 0;
    virtual ASTCvor *kloniraj() const = 0;

protected:
    ASTCvor *m_prvi, *m_drugi, *m_treci;
};

// -------------------------------

class NizNaredbiCvor : public ASTCvor {
public:
    NizNaredbiCvor();
    NizNaredbiCvor(const NizNaredbiCvor &drugi);
    ~NizNaredbiCvor();

    void dodaj_naredbu(ASTCvor *naredba);

    void ispisi(std::ostream &os) const override;
    int interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;

private:
    std::vector<ASTCvor *> m_naredbe;
};

// -------------------------------

class KonstantaCvor : public ASTCvor {
public:
    KonstantaCvor(int vrednost);

    void ispisi(std::ostream &os) const override;
    int interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;

private:
    int m_vrednost;
};

// -------------------------------

class PromenljivaCvor : public ASTCvor {
public:
    PromenljivaCvor(const std::string &id);

    void ispisi(std::ostream &os) const override;
    int interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;

private:
    std::string m_id;
};

// -------------------------------

class DodelaCvor : public UnarniCvor {
public:
    DodelaCvor(const std::string &id, ASTCvor *cvor);

    void ispisi(std::ostream &os) const override;
    int interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;

private:
    std::string m_id;
};

// -------------------------------

class IspisCvor : public UnarniCvor {
public:
    IspisCvor(ASTCvor *cvor);

    void ispisi(std::ostream &os) const override;
    int interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

class PotprogramCvor : public UnarniCvor {
public:
    PotprogramCvor(ASTCvor *cvor);

    void ispisi(std::ostream &os) const override;
    int interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

class SabiranjeCvor : public BinarniCvor {
public:
    SabiranjeCvor(ASTCvor *levi, ASTCvor *desni);

    void ispisi(std::ostream &os) const override;
    int interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

class OduzimanjeCvor : public BinarniCvor {
public:
    OduzimanjeCvor(ASTCvor *levi, ASTCvor *desni);

    void ispisi(std::ostream &os) const override;
    int interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

class ManjeCvor : public BinarniCvor {
public:
    ManjeCvor(ASTCvor *levi, ASTCvor *desni);

    void ispisi(std::ostream &os) const override;
    int interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

class VeceCvor : public BinarniCvor {
public:
    VeceCvor(ASTCvor *levi, ASTCvor *desni);

    void ispisi(std::ostream &os) const override;
    int interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

class IfCvor : public BinarniCvor {
public:
    IfCvor(ASTCvor *levi, ASTCvor *desni);

    void ispisi(std::ostream &os) const override;
    int interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

class WhileCvor : public BinarniCvor {
public:
    WhileCvor(ASTCvor *levi, ASTCvor *desni);

    void ispisi(std::ostream &os) const override;
    int interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

class IfElseCvor : public TernarniCvor {
public:
    IfElseCvor(ASTCvor *prvi, ASTCvor *drugi, ASTCvor *treci);

    void ispisi(std::ostream &os) const override;
    int interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

#endif
