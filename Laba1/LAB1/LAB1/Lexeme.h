#pragma once
#include <string>

enum class LexemeType
{
	decimal = 0,
	parenthesis,
	operation,
	function
};

class Lexeme
{
public:
	Lexeme(double number);
	Lexeme(std::string str);
	~Lexeme();

	double getValue();
	LexemeType getType();
	std::string getString();
	std::string getFormatedString();
	int getPriority();

private:
	LexemeType type;
	double num;
	std::string str;
	int priority;
};
