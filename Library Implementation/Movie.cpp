// Author: Chris Darnell
// Date: 6/2/2016
// Description: Project 10.b - Movie.cpp

#include "LibraryItem.hpp"
#include "Movie.hpp"




std::string Movie::getOrigin()

{
    return getDirector();
}





void Movie::setDirector(std::string direct)

{
    director = direct;
}





std::string Movie::getDirector()

{
    return director;
}





int Movie::getCheckOutLength()

{
    return CHECK_OUT_LENGTH;
}