#pragma once

#include"stdafx.h"
#include"MainMenuState.h"

class Game
{
private:
	//Variables
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Delta Time
	sf::Clock dtClock;
	float dt;

	//Window
	sf::RenderWindow* window;

	//Private functions
	//Initialization
	void initVariables();
	void initWindow();
	void initKeys();
	void initStates();


public:
	//Constructor and Destructor
	Game();
	~Game();

	//Functions
	void endApplication();

	//Update
	void updateDt();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Run
	void run();
};

