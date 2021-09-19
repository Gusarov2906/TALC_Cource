#include "ConsoleManager.h"
#include <iostream>

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	setlocale(LC_NUMERIC, "C");
	std::cout << "ConsoleMath by @gusarov2906" << std::endl;
	std::cout << "Write 'help' to show commands or 'exit' to stop program." << std::endl;
	ConsoleManager consoleManger;
	consoleManger.run();
	return 0;
}