#ifndef GLOBALS_H 
#define GLOBALS_H
#include <random>
#include <vector>

//globalni promenne automatu
extern double mortality;

//globalni statistiky
extern std::vector<int> DeathCounter;
extern std::vector<int> InfectedCounter;

//random generatory
extern std::mt19937 mt;
extern std::uniform_real_distribution<> PercentageDis;
extern std::uniform_int_distribution<> IntegerDis;
extern std::normal_distribution<> NormalDis;

#endif