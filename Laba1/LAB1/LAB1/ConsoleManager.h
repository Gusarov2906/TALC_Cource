#pragma once

#include <iostream>
#include "Parser.h"
#include "PolishReverseConverter.h"
#include "Solver.h"
#include <iomanip>

class ConsoleManager
{
public:
	ConsoleManager();
	~ConsoleManager();
	void run();
	double execute(std::string str);

private:
	Parser parser;
	PolishReverseConverter converter;
	Solver solver;
	bool exOut;
	std::string str;
};

