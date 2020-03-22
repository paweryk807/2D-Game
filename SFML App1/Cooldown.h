#pragma once
#include<SFML/Graphics.hpp>
class Cooldown
{
	sf::Time time;
	sf::Clock clock;
public: 
	Cooldown() = default;
	Cooldown(sf::Time t);
	~Cooldown() = default;
	
	bool elapsed();
	void setCooldown(sf::Time t);
	void restartCooldown();
	sf::Time getTime();
	sf::Clock getClock();
};

