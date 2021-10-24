#include "PushdownAutomaton.h"
#include <iostream>
#include "StringHelper.h"

bool PushdownAutomaton::checkStr(std::string str)
{
    m_pushdownStack.push("h0");
    m_pushdownStack.push("E");

    std::stack<std::string> input;
    for (int i = str.size()-1; i >= 0; i--)
    {
        input.push(std::string(1, str[i]));
    }

    ConfigCommand tmp;

    while (1)
    {
        tmp = getCommandByPushdownVal(m_pushdownStack.top());
        m_pushdownStack.pop();

        if (tmp.getType() == 2)
        {
            if (input.top() == tmp.getInputVal())
            {
                input.pop();
            }
            else
            {
                return false;
            }
        }
        else if (tmp.getType() == 1)
        {
            for (int i = 0; i < tmp.getResultStates().size(); i++)
            {
                std::vector<std::string> additionChainConfiguration;
                std::stack<std::string> pushdownStack = m_pushdownStack;
                for (int j = 0; j < tmp.getResultStates()[i].size(); j++)
                {
                    pushdownStack.push(std::string(1,tmp.getResultStates()[i][j]));
                }
                m_recursionCount++;
                if (recursiveCheck(input, pushdownStack, additionChainConfiguration))
                {
                    m_chainConfigurations.insert(m_chainConfigurations.end(), additionChainConfiguration.begin(),
                        additionChainConfiguration.end());
                    return true;
                }
            }
        }
        else if(tmp.getType() == 3)
        {
            return (input.size() == 0) ? true : false;
        }
        
        m_chainConfigurations.push_back("('S0', '" + stackToString(input) + "', '" + stackToString(m_pushdownStack) + "')");
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
        if (m_recursionCount > 5000)
        {
            return false;
        }

        tmp = getCommandByPushdownVal(pushdownStack.top());
        if (tmp.getType() == 0)
        {
            return false;
        }

        pushdownStack.pop();

        if (tmp.getType() == 2)
        {
            if (input.top() == tmp.getInputVal())
            {
                input.pop();
            }
            else
            {
                return false;
            }
        }
        else if (tmp.getType() == 1)
        {
            for (int i = 0; i < tmp.getResultStates().size(); i++)
            {
                std::vector<std::string> additionChainConfiguration;
                std::stack<std::string> tmpPushdownStack = pushdownStack;
                for (int j = 0; j < tmp.getResultStates()[i].size(); j++)
                {
                    tmpPushdownStack.push(std::string(1, tmp.getResultStates()[i][j]));
                }
                m_recursionCount++;
                if (recursiveCheck(input, tmpPushdownStack, additionChainConfiguration))
                {
                    chainConfigurations.insert(chainConfigurations.end(), additionChainConfiguration.begin(),
                        additionChainConfiguration.end());
                    return true;
                }
            }
        }
        else if (tmp.getType() == 3)
        {
            return (input.size() == 0) ? true : false;
        }

        chainConfigurations.push_back("('S0', '" + stackToString(input) + "', '" + stackToString(pushdownStack) + "')");
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

