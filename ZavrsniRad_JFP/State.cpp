#include "stdafx.h"
#include "State.h"

State::State(StateData* state_data)
{
	this->stateData = state_data;
	this->window = state_data->window;
	this->supportedKeys = state_data->supportedKeys;
	this->states = state_data->states;
	this->quit = false;
	this->paused = false;
	this->keyTime = 0.f;
	this->keyTimeMax = 10.f;
}

State::~State()
{
}

//Accessors
const bool State::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}

	return false;
}

//Functions
/*
*Converts a percentage value to pixels relative to the current resolution in the x axis
*Returns the calculated pixel value
*/
const float State::p2px(const float perc)
{
	return std::floor(static_cast<float>(this->stateData->gfxSettings->resolution.width) * (perc / 100.f));
}

/*
*Converts a percentage value to pixels relative to the current resolution in the y axis
*Returns the calculated pixel value
*/
const float State::p2py(const float perc)
{
	return std::floor(static_cast<float>(this->stateData->gfxSettings->resolution.height) * (perc / 100.f));
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 50.f * dt;
	}
}
