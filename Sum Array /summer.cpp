// Author: Chris Darnell
// Date: 5/4/2016
// Description: Project 6.a - summer.cpp

// A program that takes an array of doubles and the size of the array and returns the sum of the values in the array.


// Use recursive function. Don't use loops or static variables.



#include <iostream>
using namespace std;

// Function prototype.

double summer(double [], int);

//int main()
//
//{
//    int size;
//    
//// Get values/size of array.
//    
//    cout << "How many numbers are in the array?\n";
//    cin >> size;
//    double inputArray[size];
//    
//    cout << "Enter the numbers you wish to sum: \n";
//    
//    for(int i=0; i < size; i++)
//    
//    {
//        cin >> inputArray[i];
//        
//    }
//    
//// Call recursive function summer to calculate sum.
//    
//    double arraySum = summer(inputArray, size);
//    
//// Display sum of values in array.
//    
//    cout << "The sum of the numbers in the array is: \n";
//    cout << arraySum << endl;
//    
//    return 0;
//}







// Summer recursive function.
    
// Sums the numbers in the array.
    
    double summer(double inputArray[], int size)
    
    {
        
// Base case.
        
        if(size < 0)
        {
            return 0;
        }
        
// Call summer function recursively.
        
        
        else
            return inputArray[size] + summer(inputArray, size - 1);
    }

    
   
 
