#include "stdafx.h"
#include "GameState.h"

GameState::GameState(sf::RenderWindow* window)
	: State(window)
{
}

GameState::~GameState()
{
}

void GameState::endState()
{
}

//Functions
void GameState::update(const float& dt)
{
}

void GameState::render(sf::RenderTarget* target)
{
}
