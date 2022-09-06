#include "stdafx.h"
#include "GameOver.h"

GameOver::GameOver(sf::VideoMode& vm, sf::Font& font, int playerScore)
	: font(font)
{
	this->score = std::to_string(playerScore);

	//Init background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//Init container
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(vm.width) / 4.f,
			static_cast<float>(vm.height) - gui::p2py(9.3f, vm)
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f, 30.f);

	//Init text
	//Game ove
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(gui::calcCharSize(vm));
	this->menuText.setString("GAME OVER");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + gui::p2py(4.f, vm)
	);

	//Player score
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(gui::calcCharSize(vm, 80));
	this->menuText.setString("SCORE: "+ std::to_string(playerScore));
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + gui::p2py(5.f, vm)
	);
}

GameOver::~GameOver()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	std::ofstream myfile("Config/Scores.txt");

	if (myfile.is_open())
	 {
		myfile << score << std::endl;
	}
	else
	{
		 throw "ERROR::GAME_OVER::FAILED TO OPEN SCORE.TXT";
	}

	myfile.close();
}

//Accessor
std::map<std::string, gui::Button*>& GameOver::getButtons()
{
	return this->buttons;
}

//Functions
const bool GameOver::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void GameOver::addButton(const std::string key, const float y,
	const float width, const float height,
	const unsigned char_size, const std::string text)
{
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new gui::Button(
		x, y, width, height,
		&this->font, text, char_size,
		sf::Color(100, 100, 100, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),	//button color
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));		//text color
}

void GameOver::update(const sf::Vector2f& mousePos)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

void GameOver::render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->menuText);
}
