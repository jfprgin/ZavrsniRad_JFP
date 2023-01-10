#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
	this->animationComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movementComponent;
	delete this->animationComponent;
	//Texture deleted from outside
}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float decelartion)
{
	this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, decelartion);
}

void Entity::createHitboxComponent(sf::Sprite & sprite, float offset_x, float offset_y, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createAnimationComponent(sf::Texture & texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

//Accessors

MovementComponent* Entity::getMovementComponent()
{
	return this->movementComponent;
}

AnimationComponent* Entity::getAnimationComponent()
{
	return this->animationComponent;
}
const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
	{
		return this->hitboxComponent->getPosition();
	}

	return this->sprite.getPosition();
}

const sf::Vector2f & Entity::getSpritePosition() const
{
	return this->sprite.getPosition();
}

const sf::Vector2f Entity::getCenter() const
{
	if (this->hitboxComponent)
		return
		this->hitboxComponent->getPosition() +
		sf::Vector2f
		(
			this->hitboxComponent->getGlobalBounds().width / 2.f,
			this->hitboxComponent->getGlobalBounds().height / 2.f
		);

	return
		this->sprite.getPosition() +
		sf::Vector2f
		(
			this->sprite.getGlobalBounds().width / 2.f,
			this->sprite.getGlobalBounds().height / 2.f
		);
}

const sf::Vector2f Entity::getSpriteCenter() const
{
	return this->sprite.getPosition() +
		sf::Vector2f
		(
			this->sprite.getGlobalBounds().width / 2.f,
			this->sprite.getGlobalBounds().height / 2.f
		);
}

const sf::FloatRect Entity::getGlobalBounds() const
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
	//setOrigin was here before this->sprite.setOrigin(this->hitboxComponent->getGlobalBounds().width / 2, this->hitboxComponent->getGlobalBounds().height / 2);
	if (this->hitboxComponent)
	{
		this->sprite.setOrigin(this->hitboxComponent->getGlobalBounds().width / 2, this->hitboxComponent->getGlobalBounds().height / 2);
		this->hitboxComponent->setPosition(x, y);
	}
	else
	{
		this->sprite.setOrigin(this->getGlobalBounds().width / 2, this->getGlobalBounds().height / 2);
		this->sprite.setPosition(x, y);
	}
}

void Entity::movement(const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->movement(dt);	//Sets velocity
	}
}

void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	this->movementComponent->move(dir_x, dir_y, dt);
}


void Entity::rotate(const float dir, const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->rotate(dir, dt);
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

void Entity::setNormalMovement()
{
	if (this->movementComponent)
	{
		this->movementComponent->setNormalMovement();
	}
}

void Entity::setBoostMovement()
{
	if (this->movementComponent)
	{
		this->movementComponent->setBoostMovement();
	}
}

void Entity::update(const float& dt)
{
}

void Entity::render(sf::RenderTarget& target, const bool show_hitbox)
{
}
