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
	int shootTimer;
	float shootTimerMax;

	bool isDestroyed;

	std::deque<Bullet> m_bullets;
	Utils::RandomNumberGenerator rng;

public:
	//Accessors
	//Returns true if player explosion sound is NOT playing.
	bool isDestoryComplete() const;
	
	std::deque<Bullet>& getBullets();
	const int& getHP() const;
	const int& getHPMax() const;

	float getShootTimer();
	float getShootTimerMax();
	void setShootTimer(float shootTimer);
	const bool getDamageTimer();
	int getDamage();

	int getScore() const;

	//Modifiers
	void loseHP(const int hp);
	void gainHP(const int hp);
	void AddScore(int modifier);

	//Constructor and Destructor
	Player(float x, float y, sf::Texture& texture);
	~Player();

	//Functions
	void Destroy();
	void SpawnBullet();
	//void HandleInput();

	void update(const float& dt);
	void render(sf::RenderTarget& target, const bool show_hitbox = false);
};

