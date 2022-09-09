#pragma once

#include"Player.h"
#include"GraphicsSettings.h"

class Player;
class GraphicsSettings;
class State;

//DONE

/*
*Game (the engine) will only have one StateData object
*StateData has all the information we send to other states
*
*State:	- used for puse, unpause, quit and endState
*		- will keep track of the original StateData with "StateData* stateData"
*		- updates mouse position
*		- updates KeyTime
*/
class StateData 
{
public:
	StateData() {};

	//Variables
	sf::RenderWindow* window;
	GraphicsSettings* gfxSettings;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
};

class State
{
private:

protected:
	//Variables
	StateData* stateData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	bool gameOver;
	float keyTime;
	float keyTimeMax;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	std::map<std::string, sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;

public:
	State(StateData* state_data);
	virtual ~State();

	//Accessors
	const bool& getQuit() const;
	const bool getKeyTime();
	
	//Functions
	void endState();
	void pauseState();
	void unpauseState();
	virtual void resetGui() = 0;

	virtual void updateMousePositions();
	virtual void updateKeyTime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

