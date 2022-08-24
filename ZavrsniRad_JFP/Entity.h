#pragma once

#include"stdafx.h"

class Entity
{
private:
	void initVariables();

protected:
	sf::Texture* texture;	//Not load a new texture in, but point to a texture that has already been loaded into a state
	sf::Sprite* sprite;
	float movementSpeed;

public:
	Entity();
	~Entity();

	//Component functions
	void createSprite(sf::Texture* texture);

	//Functions
	virtual void move(const float& dt, const float dir_x, const float dir_y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

