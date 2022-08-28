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
	delete this->attributeComponent;
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

void Entity::createHitboxComponent(sf::Sprite & sprite, float offset_x, float offset_y, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createAttributeComponent()
{
	this->attributeComponent = new AttributeComponent();
}

//Accessors
const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
	{
		return this->hitboxComponent->getPosition();
	}

	return this->sprite.getPosition();
}

const sf::FloatRect Entity::getGlobalBouds() const
{
	if (this->hitboxComponent)
	{
		return this->hitboxComponent->getGlobalBounds();
	}
	return this->sprite.getGlobalBounds();
}

//Functions
void Entity::setPosition(const float x, const float y)
{
	if (this->hitboxComponent)
	{
		this->hitboxComponent->setPosition(x, y);
	}
	else
	{
		this->sprite.setPosition(x, y);
	}
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y, dt);	//Sets velocity
	}
}

void Entity::stopVelocity()
{
	if (this->movementComponent)
	{
		this->movementComponent->stopVelocity();
	}
}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
	{
		this->movementComponent->stopVelocityX();
	}
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
	{
		this->movementComponent->stopVelocityY();
	}
}

void Entity::update(const float& dt)
{
}

void Entity::render(sf::RenderTarget& target)
{
}
