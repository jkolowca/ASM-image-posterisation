#include "Controller.h"
#include <iostream>

Controller::Controller(Model* m, View* v) {
	model = m;
	view = v;
}

void Controller::processEvents() {
	sf::RenderWindow* window = view->getWindow();

	int par = 0;
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				processKeyEvent(event);
			}
			if (event.type == sf::Event::Closed)
				window->close();
		}
	}
}

void Controller::processKeyEvent(sf::Event) {

}