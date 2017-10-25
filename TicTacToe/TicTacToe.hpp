// Author: Chris Darnell
// Date: 6/2/2016
// Description: Project 10.a - TicTacToe.hpp

// Write a class called TicTacToe that allows two people to play a game.  This class will have a field for a Board object and a field to keep track of which player's turn it is.  It should have a constructor that takes a char parameter that specifies whether 'x' or 'o' should have the first move.  It should have a method called play that starts the game.  The play method should keep looping, asking the correct player for their move and sending it to the board (with makeMove) until someone has won or it's a draw (as indicated by gameState), and then declare what the outcome was.


#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP
#include <stdio.h>
#include "Board.hpp"


class TicTacToe

{
    
private:
    
    Board gameBoard;
    int playerTurn;
    char playerOne;
    char playerTwo;
    char playerTracker;
    
public:
 
    TicTacToe()
    
    {
        playerTurn = 0;
    }
    
    TicTacToe(char playerTracker)
    
    {
        playerOne = playerTracker;
        if (playerOne == 'X' || playerOne == 'x')
            playerTwo = 'O';
        if (playerOne == 'O' || playerOne == 'o')
            playerTwo = 'X';
        cout << "Player One will be " << playerOne << " and Player Two will be " << playerTwo << endl;
        
    }
    
 
    char turnTracker()
    
    {
        if (playerTurn % 2 == 0)
            return playerOne;
        else
            return playerTwo;
        
    }
    

    void play()
    
    {
        
        int xMove, yMove;
        playerTracker = turnTracker();
        cout << "\n" << playerTracker << "'s turn.";
        gameBoard.print();
        
        cout << "Enter a coordinate: \n";
        cin >> xMove >> yMove;
        while ( gameBoard.makeMove(playerTracker, xMove, yMove) == false )
            
        {
            cout << "That space is occupied. Enter a coordinate: \n";
            cin >> xMove >> yMove;
        }
        
        playerTurn++;
        
        if ( gameBoard.gameState() == UNFINISHED )
            play();
        
        else if ( gameBoard.gameState() == X_WON )
            
        {   gameBoard.print();
            cout << "\nX has won!\n";
            exit(0);
        }
        
        else if ( gameBoard.gameState() == O_WON )
            
        {   gameBoard.print();
            cout << "\nO has won!\n";
            exit(0);
        }
        
        else if ( gameBoard.gameState() == DRAW )
        
        {   gameBoard.print();
            cout << "\nIt's a draw.\n";
            exit(0);
        }
        
    }
    
};



#endif /* TicTacToe_hpp */
