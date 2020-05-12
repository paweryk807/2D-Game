#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include <iostream>
class Platform
{
	sf::RectangleShape body;
public:
	Platform(sf::RectangleShape& body);
	~Platform();

	void setBody(sf::RectangleShape& body);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	sf::RectangleShape getBody();
	MapCollider getCollider();
};
