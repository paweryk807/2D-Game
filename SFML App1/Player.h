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
	CharacterAnimation animation;


public:	
	Player() = default;
	Player(const sf::Texture &temp);
	void moveUp();
	void setExp(float nExp);
	void refresh();
	void moveDown();
	void moveRight();
	void moveLeft();
	void jump();
	void setSpeed(float temp, sf::Time tempAnim);
	void setAnimation(CharacterAnimation& a);
	void setLevel(int lvl);
	void setAtackSpeed(float aSpd);
	void setStrength(float str);
	float getStrength();
	float getAtackSpeed();
	float getExp();
	int getLevel();
	~Player() = default;

};

