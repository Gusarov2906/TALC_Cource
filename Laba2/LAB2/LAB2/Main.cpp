#include <iostream>
#include "Parser.h"
#include "FinalStateMachine.h"

int main()
{
    std::string filename;
    std::string str;
    Parser parser;
    std::map<std::string, State*> states;
    std::cout << "Write file name: ";
    std::getline(std::cin, filename);

    FinalStateMachine sm (parser.parse(filename));
    std::vector<Transition> transitions;
    for (std::pair<std::string, State*> item : sm.getStates())
    {
        for (Transition transition : item.second->getTransitions())
        {
            transitions.push_back(transition);
        }
    }
    sm.sortAndPrintTransactions(transitions);
    std::cout << std::endl;


    while (1)
    {
        std::cout << "Write str: ";
        std::getline(std::cin, str);
        if (sm.isValid(str))
        {
            std::cout << "Str is correct :)" << std::endl;
        }
        else
        {
            std::cout << "Str is not correct :(" << std::endl;
        }
    }
    return 0;
}