#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	//Texture deleted from outside
}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
	this->sprite.setScale(0.05f, 0.05f);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float decelartion)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, decelartion);
}

void Entity::createHitboxComponent(sf::Sprite & sprite, float offset_x, float offset_y, float wifth, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, wifth, height);
}

//Functions
void Entity::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt);	//Sets velocity
	}
}

void Entity::update(const float& dt)
{
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent)
	{
		this->hitboxComponent->render(target);
	}
}
