#include "Solver.h"
#define DOUBLE_CONST 0.0

Solver::Solver()
{
}

Solver::~Solver()
{
}

double Solver::solve(LexemeString lexemes)
{
    
    while (lexemes.size() > 1)
    {
        oneStep(lexemes);
    }
    return lexemes.at(0).getValue();
}

void Solver::oneStep(LexemeString& lexemes)
{
    for (int i = 0; i < lexemes.size(); i++)
    {
        if (lexemes.at(i).getType() == LexemeType::operation)
        {
            double a = lexemes.at(i - 2).getValue();
            double b = lexemes.at(i - 1).getValue();
            std::string operation = lexemes.at(i).getString();
            Lexeme* lexeme;
            if (operation == "+")
            {
                lexeme = new Lexeme(a + b);
                lexemes.erase(i);
                lexemes.erase(i - 1);
                lexemes.erase(i - 2);
                lexemes.insert(i - 2, *lexeme);
                i = 0;
            }
            else if (operation == "-")
            {
                lexeme = new Lexeme(a - b);
                lexemes.erase(i);
                lexemes.erase(i - 1);
                lexemes.erase(i - 2);
                lexemes.insert(i - 2, *lexeme);
                i = 0;
            }
            else if (operation == "*")
            {
                lexeme = new Lexeme(a * b);
                lexemes.erase(i);
                lexemes.erase(i - 1);
                lexemes.erase(i - 2);
                lexemes.insert(i - 2, *lexeme);
                i = 0;
            }
            else if (operation == "/")
            {
                lexeme = new Lexeme(a / b);
                lexemes.erase(i);
                lexemes.erase(i - 1);
                lexemes.erase(i - 2);
                lexemes.insert(i - 2, *lexeme);
                i = 0;
            }
            else if (operation == "^")
            {
                lexeme = new Lexeme(pow(a, b));
                lexemes.erase(i);
                lexemes.erase(i - 1);
                lexemes.erase(i - 2);
                lexemes.insert(i - 2, *lexeme);
                i = 0;
            }
            else
            {
                lexeme = nullptr;
            }
        }
    }
    //if (lexeme != nullptr)
    //{
    //    delete lexeme;
    //}
}
