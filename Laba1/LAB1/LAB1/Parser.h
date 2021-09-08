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

	double* getNumberInExponentForm(std::string& in);

	bool isNegativeSign(const std::string str);
	bool isArithmeticSign(const char symbol);
	bool isParenthesis(const char symbol);
	bool isPoint(const char symbol);
	bool isExponentSymbol(const char symbol);
	bool isIndention(const char symbol);

	void deleteEmptyParethesis(std::vector<Lexeme*>& lexemes, int& size, int& i);

	bool checkNextCloseParenthesis(std::vector<Lexeme*> lexemes, int i);
	bool multiplyDetectNext(std::vector<Lexeme*> lexemes, int i);
	bool multiplyDetectPrev(std::vector<Lexeme*> lexemes, int i);
	bool checkDoubleNumbers(std::vector<Lexeme*> lexemes, int i);
	bool checkDoubleOperations(std::vector<Lexeme*> lexemes, int i);
};
