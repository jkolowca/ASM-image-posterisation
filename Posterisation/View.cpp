#include "View.h"

#define WINDOWHEIGTH 480
#define WINDOWWIDTH 640

View::View() {
	window = new sf::RenderWindow(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGTH), "Posterise");
	window->setFramerateLimit(10);
}

void View::SetSprite(unsigned int width, unsigned int heigth, unsigned char* pixelArray) {
	image.create(width, heigth, pixelArray);
	texture.loadFromImage(image);

	float scale = calculateScale(width, heigth);
	sprite.setTexture(texture);
	sprite.setScale({scale, scale});

	sprite.setPosition({ ((float)window->getSize().x - ((float)width*scale)) / 2, 0 });
}

void View::Display() {
	window->clear();
	window->draw(sprite);
	window->display();
}

sf::RenderWindow* View::getWindow() {
	return window;
}

float View::calculateScale(unsigned int width, unsigned int heigth) {
	float scale;
	if ((float)width / (float)heigth > (float)window->getSize().x / (float)window->getSize().y) {
		scale = (float)window->getSize().x / (float)width;
	}
	else {
		scale = (float)window->getSize().y / (float)heigth;
	}
	return scale;
}