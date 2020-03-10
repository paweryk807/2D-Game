#pragma once
#include <SFML/Graphics.hpp>
class Animation
{
protected:
	sf::IntRect rect;
	sf::Clock animClock;
	sf::Time animTime;
public:
	Animation() = default ;
	Animation(sf::IntRect rect, sf::Time time);

	bool rotateSprite(sf::RectangleShape& sprite, const char& direction);
	
	void setAnimTime(sf::Time animT);
	void setRect(sf::IntRect rect);
	 
	~Animation();
};

