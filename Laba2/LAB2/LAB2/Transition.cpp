#include "Transition.h"
#include "State.h"
#include <algorithm>

Transition::Transition(State* from, State* to, char symbol)
{
    this->m_from.push_back(from);
    this->m_to.push_back(to);
    this->m_symbol = symbol;
}

std::string Transition::toString() const
{
    std::string res = "";
    for (State* state : m_from)
    {
        res += state->getName();
    }
    res += ",";
    res += m_symbol;
    res += "=";
    for (State* state : m_to)
    {
        res += state->getName();
    }
    return res;
}

std::vector<State*> Transition::getFromStates() const
{
    return this->m_from;
}

std::vector<State*> Transition::getToStates() const
{
    return this->m_to;
}

bool Transition::isInitialized()
{
    if (m_from.size() > 0 && m_to.size() > 0)
    {
        return true;
    }
    return false;
}

State* Transition::getFromState() const
{
    return this->m_from[0];
}

State* Transition::getToState() const
{
    return this->m_to[0];
}

const char Transition::getSymbol() const
{
    return m_symbol;
}

bool Transition::operator>(const Transition& right)
{
    return *this->m_from[0] > *right.m_from[0];
}

bool Transition::operator<(const Transition& right)
{
    return *this->m_from[0] < *right.m_from[0];
}

bool Transition::operator==(const Transition& right)
{
    return *this->m_from[0] == *right.m_from[0];
}

bool Transition::operator!=(const Transition& right)
{
    return !(*this->m_from[0] == *right.m_from[0]);
}

bool Transition::operator>=(const Transition& right)
{
    return *this->m_from[0] >= *right.m_from[0];
}

bool Transition::operator<=(const Transition& right)
{
    return *this->m_from[0] <= *right.m_from[0];
}

bool operator>(const Transition& left, const Transition& right)
{
    return *left.m_from[0] > *right.m_from[0];
}

bool operator<(const Transition& left, const Transition& right)
{
    return *left.m_from[0] < *right.m_from[0];
}

bool operator==(const Transition& left, const Transition& right)
{
    return *left.m_from[0] == *right.m_from[0];
}

bool operator!=(const Transition& left, const Transition& right)
{
    return !(*left.m_from[0] == *right.m_from[0]);
}

bool operator>=(const Transition& left, const Transition& right)
{
    return *left.m_from[0] >= *right.m_from[0];
}

bool operator<=(const Transition& left, const Transition& right)
{
    return *left.m_from[0] <= *right.m_from[0];
}
