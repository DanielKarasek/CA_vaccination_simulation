#include <iostream>
#include "CA.hpp"
#include "globals.hpp"

int main(int argc, char *argv[])
{
  //____________________________________________________________________________________________
  // Base inicializace
  // Tady vytvarim 10x10 automat
  CA automat{10};
  // Infikuju random 50 procent lidi, na kazdy zdroj budou tri jeho sousedi
  // navakcinuj 12 procenta lidi a kazdy pak necha navakcinovat 3 kamose
  automat.infectPercentageInit(0.1, 3);
  // Navakcinuj random 10 procent lidi, na kazdy zdroj budou 2 sousedi  ==>
  // navakcinuj 3.3 procenta lidi a kazdy pak necha navakcinovat 2 kamose
  //- sila vaccinace == 0.8 pro 0.3 poctu vakcinovanych a 0.1 pro 0.7 poctu vakcinovanych
  automat.vaccinatePercentageInit(0.1, 2, {0.8,0.1}, {0.3,0.7});
  //stejna semantika jako ^^
  automat.immunePercentageInit(0.1, 2, {0.8,0.1}, {0.3,0.7});


  //___________________________________________________________________________________________
  // toto si umi simulovat tri kroky, muzes vypnout verbose na false a std::cout automat smazat
  std::cout << automat;
  for (int i=0;i<3;i++){
    automat.step(true);
  }
  //_____________________________________________________________________________________________
  // zakladni dve statistiky vypsane na stdout
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
  
  //___________________________________________________________________________________________
  // Zde vypis jak zhruba to decayu podle zadane hodnoty (mortality coef odvozen od infection coef)
  
  // 
  // Human h{};  
  // int timestepDays = 10;
  // h.setImmunCoefs(0.8); // zadavas infection coef, druhy je odvozeny
  // h.setVaccinCoefs(0.95); // ^^
  // for (int i=0;i<10;i++){
  //   std::cout << "Deacay step: " << i << "("<<timestepDays*i<<") days"<<std::endl;
  //   std::cout << "Vacc inf/mort c: " << h.getVaccinInfectionCoef() << "/" 
  //             << h.getImmunInfectionCoef()  << std::endl;
  //   std::cout << "Vacc mor/mort c: " << h.getVaccinMortalityCoef() << "/"
  //             << h.getImmunMortalityCoef()  << std::endl;
  //   std::cout << "____________________________" << std::endl;
  //   h.decayDefense();
  // }
  return 0;
}