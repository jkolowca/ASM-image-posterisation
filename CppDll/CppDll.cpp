// CppDll.cpp
#include "pch.h" 
#include "CppDll.h"
#include <Windows.h>


void HelloThere()
{
	int i = MessageBox(GetForegroundWindow(), (LPCWSTR)L"Hello There!", (LPCWSTR)L"Cpp",MB_OK);
}

void posterise(unsigned char* input, unsigned char* output, unsigned int param, unsigned int size) {

	unsigned short out, in, hpar, par;
	par = 255 / param;
	if (par == 0) return;
	hpar = par / 2;

	for (unsigned int i = 0; i < size; i++) {
		in = *input++;
		out = (in + hpar) - (in + hpar) % par;
		if (out > 255) out = 255;
		output[i] = (unsigned char)out;
	}
}
