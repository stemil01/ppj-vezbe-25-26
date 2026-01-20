#ifndef SINTAKSNO_STABLO_HPP
#define SINTAKSNO_STABLO_HPP

#include <iostream>
#include <vector>
#include "tabela_simbola.hpp"

class ASTCvor {
public:
    virtual ~ASTCvor();
    virtual double interpretiraj(TabelaSimbola &tabela_simbola) const = 0;
    virtual void ispisi(std::ostream &os) const = 0;
    virtual ASTCvor *kloniraj() const = 0;
};

std::ostream &operator<<(std::ostream &os, const ASTCvor &ast_cvor);

// ---------------------------------------

class Promenljiva : public ASTCvor {
public:
    Promenljiva(const std::string &id);

    double interpretiraj(TabelaSimbola &tabela_simbola) const override;
    void ispisi(std::ostream &os) const override;
    ASTCvor *kloniraj() const override;

private:
    std::string m_id;
};

// ---------------------------------------

class Konstanta : public ASTCvor {
public:
    Konstanta(double vrednost);

    double interpretiraj(TabelaSimbola &tabela_simbola) const override;
    void ispisi(std::ostream &os) const override;
    ASTCvor *kloniraj() const override;

private:
    double m_vrednost;
};

// ---------------------------------------

class NizNaredbi : public ASTCvor {
public:
    NizNaredbi();
    NizNaredbi(const NizNaredbi &drugi);
    ~NizNaredbi();

    void dodaj_naredbu(ASTCvor *naredba);

    double interpretiraj(TabelaSimbola &tabela_simbola) const override;
    void ispisi(std::ostream &os) const override;
    ASTCvor *kloniraj() const override;

private:
    std::vector<ASTCvor *> m_naredbe;
};

// ---------------------------------------

class Definicija : public ASTCvor {
public:
    Definicija(const std::string &id, ASTCvor *izraz);
    Definicija(const Definicija &drugi);
    ~Definicija();

    double interpretiraj(TabelaSimbola &tabela_simbola) const override;
    void ispisi(std::ostream &os) const override;
    ASTCvor *kloniraj() const override;

private:
    std::string m_id;
    ASTCvor *m_izraz;
};

// ---------------------------------------

class Dodela : public ASTCvor {
public:
    Dodela(const std::string &id, ASTCvor *izraz);
    Dodela(const Dodela &drugi);
    ~Dodela();

    double interpretiraj(TabelaSimbola &tabela_simbola) const override;
    void ispisi(std::ostream &os) const override;
    ASTCvor *kloniraj() const override;

private:
    std::string m_id;
    ASTCvor *m_izraz;
};

// ---------------------------------------

class UnarniCvor : public ASTCvor {
public:
    UnarniCvor(ASTCvor *cvor);
    UnarniCvor(const UnarniCvor &drugi);
    ~UnarniCvor();

    virtual double interpretiraj(TabelaSimbola &tabela_simbola) const = 0;
    virtual void ispisi(std::ostream &os) const = 0;
    virtual ASTCvor *kloniraj() const = 0;

protected:
    ASTCvor *m_cvor;
};

// ---------------------------------------

class Negacija : public UnarniCvor {
public:
    Negacija(ASTCvor *cvor);

    double interpretiraj(TabelaSimbola &tabela_simbola) const override;
    void ispisi(std::ostream &os) const override;
    ASTCvor *kloniraj() const override;
};

// ---------------------------------------

class Ispis : public UnarniCvor {
public:
    Ispis(ASTCvor *cvor);

    double interpretiraj(TabelaSimbola &tabela_simbola) const override;
    void ispisi(std::ostream &os) const override;
    ASTCvor *kloniraj() const override;
};

// ---------------------------------------

class BinarniCvor : public ASTCvor {
public:
    BinarniCvor(ASTCvor *levi, ASTCvor *desni);
    BinarniCvor(const BinarniCvor &drugi);
    ~BinarniCvor();

    virtual double interpretiraj(TabelaSimbola &tabela_simbola) const = 0;
    virtual void ispisi(std::ostream &os) const = 0;
    virtual ASTCvor *kloniraj() const = 0;

protected:
    ASTCvor *m_levi, *m_desni;
};

// ---------------------------------------

class Sabiranje : public BinarniCvor {
public:
    Sabiranje(ASTCvor *levi, ASTCvor *desni);

    double interpretiraj(TabelaSimbola &tabela_simbola) const override;
    void ispisi(std::ostream &os) const override;
    ASTCvor *kloniraj() const override;
};

// ---------------------------------------

class Mnozenje : public BinarniCvor {
public:
    Mnozenje(ASTCvor *levi, ASTCvor *desni);

    double interpretiraj(TabelaSimbola &tabela_simbola) const override;
    void ispisi(std::ostream &os) const override;
    ASTCvor *kloniraj() const override;
};

// ---------------------------------------

class Poredjenje : public BinarniCvor {
public:
    Poredjenje(ASTCvor *levi, ASTCvor *desni);

    double interpretiraj(TabelaSimbola &tabela_simbola) const override;
    void ispisi(std::ostream &os) const override;
    ASTCvor *kloniraj() const override;
};

// ---------------------------------------

#endif
