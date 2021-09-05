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

	template <typename T>
	T getValue();
	LexemeType getType();
	std::string getString();

private:
	LexemeType type;
	double num;
	std::string str;
};
