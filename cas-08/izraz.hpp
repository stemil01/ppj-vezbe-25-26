#ifndef IZRAZ_HPP
#define IZRAZ_HPP

#include <iostream>
#include <map>

class TabelaSimbola {
public:
    void dodaj_promenljivu(const std::string &id, double vrednost);
    double vrednost_promenljive(const std::string &id) const;

private:
    std::map<std::string, double> m_promenljive;
};

// ---------------------------------

class Izraz {
public:
    virtual ~Izraz();
    virtual void ispisi(std::ostream &os) const = 0;
    virtual double izracunaj(TabelaSimbola &tabela_simbola) const = 0;
    virtual Izraz *izvod(const std::string &promenljiva) const = 0;
    virtual Izraz *kloniraj() const = 0;
};

std::ostream &operator<<(std::ostream &os, const Izraz &izraz);

// ---------------------------------

class Konstanta : public Izraz {
public:
    Konstanta(double vrednost);

    void ispisi(std::ostream &os) const override;
    double izracunaj(TabelaSimbola &tabela_simbola) const override;
    Izraz *izvod(const std::string &promenljiva) const override;
    Izraz *kloniraj() const override;

private:
    double m_vrednost;
};

// ---------------------------------

class Promenljiva : public Izraz {
public:
    Promenljiva(const std::string &id);

    void ispisi(std::ostream &os) const override;
    double izracunaj(TabelaSimbola &tabela_simbola) const override;
    Izraz *izvod(const std::string &promenljiva) const override;
    Izraz *kloniraj() const override;

private:
    std::string m_id;
};

// ---------------------------------

class UnarniIzraz : public Izraz {
public:
    UnarniIzraz(Izraz *izraz);
    UnarniIzraz(const UnarniIzraz &drugi);
    ~UnarniIzraz();

    virtual void ispisi(std::ostream &os) const = 0;
    virtual double izracunaj(TabelaSimbola &tabela_simbola) const = 0;
    virtual Izraz *izvod(const std::string &promenljiva) const = 0;
    virtual Izraz *kloniraj() const = 0;

protected:
    Izraz *m_izraz;
};

// ---------------------------------

class Sin : public UnarniIzraz {
public:
    Sin(Izraz *izraz);

    void ispisi(std::ostream &os) const override;
    double izracunaj(TabelaSimbola &tabela_simbola) const override;
    Izraz *izvod(const std::string &promenljiva) const override;
    Izraz *kloniraj() const override;
};

// ---------------------------------

class Cos : public UnarniIzraz {
public:
    Cos(Izraz *izraz);

    void ispisi(std::ostream &os) const override;
    double izracunaj(TabelaSimbola &tabela_simbola) const override;
    Izraz *izvod(const std::string &promenljiva) const override;
    Izraz *kloniraj() const override;
};

// ---------------------------------

class BinarniIzraz : public Izraz {
public:
    BinarniIzraz(Izraz *levi, Izraz *desni);
    BinarniIzraz(const BinarniIzraz &drugi);
    ~BinarniIzraz();

    virtual void ispisi(std::ostream &os) const = 0;
    virtual double izracunaj(TabelaSimbola &tabela_simbola) const = 0;
    virtual Izraz *izvod(const std::string &promenljiva) const = 0;
    virtual Izraz *kloniraj() const = 0;

protected:
    Izraz *m_levi, *m_desni;
};

// ---------------------------------

class Sabiranje : public BinarniIzraz {
public:
    Sabiranje(Izraz *levi, Izraz *desni);

    void ispisi(std::ostream &os) const override;
    double izracunaj(TabelaSimbola &tabela_simbola) const override;
    Izraz *izvod(const std::string &promenljiva) const override;
    Izraz *kloniraj() const override;
};

// ---------------------------------

class Mnozenje : public BinarniIzraz {
public:
    Mnozenje(Izraz *levi, Izraz *desni);

    void ispisi(std::ostream &os) const override;
    double izracunaj(TabelaSimbola &tabela_simbola) const override;
    Izraz *izvod(const std::string &promenljiva) const override;
    Izraz *kloniraj() const override;
};

// ---------------------------------

#endif
