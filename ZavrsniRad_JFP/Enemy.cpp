#include "stdafx.h"
#include "Enemy.h"

//Accessors
const int& Enemy::getHP() const
{
	return this->hp;
}

const int& Enemy::getHPMax() const
{
	return this->hpMax;
}

const float Enemy::getSpeed() const
{
	return this->speed;
}

bool Enemy::isDestoryComplete() const
{
	return this->exploding;
}

//Modifiers
void Enemy::loseHP(const int hp)
{
	this->hp -= hp;

	if (this->hp < 0)
	{
		this->hp = 0;
	}

	if (this->hp == 0)
		this->Destroy();
}

//Constructor and Destructor
Enemy::Enemy(sf::Texture& texture, float pos_x, float pos_y, Player* player)
	: hpMax(20),
	hp(20),
	exploding(false),
	player(player)
{
	this->speed = this->rng.getFloat(200.f, 400.f);

	this->createMovementComponent(this->speed, 15.f, 5.f);
	this->createHitboxComponent(this->sprite, -16.f, -16.f, 64.f, 64.f);

	this->setTexture(texture);

	this->setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
}

//Functions
void Enemy::Destroy()
{
	this->exploding = true;
}

void Enemy::follow(const float& dt)
{
	this->moveVec.x = this->player->getPosition().x - this->getPosition().x;
	this->moveVec.y = this->player->getPosition().y - this->getPosition().y;

	float vecLength = sqrt(pow(this->moveVec.x, 2) + pow(this->moveVec.y, 2));

	this->moveVec /= vecLength;

	if ((this->getPosition().x != this->player->getPosition().x))
	{
		this->move(this->moveVec.x, this->moveVec.y, dt);
	}
}

void Enemy::update(const float & dt)
{
	this->movementComponent->update(dt);

	this->follow(dt);

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

