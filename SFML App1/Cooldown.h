#pragma once
#include<SFML/Graphics.hpp>
class Cooldown
{
	/*
	Klasa imitujaca limity czasowe obiektow m.in. czasy animacji, czasy zycia pociskow
	*/
	sf::Time time;
	sf::Clock clock;
public:
	Cooldown() = default;

	Cooldown(sf::Time t);
	
	~Cooldown() = default;
	/* Metoda informuje czy czas trawnia cooldown'u uplynal */
	bool elapsed();
	/* Metoda pozwala zmienic czas trwania cooldown'u */
	void setCooldown(sf::Time t);
	/* Restartuje cooldown na poczatkowosc wartosc */
	void restartCooldown();
	
	sf::Time getTime();
	
	sf::Clock getClock();
};
