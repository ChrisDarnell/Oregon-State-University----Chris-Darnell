#include "timingRoutines.h"
#include <ctime>
#include <iostream>
#include <time.h>
#include <stdlib.h>



std::vector<int>* Helper::GenRandNums(int numberOfInts)
{
    srand(time(NULL));
    std::vector<int>* randNums = new std::vector<int>();
    
    for(int i = 0; i < numberOfInts; i++)
    {
        // generate numbers -100 - 100
        int num = (rand() % 201) - 100;
        randNums->push_back(num);
    }
    
    return randNums;
}

void Helper::ClockMSSFunction(int (*timeFun)(std::vector<int>), std::vector<int>* numbers)
{
    std::clock_t start = std::clock();
    int result =timeFun(*numbers);
    double total = (std::clock() - start) / (double) CLOCKS_PER_SEC;
    std::cout << "N: " << numbers->size() << " Result: " << result << " CPU Seconds: " << total << '\n';
    
}
