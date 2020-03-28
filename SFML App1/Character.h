#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "CharacterAnimation.h"
#include<string>
#include<iostream>
class Character
{
private:
	float health;
	float speed;
	float jumpHeight;
	bool onAir;
	bool canJump;
	bool canClimb;
protected:
	sf::RectangleShape sprite; 
	sf::Vector2f velocity;
	CharacterAnimation animation;



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
	sf::IntRect getIntRect();
	void setSprite(sf::RectangleShape& sprite);

	CharacterAnimation getAnimation();
	
	void reset();
	void setJumpHeight(float height);
	void setCanClimb(bool climb);
	void setHealth(float hp);

	void setCanJump(bool jump);
	void setOnAir(bool air);
	void setSpeed(float, sf::Time);
	void setVelocity(sf::Vector2f vel);
	void setAnimation(CharacterAnimation& a);
	void moveUp();
	void jump();
	void moveDown();
	void moveLeft();
	void moveRight();
	void refresh();
	void onCollision(sf::Vector2f direction);
	void correctPosition(sf::Vector2f);
	sf::Vector2f getPosition() const;
	sf::RectangleShape getSprite() const;
	Collider getCollider();


};

