#include <random>
#include "globals.hpp"

double mortality = 0.10;
std::vector<int> DeathCounter{};
std::vector<int> InfectedCounter{};


std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<> PercentageDis(0,1);
std::uniform_int_distribution<> IntegerDis(0, 1000000);
std::normal_distribution<> NormalDis(0,1);