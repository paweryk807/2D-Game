#pragma once
#include "Enemy.h"
#include "SoldierAnimation.h"
#include "Bullet.h"

//Defaultowo na pozycji 0 Idle, 1 Run, 2 Jump, 3 Death 
class Soldier : public Enemy
{
	sf::Vector2f prevPos;
	std::vector<sf::Texture> texture;
	SoldierAnimation animation;
	Bullet* bullet;

public:
	Soldier() = delete;
	Soldier(std::vector<std::string>& textures);
	~Soldier();

	void addAmmunition(Bullet* bullet);

	void moveRight();

	void moveLeft();

	void idle();

	void jump();

	void setSpeed(float temp, sf::Time tempAnim);

	void setAnimation(SoldierAnimation& a);

	//bool isDead();

	bool refresh(const Player& player, bool wall);


	bool loadTextures(std::vector<std::string>& textures);

};


