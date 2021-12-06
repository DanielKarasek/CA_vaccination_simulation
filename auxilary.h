#include <vector>
#include <iostream>
#include "globals.h"

//zda maji 2 vektory stejnou delku
bool checkVectorsLenght(std::vector<double> first, std::vector<double> second);
//Zda vektor sumuje do 1 +- 0.02
bool summs2one(std::vector<double> toCheck);

//Vytvari vektor na nahodne unique cisla do desired velikosti
std::vector<int> getShuffledVector(int desiredSize);

double clip(double n, double lower, double upper);

void printStats(std::ostream &os, int form);

template <typename T>
void printStatVector(std::ostream &os, std::string name, std::vector<T> vector);