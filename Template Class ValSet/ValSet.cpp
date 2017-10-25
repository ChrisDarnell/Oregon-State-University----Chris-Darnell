// Author: Chris Darnell
// Date: 5/18/2016
// Description: Project 8.a - ValSet.cpp

#include "ValSet.hpp"
#include <stdio.h>
using namespace std;



// Default constructor initializes pointer data member to point to array of size 10.
// Initializes the variable that stores the number of values to 0.

template <class T>
ValSet<T>::ValSet()

{
    aptr = new int[10];
    arraySize = 10;
    numberValues = 0;
}

// Destructor.

template <class T>
ValSet<T>::~ValSet()

{
    if(arraySize > 0)
    delete [] aptr;
    numberValues = 0;
    
}

// Copy constructor for ValSet class.

template <class T>
ValSet<T>::ValSet(const ValSet &obj)

{
    arraySize = obj.arraySize;
    T aptr = new ValSet[arraySize];
    for (int count = 0; count < arraySize; count++)
        aptr[count] = obj[count];
    
}

// Overloaded [] operator.


template <class T>
ValSet<T> &ValSet<T>::operator[](int sub)

{
    if (sub < 0 || sub >= arraySize)
        cout << "Error.";
    return aptr[sub];
    
    
}








// size method return number of values currently in ValSet.

template <class T>
int ValSet<T>::size()

{
    return numberValues;
    
}

// isEmpty method should return true if ValSet contains no values, false otherwise.

template <class T>
bool ValSet<T>::isEmpty()

{
    return (numberValues == 0);
}

// contains. Check for value in array.

template <class T>
bool ValSet<T>::contains(T value)

{
    for(int i = 0; i < numberValues; i++)
    
    {
        
        if(aptr[i] == value)
            return true;
    }
    
    return false;
}




// Add value to array.

template <class T>
void ValSet<T>::add(T value)

{
    for(int i = 0; i < numberValues; i++)
    {
        if(aptr[i] == value)
        {
            for(int j = i; j < numberValues - 1; j++)
            {
                aptr[j] = aptr[j - 1];
            }
            
            numberValues++;
            break;
    
        }
    }
    
}



// Remove from array.

template <class T>
void ValSet<T>::remove(T value)

{
    for(int i = 0; i < numberValues; i++)
    {
        if(aptr[i] == value)
        {
            for(int j = i; j < numberValues - 1; j++)
            {
                aptr[j] = aptr[j + 1];
            }
            
            numberValues--;
            break;
            
        }
    }
    
    
    
}

// getAsVector returns vector of type T that contains all values in ValSet.


template <class T>
void ValSet<T>::getAsVector(T)

{
    for(int k = 0; k < numberValues; k++)
    {
        cout << aptr[k] << " ";
        cout << endl;
    }
    
    
}

// Input from assignment.

template class ValSet<int>;
template class ValSet<char>;
template class ValSet<std::string>;



