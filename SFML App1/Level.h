#pragma once
#include "Platform.h"
#include "Player.h"
class Level
{
	std::vector<Platform> platforms;

public:
	Level() = default;
	Level(sf::Texture& platformTexture);
	~Level();

	bool checkCollision(sf::Vector2f direction, Player& player);

	void draw(sf::RenderWindow& window);
};

