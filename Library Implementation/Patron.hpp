// Author: Chris Darnell
// Date: 6/2/2016
// Description: Project 10.b - Patron.hpp

#ifndef PATRON_HPP
#define PATRON_HPP

#include <string>
#include <vector>

class LibraryItem;

class Patron

{
    
private:
    
    std::string idNum;
    std::string name;
    std::vector<LibraryItem*> checkedOutItems;
    double fineAmount;
    
public:
    
    Patron();
    Patron(std::string idn, std::string n);
    std::string getIdNum();
    std::string getName();
    void setIdNum(std::string);
    void setName(std::string);
    std::vector<LibraryItem*> getCheckedOutItems();
    void addLibraryItem(LibraryItem* b);
    void removeLibraryItem(LibraryItem* b);
    double getFineAmount();
    void amendFine(double amount);
    
};

#endif