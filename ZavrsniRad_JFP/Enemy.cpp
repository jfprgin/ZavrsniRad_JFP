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
Enemy::Enemy(sf::Texture& texture, float pos_x, float pos_y, float speed)
	: hpMax(20),
	hp(hpMax),
	damageMin(1),
	damageMax(2),
	speed(speed),
	exploding(false),
	direction(sf::Vector2f(-1.f, 0.f))
{
	//this->createMovementComponent(300.f, 15.f, 5.f);
	//this->createHitboxComponent(this->sprite, 0.f, 0.f, 48.f, 52.f);
	this->setTexture(texture);

	this->setPosition(pos_x, pos_y);
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
	sf::Vector2f pos(this->direction.x * this->speed * dt * 60.f, this->direction.y * this->speed * dt * 60.f);
	this->sprite.move(pos);
}

void Enemy::render(sf::RenderTarget& target, const bool show_hitbox)
{
	target.draw(this->sprite);

	/*if (show_hitbox)
	{
		this->hitboxComponent->render(target);
	}*/
}

