#pragma once
#include <SFML/Graphics.hpp>

class View {
private:
	sf::RenderWindow* window;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Image image;
public:
	View();
	void Display();
	void SetSprite(unsigned int width, unsigned int heigth, unsigned char* pixelArray);
	sf::RenderWindow* getWindow();
};