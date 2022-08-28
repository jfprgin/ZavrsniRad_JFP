#pragma once

#include"stdafx.h"
#include"MainMenuState.h"

class Game
{
private:
	//Variables
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::Event sfEvent;

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
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
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

