#pragma once
#include <string>
#include <vector>

class Interpreter
{
public:
    Interpreter(): m_index(0) {};
    void interpret(std::vector<std::string> strTokens);
private:
    std::vector<std::string> m_strTokens;
    int m_index;
    std::vector<std::pair<std::string, int>> m_variables;
    int getValueByName(std::string name);
    bool nextToken();
    bool doAssign();
    int solveExpression(std::string str);
    int trySwitchNameToValue(std::string& str, std::string& buf);
};
