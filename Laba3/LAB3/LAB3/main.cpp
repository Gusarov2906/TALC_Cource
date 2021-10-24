#include <iostream>
#include "FileReader.h"
#include "PushdownAutomaton.h"

int main()
{
    FileReader fr;
    std::string filename;
    std::string input;

    std::cout << "Write filename:" << std::endl;
    std::getline(std::cin, filename);
    std::cout << std::endl;

    fr.getData(filename);

    fr.printRawRules();
    fr.printInputAlphabet();
    fr.printNonterminalsAlphabet();
    fr.printAlphabet();
    fr.printCommands();

    while (1)
    {

        std::getline(std::cin, input);
        const std::vector<ConfigCommand> commands = fr.getCommands();
        PushdownAutomaton pa(input, commands);
        if (pa.checkStr(input))
        {
            std::cout << "Str OK :)" << std::endl;
        }
        else
        {
            std::cout << "Str not OK :(" << std::endl;
        }
        for (std::string str : pa.getChainConfigurations())
        {
            std::cout << str << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}