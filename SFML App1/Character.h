#pragma once
#include <SFML/Graphics.hpp>
#include "CharacterAnimation.h"
#include "Collider.h"
#include<string>
#include<iostream>
class Character : public sf::Drawable
{
private:
	float health;
	float speed;
	float jumpHeight;
	bool onAir;
	bool canJump;
	bool canClimb;

	void moveUp();
	void jump();
	void moveDown();
	void moveLeft();
	void moveRight();

protected:
	sf::RectangleShape sprite; 
	sf::Vector2f velocity;


public:	
	Character();  // TU POWSTAJE DEFAULTOWA POSTAC :) 
	~Character();

	bool getCanClimb();
	float getHealth();
	bool getCanJump();
	bool getOnAir();
	float getSpeed();
	float getJumpHeight();
	sf::Vector2f getVelocity();
	void setSprite(sf::RectangleShape& sprite);

	void reset();
	void setJumpHeight(float height);
	void setCanClimb(bool climb);
	void setHealth(float hp);

	void setCanJump(bool jump);
	void setOnAir(bool air);
	void setVelocity(sf::Vector2f vel);

	void refresh();
	void onCollision(sf::Vector2f direction);
	void setSpeed(float temp);
	void correctPosition(sf::Vector2f);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
	sf::Vector2f getPosition() const;
	sf::RectangleShape getSprite() const;
	Collider getCollider();

};

