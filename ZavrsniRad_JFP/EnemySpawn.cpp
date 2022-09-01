#include "stdafx.h"
#include "EnemySpawn.h"

EnemySpawn::EnemySpawn(int x, int y,
	const sf::Texture& texture, const sf::IntRect& texture_rect,
	int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance)
{
	this->enemyAmount = enemy_amount;
	this->enemyCounter = 0;
	this->enemySpawnTimer.restart();
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemyMaxDistance = enemy_max_distance;
	this->firstSpawn = true;
}

EnemySpawn::~EnemySpawn()
{

}

const int & EnemySpawn::getEnemyAmount() const
{
	return this->enemyAmount;
}

const int & EnemySpawn::getEnemyCounter() const
{
	return this->enemyCounter;
}

const bool EnemySpawn::getSpawnTimer()
{
	if (this->enemySpawnTimer.getElapsedTime().asSeconds() >= this->enemyTimeToSpawn || this->firstSpawn)
	{
		this->enemySpawnTimer.restart();
		this->firstSpawn = false;
		return true;
	}

	return false;
}

const float& EnemySpawn::getEnemyMaxDistance() const
{
	return this->enemyMaxDistance;
}

void EnemySpawn::increaseEnemyCounter()
{
	if (this->enemyCounter < this->enemyAmount)
		++this->enemyCounter;
}

void EnemySpawn::decreaseEnemyCounter()
{
	if (this->enemyCounter > 0)
		--this->enemyCounter;
}

//Functions
void EnemySpawn::update()
{

}

void EnemySpawn::render(sf::RenderTarget & target)
{
	target.draw(this->shape);
}