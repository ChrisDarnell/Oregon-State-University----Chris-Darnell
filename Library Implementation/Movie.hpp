// Author: Chris Darnell
// Date: 6/2/2016
// Description: Project 10.b - Movie.hpp




// These three classes all inherit from LibraryItem.
// All three will need a public static const int CHECK_OUT_LENGTH.  For a Book it's 21 days, for an Album it's 14 days, and for a Movie it's 7 days.
// All three will have an additional field.  For Book, it's a string field called author.  For Album, it's a string field called artist.  For Movie, it's a string field called director.  There will also need to be get methods to return the values of these fields.



#include <string>

#ifndef MOVIE_HPP
#define MOVIE_HPP
class Movie : public LibraryItem

{
    
private:
    
    std::string director;
    
public:
    
    Movie(std::string idc, std::string t, std::string direct) : LibraryItem(idc, t)
    
    {
        setDirector(direct);
        setItemType(MOVIE);
    }
    
    static const int CHECK_OUT_LENGTH = 7;
    std::string getOrigin();
    void setDirector(std::string direct);
    std::string getDirector();
    int getCheckOutLength();
    
};

#endif
