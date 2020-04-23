#pragma once
#include <fstream>
#include <string>
#include "TileMap.h"
#include "Platform.h"
#include "Character.h"
#include "Bullet.h"
class Map {
	unsigned int* tab;
	TileMap tiles;
	std::vector<Platform*> platforms;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	void setPlatforms(const unsigned int sizeTab);
	bool loadLevelToTab(const std::string& directory, unsigned int tabSize); // Podczas ladowania poziomu z pliku liczy jednostki wymagajace zaimplementowania kolizjii i dodaje je do ColliderTab
	bool loadBackground(const std::string& texture);


	//Collider* colliderTab;
public: 
	Map() = delete;
	Map(unsigned int sizeParam, const std::string& lvlDirectory);
	sf::Vector2f getSize() const;
	bool wall(Character* character) const;
	bool checkCollision(sf::Vector2f direction, Character* character) const;
	bool checkBulletCollision(sf::Vector2f direction, Bullet& bullet) const;
	bool checkPosition(Character* character);

	void draw(sf::RenderWindow& window) const;
};
