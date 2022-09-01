#pragma once

#include"Gui.h"
#include"stdafx.h"

class GameOver
{
private:
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, gui::Button*> buttons;

public:
	GameOver(sf::VideoMode& vm, sf::Font& font, int playerScore);
	~GameOver();

	//Accessor
	std::map<std::string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, const float y,
		const float width, const float height,
		const unsigned char_size, const std::string text);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};

