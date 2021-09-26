#include "Transition.h"

Transition::Transition(State from, State to, char symbol)
{
    this->m_from.clear();
    this->m_to.clear();
    this->m_from.push_back(from);
    this->m_to.push_back(to);
    this->m_symbol = symbol;
}
