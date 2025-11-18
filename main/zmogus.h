#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>

class Zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    Zmogus() = default;
    Zmogus(const std::string& v, const std::string& p)
        : vardas_(v), pavarde_(p) {}

    // Rule of three
    Zmogus(const Zmogus& other) = default;
    Zmogus& operator=(const Zmogus& other) = default;

    //destruktorius
    virtual ~Zmogus() = default;

    // Getteriai
    inline std::string vardas()  const { return vardas_; }
    inline std::string pavarde() const { return pavarde_; }

    // Setteriai
    inline void setVardas(const std::string& v)  { vardas_  = v; }
    inline void setPavarde(const std::string& p) { pavarde_ = p; }

    // Abstrakti funkcija 
    virtual void skaiciuotiGalutinius() = 0;
};

#endif
