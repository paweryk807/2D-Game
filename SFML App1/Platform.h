#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
class Platform
{
	sf::RectangleShape body;

public:
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Platform();
	
	void draw(sf::RenderWindow& window);
	Collider getCollider();
};

