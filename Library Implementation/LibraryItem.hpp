// Author: Chris Darnell
// Date: 6/2/2016
// Description: Project 10.b - LibraryItem.hpp

#ifndef LIBRARY_ITEM_HPP
#define LIBRARY_ITEM_HPP

#include <string>

// These three locations are mutually exclusive, but note that
// a LibraryItem can be on request for a Patron while being checked
// out to another Patron.  In that case the LibraryItem's location is
// CHECKED_OUT, and when it is returned, it's location will
// become ON_HOLD_SHELF.



class Patron;


enum Locale {ON_SHELF, ON_HOLD_SHELF, CHECKED_OUT};


enum Item {ALBUM = 1, BOOK, MOVIE};

class LibraryItem

{
    
private:
    
    std::string idCode;
    std::string title;
    Locale location;
    Patron* checkedOutBy;
    Patron* requestedBy;
    int dateCheckedOut;
    Item itemType;
    
public:
    
    LibraryItem();
    LibraryItem(std::string idc, std::string t);
    virtual int getCheckOutLength() = 0;
    virtual std::string getOrigin() = 0;
    std::string getIdCode();
    void setIdCode(std::string id);
    std::string getTitle();
    void setTitle(std::string t);
    Locale getLocation();
    void setLocation(Locale lo);
    Patron* getCheckedOutBy();
    void setCheckedOutBy(Patron* p);
    Patron* getRequestedBy();
    void setRequestedBy(Patron* p);
    int getDateCheckedOut();
    void setDateCheckedOut(int d);
    Item getItemType(); 
    void setItemType(Item type);
    
};



#endif /* LibraryItem_h */
