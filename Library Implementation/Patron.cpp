// Author: Chris Darnell
// Date: 6/2/2016
// Description: Project 10.b - Patron.cpp



// Patron:
// idNum - a unique identifier for a Patron - you can assume uniqueness, you don't have to enforce it
// name - cannot be assumed to be unique
// checkedOutItems - a vector of pointers to LibraryItems that a Patron currently has checked out
// fineAmount - how much the Patron owes the Library in late fines (measured in dollars); this is allowed to go negative
// constructor - takes an idNum and name
// some get and set methods
// addLibraryItem - adds the specified LibraryItem to checkedOutItems
// removeLibraryItem - removes the specified LibraryItem from checkedOutItems
// amendFine - a positive argument increases the fineAmount, a negative one decreases it; this is allowed to go negative


#include "LibraryItem.hpp"
#include "Patron.hpp"





Patron::Patron()

{
    setIdNum("");
    setName("");
}





Patron::Patron(std::string idn, std::string n)

{
    setIdNum(idn);
    setName(n);
}





std::string Patron::getIdNum()

{
    return idNum;
}





std::string Patron::getName()

{
    return name;
}




void Patron::setIdNum(std::string id)

{
    idNum = id;
}





void Patron::setName(std::string n)

{
    name = n;
}





std::vector<LibraryItem*> Patron::getCheckedOutItems()

{
    return checkedOutItems;
}





void Patron::addLibraryItem(LibraryItem* b)

{
    checkedOutItems.push_back(b);
}




void Patron::removeLibraryItem(LibraryItem* b)
{
    std::string id;
    id = b->getIdCode();
    
    int size = checkedOutItems.size();
    for (int index = 0; index < size; index++)
    {
        if ((checkedOutItems[index]->getIdCode()) == id)
        {
            checkedOutItems.erase(checkedOutItems.begin() + index);
            size = index;
        }
    }
}





double Patron::getFineAmount()
{
    return fineAmount;
}





void Patron::amendFine(double amount)
{
    fineAmount += amount;
   
}