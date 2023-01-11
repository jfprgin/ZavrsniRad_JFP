#include "stdafx.h"
#include "Explode.h"

//Initializer functions
void Explode::initAnimations()
{
	this->animationComponent->addAnimation("EXPLODE", 5.f, 0, 0, 5, 0, 100, 100);
}

//Accessors
bool Explode::isExplodeAnimationComplete() const
{
	return this->animationComponent->isDone("EXPLODE");
}


//Constructor and Destructor
Explode::Explode(sf::Texture& texture_sheet, float pos_x, float pos_y)
	: animationEnd(false)
{
	this->createAnimationComponent(texture_sheet);

	this->initAnimations();

	this->setPosition(pos_x, pos_y);
}

Explode::~Explode()
{
}

//Functions
void Explode::Destroy()
{
	this->animationEnd = true;
}

void Explode::updateAnimations(const float& dt)
{
	this->animationComponent->play("EXPLODE", dt);	
}


void Explode::update(const float& dt)
{
	this->updateAnimations(dt);
}

void Explode::render(sf::RenderTarget& target, const bool show_hitbox)
{
	target.draw(this->sprite);
}
