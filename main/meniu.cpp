#include "meniu.h"
#include "failai.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

int ivestiSk(const string &tekstas, int min_val, int max_val){
    int sk;
    while(true){
        cout << tekstas;
        string eil;
        getline(cin, eil);
        try{
            sk = stoi(eil);
            if(sk>=min_val && sk<=max_val) return sk;
            else cout << "Įveskite skaičių nuo " << min_val << " iki " << max_val << "." << endl;
        }catch(...){
            cout << "Įveskite tik skaičių." << endl;
        }
    }
}

void spausdintiLentele(const vector<Studentas>& Grupe, Metodas metodas,std::ostream& os){
    cout << setw(10) << left << "Vardas" << "|"
         << setw(15) << right << "Pavardė" << "|";
    if (metodas==Metodas::Vidurkis) cout << "Galutinis (Vid.)" << endl;
    else if (metodas==Metodas::Mediana) cout << "Galutinis (Med.)" << endl;
    else cout << "Galutinis (Vid.)|Galutinis (Med.)" << endl;
    cout << "------------------------------------------------" << endl;

    for (auto& s : Grupe){
        os << setw(10) << left << s.var
           << "|" << setw(15) << right << s.pav << "|";
        if (metodas==Metodas::Vidurkis) os << setw(10) << fixed << setprecision(2) << s.galVid << endl;
        else if (metodas==Metodas::Mediana) os << setw(10) << fixed << setprecision(2) << s.galMed << endl;
        else os << setw(10) << fixed << setprecision(2) << s.galVid
                << "|" << setw(10) << fixed << setprecision(2) << s.galMed << endl;
    }
}

void padalintiStudentus(const vector<Studentas>& Grupe, 
                        vector<Studentas>& vargsiukai, 
                        vector<Studentas>& kietiakai, 
                        Metodas metodas) 
{
    auto start_split = high_resolution_clock::now();

    for (const auto& s : Grupe) {
        double galutinis;
        if (metodas == Metodas::Vidurkis) galutinis = s.galVid;
        else if (metodas == Metodas::Mediana) galutinis = s.galMed;
        else galutinis = (s.galVid + s.galMed) / 2.0;

        if (galutinis < 5.0) vargsiukai.push_back(s);
        else kietiakai.push_back(s);
    }

    auto end_split = high_resolution_clock::now();
    cout << "Padalinimas į grupes užtruko: " 
         << duration_cast<milliseconds>(end_split - start_split).count() 
         << " ms" << endl;
}

void surikiuotiStudentus(vector<Studentas>& stud, int kriterijus, Metodas metodas) {
    if (kriterijus == 1) {
        sort(stud.begin(), stud.end(), [](const Studentas& a, const Studentas& b){
            return a.var < b.var;
        });
    } else if (kriterijus == 2) {
        sort(stud.begin(), stud.end(), [](const Studentas& a, const Studentas& b){
            return a.pav < b.pav; 
        });
    } else if (kriterijus == 3) {
        sort(stud.begin(), stud.end(), [metodas](const Studentas& a, const Studentas& b){
            double galA = (metodas == Metodas::Vidurkis) ? a.galVid :
                          (metodas == Metodas::Mediana) ? a.galMed :
                          (a.galVid + a.galMed)/2.0;
            double galB = (metodas == Metodas::Vidurkis) ? b.galVid :
                          (metodas == Metodas::Mediana) ? b.galMed :
                          (b.galVid + b.galMed)/2.0;
            return galA > galB;
        });
    }
}

