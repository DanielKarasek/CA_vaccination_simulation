#include <vector>
#include <algorithm>
#include <iostream>

#include "globals.h"

bool checkVectorsLenght(std::vector<double> first, std::vector<double> second){
  return (first.size() == second.size());
}

bool summs2one(std::vector<double> toCheck){
  double tmp{};
  for (auto val : toCheck){
    tmp+=val;
  }

  return (tmp>0.98 &&  tmp<1.02);
}

std::vector<int> getShuffledVector(int desiredSize){
  std::vector<int> v(desiredSize);

  for (size_t i = 0; i < v.size(); ++i)
      v[i] = i;

  std::shuffle(v.begin(), v.end(), mt);
  return v;
}


double clip(double n, double lower, double upper) {
  return std::max(lower, std::min(n, upper));
}

void printStats(std::ostream &os){
  os << "Death Infected NoSymptomCounter SymptomCounter RiskCounter\n";
  for (int i=0;i<InfectedCounter.size();i++){
    os << DeathCounter[i] << " "
       << InfectedCounter[i] << " "
       << NoSymptomCounter[i] << " "
       << SymptomCounter[i] << " "
       << RiskCounter[i] << std::endl;
  }

}