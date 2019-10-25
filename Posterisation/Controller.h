#pragma once
#include "Model.h"
#include "View.h"

class Controller {
private:
	Model* model;
	View* view;

	std::string input;
public:
	Controller(Model*, View*);
	void processEvents();
	void processTextEvent(sf::Event);
	void processInput();
};