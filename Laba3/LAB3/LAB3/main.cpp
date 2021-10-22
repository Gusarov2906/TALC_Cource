#include <iostream>
#include "FileReader.h"

int main()
{
    FileReader fr;
    std::string filename;

    while (1)
    {
        std::cout << "Write filename:" << std::endl;
        std::getline(std::cin, filename);
        std::cout << std::endl;

        fr.getData(filename);

        fr.printRawRules();
        fr.printInputAlphabet();
        fr.printNonterminalsAlphabet();
        fr.printAlphabet();
        fr.printCommands();
    }
    return 0;
}