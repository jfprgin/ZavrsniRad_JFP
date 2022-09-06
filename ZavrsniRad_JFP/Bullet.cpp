#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(sf::Texture& texture, float x, float y, float speed)
	: speed(speed),
	direction(sf::Vector2f(1.f, 0.f))
{
	//this->createMovementComponent(300.f, 15.f, 5.f);
	//this->createHitboxComponent(this->sprite, 0.f, 0.f, 48.f, 52.f);

	this->setTexture(texture);

	this->setPosition(x, y);
}

Bullet::~Bullet()
{
}

//Functions
void Bullet::update(const float & dt)
{
	//this->movementComponent->update(dt);
	sf::Vector2f pos(this->direction.x * this->speed * dt * 60.f, this->direction.y * this->speed * dt * 60.f);
	this->sprite.move(pos);
}

void Bullet::render(sf::RenderTarget & target, const bool show_hitbox)
{
	target.draw(this->sprite);
}
