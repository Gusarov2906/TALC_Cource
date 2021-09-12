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

std::string LexemeString::toString()
{
    std::string res;
    for (int i = 0; i < this->lexemes.size(); i++)
    {
        if (this->lexemes[i].getType() == LexemeType::decimal)
        {
            std::string tmp = std::to_string(this->lexemes[i].getValue());
            if (tmp[tmp.size() - 1] == '0')
                for (size_t i = tmp.size() - 1; tmp[i] == '0'; i--)
                    tmp.erase(i, 1);

            if (tmp[tmp.size() - 1] == ',')
                tmp.erase(tmp.size() - 1, 1);
            res += tmp;
        }
        else
        {
            res += this->lexemes[i].getFormatedString();
        }
        res += " ";
    }
    return res;
}
