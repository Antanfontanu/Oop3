#include "meniu.h"
#include "mylib.h"
#include "timer.h"
#include "studentas.h"  

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


int atsitiktinisbalas(int min, int max) {
    return min + rand() % (max - min + 1);
}