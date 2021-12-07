#pragma once
#include "ConfigCommand.h"
#include <stack>

class PushdownAutomaton
{
public:
    PushdownAutomaton(const std::string& inputStr, 
        const std::vector<ConfigCommand>& commands, const std::vector<std::string> terminals,
        const std::vector<std::string> nonTerminals)
        : m_inputStr(inputStr), m_commands(commands)
        , m_recursionCount(0), m_terminals(terminals)
        , m_nonTerminals(nonTerminals)
        , m_exitRecursion(false)
        , m_errorsCount(0)
        , m_recursionCountSkip(200){};

    bool checkStr(std::string str);
    int getErrorCount();
    std::vector<std::string> getChainConfigurations();
    std::vector<std::string> getTerminalsInOrder();

private:
    std::stack<std::string> m_pushdownStack;
    std::vector<std::string> m_terminals;
    std::vector<std::string> m_nonTerminals;
    std::vector<std::string> m_chainConfigurations;

    std::vector<std::string> m_terminalsInOrder;
    int m_recursionCount;
    int m_recursionCountSkip;
    const std::string m_inputStr;
    const std::vector<ConfigCommand>& m_commands;

    int m_errorsCount;
    bool m_exitRecursion;
    std::string m_syncInput = "h0";
    bool isSyncSym(std::string sym);
    bool isNonTerminalSym(std::string sym);

    const ConfigCommand getCommandByPushdownVal(std::string pushdownVal);
    bool skipAutomaton(std::stack<std::string>& pushdownStack);
    bool skip(ConfigCommand& tmp, std::stack<std::string>& input, std::stack<std::string>& pushdownStack);

    bool recursiveCheck(std::stack<std::string> input, 
        std::stack<std::string> pushdownStack,
        std::vector<std::string>& chainConfiguration,
        std::vector<std::string>& terminalsInOrder);

    std::string stackToString(std::stack<std::string> st);

};
