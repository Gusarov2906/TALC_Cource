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
            toStop = doFor();
            break;
        case CommandType::If:
            toStop = doIf();
            break;
        case CommandType::Print:
            toStop = doPrint();
            break;
        case CommandType::Else:
            toStop = skip();
            break;
        case CommandType::Scan:
            toStop = doScan();
            break;
        case CommandType::None:
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

bool Interpreter::doFor()
{
    if (!nextToken())
    {
        return true;
    }
    std::string name;
    std::string strValFrom;
    std::string strValTo;

    while (m_strTokens[m_index] != "=")
    {
        if (m_strTokens[m_index] != " ")
        {
            name += m_strTokens[m_index];
        }
        if (!nextToken())
        {
            return true;
        }
    }
    if (!nextToken())
    {
        return true;
    }

    while (m_strTokens[m_index] != "to")
    {
        if (m_strTokens[m_index] != " ")
        {
            strValFrom += m_strTokens[m_index];
        }
        if (!nextToken())
        {
            return true;
        }
    }
    if (!nextToken())
    {
        return true;
    }
    addToVariables(name, solveExpression(strValFrom));

    //int from = solveExpression(strValFrom);

    while (m_strTokens[m_index] != "{")
    {
        if (m_strTokens[m_index] != " ")
        {
            strValTo += m_strTokens[m_index];
        }
        if (!nextToken())
        {
            return true;
        }
    }
    if (!nextToken())
    {
        return true;
    }

    std::vector<std::string> tokens;
    while (m_strTokens[m_index] != "}")
    {
        if (m_strTokens[m_index] != " ")
        {
            tokens.push_back(m_strTokens[m_index]);
        }
        if (!nextToken())
        {
            return true;
        }
    }

    for (int i = solveExpression(strValFrom); i < solveExpression(strValTo); i++)
    {
        //std::cout << i;
        addToVariables(name, i);
        Interpreter interpreter(m_variables);
        interpreter.interpret(tokens);
    }
    if (!nextToken())
    {
        return true;
    }

    return false;
}

bool Interpreter::doIf()
{
    if (!nextToken())
    {
        return true;
    }
    std::string leftPart;
    std::string sign;

    while (m_strTokens[m_index] != "==" && m_strTokens[m_index] != "!=" &&
           m_strTokens[m_index] != ">" && m_strTokens[m_index] != "<")
    {
        if (m_strTokens[m_index] != " ")
        {
            leftPart += m_strTokens[m_index];
        }
        if (!nextToken())
        {
            return true;
        }
    }

    sign = m_strTokens[m_index];
    if (!nextToken())
    {
        return true;
    }

    std::string rightPart;

    while (m_strTokens[m_index] != "{")
    {
        if (m_strTokens[m_index] != " ")
        {
            rightPart += m_strTokens[m_index];
        }
        if (!nextToken())
        {
            return true;
        }
    }
    if (!nextToken())
    {
        return true;
    }

    std::vector<std::string> tokens;
    while (m_strTokens[m_index] != "}")
    {
        if (m_strTokens[m_index] != " ")
        {
            tokens.push_back(m_strTokens[m_index]);
        }
        if (!nextToken())
        {
            return true;
        }
    }

    while (m_strTokens[m_index] != "else")
    {
        if (!nextToken())
        {
            return true;
        }
    }


    if (sign == "==")
    {
        if (solveExpression(leftPart) == solveExpression(rightPart))
        {
            Interpreter interpreter(m_variables);
            interpreter.interpret(tokens);
        }
        else
        {
            if (m_strTokens[m_index] == "else")
            {
                return doElse();
            }
        }
    }
    else if (sign == "!=")
    {
        if (solveExpression(leftPart) != solveExpression(rightPart))
        {
            Interpreter interpreter(m_variables);
            interpreter.interpret(tokens);
        }
        else
        {
            if (m_strTokens[m_index] == "else")
            {
                return doElse();
            }
        }
    }
    else if (sign == ">")
    {
        if (solveExpression(leftPart) > solveExpression(rightPart))
        {
            Interpreter interpreter(m_variables);
            interpreter.interpret(tokens);
        }
        else
        {
            if (m_strTokens[m_index] == "else")
            {
                return doElse();
            }
        }
    }
    else if (sign == "<")
    {
        if (solveExpression(leftPart) < solveExpression(rightPart))
        {
            Interpreter interpreter(m_variables);
            interpreter.interpret(tokens);
        }
        else
        {
            if (!nextToken())
            {
                return true;
            }
            if (m_strTokens[m_index] == "else")
            {
                return doElse();
            }
        }
    }

    if (!nextToken())
    {
        return true;
    }
    return false;
}

bool Interpreter::doElse()
{
    if (!nextToken())
    {
        return true;
    }
    while (m_strTokens[m_index] != "{")
    {
        if (!nextToken())
        {
            return true;
        }
    }
    if (!nextToken())
    {
        return true;
    }

    std::vector<std::string> tokens;
    while (m_strTokens[m_index] != "}")
    {
        if (m_strTokens[m_index] != " ")
        {
            tokens.push_back(m_strTokens[m_index]);
        }
        if (!nextToken())
        {
            return true;
        }
    }

    Interpreter interpreter(m_variables);
    interpreter.interpret(tokens);
    if (!nextToken())
    {
        return true;
    }
    return false;
}

bool Interpreter::skip()
{
    while (m_strTokens[m_index] != "}")
    {
        if (!nextToken())
        {
            return true;
        }
    }
    if (!nextToken())
    {
        return true;
    }
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
        std::cout << res << std::endl;
    }
    else
    {
        std::cout << strVal << std::endl;
    }
    return false;
}

bool Interpreter::doAssign()
{
    std::string name;
    std::string strVal;
    bool valueCollecting = false;
    if (m_strTokens[m_index] == " ")
    {
        if (!nextToken())
        {
            return true;
        }
        return false;
    }
    //std::cout << "Assign" << std::endl;
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
    //std::cout << variable.first << " " << variable.second << std::endl;
}
