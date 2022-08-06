#include "board.hpp"

#include <cstdlib>
#include <ctime>
#include <random>
#include <array>
#include <algorithm>
#include <iostream>

State Person::GetState() const { return state_; };

void Person::SetState(State state) { state_ = state; };

void Person::SetCounter() {

  counter[0] = std::count(std::begin(neighborhood_), std::end(neighborhood_), State::Susceptible);
  counter[1] = std::count(std::begin(neighborhood_), std::end(neighborhood_), State::Infected);
  counter[2] = std::count(std::begin(neighborhood_), std::end(neighborhood_), State::Recovered);

  };

void Person::Update(double beta, double gamma) { 

    switch (state_) {

      case State::Susceptible: 
      
      {double randomnum1 = rand()/(RAND_MAX + 1.);  //generazione numero casuale tra 0 e 1, non so quanto sia buona sta funzione
      
      double infprob = 1 - std::pow((1 - beta), counter[1]); //probabilità di infettarsi

      if(randomnum1 <= infprob) {state_ = State::Infected; /*std::cout << "infettato" << "\n";*/}
      else{state_ = State::Susceptible;}

        break;
      }
      case State::Infected:
      {//srand((unsigned)time(0));
      double randomnum2 = rand()/(RAND_MAX + 1.);  //generazione numero casuale tra 0 e 1, non so quanto sia buona sta funzione
    
      if(randomnum2 <= gamma) {state_ = State::Recovered;}
      else{state_ = State::Infected;}

        break;
      }
      case State::Recovered:
        ;
        break;
      default:
        throw std::runtime_error{"invalid state"};
    }  
    
    };

/*void Person::SetCounter(int S, int I, int R) { //Setta il counter di ciascuna person
    counter[0] = S;
    counter[1] = I;
    counter[2] = R;
}*/

State Board::GetState(int i, int j) const { return people[i][j].GetState(); }

int Board::GetTime() const { return time; };

void Board::SetTime() { time += 1; };

void Board::InitialState() { //testata, dovrebbe funzionare (non so se la generazione di numeri casuali abbia bias)

//generazione paziente zero: si generano due numeri casuali per darne le coordinate nella griglia people
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    
    std::uniform_int_distribution<> distr1(0, rows_ - 1); //range righe
    int row_0 = distr1(gen); //generazione riga del paziente 0

    std::uniform_int_distribution<> distr2(0, columns_ - 1); //range colonne
    int column_0 = distr2(gen); //generazione colonna del paziente 0

//riempimento griglia People con lo stato iniziale: tutti Susceptible tranne il paziente 0 che è Infected
    people.resize(rows_, std::vector<Person>(columns_)); //resize della grid
    for (int i = 0; i != rows_; ++i) {
  for(int j = 0; j != columns_; ++j) {
     people[i][j] = Person{};
  }
} //necessario, senza dà segmentation fault
    
    std::cout << "Patient 0 coordinates: " << "\n" << row_0 << "\n" << column_0 << "\n";   
    people[row_0][column_0].SetState(State::Infected); //setta lo stato infected del paziente 0 in corrispondenza delle sue coordinate

    std::cout << "Generation number: 0 (Initial State)" << "\n" << "Susceptible: " << rows_ * columns_ - 1 << "\n" << "Infected: 1" << "\n" << "Recovered: 0" << "\n";
};

void Board::SetAllCounters() { //testata, dovrebbe funzionare

for(int i = 0; i != rows_; ++i) {
   for(int j = 0; j != columns_; ++j)  {
    
    (people[i][j].neighborhood_).clear(); //svuotamento vettore neighborhood vecchio di ciascuna person
    
    //std::cout << "Size of vector right now: " << (people[i][j].neighborhood_).size() << "\n";
    //riempimento vettore neighborhood con i nuovi vicini di ciascuna person e settaggio del counter di ciascuna person
    //4 angoli 
    if (i == 0 && j == 0) { //angolo in alto a sx
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i+1][j].GetState(), people[i+1][j+1].GetState(), people[i][j+1].GetState() });
      people[i][j].SetCounter();
      /*people[i][j].PrintCounter();
      std::cout << "Coordinates: " << i << ", " << j;*/
    }

    else if (i == 0 && j == (columns_ - 1)) { //angolo in alto a dx
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i][j-1].GetState(), people[i+1][j-1].GetState(), people[i+1][j].GetState() });
      people[i][j].SetCounter();  
      /*people[i][j].PrintCounter();
      std::cout << "Coordinates: " << i << ", " << j;*/ 
    }

    else if (i == (rows_ - 1) && j == (columns_ - 1)) { //angolo in basso a dx
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i][j-1].GetState(), people[i-1][j-1].GetState(), people[i-1][j].GetState() });
      people[i][j].SetCounter(); 
      /*people[i][j].PrintCounter();
      std::cout << "Coordinates: " << i << ", " << j;*/     
    }

    else if (i == (rows_ - 1) && j == 0) { //angolo in basso a sx
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i-1][j].GetState(), people[i-1][j+1].GetState(), people[i][j+1].GetState() });
      people[i][j].SetCounter();  
      /*people[i][j].PrintCounter();
      std::cout << "Coordinates: " << i << ", " << j;*/
    } 

    //4 bordi
    else if (i == 0 && 0 < j && j < (columns_ -1)) { //bordo in alto
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i][j-1].GetState(), people[i+1][j-1].GetState(), people[i+1][j].GetState(), people[i+1][j+1].GetState(), people[i][j+1].GetState() });
      people[i][j].SetCounter();  
      /*people[i][j].PrintCounter();
      std::cout << "Coordinates: " << i << ", " << j;*/
    } 

    else if (0 < i && i < (rows_ - 1) && j == (columns_ -1)) { //bordo a dx
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i-1][j].GetState(), people[i-1][j-1].GetState(), people[i][j-1].GetState(), people[i+1][j-1].GetState(), people[i+1][j].GetState() });
      people[i][j].SetCounter();    
      /*people[i][j].PrintCounter();
      std::cout << "Coordinates: " << i << ", " << j;*/
    } 

    else if (i == (rows_ - 1) && 0 < j && j < (columns_ -1)) { //bordo in basso
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i][j+1].GetState(), people[i-1][j+1].GetState(), people[i-1][j].GetState(), people[i-1][j-1].GetState(), people[i][j-1].GetState() });
      people[i][j].SetCounter();   
      /*people[i][j].PrintCounter();
      std::cout << "Coordinates: " << i << ", " << j;*/
    }

    else if (0 < i && i < (rows_ - 1) && j == 0) { //bordo a sx
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i+1][j].GetState(), people[i+1][j+1].GetState(), people[i][j+1].GetState(), people[i-1][j+1].GetState(), people[i-1][j].GetState() });
      people[i][j].SetCounter();    
      /*people[i][j].PrintCounter();
      std::cout << "Coordinates: " << i << ", " << j;*/
    }  

    else { //tutte le altre posizioni
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i+1][j-1].GetState(), people[i+1][j].GetState(), people[i+1][j+1].GetState(), people[i][j+1].GetState(), people[i-1][j+1].GetState(), people[i-1][j].GetState(), people[i-1][j-1].GetState(), people[i][j-1].GetState() });
      people[i][j].SetCounter();
      /*people[i][j].PrintCounter();
      std::cout << "Coordinates: " << i << ", " << j;*/
    }
   }
}
};

void Board::TotUpdate() {

int a[3] = {0, 0, 0};
for (int i = 0; i != rows_; ++i) {
  for(int j = 0; j != columns_; ++j) {
     people[i][j].Update(beta_, gamma_); //chiama Update() per ogni persona di people
     
     switch(people[i][j].GetState())  //riempie totcounter
     {
     case State::Susceptible: {a[0] += 1;
                              break;}
     case State::Infected: {a[1] += 1;
                              break;}
     case State::Recovered: {a[2] += 1;
                              break;}
     default: throw std::runtime_error{"invalid state"};
     }
     //std::cout << "S tot = " << totcounter[0] << "\n" << "I tot = " << totcounter[1] << "\n" << "R tot = " << totcounter[2] << "\n";
  }
}

totcounter[0] = a[0];
totcounter[1] = a[1];
totcounter[2] = a[2];
};

void Board::Evolve() {

   //reiterazione di SetAllCounters() e TotUpdate() da giorno 0 fino a duration, set del time counter e printaggio del numero di S, I, R
  for(int t = 1; t != (duration_ + 1); ++t) {
   SetAllCounters();
   TotUpdate();
   SetTime();
   std::cout << "Generation number: " << t << "\n" << "Susceptible: " << totcounter[0] << "\n" << "Infected: " << totcounter[1] << "\n" << "Recovered: " << totcounter[2] << "\n";
  }
};