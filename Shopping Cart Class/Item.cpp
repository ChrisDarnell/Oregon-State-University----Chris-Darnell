// Author: Chris Darnell
// 1/27/2016
// Project 4.b, Item.cpp




#include <iostream>
#include "Item.hpp"


// Construct empty Item, with name blank, price and quantity set to 0.

Item::Item() {
    
    setName("");
    setPrice(0.0);
    setQuantity(0);
    
}


// Create Item with name, price and quantity.

Item::Item(string nm, double pr, int qnt) {
    setName(nm);
    setPrice(pr);
    setQuantity(qnt);
}


// Return Item name.


string Item::getName() {
    return name;
}


// Return Item price.

double Item::getPrice() {
    return price;
}


// Return Item quantity.

int Item::getQuantity() {
    return quantity;
}


// Set Item name.

void Item::setName(string nm) {
    name = nm;
}


// Set Item price.

void Item::setPrice(double pr) {
    price = pr;
}


// Set Item quantity.

void Item::setQuantity(int qnt) {
    quantity = qnt;
}