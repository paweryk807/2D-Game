#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"

#define DEFAULT_PATH "images/characters.png"

class Player : public Character
{
private:
	float exp;
	int level;
	int prevLevel;
	float atackSpeed; 
	float strength;
	float maxHP;
	bool shield;

	CharacterAnimation animation;
    sf::RectangleShape shield_shape;


public:	


	Player() = default;
	Player(const sf::Texture &temp);
	float getMaxHP();
	void moveUp();
	void addExp(float nExp);
	sf::RectangleShape getShield();
	Collider getShieldCollider();
	bool leveled();
	void reset();
	bool refresh();
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
	bool getShieldState();
	void setShieldState(bool state);
	int getLevel();
	~Player() = default;

};

