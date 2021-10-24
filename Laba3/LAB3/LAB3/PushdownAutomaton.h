#pragma once
#include "ConfigCommand.h"
#include <stack>

class PushdownAutomaton
{
public:
    PushdownAutomaton(const std::string& inputStr, 
        const std::vector<ConfigCommand>& commands) 
        : m_inputStr(inputStr), m_commands(commands)
        , m_recursionCount(0) {};

    bool checkStr(std::string str);

    std::vector<std::string> getChainConfigurations();

private:
    std::stack<std::string> m_pushdownStack;
    std::vector<std::string> m_chainConfigurations;
    int m_recursionCount;
    const std::string m_inputStr;
    const std::vector<ConfigCommand>& m_commands;
   
    const ConfigCommand getCommandByPushdownVal(std::string pushdownVal);

    bool recursiveCheck(std::stack<std::string> input, 
        std::stack<std::string> pushdownStack,
        std::vector<std::string>& chainConfiguration);

    std::string stackToString(std::stack<std::string> st);

};
