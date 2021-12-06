#ifndef CA_H 
#define CA_H

#include <iostream>
#include <vector>
#include <string>

#include "human.h"
#include "globals.h"

typedef std::vector<std::vector<Human>> HumanArr;
class CA 
{

  protected:
    int m_size;
    HumanArr m_data;
  public:
    // Vytvori CA + zakladni propojeni lidi-Human class
    // (lidi si pamatuji kdo je jejich okoli a je jejich responsibilty je infikovat)
    CA(unsigned int size);
    // natvrdo nainfikuje N random lidi

    // semantika vseho je stejna jen pro jiny typ akce (vaccinace, immunizace, infekce)
    // Aplikuj na celkem percentage (0-1) lidi, to se udela tak ze se do zakladu vytvori ale o spreadCoeff-1 lozisek
    // a od tohoto loziska se nakazi spreadCoeff blizkych kontaktu 
    // Dale je vektor ruznych intenzit (0-1 hodnoty) a vektor kolik procent (0-1 hodnoty) z aplikovanych ma danou intenzitu mit
    // Use case fc(0.5, 4, {0.9, 0.6},{0.2, 0.8}) dej vakcinu 50 procentum lidi (vytvori 10 procent loziska a od kazddeho z nich nakazi dalsi 4 lidi == 50 procent)
    // 20 procentum z nich dej davku 0.9. 80 precentum z nich dej davku sily 0.6
    void vaccinatePercentageInit(double percentage, int spreadCoeff, std::vector<double>coeffs2set, std::vector<double>percentagePerCoeff);
    void immunePercentageInit(double percentage, int spreadCoeff, std::vector<double>coeffs2set, std::vector<double>percentagePerCoeff);
    void infectPercentageInit(double percentage, int spreadCoeff);

    void spreadVariable(std::vector<int> &shuffledVector, int sources, int spreadCoeff, std::string variable);
    
    // updatuje lidi do noveho kroku a pak necha kazdeho cloveka provest krok simulace
    // (nainfikovat lidi okolo)
    void step(bool verbose);
    // Nataha statistiky z CA do globalnich promennych
    void gatherStatistics();
    void gatherSingleStat(std::vector<int> &statVector, std::string stat2gather);
    
    void printImmunityMap();
    void printVaccinationMap();
    friend std::ostream& operator<<(std::ostream& os, const CA& automat);
};

#endif