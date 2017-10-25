// Author: Chris Darnell
// Date: 5/11/16
// Description: Project 7.a - Square.hpp

#ifndef Square_hpp
#define Square_hpp
#include "Rectangle.hpp"

#include <stdio.h>

// Class Square inherits from Rectangle.


class Square : public Rectangle

{

private:
    
    
public:
    
// Constructor with one double parameter.
    
// Override setLength and setWidth. If either dimension set to a new value, both values will be set to that value.
   
    Square(double length):Rectangle(length, length)
    
    {
        
    }
    
    
    
    
};



#endif /* Square_hpp */
