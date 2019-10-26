#include "Controller.h"
#include <iostream>


int main() {
	View view;
	Model model;

	Controller controller(&model, &view);
	controller.processEvents();
}