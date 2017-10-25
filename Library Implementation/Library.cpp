// Author: Chris Darnell
// Date: 6/2/2016
// Description: Project 10.b - Library.cpp

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

// Library:
// holdings - a vector of pointers to LibraryItems in the Library
// members - a vector of pointers to Patrons in the Library
// currentDate - stores the current date represented as an integer number of "days" since the Library object was created
// a constructor that initializes the currentDate to zero
// addLibraryItem - adds the parameter to holdings
// addPatron - adds the parameter to members
// getLibraryItem - returns a pointer to the LibraryItem corresponding to the ID parameter, or NULL if no such LibraryItem is in the holdings
// getPatron - returns a pointer to the Patron corresponding to the ID parameter, or NULL if no such Patron is a member
// In checkOutLibraryItem, returnLibraryItem and requestLibraryItem, check the listed conditions in the order given - for example, if checkOutLibraryItem is called with an invalid LibraryItem ID and an invalid Patron ID, it should just return "item not found"
// checkOutLibraryItem
// if the specified LibraryItem is not in the Library, return "item not found"
// if the specified Patron is not in the Library, return "patron not found"
// if the specified LibraryItem is already checked out, return "item already checked out"
// if the specified LibraryItem is on hold by another Patron, return "item on hold by other patron"
// otherwise update the LibraryItem's checkedOutBy, dateCheckedOut and Location; if the LibraryItem was on hold for this Patron, update requestedBy; update the Patron's checkedOutItems; return "check out successful"
// returnLibraryItem
// if the specified LibraryItem is not in the Library, return "item not found"
// if the LibraryItem is not checked out, return "item already in library"
// update the Patron's checkedOutItems; update the LibraryItem's location depending on whether another Patron has requested it; update the LibraryItem's checkedOutBy; return "return successful"
// requestLibraryItem
// if the specified LibraryItem is not in the Library, return "item not found"
// if the specified Patron is not in the Library, return "patron not found"
// if the specified LibraryItem is already requested, return "item already on hold"
// update the LibraryItem's requestedBy; if the LibraryItem is on the shelf, update its location to on hold; return "request successful"
// payFine
// if the specified Patron is not in the Library, return "patron not found"
// use amendFine to update the Patron's fine; return "payment successful"
// incrementCurrentDate
// increment current date; increase each Patron's fines by 10 cents for each overdue LibraryItem they have checked out (using amendFine)
// be careful - a LibraryItem can be on request without its location being the hold shelf (if another Patron has it checked out);





#include "LibraryItem.hpp"
#include "Patron.hpp"
#include "Library.hpp"
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;



Library::Library()

{
    currentDate = 0;
}





Library::~Library()

{
    for (int patron = 0; patron < (members.size()); patron++)
    {
        delete members[patron];
    }
    
    for (int item = 0; item < (holdings.size()); item++)
    {
        delete holdings[item];
    }
}





LibraryItem* Library::findHolding(std::string ItemID)

{
    int size = holdings.size();
    for (int index = 0; index < size; index++)
    {
        if ((holdings[index]->getIdCode()) == ItemID)
        {
            return holdings[index];
        }
    }
    
    return NULL;
}




Patron* Library::findMember(std::string patronID)

{
    int size = members.size();
    for (int index = 0; index < size; index++)
        
    {
        if ((members[index]->getIdNum()) == patronID)
            
        {
            return members[index];
        }
    }
    
    return NULL;
}





void Library::addLibraryItem(LibraryItem* item)

{
    holdings.push_back(item);
}




void Library::addMember(Patron* member)
{
    members.push_back(member);
}





void Library::checkOutLibraryItem(std::string patronID, std::string ItemID)

{
    LibraryItem* holding = findHolding(ItemID);
    Patron* member = findMember(patronID);
    
    if (holding == NULL)
        
    {
        cout << "Item with ID# " << ItemID;
        cout << " is not a holding in this library." << endl;
        if (member == NULL)
            
        {
            cout << "A Patron with ID# " << patronID;
            cout << " is not a member of this library." << endl;
        }
        
        return;
    }
    else if (member == NULL)
    {
        cout << "A Patron with ID# " << patronID;
        cout << " is not a member of this library." << endl;
        if (holding == NULL)
        {
            cout << "Item with ID# " << ItemID;
            cout << " is not a holding in this library." << endl;
        }
        return;
    }
    
    if (holding->getLocation() == CHECKED_OUT)
    {
        Patron* checker = holding->getCheckedOutBy();
        if ((checker->getIdNum()) == patronID)
            
        {
            cout << "Item with ID# " << ItemID;
            cout << " is already checked out by " << member->getName();
            cout << "." << endl;
            return;
        }
        
        cout << holding->getTitle() << " with ID# " << ItemID;
        cout << " is already checked out by another Patron." << endl;
        return;
    }
    
    if ((holding->getRequestedBy()) != NULL)
        
    {
        Patron* holder = holding->getRequestedBy();
        if ((holding->getLocation() == ON_HOLD_SHELF) && (holder->getIdNum() != patronID))
            
        {
            cout << holding->getTitle() << " with ID# " << ItemID;
            cout << " is on hold by another Patron." << endl;
            return;
        }
    }
    
    
    holding->setCheckedOutBy(member);
    holding->setDateCheckedOut(currentDate);
    holding->setLocation(CHECKED_OUT);
    
 
    if ((holding->getRequestedBy()) != NULL)
    {
        Patron* holder = holding->getRequestedBy();
        if (holder->getIdNum() == patronID)
        {
            holding->setRequestedBy(NULL);
        }
    }
    
 
    member->addLibraryItem(holding);
    
   
    cout << holding->getTitle() << " with ID# " << ItemID;
    cout << " has been checked out to " << member->getName() << "." << endl;
}





void Library::returnLibraryItem(std::string ItemID)

{
    LibraryItem* holding = findHolding(ItemID);
    
    if (holding == NULL)
    {
        cout << "Item with ID# " << ItemID;
        cout << " is not a holding in this library." << endl;
        return;
    }
    
    if (holding->getLocation() != CHECKED_OUT)
    {
        cout << "Item with ID# " << ItemID;
        cout << " is not checked out." << endl;
        return;
    }
    
    Patron* member = holding->getCheckedOutBy();
    
    
    member->removeLibraryItem(holding);
  
    if ((holding->getRequestedBy()) != NULL)
    {
        holding->setLocation(ON_HOLD_SHELF);
    }
    else
    {
        holding->setLocation(ON_SHELF);
    }
    
    holding->setCheckedOutBy(NULL);
    

    cout << holding->getTitle() << " has been returned." << endl;
}





void Library::requestLibraryItem(std::string patronID, std::string ItemID)

{
    LibraryItem* holding = findHolding(ItemID);
    Patron* member = findMember(patronID);
    
    if (holding == NULL)
    {
        cout << "Item with ID# " << ItemID;
        cout << " is not a holding in this library." << endl;
        if (member == NULL)
        {
            cout << "A Patron with ID# " << patronID;
            cout << " is not a member of this library." << endl;
        }
        return;
    }
    else if (member == NULL)
    {
        cout << "A Patron with ID# " << patronID;
        cout << " is not a member of this library." << endl;
        if (holding == NULL)
        {
            cout << "Item with ID# " << ItemID;
            cout << " is not a holding in this library." << endl;
        }
        return;
    }
    
    if (holding->getRequestedBy() != NULL)
    {
        Patron* holder = holding->getRequestedBy();
        if ((holder->getIdNum()) == patronID)
        {
            cout << "Item with ID# " << ItemID;
            cout << " is already requested by " << member->getName();
            cout << "." << endl;
            return;
        }
        
        cout << "Item with ID# " << ItemID;
        cout << " is already requested by another Patron." << endl;
        return;
    }
    
    if (holding->getCheckedOutBy() == member)
    {
        cout << "Item with ID# " << ItemID;
        cout << " is already checked out by Patron ID# " << patronID;
        cout << "." << endl;
        return;
    }
    
   
    holding->setRequestedBy(member);
    
 
    if (holding->getLocation() == ON_SHELF)
    {
        holding->setLocation(ON_HOLD_SHELF);
    }
    
    
    cout << holding->getTitle() << " is now on request for " << member->getName();
    cout << "." << endl;
}





void Library::incrementCurrentDate()

{
    currentDate++;
    
    for (int patron = 0; patron < (members.size()); patron++)
    {
        vector<LibraryItem*> payment = members[patron]->getCheckedOutItems();
        for (int items = 0; items < (payment.size()); items++)
        {
           
            LibraryItem* checked = payment[items];
            
            int days_checked_out  = currentDate - (checked->getDateCheckedOut());
            int days_left = (checked->getCheckOutLength()) - days_checked_out;
            
            if (days_checked_out > (checked->getCheckOutLength()))
            {
                members[patron]->amendFine(.10);
            }
        }
    }
}






void Library::payFine(std::string patronID, double payment)

{
    Patron* member = findMember(patronID);
    
    if (member == NULL)
        
    {
        cout << "A Patron with ID# " << patronID;
        cout << " is not a member of this library." << endl;
        return;
    }
    
  
    member->amendFine(payment);
    
  
    cout << "The fines for " << member->getName();
    cout << " are now $" << fixed << setprecision(2) << member->getFineAmount() <<  endl;
}





void Library::viewPatronInfo(std::string patronID)
{
    Patron* member = findMember(patronID);
    
    if (member == NULL)
    {
        cout << "A Patron with ID# " << patronID;
        cout << " is not a member of this library." << endl;
        return;
    }
    
    cout << "-----------------------------------------------" << endl;
    cout << " Patron ID#:  " << member->getIdNum() << endl;
    cout << " Name:  " << member->getName() << endl;
    cout << "-----------------------------------------------" << endl;
    cout <<"             Checked Out Items:";
    
    vector<LibraryItem*> items = member->getCheckedOutItems();
    
    if (items.empty())
    {
        cout << " None." << endl;
    }
    else
    {
        cout << endl << endl;
        int size = items.size();
        if (size == 1)
        {
            LibraryItem* checked = items[0];
            string title = checked->getTitle();
            string origin = checked->getOrigin();
            string id = checked->getIdCode();
            
            if ((checked->getItemType()) == 1)
            {
                cout << "   Album: ";
            }
            if ((checked->getItemType()) == 2)
            {
                cout << "   Book: ";
            }
            if ((checked->getItemType()) == 3)
            {
                cout << "   Movie: ";
            }
            cout <<  title << " by " << origin << ", ID# " << id << endl << endl;
        }
        else if (size > 1)
        {
            LibraryItem* checked;
            string title, origin, id;
            for (int index = 0; index < size; index++)
            {
                checked = items[index];
                title = checked->getTitle();
                origin = checked->getOrigin();
                id = checked->getIdCode();
                
                if ((checked->getItemType()) == 1)
                {
                    cout << "   Album: ";
                }
                if ((checked->getItemType()) == 2)
                {
                    cout << "   Book: ";
                }
                if ((checked->getItemType()) == 3)
                {
                    cout << "   Movie: ";
                }
                cout  << title << " by " << origin << ", ID# " << id << endl;
            }
            cout << endl;
        }
    }
    
    cout << "-----------------------------------------------" << endl;
    cout << " Current Fines:  $" << fixed << setprecision(2) << member->getFineAmount() << endl;
    cout << "-----------------------------------------------" << endl;
}





void Library::viewItemInfo(std::string ItemID)
{
    LibraryItem* holding = findHolding(ItemID);
    
    if (holding == NULL)
    {
        cout << "Item with ID# " << ItemID;
        cout << " is not a holding in this library." << endl;
        return;
    }
    
    
    cout << "-----------------------------------------------" << endl;
    
    
    cout << " Item ID#:  " << ItemID << endl;
 
    if ((holding->getItemType()) == BOOK)
    {
        cout << " Item Description:  Book" << endl;
        cout << " Author:  " << holding->getOrigin() << endl;
    }
    else if ((holding->getItemType()) == ALBUM)
    {
        cout << " Item Description:  Album" << endl;
        cout << " Artist:  " << holding->getOrigin() << endl;
    }
    else if ((holding->getItemType()) == MOVIE)
    {
        cout << " Item Description:  Movie" << endl;
        cout << " Director:  " << holding->getOrigin() << endl;
    }
    
   
    cout << " Title:  " << holding->getTitle() << endl;
    cout << "-----------------------------------------------" << endl << endl;
    
   
    cout << "         Current Location:  ";
    if ((holding->getLocation()) == 0)
    {
        cout << "On Shelf" << endl;
    }
    else if ((holding->getLocation()) == 1)
    {
        cout << "On Hold Shelf" << endl;
    }
    else if ((holding->getLocation()) == 2)
    {
        cout << "Checked Out" << endl;
    }
    

    if ((holding->getRequestedBy()) != NULL)
    {
        Patron* requester = holding->getRequestedBy();
        
        cout << "         Requested By:  " << requester->getName() << endl;
    }
    else
    {
        cout << "         Requested By:  None" << endl;
    }
    

    if ((holding->getCheckedOutBy()) != NULL)
    {
        Patron* checker = holding->getCheckedOutBy();
        
        cout << "         Checked Out By:  " << checker->getName() << endl;
    }
    else
    {
        cout << "         Checked Out By:  None" << endl;
    }
    

    if ((holding->getLocation()) == 2)
    {
        int days_checked_out  = currentDate - (holding->getDateCheckedOut());
        int days_left = (holding->getCheckOutLength()) - days_checked_out;
        if (days_checked_out > (holding->getCheckOutLength()))
        {
            cout << "         Status:  OVERDUE" << endl;
        }
        else if (days_checked_out < (holding->getCheckOutLength()))
        {
            cout << "         Status:  " << days_left << " DAYS LEFT UNTIL DUE" << endl;
        }
        else if (days_checked_out == (holding->getCheckOutLength()))
        {   
            cout << "         Status:  DUE TODAY" << endl;
        }
    }
    else
    {
        cout << "         Status:  Not Checked Out" << endl;
    } 
    
    cout << endl << "-----------------------------------------------" << endl;
}
