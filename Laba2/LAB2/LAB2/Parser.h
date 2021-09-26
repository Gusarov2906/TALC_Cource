#pragma once
#include <string>
#include <vector>

#include "State.h"

class Parser
{
public:
    Parser();
    std::vector<State> getStates(std::string str);
    void parse(std::string filename);

protected:
    std::vector<State> states;
    void sort();
};

