#pragma once
#include <string>

class Model {
private:
	unsigned char* originalImage;
	unsigned char* editedImage;
	unsigned int width, heigth, size;
public:
	Model();
	bool loadImage(std::string);
	unsigned char* getImage();
	unsigned int getWidth();
	unsigned int getHeigth();
	unsigned int getSize();
	void editImage(char, unsigned int);
};