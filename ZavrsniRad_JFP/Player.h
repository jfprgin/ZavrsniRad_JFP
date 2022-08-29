#pragma once

#include "Entity.h"

class Player :
	public Entity
{
private:
	//Variables
	int hp;
	int hpMax;

	//Initializer functions
	void initVariables();
	void initComponents();

public:
	//Accessors
	const int& getHP() const;
	const int& getHPMax() const;

	//Modifiers
	void loseHP(const int hp);
	void gainHP(const int hp);

	//Constructor and Destructor
	Player(float x, float y, sf::Texture& texture);
	~Player();

	//Functions
	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

