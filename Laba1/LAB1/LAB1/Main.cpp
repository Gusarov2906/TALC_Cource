#include <iostream>
#include "Parser.h"
#include "PolishReverseConverter.h"

int main(int argc, char* argv[])
{
	Parser parser;
	PolishReverseConverter converter;
	std::string str;
	while (1)
	{
		std::cout << ">>> ";
		std::getline(std::cin, str, '\n');
		LexemeString lexemes = parser.getLexemes(str);
		for (int i = 0; i < lexemes.size(); i++)
		{
			std::cout << lexemes.at(i).getString() << " ";
		}
		std::cout << std::endl;
		converter.convert(lexemes);
	}	
	return 0;
}