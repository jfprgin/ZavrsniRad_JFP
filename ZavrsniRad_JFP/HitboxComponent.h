#pragma once

#include"stdafx.h"

//DONE
class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;

	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float wifth, float height);
	~HitboxComponent();

	//Accessors
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	//Modifiers
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);

	//Functions
	bool intersect(const sf::FloatRect& fRect);

	void update();
	void render(sf::RenderTarget& target);
};

