#include <random>
#include "globals.hpp"

int mortality = 30;
int contagiousness = 40;

std::uniform_real_distribution<> dis(0,100);
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<> dis_int(0, 1000000);