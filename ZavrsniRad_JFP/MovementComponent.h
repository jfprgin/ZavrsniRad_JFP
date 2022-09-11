#pragma once

#include"stdafx.h"

#define PI 3.14159265358979323846

class MovementComponent
{
private:
	//Variables
	sf::Sprite& sprite;

	float directionX;
	float directionY;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;

	//Initializer functions


public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	~MovementComponent();

	//Accessors
	const sf::Vector2f& getVelocity() const;
	const float getDirectionX() const;
	const float getDirectionY() const;

	//Functions
	void stopVelocity();
	void stopVelocityX();
	void stopVelocityY();

	float DegToRad(float degrees);
	void movement(const float& dt);
	void rotate(const float dir, const float& dt);
	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);
};

