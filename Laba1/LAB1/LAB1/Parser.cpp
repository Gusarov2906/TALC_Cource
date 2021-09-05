#include "Parser.h"
#include <cctype>
#include <iostream>
#include <stack>

Parser::Parser()
{
	this->index = 0;
	prevIndexOpenParenthesis = false;
}

Parser::~Parser()
{
}

std::vector<Lexeme*> Parser::getLexemes(std::string str)
{
	std::vector<Lexeme*> lexemes;

	index = 0;
	prevIndexOpenParenthesis = false;

	Lexeme* tmp = nullptr;
	str = replaceInString(str, " ", "");
	while (index < str.length())
	{
		tmp = getLexeme(str);
		if (tmp != nullptr)
		{
			lexemes.push_back(tmp);
		}
		else
		{
			std::cout << "Nullptr lexeme!" << std::endl;;
		}
	}

	checkLexemes(lexemes);

	return lexemes;
}

Lexeme* Parser::getLexeme(const std::string& str)
{
	bool havePoint = false;
	bool haveExponentSymbol = false;
	bool haveExponentSignSymbol = false;
	bool isNumber = false;
	std::string resStr = "";
	Lexeme* lexeme = nullptr;

	if ((index == 0 || prevIndexOpenParenthesis) && ((long long)index + 1 < str.length()) &&
		((isdigit(str[(long long)index+1]) || isPoint(str[(long long)index + 1]))))
	{
		prevIndexOpenParenthesis = false;
		if (str[index] == '-' || str[index] == '+')
		{
			resStr += str[index];
			index++;
		}
	}

	while ((isdigit(str[index]) || isPoint(str[index]) || isExponentSymbol(str[index]) 
		|| (str[index]) == '-' || (str[index]) == '+') && index < str.length())
	{

		if (isPoint(str[index]) && !havePoint)
		{
			havePoint = true;
		}
		else if (isPoint(str[index]) && havePoint)
		{
			std::cout << "Two point in one number!" << std::endl;;
			return nullptr;
		}

		if (isExponentSymbol(str[index]) && !haveExponentSymbol)
		{
			havePoint = true;
		}
		else if (isExponentSymbol(str[index]) && haveExponentSymbol)
		{
			std::cout << "Two exponent symbols in one number!" << std::endl;;
			return nullptr;
		}

		if (((str[index]) == '-' || (str[index]) == '+') && !haveExponentSignSymbol)
		{
			haveExponentSignSymbol = true;
		}
		else if (((str[index]) == '-' || (str[index]) == '+') && haveExponentSignSymbol)
		{
			std::cout << "Two exponent sign symbols in one number!" << std::endl;;
			return nullptr;
		}

		resStr += str[index];

		isNumber = true;
		index++;
	}

	if (isNumber)
	{
		index--;
		if (haveExponentSymbol && haveExponentSignSymbol)
		{
			double num = std::stod(resStr.substr(0, resStr.rfind('E')));
			if (resStr[resStr.rfind('E') + 1] == '+')
			{
				num *= std::stod(resStr.substr(resStr.rfind('E') + 2, resStr.back()));
			}
			else if (resStr[resStr.rfind('E') + 1] == '-')
			{
				num /= std::stod(resStr.substr(resStr.rfind('E') + 2, resStr.back()));
			}
			else
			{
				std::cout << "Exponent error!" << std::endl;
			}
			lexeme = new Lexeme(num);
		}
		lexeme = new Lexeme(std::stod(resStr));
	}
	else if (isArithmeticSign(str[index]) || isParenthesis(str[index]))
	{
		if (str[index] == '(')
		{
			prevIndexOpenParenthesis = true;
		}
		resStr = str[index];
		lexeme = new Lexeme(resStr);
	}
	else if (isIndention(str[index]))
	{
		std::cout << "Indent symbol: " << str[index] << std::endl;;
		lexeme = nullptr;
	}
	else
	{
		std::cout << "Unknown symbol: " << str[index] << std::endl;;
		lexeme = nullptr;
	}

	index++;

	return lexeme;
}

bool Parser::isArithmeticSign(const char symbol)
{
	if (symbol == '+' || symbol == '-' || symbol == '/' || symbol == '*' || symbol == '^')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Parser::isParenthesis(const char symbol)
{
	if (symbol == '(' || symbol == ')')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Parser::isPoint(const char symbol)
{
	if (symbol == '.')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Parser::isIndention(const char symbol)
{
	if (symbol == ' ' || symbol == '\n' || symbol == '\t')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Parser::isExponentSymbol(const char symbol)
{
	if (symbol == 'E' || symbol == 'Å')
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::string Parser::replaceInString(std::string str, std::string tofind, std::string toreplace)
{
	size_t position = 0;
	for (position = str.find(tofind); position != std::string::npos; position = str.find(tofind, position))
	{
		str.replace(position, 1, toreplace);
	}
	return(str);
}

std::string Parser::checkLexemes(std::vector<Lexeme*>& lexemes)
{
	std::stack<int> openParenthesis;

	std::string code = "";

	for (int i = 0; i < lexemes.size(); i++)
	{
		if (lexemes[i]->getType() == LexemeType::parenthesis)
		{
			if (lexemes[i]->getString() == "(")
			{
				openParenthesis.push(1);
			}
			else
			{
				if (openParenthesis.size() > 0)
				{
					openParenthesis.pop();
				}
				else
				{
					code += '1';
					std::cout << "Parenthesis error!" << std::endl;;
				}
			}
		}

		if (i > 0)
		{
			if (lexemes[(long long)i - 1]->getType() == LexemeType::decimal
				&& lexemes[i]->getType() == LexemeType::decimal)
			{
				code += '3';
				std::cout << "Double numbers error!" << std::endl;;
			}
			if (lexemes[(long long)i - 1]->getType() == LexemeType::operation
				&& lexemes[i]->getType() == LexemeType::operation)
			{
				code += '4';
				std::cout << "Double operation error!" << std::endl;;
			}
		}
	}


	if (openParenthesis.size() > 0)
	{
		code += '2';
		std::cout << "Parenthesis error!" << std::endl;;
	}

	return code;
}
