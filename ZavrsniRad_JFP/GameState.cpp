#include "stdafx.h"
#include "GameState.h"

//Private functions
void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0, 0,
			this->stateData->gfxSettings->resolution.width,
			this->stateData->gfxSettings->resolution.height
		)
	);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::GAME_STATE::COULD NOT LOAD FONT");
	}
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_IDLE"].loadFromFile("Resources/Images/Sprites/Player/test.png"))
	{
		throw "ERROR::GAME_STATE::COULD NOT LOAD PLAYER IDLE TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	this->pMenu = new PauseMenu(*this->window, this->font);
	this->pMenu->addButton("QUIT", 800.f, "Quit");
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_IDLE"]);
}

GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initDeferredRender();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
}

GameState::~GameState()
{
	delete this->player;
	delete this->pMenu;
}

//Functions
void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime())
	{
		if (!this->paused)
		{
			this->pauseState();
		}
		else
		{
			this->unpauseState();
		}
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
	{
		this->player->move(-1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
	{
		this->player->move(1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
	{
		this->player->move(0.f, -1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
	{
		this->player->move(0.f, 1.f, dt);
	}

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
	{
		this->endState();
	}*/
}

void GameState::updatePauseMenuButtons()
{
	if (this->pMenu->isButtonPressed("QUIT"))
	{
		this->endState();
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateKeyTime(dt);

	if (!this->paused)	//Unpaused update
	{
		this->updatePlayerInput(dt);

		this->player->update(dt);
	}
	else			//Paused update
	{
		this->pMenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	this->renderTexture.clear();

	this->player->render(this->renderTexture);

	if (this->paused)		//Pause menu render
	{
		this->pMenu->render(this->renderTexture);
	}

	//Final render
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
