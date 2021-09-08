#include <iostream>
#include "parser.h"

int main(int argc, char* argv[])
{
	Parser parser;
	std::string str;
	while (1)
	{
		std::cout << ">>> ";
		std::getline(std::cin, str, '\n');
		std::vector<Lexeme*> lexemes = parser.getLexemes(str);
		for (int i = 0; i < lexemes.size(); i++)
		{
			std::cout << lexemes[i]->getString() << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}