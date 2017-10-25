// Author: Chris Darnell
// Date: 4/13/16
// Description: Project 3.c - Point.cpp


#include "Point.hpp"
#include <cmath>

Point::Point()

{
    setXCoord(0);
    setYCoord(0);
}

Point::Point(double x, double y)

{
    setXCoord(x);
    setYCoord(y);
    
};

double Point::getXCoord()

{
    return xCoord;
}

double Point::getYCoord()

{
    return yCoord;
}


void Point::setXCoord(double x)

{

    xCoord = x;
}

void Point::setYCoord(double y)

{
    yCoord = y;
}


// Distance fuction.

// Calculate distance between x and y points seperately, use in formula.

double Point::distanceto(const Point & terminationPoint)

{

    double xDistance = terminationPoint.xCoord - xCoord;
    double yDistance = terminationPoint.yCoord - yCoord;
    return sqrt(xDistance * xDistance + yDistance * yDistance);
}
