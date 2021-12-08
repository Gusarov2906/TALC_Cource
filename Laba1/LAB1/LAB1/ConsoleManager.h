#pragma once
#define CALCAPI_EXPORT

#if defined(CALCAPI_EXPORT) // внутри DLL
#   define CALCAPI   __declspec(dllexport)
#else // вне DLL
#   define CALCAPI   __declspec(dllimport)
#endif 

#include <iostream>
#include "Parser.h"
#include "PolishReverseConverter.h"
#include "Solver.h"
#include <iomanip>

class CALCAPI ConsoleManager
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

