//  Author: Chris Darnell
//  Date: 1/7/2016
//  Description: Project 1.b; average.cpp


#include <iostream>
#include <string>

// Calculate the averages of 5 numbers.

int main()
{
    
// Declare variables.
    
    
    double numberOne;
    double numberTwo;
    double numberThree;
    double numberFour;
    double numberFive;
    
// Get numbers and compute, display average.

    std::cout << "Please enter five numbers. First number:" << std::endl;
    std::cin >> numberOne;
    std::cout << "Please enter five numbers. Second number:" << std::endl;
    std::cin >> numberTwo;
    std::cout << "Please enter five numbers. Third number:" << std::endl;
    std::cin >> numberThree;
    std::cout << "Please enter five numbers. Fourth number:" << std::endl;
    std::cin >> numberFour;
    std::cout << "Please enter five numbers. Final number:" << std::endl;
    std::cin >> numberFive;
    double numberAverage = (numberOne + numberTwo + numberThree + numberFour + numberFive)/5;
    std::cout << "The average of those numbers is " << numberAverage;
    std::cout << "." << std::endl;
    
    return 0;
}
