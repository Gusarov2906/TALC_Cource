#pragma once
#include "ConfigCommand.h"
#include <stack>

class PushdownAutomaton
{
public:
    PushdownAutomaton(const std::string& inputStr, const std::vector<ConfigCommand>& commands) 
        : m_inputStr(inputStr), m_commands(commands) {};

private:
    std::stack<std::string> m_pushdownStack;
    const std::string m_inputStr;
    const std::vector<ConfigCommand>& m_commands;

};

