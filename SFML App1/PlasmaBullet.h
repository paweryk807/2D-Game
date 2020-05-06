#pragma once
#include "bullet.h"
#include "PlasmaBulletAnimation.h"
class PlasmaBullet :
	public Bullet
{
	sf::Texture texture;
	PlasmaBulletAnimation animation;
public:	
	PlasmaBullet() = default;
	PlasmaBullet(sf::Vector2f pos, float seconds);
	void countDirection(Character* shooter, Character* target);

	void restart(sf::Vector2f pos);

	void refresh();
};

