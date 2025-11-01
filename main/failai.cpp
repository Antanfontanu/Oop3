#include "failai.h"
#include "mylib.h"
#include "timer.h"

using namespace std;

int atsitiktinisbalas(int min, int max) {
    return min + rand() % (max - min + 1);
}

void generuotiFailus() {
    Timer t("Failo generavimas");
    vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
    cout << "Pasirinkite studentų kiekį iš šių variantų:\n";
    for (size_t i = 0; i < dydziai.size(); i++) {
        cout << i + 1 << " - " << dydziai[i] << endl;
    }
    int pasirinkimas;
    cin >> pasirinkimas; cin.ignore();
    int dydis = dydziai[pasirinkimas - 1];
    int nd_kiekis;
    cout << "Kiek namų darbų balų sugeneruoti kiekvienam studentui? ";
    cin >> nd_kiekis; cin.ignore();

    string failoVardas = "studentas" + to_string(dydis) + ".txt";
    ofstream out(failoVardas);
    if (!out) { 
        cout << "Nepavyko sukurti failo: " << failoVardas << endl; 
        return; 
    }

    
    out << setw(15) << left << "Vardas" << setw(15) << left << "Pavarde";
    for (int j = 1; j <= nd_kiekis; j++) out << "ND" << j << " ";
    out << "Egzaminas" << endl;

    for (int i = 1; i <= dydis; i++) {
        out << setw(15) << left << "Vardas" + to_string(i)
            << setw(15) << left << "Pavarde" + to_string(i);
        for (int j = 0; j < nd_kiekis; j++) out << atsitiktinisbalas(1, 10) << " ";
        out << atsitiktinisbalas(1, 10) << endl;
    }
    out.close();

    t.save();     
    cout << "Sukurtas failas: " << failoVardas 
         << " (" << dydis << " įrašų, ND=" << nd_kiekis << ")" << endl;
}


template <typename Container>
Container nuskaitytiIsFailo(const string& failoVardas) {
    Timer t("Failo nuskaitymas");
    Container grupe;
    ifstream failas(failoVardas);
    if (!failas) { 
        cout << "Nepavyko atidaryti failo: " << failoVardas << endl; 
        return grupe; 
    }

    string eilute;
    getline(failas, eilute); // praleidžiame antraštę

    while (getline(failas, eilute)) {
        if (eilute.empty()) continue;

        Studentas s;
        vector<double> nd;
        string token;
        istringstream ss(eilute);
        string vardas, pavarde;
        ss >> vardas >> pavarde;

        s.setVardas(vardas);
        s.setPavarde(pavarde);

        double egz = 0.0;
        while (ss >> token) {
            try {
                double balas = stod(token);
                nd.push_back(balas);
            } catch (...) {
                cout << "Įspėjimas: praleistas neteisingas balas \"" << token << "\" studentui " << vardas << " " << pavarde << endl;
            }
        }

        if (!nd.empty()) {
            egz = nd.back();
            nd.pop_back();
        }
        s.setNd(nd);
        s.setEgzaminas(egz);
        s.skaiciuotiGalutinius();

        grupe.push_back(s);
    }

    cout << "Sėkmingai nuskaityta " << grupe.size() << " studentų iš failo." << endl;
    t.save();
    return grupe;
}


template <typename Container>
void irasytiStudentusIFaila(const Container& stud, Metodas metodas, const string& failoVardas){
    Timer t("Įrašymas į failus");
    ofstream out(failoVardas);
    if(!out){ 
        cout << "Nepavyko sukurti failo: " << failoVardas << endl; 
        return; 
    }

    for(const auto& s : stud){
        double galutinis;
        if (metodas == Metodas::Vidurkis) galutinis = s.galutinisVid();
        else if (metodas == Metodas::Mediana) galutinis = s.galutinisMed();
        else galutinis = (s.galutinisVid() + s.galutinisMed()) / 2.0;

        out << s.vardas() << " " << s.pavarde() << " " << fixed << setprecision(2) << galutinis << endl;
    }

    out.close();
    t.save();
}


template std::vector<Studentas> nuskaitytiIsFailo<std::vector<Studentas>>(const std::string&);
template std::list<Studentas> nuskaitytiIsFailo<std::list<Studentas>>(const std::string&);
template void irasytiStudentusIFaila<std::vector<Studentas>>(const std::vector<Studentas>&, Metodas, const std::string&);
template void irasytiStudentusIFaila<std::list<Studentas>>(const std::list<Studentas>&, Metodas, const std::string&);