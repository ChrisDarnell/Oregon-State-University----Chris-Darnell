// Author: Chris Darnell
// Date: 4/13/16
// Description: Project 3.c - LineSegment.cpp

#include "LineSegment.hpp"

LineSegment::LineSegment(Point firstPoint, Point secondPoint)

{
    setEnd1(firstPoint);
    setEnd2(secondPoint);
}

Point LineSegment::getEnd1()

{
    
    return endpointOne;
    
}


Point LineSegment::getEnd2()

{
    return endpointTwo;
}

void LineSegment::setEnd1(Point firstPoint)

{
    endpointOne = firstPoint;
}

void LineSegment::setEnd2(Point secondPoint)

{
    endpointTwo = secondPoint;
}



// Length function, called from Point.

double LineSegment::length()

{
    
return endpointOne.distanceto(endpointTwo);

}

// Slope function.

double LineSegment::slope()

{

                    double xOne = endpointOne.getXCoord();
                    double xTwo = endpointTwo.getXCoord();
                    double yOne = endpointOne.getYCoord();
                    double yTwo = endpointTwo.getYCoord();


    return (yTwo-yOne)/(xTwo-xOne);
                                       
}
                                                         
