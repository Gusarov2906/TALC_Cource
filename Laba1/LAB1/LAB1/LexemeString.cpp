#include "LexemeString.h"

LexemeString::LexemeString()
{

}

LexemeString::LexemeString(std::vector<Lexeme> lexemes)
{
    for (int i = 0; i < lexemes.size(); i++)
    {
        this->lexemes.push_back(lexemes[i]);
    }
}

LexemeString::~LexemeString()
{
    //for (int i = 0; i < lexemes.size(); i++)
    //{
    //    delete lexemes[i];
    //}
}

void LexemeString::push_back(Lexeme lexeme)
{
    this->lexemes.push_back(lexeme);
}

void LexemeString::insert(int i, Lexeme lexeme)
{
    lexemes.insert(lexemes.begin() + i, lexeme);
}

void LexemeString::clear()
{
    this->lexemes.clear();
}

int LexemeString::size()
{
    return lexemes.size();
}

Lexeme LexemeString::at(int i)
{
    if (i < this->lexemes.size() && i >= 0)
    {
        return this->lexemes[i];
    }
    else
    {
        return Lexeme("default");
    }
}

void LexemeString::erase(int i)
{
    this->lexemes.erase(this->lexemes.begin() + i);
}
