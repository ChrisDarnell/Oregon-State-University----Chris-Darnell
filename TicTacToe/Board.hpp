// Author: Chris Darnell
// Date: 6/2/2016
// Description: Project 10.a - Board.hpp

#ifndef Board_hpp
#define Board_hpp

#include <iostream>
#include <cstdlib>
using namespace std;


// Write a class called Board that represents a tic-tac-toe board. It should have a 3x3 array as a data member, which will store the locations of the players' moves.

enum gameStatus {X_WON, O_WON, DRAW, UNFINISHED};

class Board

{
    
private:
    
    gameStatus status;
    char board[3][3];
    int moveX, moveY;
   
public:
    
    Board();
    void print();
    bool makeMove(char, int, int);
    gameStatus gameState();
   
    
};


#endif /* Board_hpp */
