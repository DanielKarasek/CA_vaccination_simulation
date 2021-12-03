#include <random>
#include "globals.hpp"

double mortality = 0.10;

std::uniform_real_distribution<> dis(0,1);
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<> dis_int(0, 1000000);
std::normal_distribution<> normalDis(0,1);