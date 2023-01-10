#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(sf::Texture& texture, float x, float y, float dir_x, float dir_y)
	: direction(sf::Vector2f(dir_x, dir_y))
{
	this->speed = 1200.f;

	this->createHitboxComponent(this->sprite, -8.f, -8.f, 16.f, 16.f);
	this->setTexture(texture);

	this->setPosition(x, y);
}

Bullet::~Bullet()
{
}

//Functions
void Bullet::update(const float & dt)
{
	//Update movement and hitbox
	sf::Vector2f pos(this->direction.x * this->speed * dt * 100.f, this->direction.y * this->speed * dt * 100.f);
	this->sprite.move(pos * (dt));

	this->hitboxComponent->update();
}

void Bullet::render(sf::RenderTarget & target, const bool show_hitbox)
{
	target.draw(this->sprite);

	if (show_hitbox)
	{
		this->hitboxComponent->render(target);
	}
}
