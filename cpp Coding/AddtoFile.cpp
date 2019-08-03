//  Author: Chris Darnell
//  Date: 1/13/2016
//  Description: Project 2.b; fileAdder.cpp


#include <iostream>
#include <fstream>
using namespace std;



// Pull numbers from a file, write sum to output file.


    int main()
{
    ifstream inputFile;
    ofstream outputFile("sum.txt");
    int number;
    int sum;
    string filename;
    
// Get filename from user.
    
    cout << "Please enter the filename you would like to open: ";
    cin >> filename;
    
// Open the input file.
    
    inputFile.open(filename.c_str());
    
// If file opens successfully, process it and tally sum.
    
    if (inputFile)
    {
        while (inputFile >> number)
            cout << number << endl;
        sum += number;
    }

// Display error message if file not accessed.
 
    else
  {
    cout << "could not access file";
  }
    
// Close input and output files.

    inputFile.close();
    outputFile.close();
    
    return 0;
}