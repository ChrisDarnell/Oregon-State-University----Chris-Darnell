#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>

#include "divAndC.h"
#include "fileUtils.h"
#include "timingRoutines.h"

#define RUN_TESTS 0

int main()
{
    std::ifstream input;
    input.open("/Users/chrisdarnell/Desktop/Winter 2017/CS325 - Analysis of Algorithms/DivideandConquer/DivideandConquer/MSS_Problems.txt");
    if(!input.is_open())
    {
        input.close();
        std::cout << "MSS_Problems.txt not found in current directory. Now exiting." << std::endl;
        exit(1);
    }
    
    std::ofstream out;
    out.open("MSS_Results.txt");
    
    std::vector<std::vector<int>*>* processedInts = Helper::processMSSFile(input);
    input.close();
    
   
    
    out << "Results of D&C function: \n";
    for(uint i = 0; i < processedInts->size(); i++)
    {
        int start;
        int end;
        int total = divAndC(*(processedInts->at(i)), start, end);
        Helper::WriteResultsToFile(out, *processedInts->at(i), start, end, total);
    }
    
    
    //Clean up memory
    for(uint i = 0; i < processedInts->size(); i++)
        delete processedInts->at(i);
    delete processedInts;
    
#if RUN_TESTS == 1
    std::cout << "Running timing function for enumFunction: " << std::endl;
    int enumValsN[] = {1000, 1200, 1400, 1600, 1800, 2000, 2200, 2400, 2600, 2800};
    
    for(int i = 0; i < 10; i++)
    {
        std::vector<int>* randNums = Helper::GenRandNums(enumValsN[i]);
        int(*funPtr1)(std::vector<int>) = &enumFunction;
        Helper::ClockMSSFunction(funPtr1, randNums);
        delete randNums;
    }
    
    std::cout << "Running timing function for betterEnumFunction: " << std::endl;
    int betterEnumValsN[] = {15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000, 55000, 60000};
    
    for(int i = 0; i < 10; i++)
    {
        std::vector<int>* randNums = Helper::GenRandNums(betterEnumValsN[i]);
        int(*funPtr1)(std::vector<int>) = &betterEnumFunction;
        Helper::ClockMSSFunction(funPtr1, randNums);
        delete randNums;
    }
    
    
    std::cout << "Running timing function for D&C function: " << std::endl;
    int DCValsN[] = {15000, 20000 , 25000, 30000, 35000, 40000, 45000, 50000, 55000, 60000};
    for(int i = 0; i < 10; i++)
    {
        std::vector<int>* randNums = Helper::GenRandNums(DCValsN[i]);
        int(*funPtr1)(std::vector<int>) = &divAndC;
        Helper::ClockMSSFunction(funPtr1, randNums);
        delete randNums;
    }
    
    
    std::cout << "Running timing function for linear: " << std::endl;
    int linearN[] = {10000000, 20000000, 30000000, 40000000, 50000000, 60000000, 70000000, 80000000, 90000000, 100000000};
    
    for(int i = 0; i < 10; i++)
    {
        std::vector<int>* randNums = Helper::GenRandNums(linearN[i]);
        int(*funPtr1)(std::vector<int>) = &linear;
        Helper::ClockMSSFunction(funPtr1, randNums);
        delete randNums;
    }
    
#endif
    
    return 0;
}
