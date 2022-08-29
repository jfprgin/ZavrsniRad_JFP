#include "stdafx.h"
#include "Player.h"

//Initializer functions
void Player::initVariables()
{
	this->hpMax = 100;
	this->hp = this->hpMax;
}

void Player::initComponents()
{
}

//Accessors
const int& Player::getHP() const
{
	return this->hp;
}

const int& Player::getHPMax() const
{
	return this->hpMax;
}

//Modifiers
void Player::loseHP(const int hp)
{
	this->hp -= hp;

	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

void Player::gainHP(const int hp)
{
	this->hp += hp;

	if (this->hp > this->hpMax)
	{
		this->hp = this->hpMax;
	}
}

//Constructor and Destructor
Player::Player(float x, float y, sf::Texture& texture)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 86.f, 81.f, 86.f, 111.f);
	this->setTexture(texture);

	this->createMovementComponent(300.f, 15.f, 5.f);

}

Player::~Player()
{
}

//Functions
void Player::update(const float & dt)
{
	this->movementComponent->update(dt);

	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent)
	{
		this->hitboxComponent->render(target);
	}
}
