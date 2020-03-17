#pragma once
#include "Character.h"
#include "Player.h"
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
	void refresh(Player player);
	~Enemy() = default;
};

