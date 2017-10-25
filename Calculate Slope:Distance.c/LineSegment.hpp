// Author: Chris Darnell
// Date: 4/13/16
// Description: Project 3.c - LineSegment.hpp

#ifndef LineSegment_hpp
#define LineSegment_hpp

#include <stdio.h>
#include "Point.hpp"

class LineSegment

{
private:
     Point endpointOne, endpointTwo;
    
public:
    
// Constructor
    
    LineSegment();
    LineSegment(Point, Point);
    
// Function prototypes.
    
    
    void setEnd1(Point);
    void setEnd2(Point);
    Point getEnd1();
    Point getEnd2();
    double length();
    double slope();
};

    




#endif /* LineSegment_hpp */
