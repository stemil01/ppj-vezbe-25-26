#ifndef SINTAKSNO_STABLO_HPP
#define SINTAKSNO_STABLO_HPP

#include "funkcija.hpp"
#include "tabela_simbola.hpp"
#include <mutex>
#include <vector>

// -------------------------------

class ASTCvor {
public:
    virtual ~ASTCvor();
    virtual void ispisi(std::ostream &os) const = 0;
    virtual Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const = 0;
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
    virtual Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const = 0;
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
    virtual Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const = 0;
    virtual ASTCvor *kloniraj() const = 0;

protected:
    ASTCvor *m_levi, *m_desni;
};

// -------------------------------

class NizNaredbiCvor : public ASTCvor {
public:
    NizNaredbiCvor();
    NizNaredbiCvor(const NizNaredbiCvor &drugi);
    ~NizNaredbiCvor();

    void dodaj_naredbu(ASTCvor *naredba);

    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;

private:
    std::vector<ASTCvor *> m_naredbe;
};

// -------------------------------

class PrazanCvor : public ASTCvor {
public:
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

class KonstantaCvor : public ASTCvor {
public:
    KonstantaCvor(double vrednost);

    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;

private:
    double m_vrednost;
};

// -------------------------------

class PromenljivaCvor : public ASTCvor {
public:
    PromenljivaCvor(const std::string &id);

    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;

private:
    std::string m_id;
};

// -------------------------------

class IdentitetCvor : public ASTCvor {
public:
    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

class DodelaCvor : public UnarniCvor {
public:
    DodelaCvor(const std::string &id, ASTCvor *cvor);

    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;

private:
    std::string m_id;
};

// -------------------------------

class IspisCvor : public UnarniCvor {
public:
    IspisCvor(ASTCvor *cvor);

    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

class SinCvor : public UnarniCvor {
public:
    SinCvor(ASTCvor *cvor);

    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

class CosCvor : public UnarniCvor {
public:
    CosCvor(ASTCvor *cvor);

    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

class IzvodCvor : public UnarniCvor {
public:
    IzvodCvor(ASTCvor *cvor);

    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

class VrednostCvor : public UnarniCvor {
public:
    VrednostCvor(ASTCvor *cvor, double vrednost);

    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;

private:
    double m_vrednost;
};

// -------------------------------

class SabiranjeCvor : public BinarniCvor {
public:
    SabiranjeCvor(ASTCvor *levi, ASTCvor *desni);

    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

class MnozenjeCvor : public BinarniCvor {
public:
    MnozenjeCvor(ASTCvor *levi, ASTCvor *desni);

    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

class KompozicijaCvor : public BinarniCvor {
public:
    KompozicijaCvor(ASTCvor *levi, ASTCvor *desni);

    void ispisi(std::ostream &os) const override;
    Funkcija *interpretiraj(TabelaSimbola &tabela_simbola) const override;
    ASTCvor *kloniraj() const override;
};

// -------------------------------

#endif
