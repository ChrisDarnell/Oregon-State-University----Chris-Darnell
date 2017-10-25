//// Author: Chris Darnell
//// Date: 4/20/16
//// Description: Project 4.a - findMode testing main.
//
//
//// Program to test findMode.cpp
//
//
//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//using std::cin;
//using std::cout;
//using std::endl;
//using std::vector;
//
//
//// Function prototypes.
//
//vector<int> findMode(int [], int);
//
//
//
//int main()
//
//{
//    
//// Variables. Set max Integers and initialize total of integers the user plans to enter at 0.
//    
//    const int maximumIntegers = 30;
//    int integersEntered[maximumIntegers];
//    int totalIntegers = 0;
//    
//// Get user input.
//    
//    cout << "How many integers would you like to enter? \n";
//    cin >> totalIntegers;
//    
//// Input validation, keep number of integers within bounds.
//    
//    if (totalIntegers < 1)
//        
//        {
//            totalIntegers = 1;
//        }
//    
//    else if (totalIntegers > 30)
//    
//        { totalIntegers = 30; }
//    
//        cout << "Enter the integers: \n";
//    
//// Get integers from user, send to findMode function. 
//    
//    for (int i = 0; i < totalIntegers; i++)
//    
//    {
//        cin >> integersEntered[i];
//    }
//    
//    vector<int> modes = findMode(integersEntered, totalIntegers);
//    
//// Display results.
//    
//    cout << "The mode(s) are:" << endl;
//    for (int i = 0; i < modes.size(); i++)
//    
//    {
//        cout << modes[i] << "  ";
//    }
//    
//    cout << endl;
//    
//    return 0;
//}
//
//
