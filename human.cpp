#include <iostream>

#include "human.h"
#include "globals.h"
#include "auxilary.h"





Human::Human(const Human& orig){
  this->m_currentState = orig.m_currentState;
  this->m_neighbours = orig.m_neighbours;
}

//todo rozdelit na 3 casti -> contagiousness, mortality
void Human::step()
{ 
  if (this->isIll())
  {
    switch (m_currentState){
      case Ill:
        infectedStep(Symptomatic, ContagiousnessByState[0]);
        break;
      case Symptomatic:
        infectedStep(HardCovRisk, ContagiousnessByState[1]);
        break;
      case HardCovRisk:
        for (auto human : this->m_neighbours)
          human->tryInfect(m_contagiousnessCoeff*ContagiousnessByState[2]);
        if (PercentageDis(mt) < Mortality)
          m_nextState = Dead;
        else
          this->getCured();
        break;
    }
  }
  decayDefense();
  if (AutoRevaccinate)
    this->autoRevactination();
}

void Human::autoRevactination(){
  if (!this->isIll() &&
      m_vaccinationInfectionCoef < RevaccinationInfectionBasedThreshold && 
      m_vaccinationInfectionCoef > 0 &&
      PercentageDis(mt) < RevaccinationSpeed){
    this->vaccinate(); 
  }
}

void Human::infectedStep(HumanState nextState, double contagiousnessRatio){
  double continueInfectionChance;
  double deathLoweringCoef = (1-m_immunityMortalityCoef)*(1-m_vaccinationMortalityCoef);
  for (auto human : this->m_neighbours)
    human->tryInfect(m_contagiousnessCoeff*contagiousnessRatio);
  if(m_currentState == Ill){
    continueInfectionChance = 4/(Mortality*std::sqrt(deathLoweringCoef));
  }
  else if(m_currentState == Symptomatic){
    continueInfectionChance = 0.25/(Mortality*std::sqrt(deathLoweringCoef));
  }
  
  continueInfectionChance = Mortality*deathLoweringCoef*continueInfectionChance;
  if (PercentageDis(mt) < continueInfectionChance)
    this->getCured();
  else
    m_nextState = nextState;
}

void Human::getCured(){
  m_nextState = Healthy;
  m_immunityInfectionCoef = ImmunityStartInfection + NormalDis(mt) * ImmunityStartSTD;
  m_immunityMortalityCoef = ImmunityStartMortality + NormalDis(mt) * ImmunityStartSTD;
}


void Human::tryInfect(double exposureCoef)
{
  if (this->isInfectable() &&
      PercentageDis(mt) < exposureCoef*(1-m_vaccinationInfectionCoef)*(1-m_immunityInfectionCoef)){
    this->infect();
  }
}

void Human::vaccinate(){
  m_vaccinationInfectionCoef = VaccineStartInfection + NormalDis(mt) * VaccineStartSTD;
  m_vaccinationMortalityCoef = VaccineStartMortality + NormalDis(mt) * VaccineStartSTD;
}

void Human::infect(){
  if (isInfectable()){
    this->m_nextState=Ill;
    if (PercentageDis(mt) < SuperSpreaderProb){
      m_contagiousnessCoeff = Contagiousness * SuperSpreaderMultiCoef;
    }
    else{
      m_contagiousnessCoeff = Contagiousness;
    }
  }
}

bool Human::isInfectable()
{
  return !(this->isIll() || this->isDead());
}

bool Human::statGatherer(std::string data2gather){
  if (!data2gather.compare("Ill"))
    return isIll();
  else if (!data2gather.compare("NoSymptom"))
    return isNoSymptom();
  else if (!data2gather.compare("Symptom"))
    return isSymptom();
  else if (!data2gather.compare("Risk"))
    return isRisk();
  else if (!data2gather.compare("Dead"))
    return isDead();
  std::cout <<"err";
  return false;
}

void Human::addNeighbourBidirectional(Human *newNeighbour)
{
  m_neighbours.push_back(newNeighbour);
  newNeighbour->addNeighbourUnidirection(this);
}

void Human::setImmunCoefs(double newCoef){
  newCoef = clip(newCoef, 0.01, 1);
  m_immunityInfectionCoef = newCoef;
  int count{};
  if (newCoef > ImmunityLinearInfectionThreshold){
    count = ceil((newCoef - ImmunityStartInfection)/ImmunityLinearDecayInfection);
  }
  else{
    count = ceil((ImmunityStartInfection - ImmunityLinearInfectionThreshold)/ImmunityLinearDecayInfection);
    count += ceil(log(newCoef/ImmunityLinearInfectionThreshold)/log(ImmunityDecayInfection));
  }
  m_immunityMortalityCoef = ImmunityStartMortality;
  for (; count>0;count--)
    decayImmunityMortality();
}

void Human::setVaccinCoefs(double newCoef){
  newCoef = clip(newCoef, 0.01, 1);
  m_vaccinationInfectionCoef = newCoef;
  int count{};
  if (newCoef > VaccineLinearInfectionThreshold){
    count = ceil((newCoef - VaccineStartInfection)/VaccineLinearDecayInfection);
  }
  else{
    count = ceil((VaccineStartInfection - VaccineLinearInfectionThreshold)/VaccineLinearDecayInfection);
    count += ceil(log(newCoef/VaccineLinearInfectionThreshold)/log(VaccineDecayInfection));
  }
  m_vaccinationMortalityCoef = VaccineStartMortality;
  for (; count>0;count--)
    decayVaccinationMortality();
}

int Human::spreadInfection2NeigboursGuaranted(int count)
{
  int countSpread{};
  double normalSTD = 0.1;
  for (auto human : m_neighbours)
  {
    if (!human->isIll() && !(human->m_nextState == Ill))
    {
      human->infect();
      countSpread++;
      if (countSpread == count)
        break;
    }
  }
  return count - countSpread;
}

int Human::spreadImmun2Neighbours(int count)
{
  int countSpread{};
  double normalSTD = 0.05;
  for (auto human : m_neighbours)
  {
    if (human->getImmunInfectionCoef() == 0)
    {
      human->setImmunCoefs(m_immunityInfectionCoef+NormalDis(mt)*normalSTD);
      countSpread++;
      if (countSpread == count)
        break;
    }
  }
  return count - countSpread;
}
int Human::spreadVaccine2Neighours(int count)
{
  int countSpread{};
  double normalSTD = 0.05;
  for (auto human : m_neighbours)
  {
    if (human->getVaccinInfectionCoef() == 0)
    {
      human->setVaccinCoefs(m_vaccinationInfectionCoef+NormalDis(mt)*normalSTD);
      countSpread++;
      if (countSpread == count)
        break;
    }
  }
  return count - countSpread;
}


void Human::decayDefense(){
  this->decayVaccinationInfecion();
  this->decayVaccinationMortality();
  this->decayImmunityInfecion();
  this->decayImmunityMortality();
}

void Human::decayVaccinationInfecion(){
  if (m_vaccinationInfectionCoef > VaccineLinearInfectionThreshold)
    m_vaccinationInfectionCoef -= VaccineLinearDecayInfection;
  else 
    m_vaccinationInfectionCoef *= VaccineDecayInfection;
}
void Human::decayVaccinationMortality(){
  if (m_vaccinationMortalityCoef > VaccineLinearMortalityThreshold)
    m_vaccinationMortalityCoef -= VaccineLinearDecayMortality;
  else 
    m_vaccinationMortalityCoef *= VaccineDecayMortality;
}
void Human::decayImmunityInfecion(){
  if (m_immunityInfectionCoef > ImmunityLinearInfectionThreshold)
    m_immunityInfectionCoef -= ImmunityLinearDecayInfection;
  else 
    m_immunityInfectionCoef *= ImmunityDecayInfection;
}
void Human::decayImmunityMortality(){  
  if (m_immunityMortalityCoef > ImmunityLinearMortalityThreshold)
    m_immunityMortalityCoef -= ImmunityLinearDecayMortality;
  else 
    m_immunityMortalityCoef *= ImmunityDecayMortality;
}



std::ostream& operator<<(std::ostream& os, const Human& human){
  switch (human.m_currentState){
    case Healthy:
      os << "H";
      break;
    case Dead:
      os << "D";
      break;
    case Ill:
      os << "1";
      break;
    case Symptomatic:
      os << "S";
      break;
    case HardCovRisk:
      os << "X";
      break;
  }
  return os;
}