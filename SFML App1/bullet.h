#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include "character.h"
#include "Cooldown.h"
#include "Utils.h"

class Bullet : public sf::Drawable
{
	void setVelocity(sf::Vector2f vel);
protected:
	bool used;
	Cooldown cooldown;
	sf::RectangleShape colid;
	sf::Vector2f velocity;
	sf::CircleShape sprite;

public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	Bullet() = default;
	Bullet(sf::Vector2f startPos);
	Bullet(sf::Vector2f startPos, float speed);
	void setScale(sf::Vector2f scale);
	void setSize(float size);
	void setTime(sf::Time time);
	void setDirection(Character* character);
	void upgrade(int lvl);

	void refresh();
	void restart(sf::Vector2f pos);
	bool hit(Character* character);
	void hide();
	void setUse(bool use);

	bool isUsed();
	sf::CircleShape getSprite();
	sf::Vector2f getVelocity();
	Cooldown getCooldown();
	Collider getCollider();

	~Bullet() = default;
};
