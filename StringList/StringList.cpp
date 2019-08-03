// Author: Chris Darnell
// Date: 5/25/16
// Description: Project 9.a - StringList.cpp

#include "StringList.hpp"



// The default constructor should initialize a new empty StringList object.

StringList::StringList()

{
   
    root = NULL;

}



// The destructor should delete any memory that was dynamically allocated by the StringList object.

StringList::~StringList()

{
    listnode* temp;
    while(root!= NULL)
    
    {
        temp = root;
        root = root->next;
        delete(temp);
        
    }
    
}



// The copy constructor should create a completely separate duplicate of a StringList object (a deep copy).


StringList::StringList(const StringList& obj)

{
    
    listnode* temp = obj.root;
    while(temp!= NULL){
        add(temp->val);
        temp = temp->next;
        
    }
}



// Add function adds a new node containing the value of the parameter to the end of the list.

void StringList::add(string val)

{
    
    listnode* temp = root;
    listnode* node = new listnode();
    node->val = val;
    if(root == NULL)
        root = node;
    else
        
    {
        while(temp->next != NULL)
            temp = temp->next;
        
        temp->next = node;
    }
}



//  positionitionOf() function returns the (zero-based) position in the list for the first occurrence of the parameter in the list, or -1 if that value is not in the list


int StringList::positionOf(string val)

{
    listnode* temp = root;
    int position = 0;
    while(temp != NULL)
    
    {
        if(temp->val == val)
            return position;
        
        else
            temp = temp->next;
        position++;
    }
    
    return -1;
   
}




//  In the setNodeVal() function, the first parameter represents a (zero-based) position in the list.

//  The setNodeVal() function sets the value of the node at that position to the value of the string parameter.

//  If the position parameter is >= the number of nodes in the list, the operation cannot be carried out and setNodeVal() should return false, otherwise it should be successful and return true.

bool StringList::setNodeVal(int position, string val)

{
    listnode* temp = root;
    int index = 0;
    while(temp != NULL)
    
    {
        if(index == position)
        
        {
            temp->val = val;
            return true;
        }
        
        if (index > position)
       
        {
            return false;
        }
        
        temp = temp->next;
        index++;
    }
    return false;
    
}


// The getAsVector() function returns a vector with the same size, values and order as the StringList.

vector<string> StringList::getAsVector()

{
    
    listnode* temp = root;
    vector<string> listofstring;
    while(temp != NULL)
    
    {
        listofstring.push_back(temp->val);
        temp = temp->next;
    }
    
    return listofstring;
}





