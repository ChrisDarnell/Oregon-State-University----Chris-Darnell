#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>

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
std::vector<std::vector<int>*>* processMSSFile(std::ifstream&);
std::vector<std::string>* readLinesFromFile(std::ifstream&);
void stripBrackets(std::string&);
std::vector<int>* csvToInt(std::string&);
void WriteResultsToFile(std::ofstream &outStream, std::vector<int>& results, int start, int end, int total);





std::vector<std::string>* readLinesFromFile(std::ifstream& inFromFile)
{
    std::vector<std::string>* returnStrings = new std::vector<std::string>();
    
    std::string curLine;
    while(std::getline(inFromFile, curLine))
    {
        returnStrings->push_back(curLine);
    }
    
    return returnStrings;
    
}

void stripBrackets(std::string &stripString)
{
    std::string retString;
    
    for(uint i = 0; i < stripString.length(); i++)
    {
        if(stripString.at(i) == '[' || stripString.at(i) == ']')
            continue;
        else
            retString += stripString.at(i);
    }
    
    stripString = retString;
}

std::vector<int>* csvToInt(std::string &convertString)
{
    std::vector<int>* returnVector = new std::vector<int>();
    const char *cstrConvertString = convertString.c_str();
    
    char* tmpString = strtok((char*)cstrConvertString, " ,");
    while(tmpString != NULL)
    {
        int tmp = atoi(tmpString);
        returnVector->push_back(tmp);
        tmpString = strtok(NULL, " ,");
    }
    
    return returnVector;
}

std::vector<std::vector<int>*>* processMSSFile(std::ifstream &inStream)
{
    std::vector<std::vector<int>*>* convertedLines = new std::vector<std::vector<int>*>();
    std::vector<std::string>* MSSFileLines = readLinesFromFile(inStream);
    
    for(uint i = 0; i < MSSFileLines->size(); i++)
    {
        stripBrackets(MSSFileLines->at(i));
        convertedLines->push_back(csvToInt(MSSFileLines->at(i)));
    }
    delete MSSFileLines;
    return convertedLines;
}

void WriteResultsToFile(std::ofstream &outStream, std::vector<int>& results, int start, int end, int total)
{
    outStream << "[";
    for(uint i = 0; i < results.size() - 1; i++)
        outStream << results.at(i) << ", ";
    outStream << results.at(results.size() - 1) << "]" << std::endl;
    
    outStream << "[";
    for(uint i = (unsigned)start; i < (unsigned)end; i++)
        outStream << results.at(i) << ", ";
    outStream << results.at((unsigned)end) << ']' << std::endl;
    outStream << total << std::endl;
}

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


#define RUN_TESTS 0

int main()
{
    std::ifstream input;
    input.open("/Users/chrisdarnell/Desktop/Winter 2017/CS325 - Analysis of Algorithms/DivDriver/DivDriver/MSS_Problems.txt");
    if(!input.is_open())
    {
        input.close();
        std::cout << "MSS_Problems.txt not found in current directory. Now exiting." << std::endl;
        exit(1);
    }
    
    std::ofstream out;
    out.open("/Users/chrisdarnell/Desktop/Winter 2017/CS325 - Analysis of Algorithms/DivDriver/DivDriver/MSS_Results.txt");
    
    std::vector<std::vector<int>*>* processedInts = processMSSFile(input);
    input.close();
    
    
    
    out << "Results of D&C function: \n";
    for(uint i = 0; i < processedInts->size(); i++)
    {
        int start;
        int end;
        int total = divAndC(*(processedInts->at(i)), start, end);
        WriteResultsToFile(out, *processedInts->at(i), start, end, total);
    }
    
    
    //Clean up memory
    for(uint i = 0; i < processedInts->size(); i++)
        delete processedInts->at(i);
    delete processedInts;
    
#if RUN_TESTS == 1
    
    std::cout << "Running timing function for D&C function: " << std::endl;
    int DCValsN[] = {15000, 20000 , 25000, 30000, 35000, 40000, 45000, 50000, 55000, 60000};
    for(int i = 0; i < 10; i++)
    {
        std::vector<int>* randNums = Helper::GenRandNums(DCValsN[i]);
        int(*funPtr1)(std::vector<int>) = &divAndC;
        Helper::ClockMSSFunction(funPtr1, randNums);
        delete randNums;
    }
    
    
#endif
    
    return 0;}
