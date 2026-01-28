#ifndef IZRAZ_HPP
#define IZRAZ_HPP

#include <iostream>

// ---------------------------------

class Funkcija {
public:
    virtual ~Funkcija();
    virtual void ispisi(std::ostream &os) const = 0;
    virtual double izracunaj(double vrednost) const = 0;
    virtual Funkcija *izvod() const = 0;
    virtual Funkcija *komponuj(Funkcija *funkcija) const = 0;
    virtual Funkcija *kloniraj() const = 0;
};

std::ostream &operator<<(std::ostream &os, const Funkcija &izraz);

// ---------------------------------

class KonstantnaFunkcija : public Funkcija {
public:
    KonstantnaFunkcija(double vrednost);

    void ispisi(std::ostream &os) const override;
    double izracunaj(double vrednost) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;

private:
    double m_vrednost;
};

// ---------------------------------

class IdentickaFunkcija : public Funkcija {
public:
    void ispisi(std::ostream &os) const override;
    double izracunaj(double vrednost) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// ---------------------------------

class UnarnaFunkcija : public Funkcija {
public:
    UnarnaFunkcija(Funkcija *izraz);
    UnarnaFunkcija(const UnarnaFunkcija &drugi);
    ~UnarnaFunkcija();

    virtual void ispisi(std::ostream &os) const = 0;
    virtual double izracunaj(double vrednost) const = 0;
    virtual Funkcija *izvod() const = 0;
    virtual Funkcija *komponuj(Funkcija *funkcija) const = 0;
    virtual Funkcija *kloniraj() const = 0;

protected:
    Funkcija *m_funkcija;
};

// ---------------------------------

class SinFunkcija : public UnarnaFunkcija {
public:
    SinFunkcija(Funkcija *izraz);

    void ispisi(std::ostream &os) const override;
    double izracunaj(double vrednost) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// ---------------------------------

class CosFunkcija : public UnarnaFunkcija {
public:
    CosFunkcija(Funkcija *izraz);

    void ispisi(std::ostream &os) const override;
    double izracunaj(double vrednost) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// ---------------------------------

class BinarnaFunkcija : public Funkcija {
public:
    BinarnaFunkcija(Funkcija *levi, Funkcija *desni);
    BinarnaFunkcija(const BinarnaFunkcija &drugi);
    ~BinarnaFunkcija();

    virtual void ispisi(std::ostream &os) const = 0;
    virtual double izracunaj(double vrednost) const = 0;
    virtual Funkcija *izvod() const = 0;
    virtual Funkcija *komponuj(Funkcija *funkcija) const = 0;
    virtual Funkcija *kloniraj() const = 0;

protected:
    Funkcija *m_levi, *m_desni;
};

// ---------------------------------

class SabiranjeFunkcija : public BinarnaFunkcija {
public:
    SabiranjeFunkcija(Funkcija *levi, Funkcija *desni);

    void ispisi(std::ostream &os) const override;
    double izracunaj(double vrednost) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// ---------------------------------

class MnozenjeFunkcija : public BinarnaFunkcija {
public:
    MnozenjeFunkcija(Funkcija *levi, Funkcija *desni);

    void ispisi(std::ostream &os) const override;
    double izracunaj(double vrednost) const override;
    Funkcija *izvod() const override;
    Funkcija *komponuj(Funkcija *funkcija) const override;
    Funkcija *kloniraj() const override;
};

// ---------------------------------

#endif
