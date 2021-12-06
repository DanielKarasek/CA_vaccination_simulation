#include <iostream>
#include <algorithm> 
#include <vector>    
#include <cstdio>   
#include <string>

#include "CA.h"
#include "globals.h"
#include "auxilary.h"

CA::CA(unsigned int size): m_size(size){
  // vytvoreni pole
  m_data.resize(size);
  for (auto &data_row: m_data){
    data_row.resize(size);
  }
  // propojeni sousedu dle moorova okoli
  Human *first, *second, *third, *fourth;
  int row_up, row_down, col_right;
  for (int col=0; col<size; col++){
    for (int row=0; row<size; row++){
      if (row==0)
        row_up = m_size-1;
      else
        row_up = row-1;
      if (row==m_size-1)
        row_down = 0;
      else
        row_down = row+1;
      if (col==m_size-1)
        col_right = 0;
      else
        col_right = col+1;

      first = &(m_data[row_up][col]);
      second = &(m_data[row_up][col_right]);
      third = &(m_data[row][col_right]);
      fourth = &(m_data[row_down][col_right]);
      
      m_data[row][col].addNeighbourBidirectional(first);
      m_data[row][col].addNeighbourBidirectional(second);
      m_data[row][col].addNeighbourBidirectional(third);
      m_data[row][col].addNeighbourBidirectional(fourth);
    }
  }
}

void CA::step(bool verbose){
  //update stavu lidi
  for (auto &data_row: m_data){
    for (auto &human: data_row){
      human.update_state();
    }
  }
  //provedeni kroku infekci/umrti etc.
  for (auto &data_row: m_data){
    for (auto &human: data_row){
      human.step();
    }
  }

  if (verbose){
    std::cout << *this;
  }
  this->gatherStatistics();
}

void CA::gatherStatistics(){
  gatherSingleStat(InfectedCounter, "Ill");
  gatherSingleStat(NoSymptomCounter, "NoSymptom");
  gatherSingleStat(SymptomCounter, "Symptom");
  gatherSingleStat(RiskCounter, "Risk");
  gatherSingleStat(DeathCounter, "Dead"); 
}

void CA::gatherSingleStat(std::vector<int> &statVector, std::string stat2gather){
  int counter{};
  for (auto &data_row: m_data){
    for (auto &human: data_row){
      if (human.statGatherer(stat2gather))
        counter++;
    }
  }
  statVector.push_back(counter);
}


void CA::vaccinatePercentageInit(double percentage, int spreadCoeff, std::vector<double>coeffs2set, std::vector<double>percentagePerCoeff){
  if (!checkVectorsLenght(coeffs2set,percentagePerCoeff)||!summs2one(percentagePerCoeff)){
    std::cout << "Vektor koeficientu a procent nemaji stejnou velikost, nebo procenta nescitaji do 1" << std::endl;
    return;
  }
  int totalPeople = m_size*m_size;
  int normalSTD = 0.05;
  
  std::vector<int> v = getShuffledVector(totalPeople);
  
  int count2vaccinate{};
  int rand_idx, rand_idx_first, rand_idx_second;
  int extra2spread{};
  for (int coefCounter=0; coefCounter < coeffs2set.size(); coefCounter++){
    count2vaccinate = totalPeople*percentage*percentagePerCoeff[coefCounter];
    if (spreadCoeff != 0)
      count2vaccinate /= spreadCoeff;
    for (int i=0;i<count2vaccinate;i++){
      rand_idx = v[i];
      rand_idx_first = rand_idx / m_size;
      rand_idx_second = rand_idx % m_size;
      m_data[rand_idx_first][rand_idx_second].setVaccinCoefs(coeffs2set[coefCounter]+NormalDis(mt)*normalSTD);
    }

    // rozsir na okoli
    if (spreadCoeff != 0){
      for (int i=0;i<count2vaccinate;i++){
        rand_idx = v[i];
        rand_idx_first = rand_idx / m_size;
        rand_idx_second = rand_idx % m_size;
        extra2spread += m_data[rand_idx_first][rand_idx_second].spreadVaccine2Neighours(spreadCoeff);
      }
    
    // rozsir na okoli ostatnich pokud se to nekde nepovedlo
      for (int i=0;i<count2vaccinate;i++){
        rand_idx = v[i];
        rand_idx_first = rand_idx / m_size;
        rand_idx_second = rand_idx % m_size;
        if (extra2spread == 0)
          break;
        extra2spread = m_data[rand_idx_first][rand_idx_second].spreadVaccine2Neighours(extra2spread);
      }
    }
  }
}

void CA::immunePercentageInit(double percentage, int spreadCoeff, std::vector<double>coeffs2set, std::vector<double>percentagePerCoeff){
  if (!checkVectorsLenght(coeffs2set, percentagePerCoeff)||!summs2one(percentagePerCoeff)){
    std::cout << "Vektor koeficientu a procent nemaji stejnou velikost, nebo procenta nescitaji do 1" << std::endl;
    return;
  }
  int totalPeople = m_size*m_size;
  int normalSTD = 0.05;
  
  std::vector<int> v = getShuffledVector(totalPeople);

  int count2immune{};
  int rand_idx, rand_idx_first, rand_idx_second;
  int extra2spread{};
  for (int coefCounter=0; coefCounter < coeffs2set.size(); coefCounter++){
    count2immune = totalPeople*percentage*percentagePerCoeff[coefCounter];
    if (spreadCoeff != 0)
      count2immune /= spreadCoeff;

    for (int i=0;i<count2immune;i++){
      rand_idx = v[i];
      rand_idx_first = rand_idx / m_size;
      rand_idx_second = rand_idx % m_size;
      m_data[rand_idx_first][rand_idx_second].setImmunCoefs(coeffs2set[coefCounter]+NormalDis(mt)*normalSTD);
    }
    // rozsir na okoli
    if (spreadCoeff != 0){
      for (int i=0;i<count2immune;i++){
        rand_idx = v[i];
        rand_idx_first = rand_idx / m_size;
        rand_idx_second = rand_idx % m_size;
        extra2spread += m_data[rand_idx_first][rand_idx_second].spreadImmun2Neighbours(spreadCoeff);
      }
    // rozsir na okoli ostatnich pokud se to nekde nepovedlo
      for (int i=0;i<count2immune;i++){
        rand_idx = v[i];
        rand_idx_first = rand_idx / m_size;
        rand_idx_second = rand_idx % m_size;
        if (extra2spread == 0)
          break;
        extra2spread = m_data[rand_idx_first][rand_idx_second].spreadImmun2Neighbours(extra2spread);
      }
    }
  }

  
}

void CA::infectPercentageInit(double percentage, int spreadCoeff){
  int totalPeople = m_size*m_size;
  int normalSTD = 0.1;
  
  std::vector<int> v(getShuffledVector(totalPeople));

  int count2infect = totalPeople*percentage;
  if (spreadCoeff != 0)
      count2infect /= (spreadCoeff+1);

  int rand_idx, rand_idx_first, rand_idx_second;
  int extra2spread{};
  for (int i=0;i<count2infect;i++){
    rand_idx = v[i];
    rand_idx_first = rand_idx / m_size;
    rand_idx_second = rand_idx % m_size;
    m_data[rand_idx_first][rand_idx_second].infect();
  }

  if (spreadCoeff != 0){
    // rozsir na okoli
    for (int i=0;i<count2infect;i++){
      rand_idx = v[i];
      rand_idx_first = rand_idx / m_size;
      rand_idx_second = rand_idx % m_size;
      extra2spread += m_data[rand_idx_first][rand_idx_second].spreadInfection2NeigboursGuaranted(spreadCoeff);
    }
  
    // rozsir na okoli ostatnich pokud se to nekde nepovedlo
    for (int i=0;i<count2infect;i++){
      rand_idx = v[i];
      rand_idx_first = rand_idx / m_size;
      rand_idx_second = rand_idx % m_size;
      if (extra2spread == 0)
        break;
      extra2spread = m_data[rand_idx_first][rand_idx_second].spreadInfection2NeigboursGuaranted(extra2spread);
    }
  }
}

void CA::infectNrandom(int N){
  int size_squared = m_size*m_size;
  int rand_idx, rand_idx_first, rand_idx_second;

  // vytvoreni vektoru a pak shuffle abych mohl mit unique random hodnoty
  std::vector<int> v(size_squared);
  for (size_t i = 0; i < v.size(); ++i)
      v[i] = i;


  std::shuffle(v.begin(), v.end(), mt);

  // ze zamichaneho vektoru vyberu N prvnich
  for (int i=0;i<N;i++){
    rand_idx = v[i];
    rand_idx_first = rand_idx / m_size;
    rand_idx_second = rand_idx % m_size;
    m_data[rand_idx_first][rand_idx_second].infect();
  }
}

void CA::infectPercentage(int N){
  infectNrandom(m_size*m_size*N/100);
}
 
void CA::vaccinateNrandom(int N){
  int size_squared = m_size*m_size;
  int rand_idx, rand_idx_first, rand_idx_second;

  // vytvoreni vektoru a pak shuffle abych mohl mit unique random hodnoty
  std::vector<int> v(size_squared);
  for (size_t i = 0; i < v.size(); ++i)
      v[i] = i;


  std::shuffle(v.begin(), v.end(), mt);

  // ze zamichaneho vektoru vyberu N prvnich
  for (int i=0;i<N;i++){
    rand_idx = v[i];
    rand_idx = IntegerDis(mt) % size_squared;
    rand_idx_first = rand_idx / m_size;
    rand_idx_second = rand_idx % m_size;
    m_data[rand_idx_first][rand_idx_second].vaccinate();
  }
}

void CA::vaccinatePercentage(int N){
  vaccinateNrandom(m_size*m_size*N/100);
}

void CA::printVaccinationMap(){
  for (auto &human_row: m_data){
    for (auto &human: human_row){
      printf("%.2f ", human.getVaccinInfectionCoef());
    }
    printf("\n");
  }
  printf("_______________________________________\n");
}

void CA::printImmunityMap(){
  for (auto &human_row: m_data){
    for (auto &human: human_row){
      printf("%.2f ", human.getImmunInfectionCoef());
    }
    printf("\n");
  }
  printf("_______________________________________\n");
}

std::ostream& operator<<(std::ostream& os, const CA& automat)
{
    os << "Automat is of shape "<<automat.m_size<<"x"<< automat.m_size<< std::endl;
    os << "Automat state: " << std::endl;
    for (auto &data_row: automat.m_data){
      for (auto &human: data_row){
        os << human<< " ";
      }
      os << std::endl;
    }
    return os;
}


