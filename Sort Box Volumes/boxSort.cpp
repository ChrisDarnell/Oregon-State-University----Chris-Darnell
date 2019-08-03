
// Date: 4/27/16
// Description: Project 5.b - Box.hpp


#include <iostream>
#include "Box.hpp"

using namespace std;

// Function prototypes.

void boxSort(Box[], int);
void displayArray(Box[], int);


int main()
{

// Initialize array of Box objects.
    
    const int size = 5;
    Box array[size] = {4.6, 5.4, 3.4, 6.78, 3.1};
    
// Display the array.

    
    cout << "The unsorted box volumes are: \n";
    displayArray(array, size);
    
// Sort using bubble sort.
    
    boxSort(array, size);
    
// Display sorted array.
    
    
    cout << "The box volumes sorted from greatest to least are: \n";
    displayArray(array,size);
    
    
    
    
    
    return 0;
}



void displayArray(Box object[], int size)
{
    for (int index = 0; index < size; index++)
    {
        cout << object[index].getVolume() << endl;
    }
}


//void boxSort(Box array[], int size)
//
//{
//    Box temp;
//    bool swap;
//    
//    do
//    {
//        swap = false;
//        for(int count=0; count<(size-1); count++)
//        {
//            
//            if (array[count].getVolume() > array{count + 1].getVolume())
//                {
//                    
//                
//                    temp = array[count];
//                    array[count] = array[count+1];
//                    array[count+1] = temp;
//                    swap = true;
//                }
//                
//        }
//    }
//    while(swap);
//}

                


