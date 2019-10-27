#pragma once
#include "Model.h"
#include "View.h"
#include <sstream>

class Controller {
private:
	Model* model;
	View* view;

	std::stringstream userInput;
public:
	Controller(Model*, View*);
	void processEvents();
	void processTextEvent(sf::Event);
	void processInput();
};