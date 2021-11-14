#include "PushdownAutomaton.h"
#include <iostream>
#include "StringHelper.h"
#include <algorithm>

bool PushdownAutomaton::checkStr(std::string str)
{
    m_pushdownStack.push("h0");
    m_pushdownStack.push("<program>");

    std::stack<std::string> input;
    for (int i = str.size()-1; i >= 0; i--)
    {
        input.push(std::string(1, str[i]));
    }

    ConfigCommand tmp;
    std::vector<std::string> additionChainConfiguration;
    if (recursiveCheck(input, m_pushdownStack, additionChainConfiguration))
    {
        m_chainConfigurations.insert(m_chainConfigurations.end(), additionChainConfiguration.begin(),
            additionChainConfiguration.end());
        return true;
    }
    return false;
}

std::vector<std::string> PushdownAutomaton::getChainConfigurations()
{
    return m_chainConfigurations;
}

bool PushdownAutomaton::recursiveCheck(std::stack<std::string> input, std::stack<std::string> pushdownStack, std::vector<std::string>& chainConfigurations)
{
    ConfigCommand tmp;

    while (1)
    {
        if (m_recursionCount > 500)
        {
            return false;
        }
        //std::cout << "('S0', '" + stackToString(input) + "', '" + stackToString(pushdownStack) + "')" << m_recursionCount << std::endl;
        chainConfigurations.push_back("('S0', '" + stackToString(input) + "', '" + stackToString(pushdownStack) + "')");
        tmp = getCommandByPushdownVal(pushdownStack.top());
        if (tmp.getType() == 0)
        {
            return false;
        }
        else if (tmp.getType() == 1)
        {
            bool a = true;
        }

        pushdownStack.pop();

        if (tmp.getType() == 2)
        {
            if (input.size() > 0)
            {
                int size = tmp.getInputVal().size();
                int index = 0;
                while (size-- != 0)
                {
                    if (input.top().c_str()[0] == tmp.getInputVal()[index])
                    {
                        input.pop();
                    }
                    else
                    {
                        return false;
                    }
                    index++;
                }
            }
            else
            {
                return false;
            }
        }
        else if (tmp.getType() == 1)
        {
            if (tmp.getResultStates().size() > 1)
            {
                for (int i = 0; i < tmp.getResultStates().size(); i++)
                {
                    std::vector<std::string> additionChainConfiguration;
                    std::stack<std::string> tmpPushdownStack = pushdownStack;
                    std::vector<std::string> pushdownVector;
                    for (std::string str1 : StringHelper::tokenize(std::string(tmp.getResultStates()[i]), StringHelper::qr))
                    {
                        for (std::string str2 : StringHelper::tokenize(str1, StringHelper::ql))
                        {
                            pushdownVector.push_back(str2);
                        }
                    }
                    std::vector<std::string> newPushdownVector;
                    for (int i = pushdownVector.size() - 1; i >= 0; i--)
                    {
                        if (pushdownVector[i] != "")
                        {
                            newPushdownVector.push_back(pushdownVector[i]);
                        }
                    }
                    for (std::string str : newPushdownVector)
                    {
                        tmpPushdownStack.push(str);
                    }

                    m_recursionCount++;
                    if (recursiveCheck(input, tmpPushdownStack, additionChainConfiguration))
                    {
                        chainConfigurations.insert(chainConfigurations.end(), additionChainConfiguration.begin(),
                            additionChainConfiguration.end());
                        return true;
                    }
                    m_recursionCount--;
                }
                return false;
            }
            else
            {
                std::vector<std::string> pushdownVector;
                for (std::string str1 : StringHelper::tokenize(std::string(tmp.getResultStates()[0]), StringHelper::qr))
                {
                    for (std::string str2 : StringHelper::tokenize(str1, StringHelper::ql))
                    {
                        pushdownVector.push_back(str2);
                    }
                }
                std::vector<std::string> newPushdownVector;
                for (int i = pushdownVector.size() - 1; i >= 0; i--)
                {
                    if (pushdownVector[i] != "")
                    {
                        newPushdownVector.push_back(pushdownVector[i]);
                    }
                }
                for (std::string str : newPushdownVector)
                {
                    pushdownStack.push(str);
                }
            }
        }
        else if (tmp.getType() == 3)
        {
            return (input.size() == 0) ? true : false;
        }

    }
    return false;
}

const ConfigCommand PushdownAutomaton::getCommandByPushdownVal(std::string pushdownVal)
{
    for (const ConfigCommand& command : m_commands)
    {
        if (command.getPushdownVal() == pushdownVal)
        {
            return command;
        }
    }
    return ConfigCommand();
}

std::string PushdownAutomaton::stackToString(std::stack<std::string> st)
{
    std::string res = "";
    while(!st.empty())
    {
        res += st.top();
        st.pop();
    }
    return res;
}

