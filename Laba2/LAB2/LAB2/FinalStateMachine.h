#pragma once
#include "Transition.h"
#include "State.h"
#include <map>

class FinalStateMachine
{
public:
    FinalStateMachine(std::map<std::string, State*> states);
    std::map<std::string, State*> getStates();
    bool isValid(std::string in);
    void sortAndPrintTransactions(std::vector<Transition> transitions);
    void printTransactions(std::vector<Transition>);

protected:
    std::map<std::string, State*> m_states;
    bool doStep(State* currentState, std::string in);
    int index ;
};