#include "Solver.h"
#define DOUBLE_CONST 0.0
#include <iostream>

Solver::Solver()
{
}

Solver::~Solver()
{
}

double Solver::solve(LexemeString lexemes)
{
    bool specificOperation = true;
    double a;
    double b;
    Lexeme* lexeme = nullptr;

    for (int i = 0; i < lexemes.size(); i++)
    {
        if (lexemes.at(i).getType() == LexemeType::operation
            || lexemes.at(i).getType() == LexemeType::function)
        {
            a = lexemes.at(i - 2).getValue();
            b = lexemes.at(i - 1).getValue();
            std::string operation = lexemes.at(i).getString();
            if (operation == "+")
            {
                lexeme = new Lexeme(a + b);
            }
            else if (operation == "-")
            {
                lexeme = new Lexeme(a - b);
            }
            else if (operation == "*")
            {
                lexeme = new Lexeme(a * b);
            }
            else if (operation == "/")
            {
                if (b == 0)
                {
                    throw "Division by zero!";
                }
                lexeme = new Lexeme(a / b);
            }
            else if (operation == "^")
            {
                //if (b < 0 && (b - floor(b) == 0))
                //{
                //    throw "The base of the logarithm must be greater than zero and must not be equal to one!";
                //}
                double res = pow(a, b);
                if (res == res)
                {
                    lexeme = new Lexeme(pow(a, b));
                }
                else
                {
                    throw "Exponentiation error!";
                }
            }
            else if (operation == "log(")
            {
                if (log10(a) == 1 || log10(a) == 0)
                {
                    throw "The base of the logarithm must be greater than zero and must not be equal to one!";
                }
                if (a <= 0 || b <= 0)
                {
                    throw "The number of the logarithm must be positive!";
                }
                lexeme = new Lexeme(log10(b) / log10(a));
            }
            else
            {
                specificOperation = false;
            }
            if (specificOperation)
            {
                swapToAnswer(lexemes, i, *lexeme);
                delete lexeme;
            }
        }
    }
    if (lexemes.size() == 1)
    {
        return lexemes.at(0).getValue();
    }
    else
    {
        return NULL;
    }
}

void Solver::swapToAnswer(LexemeString& lexemes, int& index, Lexeme ans)
{
    lexemes.erase(index);
    lexemes.erase(index - 1);
    lexemes.erase(index - 2);
    lexemes.insert(index - 2, ans);
    index = 0;
}
