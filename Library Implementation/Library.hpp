// Author: Chris Darnell
// Date: 6/2/2016
// Description: Project 10.b - Library.hpp

#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include <string>
#include <vector>
#include "Book.hpp"
#include "Album.hpp"
#include "Movie.hpp"
#include "Patron.hpp"


class Library

{
    
    
private:
    
    std::vector<LibraryItem*> holdings;
    std::vector<Patron*> members;
    int currentDate;
    
public:
    
    Library();
    ~Library();
    LibraryItem* findHolding(std::string ItemID);
    Patron* findMember(std::string patronID);
    void addLibraryItem(LibraryItem* item);
    void addMember(Patron* member);
    void checkOutLibraryItem(std::string patronID, std::string ItemID);
    void returnLibraryItem(std::string ItemID);
    void requestLibraryItem(std::string patronID, std::string ItemID);
    void incrementCurrentDate();
    void payFine(std::string patronID, double payment);
    void viewPatronInfo(std::string patronID);
    void viewItemInfo(std::string ItemID);
};

#endif