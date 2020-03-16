#pragma once
#include "Character.h"
class Enemy : public Character
{
	float atackSpeed; 
	float strength;
public:
	Enemy() = default;
	Enemy(const sf::Texture& temp);
	void setAtackSpeed(float aSpd);
	void setStrength(float str);
	float getStrength();
	float getAtackSpeed();
	~Enemy() = default;
};

