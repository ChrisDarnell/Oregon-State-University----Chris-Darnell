// Author: Chris Darnell
// Date: 5/18/2016
// Description: Project 8.b - CustomerProject.cpp



#include "CustomerProject.hpp"


// Constructor for CustomerProject class.

CustomerProject::CustomerProject()

{
    setHours(0);
    setTransportCost(0);
    setMaterialCost(0);
}

// A constructor that takes as parameters the values for each field and calls the set methods to initialize them.

CustomerProject::CustomerProject(double hours, double materials, double transportation)

{
    setHours(hours);
    setTransportCost(transportation);
    setMaterialCost(materials);
}



// Get and set methods for each field.

void CustomerProject::setHours(double hours)

{
    
    this->hours = hours;
}

void CustomerProject::setTransportCost(double tCost)

{
    this->transportation = tCost;
    
}

void CustomerProject::setMaterialCost(double mCost)

{
    this->materials = mCost;
}

double CustomerProject::getHours()

{
    return hours;
}

double CustomerProject::getTransportCost()

{
    return transportation;
}

double CustomerProject::getMaterialCost()

{
    return materials;
}

