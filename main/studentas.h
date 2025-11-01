#pragma once
#include "mylib.h"

inline double mediana(const std::vector<double>& v) {
    if (v.empty()) return 0.0;
    std::vector<double> temp = v;
    std::sort(temp.begin(), temp.end());
    size_t n = temp.size();
    if (n % 2 == 0)
        return (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    else
        return temp[n / 2];
}


//struct Studentas {
//    std::string var;
//    std::string pav;
//    Balas balai;
//    double galVid = 0.0;
 //   double galMed = 0.0;
//};

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<double> nd_;
    double egzaminas_;
    double galutinisVid_;
    double galutinisMed_;
public:
    // Konstruktoriai
    Studentas() : egzaminas_(0.0), galutinisVid_(0.0), galutinisMed_(0.0) {}
    Studentas(std::istream& is) { readStudent(is); }

    // Getteriai
    inline std::string vardas() const { return vardas_; }
    inline std::string pavarde() const { return pavarde_; }
    inline double egzaminas() const { return egzaminas_; }
    inline std::vector<double> nd() const { return nd_; }
    inline double galutinisVid() const { return galutinisVid_; }
    inline double galutinisMed() const { return galutinisMed_; }

    //Setteriai
    inline void setVardas(const std::string& v) { vardas_ = v; }
    inline void setPavarde(const std::string& p) { pavarde_ = p; }
    inline void setEgzaminas(double e) { egzaminas_ = e; }
    inline void setNd(const std::vector<double>& nd) { nd_ = nd; }

    std::istream& readStudent(std::istream& is);
    void skaiciuotiGalutinius();

    
    double galBalas(double (*metodas)(const std::vector<double>&) = mediana) const;

    
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);
};

enum class Metodas {
    Vidurkis = 1,
    Mediana = 2,
    Abu = 3
};


template <typename Container>
void spausdintiLentele(const Container &Grupe, Metodas metodas, std::ostream &os = std::cout) {
    os << std::setw(12) << std::left << "Vardas" << "|"
       << std::setw(15) << std::left << "Pavardė" << "|";

    if (metodas == Metodas::Vidurkis)
        os << "Galutinis (Vid.)" << std::endl;
    else if (metodas == Metodas::Mediana)
        os << "Galutinis (Med.)" << std::endl;
    else
        os << std::setw(17) << std::left << "Galutinis (Vid.)"
           << "|" << "Galutinis (Med.)" << std::endl;

    os << std::string(55, '-') << std::endl;

    for (const auto &s : Grupe) {
        os << std::setw(12) << std::left << s.vardas()
           << "|" << std::setw(15) << std::left << s.pavarde() << "|";

        if (metodas == Metodas::Vidurkis)
            os << std::setw(10) << std::fixed << std::setprecision(2) << s.galutinisVid() << std::endl;
        else if (metodas == Metodas::Mediana)
            os << std::setw(10) << std::fixed << std::setprecision(2) << s.galutinisMed() << std::endl;
        else
            os << std::setw(10) << std::fixed << std::setprecision(2) << s.galutinisVid()
               << "|" << std::setw(10) << std::fixed << std::setprecision(2) << s.galutinisMed() << std::endl;
    }
}





template <typename Container, typename Compare>
void mSort(Container &c, Compare cmp) {
    if constexpr (std::is_same_v<Container, std::list<Studentas>>) {
        c.sort(cmp);
    } else {
        std::sort(c.begin(), c.end(), cmp);
    }
}




Studentas Stud_iv();

