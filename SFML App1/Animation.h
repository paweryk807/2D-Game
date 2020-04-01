#pragma once
#include <SFML\Graphics.hpp>
#include "Cooldown.h"
class Animation
{
protected:
	sf::IntRect rect;
	Cooldown animationCooldown;
public:
	Animation() = default ;
	Animation(sf::IntRect& rect, sf::Time time);

	bool rotateSprite(sf::RectangleShape& sprite, const char& direction);
	void restartCooldown();

	void setAnimTime(sf::Time animT);
	void setRect(sf::IntRect& rect);

	sf::Time getAnimTime();
	sf::IntRect getRect();
	Cooldown getAnimationCooldown();

	~Animation();
};

