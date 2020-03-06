#pragma once
#include <SFML\Graphics.hpp>
class Collider
{
	sf::RectangleShape& body;
public: 
	Collider(sf::RectangleShape& body);
	~Collider();
	void move(float dx, float dy);
	bool checkCollision(Collider other, sf::Vector2f& direction, float push);
	sf::Vector2f getPosition();
	sf::Vector2f getHalfSize();

};

