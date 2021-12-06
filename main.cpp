#include <iostream>
#include <fstream>
#include "CA.h"
#include "globals.h"
#include "auxilary.h"

void testDan(){
  CA automat{10};
  // Infikuju random 50 procent lidi, na kazdy zdroj budou tri jeho sousedi ==>
  // prubeh fce: navakcinuj 12 procenta lidi jako zdroje a kazdy pak necha navakcinovat 3 kamose
  automat.infectPercentageInit(0.3, 2);
  // Navakcinuj random 10 procent lidi, na kazdy zdroj budou 2 sousedi  ==>
  // navakcinuj 3.3 procenta lidi a kazdy pak necha navakcinovat 2 kamose
  //- sila vaccinace == 0.8 pro 0.3 poctu vakcinovanych a 0.1 pro 0.7 poctu vakcinovanych
  automat.vaccinatePercentageInit(0.6, 3, {0.9,0.3}, {0.4,0.6});
  //stejna semantika jako ^^
  automat.immunePercentageInit(0.2, 1, {0.8,0.1}, {0.3,0.7});

  //std::cout << automat; 
  for (unsigned int i=0;i<20;i++){
    automat.step(false);
  }
  printStats(std::cout);
}

void saveForView(){
  int n = 1000;
  CA automat{n};

  automat.infectPercentageInit(0.008, 3);
  automat.vaccinatePercentageInit(0.75, 3, {0.9,0.7,0.4}, {0.5,0.4,0.1});
  automat.immunePercentageInit(0.3, 1, {0.8,0.2}, {0.3,0.7});

  std::ofstream myfile;
  myfile.open ("automatVideo.txt");
  myfile << n << std::endl;
  for (unsigned int i=0;i<100;i++){
    myfile << automat;
    automat.step(false); 
  }
  myfile << automat;

  myfile.close();
  
}

int main(int argc, char *argv[])
{
  saveForView();
  return 0;
  using namespace std;
  cout << "Size of map (NxN)" << endl << "N: ";
  unsigned int n;

  cin >> n; 

  cout << "Number of generations to simulate" << endl << "g: ";
  
  unsigned int g;
  cin >> g;

  string answer = "n";
  bool printable = false;

  cout << "Print map?" << endl << "Print [y/n]: ";
  cin >> answer;
  if(answer[0] == 'y')
  {
    printable = true;
  }
  //____________________________________________________________________________________________
  // Base inicializace
  // Tady vytvarim nxn automat
  CA automat{n};
  // Infikuju random 50 procent lidi, na kazdy zdroj budou tri jeho sousedi
  // navakcinuj 12 procenta lidi a kazdy pak necha navakcinovat 3 kamose
  automat.infectPercentageInit(0.008, 3);
  // Navakcinuj random 10 procent lidi, na kazdy zdroj budou 2 sousedi  ==>
  // navakcinuj 3.3 procenta lidi a kazdy pak necha navakcinovat 2 kamose
  //- sila vaccinace == 0.8 pro 0.3 poctu vakcinovanych a 0.1 pro 0.7 poctu vakcinovanych
  automat.vaccinatePercentageInit(0.75, 3, {0.9,0.7,0.4}, {0.5,0.4,0.1});
  //stejna semantika jako ^^
  automat.immunePercentageInit(0.3, 1, {0.8,0.2}, {0.3,0.7});

  bool run = false;

  do{
    //___________________________________________________________________________________________
    // toto si umi simulovat tri kroky, muzes vypnout verbose na false a std::cout automat smazat
    if (printable){
      std::cout << automat;
    }
    double originalContag = Contagiousness;
    double originalSpreaderProb = SuperSpreaderProb;
    for (unsigned int i=0;i<g;i++){
      automat.step(printable);
      if(InfectedCounter.back()/(n*n) > 0.01)
      {

        Contagiousness -= 0.04;
        SuperSpreaderProb -= 0.05;
      }
      else
      {
        if(Contagiousness <= originalContag)
        {
          Contagiousness += 0.04;
          
        }
        if(SuperSpreaderProb <= originalSpreaderProb)
        {
          SuperSpreaderProb += 0.05;
        }
      }
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
    cout << std::endl;
    cout << "Do you wish to continue?" << endl << "Continue [y/n]: ";
    cin >> answer;
    if(answer[0] == 'y')
    {
      run = true;
      cout << "How many generations?" << endl << "g: ";
      cin >> g;
    }
    else
    {
      run = false;
    }
    
  }while(run);

  ofstream myfile;
  myfile.open ("statistica.txt");
  myfile << "Deaths Infected" << endl;
  
  for(unsigned int i = 0; i < DeathCounter.size() && i < InfectedCounter.size(); i++)
  {
    myfile << DeathCounter[i] << " " << InfectedCounter[i] << endl;
  }
  myfile.close();
  
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