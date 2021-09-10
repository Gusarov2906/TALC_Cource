#pragma once
#include "Lexeme.h"
#include <vector>

class Solver
{
public:
    Solver();
    ~Solver();
    double solve(std::vector<Lexeme*> lexemes);
};