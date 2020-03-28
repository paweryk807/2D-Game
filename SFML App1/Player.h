#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"

#define DEFAULT_PATH "images/characters.png"

class Player : public Character
{
private:
	float exp;
	int level;
	float atackSpeed; 
	float strength;


public:	
	Player() = default;
	Player(const sf::Texture &temp);
	void setExp(float nExp);
	void setLevel(int lvl);
	void setAtackSpeed(float aSpd);
	void setStrength(float str);
	float getStrength();
	float getAtackSpeed();
	float getExp();
	int getLevel();
	~Player() = default;

};

