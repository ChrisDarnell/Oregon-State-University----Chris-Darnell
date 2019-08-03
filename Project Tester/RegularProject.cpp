// Author: Chris Darnell
// Date: 5/18/2016
// Description: Project 8.b - RegularProject.cpp


#include "CustomerProject.hpp"
#include "RegularProject.hpp"



// Constructor for Regular Project class. 

RegularProject::RegularProject(double hours, double materials, double transportation):CustomerProject(hours, materials, transportation)

{
    
}

// Regular override billAmount to return sum materials, transportation, and (80 x hours).

double RegularProject::billAmount()

{
    return materials + transportation + 80 * hours;


};
    
