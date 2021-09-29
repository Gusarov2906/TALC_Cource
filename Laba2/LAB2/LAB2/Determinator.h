#pragma once

#include "FinalStateMachine.h"

#include <stack>

class Determinator
{
public:
    Determinator();

    FinalStateMachine determinate(FinalStateMachine& fsm);
};

