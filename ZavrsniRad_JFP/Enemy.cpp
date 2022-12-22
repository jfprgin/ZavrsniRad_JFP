#include "stdafx.h"
#include "Enemy.h"

//Initializer functions
void Enemy::initAnimations(const short unsigned enemyType)
{
	//this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
}

const short unsigned Enemy::initEnemyTextures(const short unsigned enemyType)
{
	switch (enemyType)
	{
	case ENEMY1:
		this->animationComponent->addAnimation("ENEMY1", 0.f, 0, 0, 0, 0, 100, 100);
		return ENEMY1;

	case ENEMY2:
		this->animationComponent->addAnimation("ENEMY2", 0.f, 0, 1, 0, 0, 100, 100);
		return ENEMY2;

	case ENEMY3:
		this->animationComponent->addAnimation("ENEMY3", 0.f, 0, 2, 0, 0, 100, 100);
		return ENEMY3;

	case ENEMY4:
		this->animationComponent->addAnimation("ENEMY4", 0.f, 0, 3, 0, 0, 100, 100);
		return ENEMY4;

	default:
		break;
	}
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
Enemy::Enemy(sf::Texture& texture_sheet, float pos_x, float pos_y, Player* player)
	: hpMax(20),
	hp(20),
	exploding(false),
	player(player)
{
	this->speed = this->rng.getFloat(200.f, 400.f);

	this->createMovementComponent(this->speed, 15.f, 5.f);
	this->createHitboxComponent(this->sprite, -16.f, -16.f, 64.f, 64.f);
	this->createAnimationComponent(texture_sheet);

	this->initEnemyTextures(this->rng.getInt(0, 3));
	//this->setTexture(texture);
	//this->initAnimations();

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

