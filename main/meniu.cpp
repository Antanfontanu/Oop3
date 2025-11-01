#include "meniu.h"
#include "mylib.h"
#include "timer.h"
#include "studentas.h"  

using namespace std;
using namespace std::chrono;


inline double galutinis(const Studentas &s, Metodas metodas) {
    if (metodas == Metodas::Vidurkis) return s.galutinisVid();
    if (metodas == Metodas::Mediana) return s.galutinisMed();
    return (s.galutinisVid() + s.galutinisMed()) / 2.0;
}


int ivestiSk(const string &tekstas, int min_val, int max_val) {
    int sk;
    while (true) {
        cout << tekstas;
        string eil;
        getline(cin, eil);
        try {
            sk = stoi(eil);
            if (sk >= min_val && sk <= max_val)
                return sk;
            else
                cout << "Įveskite skaičių nuo " << min_val << " iki " << max_val << "." << endl;
        } catch (...) {
            cout << "Įveskite tik skaičių." << endl;
        }
    }
}


template <typename Container>
void padalintiStudentus(const Container &Grupe, Container &vargsiukai, Container &kietiakai, Metodas metodas) {
    Timer t("Padalinimas į grupes");

    for (const auto &s : Grupe) {
        double gal = galutinis(s, metodas);
        if (gal < 5.0)
            vargsiukai.push_back(s);
        else
            kietiakai.push_back(s);
    }

    t.save();
}

// Strategija 1
template <typename Container>
void padalintiStudentus1(Container &Grupe, Container &vargsiukai, Container &kietiakai, Metodas metodas) {
    Timer t("Strategija 1");

    for (auto it = Grupe.begin(); it != Grupe.end(); ++it) {
        double gal = galutinis(*it, metodas);
        if (gal < 5.0)
            vargsiukai.push_back(*it);
        else
            kietiakai.push_back(*it);
    }

    t.save();
}

// Strategija 2
template <typename Container>
void padalintiStudentus2(Container &Grupe, Container &vargsiukai, Metodas metodas) {
    Timer t("Strategija 2");

    if constexpr (std::is_same_v<Container, std::list<Studentas>>) {
        auto it = Grupe.begin();
        while (it != Grupe.end()) {
            double gal = galutinis(*it, metodas);
            if (gal < 5.0) {
                vargsiukai.push_back(*it);
                it = Grupe.erase(it);
            } else {
                ++it;
            }
        }
    } else {
        // vector
        Container naujaGrupe;
        naujaGrupe.reserve(Grupe.size());

        for (auto &stud : Grupe) {
            double gal = galutinis(stud, metodas);
            if (gal < 5.0)
                vargsiukai.push_back(std::move(stud));
            else
                naujaGrupe.push_back(std::move(stud));
        }
        Grupe = std::move(naujaGrupe);
    }

    t.save();
}

// Strategija 3
template <typename Container>
void padalintiStudentus3(Container &Grupe, Container &vargsiukai, Metodas metodas) {
    Timer t("Strategija 3 optimizuota");

    auto it = std::partition(Grupe.begin(), Grupe.end(), [&](const Studentas &s) {
        return galutinis(s, metodas) >= 5.0;
    });

    vargsiukai.insert(vargsiukai.end(),
                      std::make_move_iterator(it),
                      std::make_move_iterator(Grupe.end()));

    Grupe.erase(it, Grupe.end());

    t.save();
}

//padalijimas pagal strategiją
template <typename Container>
void padalintiStudentusPagalStrategija(Container &Grupe, Container &vargsiukai, Container &kietiakai,
                                       Metodas metodas, int strategija) {
    if (strategija == 1) {
        padalintiStudentus1(Grupe, vargsiukai, kietiakai, metodas);
    } else if (strategija == 2) {
        padalintiStudentus2(Grupe, vargsiukai, metodas);
        kietiakai = Grupe;
    } else if (strategija == 3) {
        padalintiStudentus3(Grupe, vargsiukai, metodas);
        kietiakai = Grupe;
    }
}

// Rikiavimas
template <typename Container>
void surikiuotiStudentus(Container &stud, int kriterijus, Metodas metodas) {
    if constexpr (std::is_same_v<Container, std::list<Studentas>>) {
        if (kriterijus == 1)
            stud.sort([](const Studentas &a, const Studentas &b) { return a.vardas() < b.vardas(); });
        else if (kriterijus == 2)
            stud.sort([](const Studentas &a, const Studentas &b) { return a.pavarde() < b.pavarde(); });
        else
            stud.sort([metodas](const Studentas &a, const Studentas &b) {
                return galutinis(a, metodas) > galutinis(b, metodas);
            });
    } else {
        if (kriterijus == 1) {
            sort(stud.begin(), stud.end(), [](const Studentas &a, const Studentas &b) { return a.vardas() < b.vardas(); });
        } else if (kriterijus == 2) {
            sort(stud.begin(), stud.end(), [](const Studentas &a, const Studentas &b) { return a.pavarde() < b.pavarde(); });
        } else {
            sort(stud.begin(), stud.end(), [metodas](const Studentas &a, const Studentas &b) {
                return galutinis(a, metodas) > galutinis(b, metodas);
            });
        }
    }
}


template void padalintiStudentus(const std::vector<Studentas> &,
                                 std::vector<Studentas> &,
                                 std::vector<Studentas> &,
                                 Metodas);
template void padalintiStudentus(const std::list<Studentas> &,
                                 std::list<Studentas> &,
                                 std::list<Studentas> &,
                                 Metodas);
template void surikiuotiStudentus(std::vector<Studentas> &, int, Metodas);
template void surikiuotiStudentus(std::list<Studentas> &, int, Metodas);
template void padalintiStudentusPagalStrategija(std::vector<Studentas> &, std::vector<Studentas> &, std::vector<Studentas> &, Metodas, int);
template void padalintiStudentusPagalStrategija(std::list<Studentas> &, std::list<Studentas> &, std::list<Studentas> &, Metodas, int);
template void padalintiStudentus1(std::vector<Studentas>&, std::vector<Studentas>&, std::vector<Studentas>&, Metodas);
template void padalintiStudentus1(std::list<Studentas>&, std::list<Studentas>&, std::list<Studentas>&, Metodas);
template void padalintiStudentus2(std::vector<Studentas>&, std::vector<Studentas>&, Metodas);
template void padalintiStudentus2(std::list<Studentas>&, std::list<Studentas>&, Metodas);
template void padalintiStudentus3(std::vector<Studentas>&, std::vector<Studentas>&, Metodas);
template void padalintiStudentus3(std::list<Studentas>&, std::list<Studentas>&, Metodas);
