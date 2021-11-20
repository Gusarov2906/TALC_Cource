#include "PushdownAutomaton.h"
#include <iostream>
#include "StringHelper.h"
#include <algorithm>
#include <regex>

bool PushdownAutomaton::checkStr(std::string str)
{
    m_pushdownStack.push("h0");
    m_pushdownStack.push("<program>");
    m_errorsCount = 0;

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

int PushdownAutomaton::getErrorCount()
{
    return m_errorsCount;
}

std::vector<std::string> PushdownAutomaton::getChainConfigurations()
{
    return m_chainConfigurations;
}

bool PushdownAutomaton::isSyncSym(std::string sym)
{
    std::vector<std::string> syncSyms = { "(", ")", "{", "}", ";"};
    for (std::string syncSym : syncSyms)
    {
        if (syncSym == sym)
        {
            return true;
        }
    }
    return false;
}

bool PushdownAutomaton::isNonTerminalSym(std::string sym)
{
    for (std::string nonTerm : m_nonTerminals)
    {
        if (nonTerm == sym)
        {
            return true;
        }
    }
    return false;
}

bool PushdownAutomaton::recursiveCheck(std::stack<std::string> input, std::stack<std::string> pushdownStack, std::vector<std::string>& chainConfigurations)
{
    ConfigCommand tmp;
    const std::regex regexTerminals(R"(([‘][A-Za-z_(){}0-9<>=!;]+[’])(.|$))");
    std::vector<std::string> syncSyms = { "(", ")", "{", "}", ";"};

    std::smatch matchTerminal;
    while (1)
    {
        if (m_recursionCount > 200)
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

        if (tmp.getType() == 2)
        {
            if (input.size() > 0 && pushdownStack.size() > 0)
            {
                int size = tmp.getInputVal().size();
                int index = 0;
                int counter = 0;
                while (size-- != 0 && input.size() > 0)
                {
                    if (input.top().c_str()[0] == tmp.getInputVal()[index])
                    {
                        counter++;
                        input.pop();
                    }
                    else
                    {
                        if (m_recursionCount != 0)
                        {
                            return false;
                        }
                    }
                    index++;
                }
                pushdownStack.pop();
                if (counter != tmp.getInputVal().size())
                {
                    if (!test(tmp, input, pushdownStack))
                    {
                        return false;
                    }
                }
            }
            else
            {
                return false;
            }
        }
        else if (tmp.getType() == 1)
        {
            pushdownStack.pop();
            bool isAllTerminals = true;
            if (tmp.getResultStates().size() > 0)
            {
                for (int i = 0; i <static_cast<int>(tmp.getResultStates().size()); i++)
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
                        if (isNonTerminalSym(str))
                        {
                            isAllTerminals = false;
                        }
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
            }
            if (m_recursionCount == 0)
            {
                if (!test(tmp, input, pushdownStack))
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else if (tmp.getType() == 3)
        {
            pushdownStack.pop();
            return (input.size() == 0) ? true : false;
        }

    }
    return false;
}

bool PushdownAutomaton::test(ConfigCommand& tmp, std::stack<std::string>& input, std::stack<std::string>& pushdownStack)
{
    if (m_recursionCount == 0)
    {
        //skip input syms to sync term
        while (input.size() > 0)
        {
            if (isSyncSym(input.top()))
            {
                m_syncInput = input.top();
                break;
            }
            else
            {
                input.pop();
            }
        }

        if (input.size() == 0)
        {
            std::cout << "Syntax error " << m_errorsCount << std::endl;
            m_errorsCount++;
            return false;
        }

        m_recursionCountSkip = 0;
        auto tmpPushdownStack = pushdownStack;
        tmpPushdownStack.push(tmp.getPushdownVal());
        if (isSyncSym(tmpPushdownStack.top()))
        {
            std::cout << "Syntax error " << m_errorsCount << std::endl;
            m_errorsCount++;
        }
        else
        {
            std::cout << "Lexical error " << m_errorsCount << std::endl;
            m_errorsCount++;
        }

        if (skipAutomaton(tmpPushdownStack))
        {
            pushdownStack = tmpPushdownStack;
            return true;
        }
        else
        {
            std::cout << "Undefined behavior" << std::endl;
            return false;
        }
    }
}

bool PushdownAutomaton::skipAutomaton(std::stack<std::string>& pushdownStack)
{
    while (1)
    {
        std::stack<std::string> res;
        auto tmp = getCommandByPushdownVal(pushdownStack.top());
        //std::cout << tmp.getInputVal() << "  " << tmp.getPushdownVal() << " " << m_recursionCountSkip << std::endl;
        if (m_recursionCountSkip > 200)
        {
            return false;
        }
        if (tmp.getType() == 0)
        {
            return false;
        }
        if (tmp.getType() == 2)
        {
            if (pushdownStack.size() > 0)
            {
                if (tmp.getInputVal() == m_syncInput)
                {
                    return true;
                }
                else
                {
                    pushdownStack.pop();
                }
            }
        }
        else if (tmp.getType() == 1)
        {
            pushdownStack.pop();
            if (tmp.getResultStates().size() > 0)
            {
                for (int i = 0; i < static_cast<int>(tmp.getResultStates().size()); i++)
                {
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

                    m_recursionCountSkip++;
                    if (skipAutomaton(tmpPushdownStack))
                    {
                        pushdownStack = tmpPushdownStack;
                        return true;
                    }
                    m_recursionCountSkip--;
                }
            }
        }
        else if (tmp.getType() == 3)
        {
            return false;
        }
    }
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

//if (isAllTerminals)
//{
//    while (input.size() > 0)
//    {
//        if (isSyncSym(input.top()))
//        {
//            std::cout << "Lexical error " << m_errorsCount << std::endl;
//            m_errorsCount++;
//            m_syncInput = input.top();
//            break;
//        }
//        else
//        {
//            input.pop();
//        }
//    }
//    while (pushdownStack.size() > 0)
//    {
//        if (pushdownStack.top() == m_syncInput) //|| isNonTerminalSym(pushdownStack.top()))
//        {
//            break;
//        }
//        else
//        {
//            pushdownStack.pop();
//        }
//    }
//    if (pushdownStack.size() == 0)
//    {
//        if (m_errorsCount == 0)
//        {
//            m_errorsCount++;
//        }
//        std::cout << "Semantic error " << m_errorsCount << std::endl;
//        return false;
//    }
//}
//else
//{
//    m_errorsCount++;
//    std::cout << "Syntax error " << m_errorsCount << std::endl;
//    //return false;
//}