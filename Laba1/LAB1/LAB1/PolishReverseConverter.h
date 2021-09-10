#pragma once
#include "LexemeString.h"
#include <vector>
#include <stack>

class PolishReverseConverter
{
public:
	PolishReverseConverter();
	~PolishReverseConverter();
	LexemeString convert(LexemeString lexemes);
private:
	std::stack<Lexeme> operations;
};

