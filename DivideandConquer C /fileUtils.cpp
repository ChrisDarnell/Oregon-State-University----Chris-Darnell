#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>
#include <iostream>

#include "fileUtils.h"

std::vector<std::string>* Helper::readLinesFromFile(std::ifstream& inFromFile)
{
    std::vector<std::string>* returnStrings = new std::vector<std::string>();
    
    std::string curLine;
    while(std::getline(inFromFile, curLine))
    {
        returnStrings->push_back(curLine);
    }
    
    return returnStrings;
    
}

void Helper::stripBrackets(std::string &stripString)
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

std::vector<int>* Helper::csvToInt(std::string &convertString)
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

std::vector<std::vector<int>*>* Helper::processMSSFile(std::ifstream &inStream)
{
    std::vector<std::vector<int>*>* convertedLines = new std::vector<std::vector<int>*>();
    std::vector<std::string>* MSSFileLines = Helper::readLinesFromFile(inStream);
    
    for(uint i = 0; i < MSSFileLines->size(); i++)
    {
        Helper::stripBrackets(MSSFileLines->at(i));
        convertedLines->push_back(Helper::csvToInt(MSSFileLines->at(i)));
    }
    delete MSSFileLines;
    return convertedLines;
}

void Helper::WriteResultsToFile(std::ofstream &outStream, std::vector<int>& results, int start, int end, int total)
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
