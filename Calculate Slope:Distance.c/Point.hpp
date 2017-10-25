// Author: Chris Darnell
// Date: 4/13/16
// Description: Project 3.c - Point.hpp

#ifndef Point_hpp
#define Point_hpp

#include <stdio.h>

class Point

{
private:
    
    double xCoord, yCoord;
    
public:
    
// Constructor
    
    Point();
    Point(double, double);
    
// Function prototypes.
    
    void setXCoord(double);
    void setYCoord(double);
    double getXCoord();
    double getYCoord();
    double distanceto(const Point & );

};



#endif /* Point_hpp */
