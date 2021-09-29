#pragma once
#include <string>
#include <vector>
#include <map>

#include "Transition.h"
#include "State.h"

class Parser
{
public:
    Parser();
    bool getTransition(std::string str);
    std::map<std::string, State*> parse(std::string filename);

protected:
    std::map<std::string, State*> states;
};
