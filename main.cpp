#include <iostream>
#include "CA.hpp"
#include "globals.hpp"

int main(int argc, char *argv[])
{
  // Tady vytvarim 10x10 automat
  CA automat{10};
  // Infikuju random 50 procent lidi, na kazdy zdroj budou tri jeho sousedi
  // navakcinuj 12 procenta lidi a kazdy pak necha navakcinovat 3 kamose
  automat.infectPercentageInit(0.5, 3);
  // Navakcinuj random 10 procent lidi, na kazdy zdroj budou 2 sousedi  ==>
  // navakcinuj 3.3 procenta lidi a kazdy pak necha navakcinovat 2 kamose
  //- sila vaccinace == 0.8 pro 0.3 poctu vakcinovanych a 0.1 pro 0.7 poctu vakcinovanych
  automat.vaccinatePercentageInit(0.1, 2, {0.8,0.1}, {0.3,0.7});
  //stejna semantika jako ^^
  automat.immunePercentageInit(0.1, 2, {0.8,0.1}, {0.3,0.7});


  // Vykreslim info o automatu
  // Dale volam step v loopu s Verbose prepinacem, at se to vykresluje 
  // std::cout << automat;
  std::cout << automat;
  for (int i=0;i<10;i++){
    automat.step(true);
  }
  std::cout << "Death counts:\n"; 
  for (auto val:DeathCounter){
    std::cout << val << " ";
  }
  std::cout << std::endl;

  std::cout << "Infected counts:\n";
  for (auto val:InfectedCounter){
    std::cout << val << " ";
  }
  std::cout << std::endl;
  return 0;
}