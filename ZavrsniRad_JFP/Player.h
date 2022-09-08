#pragma once

#include "Entity.h"
#include "Bullet.h"
#include "Gui.h"
#include "Random.h"

class Player :
	public Entity
{
private:
	//Variables
	int hp;
	int hpMax;

	int damageMin;
	int damageMax;

	sf::Clock damageTimer;
	sf::Int32 damageTimerMax;

	int score;

	bool isDestroyed;

	Utils::RandomNumberGenerator rng;

public:
	//Accessors
	bool isDestoryComplete() const;
	
	const int& getHP() const;
	const int& getHPMax() const;

	const bool getDamageTimer();
	int getDamage();

	int getScore();

	const float getDirectionX() const;
	const float getDirectionY() const;

	//Modifiers
	void loseHP(const int hp);
	void gainHP(const int hp);
	void AddScore(int modifier);

	//Constructor and Destructor
	Player(float x, float y, sf::Texture& texture);
	~Player();

	//Functions
	void Destroy();

	void update(const float& dt);
	void render(sf::RenderTarget& target, const bool show_hitbox = false);
};

