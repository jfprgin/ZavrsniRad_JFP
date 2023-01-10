#include "stdafx.h"
#include "Enemy.h"

//Initializer functions
void Enemy::initEnemyTextures()
{
	this->animationComponent->addAnimation("ENEMY" + std::to_string(enemyType + 1), 1.f, 0, enemyType, 0, 0, 100, 100);
	this->animationComponent->addAnimation("ENEMY" + std::to_string(enemyType + 1) + "DAMAGE", 0.f, 0, enemyType + 5, 0, 0, 100, 100);
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
void Enemy::loseHP(const int hp, const float& dt)
{
	this->takeDamage = 0.f;

	this->hp -= hp;

	if (this->hp < 0)
	{
		this->hp = 0;
	}

	if (this->hp == 0)
	{
		this->Destroy();
	}
}

void Enemy::setDamageAnimation(const float& dt)
{
 	this->animationComponent->addAnimation("ENEMY" + std::to_string(enemyType + 1) + "DAMAGE", 5.f, 0, enemyType + 5, 0, 0, 100, 100);
	this->animationComponent->play("ENEMY" + std::to_string(enemyType + 1) + "DAMAGE", dt);
}

//Constructor and Destructor
Enemy::Enemy(sf::Texture& texture_sheet, float pos_x, float pos_y, Player* player)
	: hpMax(20),
	hp(20),
	exploding(false),
	takeDamageMax(5.f),
	takeDamage(5.f),
	player(player)
{
	this->speed = this->rng.getFloat(200.f, 400.f);

	this->enemyType = this->rng.getInt(0, 3);

	this->createMovementComponent(this->speed, 15.f, 5.f);
	this->createHitboxComponent(this->sprite, -16.f, -16.f, 64.f, 64.f);
	this->createAnimationComponent(texture_sheet);

	this->initEnemyTextures();
	
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

void Enemy::updateAnimations(const float& dt)
{
	if (this->takeDamage < takeDamageMax)
	{
		this->takeDamage += 100 * dt;
	}
	else
	{
		this->animationComponent->addAnimation("ENEMY" + std::to_string(enemyType + 1), 1.f, 0, enemyType, 0, 0, 100, 100);
		this->animationComponent->play("ENEMY" + std::to_string(enemyType + 1), dt);
	}

		/*if (this->animationComponent->isDone("ENEMY" + std::to_string(enemy_type + 1) + "DAMAGE"))
		{
			this->take_damage = false;
		}

		if (this->take_damage)
		{
			this->animationComponent->play("ENEMY" + std::to_string(enemy_type + 1) + "DAMAGE", dt);
		}
		else
		{
			this->animationComponent->addAnimation("ENEMY" + std::to_string(enemy_type + 1), 1.f, 0, enemy_type, 0, 0, 100, 100);
			this->animationComponent->play("ENEMY" + std::to_string(enemy_type + 1), dt);
		}*/
}
	

void Enemy::update(const float & dt)
{
	this->updateAnimations(dt);

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

