#pragma once

#include"stdafx.h"

//NOT FINNISHED
class AnimationComponent
{
private:
	class Animation
	{
	public:
		//Variables
		sf::Texture& textureSheet;
		float speed;
		float timer;
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect endRect;

		Animation(sf::Texture& textureSheet, float speed, int start_x, int start_y, int end_x, int end_y, int width, int height)
			: textureSheet(textureSheet), speed(speed), width(width), height(height)
		{
			this->width = width;
			this->height = height;
			this->startRect = sf::IntRect(start_x, start_y, width, height);
			this->endRect = sf::IntRect(start_x, start_y, width, height);
			
		}

		//Functions
		void update(const float& dt)
		{

		}

		void pause();
		void reset();
	};

	std::map<std::string, Animation> animations;

public:
	AnimationComponent();
	~AnimationComponent();

	//Functions
};

