// Author: Chris Darnell
// Date: 6/2/2016
// Description: Project 10.b - Album.cpp

#include "LibraryItem.hpp"
#include "Album.hpp"





std::string Album::getOrigin()

{
    return getArtist();
}





void Album::setArtist(std::string art)

{
    artist = art;
}





std::string Album::getArtist()

{
    return artist;
}





int Album::getCheckOutLength()

{
    return CHECK_OUT_LENGTH;
}

