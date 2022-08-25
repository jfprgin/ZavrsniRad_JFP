#pragma once

#include"stdafx.h"

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;

public:
	HitboxComponent(sf::Sprite sprite, float offset_x, float offset_y, float wifth, float height);
	~HitboxComponent();

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

