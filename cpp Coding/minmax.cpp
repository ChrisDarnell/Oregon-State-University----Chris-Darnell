//  Author: Chris Darnell
//  Date: 1/13/2016
//  Description: Project 2.a; minmax.cpp


#include <iostream>
#include <string>
using namespace std;

// Display largest and smallest integers.

int main()
{
    
// Declare variables.
    
    int integerCount;
    int integerEntered;
    int integerMaximum = 0;
    int integerMinimum = 0;
   
    
// Get number of integers.
    
    cout << "How many integers would you like to enter?" << endl;
    cin >> integerCount;
    
// Prompt for integers.

    cout << "Please enter " << integerCount << " integers." << endl;
    
    
// Compare integer to subsequent integer, keep highest and lowest values.
    
    
    for (int count = 1; count <= integerCount; count ++)

    {
        cin >> integerEntered;
        
// Set max/min to number entered for all +/- values.
        
       
        if (count == 1)
        {
            integerMaximum = integerEntered;
            integerMinimum = integerEntered;
        }
        else if (integerEntered >= integerMaximum)
            integerMaximum = integerEntered;
        else if  (integerEntered <= integerMinimum)
            integerMinimum = integerEntered;
        
    }
   
// Display min/max.
    
    cout << "min: " << integerMinimum << endl;
    cout << "max: " << integerMaximum << endl;
    
   
    
    return 0;
}
