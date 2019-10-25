#include "Model.h"

Model::Model() {
	width = heigth = size = 0;
	originalImage = editedImage = nullptr;
}

bool Model::loadImage(std::string name) {
	width = 10;
	heigth = 10;
	size = 4 * width * heigth;
	delete[] originalImage;
	delete[] editedImage;
	originalImage = new unsigned char [size] {1};
	editedImage = new unsigned char [size] {1};
	return true;
}

void Model::editImage(int) {
	return;
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