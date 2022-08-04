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
  std::array<State, 8> neighborhood_;  // array di int (che sarebbero gli enum convertiti) per il
                      // vicinato della cellula. Magari quando capisci come si fa
                      // sostituisci con array di enum
  // occhio perché non tutte le cellule hanno 8 viciniiiii
  // mancano attributi che sono le coordinate della cellula e metodi per
  // pescarle, direi che saranno tutti const
  int counter[3];  // array con i conteggi di S, I, R che viene riempito da
                   // Count

 public:
  Person(State state, std::array<State, 8> neighborhood) : state_{state}, neighborhood_{neighborhood} {}

  State GetState();  // ritorna lo stato della persona
  int* Count();  // ritorna un puntatore perché l'array decade.
                           // Ritorna puntatore ad array 3-d, che è il counter.
  void Update(double beta, double gamma);  // Aggiorna lo stato della cellula a ogni generazione
};

class Board {
 private:
 const int rows_;
 const int columns_;
 const double beta_;
 const double gamma_;
 const int duration_; //durata totale della simulazione (in giorni)
 std::vector<std::vector<Person>> people_; //griglia di persone
 int totcounter[3]; //conta S, I ed R totali della griglia people_
 int time = 0; //tiene il conto del numero di giorni della simulazione, parte da 0. Ogni giorno è una generazione.

 public:
 int GetTime() const; //ritorna il numero della generazione in cui si trova la simulazione
 int SetTime(); //setta il contatore "time" aumentandolo di una unità a ogni generazione
 void InitialState(); //genera lo stato iniziale della simulazione (riempie griglia e TotCounter con lo stato iniziale)
 void TotUpdate(); //fa evolvere lo stato di ciascuna persona della griglia e riempie TotCounter con il numero di S, I, R
 void Evolve(int time); //reitera TotUpdate tante volte quanto è time e a ogni iterazione aumenta "time" di una unità

};
#endif