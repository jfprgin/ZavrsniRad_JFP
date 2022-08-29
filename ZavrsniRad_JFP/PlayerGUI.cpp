#include "stdafx.h"
#include "PlayerGUI.h"

//Private functions
void PlayerGUI::initFont()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR:PLAYER_GUI::COULD NOT LOAD FONT");
	}
}

void PlayerGUI::initHPBar()
{
	float width = 300.f;
	float height = 30.f;
	float x = 20.f;
	float y = 40.f;

	this->hpBarMaxWidth = width;

	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x, y);

	this->hpBarInner.setSize(sf::Vector2f(width, height));
	this->hpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());

	this->hpBarText.setFont(this->font);
	this->hpBarText.setCharacterSize(18);
	this->hpBarText.setPosition(this->hpBarInner.getPosition().x + 10.f, this->hpBarInner.getPosition().y + 5.f);
}

PlayerGUI::PlayerGUI(Player* player)
{
	this->player = player;

	this->initFont();
	this->initHPBar();
}

PlayerGUI::~PlayerGUI()
{
}

//Functions
void PlayerGUI::updateHPBar()
{
	float percent = static_cast<float>(this->player->getHP()) / static_cast<float>(this->player->getHPMax());
	
	this->hpBarInner.setSize(sf::Vector2f(static_cast<float>(std::floor(this->hpBarMaxWidth * percent)), this->hpBarInner.getSize().y));
	
	this->hpBarString = std::to_string(this->player->getHP()) + "/" + std::to_string(this->player->getHPMax());
	this->hpBarText.setString(this->hpBarString);
}

void PlayerGUI::update(const float& dt)
{
	this->updateHPBar();
}

void PlayerGUI::renderHPBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
	target.draw(this->hpBarText);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->renderHPBar(target);
}
