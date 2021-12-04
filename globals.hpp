#ifndef GLOBALS_H 
#define GLOBALS_H
#include <random>
#include <vector>

//globalni promenne automatu
extern double Mortality;

extern double VaccineDecayInfection;
extern double ImmunityDecayInfection;
extern double VaccineDecayMortality;
extern double ImmunityDecayMortality; 

extern double VaccineLinearDecayInfection;
extern double ImmunityLinearDecayInfection;
extern double VaccineLinearDecayMortality;
extern double ImmunityLinearDecayMortality;

extern double VaccineLinearInfectionThreshold;
extern double ImmunityLinearInfectionThreshold;
extern double VaccineLinearMortalityThreshold;
extern double ImmunityLinearMortalityThreshold;

extern double VaccineStartInfection;
extern double ImmunityStartInfection;
extern double VaccineStartMortality;
extern double ImmunityStartMortality;

extern double VaccineStartSTD;
extern double ImmunityStartSTD;

extern double RevaccinationInfectionBasedThreshold;
extern bool AutoRevaccinate;

extern double Contagiousness;
extern double SuperSpreaderProb;
extern double SuperSpreaderMultiCoef;


//globalni statistiky
extern std::vector<int> DeathCounter;
extern std::vector<int> InfectedCounter;

//random generatory
extern std::mt19937 mt;
extern std::uniform_real_distribution<> PercentageDis;
extern std::uniform_int_distribution<> IntegerDis;
extern std::normal_distribution<> NormalDis;

#endif