#include <iostream>
#include "Parser.h"
#include "FinalStateMachine.h"
#include "Determinator.h"

int main()
{
    std::string filename;
    std::string str;
    Parser parser;
    std::map<std::string, State*> states;
    std::vector<Transition> transitions;

    while (transitions.size() <= 0)
    {
        std::cout << "Write file name: ";
        std::getline(std::cin, filename);

        FinalStateMachine fsm(parser.parse(filename));
        Determinator determinator;

        fsm = determinator.determinate(fsm);

        for (std::pair<std::string, State*> item : fsm.getStates())
        {
            for (Transition transition : item.second->getTransitions())
            {
                transitions.push_back(transition);
            }
        }
        //fsm.sortAndPrintTransactions(transitions);
        std::cout << std::endl;


        while (1)
        {
            std::cout << "Write str: ";
            std::getline(std::cin, str);
            if (fsm.isValid(str))
            {
                std::cout << "Str is correct :)" << std::endl;
            }
            else
            {
                std::cout << "Str is not correct :(" << std::endl;
            }
        }
    }
    return 0;
}