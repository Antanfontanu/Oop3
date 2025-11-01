#include "studentas.h"
#include "mylib.h"
#include "meniu.h"
#include "failai.h"


using namespace std;

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