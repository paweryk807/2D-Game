#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include <iostream>
class Platform
{
	sf::RectangleShape body;
	sf::Texture texture;

public:
	Platform(const std::string& texture, sf::Vector2f size, sf::Vector2f position);
	~Platform();
	
	
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	sf::RectangleShape getBody();
	bool loadTexture(const std::string& tFile);
	Collider getCollider();
};

