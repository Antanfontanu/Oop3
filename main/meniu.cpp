#include "meniu.h"
#include "mylib.h"
#include "timer.h"
using namespace std;
using namespace std::chrono;


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
void padalintiStudentus(const Container &Grupe,
                        Container &vargsiukai,
                        Container &kietiakai,
                        Metodas metodas) {
    Timer t("Padalinimas į grupes");
    

    for (const auto &s : Grupe) {
        double galutinis;
        if (metodas == Metodas::Vidurkis)
            galutinis = s.galVid;
        else if (metodas == Metodas::Mediana)
            galutinis = s.galMed;
        else
            galutinis = (s.galVid + s.galMed) / 2.0;

        if (galutinis < 5.0)
            vargsiukai.push_back(s);
        else
            kietiakai.push_back(s);
    }

     t.save();
}

//1strategija

template <typename Container>
void padalintiStudentus1(Container &Grupe, Container &vargsiukai, Container &kietiakai, Metodas metodas) {
    Timer t("Strategija 1");

    for (auto it = Grupe.begin(); it != Grupe.end(); ++it) {
        double galutinis = (metodas == Metodas::Vidurkis)
                               ? it->galVid
                               : (metodas == Metodas::Mediana)
                                     ? it->galMed
                                     : (it->galVid + it->galMed) / 2.0;
        if (galutinis < 5.0)
            vargsiukai.push_back(*it);
        else
            kietiakai.push_back(*it);
    }

    t.save();
}

// 2 stratedija
template <typename Container>
void padalintiStudentus2(Container &Grupe, Container &vargsiukai, Metodas metodas) {
    Timer t("Strategija 2");

    if constexpr (std::is_same_v<Container, std::list<Studentas>>) {
        Grupe.remove_if([&](const Studentas &s) {
            double galutinis = (metodas == Metodas::Vidurkis)
                                   ? s.galVid
                                   : (metodas == Metodas::Mediana)
                                         ? s.galMed
                                         : (s.galVid + s.galMed) / 2.0;
            if (galutinis < 5.0) {
                vargsiukai.push_back(s);
                return true;
            }
            return false;
        });
    } else {
        auto it = std::remove_if(Grupe.begin(), Grupe.end(), [&](const Studentas &s) {
            double galutinis = (metodas == Metodas::Vidurkis)
                                   ? s.galVid
                                   : (metodas == Metodas::Mediana)
                                         ? s.galMed
                                         : (s.galVid + s.galMed) / 2.0;
            if (galutinis < 5.0) {
                vargsiukai.push_back(s);
                return true;
            }
            return false;
        });
        Grupe.erase(it, Grupe.end());
    }

    t.save();
}

// 3strategija
template <typename Container>
void padalintiStudentus3(Container &Grupe, Container &vargsiukai, Metodas metodas) {
    Timer t("Strategija 3");

    auto it = stable_partition(Grupe.begin(), Grupe.end(), [&](const Studentas &s) {
        double galutinis = (metodas == Metodas::Vidurkis)
                               ? s.galVid
                               : (metodas == Metodas::Mediana)
                                     ? s.galMed
                                     : (s.galVid + s.galMed) / 2.0;
        return galutinis >= 5.0;
    });

    vargsiukai.insert(vargsiukai.end(), it, Grupe.end());
    Grupe.erase(it, Grupe.end());

    t.save();
}


template <typename Container>
void padalintiStudentusPagalStrategija(Container &Grupe, Container &vargsiukai,Container &kietiakai, Metodas metodas,int strategija) {
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


template <typename Container>
void surikiuotiStudentus(Container &stud, int kriterijus, Metodas metodas) {
    if constexpr (std::is_same_v<Container, std::list<Studentas>>) {
        //sarasui
        if (kriterijus == 1)
            stud.sort([](const Studentas &a, const Studentas &b) { return a.var < b.var; });
        else if (kriterijus == 2)
            stud.sort([](const Studentas &a, const Studentas &b) { return a.pav < b.pav; });
        else
            stud.sort([metodas](const Studentas &a, const Studentas &b) {
                double galA = (metodas == Metodas::Vidurkis)
                                  ? a.galVid
                                  : (metodas == Metodas::Mediana)
                                        ? a.galMed
                                        : (a.galVid + a.galMed) / 2.0;
                double galB = (metodas == Metodas::Vidurkis)
                                  ? b.galVid
                                  : (metodas == Metodas::Mediana)
                                        ? b.galMed
                                        : (b.galVid + b.galMed) / 2.0;
                return galA > galB;
            });
    } else {
        
        if (kriterijus == 1) {
            sort(stud.begin(), stud.end(),
                 [](const Studentas &a, const Studentas &b) { return a.var < b.var; });
        } else if (kriterijus == 2) {
            sort(stud.begin(), stud.end(),
                 [](const Studentas &a, const Studentas &b) { return a.pav < b.pav; });
        } else if (kriterijus == 3) {
            sort(stud.begin(), stud.end(), [metodas](const Studentas &a, const Studentas &b) {
                double galA = (metodas == Metodas::Vidurkis)
                                  ? a.galVid
                                  : (metodas == Metodas::Mediana)
                                        ? a.galMed
                                        : (a.galVid + a.galMed) / 2.0;
                double galB = (metodas == Metodas::Vidurkis)
                                  ? b.galVid
                                  : (metodas == Metodas::Mediana)
                                        ? b.galMed
                                        : (b.galVid + b.galMed) / 2.0;
                return galA > galB;
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
template void padalintiStudentusPagalStrategija<std::vector<Studentas>>(
    std::vector<Studentas> &Grupe,
    std::vector<Studentas> &vargsiukai,
    std::vector<Studentas> &kietiakai,
    Metodas metodas,
    int strategija);

template void padalintiStudentusPagalStrategija<std::list<Studentas>>(
    std::list<Studentas> &Grupe,
    std::list<Studentas> &vargsiukai,
    std::list<Studentas> &kietiakai,
    Metodas metodas,
    int strategija);

template void padalintiStudentus1(std::vector<Studentas>&, std::vector<Studentas>&, std::vector<Studentas>&, Metodas);
template void padalintiStudentus1(std::list<Studentas>&, std::list<Studentas>&, std::list<Studentas>&, Metodas);
template void padalintiStudentus2(std::vector<Studentas>&, std::vector<Studentas>&, Metodas);
template void padalintiStudentus2(std::list<Studentas>&, std::list<Studentas>&, Metodas);
template void padalintiStudentus3(std::vector<Studentas>&, std::vector<Studentas>&, Metodas);
template void padalintiStudentus3(std::list<Studentas>&, std::list<Studentas>&, Metodas);

