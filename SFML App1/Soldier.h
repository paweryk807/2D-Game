#pragma once
#include "Player.h"
//#include "Bullet.h"

//Defaultowo na pozycji 0 Idle, 1 Run, 2 Jump, 3 Death
class Soldier : public Character
{
	sf::Vector2f prevPos;
	std::vector<sf::Texture>& texture;
	Bullet* bullet;
	float strength;
	/* Poruszanie sie i animacja postaci */
	void moveRight(); 

	void moveLeft();

	void idle();

	void jump();

public:

	Soldier() = delete;

	Soldier(std::vector<sf::Texture>& textures);

	~Soldier();

	void setStrength(float str);

	void reset();
	 
	void setSpeed(float temp, sf::Time tempAnim);

	void addAmmunition(Bullet& bullet);

	void levelUp(int round);

	float getStrength();
	/* Aktualizacja stanu postaci i AI */
	bool refresh(const Player& player, bool wall);
};
