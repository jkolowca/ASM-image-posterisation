#include "Controller.h"
#include <iostream>

Controller::Controller(Model* m, View* v) {
	model = m;
	view = v;
	model->loadImage("pic.bmp");
	view->SetSprite(model->getWidth(), model->getHeigth(), model->getImage());
}

void Controller::processEvents() {
	sf::RenderWindow* window = view->getWindow();

	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed && event.key.code == 58) {
				processInput();
			}
			if (event.type == sf::Event::TextEntered) {
				processTextEvent(event);
			}
			if (event.type == sf::Event::Closed)
				window->close();
		}
	view->Display();
	}
}

void Controller::processTextEvent(sf::Event e) {
	input += e.text.unicode;
}

void Controller::processInput() {
	int par;
	try {
		par = std::stoi(input);
	}
	catch (...) {
		std::cout << "Invalid argument" << std::endl;
		par = 255;
	}
	model->editImage(par);
	view->SetSprite(model->getWidth(), model->getHeigth(), model->getImage());
	input.clear();
}