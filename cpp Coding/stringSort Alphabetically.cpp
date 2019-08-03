// Author: Chris Darnell
// 2/3/2016
// Project 5.a, stringSort.cpp

#include <iostream>
#include <cctype>

using namespace std;

// Sort string array values alphabetically.

// Function prototypes.


void stringSort(string [], int);
void showArray(string [], int);





int main()

{
    const int SIZE = 5;
    
    string word[SIZE] =
    { "alligator", "Zebra", "cat",
        "Horse", "monkey"};
    
// Display unsorted values.
    
    cout << "The unsorted values are:";
    cout << "\n--------------------------" << endl;
    showArray(word, SIZE);
    
    

    
// Display sorted values.
    
    stringSort(word, SIZE);
   
    
   
    cout << "\nThe sorted values are:";
    cout << "\n--------------------------" << endl;
    showArray(word, SIZE);
    
    return 0;
}

// stringSort function. Performs alphabetical sort on array.

void stringSort(string word[], int size) // Array word of certain size.
{
    int startScan, minIndex;
    string strword;
        
    for (startScan = 0; startScan < (size - 1); startScan++)  // Run scan for every item in array.
    {
        
// Change items all to one case.
        
        
        minIndex = startScan;
        strword = word[startScan];  // For each pass, the word in the array is stored as strword.
      
        for(int index = startScan + 1; index < size; index++) //Run until index is startscan is less than size
        {
        
            if (word[index] < strword)  //If
            {
                strword = word[index];
                minIndex = index;
            }
        }
        word[minIndex] = word[startScan];
        word[startScan] = strword;
    }
}










// showArray function displays contents of array.

void showArray(string word[], int size)
{
    for (int count = 0; count < size; count++)
        cout << word[count] << endl;
}


