#include "Model.h"
#include <SFML/Graphics.hpp>
#include <iostream>

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