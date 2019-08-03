// Author: Chris Darnell
// Date: 6/2/2016
// Description: Project 10.a - TicTacToe.cpp

#include "TicTacToe.hpp"
#include <cstdlib>
#include <iostream>
using namespace std;

// Write a main method (in TicTacToe.cpp) that asks the user which player should go first, creates a new TicTacToe object and starts the game.  For this project (10.a) only, you will not comment out your main method.


int main()

{
    char firstMove;
    cout << "Will X or O go first?\n";
    cin >> firstMove;
    TicTacToe game(firstMove);
    game.play();
    
    return 0;
}
