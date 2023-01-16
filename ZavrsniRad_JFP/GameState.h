#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "GameOver.h"
#include "PlayerGUI.h"
#include "Enemy.h"
#include "HealthPack.h"

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
	sf::Clock enemySpawnClock;

	//Health Pack spawning
	unsigned maxHealthPack;
	float healthPackSpawnInterval;
	sf::Clock healthPackSpawnClock;

	//Difficulty increase
	float difficultyIncreaseInterval;
	sf::Clock difficultyIncreaseClock;

	//Shooting
	float shootTimer;
	float shootTimerMax;

	//Boosting
	float boostTimer;
	float boostTimerMax;
	bool insideBoostLoop;

	sf::VideoMode vm;
	sf::Font font;
	
	//Background
	sf::Texture backgroundTexture;
	sf::RectangleShape background;

	//Textures
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;
	GraphicsSettings* gfxSettings;

	//Random number and clock
	Utils::RandomNumberGenerator rng;
	sf::Clock keyTimer;
	float keyTimeMax;

	//Pause and Game Over
    PauseMenu* pMenu;
	GameOver* gOver;

	//Player
    Player* player;
    PlayerGUI* playerGUI;

	//Enemies
	std::vector<Enemy*> enemies;

	//Bullets
	std::deque<Bullet*> bullets;

	//Explode Animations
	std::vector<Explode*> explodeAnimation;

	//Health Packs
	std::vector<HealthPack*> healthPacks;

    //Private functions
	void initDeferredRender();
    void initKeybinds();
    void initFonts();
	void initTextures();

	void initPlayers();
    void initPlayerGUI();

	void initPauseMenu();
	void initGameOver();

public:
	//Constructor and Desturctor
    GameState(StateData* state_data);
    ~GameState();

    //Functions
	//General
	void updateInput(const float& dt);
	void IncreaseDifficulty();
	void SetGameOver();

	//Update player
	void updatePlayerInput(const float& dt);
	void updatePlayerGUI(const float& dt);
	void updatePlayerWorldCollision();
   
	//Update bullets and enemies
	void updateBullet(const float& dt);
	void spawnEnemies();
	void spawnHealthPacks();
	void updateCombat(const float& dt);
	void updateEnemyCollision(const float& dt);
	void updateExplosions(const float& dt);
	void updateHealthPacks(const float& dt);

	//Update Menus
    void updatePauseMenuButtons();
	void updateGameOverButtons();
    
	//Main functions
	void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);

	void resetGui();
	bool isSettingsState();
};

