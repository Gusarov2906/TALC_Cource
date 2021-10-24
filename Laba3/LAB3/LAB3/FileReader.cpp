#include "FileReader.h"
#include <fstream>
#include <regex>
#include <iostream>
#include <sstream>
#include "StringHelper.h"

FileReader::FileReader()
{
}

bool FileReader::getData(std::string filename)
{
    std::ifstream file(filename);
    std::string line;
    bool validity = true;

    m_terminals.clear();
    m_nonTerminals.clear();
    m_configCommands.clear();
    m_rawRules.clear();

    while (std::getline(file, line))
    {
        if (!isValid(line))
        {
            validity = false;
        }
        m_rawRules.push_back(line);
    }

    return validity;
}

std::vector<ConfigCommand> FileReader::getCommands()
{
    return m_configCommands;
}

void FileReader::printRawRules()
{
    std::cout << "Raw rules: " << std::endl;
    for (std::string str : m_rawRules)
    {
        std::cout << str << std::endl;
    }
    std::cout << std::endl;
}

void FileReader::printCommands()
{
    std::cout << "Commands: " << std::endl;
    for (ConfigCommand command : m_configCommands)
    {
        std::cout << command.toString() << std::endl;
    }
    std::cout << std::endl;
}

void FileReader::printInputAlphabet()
{
    std::cout << "Input alphabet:" << std::endl;
    for (std::string terminal : m_terminals)
    {
        std::cout << terminal << " ";
    }
    std::cout << std::endl << std::endl;
}

void FileReader::printNonterminalsAlphabet()
{
    std::cout << "Nonterminal alphabet:" << std::endl;
    for (std::string nonterminal : m_nonTerminals)
    {
        std::cout << nonterminal << " ";
    }
    std::cout << std::endl << std::endl;
}

void FileReader::printAlphabet()
{
    std::cout << "Common alphabet: " << std::endl;
    for (std::string terminal : m_terminals)
    {
        std::cout << terminal << " ";
    }
    for (std::string nonterminal : m_nonTerminals)
    {
        std::cout << nonterminal << " ";
    }
    std::cout << std::endl << std::endl;
}

void FileReader::printCommandsChain()
{
    std::cout << "Raw rules: " << std::endl;
    for (std::string str : m_rawRules)
    {
        std::cout << str << std::endl;
    }
    std::cout << std::endl;
}

bool FileReader::isValid(std::string str)
{
    const std::regex regexStr(R"(([A-Z])>(.*))");
    const std::regex regexTerminals(R"(([^A-Z|])(.|$))");

    std::smatch matchStr;
    std::smatch matchTerminal;
    std::string rightPart;

    if (!std::regex_match(str, matchStr, regexStr))
    {
        return false;
    }
    else
    {
        if (matchStr.ready())
        {
            m_nonTerminals.push_back(matchStr.str(1));
            rightPart = matchStr.str(2);
            std::vector<std::string> parts = StringHelper::split(rightPart, '|');

            std::for_each(parts.begin(), parts.end(), [&parts](std::string& str)
                {
                    std::reverse(str.begin(), str.end());
                });
            m_configCommands.push_back(ConfigCommand(" ", matchStr.str(1), parts));

            std::string::const_iterator searchStart(rightPart.cbegin());
            while (std::regex_search(searchStart, rightPart.cend(), matchTerminal, regexTerminals))
            {
                m_terminals.push_back(matchTerminal.str(1));
                m_configCommands.push_back(ConfigCommand(matchTerminal.str(1), matchTerminal.str(1), " "));
                searchStart = matchTerminal.suffix().first;
            }
        }
        m_configCommands.push_back(ConfigCommand(" ", "h0" , " "));
    }
    return true;
}
