#include <iostream>
#include <fstream>
#include "CA.h"
#include "globals.h"
#include "auxilary.h"

void testDecay(double deltaTime)
{
  Human h{};  
  double timestepDays {3.5};
  int iteration{};
  h.setImmunCoefs(ImmunityStartInfection); // zadavas infection coef, druhy je odvozeny
  h.setVaccinCoefs(VaccineStartInfection); // ^^
  while (iteration*timestepDays<=deltaTime){
    std::cout << "Deacay step: " << iteration << "("<<timestepDays*iteration<<") days"<<std::endl;
    std::cout << "Vacc inf/mort c: " << h.getVaccinInfectionCoef() << "/" 
              << h.getImmunInfectionCoef()  << std::endl;
    std::cout << "Vacc mor/mort c: " << h.getVaccinMortalityCoef() << "/"
              << h.getImmunMortalityCoef()  << std::endl;
    std::cout << "____________________________" << std::endl;
    h.decayDefense();
    ++iteration;
  }
}


int main(int argc, char *argv[])
{
  // testDecay(180);
  // return 0;
  using std::cout;
  using std::cin;
  int n{}, g{};
  n = getIntOnCondition("Size of map (NxN)\nN, where N>1: ", [](int a) {return (a>1);});
  g = getIntOnCondition("Positive number of generations to simulate\ng: ",
                        [](int a) {return (a>0);});
  

  std::string answer{};
  bool printable = false;

  cout << "Print map?\nPrint [y/n]: ";
  cin >> answer;

  if(answer[0] == 'y') printable = true;
  
  // automat init
  CA automat{n};
  
  automat.infectPercentageInit(0.008, 3);
  automat.vaccinatePercentageInit(0.75, 3, {0.9,0.7,0.4}, {0.4,0.4,0.2});
  automat.immunePercentageInit(0.2, 2, {0.8,0.3}, {0.3,0.7});

  double originalContag = Contagiousness;
  double originalSpreaderProb = SuperSpreaderProb;
  
  
  if (printable) cout << automat;
  
  while (g > 0){
    automat.step(printable);
    if(InfectedCounter.back()/(n*n) > 0.01)
    {

      Contagiousness -= 0.0065;
      SuperSpreaderProb -= 0.0055;
    }
    else
    {
      if(Contagiousness <= originalContag)
      {
        Contagiousness += 0.005;
        
      }
      if(SuperSpreaderProb <= originalSpreaderProb)
      {
        SuperSpreaderProb += 0.005;
      }
    }
    if (g == 1)
    {
      printStats(std::cout, false);
      cout << '\n';
      cout << "Do you wish to continue?\nContinue [y/n]: ";
      cin >> answer;
      if(answer[0] == 'y')
      {
        g = getIntOnCondition("How many generations?\ng: ", [](int inp){return inp>1;}) + 1; 
        if (printable) std::cout << automat;
      }
    }
    --g;
  }

  std::ofstream myfile;
  myfile.open ("statistica.txt");  
  
  printStats(myfile, true);
  
  myfile.close();
  
  return 0;
}