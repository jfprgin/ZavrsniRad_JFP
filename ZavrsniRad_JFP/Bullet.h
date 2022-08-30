#pragma once

#include "Entity.h"

class Bullet :
	public Entity
{
private:
	sf::CircleShape bullet;
	sf::Vector2f currVelocity;
	float maxSpeed;
public:
	Bullet(float x, float y, float radius = 5.f);
	~Bullet();

	//Functions
	void update(const float& dt);
	void render(sf::RenderTarget& target, const bool show_hitbox = false);
};

