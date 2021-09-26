#include "StateMachine.h"

StateMachine::StateMachine(std::vector<Transition> transactions)
{
    this->m_transactions = transactions;
}
