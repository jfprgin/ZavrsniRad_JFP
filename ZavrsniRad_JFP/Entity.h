#pragma once

#include"MovementComponent.h"

class Entity
{
private:
	void initVariables();

protected:
	sf::Texture texture;	//Not load a new texture in, but point to a texture that has already been loaded into a state
	sf::Sprite sprite;
	
	MovementComponent* movementComponent;

public:
	Entity();
	~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float decelartion);

	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float dir_x, const float dir_y, const float& dt);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

