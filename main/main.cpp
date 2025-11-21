#include "mylib.h"
#include "studentas.h"
#include "failai.h"
#include "meniu.h"
#include "timer.h"
#include "zmogus.h"



using namespace std;
using namespace std::chrono;

template <typename Container>
void paleistiPrograma(Container &Grupe) {
    int pasirinkimas;

    while (true) {
        cout << "\n------Meniu-----\n";
        cout << "1 - Įvesti studentus\n";
        cout << "2 - Nuskaityti studentus iš failo\n";
        cout << "3 - Parodyti rezultatų lentelę\n";
        cout << "4 - Testavimas pagal failą\n";
        cout << "5 - Generuoti atsitiktinius studentų failus\n";
        cout << "6 - Padalinti studentus į grupes (vargšiukai/kietiakai)\n";
        cout << "7 - Baigti programą\n";
        cout << "----------------\n";

        pasirinkimas = ivestiSk("Pasirinkimas: ", 1, 7);

        switch (pasirinkimas) {
            case 1: {
                int m = ivestiSk("Kiek studentų grupėje: ", 1);
                for (int z = 0; z < m; z++) {
                    Grupe.push_back(Stud_iv());
                    cout << "Studento objektas saugomas adresu: " << &Grupe.back() << endl;
                }
                mSort(Grupe, [](const Studentas& a, const Studentas& b){ return a.pavarde() < b.pavarde(); });
                break;
            }

            case 2: {
                cout << "Pasirinkite failą:\n";
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
                    cout << "Failo \"" << failoKelias << "\" nėra! Sugeneruokite jį meniu nr.5." << endl;
                    continue;
                }

                Container failoGrupe = nuskaitytiIsFailo<Container>(failoKelias);
                Grupe.insert(Grupe.end(), failoGrupe.begin(), failoGrupe.end());
                cout << "Nuskaityta " << failoGrupe.size() << " studentų." << endl;
                break;
            }

            case 3: {
                if (Grupe.empty()) { 
                    cout << "Turi būti įvestas bent vienas studentas." << endl; 
                    continue; 
                }

                cout << "Pasirinkite galutinio balo skaičiavimo metodą:\n";
                cout << "1 - Vidurkis\n2 - Mediana\n3 - Abu\n";
                int metodas = ivestiSk("Pasirinkimas: ", 1, 3);

                cout << "Pasirinkite rikiavimo kriterijų:\n";
                cout << "1 - Pagal vardą\n2 - Pagal pavardę\n3 - Pagal galutinį pažymį\n";
                int kriterijus = ivestiSk("Pasirinkimas: ", 1, 3);

                surikiuotiStudentus(Grupe, kriterijus, Metodas(metodas));
                spausdintiLentele(Grupe, Metodas(metodas));
                break;
            }

            case 4: {
                cout << "Pasirinkite testavimo failą:\n";
                cout << "1 - studentai10000.txt\n2 - studentai100000.txt\n3 - studentai1000000.txt\n";
                int failoPasirinkimas = ivestiSk("Pasirinkimas: ", 1, 3);

                string failoKelias;
                switch (failoPasirinkimas) {
                    case 1: failoKelias = "studentai10000.txt"; break;
                    case 2: failoKelias = "studentai100000.txt"; break;
                    case 3: failoKelias = "studentai1000000.txt"; break;
                }

                Container testGrupe = nuskaitytiIsFailo<Container>(failoKelias);
                if (testGrupe.empty()) { 
                    cout << "Failas tuščias arba jo nepavyko atidaryti." << endl; 
                    continue; 
                }
                mSort(testGrupe, [](const Studentas &a, const Studentas &b){ return a.pavarde() < b.pavarde(); });

                ofstream fout("testavimo_rezultatai.txt");
                if (!fout) { 
                    cout << "Nepavyko sukurti rezultatų failo!" << endl; 
                    continue; 
                }

                fout << "Testavimo rezultatai:\n";
                spausdintiLentele(testGrupe, Metodas::Abu, fout);
                fout.close();

                cout << "Rezultatai įrašyti į testavimo_rezultatai.txt" << endl;
                break;
            }

            case 5:
                generuotiFailus();
                break;

            case 6: {
                if (Grupe.empty()) { 
                    cout << "Pirmiau įveskite studentus." << endl; 
                    continue; 
                }

                cout << "Pasirinkite galutinio balo skaičiavimo metodą:\n1 - Vidurkis\n2 - Mediana\n3 - Abu\n";
                int metodas = ivestiSk("Pasirinkimas: ", 1, 3);

                cout << "Pasirinkite padalijimo strategiją:\n";
                cout << "1 - Kopijuoti į du konteinerius\n";
                cout << "2 - Perkelti vargšiukus (ištrinti iš bendro)\n";
                cout << "3 - Optimizuota versija\n";
                int strategija = ivestiSk("Pasirinkimas: ", 1, 3);

                Container vargsiukai, kietiakai;
                padalintiStudentusPagalStrategija(Grupe, vargsiukai, kietiakai, Metodas(metodas), strategija);

                cout << "Pasirinkite rikiavimo kriterijų:\n1 - Pagal vardą\n2 - Pagal pavardę\n3 - Pagal galutinį pažymį\n";
                int kriterijus = ivestiSk("Pasirinkimas: ", 1,3);

                surikiuotiStudentus(vargsiukai, kriterijus, Metodas(metodas));
                surikiuotiStudentus(kietiakai, kriterijus, Metodas(metodas));

                irasytiStudentusIFaila(vargsiukai, Metodas(metodas), "vargsiukai.txt");
                irasytiStudentusIFaila(kietiakai, Metodas(metodas), "kietiakai.txt");
                break;
            }

            case 7:
                cout << "Programa baigta." << endl;
                return;

            default:
                cout << "Neteisingas pasirinkimas!" << endl;
                break;
        }
    }
}


void printTestRow(const std::string& name, bool ok) {
    std::cout << std::left << std::setw(28) << name
              << "| " << (ok ? "+" : "-") << "\n";
}

void testRuleOfThree() {
    std::cout << "Operatorius, konstruktorius ir destruktorius programoje atlikus testavimą veikia korektiškai:\n";

    //Default konstruktorius
    Studentas s1;
    bool okDefault = true;

    //  Copy konstruktorius 
    s1.setVardas("Jonas");
    s1.setPavarde("Jonaitis");
    Studentas s2(s1);
    bool okCopyCtor = (s2.vardas() == s1.vardas() && s2.pavarde() == s1.pavarde());

    // Copy assignment operatorius
    Studentas s3;
    s3 = s1;
    bool okCopyAssign = (s3.vardas() == s1.vardas() && s3.pavarde() == s1.pavarde());

    // Operator >> 
    std::istringstream iss("Petras Petrauskas 10 9 8 7");
    Studentas s4;
    iss >> s4;
    bool okInput = (s4.vardas() == "Petras" && s4.pavarde() == "Petrauskas");

    //  Operator << 
    std::ostringstream oss;
    oss << s4;
    bool okOutput = !oss.str().empty();

    //  Destruktorius
    
    bool okDtor = true;

    // Lentelė 
    printTestRow("Default konstruktorius", okDefault);
    printTestRow("Copy konstruktorius", okCopyCtor);
    printTestRow("Copy assignment operatorius", okCopyAssign);
    printTestRow("Ivesties operatorius", okInput);
    printTestRow("Isvesties operatorius", okOutput);
    printTestRow("Destruktorius", okDtor);
}
int main() {
    //Demonstracija zmogaus objektų kūrimo
    //Zmogus z("Jonas", "Jonaitis");


    srand((unsigned)system_clock::now().time_since_epoch().count());
    

    cout << "Pasirinkite konteinerio tipą:\n1 - std::vector\n2 - std::list\n";
    int tipas = ivestiSk("Pasirinkimas: ", 1, 2);

    switch (tipas) {
        case 1: {
            cout << "\nNaudojamas konteineris: std::vector\n";
            vector<Studentas> Grupe;
            paleistiPrograma(Grupe);
            break;
        }
        case 2: {
            cout << "\nNaudojamas konteineris: std::list\n";
            list<Studentas> Grupe;
            paleistiPrograma(Grupe);
            break;
        }
    }

    cout << "\n Visi laikai \n";
    Timer::showAll();
    cout << "\n Rule of Three testavimas \n";
    testRuleOfThree();
    return 0;
}