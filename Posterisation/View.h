#pragma once
#include <SFML/Graphics.hpp>
#include "Model.h"
#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

class View {
private:
	sf::RenderWindow* window;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Image image;
	sf::Color bgColor;
	Model* model;
	char inputFileName[255] = "";
	char outputFileName[255] = "";
	char logFileName[255] = "";
	int parameter = 255;
	int threads = 65;
	int library = 0;
	bool autoThreads = false;
	sf::Clock deltaClock;
	void display();
	void setSprite(unsigned int width, unsigned int heigth, unsigned char* pixelArray);
	float calculateScale(unsigned int, unsigned int);
public:
	View(Model*);
	void processEvents();
};