#include <iostream>
#include "Parser.h"

int main()
{
    std::string filename;
    Parser parser;

    std::cout << "Write file name: ";
    std::cin >> filename;

    parser.parse(filename);

    return 0;
}