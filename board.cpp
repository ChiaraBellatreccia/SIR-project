#include "board.hpp"

#include <cstdlib>
#include <ctime>
#include <random>
#include <array>
#include <algorithm>

State Person::GetState() const { return state_; };

int* Person::Count() {

  counter[0] = std::count(std::begin(neighborhood_), std::end(neighborhood_), State::Susceptible);
  counter[1] = std::count(std::begin(neighborhood_), std::end(neighborhood_), State::Infected);
  counter[2] = std::count(std::begin(neighborhood_), std::end(neighborhood_), State::Recovered);

  return counter;
  };

void Person::Update(double beta, double gamma) { 

    switch (state_) {

      case State::Susceptible: 
      
      {srand((unsigned)time(0));
      double randomnum1 = (double) rand()/RAND_MAX;  //generazione numero casuale tra 0 e 1, non so quanto sia buona sta funzione
      
      double infprob = beta * counter[1] / 8; //probabilità di infettarsi

      if(randomnum1 <= infprob) {state_ = State::Infected;}
      else{state_ = State::Susceptible;}

        break;
      }
      case State::Infected:
      {srand((unsigned)time(0));
      double randomnum2 = (double) rand()/RAND_MAX;  //generazione numero casuale tra 0 e 1, non so quanto sia buona sta funzione
    
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

int Board::GetTime() const { return time; };

void Board::SetTime() { time += 1; };

void Board::InitialState() {

//generazione paziente zero: si generano due numeri casuali per darne le coordinate nella griglia people
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    
    std::uniform_int_distribution<> distr(0, rows_ - 1); //range righe
    int row_0 = distr(gen); //generazione riga del paziente 0

    std::uniform_int_distribution<> distr(0, columns_ - 1); //range colonne
    int column_0 = distr(gen); //generazione colonna del paziente 0

//riempimento griglia People con lo stato iniziale: tutti Susceptible tranne il paziente 0 che è Infected


}