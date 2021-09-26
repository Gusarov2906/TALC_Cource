#pragma once
#include <vector>
#include <string>

class State
{
public:
    State(std::string name);
    std::string getName();

protected:
    std::string name;

};

