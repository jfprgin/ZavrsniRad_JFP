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
	float width = gui::p2px(15.f, this->vm);
	float height = gui::p2py(3.f, this->vm);
	float x = gui::p2px(1.f, this->vm);
	float y = gui::p2py(2.f, this->vm);

	this->hpBarMaxWidth = width;

	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x, y);

	this->hpBarInner.setSize(sf::Vector2f(width, height));
	this->hpBarInner.setFillColor(sf::Color(250, 20, 20, 100));
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());

	this->hpBarText.setFont(this->font);
	this->hpBarText.setCharacterSize(gui::calcCharSize(this->vm, 150));
	this->hpBarText.setPosition(this->hpBarInner.getPosition().x + gui::p2px(0.53f, this->vm), this->hpBarInner.getPosition().y + gui::p2py(0.5f, this->vm));
}

void PlayerGUI::initBoostBar()
{
	float width = gui::p2px(30.f, this->vm);
	float height = gui::p2py(5.f, this->vm);
	float x = gui::p2px(50.f, this->vm);
	float y = gui::p2py(90.f, this->vm);

	this->boostBarMaxWidth = width;

	this->boostBarBack.setSize(sf::Vector2f(width, height));
	this->boostBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->boostBarBack.setPosition(x - this->boostBarMaxWidth / 2, y);

	this->boostBarInner.setSize(sf::Vector2f(width, height));
	this->boostBarInner.setFillColor(sf::Color(255, 255, 255, 100));
	this->boostBarInner.setPosition(this->boostBarBack.getPosition());
}

void PlayerGUI::initScore()
{
	this->ScoreText.setFont(this->font);
	this->ScoreText.setCharacterSize(gui::calcCharSize(this->vm, 70));
	this->ScoreText.setPosition(gui::p2px(86.f, this->vm), gui::p2py(1.f, this->vm));
}

PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm)
	:vm(vm)
{
	this->player = player;

	this->initFont();
	this->initHPBar();
	this->initBoostBar();
	this->initScore();
}

PlayerGUI::~PlayerGUI()
{
}

//Modifiers
void PlayerGUI::setBoostColour(bool isBoostActive)
{
	if (isBoostActive)
	{
		this->boostBarInner.setFillColor(sf::Color(255, 255, 0, 100));
	}
	else
	{
		this->boostBarInner.setFillColor(sf::Color(255, 255, 255, 100));
	}
}

//Functions
void PlayerGUI::updateHPBar()
{
	float percent = static_cast<float>(this->player->getHP()) / static_cast<float>(this->player->getHPMax());
	
	this->hpBarInner.setSize(sf::Vector2f(static_cast<float>(std::floor(this->hpBarMaxWidth * percent)), this->hpBarInner.getSize().y));
	
	this->hpBarString = std::to_string(this->player->getHP()) + "/" + std::to_string(this->player->getHPMax());
	this->hpBarText.setString(this->hpBarString);
}

void PlayerGUI::updateBoostBar()
{
	float percent = static_cast<float>(this->player->getBoost()) / static_cast<float>(this->player->getBoostMax());

	this->boostBarInner.setSize(sf::Vector2f(static_cast<float>(std::floor(this->boostBarMaxWidth * percent)), this->boostBarInner.getSize().y));
}

void PlayerGUI::updateScore()
{
	this->ScoreString = "SCORE: " + std::to_string(this->player->getScore());
	this->ScoreText.setString(this->ScoreString);
}

void PlayerGUI::update(const float& dt)
{
	this->updateHPBar();
	this->updateBoostBar();
	this->updateScore();
}

void PlayerGUI::renderHPBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
	target.draw(this->hpBarText);
}

void PlayerGUI::renderBoostBar(sf::RenderTarget& target)
{
	target.draw(this->boostBarBack);
	target.draw(this->boostBarInner);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->renderHPBar(target);
	this->renderBoostBar(target);

	target.draw(this->ScoreText);
}
