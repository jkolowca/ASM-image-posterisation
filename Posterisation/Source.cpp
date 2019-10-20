#include <iostream>
#include <Windows.h>

typedef void (__stdcall *HelloThere)();

int main(int argc, char* argv[]) {
	HINSTANCE libA = LoadLibrary("AssemblerDll.dll");
	HINSTANCE libC = LoadLibrary("CppDll.dll");
	HelloThere helloA, helloC;

	if (libA && libC) {
		helloA = (HelloThere)GetProcAddress(libA, "HelloThere");
		helloC = (HelloThere)GetProcAddress(libC, "HelloThere");
		if (helloA && helloC) {
			int i;
			std::cout << "1 - assembler function\n2- cpp function"<<std::endl;
			while (std::cin >> i) {
				if (i == 1) helloA();
				if (i == 2)helloC();
			}
		}
	}

	return 0;
}