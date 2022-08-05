#include "board.hpp"

#include <cstdlib>
#include <ctime>
#include <random>
#include <array>
#include <algorithm>

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

/*void Person::SetCounter(int S, int I, int R) { //Setta il counter di ciascuna person
    counter[0] = S;
    counter[1] = I;
    counter[2] = R;
}*/

int Board::GetTime() const { return time; };

void Board::SetTime() { time += 1; };

void Board::InitialState() {

//generazione paziente zero: si generano due numeri casuali per darne le coordinate nella griglia people
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    
    std::uniform_int_distribution<> distr1(0, rows_ - 1); //range righe
    int row_0 = distr1(gen); //generazione riga del paziente 0

    std::uniform_int_distribution<> distr2(0, columns_ - 1); //range colonne
    int column_0 = distr2(gen); //generazione colonna del paziente 0

//riempimento griglia People con lo stato iniziale: tutti Susceptible tranne il paziente 0 che è Infected
    people.resize(rows_, std::vector<Person>(columns_)); //resize della grid con tutte Person nello stato Susceptible (perché viene chiamato il costruttore di default)
    people[row_0][column_0].SetState(State::Infected); //setta lo stato infected del paziente 0 in corrispondenza delle sue coordinate

};

void Board::SetAllCounters() {

for(int i = 0; i != rows_; ++i) {
   for(int j = 0; j != columns_; ++j)  {

    //4 angoli 
    if (i == 0 && j == 0) { //angolo in alto a sx
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i+1][j].GetState(), people[i+1][j+1].GetState(), people[i][j+1].GetState() });
      people[i][j].SetCounter();
    }

    else if (i == 0 && j == (columns_ - 1)) { //angolo in alto a dx
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i][j-1].GetState(), people[i+1][j-1].GetState(), people[i+1][j].GetState() });
      people[i][j].SetCounter();      
    }

    else if (i == (rows_ - 1) && j == (columns_ - 1)) { //angolo in basso a dx
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i][j-1].GetState(), people[i-1][j-1].GetState(), people[i-1][j].GetState() });
      people[i][j].SetCounter();      
    }

    else if (i == (rows_ - 1) && j == (columns_ - 1)) { //angolo in basso a sx
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i-1][j].GetState(), people[i-1][j+1].GetState(), people[i][j+1].GetState() });
      people[i][j].SetCounter();      
    } 

    //4 bordi
    else if (i == 0 && 0 < j && j < (columns_ -1)) { //bordo in alto
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i][j-1].GetState(), people[i+1][j-1].GetState(), people[i+1][j].GetState(), people[i+1][j+1].GetState(), people[i][j+1].GetState() });
      people[i][j].SetCounter();    
    } 

    else if (0 < i && i < (rows_ - 1) && j == (columns_ -1)) { //bordo a dx
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i-1][j].GetState(), people[i-1][j-1].GetState(), people[i][j-1].GetState(), people[i+1][j-1].GetState(), people[i+1][j].GetState() });
      people[i][j].SetCounter();    
    } 

    else if (i == (rows_ - 1) && 0 < j && j < (columns_ -1)) { //bordo in basso
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i][j+1].GetState(), people[i-1][j+1].GetState(), people[i-1][j].GetState(), people[i-1][j-1].GetState(), people[i][j-1].GetState() });
      people[i][j].SetCounter();    
    }

    else if (0 < i && i < (rows_ - 1) && j == 0) { //bordo a sx
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i+1][j].GetState(), people[i+1][j+1].GetState(), people[i][j+1].GetState(), people[i-1][j+1].GetState(), people[i-1][j].GetState() });
      people[i][j].SetCounter();    
    }  

    else { //tutte le altre posizioni
      people[i][j].neighborhood_.insert((people[i][j].neighborhood_).end(), { people[i+1][j].GetState(), people[i+1][j+1].GetState(), people[i][j+1].GetState(), people[i-1][j+1].GetState(), people[i-1][j].GetState(), people[i-1][j-1].GetState(), people[i][j-1].GetState() });
      people[i][j].SetCounter();
    }
   }
}
};

