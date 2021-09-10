#include <iostream>
#include "Parser.h"
#include "PolishReverseConverter.h"
#include "Solver.h"
#include <iomanip>

int main(int argc, char* argv[])
{
	Parser parser;
	PolishReverseConverter converter;
	Solver solver;

	std::string str;
	while (1)
	{
		std::cout << ">>> ";
		std::getline(std::cin, str, '\n');
		LexemeString lexemes = parser.getLexemes(str);
		std::cout << "After parse:" << std::endl;
		std::cout <<  lexemes.toString() << std::endl;
		LexemeString lex = converter.convert(lexemes);
		std::cout << "After convert:" << std::endl;
		std::cout << lex.toString() << std::endl;
		std::cout << "ANSWER: " << solver.solve(lex) << std::endl;
	}	
	return 0;
}