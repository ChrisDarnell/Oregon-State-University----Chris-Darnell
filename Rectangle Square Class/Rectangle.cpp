// Author: Chris Darnell
// Date: 5/11/16
// Description: Project 7.a - Rectangle.cpp


#include "Rectangle.hpp"

// Initialize values.

Rectangle::Rectangle()

{
    
}


Rectangle::Rectangle(double, double)

{
    width = 0.0;
    length = 0.0;
    
}



// Functions to set and get dimensions.

void Rectangle::setWidth(double w)

{
    width = w;
    
}

void Rectangle::setLength(double l)

{
    length = l;
}





// Calculate shape perimeter.

double Rectangle::perimeter()

{
    return shapePerimeter = 2 * width + 2 * length;
   
    
}

// Calculate shape area.

double Rectangle::area()

{
    return shapeArea = width * length;
    
}


