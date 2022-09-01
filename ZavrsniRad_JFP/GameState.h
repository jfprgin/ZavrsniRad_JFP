#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "GameOver.h"
#include "PlayerGUI.h"
#include "EnemySystem.h"
#include "Random.h"

//Add Enemies
class GameState :
    public State
{
private:
    unsigned maxEnemy;
    unsigned currentEnemyLimit;
    float enemySpawnInterval;
    float enemySpawnIntervalMin;
    float difficultyIncreaseInterval;
    bool gameOver;

    sf::Clock enemySpawnClock;
    sf::Clock difficultyIncreaseClock;

	sf::VideoMode& vm;

	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	Utils::RandomNumberGenerator rng;
	sf::Clock keyTimer;
	float keyTimeMax;

    sf::Font font;
    PauseMenu* pMenu;
	GameOver* gOver;

    Player* player;
    PlayerGUI* playerGUI;

	std::vector<Enemy*> activeEnemies;
	EnemySystem *enemySystem;

    //Functions
	void initDeferredRender();
    void initKeybinds();
    void initFonts();
	void initTextures();
    void initPauseMenu();
	void initGameOver();

	void initPlayers();
    void initPlayerGUI();
	void initEnemySystem();

public:
    GameState(StateData* state_data);
    ~GameState();

    //Functions
    //void SpawnEnemy();
	void IncreaseDifficulty();
	//void HandleCombat();
	void ClearObjects();

	void updateCollision();
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePlayerGUI(const float& dt);
    void updatePauseMenuButtons();
	void updateGameOverButtons();
	void updateCombatAndEnemies(const float & dt);
	void updateCombat(Enemy* enemy, const int index, const float & dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

