//  Author: Chris Darnell
//  Date: 1/13/2016
//  Description: Project 2.e; smallSort.cpp


// #include <iostream>
// #include <string>
// using namespace std;



// Create a void function smallSort.cpp that sorts values into ascending order.

    
void smallSort(int&, int&, int&);
    


// int main()

// Prompt for user numbers to sort.

{
        int numberOne, numberTwo, numberThree;
        
        
        cout << "Enter the first number:" << endl;
        cin >> numberOne;
        cout << "Enter the second number:" << endl;
        cin >> numberTwo;
        cout << "Enter the third number:" << endl;
        cin >> numberThree;
        
// Call smallSort function.
      
        
        smallSort(numberOne, numberTwo, numberThree);
        
        return 0;
}
    



// smallSort void function. Test value of each number against one another, return outcome.


void smallSort(int& numberOne, int& numberTwo, int& numberThree)

{
        if(numberOne > numberTwo)
            swap(numberOne, numberTwo);
        if(numberOne > numberThree)
            swap(numberOne, numberThree);
        if(numberTwo > numberThree)
            swap(numberTwo, numberThree);
        
    
        cout << numberOne << ", " << numberTwo << ", " << numberThree << endl;
}