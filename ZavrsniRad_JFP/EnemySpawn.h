#pragma once

#include "stdafx.h"

class EnemySpawn
{
private:
	int enemyType;
	int enemyAmount;
	int enemyCounter;
	sf::Clock enemySpawnTimer;
	sf::Int32 enemyTimeToSpawn;
	float enemyMaxDistance;
	bool firstSpawn;

	//Spawn timer


public:
	EnemySpawn(int x, int y,
		const sf::Texture& texture, const sf::IntRect& texture_rect,
		int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance);
	virtual ~EnemySpawn();

	//Accessors
	const int& getEnemyAmount() const;
	const int& getEnemyCounter() const;
	const bool getSpawnTimer();
	const float& getEnemyMaxDistance() const;

	//Functions
	void increaseEnemyCounter();
	void decreaseEnemyCounter();

	void update();
	void render(sf::RenderTarget & target);
};

