// Author: Chris Darnell
// Date: 6/2/2016
// Description: Project 10.b - Book.cpp

#include "LibraryItem.hpp"
#include "Book.hpp"





std::string Book::getOrigin()

{
    return getAuthor();
}





void Book::setAuthor(std::string auth)

{
    author = auth;
}





std::string Book::getAuthor()

{
    return author;
}





int Book::getCheckOutLength()

{
    return CHECK_OUT_LENGTH;
}