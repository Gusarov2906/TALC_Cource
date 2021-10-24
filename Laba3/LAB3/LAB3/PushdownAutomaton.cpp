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
            for (int i = 0; i < tmp.getResultStates()[0].size(); i++)
            {
                m_pushdownStack.push(std::string(1,tmp.getResultStates()[0][i]));
            }
        }
        else if(tmp.getType() == 3)
        {
            return (input.size() == 0) ? true : false;
        }
        
        std::cout << "('S0', '" << stackToString(input) << "', '" << stackToString(m_pushdownStack) << "')" << std::endl;
    }

    return false;
}

const ConfigCommand& PushdownAutomaton::getCommandByPushdownVal(std::string pushdownVal)
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

