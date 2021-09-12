#include "ConsoleManager.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	ConsoleManager consoleManger;
	consoleManger.run();
	return 0;
}