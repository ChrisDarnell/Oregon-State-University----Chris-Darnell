// Author: Chris Darnell
// Date: 5/11/16
// Description: Project 7.b - MyInteger.cpp

// Program to return list of integers. 


#include "MyInteger.hpp"
#include <iostream>



//int main()
//
//{
//    
//// Prompt from assignment.
//    
//    std::cout << "Output: \n";
//    
//    MyInteger obj1(17);
//    MyInteger obj2 = obj1;
//    std::cout << obj1.getMyInt() << std::endl;
//    std::cout << obj2.getMyInt() << std::endl;
//    
//    obj2.setMyInt(9);
//    std::cout << obj1.getMyInt() << std::endl;
//    std::cout << obj2.getMyInt() << std::endl;
//    
//    MyInteger obj3(42);
//    obj2 = obj3;
//    std::cout << obj2.getMyInt() << std::endl;
//    std::cout << obj3.getMyInt() << std::endl;
//    
//    
//    obj3.setMyInt(1);
//    std::cout << obj2.getMyInt() << std::endl;
//    std::cout << obj3.getMyInt() << std::endl;
//    
//    return 0;
//}


// Function calls for get/set int. 


void MyInteger::setMyInt(int obj)

{
    
    *pInteger = obj;
}

int MyInteger::getMyInt()

{
    return *pInteger;
}





