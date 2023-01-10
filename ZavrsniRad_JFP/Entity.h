#pragma once

#include"HitboxComponent.h"
#include"MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:
	void initVariables();

protected:
	sf::Texture texture;	//Not load a new texture in, but point to a texture that has already been loaded into a state
	sf::Sprite sprite;
	
	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

public:
	Entity();
	~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float decelartion);
	void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	void createAnimationComponent(sf::Texture& texture_sheet);

	//Accessors
	virtual MovementComponent* getMovementComponent();
	virtual AnimationComponent* getAnimationComponent();

	const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2f& getSpritePosition() const;
	virtual const sf::Vector2f getCenter() const;
	virtual const sf::Vector2f getSpriteCenter() const;
	virtual const sf::FloatRect getGlobalBounds() const;

	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void rotate(const float dir, const float& dt);
	virtual void movement(const float& dt);
	virtual void move(const float dir_x, const float dir_y, const float& dt);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();
	void setNormalMovement();
	void setBoostMovement();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target, const bool show_hitbox) = 0;
};

