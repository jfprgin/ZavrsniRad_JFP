#pragma once

#include "Entity.h"

class Bullet :
	public Entity
{
private:
	sf::Vector2f direction;
	//sf::Vector2f currVelocity;
	float speed;

public:
	Bullet(sf::Texture& texture, float x, float y, float speed);
	~Bullet();

	//Functions
	void update(const float& dt);
	void render(sf::RenderTarget& target, const bool show_hitbox = false);
};

