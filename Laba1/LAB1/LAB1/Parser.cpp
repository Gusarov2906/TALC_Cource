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

LexemeString Parser::getLexemes(std::string str)
{
    LexemeString lexemes;

    index = 0;
    prevIndexOpenParenthesis = false;

    Lexeme* tmp = nullptr;
    str = replaceInString(str, " ", "");
    while (index < str.length())
    {
        tmp = getLexeme(str);
        if (tmp != nullptr)
        {
            lexemes.push_back(*tmp);
        }
        else
        {
            lexemes.clear();
            return lexemes;
        }
        delete tmp;
    }

    if (checkLexemes(lexemes) != "")
    {
        lexemes.clear();
        return lexemes;
    }

    return lexemes;
}

Lexeme* Parser::getLexeme(const std::string& str)
{
    bool havePoint = false;
    bool haveExponentSymbol = false;
    bool haveExponentSignSymbol = false;
    bool isNumber = false;
    bool isLog = false;

    char expSymbol;
    int n = 0;

    std::string resStr = "";
    Lexeme* lexeme = nullptr;

    if (isNegativeSign(str))
    {
        prevIndexOpenParenthesis = false;
        if (str[index] == '-' || str[index] == '+')
        {
            resStr += str[index];
            index++;
        }
    }

    while (isdigit(str[index])
        || (isPoint(str[index]) && !havePoint)
        || (isExponentSymbol(str[index]) && !haveExponentSymbol && resStr.length() > 0)
        || ((str[index]) == '-' && haveExponentSymbol && !haveExponentSignSymbol)
        || ((str[index]) == '+' && haveExponentSymbol && !haveExponentSignSymbol)
        && index < str.length())
    {

        if (isPoint(str[index]))
        {
            havePoint = true;
        }

        if (isExponentSymbol(str[index]))
        {

            haveExponentSymbol = true;
            expSymbol = getExponentSymbol(str[index]);
        }

        if (((str[index]) == '-' || (str[index]) == '+') && !haveExponentSignSymbol && haveExponentSymbol)
        {
            haveExponentSignSymbol = true;
        }

        resStr += str[index];

        isNumber = true;
        index++;
    }

    while (str[index] == 'l' || str[index] == 'o' || str[index] == 'g')
    {
        n++;
        index++;
    }

    if (n == 3)
    {
        std::string substr = str.substr((long long)index - 3, 4);
        if (isLogFunctionStart(substr))
        {
            isLog = true;
        }
    }
    else if (n != 0 && n != 3)
    {
        std::cout << "Function name error!" << std::endl;;
    }

    if (isExponentSymbol(str[index]) && haveExponentSymbol)
    {
        std::cout << "Two exponent symbols in one number!" << std::endl;;
        return nullptr;
    }

    if (isPoint(str[index]) && havePoint)
    {
        std::cout << "Two point in one number!" << std::endl;;
        return nullptr;
    }

    if (isExponentSymbol(str[index]) && haveExponentSymbol)
    {
        std::cout << "Two exponent symbols in one number!" << std::endl;;
        return nullptr;
    }


    if (isNumber)
    {
        index--;
        if (haveExponentSymbol && haveExponentSignSymbol)
        {
            double* num = getNumberInExponentForm(resStr, expSymbol);
            if (num != nullptr)
            {
                lexeme = new Lexeme(*num);
                delete num;
            }
        }
        else if (haveExponentSymbol)
        {
            std::cout << "Exponent symbol error!" << std::endl;;
        }
        else if (haveExponentSignSymbol)
        {
            std::cout << "Exponent sign error!" << std::endl;;
        }
        else
        {
            //if (resStr[0] == '.')
            //{
            //    std::string tmp = '0' + resStr;
            //    resStr = tmp;
            //}
            lexeme = new Lexeme(std::stod(resStr));
        }
        prevIndexOpenParenthesis = false;
    }
    else if (isLog)
    {
        prevIndexOpenParenthesis = true;
        lexeme = new Lexeme("log(");
    }
    else if (isComma(str[index]))
    {
        lexeme = new Lexeme(",");
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
    else
    {
        prevIndexOpenParenthesis = false;
        std::cout << "Unknown symbol: " << str[index] << std::endl;;
        lexeme = nullptr;
    }

    index++;

    return lexeme;
}

double* Parser::getNumberInExponentForm(std::string& in, char expSymbol)
{
    double* num = new double();
    *num = std::stod(in.substr(0, in.rfind(expSymbol)));
    if (in.rfind(expSymbol) + 2 < in.size())
    {
        if (in[in.rfind(expSymbol) + 1] == '+')
        {
            for (int i = 0; i < std::stod(in.substr(in.rfind(expSymbol) + 2, in.back())); i++)
            {
                *num *= 10;
            }
        }
        else if (in[in.rfind(expSymbol) + 1] == '-')
        {
            for (int i = 0; i < std::stod(in.substr(in.rfind(expSymbol) + 2, in.back())); i++)
            {
                *num /= 10;
            }
        }
        else
        {
            std::cout << "Exponent error!" << std::endl;
            return nullptr;
        }
    }
    else
    {
        std::cout << "Exponent error!" << std::endl;
        return nullptr;
    }
    return num;
}

std::string Parser::checkLexemes(LexemeString& lexemes)
{
    std::stack<int> openParenthesis;
    std::string code = "";

    int countNums = 0;
    int countOperations = 0;
    int size = lexemes.size();

    for (int i = 0; i < lexemes.size(); i++)
    {
        if (lexemes.at(i).getType() == LexemeType::decimal)
        {
            countNums++;
        }

        if (lexemes.at(i).getType() == LexemeType::operation)
        {
            countOperations++;
            if((checkNextOpenParenthesis(lexemes, i) || checkNextStartFunction(lexemes, i)) &&
                (checkPrevOpenParenthesis(lexemes, i) || i == 0))
            {
                if (lexemes.at(i).getString() == "+")
                {
                    lexemes.erase(i);
                    i--;
                }
                else if (lexemes.at(i).getString() == "-")
                {
                    lexemes.insert(i, Lexeme(0));
                    i++;
                }
                //else
                //{
                //    code += '6';
                //    std::cout << "Operation argument error!" << std::endl;
                //}
            }
            if (!checkNextDecimal(lexemes, i) && !checkNextOpenParenthesis(lexemes, i)
                && !checkNextStartFunction(lexemes, i) || checkPrevOpenParenthesis(lexemes, i))
            {
                code += '6';
                std::cout << "Operation argument error!" << std::endl;
            }
            if (checkPrevOpenParenthesis(lexemes, i))
            {
                if (lexemes.at(i).getString() != "+" && lexemes.at(i).getString() != "-")
                {
                    code += '6';
                    std::cout << "Operation argument error!" << std::endl;
                }
            }
            if (i == 0 || lexemes.at(i - 1).getType() != LexemeType::decimal
                && lexemes.at(i - 1).getType() != LexemeType::parenthesis)
            {
                code += '6';
                std::cout << "Operation argument error!" << std::endl;
            }
        }

        if (lexemes.at(i).getType() == LexemeType::parenthesis)
        {
            if (lexemes.at(i).getString() == "(")
            {
                if (checkNextCloseParenthesis(lexemes, i))
                {
                    size = lexemes.size();
                    deleteEmptyParethesis(&lexemes, size, i);
                    while (!openParenthesis.empty())
                    {
                        openParenthesis.pop();
                    }
                    continue;
                }

                openParenthesis.push(1);

                if (multiplyDetectPrev(lexemes, i))
                {
                    lexemes.insert(i, (Lexeme("*")));
                    i++;
                }
            }
            else if (lexemes.at(i).getString() == ")")
            {
                if (openParenthesis.size() > 0)
                {
                    openParenthesis.pop();
                }
                else
                {
                    code += '1';
                    std::cout << "Parenthesis error!" << std::endl;
                }

                if (multiplyDetectNext(lexemes, i))
                {
                    lexemes.insert(i + 1, (Lexeme("*")));
                }
            }
        }

        if (lexemes.at(i).getType() == LexemeType::function)
        {
            if (lexemes.at(i).getString() == "log(")
            {
                countOperations++;
                openParenthesis.push(1);
                if (multiplyDetectPrev(lexemes, i))
                {
                    lexemes.insert(i, (Lexeme("*")));
                    i++;
                }
            }
            if (lexemes.at(i).getString() == ")")
            {
                openParenthesis.pop();
            }
        }

        if (i > 0)
        {
            if (checkDoubleNumbers(lexemes, i))
            {
                code += '3';
                std::cout << "Double numbers error!" << std::endl;;
            }
            if (checkDoubleOperations(lexemes, i))
            {
                code += '4';
                std::cout << "Double operation error!" << std::endl;;
            }
        }
    }

    for (int i = 0; i < lexemes.size(); i++)
    {
        if (lexemes.at(i).getType() == LexemeType::function)
        {
            if (lexemes.at(i).getString() == "log(")
            {
                if (!getLenghtFunction(&lexemes, i + 1))
                {
                    code += '7';
                    std::cout << "Function error!" << std::endl;
                }
            }
        }
    }

    if (openParenthesis.size() > 0)
    {
        code += '2';
        std::cout << "Parenthesis error!" << std::endl;;
    }

    if (countNums < 2 || countOperations < 1)
    {
        code += '5';
        std::cout << "Need at least two numbers and one operator! " << std::endl;;
    }

    return code;
}


void Parser::deleteEmptyParethesis(LexemeString* lexemes, int& size, int& i)
{
    lexemes->erase(i);
    lexemes->erase(i);
    size--;
    size--;
    i = -1;
}

char Parser::getExponentSymbol(const char symbol)
{
    if (symbol == 'E')
    {
        return 'E';
    }
    else if (symbol == 'e')
    {
        return 'e';
    }
    else
    {
        return NULL;
    }
}

bool Parser::checkNextCloseParenthesis(LexemeString& lexemes, int i)
{
    if (((long long)i + 1) < lexemes.size())
    {
        if (lexemes.at((long long)i + 1).getString() == ")")
        {
            return true;
        }
    }
    return false;
}

bool Parser::checkNextOpenParenthesis(LexemeString& lexemes, int i)
{
    if (((long long)i + 1) < lexemes.size())
    {
        if (lexemes.at((long long)i + 1).getString() == "(")
        {
            return true;
        }
    }
    return false;
}

bool Parser::checkPrevCloseParenthesis(LexemeString& lexemes, int i)
{
    if (((long long)i - 1) >= 0)
    {
        if (lexemes.at((long long)i - 1).getString() == ")")
        {
            return true;
        }
    }
    return false;
}

bool Parser::checkPrevOpenParenthesis(LexemeString& lexemes, int i)
{
    if (((long long)i - 1) >= 0)
    {
        if (lexemes.at((long long)i - 1).getString() == "(")
        {
            return true;
        }
    }
    return false;
}

bool Parser::checkNextOperation(LexemeString& lexemes, int i)
{
    if (((long long)i + 1) < lexemes.size())
    {
        if (lexemes.at((long long)i + 1).getType() == LexemeType::operation)
        {
            return true;
        }
    }
    return false;
}

bool Parser::multiplyDetectNext(LexemeString& lexemes, int i)
{
    if (((long long)i + 1) < lexemes.size())
    {
        if (lexemes.at((long long)i + 1).getType() == LexemeType::decimal
            || lexemes.at((long long)i - 1).getString() == "(")
        {
            return true;
        }
    }
    return false;
}

bool Parser::multiplyDetectPrev(LexemeString& lexemes, int i)
{
    if (((long long)i - 1) >= 0)
    {
        if (lexemes.at((long long)i - 1).getType() == LexemeType::decimal
            || lexemes.at((long long)i - 1).getString() == ")")
        {
            return true;
        }
    }
    return false;
}

bool Parser::checkDoubleNumbers(LexemeString& lexemes, int i)
{
    if (lexemes.at((long long)i - 1).getType() == LexemeType::decimal
        && lexemes.at(i).getType() == LexemeType::decimal)
    {
        return true;
    }
    return false;
}

bool Parser::checkDoubleOperations(LexemeString& lexemes, int i)
{
    if (lexemes.at((long long)i - 1).getType() == LexemeType::operation
        && lexemes.at(i).getType() == LexemeType::operation)
    {
        return true;
    }
    return false;
}

bool Parser::checkNextDecimal(LexemeString& lexemes, int i)
{
    if (((long long)i + 1) < lexemes.size())
    {
        if (lexemes.at((long long)i + 1).getType() == LexemeType::decimal)
        {
            return true;
        }
    }
    return false;
}

bool Parser::checkNextStartFunction(LexemeString& lexemes, int i)
{
    if (((long long)i + 1) < lexemes.size())
    {
        if (lexemes.at((long long)i + 1).getType() == LexemeType::function)
        {
            return true;
        }
    }
    return false;
}

int Parser::getLenghtFunction(LexemeString* lexemes, int i)
{
    std::stack<int> parenthesisStack;
    int startIndex = i;
    int numOfCommas = 0;
    int size = lexemes->size();
    lexemes->insert(i, Lexeme("("));
    i++;
    size++;
    while (i < lexemes->size())
    {
        if (lexemes->at(i).getType() == LexemeType::function && lexemes->at(i).getString() == "log(")
        {
            int offset = getLenghtFunction(lexemes, i+1);
            if (offset == 0)
            {
                return 0;
            }
            else
            {
                i += offset;
            }
        }
        if (lexemes->at(i).getType() == LexemeType::parenthesis && lexemes->at(i).getString() == "(")
        {
            parenthesisStack.push(1);
        }
        if (lexemes->at(i).getType() == LexemeType::parenthesis && lexemes->at(i).getString() == ")" && !parenthesisStack.empty())
        {
            parenthesisStack.pop();
        }
        if (lexemes->at(i).getType() == LexemeType::function && lexemes->at(i).getString() == ",")
        {
            if (!parenthesisStack.empty())
            {
                return 0;
            }
            else
            {
                lexemes->insert(i, Lexeme(")"));
                lexemes->insert(i+2, Lexeme("("));
                size += 2;
                i += 2;
                if (numOfCommas == 0)
                {
                    numOfCommas++;
                }
                else
                {
                    return 0;
                }
            }
        }
        if (lexemes->at(i).getType() == LexemeType::parenthesis
            && lexemes->at(i).getString() == ")" && parenthesisStack.empty()
            && numOfCommas == 1)
        {
            lexemes->insert(i, Lexeme(")"));
            return i - startIndex + 3;
        }
        i++;
    }
    return false;
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

bool Parser::isNegativeSign(const std::string str)
{
    if ((index == 0 || prevIndexOpenParenthesis)
        && ((long long)index + 1 < str.length())
        && ((isdigit(str[(long long)index + 1]) || isPoint(str[(long long)index + 1]))))
    {
        return true;
    }
    else
    {
        return false;
    }
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

bool Parser::isLogFunctionStart(std::string str)
{
    if (str == "log(")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Parser::isComma(const char symbol)
{
    if (symbol == ',')
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
    if (symbol == 'E' || symbol == 'e')
    {
        return true;
    }
    else
    {
        return false;
    }
}

//std::cout << i << std::endl;
//for (int j = 0; j < lexemes.size(); j++)
//{
//	std::cout << lexemes[j]->getString() << " ";
//}
//std::cout << std::endl;
