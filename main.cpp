#include "board.hpp"

#include <iostream>

int main() {
    
    srand((unsigned)time(NULL));
    Board board{600, 100, 0.5, 0.1, 150};
    board.InitialState();
    board.Evolve();
}