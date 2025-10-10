
#include "mylib.h"
#include "studentas.h"
#include "failai.h"
#include "meniu.h"
#include "timer.h"

using namespace std;
using namespace std::chrono;


template <typename Container>

void paleistiPrograma(Container &Grupe) {
    int pasirinkimas;

    while (true) {
        cout << "\n======= Meniu =======\n";
        cout << "1 - Įvesti studentus\n";
        cout << "2 - Nuskaityti studentus iš failo\n";
        cout << "3 - Parodyti rezultatų lentelę\n";
        cout << "4 - Testavimas pagal failą\n";
        cout << "5 - Generuoti atsitiktinius studentų failus\n";
        cout << "6 - Padalinti studentus į grupes (vargšiukai/kietiakai)\n";
        cout << "7 - Baigti programą\n";
        cout << "=====================\n";

        pasirinkimas = ivestiSk("Pasirinkimas: ", 1, 7);

        if (pasirinkimas == 1) {
            int m = ivestiSk("Kiek studentų grupėje: ", 1);
            for (int z = 0; z < m; z++) Grupe.push_back(Stud_iv());

            
            mSort(Grupe, [](const Studentas& a, const Studentas& b){ return a.pav < b.pav; });


        }else if (pasirinkimas == 2) {
            cout << "Pasirinkite, iš kurio failo nuskaityti studentus:\n";
            cout << "1 - kursiokai.txt\n";
            cout << "2 - studentas1000.txt\n";
            cout << "3 - studentas10000.txt\n";
            cout << "4 - studentas100000.txt\n";
            cout << "5 - studentas1000000.txt\n";
            cout << "6 - studentas10000000.txt\n";

            int f = ivestiSk("Pasirinkimas: ", 1, 6);
            string failoKelias;

            switch (f) {
                case 1: failoKelias = "kursiokai.txt"; break;
                case 2: failoKelias = "studentas1000.txt"; break;
                case 3: failoKelias = "studentas10000.txt"; break;
                case 4: failoKelias = "studentas100000.txt"; break;
                case 5: failoKelias = "studentas1000000.txt"; break;
                case 6: failoKelias = "studentas10000000.txt"; break;
            }

            if (!filesystem::exists(failoKelias)) {
                 cout << "Failo \"" << failoKelias << "\" nėra! "
                    << "Pirmiausia sugeneruokite jį (naudokite meniu nr 5)." << endl;
                continue;
            }

            

            
            Container failoGrupe = nuskaitytiIsFailo<Container>(failoKelias);
            Grupe.insert(Grupe.end(), failoGrupe.begin(), failoGrupe.end());
            cout << "Nuskaityta " << failoGrupe.size() << " studentų." << endl;
        }

        else if (pasirinkimas == 3) {
            if (Grupe.empty()) { cout << "Turi būti įvestas bent vienas studentas " << endl; continue; }

            cout << "Pasirinkite galutinio balo skaičiavimo metodą:"<< endl;
            cout << "1 - Vidurkis" << endl;
            cout << "2 -  Mediana" << endl;
            cout << "3 - Abu" << endl;
            int metodas = ivestiSk("Pasirinkimas: ", 1, 3);

            cout << "Pasirinkite rikiavimo kriterijų:\n";
            cout << "1 - Pagal vardą" << endl;
            cout << "2 - Pagal pavardę" << endl;
            cout << "3 - Pagal galutinį pažymį" << endl;
            int kriterijus = ivestiSk("Pasirinkimas: ", 1,3);

            surikiuotiStudentus(Grupe, kriterijus, Metodas(metodas));
            spausdintiLentele(Grupe, Metodas(metodas));
        }

        else if (pasirinkimas == 4) {
            cout << "Pasirinkite failą testavimui:\n";
            cout << "1 - studentai10000.txt\n";
            cout << "2 - studentai100000.txt\n";
            cout << "3 - studentai1000000.txt\n";
            int failoPasirinkimas = ivestiSk("Pasirinkimas: ", 1, 3);

            string failoKelias;
            if (failoPasirinkimas == 1) failoKelias = "studentai10000.txt";
            else if (failoPasirinkimas == 2) failoKelias = "studentai100000.txt";
            else failoKelias = "studentai1000000.txt";

            
            Container testGrupe = nuskaitytiIsFailo<Container>(failoKelias);
            if (testGrupe.empty()) { cout << "Failas tuščias arba jo nepavyko atidaryti." << endl; continue; }
            mSort(testGrupe, [](const Studentas &a, const Studentas &b){ return a.pav < b.pav; });

            

            ofstream fout("testavimo_rezultatai.txt");
            if (!fout) { cout << "Nepavyko sukurti rezultatų failo!" << endl; continue; }
            
            fout << "Testavimo rezultatai:\n";
            spausdintiLentele(testGrupe, Metodas::Abu, fout);
            fout.close();

            cout << "Rezultatai įrašyti į testavimo_rezultatai.txt" << endl;
        }

        else if (pasirinkimas == 5) {
            generuotiFailus();
        }

        else if (pasirinkimas == 6) {
            if (Grupe.empty()) { cout << "Pirmiau įveskite studentus." << endl; continue; }

            cout << "Pasirinkite galutinio balo skaičiavimo metodą:\n";
            cout << "1 - Vidurkis" << endl;
            cout << "2 - Mediana" << endl;
            cout << "3 - Abu" << endl;
            int metodas = ivestiSk("Pasirinkimas: ", 1, 3);

            Container vargsiukai, kietiakai;
            padalintiStudentus(Grupe, vargsiukai, kietiakai, Metodas(metodas));

            cout << "Pasirinkite rikiavimo kriterijų:\n";
            cout << "1 - Pagal vardą" << endl;
            cout << "2 - Pagal pavardę" << endl;
            cout << "3 - Pagal galutinį pažymį" << endl;
            int kriterijus = ivestiSk("Pasirinkimas: ", 1,3);

            surikiuotiStudentus(vargsiukai, kriterijus, Metodas(metodas));
            surikiuotiStudentus(kietiakai, kriterijus, Metodas(metodas));

            
            irasytiStudentusIFaila(vargsiukai, Metodas(metodas), "vargsiukai.txt");
           
            irasytiStudentusIFaila(kietiakai, Metodas(metodas), "kietiakai.txt");
           

        }else if (pasirinkimas == 7) {
            cout << "Programa baigta." << endl;
            break;
        }
    }
}


int main() {
    srand((unsigned)system_clock::now().time_since_epoch().count());

    cout << "Pasirinkite konteinerio tipą:\n1 - std::vector\n2 - std::list\n";
    int tipas = ivestiSk("Pasirinkimas: ", 1, 2);

    if (tipas == 1) {
        cout << "\nNaudojamas konteineris: std::vector\n";
        vector<Studentas> Grupe;
        paleistiPrograma(Grupe);
    } 
    else {
        cout << "\nNaudojamas konteineris: std::list\n";
        list<Studentas> Grupe;
        paleistiPrograma(Grupe);
        
    }
    cout << "\n==== Visų matuotų laikų suvestinė ====\n";
    Timer::showAll();
    return 0;
}
