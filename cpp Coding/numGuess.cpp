//  Author: Chris Darnell
//  Date: 1/13/2016
//  Description: Project 2.c; numGuess.cpp


#include <iostream>
#include <string>
using namespace std;

// Create a number guessing game.

int main()
{
    
// Declare variables.
    
    
    int userGuess;
    int targetNumber;
    int numberTries= 1;
    
    
// Enter target number.
    
    cout << "Enter the number for the player to guess." << endl;
    cin >> targetNumber;
    
// Collect/evaluate player guesses, track number of attempts.
    
    cout << "Enter your guess." << endl;
    cin >> userGuess;
    
    while (userGuess != targetNumber)
    
    {

        
        if (userGuess < targetNumber) {
            cout << "Too low - try again." << endl;
            cin >> userGuess;
            numberTries = numberTries + 1;
        } else if (userGuess > targetNumber) {
            cout << "Too high - try again." << endl;
            cin >> userGuess;
            numberTries = numberTries +1;
        }

    
    }

// Display results.
    
    cout << "You guessed it in " << numberTries;
    cout << " tries.";

    return 0;
}