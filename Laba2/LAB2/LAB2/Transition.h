#pragma once
#include <vector>
#include <iostream>

class State;


class Transition
{
public:
    Transition(State* from, State* to, char symbol);
    Transition();

    std::string toString() const;

    std::vector<State*> getFromStates() const;
    std::vector<State*> getToStates() const;

    bool isInitialized();

    State* getFromState() const;
    State* getToState() const;

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
    std::vector<State*> m_from;
    std::vector<State*> m_to;
    char m_symbol;

};

