#pragma once
#include "Transition.h"
class StateMachine
{
public:
    StateMachine(std::vector<Transition> transactions);
    std::vector<Transition> getTransactions();
    bool isValid(std::string in);

protected:
    std::vector<Transition> m_transactions;
    void sortTransactions();
};

