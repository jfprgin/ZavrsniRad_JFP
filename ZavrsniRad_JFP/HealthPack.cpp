#include "stdafx.h"
#include "HealthPack.h"

//Initializer functions
void HealthPack::initAnimations()
{
	this->animationComponent->addAnimation("HEALTH", 30.f, 0, 0, 1, 0, 100, 100);
}


//Constructor and Destructor
HealthPack::HealthPack(sf::Texture& texture_sheet, float pos_x, float pos_y)
	: hp(20), exploding(false)
{
	this->createAnimationComponent(texture_sheet);
	this->createHitboxComponent(this->sprite, -50.f, -50.f, 100.f, 100.f);

	this->initAnimations();

	this->setPosition(pos_x, pos_y);
}

HealthPack::~HealthPack()
{
}

//Accessors
const int& HealthPack::getHP() const
{
	return this->hp;
}

//Functions
void HealthPack::Destroy()
{
	this->exploding = true;
}

void HealthPack::updateAnimations(const float& dt)
{
	this->animationComponent->play("HEALTH", dt);
}


void HealthPack::update(const float& dt)
{
	this->updateAnimations(dt);
}

void HealthPack::render(sf::RenderTarget& target, const bool show_hitbox)
{
	target.draw(this->sprite);

	if (show_hitbox)
	{
		this->hitboxComponent->render(target);
	}
}
