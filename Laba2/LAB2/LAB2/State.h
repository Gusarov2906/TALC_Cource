#pragma once
#include <vector>
#include <string>

#include "Transition.h"

class State
{
public:
    State(std::string name);

    void setName(std::string name);

    std::string getName() const;

    const bool isStart() const;
    const bool isFinal() const;

    std::vector<State*> nextState(char sym);

    std::vector<Transition> getTransitions() const;
    std::vector<Transition> getTransitions(char sym) const;

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

