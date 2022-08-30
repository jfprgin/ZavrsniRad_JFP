#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "PlayerGUI.h"
#include "Enemy.h"

//Add Enemies
class GameState :
    public State
{
private:
	sf::VideoMode& vm;

	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Clock keyTimer;
	float keyTimeMax;

    sf::Font font;
    PauseMenu* pMenu;

    Player* player;
    PlayerGUI* playerGUI;

	Enemy* testEnemy;

    //Functions
	void initDeferredRender();
    void initKeybinds();
    void initFonts();
	void initTextures();
    void initPauseMenu();

	void initPlayers();
    void initPlayerGUI();

public:
    GameState(StateData* state_data);
    ~GameState();

    //Functions
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePlayerGUI(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

