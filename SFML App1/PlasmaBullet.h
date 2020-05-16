#pragma once
#include "bullet.h"
#include "PlasmaBulletAnimation.h"
class PlasmaBullet :
	public Bullet
{
	/*
	Klasa pocisku drona 
	*/
	sf::Texture texture;
	PlasmaBulletAnimation animation;
public:
	PlasmaBullet() = default;

	PlasmaBullet(sf::Vector2f pos, float seconds);
	/* Metoda odpowiedzialna za obranie przez pocisk kierunku, ktory pozwoli na uderzenie w gracza */
	void countDirection(Character* shooter, Character* target);

	void restart(sf::Vector2f pos);

	void refresh();
};
