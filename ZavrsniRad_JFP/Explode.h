#pragma once
#include "Entity.h"
#include "Random.h"

class Explode :
	public Entity
{
private:
	//Variables
	bool animationEnd;

	Utils::RandomNumberGenerator rng;

	//Initializer functions
	void initExplodeTextures();

public:
	//Accessors
	bool isExplodeAnimationComplete() const;

	sf::Vector2f const& getPosition() const { return this->sprite.getPosition(); }
	sf::FloatRect getBoundingBox() const { return this->sprite.getGlobalBounds(); }

	//Constructor and Destructor
	Explode(sf::Texture& texture, float pos_x, float pos_y);//, Player* player);
	~Explode();

	//Functions
	void Destroy();

	void updateAnimations(const float& dt);

	void update(const float& dt);
	void render(sf::RenderTarget& target, const bool show_hitbox = false);
};

