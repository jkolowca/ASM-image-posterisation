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
	userInput << (char)e.text.unicode;
}

void Controller::processInput() {
	unsigned int par;
	char lib;
	try {
		userInput >> lib >> par;
		std::cout << lib << " " << par << std::endl;
	}
	catch (...) {
		std::cout << "Invalid argument" << std::endl;
		par = 255;
		lib = 'a';
	}
	model->editImage(lib, par);
	view->SetSprite(model->getWidth(), model->getHeigth(), model->getImage());
	userInput.clear();
}