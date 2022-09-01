#pragma once

#include "Player.h"
#include "stdafx.h"

//ADD POINTS AND HIGHSCORE
class PlayerGUI
{
private:
	Player* player;

	sf::VideoMode& vm;
	sf::Font font;

	//HP bar
	std::string hpBarString;
	sf::Text hpBarText;
	float hpBarMaxWidth;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInner;

	//Score
	std::string ScoreString;
	sf::Text ScoreText;

	//Private functions
	void initFont();
	void initHPBar();
	void initScore();

public:
	PlayerGUI(Player* player, sf::VideoMode& vm);
	~PlayerGUI();

	//Functions
	void updateHPBar();
	void updateScore();
	void update(const float& dt);

	void renderHPBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

