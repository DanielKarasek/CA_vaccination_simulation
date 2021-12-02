#include <iostream>
#include "CA.hpp"
#include "globals.hpp"

int main(int argc, char *argv[])
{
  // Tady vytvarim 10x10 automat
  CA automat{10};
  // Infikuju random lidi
  automat.infectPercentage(10);

  // Vykreslim info o automatu
  // Dale volam step v loopu s Verbose prepinacem, at se to vykresluje 
  std::cout << automat;
  for (int i=0;i<10;i++){
    automat.step(true);
  }
  return 0;
}