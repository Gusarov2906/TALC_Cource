#pragma once

#if defined(CALCAPI_EXPORT) // внутри DLL
#   define CALCAPI   __declspec(dllexport)
#else // вне DLL
#   define CALCAPI   __declspec(dllimport)
#endif 

#include <iostream>
#include <iomanip>

CALCAPI double execute(std::string str);

