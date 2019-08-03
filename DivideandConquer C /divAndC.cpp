#include "divAndC.h"

int divAndC(std::vector <int> vec)
{
    int start = 0;
    int end = vec.size() - 1;
    return findMax(vec, start, end);
}

int divAndC(std::vector <int> vec, int &start, int &end)
{
    start = 0;
    end = vec.size() - 1;
    maxSub ms;
    ms = findMaxSub(vec, start, end);
    start = ms.start;
    end = ms.end;
    return ms.sum;
}

int findMax(std::vector <int> vec, int start, int end)
{
    if (start == end)
    {
        return vec[start];
    }
    
    int mid = (start + end) / 2;
    
    return std::max(std::max(findMax(vec, start, mid), findMax(vec, mid + 1, end)), maxCrossing(vec, start, end, mid));
    
}

maxSub findMaxSub(std::vector <int> vec, int start, int end)
{
    maxSub temp;
    
    if (start == end)
    {
        temp.start = start;
        temp.end = end;
        temp.sum = vec[start];
        return temp;
    }
    
    int mid = (start + end) / 2;
    
    maxSub leftSub;
    leftSub = findMaxSub(vec, start, mid);
    maxSub rightSub;
    rightSub = findMaxSub(vec, mid + 1, end);
    maxSub crossSub;
    crossSub = maxCrossingSub(vec, start, end, mid);
    
    if (leftSub.sum >= rightSub.sum && leftSub.sum >= crossSub.sum)
    {
        return leftSub;
    }
    else if (rightSub.sum >= leftSub.sum && rightSub.sum >= crossSub.sum)
    {
        return rightSub;
    }
    else
    {
        return crossSub;
    }
    
}

int maxCrossing(std::vector<int> vec, int crossStart, int crossEnd, int mid)
{
    //find max sum left half
    int leftMax = INT_MIN;
    int sum = 0;
    for (int i = mid; i >= crossStart; i--)
    {
        sum += vec[i];
        if (sum > leftMax)
        {
            leftMax = sum;
        }
    }
    
    //find max sum right half
    int rightMax = INT_MIN;
    sum = 0;
    for (int j = mid + 1; j <= crossEnd; j++)
    {
        sum += vec[j];
        if (sum > rightMax)
        {
            rightMax = sum;
        }
    }
    
    return leftMax + rightMax;
}

maxSub maxCrossingSub(std::vector<int> vec, int crossStart, int crossEnd, int mid)
{
    //find max sum left half
    maxSub temp;
    int leftMax = INT_MIN;
    int leftStart, rightEnd;
    int sum = 0;
    for (int i = mid; i >= crossStart; i--)
    {
        sum += vec[i];
        if (sum > leftMax)
        {
            leftMax = sum;
            leftStart = i;
        }
    }
    
    //find max sum right half
    int rightMax = INT_MIN;
    sum = 0;
    for (int j = mid + 1; j <= crossEnd; j++)
    {
        sum += vec[j];
        if (sum > rightMax)
        {
            rightMax = sum;
            rightEnd = j;
        }
    }
    
    temp.sum = leftMax + rightMax;
    temp.start = leftStart;
    temp.end = rightEnd;
    
    return temp;
    
}
