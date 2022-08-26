#include "stdafx.h"
#include "Player.h"

//Initializer functions
void Player::initVariables()
{
}

void Player::initComponents()
{
}

//Constructor and Destructor
Player::Player(float x, float y, sf::Texture& texture)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 192.f, 192.f);
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
