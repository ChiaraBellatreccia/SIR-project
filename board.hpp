#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <vector>
#include <cstdlib>

enum class State : int { Susceptible, Infected, Recovered };

class Person {
 private:
  State state_;  // ricorda di convertire esplicitamente quando assegni il
                 // valore S, I o R
  int counter[3];  // vettore con i conteggi di S, I, R nel vicinato della cellula che viene riempito da
                   // Count

 public:
  Person(State state) : state_{state} {} //costruttore
  Person() : state_{State::Susceptible} {} //costruttore di default

  std::vector<State> neighborhood_;  // array di int (che sarebbero gli enum convertiti) per il
                      // vicinato della cellula. Magari quando capisci come si fa
                      // sostituisci con array di enum
  // occhio perché non tutte le cellule hanno 8 viciniiiii
  // mancano attributi che sono le coordinate della cellula e metodi per
  // pescarle, direi che saranno tutti const
  State GetState() const;  // ritorna lo stato della persona
  void SetState(State state); //setta lo stato della persona
  void SetCounter();  // ritorna un puntatore perché l'array decade.
                           // Ritorna puntatore ad array 3-d, che è il counter.
  //void SetCounter(int S, int I, int R); //Setta il vicinato della persona (il counter)
  void Update(double beta, double gamma);  // Aggiorna lo stato della cellula a ogni generazione
};

class Board {
 private:
 const int rows_;
 const int columns_;
 const double beta_;
 const double gamma_;
 const int duration_; //durata totale della simulazione (in giorni)
 std::vector<std::vector<Person>> people; //griglia di persone
 int totcounter[3]; //conta S, I ed R totali della griglia people_
 int time = 0; //tiene il conto del numero di giorni della simulazione, parte da 0. Ogni giorno è una generazione.

 public:
 Board(int rows, int columns, double beta, double gamma, int duration) : rows_{rows}, columns_{columns}, beta_{beta}, gamma_{gamma}, duration_{duration} {}
 int GetTime() const; //ritorna il numero della generazione in cui si trova la simulazione
 void SetTime(); //setta il contatore "time" aumentandolo di una unità a ogni generazione
 void InitialState(); //genera lo stato iniziale della simulazione (riempie griglia e TotCounter con lo stato iniziale)
 void SetAllCounters(); //setta ciascuna counter di ciascuna person nella griglia riempiendo prima il vettore neighborhood di ciascuna persona
 void TotUpdate(); //fa evolvere lo stato di ciascuna persona della griglia e riempie TotCounter con il numero di S, I, R
 void Evolve(); //reitera prima SetAllCounters e poi TotUpdate tante volte quanto è time e a ogni iterazione aumenta "time" di una unità
 void PrintTotCounter(); //stampa a schermo totcounter a ogni generazione

};
#endif