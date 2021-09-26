#include <iostream>
#include "Parser.h"

int main()
{
    std::string filename;
    Parser parser;
    std::vector<Transition> transitions;
    std::cout << "Write file name: ";
    std::cin >> filename;

    transitions = parser.parse(filename);
    for (Transition item : transitions)
    {
        std::cout << item.toString() << std::endl;
    }
    return 0;
}