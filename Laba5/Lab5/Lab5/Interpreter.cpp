#include "Interpreter.h"
#include "CommandHelper.h"
#include "StringHelper.h"
#include "ConsoleManagerExport.h"
#include <iostream>

bool Interpreter::getNumericParam(int& param)
{
    std::cin >> param;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        std::cout << "Invalid input " << std::endl;
        return false;
    }
    std::cin.clear();
    std::cin.ignore(1024, '\n');
    return true;

}

void Interpreter::interpret(std::vector<std::string> strTokens)
{
    m_strTokens = strTokens;
    m_index = 0;
    bool toStop = false;
    while(!toStop)
    {
        switch (CommandHelper::getCommandType(strTokens[m_index]))
        {
        case CommandType::For:
            std::cout << "For" << std::endl;
            break;
        case CommandType::If:
            std::cout << "If" << std::endl;
            break;
        case CommandType::Else:
            std::cout << "Else" << std::endl;
            break;
        case CommandType::Print:
            std::cout << "Print" << std::endl;
            toStop = doPrint();
            break;
        case CommandType::Scan:
            std::cout << "Scan" << std::endl;
            toStop = doScan();
            break;
        case CommandType::None:
            std::cout << "Assign" << std::endl;
            toStop = doAssign();
            break;

        }
    }
}

int Interpreter::getValueByName(std::string name)
{
    for (std::pair<std::string, int> item : m_variables)
    {
        if (item.first == name)
        {
            return item.second;
        }
    }
    throw std::string("No value by that name!");
    return -1;
}

bool Interpreter::nextToken()
{
    m_index++;
    if (m_index < m_strTokens.size())
    {
        return true;
    }
    return false;
}
bool Interpreter::doScan()
{
    std::string name;
    std::string strVal;
    if (!nextToken())
    {
        return true;
    }
    while (m_strTokens[m_index] != ";")
    {
        if (m_strTokens[m_index] == " ")
        {
            if (!nextToken())
            {
                return true;
            }
        }

        name += m_strTokens[m_index];
        if (!nextToken())
        {
            return true;
        }
    }
    int val;
    while(!getNumericParam(val));
    addToVariables(name, val);
    if (!nextToken())
    {
        return true;
    }
    return false;
}

bool Interpreter::doPrint()
{
    int value;
    std::string name;
    std::string strVal;
    bool valueCollecting = false;
    bool isExpression = true;
    if (!nextToken())
    {
        return true;
    }
    while (m_strTokens[m_index] != ";")
    {
        if (m_strTokens[m_index] == " ")
        {
            if (!nextToken())
            {
                return true;
            }
        }
        if (m_strTokens[m_index] == "\"")
        {
            isExpression = false;
            if (!nextToken())
            {
                return true;
            }
            while (m_strTokens[m_index] != "\"")
            {
                strVal += m_strTokens[m_index];
                if (!nextToken())
                {
                    return true;
                }
            }
            break;
        }
        //value
        strVal += m_strTokens[m_index];
        if (!nextToken())
        {
            return true;
        }
    }
    if (isExpression)
    {
        int res = solveExpression(strVal);
        std::cout << res;
    }
    else
    {
        std::cout << strVal;
    }
}

bool Interpreter::doAssign()
{
    std::string name;
    std::string strVal;
    bool valueCollecting = false;
    while (m_strTokens[m_index] != ";")
    {
        if (m_strTokens[m_index] == " ")
        {
            if (!nextToken())
            {
                return true;
            }
        }

        //value
        if (valueCollecting)
        {
            strVal += m_strTokens[m_index];
        }
        else if (m_strTokens[m_index] == "=")
        {
            valueCollecting = true;
        }
        // name
        else if (!valueCollecting)
        {
            name += m_strTokens[m_index];
        }
        if (!nextToken())
        {
            return true;
        }
    }

    int res = solveExpression(strVal);

    addToVariables(name, res);
    if (!nextToken())
        return true;
    return false;
}

int Interpreter::solveExpression(std::string str)
{
    std::string buf;
    for (int i = 0; i < str.size(); i++)
    {
        if (!isdigit(str[i]) && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' && str[i] != '(' && str[i] != ')' && str[i] != ' ')
        {
            buf += str[i];
        }
        else
        {
            trySwitchNameToValue(str, buf);
        }

    }
    trySwitchNameToValue(str, buf);
    int res = execute(str);
    return res;
}

int Interpreter::trySwitchNameToValue(std::string& str, std::string& buf)
{
    if (buf != "")
    {
        int value = 0;
        try
        {
            value = getValueByName(buf);
            StringHelper::replaceAll(str, buf, std::to_string(value));
            buf = "";
            return value;
        }
        catch (...)
        {
            std::cout << "Variable not defined!" << std::endl;
        }
    }
    buf = "";
}

void Interpreter::addToVariables(std::string name, int res)
{
    std::pair<std::string, int> variable(name, res);
    bool contains = false;
    for (int i = 0; i < m_variables.size(); i++)
    {
        if (m_variables[i].first == name)
        {
            m_variables[i].second = res;
            contains = true;
        }
    }
    if (!contains)
    {
        m_variables.push_back(variable);
    }
    std::cout << variable.first << " " << variable.second << std::endl;
}
