#include "View.h"

#define WINDOWHEIGTH 480
#define WINDOWWIDTH 640

View::View() {
	window = new sf::RenderWindow(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGTH), "Posterise");
	window->setFramerateLimit(10);
	image.create(640, 480, sf::Color::Black);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}

void View::SetSprite(unsigned int width, unsigned int heigth, unsigned char* pixelArray) {
	image.create(width, heigth, pixelArray);
	texture.loadFromImage(image);
	sprite.setScale(sf::Vector2f(WINDOWWIDTH / (float)width, WINDOWWIDTH / (float)width));
	sprite.setOrigin({ (float)width / 2, (float)heigth / 2 });
	sprite.setPosition({ WINDOWWIDTH / 2, WINDOWHEIGTH / 2 });
}

void View::Display() {
	window->clear();
	window->draw(sprite);
	window->display();
}

sf::RenderWindow* View::getWindow() {
	return window;
}