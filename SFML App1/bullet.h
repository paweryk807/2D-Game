#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include "Character.h"
#define TEXTURE_PATH "images/bullets.png"

class Bullet
{
	sf::Texture texture;
	sf::CircleShape sprite; 
	sf::Vector2f velocity;
	sf::IntRect rect;
	Cooldown cooldown;
	sf::RectangleShape colid;
public:
	Bullet(sf::Vector2f startPos);

	void setScale(sf::Vector2f scale);
	bool loadTexture(const std::string path);
	void refresh();
	void restart(); 
	void setDirection(Character* character);
	sf::CircleShape getSprite();
	sf::Vector2f getVelocity();
	Cooldown getCooldown();
	void setIntRect(sf::IntRect rect);
	void setVelocity(sf::Vector2f vel);
	Collider getCollider();
	~Bullet() = default;
};

