#include <iostream>
#include <algorithm> 
#include <vector>       

#include "CA.hpp"
#include "globals.hpp"

CA::CA(int size): m_size(size){
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
    rand_idx = dis_int(mt) % size_squared;
    rand_idx_first = rand_idx / m_size;
    rand_idx_second = rand_idx % m_size;
    m_data[rand_idx_first][rand_idx_second].vaccinate();
  }
}

void CA::vaccinatePercentage(int N){
  vaccinateNrandom(m_size*m_size*N/100);
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
