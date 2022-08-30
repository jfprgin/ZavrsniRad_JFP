#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(float x, float y, float radius)
{
	this->bullet.setRadius(radius);
	this->bullet.setFillColor(sf::Color::White);

	this->createMovementComponent(300.f, 15.f, 5.f);

	this->setPosition(x, y);
}

Bullet::~Bullet()
{
}

//Functions
void Bullet::update(const float & dt)
{
	this->movementComponent->update(dt);
}

void Bullet::render(sf::RenderTarget & target, const bool show_hitbox)
{
	target.draw(this->sprite);
}
