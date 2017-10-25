// Author: Chris Darnell
// Date: 6/2/2016
// Description: Project 10.b - LibraryItem.cpp

#include <iostream>
#include "Patron.hpp"

// LibraryItem:
// idCode - a unique identifier for a LibraryItem - you can assume uniqueness, you don't have to enforce it
// title - cannot be assumed to be unique
// location - a LibraryItem can be either on the shelf, on the hold shelf, or checked out
// checkedOutBy - pointer to the Patron who has it checked out (if any)
// requestedBy - pointer to the Patron who has requested it (if any); a LibraryItem can only be requested by one Patron at a time
// dateCheckedOut - when a LibraryItem is checked out, this will be set to the currentDate of the Library
// constructor - takes an idCode, and title; checkedOutBy and requestedBy should be initialized to NULL; a new LibraryItem should be on the shelf
// some get and set methods

#include "LibraryItem.hpp"




LibraryItem::LibraryItem()

{
    setIdCode("");
    setTitle("");
    setCheckedOutBy(NULL);
    setRequestedBy(NULL);
    setLocation(ON_SHELF);
}





LibraryItem::LibraryItem(std::string idc, std::string t)

{
    setIdCode(idc);
    setTitle(t);
    setCheckedOutBy(NULL);
    setRequestedBy(NULL);
    setLocation(ON_SHELF);
}





std::string LibraryItem::getIdCode()

{
    return idCode;
}





void LibraryItem::setIdCode(std::string id)

{
    idCode = id;
}





std::string LibraryItem::getTitle()

{
    return title;
}





void LibraryItem::setTitle(std::string t)

{
    title = t;
}





Locale LibraryItem::getLocation()

{
    return location;
}





void LibraryItem::setLocation(Locale lo)

{
    location = lo;
}






Patron* LibraryItem::getCheckedOutBy()

{
    return checkedOutBy;
}





void LibraryItem::setCheckedOutBy(Patron *p)

{
    checkedOutBy = p;
}




Patron* LibraryItem::getRequestedBy()

{
    return requestedBy;
}





void LibraryItem::setRequestedBy(Patron* p)

{
    requestedBy = p;
}




int LibraryItem::getDateCheckedOut()

{
    return dateCheckedOut;
}





void LibraryItem::setDateCheckedOut(int d)

{
    dateCheckedOut = d;
}





Item LibraryItem::getItemType()

{
    return itemType;
}





void LibraryItem::setItemType(Item type)
{
    itemType = type;
}







