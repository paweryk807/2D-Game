#pragma once
#include "Platform.h"
#include "Character.h"
#include "Bullet.h"
#include "TileMap.h"

#include "SFML/Graphics.hpp"
#define SHEET  "images/sheet.png"
#define TILES "images/TileSet.png"
class Level
{	
	TileMap tMap;
	sf::Vector2f size;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	std::vector<Platform*> platforms;
	sf::VertexArray textures;
public:
	Level() = delete;
	Level(sf::Vector2f size, const std::string& backgroundTexture);
	bool checkCollision(sf::Vector2f direction, Character* character);
	bool checkBulletCollision(sf::Vector2f direction, Bullet bullet);
	bool checkPosition(Character* character);
	bool wall(Character* character);
	void draw(sf::RenderWindow& window);
	bool loadBackground(const std::string& texture);
	void reset();
	sf::Vector2f getSize();
	bool addPlatform(sf::Vector2f pos);
	~Level();
};

