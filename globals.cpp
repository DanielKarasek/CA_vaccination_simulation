#include <random>
#include "globals.hpp"

double Mortality = 0.0075;

double VaccineDecayInfection   = 0.92;
double ImmunityDecayInfection  = 0.92;
double VaccineDecayMortality   = 0.95;
double ImmunityDecayMortality  = 0.95; 

double VaccineLinearDecayInfection  = 0.0258;
double ImmunityLinearDecayInfection = 0.02;
double VaccineLinearDecayMortality  = 0.0009;
double ImmunityLinearDecayMortality = 0.0009;

double VaccineLinearInfectionThreshold   = 0.7;
double ImmunityLinearInfectionThreshold  = 0.7;
double VaccineLinearMortalityThreshold   = 0.7;
double ImmunityLinearMortalityThreshold  = 0.7;

double VaccineStartInfection  = 0.83;
double ImmunityStartInfection = 0.9;
double VaccineStartMortality  = 0.98;
double ImmunityStartMortality = 0.95;

double VaccineStartSTD = 0.07;
double ImmunityStartSTD = 0.07;

double RevaccinationInfectionBasedThreshold = 0.5;
bool AutoRevaccinate = true;
double RevaccinationSpeed = 0.8; // if 1, vaccination comes instantly, if 0, vaccination does not come ever, 0.5 is 50 % chance during step

double Contagiousness = 0.31;
double SuperSpreaderProb = 0.35;
double SuperSpreaderMultiCoef = 10;

//Stats
std::vector<int> DeathCounter{};
std::vector<int> InfectedCounter{};

//Random generators
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<> PercentageDis(0,1);
std::uniform_int_distribution<> IntegerDis(0, 1000000);
std::normal_distribution<> NormalDis(0,1);