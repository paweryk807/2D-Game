#pragma once
#include "Character.h"
#include "Bullet.h"

class PlasmaDrone : public Character {
	std::vector<Bullet> bullets;
	std::vector<sf::Texture> texture;
	CharacterAnimation animation;
	utils::PlasmaDroneState state;
	float strength;
	bool changeDirectionX;
	bool changeDirectionY;

	void prepareToFly();
	void prepareToExplode();
	void prepareToFire();

	//void moveRight();

	//void moveLeft();

	//void moveUp();
	
	//void moveDown();

	//void explode();

	bool loadTextures(std::vector<std::string>& textures);

	void createBullets();


public:
	PlasmaDrone();
	bool refresh(const Player& player, bool wall);
	void levelUp(int round);
	void draw(sf::RenderTarget& target, sf::RenderStates state);
	//Collider getCollider();

};