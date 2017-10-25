// Author: Chris Darnell
// Date: 4/20/16
// Description: Project 4.a - findMode.cpp


#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;



// Program to find the mode(s) from an array of int, and sort the array into ascending order.


vector<int> findMode(int numbers[], int size)

    {
    
// Initialize highest frequency.
        
        int highestFrequency = 1;
    
// Vector to hold modes.
    
        vector<int> modes;
    
// Iterate through the array to find the highest frequency without storing modes.
    
    
            for (int i = 0; i < size; i++)
    
            {
        
                int frequencyCount = 1;
            
// Iterate through array again, compare the counts for each value to highest frequency.
        
                for (int j = i + 1; j < size; j++)
            
                {
        
            
                    if (numbers[i] == numbers[j])
            
                    {
                
                        frequencyCount++;
                    }
             }
        
// If count for a value equals highest frequency, push value into results vector.
                
                if (frequencyCount == highestFrequency)
        
                {
            
                    modes.push_back(numbers[i]);
            
                }
        
                if (frequencyCount > highestFrequency)
        
                {
           
                    highestFrequency = frequencyCount;
                    modes.clear();
                    modes.push_back(numbers[i]);
            
                }
            }
    
// Sort modes in ascending order.
    
    sort(modes.begin(), modes.end());
    
    return modes;
}