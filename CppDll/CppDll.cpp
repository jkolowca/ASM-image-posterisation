// CppDll.cpp
#include "pch.h" 
#include "CppDll.h"
#include <Windows.h>


void HelloThere()
{
	int i = MessageBox(GetForegroundWindow(), (LPCWSTR)L"Hello There!", (LPCWSTR)L"Cpp",MB_OK);
}