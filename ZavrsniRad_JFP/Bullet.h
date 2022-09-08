#pragma once

#include "Entity.h"
//DONE
class Bullet :
	public Entity
{
private:
	sf::Vector2f direction;
	float speed;

public:
	Bullet(sf::Texture& texture, float x, float y, float dir_x, float dir_y);
	~Bullet();

	//Functions
	void update(const float& dt);
	void render(sf::RenderTarget& target, const bool show_hitbox = false);
};

