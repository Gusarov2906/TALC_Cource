#include "State.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>


std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

State::State(std::string name)
{
    this->m_name = name;
    m_isStart = false;
    m_isFinal = false;

    //if (name.length() > 1)
    //{
    if (name[0] == 'q' && name[1] == '0')
    {
        m_isStart = true;
    }
    if (name.find('f') != std::string::npos)
    {
        m_isFinal = true;
    }
    //}
    //else
    //{
    //    std::cout << "State error!";
    //}

}

void State::setName(std::string name)
{
    this->m_name = name;
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

std::vector<State*> State::nextState(char sym)
{
    std::vector<State*> res;
    for (Transition item : m_transitions)
    {
        if (item.getSymbol() == sym)
        {
            res.push_back(item.getToState());
        }
    }
    return res;
}

std::vector<Transition> State::getTransitions() const
{
    return this->m_transitions;
}

std::vector<Transition> State::getTransitions(char sym) const
{
    std::vector<Transition> res;
    for (Transition item : m_transitions)
    {
        if (item.getSymbol() == sym)
        {
            res.push_back(item);
        }
    }
    return res;
}

void State::addTransition(Transition transition)
{
    this->m_transitions.push_back(transition);
}

bool State::operator==(const State& right)
{
    std::vector<std::string> m_left = split(this->getName(), '|');
    std::vector<std::string> m_right = split(right.getName(), '|');
    std::sort(m_left.begin(), m_left.end());
    std::sort(m_right.begin(), m_right.end());
    if (m_left.size() == m_right.size())
    {
        for (int i = 0; i < m_left.size(); i++)
        {
            if (m_left[i] != m_right[i])
                return false;
        }
    }
    return true;
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
    bool isEqual = false;
    std::vector<std::string> m_left = split(left.getName(), '|');
    std::vector<std::string> m_right = split(right.getName(), '|');
    std::sort(m_left.begin(), m_left.end());
    std::sort(m_right.begin(), m_right.end());

    if (m_left.size() == m_right.size())
    {
        for (int i = 0; i < m_left.size(); i++)
        {
            if (m_left[i] != m_right[i])
                return false;
        }
    }
    else
    {
        return false;
    }
    
    return true;
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
