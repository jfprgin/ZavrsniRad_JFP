#pragma once

#include"stdafx.h"

//DONE
class GraphicsSettings
{
private:

public:
	GraphicsSettings();
	~GraphicsSettings();

	//Variables
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned framerateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	//Functions
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};