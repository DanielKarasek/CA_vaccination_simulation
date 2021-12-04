#include <iostream>
#include "human.hpp"
#include "globals.hpp"


double clip(double n, double lower, double upper) {
  return std::max(lower, std::min(n, upper));
}

Human::Human(const Human& orig){
  this->m_currentState = orig.m_currentState;
  this->m_neighbours = orig.m_neighbours;
}

void Human::step()
{ 
  if (m_currentState == Ill)
  {
    m_nextState = Healthy;    
    for (auto human : this->m_neighbours)
      human->tryInfect(m_contagiousnessCoeff); 
    if (PercentageDis(mt) < Mortality*(1-m_immunityMortalityCoef)*(1-m_vaccinationMortalityCoef))
      m_nextState = Dead;

    m_immunityInfectionCoef = ImmunityStartInfection + NormalDis(mt) * ImmunityStartSTD;
    m_immunityMortalityCoef = ImmunityStartMortality + NormalDis(mt) * ImmunityStartSTD;
  }
  double tmp_vacc = m_vaccinationInfectionCoef;
  decayDefense();
  if (AutoRevaccinate &&
      tmp_vacc>=RevaccinationInfectionBasedThreshold &&
      m_vaccinationInfectionCoef<RevaccinationInfectionBasedThreshold){
    this->vaccinate(); 
  }
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
  if (!this->isDead()){
    this->m_nextState=Ill;
    if (PercentageDis(mt) < SuperSpreaderProb){
      m_contagiousnessCoeff = Contagiousness * SuperSpreaderMultiCoef;
    }
    else{
      m_contagiousnessCoeff = Contagiousness;
    }
  }
}

void Human::addNeighbourBidirectional(Human *newNeighbour)
{
  m_neighbours.push_back(newNeighbour);
  newNeighbour->addNeighbourUnidirection(this);
}

bool Human::isInfectable()
{
  return !(this->isIll() || this->isDead());
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


std::ostream& operator<<(std::ostream& os, const Human& human){
  switch (human.m_currentState){
    case Healthy:
      os << "H";
      break;
    case Ill:
      os << "I";
      break;
    case Dead:
      os << "D";
      break;
  }
  return os;
}