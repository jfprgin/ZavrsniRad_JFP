#pragma once

#include "State.h"
#include "PauseMenu.h"


class GameState :
    public State
{
private:
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;


    sf::Font font;
    PauseMenu* pMenu;

    Player* player;

    //Functions
	void initDeferredRender();
    void initKeybinds();
    void initFonts();
	void initTextures();
    void initPauseMenu();
	void initPlayers();

public:
    GameState(StateData* state_data);
    ~GameState();

    //Functions
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

