#pragma once
#include <string>
#include <vector>

#include "Transition.h"

class Parser
{
public:
    Parser();
    Transition getTransition(std::string str);
    std::vector<Transition> parse(std::string filename);
};

