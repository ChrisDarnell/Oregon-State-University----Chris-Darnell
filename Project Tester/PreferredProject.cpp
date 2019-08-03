// Author: Chris Darnell
// Date: 5/18/2016
// Description: Project 8.b - PreferredProject.cpp

#include "PreferredProject.hpp"
#include "CustomerProject.hpp"


// Constructor for PreferredProject class.

PreferredProject::PreferredProject(double hours, double materials, double transportation):CustomerProject(hours, materials, transportation)

{
    
    
}

// Preferred override billAmount to return sum of 85% materials, 90% transport, (80 x hours) up to 100.
// > 100 are free.


double PreferredProject::billAmount()

{
   
    if(hours < 100)
        return .85 * materials + .90 * transportation + 80 * hours;
    else
        return .85 * materials + .90 * transportation + 80 * 100;
};

