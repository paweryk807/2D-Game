#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include <iostream>
class Platform
{
	sf::RectangleShape body;	
	sf::Texture platformTexture;


public:
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Platform();
	
	void draw(sf::RenderWindow& window);
	Collider getCollider();
};

