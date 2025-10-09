#pragma once
#include "studentas.h"
#include <vector>
#include <iostream>

int ivestiSk(const std::string &tekstas, int min_val=-1000000, int max_val=1000000);
template <typename Container>
void padalintiStudentus(const Container& Grupe, Container& vargsiukai, Container& kietiakai, Metodas metodas);
template <typename Container>
void surikiuotiStudentus(Container& stud, int kriterijus, Metodas metodas);


