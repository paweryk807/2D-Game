#pragma once
#include "Character.h"
#include "Bullet.h"


//Defaultowo na pozycji 0 Idle, 1 Run, 2 Jump, 3 Death 
class Soldier : public Character
{
	sf::Vector2f prevPos;
	std::vector<sf::Texture> texture;
	CharacterAnimation animation;
	Bullet* bullet;
	float strength;

	void moveRight();

	void moveLeft();

	void idle();

	void jump();

	bool loadTextures(std::vector<std::string>& textures);

public:

	Soldier() = delete;

	Soldier(std::vector<std::string>& textures);

	~Soldier();

	void setStrength(float str);

	void reset();
	
	void setSpeed(float temp, sf::Time tempAnim);
	
	void setAnimation(CharacterAnimation& a);
	
	void addAmmunition(Bullet& bullet);

	void levelUp(int round);

	float getStrength();

	bool refresh(const Player& player, bool wall);
};


