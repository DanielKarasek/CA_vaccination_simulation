#include <random>
#include "globals.h"

//typedefs


//globalni promenne automatu
double Mortality = 0.005;


double VaccineDecayInfection   = 0.90;
double ImmunityDecayInfection  = 0.90;
double VaccineDecayMortality   = 0.90;
double ImmunityDecayMortality  = 0.90; 

double VaccineLinearDecayInfection  = 0.01;
double ImmunityLinearDecayInfection = 0.007;
double VaccineLinearDecayMortality  = 0.005;
double ImmunityLinearDecayMortality = 0.0034;

double VaccineLinearInfectionThreshold   = 0.4;
double ImmunityLinearInfectionThreshold  = 0.4;
double VaccineLinearMortalityThreshold   = 0.5;
double ImmunityLinearMortalityThreshold  = 0.5;

double VaccineStartInfection  = 0.77;
double ImmunityStartInfection = 0.93;
double VaccineStartMortality  = 0.95;
double ImmunityStartMortality = 0.95;

double VaccineStartSTD = 0.07;
double ImmunityStartSTD = 0.07;

double RevaccinationInfectionBasedThreshold = 0.00;
bool AutoRevaccinate = true;
//podeleno tremi
double RevaccinationSpeed = 0.075; // if 1, vaccination comes instantly, if 0, vaccination does not come ever, 0.5 is 50 % chance during step 

double Contagiousness = 0.25;
double SuperSpreaderProb = 0.1;
double SuperSpreaderMultiCoef = 20;

// NOVE sance ze neighbour bude mit souseda z random mista na pame (dela se ve while loopu takze pak je i tahle hodnot * tahle hodnota)
// ze bude mit dva sousedy
double RandomNeighbourChance = 0.15;
//NOVE pomer pravdepodobnosti transition Ill->symptomatic : symptomatic:HardCovRisk
double InfectionStateTransitionRatio = 2;

std::vector<double> ContagiousnessByState{0.6, 0.3, 0.1};
std::vector<double> InitInfectionStateProbDistr = {0.6, 0.3, 0.1};

//Stats
std::vector<int> DeathCounter{};
std::vector<int> InfectedCounter{};
std::vector<int> NoSymptomCounter{};
std::vector<int> SymptomCounter{};
std::vector<int> RiskCounter{};

//NOVE
std::vector<int> TotalVaccinated{};
std::vector<int> TotalImmuned{};

double TotalStatVaccinationMortalityThreshold{0.6};
double TotalStatImmunedMortalityThreshold{0.6};

std::vector<double> MeanVaccinationMortalityCoef{};
std::vector<double> MeanVaccinationInfectionCoef{};
std::vector<double> MeanImmunityMortalityCoef{};
std::vector<double> MeanImmunityInfectionCoef{};


//Random generators
std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<> PercentageDis(0,1);
std::uniform_int_distribution<> IntegerDis(0, 1000000);
std::normal_distribution<> NormalDis(0,1);