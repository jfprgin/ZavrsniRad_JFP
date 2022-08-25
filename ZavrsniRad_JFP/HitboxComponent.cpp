#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite sprite, float offset_x, float offset_y, float width, float height)
	: sprite(sprite)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
}

HitboxComponent::~HitboxComponent()
{
}
