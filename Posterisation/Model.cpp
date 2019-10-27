#include "Model.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <thread>

typedef void(__stdcall* posterise)(unsigned char*, unsigned char*, unsigned int, unsigned int);

Model::Model() {
	width = heigth = size = 0;
	originalImage = editedImage = nullptr;
}

bool Model::loadImage(std::string name) {
	sf::Image img;
	if (!img.loadFromFile(name)) {
		std::cout << "failed loading image";
		return false;
	}
	width = img.getSize().x;
	heigth = img.getSize().y;
	size = 4 * width * heigth;

	originalImage = new unsigned char[size];
	editedImage = new unsigned char[size];

	const unsigned char* pixptr;
	pixptr = img.getPixelsPtr();

	for (unsigned int i = 0; i < size; i++) {
		originalImage[i] = editedImage[i] = *pixptr++;
	}

	return true;
}

void Model::editImage(char libraryType, unsigned int param) {
	if (param == 0) return;

	HINSTANCE lib;
	if (libraryType == 'a') {
		lib = LoadLibrary("AssemblerDll.dll");
	}
	else if (libraryType == 'c') {
		lib = LoadLibrary("CppDll.dll");
	}
	else return;

	unsigned int threads = std::thread::hardware_concurrency();
	posterise poster;

	if (lib) {
		poster = (posterise)GetProcAddress(lib, "posterise");
		if (poster) {
			std::vector<std::thread> thr;
			for (unsigned int i = 0; i < threads; i++) {
				thr.push_back(std::thread(poster, originalImage + i * size / threads, editedImage + i * size / threads, param, size / threads));
			}
			for (auto iter = thr.begin(); iter != thr.end(); iter++) {
				iter->join();
			}
		}
	}
}

unsigned char* Model::getImage() {
	return editedImage;
}

unsigned int Model::getWidth() {
	return width;
}

unsigned int Model::getHeigth() {
	return heigth;
}

unsigned int Model::getSize() {
	return size;
}