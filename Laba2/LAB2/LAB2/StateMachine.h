#pragma once
#include "Transition.h"
class StateMachine
{
public:
    StateMachine(std::vector<Transition> transactions);

protected:
    std::vector<Transition> m_transactions;

};

