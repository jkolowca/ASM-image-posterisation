#include "Model.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <thread>
#include <fstream>

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

void Model::editImage(char libraryType, unsigned int param, unsigned int threads) {
	if (param == 0) return;

	HINSTANCE lib;
	if (libraryType == 'a') {
		lib = LoadLibrary("AssemblerDll.dll");
	}
	else if (libraryType == 'c') {
		lib = LoadLibrary("CppDll.dll");
	}
	else return;

	if(threads==0) threads = std::thread::hardware_concurrency();
	posterise poster;
	if (lib) {
		poster = (posterise)GetProcAddress(lib, "posterise");
		if (poster) {

			std::vector<std::thread> thr;
			int length = size / threads;

			auto start = std::chrono::high_resolution_clock::now();

			for (unsigned int i = 0; i < threads; i++) {
				thr.push_back(std::thread(poster, originalImage + i * length, editedImage + i * length, param, length));
			}
			for (auto iter = thr.begin(); iter != thr.end(); iter++) {
				iter->join();
			}

			auto stop = std::chrono::high_resolution_clock::now();

			duration = duration_cast<milliseconds>(stop - start).count();
		}
	}
	
}

void Model::runTests(std::string logFile) {
	std::ofstream myfile;
	myfile.open(logFile);
	myfile << width << "x" << heigth << "\n";
	myfile << "asm:\n";
	for (unsigned int i = 1; i < 66; i++) {
		editImage('a', 2, i);
		myfile << duration << "\n";
	}
	myfile << "cpp:\n";
	for (unsigned int i = 1; i < 66; i++) {
		editImage('c', 2, i);
		myfile << duration << "\n";
	}
	myfile.close();
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