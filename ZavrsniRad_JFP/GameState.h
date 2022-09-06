#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "GameOver.h"
#include "PlayerGUI.h"
#include "Enemy.h"
#include "Random.h"

class GameState :
    public State
{
private:
	//Variables
	//Enemy spawning
    unsigned maxEnemy;
    unsigned currentEnemyLimit;
    float enemySpawnInterval;
    float enemySpawnIntervalMin;
    float difficultyIncreaseInterval;

	sf::Clock enemySpawnClock;
	sf::Clock difficultyIncreaseClock;

	//Shooting
	float shootTimer;
	float shootTimerMax;

	sf::VideoMode& vm;
	
	//Background
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	//Textures
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	//Random number and clock
	Utils::RandomNumberGenerator rng;
	sf::Clock keyTimer;
	float keyTimeMax;

    sf::Font font;
    PauseMenu* pMenu;
	GameOver* gOver;

	//Player
    Player* player;
    PlayerGUI* playerGUI;

	//Enemies
	std::vector<Enemy> enemies;
	std::vector<Enemy> enemyGCList;

	//Bullets
	std::deque<Bullet> bullets;

    //Functions
	void initDeferredRender();
    void initKeybinds();
    void initFonts();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
    void initPlayerGUI();
	void initGameOver();

public:
    GameState(StateData* state_data);
    ~GameState();

    //Functions
	void SpawnBullet();
    void SpawnEnemy();
	void IncreaseDifficulty();
	void HandleCombat();
	void ClearObjects();

	void updateCollision();
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePlayerGUI(const float& dt);
    void updatePauseMenuButtons();
	void updateGameOverButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

