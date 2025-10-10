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
