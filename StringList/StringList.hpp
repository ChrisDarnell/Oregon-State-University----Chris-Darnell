// Author: Chris Darnell
// Date: 5/25/16
// Description: Project 9.a - StringList.hpp

#ifndef StringList_hpp
#define StringList_hpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;
    

// A simple linked list class StringList.
    
typedef struct list

{
        string val;
        struct list* next;
    
}

listnode;
    
    
class StringList

{

private:
    
    listnode* root;
        
public:
    
// Member functions from assignment.
    
    
    StringList();
    StringList(const StringList &obj);
    ~StringList();
    void add(string val);
    int positionOf(string val);
    bool setNodeVal(int position, string val);
    vector<string> getAsVector();
    
};
    
    
    


#include <stdio.h>



#endif /* StringList_hpp */
