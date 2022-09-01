#include "stdafx.h"
#include "Enemy.h"

//Accessors
EnemySpawn & Enemy::getEnemySpawn()
{
	return this->enemySpawn;
}

const int& Enemy::getHP() const
{
	return this->hp;
}

const int& Enemy::getHPMax() const
{
	return this->hpMax;
}

const int & Enemy::getDamageMin() const
{
	return this->damageMin;
}

const int & Enemy::getDamageMax() const
{
	return this->damageMax;
}

bool Enemy::isDestoryComplete() const
{
	return this->exploding;
}

const bool Enemy::getDamageTimerDone() const
{
	return this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax;
}

const bool Enemy::getDespawnTimerDone() const
{
	return this->despawnTimer.getElapsedTime().asMilliseconds() >= this->despawnTimerMax;
}

//Modifiers
void Enemy::resetDamageTimer()
{
	this->damageTimer.restart();
}

void Enemy::loseHP(const int hp)
{
	this->hp -= hp;

	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

void Enemy::gainHP(const int hp)
{
	this->hp += hp;

	if (this->hp > this->hpMax)
	{
		this->hp = this->hpMax;
	}
}

//Constructor and Destructor
Enemy::Enemy(EnemySpawn& enemy_spawn)
	: enemySpawn(enemy_spawn), hpMax(100), hp(100), damageMin(5), damageMax(15),
	damageTimerMax(1000), despawnTimerMax(1000), exploding(false)
{
	//this->createMovementComponent(300.f, 15.f, 5.f);
	//this->createHitboxComponent(this->sprite, 0.f, 0.f, 48.f, 52.f);
	//this->setTexture(texture);

	//this->setPosition(x, y);
}

Enemy::~Enemy()
{
}

//Functions
bool Enemy::Destroy()
{
	return this->exploding = true;
}

//VIDI!!!
void Enemy::update(const float & dt)
{
	//this->movementComponent->update(dt);

	//this->hitboxComponent->update();
}

void Enemy::render(sf::RenderTarget& target, const bool show_hitbox)
{
	target.draw(this->sprite);

	if (show_hitbox)
	{
		this->hitboxComponent->render(target);
	}
}

