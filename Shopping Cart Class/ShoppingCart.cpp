// Author: Chris Darnell
// 1/27/2016
// Project 4.b, ShoppingCart.cpp





#include "Item.hpp"
#include "ShoppingCart.hpp"
#include <iostream>

using std::cout;
using std::endl;


// Construct empty ShoppingCart.


ShoppingCart::ShoppingCart() {
    Item** ptr;
    
  
    for (ptr = itemList; ptr < itemList + SIZE; ptr++) {
        *ptr = NULL;
    }
    
    arrayEnd = 0;
}


// Add Items into ShoppingCart.

void ShoppingCart::addItem(Item *item) {
    if (arrayEnd < SIZE) {
        itemList[arrayEnd++] = item;
    }
}


// Calculate total price for all Items in ShoppingCart.


double ShoppingCart::totalPrice() {
    Item** item;
    double total = 0.0;
    

// Add each price to running total.
    
    
    for (item = itemList; item < itemList + arrayEnd; item++) {
        Item currentItem = **item;
        total += currentItem.getPrice() * currentItem.getQuantity();
    }

// Return total.
    
    return total;
}