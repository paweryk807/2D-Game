#pragma once
#include "Enemy.h"
#include "SoldierAnimation.h"

//Defaultowo na pozycji 0 Idle, 1 Run, 2 Jump, 3 Death 
class Soldier : public Enemy
{
	std::vector<sf::Texture> texture;
	SoldierAnimation animation;
public:
	Soldier() = delete;
	Soldier(std::vector<std::string>& textures);

	void moveRight();

	void moveLeft();

	void idle();

	void jump();

	void setSpeed(float temp, sf::Time tempAnim);

	void setAnimation(SoldierAnimation& a);

	void refresh(const Player& player, bool wall);


	bool loadTextures(std::vector<std::string>& textures);

};


