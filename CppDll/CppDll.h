// CppDll.h - Contains declarations of math functions
#pragma once

#ifdef CPPDLL_EXPORTS
#define CPPDLL_API __declspec(dllexport)
#else
#define CPPDLL_API __declspec(dllimport)
#endif

extern "C" CPPDLL_API void HelloThere();

extern "C" CPPDLL_API void posterise(unsigned char*, unsigned char*, unsigned int, unsigned int);