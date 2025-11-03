#pragma once
#include "studentas.h"
#include <vector>
#include <iostream>


int atsitiktinisbalas(int min, int max);
int ivestiSk(const std::string &tekstas, int min_val=-1000000, int max_val=1000000);

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
