#pragma once
#include <vector>

#include "State.h"

class Transition
{
public:
    Transition(State from, State to, char symbol);
    std::string toString() const;

    const std::vector<State> getFromStates() const;
    const std::vector<State> getToStates() const;

    const State getFromState() const;
    const State getToState() const;

    const char getSymbol() const;

    friend bool operator>(const Transition& left, const Transition& right);
    friend bool operator<(const Transition& left, const Transition& right);
    friend bool operator==(const Transition& left, const Transition& right);
    friend bool operator!=(const Transition& left, const Transition& right);
    friend bool operator>=(const Transition& left, const Transition& right);
    friend bool operator<=(const Transition& left, const Transition& right);

    bool operator>(const Transition& right);
    bool operator<(const Transition& right);
    bool operator==(const Transition& right);
    bool operator!=(const Transition& right);
    bool operator>=(const Transition& right);
    bool operator<=(const Transition& right);

private:
    std::vector<State> m_from;
    std::vector<State> m_to;
    char m_symbol;

};

