#pragma once
#include "Player.h"
#include "PlasmaBullet.h"

class PlasmaDrone : public Character {
	std::vector <std::unique_ptr<PlasmaBullet>>& bullets;
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
	PlasmaDrone(std::vector<std::unique_ptr<PlasmaBullet>>& bullets);
	bool refresh(Player* player, bool wall);
	void levelUp(int round);
	void draw(sf::RenderTarget& target, sf::RenderStates state);
	void reset();
	//Collider getCollider();

};