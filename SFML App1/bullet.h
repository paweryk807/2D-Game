#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
#include "Player.h"
#define TEXTURE_PATH "images/bullets.png"

class Bullet : public sf::Drawable
{
	sf::Texture texture;
	sf::CircleShape sprite; 
	sf::Vector2f velocity;
	Animation animation;
	sf::RectangleShape colid;
public:
	Bullet(sf::Vector2f startPos);
	Bullet(sf::Vector2f startPos, float speed);
	void setScale(sf::Vector2f scale);
	bool loadTexture(const std::string path);
	void refresh();
	void restart(sf::Vector2f pos);
	void upgrade(int lvl);
	bool hit(Character* character); 
	void hide();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	//bool hit(Player* character);*/
	void setDirection(Character* character);
	sf::CircleShape getSprite();
	sf::Vector2f getVelocity();
	Cooldown getCooldown();
	void setIntRect(sf::IntRect rect);
	void setVelocity(sf::Vector2f vel);
	Collider getCollider();
	~Bullet() = default;
};

