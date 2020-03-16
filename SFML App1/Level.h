#pragma once
#include "Platform.h"
#include "Character.h"
#include "SFML/Graphics.hpp"
class Level
{	
	sf::Vector2i size;
	sf::RectangleShape background;
	std::vector<Platform> platforms;

public:
	Level() = delete;
	Level(sf::Vector2i size, sf::Texture& platformTexture);
	bool checkCollision(sf::Vector2f direction, Character* character);
	bool checkPosition(Character* character);
	void draw(sf::RenderWindow& window);
	sf::Vector2i getSize();
	~Level();
};

