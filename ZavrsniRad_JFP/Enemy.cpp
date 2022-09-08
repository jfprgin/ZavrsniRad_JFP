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
Enemy::Enemy(sf::Texture& texture, float pos_x, float pos_y, Player* player, float speed)
	: hpMax(20),
	hp(20),
	damageMin(1),
	damageMax(2),
	speed(speed),
	exploding(false),
	direction(sf::Vector2f(-1.f, 0.f)),
	player(player)
{
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

//VIDI!!!
void Enemy::update(const float & dt)
{
	sf::Vector2f moveVec;
	moveVec.x = this->player->getPosition().x - this->getPosition().x;
	moveVec.y = this->player->getPosition().y - this->getPosition().y;

	float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

	moveVec /= vecLength;

	if ((this->getPosition().x != this->player->getPosition().x))
	{
		sf::Vector2f pos(moveVec.x * dt * 60.f, moveVec.y * this->speed * dt * 60.f);
		this->move(pos);
	}
	//sf::Vector2f pos(this->direction.x * this->speed * dt * 60.f, this->direction.y * this->speed * dt * 60.f);
	//this->sprite.move(pos);
}

void Enemy::render(sf::RenderTarget& target, const bool show_hitbox)
{
	target.draw(this->sprite);
}

