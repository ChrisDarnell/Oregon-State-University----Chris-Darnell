// Author: Chris Darnell
// Date: 5/18/2016
// Description: Project 8.b - CustomerProject.hpp

#ifndef CustomerProject_hpp
#define CustomerProject_hpp

#include <stdio.h>

// Write a class called Customer Project. 3 double fields.

class CustomerProject

{

protected:
    
    double hours, transportation, materials;
    
    
public:
    
    CustomerProject();
    CustomerProject(double hours, double materials, double transportation);
    
    void setHours(double hours);
    void setTransportCost(double tCost);
    void setMaterialCost(double mCost);
    
    double getHours();
    double getTransportCost();
    double getMaterialCost();
    
//  A pure virtual function called billAmount that takes no parameters and returns a double.
    
    virtual double billAmount() = 0;

};



#endif /* CustomerProject_hpp */
