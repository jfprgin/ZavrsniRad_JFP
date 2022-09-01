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

	//TEST!
	std::string enemyTexturePath = "Resources/Images/Sprites/Enemy/enemy" + std::to_string(this->rng.getInt(1, 8)) + ".png";

	if (!this->textures["ENEMY"].loadFromFile("Resources/Images/Sprites/Enemy/enemy.png"))
	{
		throw "ERROR::GAME_STATE::COULD NOT LOAD PLAYER IDLE TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	this->pMenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);
	this->pMenu->addButton("QUIT", gui::p2py(74.f, vm), gui::p2px(13.f, vm), gui::p2py(6.f, vm), gui::calcCharSize(vm), "Quit");
}

void GameState::initGameOver()
{
	this->gOver = new GameOver(this->stateData->gfxSettings->resolution, this->font, this->player->getScore());
	this->gOver->addButton("QUIT", gui::p2py(74.f, vm), gui::p2px(13.f, vm), gui::p2py(6.f, vm), gui::calcCharSize(vm), "Quit");
}

void GameState::initPlayers()
{
	this->player = new Player(gui::p2px(50.f, vm), gui::p2py(50.f, vm), this->textures["PLAYER_IDLE"]);
}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, this->stateData->gfxSettings->resolution);
}

void GameState::initEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures, *this->player);
}

//UREDITI
GameState::GameState(StateData* state_data)
	: State(state_data), vm(this->stateData->gfxSettings->resolution),
	maxEnemy(50), currentEnemyLimit(4), enemySpawnInterval(4.f),
	enemySpawnIntervalMin(1.5f), difficultyIncreaseInterval(25.f), gameOver(false)
{
	this->initDeferredRender();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
	this->initPlayerGUI();
	this->initEnemySystem();

	this->enemySpawnClock.restart();
	this->difficultyIncreaseClock.restart();
}

GameState::~GameState()
{
	delete this->pMenu;
	delete this->player;
	delete this->playerGUI;
	delete this->enemySystem;

	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}
}

//Functions
/*void GameState::SpawnEnemy()
{
	float minX = static_cast<float>(this->stateData->gfxSettings->resolution.width)  / 2.f;
	float maxX = static_cast<float>(this->stateData->gfxSettings->resolution.width);
	float maxY = static_cast<float>(this->stateData->gfxSettings->resolution.height) - 90.f;

	float xPos = this->rng.getFloat(minX, maxX);
	float yPos = this->rng.getFloat(55.f, maxY);
	float speed = this->rng.getFloat(1.f, 5.f);

	this->enemies.emplace_back(xPos, yPos, this->textures["ENEMY"], speed);
}*/

void GameState::IncreaseDifficulty()
{
	if (this->difficultyIncreaseClock.getElapsedTime().asSeconds() > this->difficultyIncreaseInterval)
	{
		if (this->currentEnemyLimit < this->maxEnemy)
			this->currentEnemyLimit++;

		if (this->enemySpawnInterval > this->enemySpawnIntervalMin)
			this->enemySpawnInterval -= 0.5f;

		this->difficultyIncreaseClock.restart();
	}
}

void GameState::ClearObjects()
{
	//Player bullet GC
	if (!this->player->getBullets().empty())
	{
		for (auto bullet = this->player->getBullets().begin(); bullet != this->player->getBullets().end(); ++bullet)
		{
			if ((bullet->getPosition().x < 0 ||
				bullet->getPosition().y < 0 ||
				bullet->getPosition().x > window->getSize().x ||
				bullet->getPosition().y > window->getSize().y) || this->gameOver)
			{
				this->player->getBullets().erase(bullet);
				break;
			}
		}
	}
	/*
	*	POGLEDAJ!!!!!!!!
	*	POGLEDAJ!!!!!!!!
	*/
	/*
	//Enemy GC
	for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it)
	{
		if (it->getPosition().x < -100)
		{
			if (!it->isDestoryComplete())
			{
				//If player missed the enemy takes 1 damage
				this->player->loseHP(1);
			}

			//vector::erase kullanmiyoruz cunku erase() vector degerlerini kopyaliyor.
			//kopyalanan enemy degerleri de o sirada her hangi bir enemy sound playing
			//durumunda sesi erken kesiyor.
			std::swap(*it, this->enemies.back());
			this->enemies.pop_back();
			break;
		}
	}*/
}

void GameState::updateCollision()
{
	//Player world collision
	//Left
	if (this->player->getGlobalBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getGlobalBounds().top);
		this->player->stopVelocityX();
	}
	//Right
	else if (this->player->getGlobalBounds().left + this->player->getGlobalBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(window->getSize().x - this->player->getGlobalBounds().width, this->player->getGlobalBounds().top);
		this->player->stopVelocityX();
	}
	//Top
	if (this->player->getGlobalBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getGlobalBounds().left, 0.f);
		this->player->stopVelocityY();
	}
	//Bottom
	else if (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getGlobalBounds().left, window->getSize().y - this->player->getGlobalBounds().height);
		this->player->stopVelocityY();
	}

	/*//Player & enemy collision check
	auto playerBox = this->player->getGlobalBounds();
	for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it)
	{
		auto enemyBox = (*it).getGlobalBounds();
		if (enemyBox.intersects(playerBox) && (!(*it).isDestoryComplete()))
		{
			this->player->loseHP((*it).getHP());
			(*it).loseHP((*it).getHP());
			break;
		}
	}*/

	//Bullet & enemy collision check
	/*for (auto enemy = this->enemies.begin(); enemy != this->enemies.end(); ++enemy)
	{
		if (!(*enemy).isDestoryComplete())
		{
			if (!this->player->getBullets().empty())
			{
				for (auto bullet = this->player->getBullets().begin(); bullet != this->player->getBullets().end(); ++bullet)
				{
					if ((*bullet).getGlobalBounds().intersects(enemy->getGlobalBounds()))
					{
						enemy->loseHP(this->player->getDamage());
						this->player->getBullets().erase(bullet);

						if (enemy->isDestoryComplete())
							this->player->AddScore(5);

						break;
					}
				}
			}
		}
	}*/
}

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
}

void GameState::updatePlayerGUI(const float& dt)
{
	this->playerGUI->update(dt);
}

void GameState::updatePauseMenuButtons()
{
	if (this->pMenu->isButtonPressed("QUIT"))
	{
		this->endState();
	}
}

void GameState::updateGameOverButtons()
{
	if (this->gOver->isButtonPressed("QUIT"))
	{
		this->endState();
	}
}

/*void GameState::HandleCombat()
{
	if (this->player->getHP() <= 0)
	{
		this->player->Destroy();
		this->gameOver = true;
	}
}*/

void GameState::updateCombatAndEnemies(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SHOOT"))) && this->player->getShootTimer() >= this->player->getShootTimerMax())
	{
		this->player->SpawnBullet();
		this->player->setShootTimer(0.f);
	}

	unsigned index = 0;
	for (auto *enemy : this->activeEnemies)
	{
		enemy->update(dt);

		this->updateCombat(enemy, index, dt);

		if (enemy->isDestoryComplete())
		{

			this->enemySystem->removeEnemy(index);
			continue;
		}
		else if (enemy->getDespawnTimerDone())
		{
			this->enemySystem->removeEnemy(index);
			continue;
		}

		++index;
	}

}


void GameState::updateCombat(Enemy* enemy, const int index, const float & dt)
{
	if (this->player->getHP() <= 0)
	{
		this->player->Destroy();
		this->gameOver = true;
	}
	else
	{
		if (enemy->getDamageTimerDone())
		{
			//Get to this!!!!
			int dmg = static_cast<int>(this->player->getDamage());
			enemy->loseHP(dmg);
			enemy->resetDamageTimer();
		}

		//Check for enemy damage
		if (enemy->getGlobalBounds().intersects(this->player->getGlobalBounds()) && this->player->getDamageTimer())
		{
			int dmg = enemy->getDamageMax();
			this->player->loseHP(dmg);
		}
	}
}
//UREDITI UPDATE
void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateKeyTime(dt);

	// Game over condition
	if (this->gameOver && this->player->isDestoryComplete())
	{
		this->gOver->update(this->mousePosView);
		this->updateGameOverButtons();
	}

	if (!this->gameOver && !this->paused)	//Unpaused update
	{
		//Player
		this->updatePlayerInput(dt);

		this->player->update(dt);

		this->playerGUI->update(dt);

		this->updateCollision();

		//Update all enemies
		this->updateCombatAndEnemies(dt);

		/*//Spawn an enemy every enemySpawnSeconds interval.
		if (this->enemySpawnClock.getElapsedTime().asSeconds() >= enemySpawnInterval && this->enemies.size() < this->currentEnemyLimit)
		{
			this->SpawnEnemy();
			this->enemySpawnClock.restart();
		}

		//Enemy update cycle
		for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it)
		{
			(*it).update(dt);
		}*/

		//Handle combat
		//this->HandleCombat();

		//Increase difficulty
		this->IncreaseDifficulty();
	}
	else			//Paused update
	{
		this->pMenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}

	//Clear objects
	//this->ClearObjects();
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}

	this->renderTexture.clear();

	//Render player
	this->player->render(this->renderTexture, true);

	/*//Draw enemies
	for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it)
	{
		if (!(*it).isDestoryComplete())
			(*it).render(this->renderTexture, true);
	}*/

	//Render enemies
	for (auto *enemy : this->activeEnemies)
	{
		enemy->render(this->renderTexture, true);
	}

	//Render GUI
	this->playerGUI->render(this->renderTexture);

	if (this->paused)		//Pause menu render
	{
		this->pMenu->render(this->renderTexture);
	}
	if (this->gameOver)		//Game over render
	{
		this->gOver->render(this->renderTexture);
	}

	//Final render
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}
