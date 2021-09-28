#include "Parser.h"
#include <iostream>
#include <fstream>
#include <regex>

Parser::Parser()
{
}

void Parser::getTransition(std::string str)
{
    const std::regex r(R"((^q\d{1,2}),(.{1})=([fq]\d{1,2})$)");
    std::smatch m;
    if (std::regex_match(str, m, r))
    {
        if (m.ready())
        {
            states.try_emplace(m.str(1), new State(m.str(1)));
            states.try_emplace(m.str(3), new State(m.str(3)));
            states[m.str(1)]->addTransition(Transition(states[m.str(1)], states[m.str(3)], m.str(2)[0]));
        }
    }
  
}

std::map<std::string, State*> Parser::parse(std::string filename)
{
    states.clear();
    const std::regex r(R"(^q(\d{1,2}),(.{1})=([fq])(\d{1,2})$)");
    std::ifstream file(filename);

    if (file.is_open())
    {
        std::string line;
        int i = 0;
        while (std::getline(file, line))
        {
            if (std::regex_match(line, r))
            {
                this->getTransition(line);
            }
            else
            {
                std::cout << "Line " << i << " is not transition!" << std::endl;
            }
            i++;
        }
        file.close();
    }
    else
    {
        std::cout << "File error!" << std::endl;
    }
    return this->states;
}
