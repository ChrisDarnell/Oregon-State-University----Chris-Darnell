//  Author: Chris Darnell
//  Date: 1/7/2016
//  Description: Project 1.d; change.cpp


#include <iostream>
#include <string>

// Determine how many of each type of coin makes up a certain number of cents.

int main()
{
    
// Get number cents and compute.
    
    int numberCents;
    
    std::cout << "Please enter an amount in cents less than a dollar. " << std::endl;
    std::cin >> numberCents;
    int numberQuarters = numberCents/25;
    int numberDimes =   (numberCents%25) / 10;
    int numberNickels =  ((numberCents%25)%10) / 5;
    int numberPennies =  ((numberCents%25)%10)%5;
    
// Display results.
    
    std::cout << "Your change will be: " << std::endl;
    std::cout << "Q: " << numberQuarters << std::endl;
    std::cout << "D: " << numberDimes << std::endl;
    std::cout << "N: " << numberNickels << std::endl;
    std::cout << "P: " << numberPennies << std::endl;
    
    return 0;
}
