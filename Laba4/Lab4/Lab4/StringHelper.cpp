#include "StringHelper.h"

const char StringHelper::ql[] = { char(-30), char(-128), char(-103) };
const char StringHelper::qr[] = { char(-30), char(-128), char(-104) };

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

std::string StringHelper::replaceFirstOccurrence(
    std::string& s,
    const std::string& toReplace,
    const std::string& replaceWith)
{
    std::size_t pos = s.find(toReplace);
    if (pos == std::string::npos) return s;
    return s.replace(pos, toReplace.length(), replaceWith);
}

std::vector<std::string> StringHelper::tokenize(std::string s, std::string del)
{
    std::vector<std::string> res;
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        std::string tmp = s.substr(start, end - start);
        if(tmp != "")
            res.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    std::string tmp = s.substr(start, end - start);
    if (tmp != "")
        res.push_back(s.substr(start, end - start));
    return res;
}
