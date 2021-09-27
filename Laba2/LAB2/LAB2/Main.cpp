#include <iostream>
#include "Parser.h"
#include "StateMachine.h"

int main()
{
    std::string filename;
    std::string str;
    Parser parser;
    std::vector<Transition> transitions;
    std::cout << "Write file name: ";
    std::cin >> filename;
    std::cout << "Write str: ";
    std::cin >> str;
    StateMachine sm (parser.parse(filename));
    for (Transition item : sm.getTransactions())
    {
        std::cout << item.toString() << std::endl;
    }
    std::cout << sm.isValid(str);
    return 0;
}