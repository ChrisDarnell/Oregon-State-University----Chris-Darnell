// Author: Chris Darnell
// Date: 5/25/16
// Description: Project 9.a - main.cpp

#include <iostream>
#include "StringList.hpp"

//int main()
//
//{
//    int i;
//    
//    StringList obj;
//    vector<string> stringvector;
//    
//    obj.add("Guess");
//    obj.add("see");
//    obj.add("drink");
//    obj.add("martyr");
//    obj.add("coffee");
//    
//    stringvector = obj.getAsVector();
//    for(i = 0;i < stringvector.size(); i++)
//        cout << stringvector[i] << endl;
//    
//    printf("\n\nThe list is: \n");
//    obj.setNodeVal(4,"redrum");
//    stringvector = obj.getAsVector();
//    for(i = 0;i < stringvector.size(); i++)
//        cout << stringvector[i] << endl;
//    
//    printf("\n\nThe position of redrum is %d\n",obj.positionOf("redrum") );
//    
//    StringList obj2 = obj;
//    stringvector = obj2.getAsVector();
//    printf("\n\nThe new list is: \n");
//    for(i = 0;i < stringvector.size(); i++)
//        cout << stringvector[i] << endl;
//    
//}