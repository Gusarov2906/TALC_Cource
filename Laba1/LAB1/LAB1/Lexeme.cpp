#include "Lexeme.h"

Lexeme::Lexeme(double number)
{
	this->type = LexemeType::decimal;
	this->num = number;
	this->str = "";
}

Lexeme::Lexeme(std::string str)
{
	if (str == "(" || str == ")")
	{
		this->type = LexemeType::parenthesis;
	} else if (str == "+" || str == "-" || str == "*" || str == "/" || str == "^")
	{
		this->type = LexemeType::operation;
	} else 
	{
		this->type = LexemeType::function;
	}
	this->num = 0;
	this->str = str;
}

Lexeme::~Lexeme()
{

}

template <typename T>
T Lexeme::getValue()
{
	switch (this->type)
	{
	case LexemeType::decimal:
		return num;
		break;
	default:
		return str;
		break;
	}
}

LexemeType Lexeme::getType()
{
	return this->type;
}

std::string Lexeme::getString()
{
	switch (this->type)
	{
	case LexemeType::decimal:
		return std::to_string(num);
		break;
	default:
		return str;
		break;
	}
}
