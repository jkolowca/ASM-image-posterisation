#include "View.h"

#define WINDOWHEIGTH 800
#define WINDOWWIDTH 1200

View::View(Model* m) {
	model = m;
	window = new sf::RenderWindow(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGTH), "Posterise", sf::Style::Close);
	window->setFramerateLimit(10);
	window->setVerticalSyncEnabled(true);
	ImGui::SFML::Init(*window);
	//window->resetGLStates(); // call it if you only draw ImGui. Otherwise not needed.
	// model->loadImage("pic.bmp");
	// SetSprite(model->getWidth(), model->getHeigth(), model->getImage());
}

void View::setSprite(unsigned int width, unsigned int heigth, unsigned char* pixelArray) {
	image.create(width, heigth, pixelArray);
	texture.loadFromImage(image);

	float scale = calculateScale(width, heigth);
	sprite.setTexture(texture);
	sprite.setScale({scale, scale});

	sprite.setPosition({ ((float)window->getSize().x - ((float)width*scale) + 250) / 2, 
						 ((float)window->getSize().y - ((float)heigth*scale))/2 });
}

void View::display() {		

		ImGui::SFML::Update(*window, deltaClock.restart());

		
		ImGuiWindowFlags window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoTitleBar;
		window_flags |= ImGuiWindowFlags_NoScrollbar;
		window_flags |= ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoResize;
		
		if (!ImGui::Begin("Menu", NULL, window_flags))
		{
			// Early out if the window is collapsed, as an optimization.
			ImGui::End();
			return;
		}
		ImGui::PushItemWidth(235);

		ImGui::Text("MENU", IMGUI_VERSION);
		ImGui::Dummy(ImVec2(0.0f, 20.0f));

		if (ImGui::CollapsingHeader("Help"))
		{
			"1. \n2. hit Test button";
			
			ImGui::Text("To process image:");
			ImGui::BulletText("set path to image \n");
			ImGui::BulletText("set no of progs in between\n 1 and 255\n");
			ImGui::BulletText("set no of threads or\n select auto \n");
			ImGui::BulletText("hit Run button");
			ImGui::Separator();

			ImGui::Text("To save processed image:");
			ImGui::BulletText("set path to new image,\n if it exists will be changed,\n otherwise created");
			ImGui::BulletText("hit Save button");
			
			ImGui::Separator();

			ImGui::Text("To run set of test \nusing both libraries \nand multiple thread settings::");
			ImGui::BulletText("set path to file where \nlogs will be saved");
			ImGui::BulletText("hit Test button");
			ImGui::Separator();
			
		}

		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		ImGui::Text("Path to image:");
		ImGui::InputText("##input",inputFileName, 255, ImGuiInputTextFlags_CharsNoBlank);
		
		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		if(ImGui::Button("Load", { 235,20 })) {
			model->loadImage(inputFileName);
			setSprite(model->getWidth(), model->getHeigth(), model->getImage());
		}

		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		ImGui::Separator();

		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		ImGui::Text("Number of color levels:");
		ImGui::SliderInt("slider parameter", &parameter, 1, 255);
		
		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		ImGui::Text("Number of threads:");
		ImGui::SliderInt("slider threads", &threads, 1, 65);
		ImGui::Checkbox("auto adjust", &autoThreads);

		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		ImGui::Text("Library used:");
		ImGui::Combo("library", &library, "Asm\0Cpp\0");

		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		if (ImGui::Button("Process", { 235, 20 })) {
			if (autoThreads) model->editImage(library ? 'c' : 'a', parameter, 0);
			else model->editImage(library ? 'c' : 'a', parameter, threads);
			setSprite(model->getWidth(), model->getHeigth(), model->getImage());
		}

		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		ImGui::Separator();

		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		ImGui::Text("Path to new file:");
		ImGui::InputText("##output", outputFileName, 255, ImGuiInputTextFlags_CharsNoBlank);

		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		if(ImGui::Button("Save", { 235, 20 })) {
			texture.copyToImage().saveToFile(outputFileName);
		}

		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		ImGui::Separator();

		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		ImGui::Text("Path to log file:");
		ImGui::InputText("##test", logFileName, 255, ImGuiInputTextFlags_CharsNoBlank);

		ImGui::Dummy(ImVec2(0.0f, 20.0f));
		if(ImGui::Button("Run tests", { 235, 20 })) {
			model->runTests(logFileName);
		}

		ImGui::End();

		window->clear(sf::Color(80,80,80)); // fill background with color
		window->draw(sprite);
		ImGui::SFML::Render(*window);
		window->display();
}

void View::processEvents() {
	sf::Event event;
	while (window->isOpen()) {
		while (window->pollEvent(event)) {
		ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed)
				window->close();
		}
		display();
	}

	ImGui::SFML::Shutdown();
}


float View::calculateScale(unsigned int width, unsigned int heigth) {
	float scale;
	if ((float)width / (float)heigth > ((float)window->getSize().x - 250)/ (float)window->getSize().y) {
		scale = ((float)window->getSize().x - 250) / (float)width;
	}
	else {
		scale = (float)window->getSize().y / (float)heigth;
	}
	return scale;
}
