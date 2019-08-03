// Author: Chris Darnell
// Date: 5/11/16
// Description: Project 7.b - MyInteger.hpp

#ifndef MyInteger_hpp
#define MyInteger_hpp
#include <iostream>

// Declaration of class MyInteger.

class MyInteger

{
    
    
private:
    
// Field of type point-to-int called pInteger.
    
    int *pInteger;

public:
    
// Constructor.
    
    MyInteger(int obj)
    
    {
        pInteger = new int;
        *pInteger = obj;
    }
    
    
// Destructor.
    
    ~MyInteger()
    
    {
        pInteger = NULL;
        delete pInteger;
        
    };
    
// Function prototypes to get/set int.
    
    int getMyInt();
    void setMyInt(int obj);
    
    
// Copy consructor to overload '='.
    
// Make pInteger in the new object point it. Return of type MyInteger.
    
    MyInteger(MyInteger &obj)
    
    {
        pInteger = new int;
        *pInteger = obj.getMyInt();
    }
    
    
};



#endif /* MyInteger_hpp */
