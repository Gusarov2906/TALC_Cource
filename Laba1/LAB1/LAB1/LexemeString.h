#pragma once
#include "Lexeme.h"
#include <vector>
#include <string>

class LexemeString
{
public:
    LexemeString();
    LexemeString(std::vector<Lexeme> lexemes);
    ~LexemeString();

    void push_back(Lexeme lexeme);
    void insert(int i, Lexeme lexeme);
    void clear();
    int size();
    Lexeme at(int i);
    void erase(int i);
    std::string toString();
protected:
    std::vector<Lexeme> lexemes;

};
