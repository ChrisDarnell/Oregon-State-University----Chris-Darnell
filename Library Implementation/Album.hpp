// Author: Chris Darnell
// Date: 6/2/2016
// Description: Project 10.b - Album.hpp

#ifndef Album_hpp
#define Album_hpp

// These three classes all inherit from LibraryItem.
// All three will need a public static const int CHECK_OUT_LENGTH.  For a Book it's 21 days, for an Album it's 14 days, and for a Movie it's 7 days.
// All three will have an additional field.  For Book, it's a string field called author.  For Album, it's a string field called artist.  For Movie, it's a string field called director.  There will also need to be get methods to return the values of these fields.


#include <string>

class Album : public LibraryItem

{
    
private:
    
    std::string artist;
    
public:
    
    Album(std::string idc, std::string t, std::string art) : LibraryItem(idc, t)
    
    {
        setArtist(art);
        setItemType(ALBUM);
    }
    
    static const int CHECK_OUT_LENGTH = 14;
    std::string getOrigin();
    void setArtist(std::string art);
    std::string getArtist();
    int getCheckOutLength();
    
};

#endif /* Album_hpp */
