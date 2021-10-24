#pragma once
#include "ConfigCommand.h"
#include <stack>

class PushdownAutomaton
{
public:
    PushdownAutomaton(const std::string& inputStr, const std::vector<ConfigCommand>& commands) 
        : m_inputStr(inputStr), m_commands(commands) {};
    bool checkStr(std::string str);

private:
    std::stack<std::string> m_pushdownStack;
    std::stack<std::string> m_queueStack;
    const std::string m_inputStr;
    const std::vector<ConfigCommand>& m_commands;
   
    const ConfigCommand& getCommandByPushdownVal(std::string pushdownVal);
    std::string stackToString(std::stack<std::string> st);

};

