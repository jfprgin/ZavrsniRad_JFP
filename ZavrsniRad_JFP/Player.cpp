#include "stdafx.h"
#include "Player.h"

//Initializer functions
void Player::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
}

//Accessors
bool Player::isDestoryComplete() const
{
	return this->isDestroyed;
}

const int& Player::getHP() const
{
	return this->hp;
}

const int& Player::getHPMax() const
{
	return this->hpMax;
}

const bool Player::getDamageTimer()
{
	if (this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax)
	{
		this->damageTimer.restart();
		return true;
	}

	return false;
}

int Player::getDamage()
{
	return this->rng.getInt(this->damageMin, this->damageMax);
}


int Player::getScore()
{
	return this->score;
}

const float Player::getDirectionX() const
{
	return this->movementComponent->getDirectionX();
}

const float Player::getDirectionY() const
{
	return this->movementComponent->getDirectionY();
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

void Player::AddScore(int modifier)
{
	this->score += modifier;
}

//Constructor and Destructor
Player::Player(float x, float y, sf::Texture&  texture_sheet)
	: hpMax(100), hp(100), damageMin(5), damageMax(20), damageTimerMax(500), damageTimer(damageTimer),
	score(0), isDestroyed(false)
{
	this->createHitboxComponent(this->sprite, -32.f, -32.f, 64.f, 64.f);
	this->createMovementComponent(500.f, 10.f, 3.f);
	this->createAnimationComponent(texture_sheet);
	
	//this->setTexture(texture);

	this->setPosition(x, y);
	this->initAnimations();
}

Player::~Player()
{
}

void Player::Destroy()
{
	this->isDestroyed = true;
}

//Functions
void Player::updateAnimation(const float & dt)
{
	/*if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}*/
	/*else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity()); //zadnje vjerojatno ne treba
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}*/
}

void Player::update(const float & dt)
{
	this->movementComponent->update(dt);

	this->hitboxComponent->update();

	this->updateAnimation(dt);
}

void Player::render(sf::RenderTarget& target, const bool show_hitbox)
{
	target.draw(this->sprite);

	if (show_hitbox)
	{
		this->hitboxComponent->render(target);
	}
}
