#pragma once
#include "Platform.h"
#include "Character.h"
#include "Bullet.h"

#include "SFML/Graphics.hpp"
class Level
{	
	sf::Vector2f size;
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	std::vector<Platform*> platforms;

public:
	Level() = delete;
	Level(sf::Vector2f size, const std::string& backgroundTexture);
	bool checkCollision(sf::Vector2f direction, Character* character);
	bool checkBulletCollision(sf::Vector2f direction, Bullet bullet);
	bool checkPosition(Character* character);
	bool wall(Character* character);
	void draw(sf::RenderWindow& window);
	bool loadBackground(const std::string& texture);
	sf::Vector2f getSize();
	bool addPlatform(Platform* object);
	~Level();
};

