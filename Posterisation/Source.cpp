#include "View.h"
#include <iostream>


int main() {
	Model model;
	View view(&model);

	view.processEvents();
}
