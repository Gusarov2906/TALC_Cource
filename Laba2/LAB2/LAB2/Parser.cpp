#include "Parser.h"
#include <iostream>
#include <fstream>
#include <regex>

Parser::Parser()
{
}

std::vector<State> Parser::getStates(std::string str)
{
    return std::vector<State>();
}

void Parser::parse(std::string filename)
{
    const std::regex r(R"(^q(\d{1,2}),(.{1})=([fq])(\d{1,2})$)");
    std::ifstream file(filename);

    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (std::regex_match(line, r))
            {
                std::cout << line << std::endl;
            }
        }
        file.close();
    }
    else
    {
        std::cout << "File error!" << std::endl;
    }
}

void Parser::sort()
{
}
