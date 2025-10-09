# OOP
v.03 - release
## Atnaujinimai
Pridėtas pasirinkimas su kuriais vektoriais norime dirbti <br> 
Taip pat pridėtas atsitiktinis failų generavimas. <br>
bei studentų skirstymas grupėmis pagal jų rezultatus. <br>



## Programos spartos analizė

Laiko testavimas buvo atliktas su vektoriaus ir sąrašo konteineriais, naudoti tie patys sugeneruoti failai su 5 namų darbų pažymiais, laikui imtas 3 bandymų vidurkis
### Testavimo sistemos parametrai
CPU: AMD Ryzen 5 7535U with Radeon Graphics 2.90 GHz
RAM: 16GB (13.7GB naudojami)<br>
HDD: SSD 512GB (SKHynix HFS512GEJ4X112N) <br>
### Laiko matavimo metodas
Buvo naudota naudota C++ biblioteka chrono
### Testuoti failai:
studentas1000.txt - 1000 studentų <br>
studentas10000.txt - 10000 studentų <br>
studentas100000.txt - 100000 studentų <br>
studentas1000000.txt - 1000000 studentų <br> 
studentas10000000.txt - 10000000 studentų <br>
#### Kodas:
```cpp
auto start = high_resolution_clock::now();
auto end = high_resolution_clock::now();
auto duration = duration_cast<milliseconds>(end - start).count();
```

### Testevimo kategorijos
1 Failų kūrimas <br>
2 Duomenų nuskaitymas iš failų <br>
3 Studentų rūšiavimas į dvi grupes <br>
4 Surūšiuotų studentų išvedimas į vargšiukai.txt <br>
5 Surūšiuotų studentų išvedimas į kietiakai.txt <br>
### Rezultatų lentelė
### Testavimas su vektoriaus konteineriu

| Failas                 | Failo kūrimas | Duomenų nuskaitymas | Studentų rūšiavimas | Išvedimas į kietiakai |Išvedimas į vargšiukai|
|:------------------------|:--------------|:--------------------|:--------------------|:-------------------|:-------------------|
| studentas1000.txt       | 5.4 s         | 0.008 s             | 0 s                 | 0.004 s            | 0.01 s             |
| studentas10000.txt      | 4.9 s         | 0.048 s             | 0.003 s             | 0.048 s            | 0.044 s            |
| studentas100000.txt     | 7.1 s         | 0.445 s             | 0.049 s             | 0.388 s            | 0.282 s            |
| studentas1000000.txt    | 16.7 s        | 3.21 s              | 0.304 s             | 4.51 s             | 3.12 s             |
| studentas10000000.txt   | 111.6 s       | 34.3 s              | 3.1 s               | 56.12 s            | 64.33 s            |

### Testavimas su sąrašo konteineriu

| Failas                 | Failo kūrimas | Duomenų nuskaitymas | Studentų rūšiavimas | Išvedimas į kietiakai |Išvedimas į vargšiukai|
|:------------------------|:--------------|:--------------------|:--------------------|:-------------------|:-------------------|
| studentas1000.txt       | 5.4 s         | 0.008 s             | 0 s                 | 0.04 s             | 0.049 s            |
| studentas10000.txt      | 4.9 s         | 0.057 s             | 0.003 s             | 0.133 s            | 0.049 s            |
| studentas100000.txt     | 7.1 s         | 0.567 s             | 0.049 s             | 1.615 s            | 0.049 s            |
| studentas1000000.txt    | 16.7 s        | 4.21 s              | 0.504 s             | 10.7 s             | 0.049 s            |
| studentas10000000.txt   | 111.6 s       | 39.3 s              | 3.8 s               | 121.1 s            | 0.049 s            |
