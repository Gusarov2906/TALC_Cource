#include "StateMachine.h"

int cmpfunc(const void* a, const void* b)
{
    if (*(Transition*)a < *(Transition*)b) return -1;
    if (*(Transition*)a == *(Transition*)b) return 0;
    if (*(Transition*)a > *(Transition*)b) return 1;
}

StateMachine::StateMachine(std::vector<Transition> transactions)
{
    this->m_transactions = transactions;
    sortTransactions();
}

std::vector<Transition> StateMachine::getTransactions()
{
    return this->m_transactions;
}

bool StateMachine::isValid(std::string in)
{
    //check start and final
    if (m_transactions.size() <= 0)
    {
        return false;
    }

    int i = 0;
    int j = 0;
    int indexStateFrom = 0;

    State stateFrom = m_transactions[indexStateFrom].getFromState();
    
    //while (1)
    //{
    //    bool toSkip = false;
    //    bool inWhile = false;
    //    if (i < m_transactions.size())
    //    {
    //        while (i < m_transactions.size() && stateFrom == m_transactions[i].getFromState())
    //        {
    //            if (!toSkip && in.length() > j && in[j] == m_transactions[i].getSymbol())
    //            {
    //                j++;
    //                indexStateFrom = i;
    //                toSkip = true;
    //            }
    //            else
    //            {
    //                if (!toSkip && stateFrom != m_transactions[i].getFromState())
    //                {
    //                    return false;
    //                }
    //                else
    //                {
    //                    i++;
    //                    inWhile = true;
    //                }
    //            }
    //        }
    //        if (inWhile)
    //        {
    //            i--;
    //        }
    //        i++;
    //        stateFrom = m_transactions[indexStateFrom].getToState();
    //    }
    //    else
    //    {
    //        break;
    //    }
    //}
  
    //return true;
}

void StateMachine::sortTransactions()
{
    qsort(&m_transactions[0], m_transactions.size(), sizeof(Transition), cmpfunc);
}
