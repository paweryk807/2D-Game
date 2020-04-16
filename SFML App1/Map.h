#pragma once
#include <fstream>
#include <string>
#include "TileMap.h"
#include "Collider.h"
#include "Character.h"
#include "Bullet.h"
class Map {
	unsigned int* tab;
	TileMap tiles;
	std::vector<Collider*> platforms;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	void setCollider(const unsigned int sizeTab);

	//Collider* colliderTab;
public: 
	Map() = delete;
	Map(unsigned int sizeParam, const std::string& lvlDirectory);
	bool loadLevelToTab(const std::string& directory, unsigned int tabSize); // Podczas ladowania poziomu z pliku liczy jednostki wymagajace zaimplementowania kolizjii i dodaje je do ColliderTab
	bool checkCollision(sf::Vector2f direction, Character* character);
	bool checkBulletCollision(sf::Vector2f direction, Bullet bullet);
	bool checkPosition(Character* character);
	bool loadBackground(const std::string& texture);
	bool wall(Character* character);
	sf::Vector2f getSize() const;
	void draw(sf::RenderWindow& window) const;
};

