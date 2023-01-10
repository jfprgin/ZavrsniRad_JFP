#include "stdafx.h"
#include "HealthPack.h"

//Initializer functions
void HealthPack::initTextures()
{
	this->animationComponent->addAnimation("HEALTH", 10.f, 0, 0, 4, 0, 64, 64);
}


//Constructor and Destructor
HealthPack::HealthPack(sf::Texture& texture_sheet, float pos_x, float pos_y)
	: hp(20), exploding(false)
{
	this->createAnimationComponent(texture_sheet);
	this->createHitboxComponent(this->sprite, -16.f, -16.f, 64.f, 64.f);

	this->initTextures();

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
}
