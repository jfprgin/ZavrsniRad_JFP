#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration), directionX(0.f), directionY(-1.f)
{
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{
}

//Accessors
const sf::Vector2f & MovementComponent::getVelocity() const
{
	return this->velocity;
}

const float MovementComponent::getDirectionX() const
{
	return this->directionX;
}

const float MovementComponent::getDirectionY() const
{
	return this->directionY;
}

void MovementComponent::stopVelocity()
{
	/*Resets the velocity to 0*/
	this->velocity.x = 0.f;
	this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX()
{
	/*Resets the velocity x to 0*/
	this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY()
{
	/*Resets the velocity y to 0*/
	this->velocity.y = 0.f;
}

//Functions

float MovementComponent::DegToRad(float degrees) {
	return degrees * static_cast<float>(PI / 180);
}

void MovementComponent::rotate(const float dir, const float & dt)
{
	this->sprite.rotate(dir);

	this->updateDirection();
}

void MovementComponent::movement(const float& dt)
{
	this->updateDirection();
	
	move(this->directionX, this->directionY, dt);
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt)
{
	/*Accelerating a sprite until it reaches the max velocity*/

	this->velocity.x += this->acceleration * dir_x * dt * 100;
	this->velocity.y += this->acceleration * dir_y * dt * 100;
}

void MovementComponent::updateDirection()
{
	this->directionX = sin(DegToRad(sprite.getRotation()));
	this->directionY = -cos(DegToRad(sprite.getRotation()));
}

void MovementComponent::update(const float & dt)
{
	/*Decelerates the sprite and controls the maximum velocity
	Moves the sprite*/
	if (this->velocity.x > 0.f) //Check for positive x
	{
		//Max velocity check
		if (this->velocity.x > this->maxVelocity)
		{
			this->velocity.x = this->maxVelocity;
		}

		//Deceleration
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
		{
			this->velocity.x = 0.f;
		}

		
	}
	else if (this->velocity.x < 0.f)	//Check for negative x
	{
		//Max velocity check
		if (this->velocity.x < -this->maxVelocity)
		{
			this->velocity.x = -this->maxVelocity;
		}

		// Deceleration
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
		{
			this->velocity.x = 0.f;
		}
	}

	if (this->velocity.y > 0.f)		//Check for positive y
	{
		//Max velocity check
		if (this->velocity.y > this->maxVelocity)
		{
			this->velocity.y = this->maxVelocity;
		}

		//Deceleration
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
		{
			this->velocity.y = 0.f;
		}
	}
	else if (this->velocity.y < 0.f)	//Check for negative y
	{
		//Max velocity check
		if (this->velocity.y < -this->maxVelocity)
		{
			this->velocity.y = -this->maxVelocity;
		}

		// Deceleration
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
		{
			this->velocity.y = 0.f;
		}
	}

	//Final move
	this->sprite.move(this->velocity * dt);
}
