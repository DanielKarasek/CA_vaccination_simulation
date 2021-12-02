#ifndef GLOBALS_H 
#define GLOBALS_H
#include <random>

//globalni promenne automatu
extern int mortality;
extern int contagiousness;

//random generatory
extern std::uniform_real_distribution<> dis;
extern std::mt19937 mt;
extern std::uniform_int_distribution<> dis_int;

#endif