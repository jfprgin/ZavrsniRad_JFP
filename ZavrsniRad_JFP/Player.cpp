#include "stdafx.h"
#include "Player.h"

//Initializer functions
void Player::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 2.f, 0, 0, 1, 0, 64, 64);
	this->animationComponent->addAnimation("DAMAGE", 2.f, 0, 1, 1, 0, 64, 64);
	this->animationComponent->addAnimation("HEALING", 2.f, 0, 2, 1, 0, 64, 64);
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

/*const bool Player::getDamageTimer()
{
	if (this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax)
	{
		this->damageTimer.restart();
		return true;
	}

	return false;
}*/

int Player::getDamage()
{
	return this->bulletDamage;
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

const float Player::getBoost() const
{
	return this->boostTimer;
}

const float Player::getBoostMax() const
{
	return this->boostTimerMax;
}

//Modifiers
void Player::loseHP(const int hp)
{
	this->damageAnimationTimer = 0.f;

	this->hp -= hp;

	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

void Player::gainHP(const int hp)
{
	this->healingAnimationTimer = 0.f;

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

void Player::setDamageAnimation(const float& dt)
{
	this->animationComponent->addAnimation("DAMAGE", 2.f, 0, 1, 1, 0, 64, 64);
	this->animationComponent->play("DAMAGE", dt);
}

void Player::setHealingAnimation(const float& dt)
{
	this->animationComponent->addAnimation("HEALING", 2.f, 0, 2, 1, 0, 64, 64);
	this->animationComponent->play("HEALING", dt);
}

void Player::setBoostTimer(const float boost_timer)
{
	this->boostTimer = boost_timer;
}

//Constructor and Destructor
Player::Player(float x, float y, sf::Texture&  texture_sheet, float boost_timer, float boost_timer_max)
	: hpMax(100), hp(100), bulletDamage(10), //damageTimerMax(500), damageTimer(damageTimer),
	score(0), isDestroyed(false),
	damageAnimationTimer(5.f), damageAnimationTimerMax(5.f),
	healingAnimationTimer(5.f), healingAnimationTimerMax(5.f),
	boostTimer(boost_timer), boostTimerMax(boost_timer_max)
{
	this->createHitboxComponent(this->sprite, -32.f, -32.f, 64.f, 64.f);
	this->createMovementComponent(500.f, 10.f, 3.f);
	this->createAnimationComponent(texture_sheet);

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
	if (this->damageAnimationTimer < this->damageAnimationTimerMax)
	{
		this->damageAnimationTimer += 100 * dt;
	}
	else if (this->healingAnimationTimer < this->healingAnimationTimerMax)
	{
		this->healingAnimationTimer += 100 * dt;
	}
	else
	{
		//this->animationComponent->addAnimation("IDLE", 1.f, 0, 0, 2, 0, 64, 64);
		this->animationComponent->play("IDLE", dt);
	}
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
