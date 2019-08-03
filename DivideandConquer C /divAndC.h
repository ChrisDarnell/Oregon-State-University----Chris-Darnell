#include <vector>
#include <algorithm>
#include <limits.h>

struct maxSub
{
    int sum;
    int start;
    int end;
};

int divAndC(std::vector <int> vec);
int divAndC(std::vector <int> vec, int &start, int &end);
int findMax(std::vector <int> vec, int start, int end);
maxSub findMaxSub(std::vector <int> vec, int start, int end);
maxSub maxCrossingSub(std::vector<int> vec, int crossStart, int crossEnd, int mid);
int maxCrossing(std::vector<int> vec, int crossStart, int crossEndm, int mid);
