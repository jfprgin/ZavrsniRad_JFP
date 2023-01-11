#pragma once
#include "Entity.h"
#include "Random.h"

class HealthPack :
    public Entity
{
private:
	//Variables
	int hp;
	bool exploding;

	Utils::RandomNumberGenerator rng;

	//Initializer functions
	void initAnimations();

public:
	//Accessors
	const int& getHP() const;

	sf::Vector2f const& getPosition() const { return this->sprite.getPosition(); }
	sf::FloatRect getBoundingBox() const { return this->sprite.getGlobalBounds(); }

	//Constructor and Destructor
	HealthPack(sf::Texture& texture, float pos_x, float pos_y);//, Player* player);
	~HealthPack();

	//Functions
	void Destroy();

	void updateAnimations(const float& dt);

	void update(const float& dt);
	void render(sf::RenderTarget& target, const bool show_hitbox = false);
};

