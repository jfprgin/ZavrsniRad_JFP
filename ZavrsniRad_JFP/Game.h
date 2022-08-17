#pragma once

#include"stdafx.h"
#include"GameState.h"

class Game
{
private:
	//Variables
	sf::Event sfEvent;

	std::stack<State*> states;

	//Delta Time
	sf::Clock dtClock;
	float dt;

	//Window
	sf::RenderWindow* window;

	//Private functions
	void initWindow();
	void initStates();


public:
	//Constructor and Destructor
	Game();
	~Game();

	//Functions
	void run();

	void updateDt();
	void updateSFMLEvents();

	void update();
	void render();
};

