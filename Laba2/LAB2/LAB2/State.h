#pragma once
#include <vector>
#include <string>

#include "Transition.h"

class State
{
public:
    State(std::string name);
    std::string getName() const;

    const bool isStart() const;
    const bool isFinal() const;

    State* nextState(char sym);

    std::vector<Transition> getTransitions() const;

    void addTransition(Transition transition);

    friend bool operator>(const State& left, const State& right);
    friend bool operator<(const State& left, const State& right);
    friend bool operator==(const State& left, const State& right);
    friend bool operator!=(const State& left, const State& right);
    friend bool operator>=(const State& left, const State& right);
    friend bool operator<=(const State& left, const State& right);

    bool operator>(const State& right);
    bool operator<(const State& right);
    bool operator==(const State& right);
    bool operator!=(const State& right);
    bool operator>=(const State& right);
    bool operator<=(const State& right);

protected:
    std::string m_name;
    bool m_isStart;
    bool m_isFinal;
    std::vector<Transition> m_transitions;
};

