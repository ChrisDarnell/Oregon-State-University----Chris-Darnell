// Author: Chris Darnell
// Date: 6/2/2016
// Description: Project 10.a - Board.cpp

#include "Board.hpp"


// It should have a default constructor that initializes the 3x3 array to being empty.

Board::Board()

{
    
    char empty = '-';
    for (int x = 0; x < 3; x++)
        
    {
        
        for (int y = 0; y < 3; y++)
            
        { board[x][y] = empty; }
        
    }
    
}

// There should also be a method called print, which just prints out the current board to the screen.

void Board::print()

{
    
    cout << "\n  0 1 2" << endl;
    cout << "0 " << board[0][0] << " " << board[1][0] << " " << board[2][0] << endl;
    cout << "1 " << board[0][1] << " " << board[1][1] << " " << board[2][1] << endl;
    cout << "2 " << board[0][2] << " " << board[1][2] << " " << board[2][2] << endl;
    
}

//  It should have a method called makeMove that takes the x and y coordinates of the move (see the example below) and which player's turn it is as parameters.  If that location is unoccupied, makeMove should record the move and return true.
// If that location is already occupied, makeMove should just return false.

bool Board::makeMove(char player, int yCoordinate, int xCoordinate)

{
    
    if (board[xCoordinate][yCoordinate] == '-')
        
    {
        board[xCoordinate][yCoordinate] = player;
        return true;
    }
    
    else
        return false;
    
}

// There should be a method called gameState that takes no parameters and returns a value indicating one of four possibilities: 'x' has won, 'o' has won, the game is a draw, or the game is still in progress - use an enum for this (the enum definition should go in Board.hpp).


gameStatus Board::gameState()

{
    
// X wins
 
    if (board[0][0] == 'X' && board[0][0] == board[0][1] && board[0][0] == board[0][2])
        return status = X_WON;
    if (board[0][0] == 'X' && board[0][0] == board[1][0] && board[0][0] == board[2][0])
        return status = X_WON;
    if (board[0][0] == 'X' && board[0][0] == board[1][1] && board[0][0] == board[2][2])
        return status = X_WON;
    if (board[0][1] == 'X' && board[0][1] == board[1][1] && board[0][1] == board[2][1])
        return status = X_WON;
    if (board[0][2] == 'X' && board[0][2] == board[1][2] && board[0][2] == board[2][2])
        return status = X_WON;
    if (board[1][0] == 'X' && board[1][0] == board[1][1] && board[1][0] == board[1][2])
        return status = X_WON;
    if (board[2][0] == 'X' && board[2][0] == board[2][1] && board[2][0] == board[2][2])
        return status = X_WON;
    if (board[2][0] == 'X' && board[2][0] == board[1][1] && board[2][0] == board[0][2])
        return status = X_WON;
    
// O wins
    
    if (board[0][0] == 'O' && board[0][0] == board[0][1] && board[0][0] == board[0][2])
        return status = O_WON;
    if (board[0][0] == 'O' && board[0][0] == board[1][0] && board[0][0] == board[2][0])
        return status = O_WON;
    if (board[0][0] == 'O' && board[0][0] == board[1][1] && board[0][0] == board[2][2])
        return status = O_WON;
    if (board[0][1] == 'O' && board[0][1] == board[1][1] && board[0][1] == board[2][1])
        return status = O_WON;
    if (board[0][2] == 'O' && board[0][2] == board[1][2] && board[0][2] == board[2][2])
        return status = O_WON;
    if (board[1][0] == 'O' && board[1][0] == board[1][1] && board[1][0] == board[1][2])
        return status = O_WON;
    if (board[2][0] == 'O' && board[2][0] == board[2][1] && board[2][0] == board[2][2])
        return status = O_WON;
    if (board[2][0] == 'O' && board[2][0] == board[1][1] && board[2][0] == board[0][2])
        return status = O_WON;
    
// Game in progress.
    
    int count = 0;
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            if (board[x][y] == 'X' || board[x][y] == 'O')
                count ++;
            else
                return status = UNFINISHED;
        }
    }
    
// Draw.
    
    return status = DRAW;
}
