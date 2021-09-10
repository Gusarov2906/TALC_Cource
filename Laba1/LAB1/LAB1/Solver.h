#pragma once
#include "LexemeString.h"
#include <vector>

class Solver
{
public:
    Solver();
    ~Solver();
    double solve(LexemeString lexemes);
    void oneStep(LexemeString& lexemes);
};