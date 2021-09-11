#pragma once
#include "LexemeString.h"
#include <vector>

class Solver
{
public:
    Solver();
    ~Solver();
    double solve(LexemeString lexemes);
    void swapToAnswer(LexemeString& lexemes, int& index, Lexeme ans);
};