#pragma once
#include "Lexeme.h"
#include <vector>

class Parser
{
public:
	Parser();
	~Parser();
	std::vector<Lexeme*> getLexemes(std::string str);
private:
	int index;
	bool prevIndexOpenParenthesis;
	Lexeme* getLexeme(const std::string& str);
	std::string replaceInString(std::string str, std::string tofind, std::string toreplace);

	std::string checkLexemes(std::vector<Lexeme*>& lexemes);

	bool isArithmeticSign(const char symbol);
	bool isParenthesis(const char symbol);
	bool isPoint(const char symbol);
	bool isExponentSymbol(const char symbol);
	bool isIndention(const char symbol);
};
