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
extern double RevaccinationSpeed;

extern double Contagiousness;
extern double SuperSpreaderProb;
extern double SuperSpreaderMultiCoef;

extern double RandomNeighbourChance;

extern double InfectionStateTransitionRatio;

extern std::vector<double> ContagiousnessByState;
extern std::vector<double> InitInfectionStateProbDistr;


//globalni statistiky
extern std::vector<int> DeathCounter;
extern std::vector<int> InfectedCounter;
extern std::vector<int> NoSymptomCounter;
extern std::vector<int> SymptomCounter;
extern std::vector<int> RiskCounter;

extern std::vector<int> TotalVaccinated;
extern std::vector<int> TotalImmuned;

extern double TotalStatVaccinationMortalityThreshold;
extern double TotalStatImmunedMortalityThreshold;

extern std::vector<double> MeanVaccinationMortalityCoef;
extern std::vector<double> MeanVaccinationInfectionCoef;
extern std::vector<double> MeanImmunityMortalityCoef;
extern std::vector<double> MeanImmunityInfectionCoef;

//random generatory
extern std::mt19937 mt;
extern std::uniform_real_distribution<> PercentageDis;
extern std::uniform_int_distribution<> IntegerDis;
extern std::normal_distribution<> NormalDis;

#endif