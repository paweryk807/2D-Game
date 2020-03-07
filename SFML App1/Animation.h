#pragma once
#include <SFML/Graphics.hpp>
class Animation
{
	sf::IntRect rect;
	sf::Clock animClock;
	sf::Time animTime;
public:
	Animation() = default ;
	Animation(sf::IntRect rect, sf::Time time);
	
	bool oX(int width, int leftStart, int leftEnd, sf::RectangleShape& sprite); //width - szerokosc tekstury leftStart - pozycja startowa z pliku , leftEnd - koncowa 
	bool oY(int width, int leftStart, int leftEnd, sf::RectangleShape& sprite);
	bool jump(int width, int leftStart, int leftEnd, sf::RectangleShape& sprite,  sf::Vector2f velocity);
	bool rotateSprite(sf::RectangleShape& sprite, const char& direction);
	
	void setAnimTime(sf::Time animT);
	void setRect(sf::IntRect rect);
	 
	~Animation();
};

