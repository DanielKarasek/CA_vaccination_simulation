#ifndef CA_H 
#define CA_H

#include <iostream>
#include <vector>

#include "human.hpp"
#include "globals.hpp"

typedef std::vector<std::vector<Human>> HumanArr;

class CA 
{
  protected:
    int m_size;
    HumanArr m_data;
  public:
    // Vytvori CA + zakladni propojeni lidi-Human class
    // (lidi si pamatuji kdo je jejich okoli a je jejich responsibilty je infikovat)
    CA(int size);
    // natvrdo nainfikuje N random lidi
    void infectNrandom(int N);
    // nainfikuje procenta lidi 0,100 int -- asi predelam na double
    void infectPercentage(int N);

    // natvrdo navakcinuje N random lidi, vakcinace u lidi neni implementovana
    // -- asi predelam na double
    void vaccinateNrandom(int N);
    // navakcinuje procenta lidi 0,100 int, vakcinace u lidi neni implementovana
    // -- asi predelam na double
    void vaccinatePercentage(int N);
    void vaccinatePercentageInit(double percentage, int spreadCoeff, std::vector<double>coeffs2set, std::vector<double>percentagePerCoeff);
    void immunePercentageInit(double percentage, int spreadCoeff, std::vector<double>coeffs2set, std::vector<double>percentagePerCoeff);
    void infectPercentageInit(double percentage, int spreadCoeff);
    
    // updatuje lidi do noveho kroku a pak necha kazdeho cloveka provest krok simulace
    // (nainfikovat lidi okolo)
    void step(bool verbose);
    void gatherStatistics();
    
    friend std::ostream& operator<<(std::ostream& os, const CA& automat);
};

#endif