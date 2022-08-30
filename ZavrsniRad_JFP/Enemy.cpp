#include "stdafx.h"
#include "Enemy.h"

//Initializer functions
void Enemy::initVariables()
{
	this->hpMax = 100;
	this->hp = this->hpMax;
}

//Accessors
const int& Enemy::getHP() const
{
	return this->hp;
}

const int& Enemy::getHPMax() const
{
	return this->hpMax;
}

//Modifiers
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
Enemy::Enemy(float x, float y, sf::Texture& texture)
{
	this->initVariables();

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 48.f, 52.f);
	this->createMovementComponent(300.f, 15.f, 5.f);
	this->setTexture(texture);

	this->setPosition(x, y);
}

Enemy::~Enemy()
{
}

//Functions
void Enemy::update(const float & dt)
{
	this->movementComponent->update(dt);

	this->hitboxComponent->update();
}

void Enemy::render(sf::RenderTarget& target, const bool show_hitbox)
{
	target.draw(this->sprite);

	if (show_hitbox)
	{
		this->hitboxComponent->render(target);
	}
}
