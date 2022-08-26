#pragma once

#include"stdafx.h"

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;

	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite sprite, float offset_x, float offset_y, float wifth, float height);
	~HitboxComponent();

	//Functions
	bool checkIntersect(const sf::FloatRect& fRect);

	void update();
	void render(sf::RenderTarget& target);
};

