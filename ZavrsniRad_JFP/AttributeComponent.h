#pragma once

#include "stdafx.h"

class AttributeComponent
{
private:

public:
	//Stats
	int hp;
	int hpMax;
	int damage;
	int damageMax;

	//Constructor and Destructor
	AttributeComponent();
	~AttributeComponent();

	//Functions
	void updateStats(const bool reset);
	void update();
};

