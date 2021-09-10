#pragma once
#include "Lexeme.h"
#include <vector>
#include "LexemeString.h"

class Parser
{
public:
	Parser();
	~Parser();
	LexemeString getLexemes(std::string str);
private:
	int index;
	bool prevIndexOpenParenthesis;
	Lexeme* getLexeme(const std::string& str);
	std::string replaceInString(std::string str, std::string tofind, std::string toreplace);

	std::string checkLexemes(LexemeString& lexemes);

	double* getNumberInExponentForm(std::string& in);

	bool isNegativeSign(const std::string str);
	bool isArithmeticSign(const char symbol);
	bool isParenthesis(const char symbol);
	bool isPoint(const char symbol);
	bool isExponentSymbol(const char symbol);
	bool isIndention(const char symbol);

	void deleteEmptyParethesis(LexemeString* lexemes, int& size, int& i);

	bool checkNextCloseParenthesis(LexemeString& lexemes, int i);
	bool multiplyDetectNext(LexemeString& lexemes, int i);
	bool multiplyDetectPrev(LexemeString& lexemes, int i);
	bool checkDoubleNumbers(LexemeString& lexemes, int i);
	bool checkDoubleOperations(LexemeString& lexemes, int i);
};
