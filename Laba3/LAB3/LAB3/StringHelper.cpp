#include "StringHelper.h"

std::string StringHelper::join(const std::vector<std::string>& vec, const char* delim)
{
    std::stringstream ss;
    std::string res;
    copy(vec.begin(), vec.end(), std::ostream_iterator<std::string>(ss, delim));
    res = ss.str();
    res.resize(res.size() - 1);
    return res;
}

std::vector<std::string> StringHelper::split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
    {
        splittedStrings.push_back(item);
    }
    return splittedStrings;
}
