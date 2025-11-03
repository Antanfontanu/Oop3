#pragma once
#include "studentas.h"
#include "mylib.h"



template <typename Container>
Container nuskaitytiIsFailo(const std::string& failoVardas);

template <typename Container>
void irasytiStudentusIFaila(const Container& stud, Metodas metodas, const std::string& failoVardas);
void generuotiFailus();


