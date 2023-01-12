#include "stdafx.h"
#include "GameState.h"

/*=========================Private functions===============================*/
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
	//Player
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/player.png"))
	{
		throw "ERROR::GAME_STATE::COULD NOT LOAD PLAYER IDLE TEXTURE";
	}

	//Enemies
	if (!this->textures["ENEMY"].loadFromFile("Resources/Images/Sprites/Enemy/enemy.png"))
	{
		throw "ERROR::GAME_STATE::COULD NOT LOAD PLAYER IDLE TEXTURE";
	}

	//Bullets
	if (!this->textures["BULLET"].loadFromFile("Resources/Images/Sprites/Bullet/bullet.png"))
	{
		throw "ERROR::GAME_STATE::COULD NOT LOAD BULLET TEXTURE";
	}

	//Explode Animation
	if (!this->textures["EXPLODE"].loadFromFile("Resources/Images/Sprites/ExplodeAnimation/explode.png"))
	{
		throw "ERROR::GAME_STATE::COULD NOT LOAD EXPLODE TEXTURE";
	}

	//Explode Animation
	if (!this->textures["HEALTH"].loadFromFile("Resources/Images/Sprites/HEALTHPACK/health.png"))
	{
		throw "ERROR::GAME_STATE::COULD NOT LOAD HEALTH PACK TEXTURE";
	}

	//Background init
	this->background.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg3.jpg"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED TO LOAD BACKGROUND TEXTURE";
	}
	this->background.setTexture(&this->backgroundTexture);
}

void GameState::initPlayers()
{
	this->player = new Player(gui::p2px(50.f, this->vm), gui::p2py(50.f, this->vm), this->textures["PLAYER_SHEET"], this->boostTimer, this->boostTimerMax);
}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, this->stateData->gfxSettings->resolution);
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

/*======================================Constructorand Desturctor=====================================*/
GameState::GameState(StateData* state_data)
	: State(state_data), vm(this->stateData->gfxSettings->resolution),
	maxEnemy(40), currentEnemyLimit(10),
	enemySpawnInterval(3.f), enemySpawnIntervalMin(0.5f),
	difficultyIncreaseInterval(20.f),
	shootTimer(0.f), shootTimerMax(8.f),
	boostTimer(100.f), boostTimerMax(100.f), insideBoostLoop(false),
	maxHealthPack(2), healthPackSpawnInterval(15.f)
{
	this->initDeferredRender();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();

	this->initPlayers();
	this->initPlayerGUI();

	this->initPauseMenu();
	this->initGameOver();

	this->enemySpawnClock.restart();
	this->difficultyIncreaseClock.restart();

	this->healthPackSpawnClock.restart();

	this->resetGui();
}

GameState::~GameState()
{
	delete this->pMenu;
	delete this->gOver;
	delete this->player;
	delete this->playerGUI;

	//Delete bullets
	for (auto& i : this->bullets)
	{
		delete i;
	}

	//Delete enemies
	for (auto& i : this->enemies)
	{
		delete i;
	}
}

/*===========================================Functions==============================================*/
//General
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

void GameState::SetGameOver()
{
	if (this->player->getHP() <= 0)
	{
		//Initializes explode animation
		this->explodeAnimation.push_back(new Explode(this->textures["EXPLODE"], this->player->getPosition().x, this->player->getPosition().y));

		this->player->Destroy();
		this->gameOver = true;
	}
}

//Update Player
void GameState::updatePlayerInput(const float& dt)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ROTATE_LEFT"))))
	{
		this->player->rotate(-2.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ROTATE_RIGHT"))))
	{
		this->player->rotate(2.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE"))))
	{
		this->player->setNormalMovement();
		this->player->movement(dt);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("BOOST"))) && ((this->boostTimer >= this->boostTimerMax) || insideBoostLoop == true))
	{
		if (this->boostTimer > 1.f)
		{
			this->player->setBoostAnimation(dt);
			this->player->setBoostMovement();
			this->player->movement(dt);

			this->boostTimer -= 1.f * dt * 180;
			this->insideBoostLoop = true;
		}
		else
		{
			this->insideBoostLoop = false;
		}
	}

	//Shoot
	//Spawns bullets and set shootTimer to 0
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("SHOOT"))) && (this->shootTimer >= this->shootTimerMax))
	{
		this->bullets.push_back(
			new Bullet(
				this->textures["BULLET"],
				this->player->getPosition().x + this->player->getGlobalBounds().width / 2.f,
				this->player->getPosition().y + this->player->getGlobalBounds().height / 2.f,
				this->player->getDirectionX(),
				this->player->getDirectionY()
			)
		);

		this->shootTimer = 0.f;
	}
}

void GameState::updatePlayerGUI(const float& dt)
{
	this->playerGUI->update(dt);
}

void GameState::updatePlayerWorldCollision()
{
	//Left
	if (this->player->getGlobalBounds().left < 0.f)
	{
		this->player->stopVelocityX();
		this->player->setPosition(0.f, this->player->getGlobalBounds().top);
	}
	//Right
	else if (this->player->getGlobalBounds().left + this->player->getGlobalBounds().width >= this->window->getSize().x)
	{
		this->player->stopVelocityX();
		this->player->setPosition(window->getSize().x - this->player->getGlobalBounds().width, this->player->getGlobalBounds().top);
	}
	//Top
	if (this->player->getGlobalBounds().top < 0.f)
	{
		this->player->stopVelocityY();
		this->player->setPosition(this->player->getGlobalBounds().left, 0.f);
	}
	//Bottom
	else if (this->player->getGlobalBounds().top + this->player->getGlobalBounds().height >= this->window->getSize().y)
	{
		this->player->stopVelocityY();
		this->player->setPosition(this->player->getGlobalBounds().left, window->getSize().y - this->player->getGlobalBounds().height);
	}
}

//Update bullets and enemies
void GameState::updateBullet(const float& dt)
{
	unsigned counter = 0;

	bool bulletDeleted = false;
	for (size_t i = 0; i < this->bullets.size() && bulletDeleted == false; i++)
	{
		bullets[i]->update(dt);
		
		//Bullet culling with screen
		//Left
		if (bulletDeleted == false && bullets[i]->getGlobalBounds().left  + bullets[i]->getGlobalBounds().width < 0.f)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			bulletDeleted = true;
		}
		//Right
		else if (bulletDeleted == false && bullets[i]->getGlobalBounds().left >= this->window->getSize().x)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			bulletDeleted = true;
		}
		//Top
		if (bulletDeleted == false && bullets[i]->getGlobalBounds().top + bullets[i]->getGlobalBounds().height < 0.f)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			bulletDeleted = true;
		}
		//Bottom
		else if (bulletDeleted == false && bullets[i]->getGlobalBounds().top >= this->window->getSize().y)
		{
			//Delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			bulletDeleted = true;
		}

		++counter;
	}
}

void GameState::spawnEnemies()
{
	//Spawn an enemy every enemySpawnSeconds interval.
	if (this->enemySpawnClock.getElapsedTime().asSeconds() >= enemySpawnInterval && this->enemies.size() < this->currentEnemyLimit)
	{
		float maxX = static_cast<float>(this->stateData->gfxSettings->resolution.width) + 200.f;
		float minX = -200.f;
		float maxY = static_cast<float>(this->stateData->gfxSettings->resolution.height) + 200.f;
		float minY = -200.f;

		float xPos = 0.f;
		float yPos = 0.f;

		do
		{
			xPos = this->rng.getFloat(minX, maxX);
		} while (xPos > 0.f && xPos < static_cast<float>(this->stateData->gfxSettings->resolution.width));
		
		do
		{
			yPos = this->rng.getFloat(minY, maxY);
		} while (xPos > 0.f && xPos < static_cast<float>(this->stateData->gfxSettings->resolution.height));

		this->enemies.push_back(new Enemy(this->textures["ENEMY"], xPos, yPos, this->player));
		
		this->enemySpawnClock.restart();
	}
}

void GameState::spawnHealthPacks()
{
	//Spawn a Health Pack every healthPackSpawnSeconds interval.
	if (this->healthPackSpawnClock.getElapsedTime().asSeconds() >= healthPackSpawnInterval && this->healthPacks.size() < this->maxHealthPack)
	{
		float maxX = static_cast<float>(this->stateData->gfxSettings->resolution.width) - 
			(50.f + 0.01f * static_cast<float>(this->stateData->gfxSettings->resolution.width));
		float minX = 32.f;
		float maxY = static_cast<float>(this->stateData->gfxSettings->resolution.height) - 
			(50.f + 0.01f * static_cast<float>(this->stateData->gfxSettings->resolution.height));
		float minY = 32.f;

		float xPos = 0.f;
		float yPos = 0.f;

		xPos = this->rng.getFloat(minX, maxX);
		yPos = this->rng.getFloat(minY, maxY);

		this->healthPacks.push_back(new HealthPack(this->textures["HEALTH"], xPos, yPos));

		this->healthPackSpawnClock.restart();
	}

	if (this->healthPacks.size() == this->maxHealthPack)
	{
		this->healthPackSpawnClock.restart();
	}
}

void GameState::updateCombat(const float& dt)
{
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		bool enemyDeleted = false;

		for (size_t k = 0; k < this->bullets.size() && enemyDeleted == false; k++)
		{
			if (this->enemies[i]->getGlobalBounds().intersects(this->bullets[k]->getGlobalBounds()))
			{
				this->enemies[i]->setDamageAnimation(dt);
				this->enemies[i]->loseHP(this->player->getDamage(), dt);

				if (this->enemies[i]->isDestoryComplete())
				{
					//Adds score to player
					this->player->AddScore(1);

					//Initializes explode animation
					this->explodeAnimation.push_back(new Explode(this->textures["EXPLODE"], this->enemies[i]->getPosition().x, this->enemies[i]->getPosition().y));

					//Delete Enemy
					delete this->enemies[i];
					this->enemies.erase(this->enemies.begin() + i);

					enemyDeleted = true;
				}

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);
			}
		}
	}
}

void GameState::updateEnemyCollision(const float& dt)
{
	//Update
	unsigned counter = 0;

	for (auto* enemy : this->enemies)
	{
		enemy->update(dt);

		//Enemy player collision
		if (enemy->getGlobalBounds().intersects(this->player->getGlobalBounds()))
		{
			//Initializes explode animation
			this->explodeAnimation.push_back(new Explode(this->textures["EXPLODE"], this->enemies.at(counter)->getPosition().x, this->enemies.at(counter)->getPosition().y));

			//Player take damage and animation
			this->player->loseHP(this->enemies.at(counter)->getHP());
			this->player->setDamageAnimation(dt);

			//Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}

		++counter;
	}

	bool enemyDeleted = false;
	
	if (this->enemies.size() > 0)
	{
		for (size_t i = 0; i < (this->enemies.size() - 1) && enemyDeleted == false; i++)
		{
			for (size_t k = i + 1; k < this->enemies.size() && enemyDeleted == false; k++)
			{
				if (this->enemies[i]->getGlobalBounds().intersects(this->enemies[k]->getGlobalBounds()))
				{
					//Initializes explode animation
					this->explodeAnimation.push_back(new Explode(this->textures["EXPLODE"], this->enemies[k]->getPosition().x, this->enemies[k]->getPosition().y));

					//Delete enemy
					delete this->enemies[k];
					this->enemies.erase(this->enemies.begin() + k);

					enemyDeleted = true;
				}
			}
		}
	}
}

//STVARA PROBLEME
void GameState::updateExplosions(const float& dt)
{
	unsigned counter = 0;

	for (auto* explosion : this->explodeAnimation)
	{
		explosion->update(dt);

		if (explosion->isExplodeAnimationComplete())
		{
			delete this->explodeAnimation.at(counter);
			this->explodeAnimation.erase(this->explodeAnimation.begin() + counter);
			--counter;
		}

		++counter;
	}
}

void GameState::updateHealthPacks(const float& dt)
{
	unsigned counter = 0;

	for (auto* healthPack : this->healthPacks)
	{
		healthPack->update(dt);

		if (healthPack->getGlobalBounds().intersects(this->player->getGlobalBounds()))
		{
			//Player healing and animation
			this->player->gainHP(this->healthPacks.at(counter)->getHP());
			this->player->setHealingAnimation(dt);

			//Delete Health Pack
			delete this->healthPacks.at(counter);
			this->healthPacks.erase(this->healthPacks.begin() + counter);
		}

		++counter;
	}
}

//Update Menus
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

//Main functions
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
		this->gOver->updateScore(player->getScore());
		this->playerGUI->update(dt);

		//Update explosions
		this->updateExplosions(dt);
	}

	//Unpaused update
	if (!this->gameOver && !this->paused)
	{
		//Player
		this->updatePlayerInput(dt);

		this->player->update(dt);

		this->playerGUI->update(dt);
		this->playerGUI->setBoostColour(this->insideBoostLoop || this->boostTimer >= this->boostTimerMax);

		this->updatePlayerWorldCollision();

		//Update explosions
		this->updateExplosions(dt);

		//Update Health Packs
		this->updateHealthPacks(dt);

		//Shoot timer
		if (this->shootTimer < this->shootTimerMax)
			this->shootTimer += 1.f * dt * 60.f;

		//Boost timer
		if (this->boostTimer < this->boostTimerMax)
		{
			this->boostTimer += 1.f * dt * 10.f;
			this->player->setBoostTimer(this->boostTimer);
		}

		//Handle combat
		this->updateBullet(dt);

		this->spawnEnemies();

		this->spawnHealthPacks();

		this->updateCombat(dt);
		
		this->updateEnemyCollision(dt);

		this->SetGameOver();

		//Increase difficulty
		this->IncreaseDifficulty();
	}
	//Paused update
	else
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

	this->renderTexture.draw(this->background);

	//Render bullets
	for (auto* bullet : this->bullets)
	{
		bullet->render(this->renderTexture, false);
	}

	//Render enemies
	for (auto* enemy : this->enemies)
	{
		enemy->render(this->renderTexture, false);
	}

	//Render enemies
	for (auto* healthPack : this->healthPacks)
	{
		healthPack->render(this->renderTexture, false);
	}

	//Render explosions
	for (auto* explosion : this->explodeAnimation)
	{
		explosion->render(this->renderTexture, false);
	}

	//Render player
	if(!this->gameOver)
		this->player->render(this->renderTexture, false);

	//Render GUI
	this->playerGUI->render(this->renderTexture);

	//Pause menu render
	if (this->paused && !this->gameOver)
	{
		this->pMenu->render(this->renderTexture);
	}

	//Game over render
	if (this->gameOver)
	{
		this->gOver->render(this->renderTexture);
	}

	//Final render
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}

void GameState::resetGui()
{
}