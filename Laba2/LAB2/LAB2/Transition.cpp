#include "Transition.h"
#include <algorithm>

Transition::Transition(State from, State to, char symbol)
{
    this->m_from.clear();
    this->m_to.clear();
    this->m_from.push_back(from);
    this->m_to.push_back(to);
    this->m_symbol = symbol;
}

std::string Transition::toString() const
{
    std::string res = "";
    for (State state : m_from)
    {
        res += state.getName();
    }
    res += ",";
    res += m_symbol;
    res += "=";
    for (State state : m_to)
    {
        res += state.getName();
    }
    return res;
}

const std::vector<State> Transition::getFromStates() const
{
    return this->m_from;
}

const std::vector<State> Transition::getToStates() const
{
    return this->m_to;
}

const State Transition::getFromState() const
{
    return this->m_from[0];
}

const State Transition::getToState() const
{
    return this->m_to[0];
}

const char Transition::getSymbol() const
{
    return m_symbol;
}

bool Transition::operator>(const Transition& right)
{
    return this->m_from[0] > right.m_from[0];
}

bool Transition::operator<(const Transition& right)
{
    return this->m_from[0] < right.m_from[0];
}

bool Transition::operator==(const Transition& right)
{
    return this->m_from[0] == right.m_from[0];
}

bool Transition::operator!=(const Transition& right)
{
    return !(this->m_from[0] == right.m_from[0]);
}

bool Transition::operator>=(const Transition& right)
{
    return this->m_from[0] >= right.m_from[0];
}

bool Transition::operator<=(const Transition& right)
{
    return this->m_from[0] <= right.m_from[0];
}

bool operator>(const Transition& left, const Transition& right)
{
    return left.m_from[0] > right.m_from[0];
}

bool operator<(const Transition& left, const Transition& right)
{
    return left.m_from[0] < right.m_from[0];
}

bool operator==(const Transition& left, const Transition& right)
{
    return left.m_from[0] == right.m_from[0];
}

bool operator!=(const Transition& left, const Transition& right)
{
    return left.m_from[0] != right.m_from[0];
}

bool operator>=(const Transition& left, const Transition& right)
{
    return left.m_from[0] >= right.m_from[0];
}

bool operator<=(const Transition& left, const Transition& right)
{
    return left.m_from[0] <= right.m_from[0];
}
