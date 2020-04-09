#pragma once
#include <SFML\Graphics.hpp>
class Collider
{
	sf::RectangleShape& body;
public: 
	Collider() = delete;
	Collider(sf::RectangleShape& body);
	~Collider();
	void move(float dx, float dy);
	void setBody(sf::RectangleShape sh);	
	sf::RectangleShape getBody();	
	void setPosition(sf::Vector2f pos);

	bool checkCollisionX(Collider other) ;
	bool checkCollision(Collider other, sf::Vector2f& direction, float push);
	bool onCollision(Collider other);
	sf::Vector2f getPosition();
	sf::Vector2f getHalfSize();

};

