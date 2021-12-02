#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <vector>
#include <random>

#include "globals.hpp"

// enum stavu tridy Human
enum HumanState{Healthy, Ill, Dead};


class Human
{
  protected:
    // Soucasny a dalsi stav + seznam sousedu
    HumanState m_currentState{Healthy};
    HumanState m_nextState{Healthy};
    std::vector<Human *> m_neighbours{};
    
    // Pridani do seznamu sousedu, bez zpetne vazby
    void addNeighbourUnidirection(Human *newNeighbour){m_neighbours.push_back(newNeighbour);}

  public:
    Human(){}
    Human(const Human& orig);

  
    void update_state()
    {
      m_currentState = m_nextState;
    }

    // pokud sme nemocni tak nejdriv pokusime nakazit sousedy
    // pak zkusime umrit
    // neni doimplementovano (spravne hodnoty, a jak se chovat dle vakcinace)
    void step();
    


    // pokus nakazeni sama sebe, exposureCoef muze snizit sanci nakazeni
    // neni doresena implementace (hodnoty, a jak dle vakcinace)
    void tryInfect(double exposureCoef);
    

    // Pridani do seznamu sousedu, ten si nas prida zpatky
    void addNeighbourBidirectional(Human *newNeighbour);

    
    // Navakcinuj cloveka -- zatim neimplementovano vubec
    void vaccinate(){};
    // Infikuje - uzito pri inicializaci automatu
    void infect(){if (!(this->m_currentState==Dead)) this->m_nextState=Ill;}
    // Zabije - uzito pri inicializaci automatu
    void kill(){this->m_nextState=Dead;}
    
  friend std::ostream& operator<<(std::ostream& os, const Human& human);
};

#endif