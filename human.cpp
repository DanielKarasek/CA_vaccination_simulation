#include <iostream>
#include "human.hpp"
#include "globals.hpp"

Human::Human(const Human& orig){
  this->m_currentState = orig.m_currentState;
  this->m_neighbours = orig.m_neighbours;
}

void Human::step()
{ 
  if (m_currentState == Ill){
    m_nextState = Healthy;
    for (auto human : this->m_neighbours){
      human->tryInfect(1); 
    }
    if (dis(mt) < mortality){
      m_nextState = Dead;
    }

  }
}

void Human::tryInfect(double exposureCoef)
{
  if (m_currentState != Dead &&
      m_currentState != Ill &&
      m_nextState != Dead &&
      dis(mt) < contagiousness*exposureCoef){
    m_nextState = Ill;
  }
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