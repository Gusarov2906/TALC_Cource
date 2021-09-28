#include "State.h"
#include <iostream>

State::State(std::string name)
{
    this->m_name = name;
    m_isStart = false;
    m_isFinal = false;

    if (name.length() > 1)
    {
        if (name[0] == 'q' && name[1] == '0')
        {
            m_isStart = true;
        }
        if (name[0] == 'f')
        {
            m_isFinal = true;
        }
    }
    else
    {
        std::cout << "State error!";
    }

}

std::string State::getName() const
{
    return this->m_name;
}

const bool State::isStart() const
{
    return m_isStart;
}

const bool State::isFinal() const
{
    return m_isFinal;
}

State* State::nextState(char sym)
{
    for (Transition item : m_transitions)
    {
        if (item.getSymbol() == sym)
        {
            return item.getToState();
        }
    }
    return nullptr;
}

std::vector<Transition> State::getTransitions() const
{
    return this->m_transitions;
}

void State::addTransition(Transition transition)
{
    this->m_transitions.push_back(transition);
}

bool State::operator==(const State& right)
{
    return std::stoi(this->m_name.substr(1)) == std::stoi(right.m_name.substr(1));
}

bool State::operator!=(const State& right)
{
    return !(std::stoi(this->m_name.substr(1)) == std::stoi(right.m_name.substr(1)));
}

bool State::operator>=(const State& right)
{
    return std::stoi(this->m_name.substr(1)) >= std::stoi(right.m_name.substr(1));
}

bool State::operator<=(const State& right)
{
    return std::stoi(this->m_name.substr(1)) <= std::stoi(right.m_name.substr(1));
}

bool State::operator>(const State& right)
{
    return std::stoi(this->m_name.substr(1)) > std::stoi(right.m_name.substr(1));
}

bool State::operator<(const State& right)
{
    return std::stoi(this->m_name.substr(1)) < std::stoi(right.m_name.substr(1));
}

bool operator>(const State& left, const State& right)
{
    return std::stoi(left.m_name.substr(1)) > std::stoi(right.m_name.substr(1));
}

bool operator<(const State& left, const State& right)
{
    return std::stoi(left.m_name.substr(1)) < std::stoi(right.m_name.substr(1));
}

bool operator==(const State& left, const State& right)
{
    return std::stoi(left.m_name.substr(1)) == std::stoi(right.m_name.substr(1));
}

bool operator!=(const State& left, const State& right)
{
    return !(std::stoi(left.m_name.substr(1)) == std::stoi(right.m_name.substr(1)));
}

bool operator>=(const State& left, const State& right)
{
    return std::stoi(left.m_name.substr(1)) >= std::stoi(right.m_name.substr(1));
}

bool operator<=(const State& left, const State& right)
{
    return std::stoi(left.m_name.substr(1)) <= std::stoi(right.m_name.substr(1));
}
