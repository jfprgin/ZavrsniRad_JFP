#pragma once

#include "Entity.h"
#include "Random.h"
#include "Player.h"
#include "Explode.h"

enum enemies {ENEMY1 = 0, ENEMY2, ENEMY3, ENEMY4, ENEMY5};

class Enemy :
	public Entity
{
private:
	//Variables
	int hp;
	int hpMax;

	//Is Enemy destroyed
	bool exploding;

	//Movement
	sf::Vector2f moveVec;
	float speed;

	//Timer for taking damage animation because it won't work properly
	float damageAnimationTimer;
	float damageAnimationTimerMax;

	//Type of Enemy texture
	short unsigned enemyType;
	short unsigned enemyColour;

	Player* player;

	Utils::RandomNumberGenerator rng;

	//Enemies textures
	std::map<std::string, sf::Texture> textures;
	
	//Initializer functions
	void initAnimations();

public:
	//Accessors
	const int& getHP() const;
	const int& getHPMax() const;
	const float getSpeed() const;

	bool isDestoryComplete() const;

	sf::Vector2f const& getPosition() const { return this->sprite.getPosition(); }
	sf::FloatRect getBoundingBox() const { return this->sprite.getGlobalBounds(); }

	//Modifiers
	void loseHP(const int hp, const float& dt);
	void setDamageAnimation(const float& dt);

	//Constructor and Destructor
	Enemy(sf::Texture& texture, float pos_x, float pos_y, Player* player);
	~Enemy();

	//Functions
	void Destroy();
	void follow(const float& dt);

	void updateAnimations(const float& dt);

	void update(const float& dt);
	void render(sf::RenderTarget& target, const bool show_hitbox = false);
};

