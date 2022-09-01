#pragma once

#include "Entity.h"
#include "EnemySpawn.h"

class Enemy :
	public Entity
{
private:
	//Variables
	EnemySpawn& enemySpawn;
	int hp;
	int hpMax;

	int damageMin;
	int damageMax;

	sf::Clock damageTimer;
	sf::Int32 damageTimerMax;
	sf::Clock despawnTimer;
	sf::Int32 despawnTimerMax;

	float speed;

	bool exploding;

public:
	//Accessors
	EnemySpawn& getEnemySpawn();
	const int& getHP() const;
	const int& getHPMax() const;

	const int& getDamageMin() const;
	const int& getDamageMax() const;

	const bool getDamageTimerDone() const;
	const bool getDespawnTimerDone() const;

	bool isDestoryComplete() const;

	//Modifiers
	void resetDamageTimer();
	void loseHP(const int hp);
	void gainHP(const int hp);

	//Constructor and Destructor
	Enemy(EnemySpawn& enemy_spawn);
	~Enemy();

	//Functions
	bool Destroy();

	void update(const float& dt);
	void render(sf::RenderTarget& target, const bool show_hitbox = false);
};

