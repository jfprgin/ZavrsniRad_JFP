#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies,
	std::map<std::string, sf::Texture>& textures, Entity& player)
	: textures(textures), activeEnemies(activeEnemies), player(player)
{

}

EnemySystem::~EnemySystem()
{

}

void EnemySystem::createEnemy(const float xPos, const float yPos, EnemySpawn& enemy_spawn)
{

	this->activeEnemies.push_back(new Enemy(xPos, yPos, this->textures["ENEMY"], enemy_spawn, this->player));
	enemy_spawn.increaseEnemyCounter();
}

void EnemySystem::removeEnemy(const int index)
{
	this->activeEnemies[index]->decreaseEnemyCounter();
	delete this->activeEnemies[index];
	this->activeEnemies.erase(this->activeEnemies.begin() + index);
}

void EnemySystem::update(const float & dt)
{

}

void EnemySystem::render(sf::RenderTarget * target)
{

}