#pragma once

#include "Entity.h"
#include "Random.h"
#include "Player.h"

class Enemy :
	public Entity
{
private:
	//Variables
	int hp;
	int hpMax;

	int damageMin;
	int damageMax;

	float speed;
	bool exploding;

	sf::Vector2f direction;
	Player* player;

public:
	//Accessors
	const int& getHP() const;
	const int& getHPMax() const;
	const float getSpeed() const;

	bool isDestoryComplete() const;

	sf::Vector2f const& getPosition() const { return this->sprite.getPosition(); }
	sf::FloatRect getBoundingBox() const { return this->sprite.getGlobalBounds(); }

	//Modifiers
	void loseHP(const int hp);

	//Constructor and Destructor
	Enemy(sf::Texture& texture, float pos_x, float pos_y, Player* player, float speed = 15.f);
	~Enemy();

	//Functions
	void Destroy();

	void update(const float& dt);
	void render(sf::RenderTarget& target, const bool show_hitbox = false);
};

