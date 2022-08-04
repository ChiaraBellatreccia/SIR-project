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
 int rows_;
 int columns_;
 std::vector<std::vector<State>> grid_;

 public:
 

};
#endif