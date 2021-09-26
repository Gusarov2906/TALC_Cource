#include "State.h"

State::State(std::string name)
{
    this->name = name;
}

std::string State::getName()
{
    return this->name;
}
