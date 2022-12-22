#pragma once

#include "Entity.h"
#include "Random.h"
#include "Player.h"

enum enemies {ENEMY1 = 0, ENEMY2, ENEMY3, ENEMY4};

class Enemy :
	public Entity
{
private:
	//Variables
	int hp;
	int hpMax;

	bool exploding;

	sf::Vector2f moveVec;
	float speed;

	Player* player;

	Utils::RandomNumberGenerator rng;

	//Enemies textures
	std::map<std::string, sf::Texture> textures;

public:
	//Initializer functions
	void initEnemyTextures();
	void initAnimations();

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
	Enemy(sf::Texture& texture, float pos_x, float pos_y, Player* player);
	~Enemy();

	//Functions
	void Destroy();
	void follow(const float& dt);

	void update(const float& dt);
	void render(sf::RenderTarget& target, const bool show_hitbox = false);
};

