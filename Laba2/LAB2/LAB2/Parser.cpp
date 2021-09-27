#include "Parser.h"
#include <iostream>
#include <fstream>
#include <regex>

Parser::Parser()
{
}

Transition Parser::getTransition(std::string str)
{
    const std::regex r(R"((^q\d{1,2}),(.{1})=([fq]\d{1,2})$)");
    std::smatch m;
    if (std::regex_match(str, m, r))
    {
        if (m.ready())
        {
            return Transition(State(m.str(1)), State(m.str(3)), m.str(2)[0]);
        }
    }
    return Transition(State("def"), State("def"), '\0');
}

std::vector<Transition> Parser::parse(std::string filename)
{
    std::vector<Transition> transitions;

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
                transitions.push_back(this->getTransition(line));
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
    return transitions;
}
