#pragma once
#include <string>
#include <sstream>
#include <vector>


static class StringHelper
{
public:
    static std::string join(const std::vector<std::string>& vec, const char* delim);
    static std::vector<std::string> split(std::string strToSplit, char delimeter);
private:
    StringHelper() {}
};

