// Author: Chris Darnell
// Date: 6/2/2016
// Description: Project 10.b - libMain.cpp



#include "LibraryItem.hpp"
#include "Book.hpp"
#include "Album.hpp"
#include "Movie.hpp"
#include "Patron.hpp"
#include "Library.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>
using namespace std;

// Function Prototypes:


int programMenu();


//
//int main ()
//
//{
//    
//    Library simulation;
//    
//    int input = 0;
//    while (input !=12)
//        
//    {
//        system("clear");
//        input = programMenu();
//        
//        if (input == 1)
//            
//        {
//            string title, author, id;
//            
//// Get user input.
//            
//            cout << " ADD BOOK TO LIBRARY" << endl;
//            cout << "------------------------------" << endl;
//            cout << " Enter Title:  ";
//            getline(cin, title);
//            cout << " Enter Author:  ";
//            getline(cin, author);
//            cout << " Assign Unique ID#:  ";
//            getline(cin, id);
//            
//          
//            LibraryItem* check = simulation.findHolding(id);
//            if (check != NULL)
//            {
//                cout << endl << "That ID is already in use." << endl;
//            }
//            else
//            {
//                Book *newItem;
//                newItem = new Book(id, title, author);
//                
//                simulation.addLibraryItem(newItem);
//                cout << endl << "The book has been added to the library." << endl;
//            }
//            
//            cout << endl << "Press [Enter] to return to the main menu." << endl;
//            cin.ignore();
//        }
//        
//        if (input == 2)
//        {
//            string title, director, id;
//            
//            
//            cout << " ADD MOVIE TO LIBRARY HOLDINGS" << endl;
//            cout << "-------------------------------" << endl;
//            cout << " Enter Title:  ";
//            getline(cin, title);
//            cout << " Enter Director:  ";
//            getline(cin, director);
//            cout << " Assign Unique ID#:  ";
//            getline(cin, id);
//            
//        
//            LibraryItem* check = simulation.findHolding(id);
//            if (check != NULL)
//            {
//                cout << endl << "That ID is already in use." << endl;
//            }
//            else
//            {
//                Movie *newItem;
//                newItem = new Movie(id, title, director);
//                
//                simulation.addLibraryItem(newItem);
//                cout << endl << "The movie has been added to the library." << endl;
//            }
//            
//            cout << endl << "Press [Enter] to return to the main menu." << endl;
//            cin.ignore();
//        }
//        
//        if (input == 3)
//        {
//            string title, artist, id;
//            
//    
//            cout << " ADD ALBUM TO LIBRARY " << endl;
//            cout << "-------------------------------" << endl;
//            cout << " Enter Title:  ";
//            getline(cin, title);
//            cout << " Enter Artist:  ";
//            getline(cin, artist);
//            cout << " Assign Unique ID#:  ";
//            getline(cin, id);
//            
//        
//            LibraryItem* check = simulation.findHolding(id);
//            if (check != NULL)
//            {
//                cout << endl << "That ID is already in use." << endl;
//            }
//            else
//            {
//                Album *newItem;
//                newItem = new Album(id, title, artist);
//                
//                simulation.addLibraryItem(newItem);
//                cout << endl << "The album has been added to the library." << endl;
//            }
//            
//            cout << endl << "Press [Enter] to return to the main menu." << endl;
//            cin.ignore();
//        }
//        
//        if (input == 4)
//        {
//            string name, id;
//            
//            cout << " ADD NEW LIBRARY MEMBER" << endl;
//            cout << "------------------------" << endl;
//            cout << " Enter Name:  ";
//            getline(cin, name);
//            cout << " Enter Unique ID#:  ";
//            getline(cin, id);
//            
//        
//            Patron* check = simulation.findMember(id);
//            if (check != NULL)
//            
//            {
//                cout << endl << "That ID is already in use." << endl;
//            }
//            
//            else
//                
//            {
//                Patron *patron;
//                patron = new Patron(id, name);
//                simulation.addMember(patron);
//                cout << endl << "The patron has been added to the library." << endl;
//            }
//            
//            cout << endl << "Press [Enter] to return to the main menu." << endl;
//            cin.ignore();
//        }
//        
//        if (input == 5)
//        {
//            string id;
//            double payment;
//            
//            cout << " MAKE A PAYMENT ON A LIBRARY FINE " << endl;
//            cout << "----------------------------------" << endl;
//            cout << " Enter Patron ID#:  ";
//            getline(cin, id);
//            cout << " Enter Payment Amount:  $";
//            cin >> payment;
//            payment *= -1;
//            
//            cout << endl;
//            simulation.payFine(id, payment);
//            
//            cin.ignore();
//            cout << endl << "Press [Enter] to return to the main menu." << endl;
//            cin.ignore();
//        }
//        
//        if (input == 6)
//        {
//            string id;
//            
//            cout << " VIEW LIBRARY MEMBER ACCOUNT" << endl;
//            cout << "-----------------------------" << endl;
//            cout << " Enter Patron ID#:  ";
//            cin >> id;
//            
//            cout << endl;
//            simulation.viewPatronInfo(id);
//            cin.ignore();
//            
//            cout << endl << "Press [Enter] to return to the main menu." << endl;
//            cin.ignore();
//        }
//        
//        if (input == 7)
//        {
//            string id;
//            
//            cout << " VIEW LIBRARY ITEM INFORMATION" << endl;
//            cout << "-------------------------------" << endl;
//            cout << " Enter Item ID#:  ";
//            getline(cin, id);
//            
//            cout << endl;
//            simulation.viewItemInfo(id);
//            
//            cout << endl << "Press [Enter] to return to the main menu." << endl;
//            cin.ignore();
//        }
//        
//        if (input == 8)
//        {
//            string ID, ItemID;
//            
//            cout << " REQUEST ITEM FROM LIBRARY" << endl;
//            cout << "---------------------------" << endl;
//            cout << " Enter Patron ID#:  ";
//            getline(cin, ID);
//            cout << " Enter Item ID#:  ";
//            getline(cin, ItemID);
//            
//            cout << endl;
//            simulation.requestLibraryItem(ID, ItemID);
//            
//            cout << endl << "Press [Enter] to return to the main menu." << endl;
//            cin.ignore();
//        }
//        
//        if (input == 9)
//        {
//            string ID, ItemID;
//            
//            cout << " CHECK OUT LIBRARY ITEM" << endl;
//            cout << "------------------------" << endl;
//            cout << " Enter Patron ID#:  ";
//            getline(cin, ID);
//            cout << " Enter Item ID#:  ";
//            getline(cin, ItemID);
//            
//            cout << endl;
//            simulation.checkOutLibraryItem(ID, ItemID);
//            
//            cout << endl << "Press [Enter] to return to the main menu." << endl;
//            cin.ignore();
//        }
//        
//        if (input == 10)
//        {
//            string id;
//            
//            cout << " RETURN LIBRARY ITEM" << endl;
//            cout << "---------------------" << endl;
//            cout << " Enter Item ID#:  ";
//            getline(cin, id);
//            
//            cout << endl;
//            simulation.returnLibraryItem(id);
//            
//            cout << endl << "Press [Enter] to return to the main menu." << endl;
//            cin.ignore();
//        }
//        
//        if (input == 11)
//        {
//            simulation.incrementCurrentDate();
//            cout << "The date has been incremented." << endl;
//            
//            cout << endl << "Press [Enter] to return to the main menu." << endl;
//            cin.ignore();
//        }
//    }
//    
//    return 0;
}


// Display menu.

int programMenu()

{
    int input;
    bool integerFail = false;
    
    cout << endl << endl << endl;
    cout << "       ==========================================" << endl;
    cout << "       |             Library Menu               |" << endl;
    cout << "       ==========================================" << endl;
    cout << "       |   1.  Add Book to Library              |" << endl;
    cout << "       |   2.  Add Movie to Library             |" << endl;
    cout << "       |   3.  Add Album to Library             |" << endl;
    cout << "       |   4.  Add New Member                   |" << endl;
    cout << "       |   5.  Pay Fine                         |" << endl;
    cout << "       |   6.  View Member Account              |" << endl;
    cout << "       |   7.  View Item Information            |" << endl;
    cout << "       |   8.  Request Item                     |" << endl;
    cout << "       |   9.  Check Out Item                   |" << endl;
    cout << "       |   10. Return Item                      |" << endl;
    cout << "       |   11. Increment Current Date           |" << endl;
    cout << "       |   12. Quit                             |" << endl;
    cout << "       ==========================================" << endl;
    cout << "        Option:  ";
    
    do
    
    {
        cin >> input; 
        integerFail = cin.fail();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    while (integerFail == true);
    cout << endl;
    
    return input;
}