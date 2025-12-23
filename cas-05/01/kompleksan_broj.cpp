#include <iostream>

class KompleksanBroj {
public:
    KompleksanBroj() : m_re(0.0), m_im(0.0) {
        // std::cout << "prazan konstruktor" << std::endl;
    }

    KompleksanBroj(double re, double im) : m_re(re), m_im(im) {
        // std::cout << "konstruktor sa dva argumenta" << std::endl;
    }

    KompleksanBroj(const KompleksanBroj &drugi) {
        m_re = drugi.m_re;
        m_im = drugi.m_im;
        // std::cout << "konstruktor kopije" << std::endl;
    }

    ~KompleksanBroj() {
        // std::cout << "destruktor" << std::endl;
    }

    double get_re() const {
        return m_re;
    }

    double get_im() const {
        return m_im;
    }

    void set_re(double re) {
        m_re = re;
    }

    void set_im(double im) {
        m_im = im;
    }

    KompleksanBroj saberi(const KompleksanBroj &drugi) {
        return KompleksanBroj(m_re + drugi.m_re, m_im + drugi.m_im);
    }

    KompleksanBroj operator+(const KompleksanBroj &drugi) {
        return KompleksanBroj(m_re + drugi.m_re, m_im + drugi.m_im);
    }

    KompleksanBroj operator-(const KompleksanBroj &drugi) {
        return KompleksanBroj(m_re - drugi.m_re, m_im - drugi.m_im);
    }

    KompleksanBroj &operator++() {
        m_re += 1;
        return *this;
    }

    KompleksanBroj operator++(int) {
        KompleksanBroj stari = *this;
        m_re += 1;
        return stari;
    }

private:
    double m_re, m_im;
};

std::ostream &operator<<(std::ostream &os, const KompleksanBroj &z) {
    os << z.get_re() << " + " << z.get_im() << " * i";
    return os;
}

std::istream &operator>>(std::istream &is, KompleksanBroj &z) {
    double re, im;
    is >> re >> im;

    z.set_re(re);
    z.set_im(im);

    return is;
}

int main() {
    KompleksanBroj z(1, 2);

    std::cout << z << std::endl;
    std::cout << ++z << std::endl;
    std::cout << z << std::endl;

    std::cout << z++ << std::endl;
    std::cout << z << std::endl;

    return 0;
}
