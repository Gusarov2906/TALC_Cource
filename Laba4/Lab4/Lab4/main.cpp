#include <iostream>
#include "FileReader.h"
#include "PushdownAutomaton.h"
#include <Windows.h>

int main()
{
    FileReader fr;
    std::string filename;
    std::string input;
 //   setlocale(LC_ALL, "Russian");
 //   SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    bool isFileOk = false;

    while (!isFileOk)
    {
        std::cout << "Write filename:" << std::endl;
        try
        {
            std::getline(std::cin, filename);
            fr.getData(filename);
            isFileOk = true;

        }
        catch (std::string err)
        {
            std::cout << err << std::endl;
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;

    fr.printRawRules();
    fr.printInputAlphabet();
    fr.printNonterminalsAlphabet();
    fr.printAlphabet();
    fr.printCommands();

    while (1)
    {
        std::cout << "Write str:" << std::endl;
        std::getline(std::cin, input);
        const std::vector<ConfigCommand> commands = fr.getCommands();
        PushdownAutomaton pa(input, commands);
        if (pa.checkStr(input))
        {
            std::cout << "Str OK :)" << std::endl;
            for (std::string str : pa.getChainConfigurations())
            {
                std::cout << str << std::endl;
            }
        }
        else
        {
            std::cout << "Str not OK :(" << std::endl;
        }
        std::cout << std::endl;
    }
    return 0;
}