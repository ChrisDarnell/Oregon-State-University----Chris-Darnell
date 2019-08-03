//  Author: Chris Darnell
//  Date: 1/13/2016
//  Description: Project 2.d; fallDistance.cpp


// #include <iostream>
// #include <string>
// using namespace std;

// Create a function that takes falling time as an argument.

    double fallDistance(double);

// int main()
{
    
// Declare variables.
    
    
    double fallingTime;
    

// Get falling time from user.
    
    cout << "Enter the falling time in seconds: " << endl;
    cin >> fallingTime;
    
// Call function and display results.
    
    
    cout << "The distance in meters that the object has fallen is " << fallDistance(fallingTime) << ".";

    return 0;
}




// fallDistance Function. Take fallingTime entered by user, use formula to calculate and return distanceMeters.


double fallDistance(double fallingTime)

{
    
    double distanceMeters = 0;
    
    distanceMeters = .5 * 9.8 *(fallingTime * fallingTime);

    return distanceMeters;
}