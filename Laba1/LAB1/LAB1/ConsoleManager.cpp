#include "ConsoleManager.h"

ConsoleManager::ConsoleManager()
{
    exOut = true;
}

ConsoleManager::~ConsoleManager()
{
}

void ConsoleManager::run()
{
	std::string str;
	while (1)
	{
		std::cout << ">>> ";
		try
		{
			std::getline(std::cin, str, '\n');
		}
		catch (...)
		{
			std::cout << "Unknown error!";
		}
		if (str == "help")
		{
			std::cout << "clear         - clear console" << std::endl;
			std::cout << "exout <1/0>   - on/off extended output" << std::endl;
			std::cout << std::endl;
		}
		else if (str == "clear")
		{
			system("cls");
		}
		else if (str == "exout 1")
		{
			exOut = true;
			std::cout << std::endl;
		}
		else if (str == "exout 0")
		{
			exOut = false;
			std::cout << std::endl;
		}
		else
		{
			execute(str);
		}
	}
}

double ConsoleManager::execute(std::string str)
{
	LexemeString lexemesAfterParse = parser.getLexemes(str);
	if (lexemesAfterParse.size() > 0)
	{
		if (exOut)
		{
			std::cout << std::endl << "After parse:" << std::endl;
			std::cout << lexemesAfterParse.toString() << std::endl;
		}
		LexemeString lexemesAfterConvert = converter.convert(lexemesAfterParse);
		if (exOut)
		{
			std::cout << "After convert:" << std::endl;
			std::cout << lexemesAfterConvert.toString() << std::endl;
		}
		try
		{
			double ans = solver.solve(lexemesAfterConvert);
			std::cout << "ANSWER: " << ans << std::endl << std::endl;
			return ans;
		}
		catch (const char* msg)
		{
			std::cout << "ERROR: " << msg << std::endl << std::endl;
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}
