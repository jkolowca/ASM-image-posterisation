#pragma once
#include <string>
#include <chrono>

using namespace std::chrono;
class Model {
private:
	unsigned char* originalImage;
	unsigned char* editedImage;
	unsigned int width, heigth, size;
	int duration;
public:
	Model();
	void runTests(std::string);
	bool loadImage(std::string);
	unsigned char* getImage();
	unsigned int getWidth();
	unsigned int getHeigth();
	unsigned int getSize();
	void editImage(char, unsigned int, unsigned int);
};