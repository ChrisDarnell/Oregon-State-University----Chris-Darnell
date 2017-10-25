// Author: Chris Darnell
// Date: 5/18/2016
// Description: Project 8.b - PreferredProject.hpp

#ifndef PreferredProject_hpp
#define PreferredProject_hpp

#include <stdio.h>
#include "CustomerProject.hpp"

// Preferred override billAmount to return sum of 85% materials, 90% transport, (80 x hours) up to 100.
// > 100 are free.

class PreferredProject : public CustomerProject

{
    
public:
   
    PreferredProject(double hours, double materials, double transportation);
    
    virtual double billAmount();
    
};



#endif /* PreferredProject_hpp */
