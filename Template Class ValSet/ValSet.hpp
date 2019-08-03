// Author: Chris Darnell
// Date: 5/18/2016
// Description: Project 8.a - ValSet.hpp


#ifndef ValSet_hpp
#define ValSet_hpp
#include <iostream>
using namespace std;


// Write a template class called ValSet, which represents a mathematical set of values, T.

template <class T>

// ValSet class.

class ValSet

{
    
private:
    
// Variables.
    
    int arraySize;
    T *aptr;
    int numberValues;
    
public:
    
// Constructor/Copy Constructor.
    
    ValSet<T>();
    ValSet<T>(int);
    ValSet<T>(const ValSet &);
    
// Destructor.
    
    ~ValSet<T>();
    
// Overloaded operator.
    
    ValSet<T> &operator[](int);
    
// Methods to handle data.
    
    int size();
    bool isEmpty();
    void add(T);
    void remove(T);
    bool contains(T);
    void getAsVector(T);
    
};



















#endif /* ValSet_hpp */
