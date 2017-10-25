// Author: Chris Darnell
// Date: 5/11/16
// Description: Project 7.a - Rectangle.hpp

#ifndef Rectangle_hpp
#define Rectangle_hpp

// Class Rectangle with double fields for length and width.


class Rectangle

{

private:
    double width;
    double length;
    double shapePerimeter;
    double shapeArea;
    
public:
    
    Rectangle();
    Rectangle(double w, double l);
    
    
// Set methods for length and width. Passed two double parameters from constructor.
    
// Methods for area and perimeter.
    
    void setWidth(double w);
    void setLength(double l);
    double perimeter();
    double area();
    
    
};






#endif /* Rectangle_hpp */
