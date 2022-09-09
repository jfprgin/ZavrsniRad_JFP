#pragma once

#include"stdafx.h"
#include"MainMenuState.h"

/*=========================The Engine=============================*/
/*
*Creates the window
*Runs the game loop (update and render)
*Initializes keys
*Updates dt variable
*Manages states:
*	- Initializes StateData and State stack
*	- Initializes Main menu
*	- Pop State from stack when quit is called
*	- Renders State on the top of the stack
*	- Clears stack
*/

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

