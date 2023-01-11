#pragma once

#include "Entity.h"
#include "Bullet.h"
#include "Gui.h"
#include "Random.h"

//enum player { IDLE = 0, DAMAGE, HEALING, BOOST };

class Player :
	public Entity
{
private:
	//Variables

	//HP and Damage
	int hp;
	int hpMax;

	int bulletDamage;

	//sf::Clock damageTimer;
	//sf::Int32 damageTimerMax;

	//Score
	int score;

	//Boost
	float boostTimer;
	float boostTimerMax;

	//Timer for taking damage, healing and boost animation because it won't work properly
	float damageAnimationTimer;
	float damageAnimationTimerMax;
	float healingAnimationTimer;
	float healingAnimationTimerMax;
	float boostAnimationTimer;
	float boostAnimationTimerMax;

	bool isDestroyed;

	Utils::RandomNumberGenerator rng;

	//Initializer functions
	void initAnimations();

public:
	//Accessors
	bool isDestoryComplete() const;
	
	const int& getHP() const;
	const int& getHPMax() const;

	//const bool getDamageTimer();
	int getDamage();

	int getScore();

	const float getDirectionX() const;
	const float getDirectionY() const;

	const float getBoost() const;
	const float getBoostMax() const;

	//Modifiers
	void loseHP(const int hp);
	void gainHP(const int hp);

	void AddScore(int modifier);

	//Animations
	void setDamageAnimation(const float& dt);
	void setHealingAnimation(const float& dt);
	void setBoostAnimation(const float& dt);

	void setBoostTimer(const float boost_timer);

	//Constructor and Destructor
	Player(float x, float y, sf::Texture& texture_sheet, float boost_timer, float boost_timer_max);
	~Player();

	//Functions
	void Destroy();

	void updateAnimation(const float& dt);
	void update(const float& dt);

	void render(sf::RenderTarget& target, const bool show_hitbox = false);
};

