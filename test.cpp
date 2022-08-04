#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <array>
#include <algorithm>

enum class State : int { Susceptible, Infected, Recovered };

class Person {
 private:
  State state_; 
  std::array<State, 8> neighborhood_;  
  int counter[3]; 

 public:
  Person(State state, std::array<State, 8> neighborhood) : state_{state}, neighborhood_{neighborhood} {}

  State GetState() const { return state_; }; 

  int* Count() {

  counter[0] = std::count(std::begin(neighborhood_), std::end(neighborhood_), State::Susceptible);
  counter[1] = std::count(std::begin(neighborhood_), std::end(neighborhood_), State::Infected);
  counter[2] = std::count(std::begin(neighborhood_), std::end(neighborhood_), State::Recovered);

  return counter;
  }  

void Update(double beta, double gamma) { 

    switch (state_) {

      case State::Susceptible: 
      
      {srand((unsigned)time(0));
      double randomnum1 = (double) std::rand()/RAND_MAX;  //generazione numero casuale tra 0 e 1, non so quanto sia buona sta funzione
      
      double infprob = beta * counter[1] / 8; //probabilità di infettarsi

      if(randomnum1 <= infprob) {state_ = State::Infected;}
      else{state_ = State::Susceptible;}

        break;
      }
      case State::Infected:
      {srand((unsigned)time(0));
      double randomnum2 = (double) std::rand()/RAND_MAX;  //generazione numero casuale tra 0 e 1, non so quanto sia buona sta funzione
    
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
    
    }


void SetState(State newstate) {state_ = newstate;}
};


TEST_CASE("testing the Count() and Update() functions") {

std::array<State, 8> neighborhood {State::Infected, State::Infected, State::Infected, State::Infected, State::Infected, State::Infected, State::Infected, State::Infected};
Person person(State::Recovered, neighborhood);

    CHECK(person.Count()[0] == 0);
    CHECK(person.Count()[1] == 8);
    CHECK(person.Count()[2] == 0);

double beta = 0;
double gamma = 1;

    person.Update(beta, gamma);
    CHECK(person.GetState() == State::Recovered);
    person.SetState(State::Infected);
    person.Update(beta, gamma);
    CHECK(person.GetState() == State::Recovered);
    person.SetState(State::Susceptible);
    person.Update(beta, gamma);
    CHECK(person.GetState() == State::Susceptible);
}