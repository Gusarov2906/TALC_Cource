#pragma once
#include <string>
#include <vector>

class Interpreter
{
public:
    Interpreter(): m_index(0) {};
    Interpreter(std::vector<std::pair<std::string, int>> variables) : m_index(0), m_variables(variables) {};
    void interpret(std::vector<std::string> strTokens);
private:
    std::vector<std::string> m_strTokens;
    int m_index;
    std::vector<std::pair<std::string, int>> m_variables;
    int getValueByName(std::string name);
    bool nextToken();

    bool doAssign();
    bool doScan();
    bool doPrint();
    bool doFor();
    bool doIf();
    bool doElse();
    bool skip();

    int solveExpression(std::string str);
    int trySwitchNameToValue(std::string& str, std::string& buf);
    bool getNumericParam(int& param);
    void addToVariables(std::string name, int res);
};
