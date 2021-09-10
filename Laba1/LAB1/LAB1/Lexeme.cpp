#include "Lexeme.h"

Lexeme::Lexeme(double number)
{
	this->type = LexemeType::decimal;
	this->num = number;
	this->str = "";
	this->priority = 0;
}

Lexeme::Lexeme(std::string str)
{
	if (str == "(" || str == ")")
	{
		this->type = LexemeType::parenthesis;
		this->priority = 1;
	} else if (str == "+" || str == "-" || str == "*" || str == "/" || str == "^")
	{
		this->type = LexemeType::operation;
		if (str == "+" || str == "-")
		{
			this->priority = 2;
		} else if (str == "/" || str == "*")
		{
			this->priority = 3;
		}
		else
		{
			this->priority = 4;
		}
	} else 
	{
		this->type = LexemeType::function;
		this->priority = 5;
	}
	this->num = 0;
	this->str = str;
}

Lexeme::~Lexeme()
{

}

double Lexeme::getValue()
{
	switch (this->type)
	{
	case LexemeType::decimal:
		return num;
		break;
	default:
		return 0;
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

int Lexeme::getPriority()
{
	return this->priority;
}
