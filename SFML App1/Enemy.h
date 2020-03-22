#pragma once
#include "Character.h"
#include "Player.h"

#define DEFAULT_PATH "images/characters2.png"
class Enemy : public Character
{
	float atackSpeed; 
	float strength;
public:
	Enemy(const sf::Texture& temp);
	void setAtackSpeed(float aSpd);
	void setStrength(float str);
	float getStrength();
	float getAtackSpeed();
	void refresh(const Player& player, bool wall);
	~Enemy() = default;
};

