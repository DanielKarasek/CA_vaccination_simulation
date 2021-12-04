#include <random>
#include "globals.hpp"

double Mortality = 0.10;

double VaccineDecayInfection   = 0.9;
double ImmunityDecayInfection  = 0.9;
double VaccineDecayMortality   = 0.9;
double ImmunityDecayMortality  = 0.9; 

double VaccineLinearDecayInfection  = 0.02;
double ImmunityLinearDecayInfection = 0.02;
double VaccineLinearDecayMortality  = 0.003;
double ImmunityLinearDecayMortality = 0.02;

double VaccineLinearInfectionThreshold   = 0.85;
double ImmunityLinearInfectionThreshold  = 0.85;
double VaccineLinearMortalityThreshold   = 0.85;
double ImmunityLinearMortalityThreshold  = 0.85;

double VaccineStartInfection  = 0.9;
double ImmunityStartInfection = 0.9;
double VaccineStartMortality  = 0.9;
double ImmunityStartMortality = 0.9;

double VaccineStartSTD = 0.06;
double ImmunityStartSTD = 0.06;
//Stats
std::vector<int> DeathCounter{};
std::vector<int> InfectedCounter{};

//Random generators
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<> PercentageDis(0,1);
std::uniform_int_distribution<> IntegerDis(0, 1000000);
std::normal_distribution<> NormalDis(0,1);