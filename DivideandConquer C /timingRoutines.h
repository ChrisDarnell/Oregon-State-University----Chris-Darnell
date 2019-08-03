#pragma once
#include <vector>

namespace Helper
{
    std::vector<int>* GenRandNums(int numberOfInts);
    void ClockMSSFunction(int (*timeFun)(std::vector<int>), std::vector<int>* numbers);
}
