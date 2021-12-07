#pragma once
#include <string>
#include <vector>
#include "ConfigCommand.h"

class FileReader
{
public:
    FileReader();
    bool getData(std::string filename);
    std::vector<ConfigCommand> getCommands();
    std::vector<std::string> getTerminals();
    std::vector<std::string> getNonTerminals();
    void printRawRules();
    void printCommands();
    void printInputAlphabet();
    void printNonterminalsAlphabet();
    void printAlphabet();
    void printCommandsChain();

private:
    bool isValid(std::string str);
    std::vector<std::string> m_rawRules;
    std::vector<std::string> m_terminals;
    std::vector<std::string> m_nonTerminals;
    std::vector<ConfigCommand> m_configCommands;
};

