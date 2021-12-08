#include "ConsoleManagerExport.h"
#include "ConsoleManager.h"

double execute(std::string str)
{
    ConsoleManager consoleManager;
    return consoleManager.execute(str);
}
