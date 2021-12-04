#ifndef HUMAN_H
#define HUMAN_H

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "globals.hpp"

// enum stavu tridy Human
enum HumanState{Healthy, Ill, Dead};

double clip(double n, double lower, double upper);

class Human
{
  protected:
    // Soucasny a dalsi stav + seznam sousedu
    HumanState m_currentState{Healthy};
    HumanState m_nextState{Healthy};
    double m_vaccinationInfectionCoef{};
    double m_immunityInfectionCoef{};
    double m_vaccinationMortalityCoef{};
    double m_immunityMortalityCoef{};
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
    // Decay funkce pro obranne slozky, aby sme nebyli imunni navzdy
    void decayDefense();
    void decayVaccinationInfecion();
    void decayVaccinationMortality();
    void decayImmunityInfecion();
    void decayImmunityMortality();
    
    // pomocne dotazy na stav, pro prehlednejsi kod
    bool isIll(){return m_currentState==Ill;}
    bool willBeIll(){return m_nextState==Ill;}
    bool isDead(){return m_nextState==Dead;}
    bool isInfectable();

    // pokus nakazeni sama sebe, exposureCoef muze snizit sanci nakazeni
    // neni doresena implementace (hodnoty, a jak dle vakcinace)
    void tryInfect(double exposureCoef);
    

    // Pridani do seznamu sousedu, ten si nas prida zpatky
    void addNeighbourBidirectional(Human *newNeighbour);

    // Navakcinuj cloveka -- zatim neimplementovano vubec
    void vaccinate();

    // Infikuje - uzito pri inicializaci automatu
    void infect(){if (!this->isDead()) this->m_nextState=Ill;}
    // Zabije - uzito pri inicializaci automatu
    void kill(){this->m_nextState=Dead;}

    // Nastavi infekcni obranu na novy koeficient a odvodi obranu proti mortalite
    void setImmunCoefs(double newCoef);
    void setVaccinCoefs(double newCoef);

    //gettery
    double getImmunInfectionCoef(){return m_immunityInfectionCoef;}
    double getVaccinInfectionCoef(){return m_vaccinationInfectionCoef;}
    double getImmunMortalityCoef(){return m_immunityMortalityCoef;}
    double getVaccinMortalityCoef(){return m_vaccinationMortalityCoef;}

    // funkce uccine 100% nakazi/immunuje/vakcinuje pocet:count v okoli
    int spreadImmun2Neighbours(int count);
    int spreadVaccine2Neighours(int count);
    int spreadInfection2NeigboursGuaranted(int count);
    
  friend std::ostream& operator<<(std::ostream& os, const Human& human);
};

#endif