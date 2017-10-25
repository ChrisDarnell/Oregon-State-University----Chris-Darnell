// Author: Chris Darnell
// Date: 5/4/2016
// Description: Project 6.b - converter.cpp

// A program with two recursive functions.

// Recursive function #1: parameter a C++ string of 1 and 0s that binary represent positive integer and return integer value.

// Recursive function #2: parameter positve int and return C++ binary string with no leading zeros.

// Do not use loops or static variables or C++ library conversion.


#include<iostream>
#include <math.h>
using namespace std;


// Function prototypes.

int binarySum = 0;
int binToDec(int, int);
void decToBin(int, int);


int main()

{
    
// Variables.
    
    int integer;
    int integerEquivalent;
    integerEquivalent = 0;
    int binary;
    
    
// Get user input.
    
    cout << "Enter the positive integer you wish to convert: \n";
    cin >> integer;
    
    cout << "\nEnter the binary string you wish to convert: \n";
    cin >> binary;
    
// Pass input to respective functions, display results.
    
    cout << "\nThe binary equivalent is: " << " \n";
    decToBin (integer, 2);
    cout << "\n";
    
    binarySum = binToDec(binary, integerEquivalent);
    cout << "\nThe integer equivalent is: \n" << binarySum << "\n";
    
    return 0;
}




// Convert integer to binary. Recursive call.


void decToBin(int integer, int base)
{
    
    if (integer > 0)
    {
        decToBin(integer/base, base);
        cout << integer % base;
    }
    
}




// Convert binary to integer. Recursive call.


int binToDec(int convertBinary, int i)

{
    
    int storedConversion;
    
    if (convertBinary > 0 )
        
// Conversion formula from assignment.
        
    {
        storedConversion = convertBinary % 10;
        binarySum = binarySum + storedConversion * pow(2, i );
        convertBinary = convertBinary / 10;
        i++;
        binToDec(convertBinary, i );
    }
    
    return binarySum;
}