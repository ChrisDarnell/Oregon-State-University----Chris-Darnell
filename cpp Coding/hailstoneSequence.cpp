//  Author: Chris Darnell
//  Date: 1/13/2016
//  Description: Project 2.f; hailstone.cpp


// #include <iostream>
// #include <string>
// using namespace std;

// Write a function named hailstone to count steps in a hailstone sequence.

    int Hailstone(int);

// int main()
{
    
    int startInteger = 0;

    cout << "Enter a positive integer to start the sequence: " << endl;
    cin >> startInteger;
    
// Output for function testing.
    
    cout << "Steps: " << Hailstone(startInteger) << endl;
    return 0;
}

    
// Test if number is even or odd, return the value, adding to step count for each turn through loop.


int Hailstone(int startInteger)

    {
    int stepsCount = 0;
    while (startInteger != 1)
    
    
        if (startInteger % 2 == 0)
    {
        startInteger /= 2;
        stepsCount++;
    }
    else
    {
        startInteger = 3 * startInteger + 1;
        stepsCount++;
        
        
    }
   

    return stepsCount;
    
}
