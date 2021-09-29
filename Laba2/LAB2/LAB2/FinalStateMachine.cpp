#include "FinalStateMachine.h"

int cmpfunc(const void* a, const void* b)
{
    if (*(Transition*)a < *(Transition*)b) return -1;
    if (*(Transition*)a == *(Transition*)b) return 0;
    if (*(Transition*)a > *(Transition*)b) return 1;
}

void FinalStateMachine::sortAndPrintTransactions(std::vector<Transition> transitions)
{
    std::vector<Transition> sortedTransitions = transitions;
    if (transitions.size() > 0)
    {
        qsort(&sortedTransitions[0], sortedTransitions.size(), sizeof(Transition), cmpfunc);
        printTransactions(sortedTransitions);
    }
}

void FinalStateMachine::printTransactions(std::vector<Transition> transitions)
{
    for (Transition item : transitions)
    {
        std::cout << item.toString() << std::endl;
    }
}

FinalStateMachine::FinalStateMachine(std::map<std::string, State*> states)
{
    this->index = 0;
    this->m_states = states;
}

std::map<std::string, State*> FinalStateMachine::getStates()
{
    return this->m_states;
}

bool FinalStateMachine::isValid(std::string in)
{
    if (m_states.size() <= 0)
    {
        return false;
    }
    index = 0;

    State* currentState = this->m_states["|q0|"];
    
    return doStep(currentState, in);
}

bool FinalStateMachine::doStep(State* currentState, std::string in)
{
    if (currentState->nextState(in[index]).size() > 0)
    {
        currentState = currentState->nextState(in[index])[0];
        index++;
        if ((index) == in.size())
        {
            if (currentState->isFinal())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        return doStep(currentState, in);
    }
    else
    {
        return false;
    }
}
