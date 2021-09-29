#include "Determinator.h"

struct isValue
{
    State* m_value;

    isValue(State* value)
    {
        m_value = value;
    }

    bool operator()(const State* cls) const
    {
        return *cls == *m_value;
    }
};

Determinator::Determinator()
{

}

FinalStateMachine Determinator::determinate(FinalStateMachine& fsm)
{
    std::stack<State*> statesStack;
    std::vector<State*> history;
    std::vector<char> symbols;


    std::vector<Transition> oldTransitions;


    for (std::pair<std::string, State*> item : fsm.getStates())
    {
        for (Transition transition : item.second->getTransitions())
        {
            oldTransitions.push_back(transition);
        }
    }
    fsm.sortAndPrintTransactions(oldTransitions);

    for (Transition transition : oldTransitions)
    {
        if (std::find(symbols.begin(), symbols.end(), transition.getSymbol()) == symbols.end())
        {
            symbols.push_back(transition.getSymbol());
        }
    }

    State* tmp = new State("q0");
    tmp->setName('|' + fsm.getStates()["q0"]->getName() + '|');
    statesStack.push(tmp);
    history.push_back(tmp);

    while (statesStack.size() != 0)
    {
        State* topStack = statesStack.top();
        statesStack.pop();

        for (char sym : symbols)
        {
            std::vector<Transition> transitions;
            for (Transition item : oldTransitions)
            {
                if ((topStack->getName().find('|' + item.getFromState()->getName()+'|') != std::string::npos) && item.getSymbol() == sym)
                {
                    transitions.push_back(item);
                }
            }

            State* nextState = new State("|");

            Transition newTransition(topStack, nextState, sym);
            for (Transition transition : transitions)
            {
                nextState->setName(nextState->getName() + transition.getToState()->getName() + '|');
            }
            
            if (nextState->getName() != "|")
            {
                topStack->addTransition(newTransition);

                if (std::find_if(history.begin(), history.end(), isValue(nextState)) == history.end())
                {
                    statesStack.push(nextState);
                    history.push_back(nextState);
                }
            }
        }
    }

    std::map<std::string, State*> res;

    for (State* state : history)
    {
        res[state->getName()] = state;
    }
    FinalStateMachine newFsm(res);
    return newFsm;

    //while (statesStack.size() != 0)
    //{
    //    State* lastTop = statesStack.top();
    //    statesStack.pop();
    //    for (char sym : symbols)
    //    {
    //        State* state = new State("");
    //        std::vector<Transition> transitionsWithSymbol = lastTop->getTransitions(sym);

    //        for (Transition transition : transitionsWithSymbol)
    //        {
    //            
    //        }
    //    }
    //}

    //for (char sym : symbols)
    //{
    //    for (std::pair<std::string, State*> item : fsm.getStates())
    //    {
    //        std::vector<State*> from;
    //        std::vector<State*> to;
    //        for (Transition transition : item.second->getTransitions(sym))
    //        {
    //            for (State* state : transition.getFromStates())
    //            {
    //                from.push_back(state);
    //            }
    //            for (State* state : transition.getToStates())
    //            {
    //                to.push_back(state);
    //            }
    //            transition.getFromState()
    //        }
    //    }
    //}

}
