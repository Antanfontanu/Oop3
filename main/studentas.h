#pragma once
#include "mylib.h"

struct Balas {
    std::vector<int> nd;
    int egz = 0;
};

struct Studentas {
    std::string var;
    std::string pav;
    Balas balai;
    double galVid = 0.0;
    double galMed = 0.0;
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
        os << std::setw(12) << std::left << s.var
           << "|" << std::setw(15) << std::left << s.pav << "|";

        if (metodas == Metodas::Vidurkis)
            os << std::setw(10) << std::fixed << std::setprecision(2) << s.galVid << std::endl;
        else if (metodas == Metodas::Mediana)
            os << std::setw(10) << std::fixed << std::setprecision(2) << s.galMed << std::endl;
        else
            os << std::setw(10) << std::fixed << std::setprecision(2) << s.galVid
               << "|" << std::setw(10) << std::fixed << std::setprecision(2) << s.galMed << std::endl;
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
double skaiciuotiMediana(const std::vector<int>& paz);
