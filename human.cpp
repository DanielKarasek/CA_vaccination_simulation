#include <iostream>
#include "human.hpp"
#include "globals.hpp"

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
      human->tryInfect(1); 
    if (dis(mt) < mortality)
      m_nextState = Dead;
  }
}
void Human::spreadInfection2NeigboursGuaranted(int count)
{
  int countSpread{};
  double normalSTD = 0.1;
  for (auto human : m_neighbours)
  {
    if (!human->isIll() || !(human->m_nextState ==Ill))
    {
      human->infect();
      countSpread++;
      if (countSpread == count)
        break;
    }
  }
}

void Human::spreadImmun2Neighbours(int count)
{
  int countSpread{};
  double normalSTD = 0.05;
  for (auto human : m_neighbours)
  {
    if (human->getImmunCoef() == 0)
    {
      human->setImmunCoef(m_immunityCoef+normalDis(mt)*normalSTD);
      countSpread++;
      if (countSpread == count)
        break;
    }
  }
}
void Human::spreadVaccine2Neighours(int count)
{
  int countSpread{};
  double normalSTD = 0.05;
  for (auto human : m_neighbours)
  {
    if (human->getVaccinCoef() == 0)
    {
      human->setVaccinCoef(m_vaccinationCoef+normalDis(mt)*normalSTD);
      countSpread++;
      if (countSpread == count)
        break;
    }
  }
}

void Human::tryInfect(double exposureCoef)
{
  if (this->isInfectable() &&
      dis(mt) < exposureCoef*(1-m_vaccinationCoef)*(1-m_immunityCoef)){
    m_nextState = Ill;
    m_immunityCoef = 0.8;
  }
}

bool Human::isIll()
{
  return m_currentState == Ill;
}

bool Human::isInfectable()
{
  return !(this->isIll() || m_currentState == Dead || m_nextState == Dead);
}

void Human::addNeighbourBidirectional(Human *newNeighbour)
{
  m_neighbours.push_back(newNeighbour);
  newNeighbour->addNeighbourUnidirection(this);
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