#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"

#include "studentas.h"
#include <sstream>

//  Getteriai ir setteriai 
TEST_CASE("getteriai ir setteriai") {
    Studentas s;

    s.setVardas("Jonas");
    s.setPavarde("Jonaitis");
    s.setNd({10.0, 9.0, 8.0});
    s.setEgzaminas(9.0);

    REQUIRE(s.vardas() == "Jonas");
    REQUIRE(s.pavarde() == "Jonaitis");
    REQUIRE(s.nd().size() == 3);
    REQUIRE(s.nd()[0] == 10.0);
    REQUIRE(s.egzaminas() == 9.0);
}

//  default konstruktorius 

TEST_CASE("default konstruktorius") {
    Studentas s;

    REQUIRE(s.egzaminas() == 0.0);
    REQUIRE(s.nd().empty());
    REQUIRE(s.galutinisVid() == 0.0);
    REQUIRE(s.galutinisMed() == 0.0);
}

//  copy konstruktorius

TEST_CASE(" copy konstruktorius") {
    Studentas s1;
    s1.setVardas("Petras");
    s1.setPavarde("Petrauskas");
    s1.setNd({5.0, 6.0, 7.0});
    s1.setEgzaminas(8.0);
    s1.skaiciuotiGalutinius();   

    Studentas s2(s1);

    REQUIRE(s2.vardas() == "Petras");
    REQUIRE(s2.pavarde() == "Petrauskas");
    REQUIRE(s2.nd().size() == 3);
    REQUIRE(s2.nd()[1] == 6.0);
    REQUIRE(s2.egzaminas() == 8.0);
    REQUIRE(s2.galutinisVid() == s1.galutinisVid());
    REQUIRE(s2.galutinisMed() == s1.galutinisMed());
}

//  copy assignment operatorius 

TEST_CASE("Studentas: copy assignment operatorius perkelia duomenis") {
    Studentas s1;
    s1.setVardas("Vardas");
    s1.setPavarde("Pavardė");
    s1.setNd({9.0, 9.0});
    s1.setEgzaminas(10.0);
    s1.skaiciuotiGalutinius();

    Studentas s2;
    s2.setVardas("Tomas");
    s2.setPavarde("Tomaitis");
    s2.setNd({1.0});
    s2.setEgzaminas(2.0);

    s2 = s1; 

    REQUIRE(s2.vardas() == "Vardas");
    REQUIRE(s2.pavarde() == "Pavardė");
    REQUIRE(s2.nd().size() == 2);
    REQUIRE(s2.nd()[0] == 9.0);
    REQUIRE(s2.egzaminas() == 10.0);
    REQUIRE(s2.galutinisVid() == s1.galutinisVid());
    REQUIRE(s2.galutinisMed() == s1.galutinisMed());
}

TEST_CASE("Studentas: destruktorius korektiskai suveikia") {
    bool reachedEnd = false;

    {
        Studentas s;
        s.setVardas("Test");
        s.setPavarde("Studentas");
        s.setNd({1.0, 2.0, 3.0});
        s.setEgzaminas(5.0);
        s.skaiciuotiGalutinius();

        // Čia objektas dar gyvas
        REQUIRE(s.vardas() == "Test");
        REQUIRE(s.nd().size() == 3);

        reachedEnd = true;
    } 
   

    REQUIRE(reachedEnd);  
}
//  Operator >> 

TEST_CASE("operator>> ") {
    std::istringstream iss("Petras Petrauskas 10 9 8 7");
    Studentas s;
    iss >> s;

    REQUIRE(s.vardas() == "Petras");
    REQUIRE(s.pavarde() == "Petrauskas");
    REQUIRE_FALSE(s.nd().empty());
    REQUIRE(s.egzaminas() >= 0.0); 
}

// Operator <<

TEST_CASE(" operator<< ") {
    Studentas s;
    s.setVardas("Jonas");
    s.setPavarde("Jonaitis");
    s.setNd({10.0, 9.0});
    s.setEgzaminas(8.0);
    s.skaiciuotiGalutinius();

    std::ostringstream oss;
    oss << s;

    std::string out = oss.str();
    REQUIRE_FALSE(out.empty());
    REQUIRE(out.find("Jonas") != std::string::npos);
    REQUIRE(out.find("Jonaitis") != std::string::npos);
}
