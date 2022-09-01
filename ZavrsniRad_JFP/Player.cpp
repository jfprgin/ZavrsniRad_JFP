#include "stdafx.h"
#include "Player.h"


//Accessors
bool Player::isDestoryComplete() const
{
	return this->isDestroyed;
}

std::deque<Bullet>& Player::getBullets()
{
	return this->m_bullets;
}

const int& Player::getHP() const
{
	return this->hp;
}

const int& Player::getHPMax() const
{
	return this->hpMax;
}

float Player::getShootTimer()
{
	return this->shootTimer;
}

float Player::getShootTimerMax()
{
	return this->shootTimerMax;
}

void Player::setShootTimer(float shootTimer)
{
	this->shootTimer = shootTimer;
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


int Player::getScore() const
{
	return this->score;
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
Player::Player(float x, float y, sf::Texture& texture)
	: hpMax(100), hp(100), damageMin(5), damageMax(15), damageTimerMax(500), damageTimer(damageTimer),
	score(0), shootTimerMax(8.f), shootTimer(shootTimerMax), isDestroyed(false)
{
	this->createHitboxComponent(this->sprite, 0.f, 0.f, 64.f, 64.f);
	this->createMovementComponent(300.f, 15.f, 5.f);
	this->setTexture(texture);

	this->setPosition(x, y);
}

Player::~Player()
{
}

void Player::Destroy()
{
	this->isDestroyed = true;
}

void Player::SpawnBullet()
{
	this->m_bullets.emplace_front(this->getSpriteCenter().x, this->getSpriteCenter().y, 5.f);
}

/*void Player::HandleInput()
{
	//Shoot
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && this->shootTimer >= this->shootTimerMax)
	{
		this->SpawnBullet();
		this->shootTimer = 0.f;
	}
}*/


//Functions
void Player::update(const float & dt)
{
	this->movementComponent->update(dt);

	this->hitboxComponent->update();

	//Shoot timer
	if (this->shootTimer < this->shootTimerMax)
		this->shootTimer += 1.f * dt * 60.f;

	//Update bullets
	for (auto it = this->m_bullets.begin(); it != this->m_bullets.end(); ++it)
	{
		(*it).update(dt);
	}
}

void Player::render(sf::RenderTarget& target, const bool show_hitbox)
{
	//Draw bullets
	if (!this->m_bullets.empty())
	{
		for (auto it = this->m_bullets.begin(); it != this->m_bullets.end(); ++it)
		{
			(*it).render(target);
		}
	}

	target.draw(this->sprite);

	if (show_hitbox)
	{
		this->hitboxComponent->render(target);
	}
}
