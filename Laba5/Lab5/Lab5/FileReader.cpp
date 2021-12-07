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
    if (file.fail())
    {
        throw std::string("File opening error!");
    }
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
            throw std::string("Input rules is not");
        }
        m_rawRules.push_back(line);
    }
    m_configCommands.push_back(ConfigCommand("", "h0", " "));
    m_configCommands.push_back(ConfigCommand(" ", " ", " "));

    return validity;
}

std::vector<ConfigCommand> FileReader::getCommands()
{
    return m_configCommands;
}

std::vector<std::string> FileReader::getTerminals()
{
    return m_terminals;
}

std::vector<std::string> FileReader::getNonTerminals()
{
    return m_nonTerminals;
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
    const std::regex regexStr(R"((<[A-Za-z_]*>):(.*))");
    const std::regex regexTerminals(R"(([‘][^‘’|]+[’])(.|$))");

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
            if (!(std::find(m_nonTerminals.begin(), m_nonTerminals.end(), matchStr.str(1)) != m_nonTerminals.end()))
            {
                m_nonTerminals.push_back(matchStr.str(1));
            }
            rightPart = matchStr.str(2);
            while (true)
            {
                std::string tmp = rightPart;
                StringHelper::replaceFirstOccurrence(rightPart, "><", ">"+std::string(StringHelper::qr) + std::string(StringHelper::ql) +"<");
                if (rightPart == tmp)
                    break;
            }

            std::vector<std::string> parts = StringHelper::split(rightPart, '|');

            //std::for_each(parts.begin(), parts.end(), [&parts](std::string& str)
            //    {
            //        //std::reverse(str.begin(), str.end());
            //        //while (true)
            //        //{
            //        //    std::string tmp = str;
            //        //    StringHelper::replaceFirstOccurrence(str, "'", "");
            //        //    if (str == tmp)
            //        //        break;
            //        //}
            //    });

            while (true)
            {
                std::string tmp = rightPart;
                StringHelper::replaceFirstOccurrence(rightPart, StringHelper::qr, "‘");
                StringHelper::replaceFirstOccurrence(rightPart, StringHelper::ql, "’");
                if (rightPart == tmp)
                    break;
            }

            //std::string newRightPart = "";
            m_configCommands.push_back(ConfigCommand("", matchStr.str(1), parts));
            //for (std::string str1 : StringHelper::tokenize(rightPart, StringHelper::qr))
            //{
            //    for (std::string str2 : StringHelper::tokenize(str1, StringHelper::ql))
            //    {
            //        newRightPart += str2;
            //    }
            //}

            std::string::const_iterator searchStart(rightPart.cbegin());
            while (std::regex_search(searchStart, rightPart.cend(), matchTerminal, regexTerminals))
            {
                if (!(std::find(m_terminals.begin(), m_terminals.end(), matchTerminal.str(1)) != m_terminals.end())) 
                {
                    std::string term = matchTerminal.str(1);
                    term.resize(term.size() - 1);
                    term = term.substr(1, term.size() - 1);
                    m_terminals.push_back(term);
                    m_configCommands.push_back(ConfigCommand(term, term, " "));
                }
                searchStart = matchTerminal.suffix().first;
            }
        }
    }
    return true;
}
