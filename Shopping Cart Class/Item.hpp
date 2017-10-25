// Author: Chris Darnell
// 1/27/2016
// Project 4.b, Item.hpp





#ifndef Item_h
#define Item_h

#include <string>


using std::string;

// Declare class Item with name, price, quantity.


class Item {
    
    private:
        string name;
        double price;
        int quantity;
    
    public:
        Item();
        Item(string, double, int);
    
// Accessor methods
    
    string getName();
    double getPrice();
    int getQuantity();
    
// Mutator methods
    
    void setName(string);
    void setPrice(double);
    void setQuantity(int);

}; 

#endif /* Item_h */
