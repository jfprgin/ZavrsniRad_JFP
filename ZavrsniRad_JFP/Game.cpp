#include "stdafx.h"
#include "Game.h"

//Private functions
//Initalizer functions
void Game::initVariables()
{
	this->window = nullptr;

	this->dt = 0.f;

}

void Game::initGraphicsSettings()
{
	this->gfxSettings.loadFromFile("Config/graphics.ini");
}

void Game::initWindow()
{
	/*Create SFML Window*/
	if (this->gfxSettings.fullscreen)
	{
		this->window = new sf::RenderWindow(
			this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Fullscreen,
			this->gfxSettings.contextSettings);
	}
	else
	{
		this->window = new sf::RenderWindow(this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Titlebar | sf::Style::Close,
			this->gfxSettings.contextSettings);
	}
	
	this->window->setFramerateLimit(this->gfxSettings.framerateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();
}


void Game::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
}

void Game::initStates()
{
	//Initialize Main menu state
	this->states.push(new MainMenuState(&this->stateData));
}

//Constructor and Destructor
Game::Game()
{
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

//Functions
void Game::endApplication()
{
	std::cout << "Ending application!" << std::endl;
}

void Game::run()
{
	/*Game loop -> update dt, update and render game*/
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}

void Game::updateDt()
{
	/*Updates the dt variable with the time it takes to update and render one frame so that we move framerate independently.*/
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	//Checks if close is pressed
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}
	}
}

void Game::update()
{
	/*Check if states stack is empty
	*	- If it is -> end application
	*	- If it isn't -> check if player has exited state and pop the state on top of stack
	*/
	this->updateSFMLEvents();

	if (!this->states.empty() && this->window->hasFocus())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();

			if (this->states.size() > 0)
			{
				//this->initGraphicsSettings();
				//this->initStateData();
				this->states.top()->resetGui();
				this->dt = 0.f;
			}
			
		}
	}
	//Application end
	else
	{
		this->endApplication();
		this->window->close();
	}
}

void Game::render()
{
	// First clear window and then render the state on top of stack
	this->window->clear();

	//Render items
	if (!this->states.empty())
	{
		this->states.top()->render(this->window);
	}

	this->window->display();
}
