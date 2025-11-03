#include "studentas.h"
#include "mylib.h"
#include "meniu.h"
#include "timer.h"
#include "failai.h"


using namespace std;

inline double galutinis(const Studentas &s, Metodas metodas) {
    if (metodas == Metodas::Vidurkis) return s.galutinisVid();
    if (metodas == Metodas::Mediana) return s.galutinisMed();
    return (s.galutinisVid() + s.galutinisMed()) / 2.0;
}



Studentas Stud_iv() {
    Studentas s;
    string vardas, pavarde;
    vector<double> nd;
    double egz = 0.0;

    cout << "Įveskite studento duomenis" << endl;
    cout << "Vardas: "; 
    cin >> vardas;
    cout << "Pavardė: "; 
    cin >> pavarde;
    cin.ignore();

    int ats = ivestiSk("Ar norite sugeneruoti atsitiktinius balus už namų darbus ir egzaminą? (1 - taip, 0 - ne): ", 0, 1);

    if (ats == 1) {
        int balu_sk = ivestiSk("Kiek balų atsitiktinai sugeneruoti: ", 1);
        for (int i = 0; i < balu_sk; ++i) {
            nd.push_back(atsitiktinisbalas(1, 10));
        }
        egz = atsitiktinisbalas(1, 10);

        cout << "Sugeneruoti " << balu_sk
             << " namų darbų ir egzamino balai studentui "
             << vardas << " " << pavarde << "." << endl;
    } 
    else {
        cout << "Įveskite pažymius (nuo 1 iki 10). Du kartus ENTER — pabaiga." << endl;
        string eil;
        int tuscios_eil = 0;

        while (true) {
            cout << "Pažymys: ";
            getline(cin, eil);

            if (eil.empty()) {
                tuscios_eil++;
                if (tuscios_eil == 2) break;
                else continue;
            } else tuscios_eil = 0;

            try {
                int laik_paz = stoi(eil);
                if (laik_paz < 1 || laik_paz > 10) {
                    cout << "Pažymys turi būti nuo 1 iki 10." << endl;
                    continue;
                }
                nd.push_back(laik_paz);
            } catch (...) {
                cout << "Reikia įvesti skaičių, bandykite dar kartą." << endl;
            }
        }

        egz = ivestiSk("Įveskite egzamino pažymį: ", 1, 10);
    }

    
    s.setVardas(vardas);
    s.setPavarde(pavarde);
    s.setNd(nd);
    s.setEgzaminas(egz);
    s.skaiciuotiGalutinius();

    // Įspėjimas, jei nėra ND
    if (nd.empty()) {
        cout << "Įspėjimas: studentui " << vardas << " " << pavarde
             << " nėra įvestų pažymių. Galutinis balas lygus egzamino balui." << endl;
    }

    return s;
}
void Studentas::skaiciuotiGalutinius() {
    if (nd_.empty()) {
        galutinisVid_ = egzaminas_;
        galutinisMed_ = egzaminas_;
        return;
    }
    double suma = std::accumulate(nd_.begin(), nd_.end(), 0.0);
    galutinisVid_ = suma / nd_.size() * 0.4 + egzaminas_ * 0.6;

    
    galutinisMed_ = mediana(nd_) * 0.4 + egzaminas_ * 0.6;
}
double Studentas::galBalas(double (*metodas)(const std::vector<double>&)) const {
    if (metodas == nullptr) return galutinisVid_;
    return metodas(nd_) * 0.4 + egzaminas_ * 0.6;
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
